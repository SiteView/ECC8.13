/*
 * 
 * Created on 2005-3-9 22:12:36
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.Page;

import java.io.File;

import jgl.Array;
import jgl.HashMap;
import COM.dragonflow.HTTP.HTTPRequestException;

// Referenced classes of package COM.dragonflow.Page:
// CGI

public class videowallupdatePage extends COM.dragonflow.Page.CGI
{

    public static java.lang.Thread vwallthread;
    public static boolean isScrolling = true;
    java.lang.String action;
    int last;
    jgl.HashMap configHash;
    java.lang.String version;

    public videowallupdatePage()
    {
        version = "v0.9a";
    }

    public static void vwallrunner()
    {
        vwallthread = new Thread(new java.lang.Runnable() {

            public void run()
            {
                do
                {
                    try
                    {
                        if(COM.dragonflow.Page.videowallupdatePage.isScrolling)
                        {
                            COM.dragonflow.Utils.TextUtils.debugPrint("loading data");
                            COM.dragonflow.SiteView.VWALL.loadhashmap(COM.dragonflow.SiteView.VWALL.currentconfig);
                            COM.dragonflow.Utils.TextUtils.debugPrint("writing data");
                            COM.dragonflow.SiteView.VWALL.writeVwall();
                            COM.dragonflow.Utils.TextUtils.debugPrint("sleeping");
                        }
                        java.lang.Thread.sleep(30000L);
                    }
                    catch(java.lang.Exception exception)
                    {
                        return;
                    }
                } while(true);
            }

        });
        vwallthread.setDaemon(true);
        vwallthread.start();
    }

    public void printBody()
        throws java.lang.Exception
    {
        if(!request.actionAllowed("_tools"))
        {
            throw new HTTPRequestException(557);
        }
        if(vwallthread == null)
        {
            COM.dragonflow.Page.videowallupdatePage.vwallrunner();
        }
        configHash = new HashMap();
        java.util.Enumeration enumeration = request.getVariables();
        action = request.getValue("action");
        if(action.equals("add") || action.equals("stop") || action.equals("start") || action == null || action.equals(""))
        {
            if(action.equals("stop") && isScrolling)
            {
                isScrolling = false;
            }
            if(action.equals("start") && !isScrolling)
            {
                isScrolling = true;
            }
            if(action == null || action.equals(""))
            {
                request.setValue("config", "videowallupdate_administrator.vid");
                request.setValue("vwallname", "videowallupdate");
                COM.dragonflow.Utils.TextUtils.debugPrint("config=" + request.getValue("config"));
            }
            printButtonBar("videowallupdate.htm", "");
            jgl.HashMap hashmap = new HashMap();
            java.lang.String s1 = "" + request.getValue("vwallname") + "_" + request.getAccount() + ".vid";
            hashmap = loadConfig(hashmap, s1);
            java.lang.String s2 = (java.lang.String)hashmap.get("lastupdate");
            long l = COM.dragonflow.Utils.TextUtils.toLong(request.getValue("timemillis"));
            long l1 = COM.dragonflow.Utils.TextUtils.toLong(s2);
            if(request.getValue("config") != null && !request.getValue("config").equals(""))
            {
                configHash = loadConfig(configHash, request.getValue("config"));
                java.lang.String s4 = (java.lang.String)configHash.get("last");
                configHash.put("message" + s4, "");
                configHash.put("color" + s4, "");
                configHash.put("linenum" + s4, "");
                configHash.put("colnum" + s4, "");
                configHash.put("timeout" + s4, "");
                configHash.put("delete" + s4, "");
                configHash.put("starttime" + s4, "");
                saveConfig(configHash, request.getValue("config"));
                printAddForm(configHash);
            } else
            if(!request.getValue("vwallname").equals("") && l < l1)
            {
                java.lang.String s5 = request.getValue("vwallname") + "_" + request.getAccount() + ".vid";
                configHash = loadConfig(configHash, s5);
                java.lang.String s7 = (java.lang.String)configHash.get("last");
                configHash.put("message" + s7, "");
                configHash.put("color" + s7, "");
                configHash.put("linenum" + s7, "");
                configHash.put("colnum" + s7, "");
                configHash.put("timeout" + s7, "");
                configHash.put("delete" + s7, "");
                configHash.put("starttime" + s7, "");
                printAddForm(configHash);
            } else
            {
                java.lang.String s6 = request.getValue("vwallname") + "_" + request.getAccount() + ".vid";
                configHash = updateHashMap(enumeration, configHash);
                saveConfig(configHash, s6);
                printAddForm(configHash);
            }
        } else
        if(action.equals("post"))
        {
            java.lang.String s = "" + request.getValue("vwallname");
            s = s + "_" + request.getAccount() + ".vid";
            configHash = loadConfig(configHash, s);
            int i = COM.dragonflow.Utils.TextUtils.toInt((java.lang.String)configHash.get("last"));
            if(!request.getValue("message").equals(""))
            {
                configHash.put("last", "" + (i + 1));
                configHash.put("message" + i, "" + request.getValue("message"));
                configHash.put("color" + i, "" + request.getValue("color"));
                configHash.put("linenum" + i, "" + request.getValue("linenum"));
                configHash.put("colnum" + i, "" + request.getValue("colnum"));
                if(request.getValue("timeout").equals(""))
                {
                    configHash.put("timeout" + i, "60");
                } else
                {
                    configHash.put("timeout" + i, "" + request.getValue("timeout"));
                }
                configHash.put("starttime" + i, "" + COM.dragonflow.SiteView.Platform.timeMillis());
            }
            saveConfig(configHash, s);
            jgl.HashMap hashmap1 = new HashMap();
            java.lang.String s3 = "videowallupdate_administrator.vid";
            hashmap1 = loadConfig(hashmap1, s3);
            printButtonBar("videowallupdate.htm", "");
            printAddForm(hashmap1);
        } else
        {
            printButtonBar("videowallupdate.htm", "");
            outputStream.println("<h2>Configure Videowall Update Tool " + version + "</h2>" + "<BR><table>" + "<form name=vwall method=get action=\"/SiteView/cgi/go.exe/SiteView\" >" + "<input type=hidden name=account value=" + request.getAccount() + ">" + "<input type=hidden name=page value=videowallupdate>" + "<input type=hidden name=last value=1>" + "<input type=hidden name=action value=add>" + "<input type=hidden name=message1 value=\"\">" + "<input type=hidden name=color1 value=\"\">" + "<input type=hidden name=linenum1 value=\"\">" + "<input type=hidden name=colnum1 value=\"\">" + "<input type=hidden name=timeout1 value=\"\">" + "<input type=hidden name=starttime1 value=\"\">" + "<tr><td><b>vwall Name</b></td>" + "<td><input type=text size=50 name=vwallname value=defaultvideowallupdate" + "></td></tr>");
            outputStream.println("<tr><td><b>Load Config file</b></td><td>");
            printConfigSelect();
            outputStream.println("<br></td></tr></table><input type=submit value=\"submit\"><br></form>");
        }
        printFooter(outputStream);
    }

    public void printConfigSelect()
    {
        java.io.File file = new File(COM.dragonflow.SiteView.Platform.getRoot() + "/templates.view");
        java.lang.String s = request.getAccount();
        try
        {
            java.lang.String as[] = file.list();
            outputStream.println("<select name=config size=1>");
            outputStream.println("<option value=\"\" ></option>");
            for(int i = 0; i < as.length; i++)
            {
                if(COM.dragonflow.Utils.TextUtils.match(as[i], "/.*_" + s + ".vid$/"))
                {
                    outputStream.println("<option value=\"" + as[i] + "\" ");
                    outputStream.println(">" + as[i] + " </option>");
                }
            }

            outputStream.println("</select>");
        }
        catch(java.lang.Exception exception)
        {
            exception.printStackTrace();
        }
    }

    public void printAddForm(jgl.HashMap hashmap)
    {
        outputStream.println("<form method=post action=\"/SiteView/cgi/go.exe/SiteView\" name=datasheet >");
        outputStream.println("<input type=hidden name=action value=add><br><br>");
        outputStream.println("<table border=1 cellspacing=0><tr><th colspan=7><b>Update VideoWall Ticket Board</b></th></tr><tr><th>#</th><th>MESSAGE</th><th>Color</th><th>Line#</th><th>Col#</th><th>Timeout</th><th>DEL</TH></tr>");
        for(int i = 1; i < COM.dragonflow.Utils.TextUtils.toInt((java.lang.String)hashmap.get("last")); i++)
        {
            outputStream.println("<tr><td><b>" + i + "</b></td><td>" + "<input type=text size=80 name=message" + i + " value=\"" + (java.lang.String)hashmap.get("message" + i) + "\">");
            outputStream.println("</td><td><input type=text size=4 name=color" + i + " value=\"" + (java.lang.String)hashmap.get("color" + i) + "\">");
            outputStream.println("</td><td>");
            outputStream.println("<input type=text size=2 name=linenum" + i + " value=\"" + (java.lang.String)hashmap.get("linenum" + i) + "\">");
            outputStream.println("</td><td>");
            outputStream.println("<input type=text size=2 name=colnum" + i + " value=\"" + (java.lang.String)hashmap.get("colnum" + i) + "\">");
            outputStream.println("</td><td>");
            outputStream.println("<input type=text size=3 name=timeout" + i + " value=\"" + (java.lang.String)hashmap.get("timeout" + i) + "\">");
            outputStream.println("<input type=hidden name=starttime" + i + " value=\"" + (java.lang.String)hashmap.get("starttime" + i) + "\">");
            outputStream.println("</td><td>");
            outputStream.println("<input type=checkbox name=delete" + i + " ></td></tr>");
        }

        java.lang.String s = (java.lang.String)hashmap.get("last");
        outputStream.println("<input type=hidden name=page value=videowallupdate><input type=hidden name=message" + s + " value=\"\">" + "<input type=hidden name=color" + s + " value=\"\">");
        outputStream.println("<input type=hidden name=linenum" + s + " value=\"\">");
        outputStream.println("<input type=hidden name=colnum" + s + " value=\"\">");
        outputStream.println("<input type=hidden name=timeout" + s + " value=\"\">");
        outputStream.println("<input type=hidden name=delete" + s + " >");
        outputStream.println("</table><input type=hidden name=page value=videowallupdate><input type=hidden name=timemillis value=" + COM.dragonflow.SiteView.Platform.timeMillis() + ">" + "<input type=hidden name=account value=" + request.getAccount() + ">" + "<input type=hidden name=last value=" + (java.lang.String)hashmap.get("last") + ">");
        outputStream.println("<input type=hidden name=vwallname value=videowallupdate");
        outputStream.println("<input type=hidden name=config value=\"videowallupdate_administrator.vid\">");
        outputStream.println("<input type=submit value=\"Update\"></form><br>");
        outputStream.println("<form method=post action=\"/SiteView/cgi/go.exe/SiteView\" name=postsheet ><input type=hidden name=page value=videowallupdate><input type=hidden name=action value=post><input type=hidden name=vwallname value=videowallupdate><table border=1 cellspacing=0><tr><th colspan=6><b>Or add a new entry</th></tr><tr><th>#</th><th>MESSAGE</th><th>Color</th><th>Line#</th><th>Col#</th><th>Timeout</th><tr><tr><td><b>" + s + "</b></td><td>" + "<input type=text size=80 name=message value=\"\">" + "</td><td>" + "<input type=text size=4 name=color  value=\"\">" + "</td><td>");
        outputStream.println("<input type=text size=2 name=linenum value=\"\">");
        outputStream.println("</td><td>");
        outputStream.println("<input type=text size=2 name=colnum value=\"\">");
        outputStream.println("</td><td>");
        outputStream.println("<input type=text size=3 name=timeout value=\"\">");
        outputStream.println("</td></tr></table><input type=submit value=Add></form>");
    }

    public void saveConfig(jgl.HashMap hashmap, java.lang.String s)
    {
        COM.dragonflow.Utils.TextUtils.debugPrint("saving config from videowallupdate class");
        hashmap.put("lastupdate", java.lang.Long.toString(COM.dragonflow.SiteView.Platform.timeMillis()));
        jgl.Array array = new Array();
        array.add(hashmap);
        try
        {
            COM.dragonflow.Properties.FrameFile.writeToFile(COM.dragonflow.SiteView.Platform.getRoot() + "/templates.view/" + s + "", array, "", true, true);
        }
        catch(java.io.IOException ioexception)
        {
            ioexception.printStackTrace();
        }
    }

    public jgl.HashMap updateHashMap(java.util.Enumeration enumeration, jgl.HashMap hashmap)
    {
        while(enumeration.hasMoreElements()) 
        {
            java.lang.String s = (java.lang.String)enumeration.nextElement();
            java.lang.String s1 = request.getValue(s);
            if(s.startsWith("starttime") && !request.getValue("message" + s.substring(9, s.length())).equals("") && (s1 == null || s1.equals("") || s1.equals("null")))
            {
                hashmap.put(s, "" + COM.dragonflow.SiteView.Platform.timeMillis());
            } else
            if(s.startsWith("timeout") && !request.getValue("message" + s.substring(7, s.length())).equals("") && (s1 == null || s1.equals("") || s1.equals("null")))
            {
                hashmap.put(s, "60");
            } else
            {
                hashmap.put(s, request.getValue(s));
            }
        }
        int i = COM.dragonflow.Utils.TextUtils.toInt((java.lang.String)hashmap.get("last"));
        if(!((java.lang.String)hashmap.get("message" + i)).equals(""))
        {
            hashmap.put("last", "" + (i + 1));
            hashmap.put("message" + (i + 1), "");
            hashmap.put("color" + (i + 1), "");
            hashmap.put("linenum" + (i + 1), "");
            hashmap.put("colnum" + (i + 1), "");
            hashmap.put("timeout" + (i + 1), "");
            hashmap.put("delete" + (i + 1), "");
            hashmap.put("starttime" + (i + 1), "");
        }
        int j = 0;
        i = COM.dragonflow.Utils.TextUtils.toInt((java.lang.String)hashmap.get("last"));
        for(int k = 1; k < i; k++)
        {
            java.lang.String s2 = "";
            if(hashmap.get("delete" + k) != null)
            {
                s2 = (java.lang.String)hashmap.get("delete" + k);
                hashmap.put("delete" + k, "");
            } else
            {
                s2 = "";
            }
            if(s2.equals("on"))
            {
                j++;
                hashmap.put("last", "" + (COM.dragonflow.Utils.TextUtils.toInt((java.lang.String)hashmap.get("last")) - 1));
                continue;
            }
            if(j > 0)
            {
                hashmap.put("message" + (k - j), (java.lang.String)hashmap.get("message" + k));
                hashmap.put("color" + (k - j), (java.lang.String)hashmap.get("color" + k));
                hashmap.put("linenum" + (k - j), (java.lang.String)hashmap.get("linenum" + k));
                hashmap.put("colnum" + (k - j), (java.lang.String)hashmap.get("colnum" + k));
                hashmap.put("timeout" + (k - j), (java.lang.String)hashmap.get("timeout" + k));
                hashmap.put("starttime" + (k - j), (java.lang.String)hashmap.get("starttime" + k));
                hashmap.put("message" + k, "");
                hashmap.put("color" + k, "");
                hashmap.put("linenum" + k, "");
                hashmap.put("colnum" + k, "");
                hashmap.put("timeout" + k, "");
                hashmap.put("starttime" + k, "");
            }
        }

        return hashmap;
    }

    public jgl.HashMap loadConfig(jgl.HashMap hashmap, java.lang.String s)
    {
        try
        {
            jgl.Array array = COM.dragonflow.Properties.FrameFile.readFromFile(COM.dragonflow.SiteView.Platform.getRoot() + "/templates.view/" + s + "");
            if(array != null && array.size() > 0)
            {
                hashmap = (jgl.HashMap)array.at(0);
            }
        }
        catch(java.io.IOException ioexception)
        {
            ioexception.printStackTrace();
        }
        return hashmap;
    }

    public static void main(java.lang.String args[])
        throws java.io.IOException
    {
        COM.dragonflow.Page.videowallupdatePage videowallupdatepage = new videowallupdatePage();
        if(args.length > 0)
        {
            videowallupdatepage.args = args;
        }
        videowallupdatepage.handleRequest();
    }

}
