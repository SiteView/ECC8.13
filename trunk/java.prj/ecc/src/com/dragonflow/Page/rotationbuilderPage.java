/*
 * 
 * Created on 2005-3-9 22:12:36
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Page;

import java.io.File;
import java.io.FileOutputStream;

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequestException;

// Referenced classes of package com.dragonflow.Page:
// CGI

public class rotationbuilderPage extends com.dragonflow.Page.CGI
{

    java.lang.String action;
    int last;
    jgl.HashMap configHash;
    java.lang.String version;

    public rotationbuilderPage()
    {
        version = "v0.9a";
    }

    public void printBody()
        throws java.lang.Exception
    {
        if(!request.actionAllowed("_tools"))
        {
            throw new HTTPRequestException(557);
        }
        configHash = new HashMap();
        java.util.Enumeration enumeration = request.getVariables();
        action = request.getValue("action");
        if(action.equals("add"))
        {
            printButtonBar("rotationbuilder.htm", "");
            if(request.getValue("config").equals(""))
            {
                configHash = updateHashMap(enumeration, configHash);
                printAddForm(configHash);
                java.lang.String s = "" + request.getValue("rotationname") + "_" + request.getValue("account") + ".rot";
                saveConfig(configHash, s);
            } else
            {
                java.lang.String s1 = "" + request.getValue("config");
                configHash = loadConfig(configHash, s1);
                printAddForm(configHash);
                saveConfig(configHash, s1);
            }
        } else
        if(action.equals("save"))
        {
            configHash = updateHashMap(enumeration, configHash);
            printButtonBar("rotationbuilder.htm", "");
            java.lang.String s2 = request.getValue("rotationname");
            java.lang.String s3 = s2;
            if(s3.equals(""))
            {
                s3 = "defaultrotationbuilder";
            }
            if(s2.equals(""))
            {
                s2 = com.dragonflow.SiteView.Platform.getRoot() + "/htdocs/" + s3;
            } else
            {
                s2 = com.dragonflow.SiteView.Platform.getRoot() + "/htdocs/" + s3;
            }
            java.lang.String s4 = request.getAccount();
            for(int i = 1; i <= com.dragonflow.Utils.TextUtils.toInt((java.lang.String)configHash.get("last")) - 1;i++)/*dingbing.xu add i++*/
            {
                try
                {
                    java.io.PrintWriter printwriter = com.dragonflow.Utils.FileUtils.MakeOutputWriter(new FileOutputStream(s2 + "_" + i + "_" + s4 + ".htm"));
                    if(request.getValue("rotation").equals(""))
                    {
                        writerotation(printwriter, configHash, i);
                    } else
                    {
                        printwriter.println(request.getValue("rotation"));
                    }
                    printwriter.close();
                    outputStream.println("<b>File:" + s2 + "_" + i + "_" + s4 + ".htm was saved.</b><br>");
                    continue;
                }
                catch(java.io.IOException ioexception)
                {
                    outputStream.println("Couldn't save file:" + s2 + "_" + i + "_" + s4 + ".htm<br>");
                    ioexception.printStackTrace();
                    continue;
                }
                catch(java.lang.Exception exception)
                {
                    outputStream.println("Couldn't save file:" + s2 + "_" + i + "_" + s4 + ".htm<br>");
                    exception.printStackTrace();
                    //i++;/*delete by dingbing.xu*/
                }
            }

            java.lang.String s5 = "" + request.getValue("rotationname") + "_" + request.getValue("account") + ".rot";
            saveConfig(configHash, s5);
            outputStream.println("<br><br><a href=/SiteView/htdocs/" + request.getValue("rotationname") + "_1_" + request.getValue("account") + ".htm>Click to view rotation</a>");
            outputStream.println("<br><br><br><a href=\"/SiteView/cgi/go.exe/SiteView?page=rotationbuilder&account=" + request.getAccount() + "&config=" + request.getValue("rotationname") + "_" + request.getAccount() + ".rot&action=add\">Click to continue editing this rotation</a>");
        } else
        {
            printButtonBar("rotationbuilder.htm", "");
            outputStream.println("<h2>Configure rotationbuilder Tool " + version + "</h2>" + "<a href=/SiteView/htdocs/rotationbuilderhelp.htm >HELP</A><BR><table>" + "<form name=rotation method=get action=\"/SiteView/cgi/go.exe/SiteView\" >" + "<input type=hidden name=account value=" + request.getAccount() + ">" + "<input type=hidden name=page value=rotationbuilder>" + "<input type=hidden name=last value=1>" + "<input type=hidden name=action value=add>" + "<input type=hidden name=URL1 value=\"\">" + "<input type=hidden name=refresh1 value=\"\">" + "<input type=hidden name=title1 value=\"\">" + "<tr><td><b>rotation Name</b></td>" + "<td><input type=text size=50 name=rotationname value=defaultrotationbuilder" + "></td></tr>");
            outputStream.println("<tr><td><b>Load Config file</b></td><td>");
            printConfigSelect();
            outputStream.println("<br></td></tr></table><input type=submit value=\"submit\"><br></form>");
        }
        printFooter(outputStream);
    }

    public void printConfigSelect()
    {
        java.io.File file = new File(com.dragonflow.SiteView.Platform.getRoot() + "/templates.view");
        java.lang.String s = request.getAccount();
        try
        {
            java.lang.String as[] = file.list();
            outputStream.println("<select name=config size=1>");
            outputStream.println("<option value=\"\" ></option>");
            for(int i = 0; i < as.length; i++)
            {
                if(com.dragonflow.Utils.TextUtils.match(as[i], "/.*_" + s + ".rot$/"))
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
        outputStream.println("<form method=post action=\"/SiteView/cgi/go.exe/SiteView\" name=datasheet ><input type=radio name=action value=add checked=on ><b>Add Item</b><input type=radio name=action value=save ><b>Save rotation</b><input type=submit value=\"Update\">");
        outputStream.println("<table border=1 cellspacing=0><tr><th colspan=4>Current Configuration:" + (java.lang.String)hashmap.get("rotationname") + "/<a href=/SiteView/htdocs/rotationbuilderhelp.htm> HELP PAGE</A></th></tr>" + "<tr><th>#</th><th>URL</th><th>Refresh Time(default=60)</th><th>Title(optional)</th><th>DEL</TH>" + "</tr>");
        for(int i = 1; i <= com.dragonflow.Utils.TextUtils.toInt((java.lang.String)hashmap.get("last")); i++)
        {
            outputStream.println("<tr><td><b>" + i + "</b></td><td>" + "<input type=text size=70 name=URL" + i + " value=\"" + (java.lang.String)hashmap.get("URL" + i) + "\">");
            outputStream.println("</td><td><input type=text size=4 name=refresh" + i + " value=\"" + (java.lang.String)hashmap.get("refresh" + i) + "\">");
            outputStream.println("</td><td>");
            outputStream.println("<input type=text size=20 name=title" + i + " value=\"" + (java.lang.String)hashmap.get("title" + i) + "\">");
            outputStream.println("</td><td>");
            outputStream.println("<input type=checkbox name=delete" + i + " ></td></tr>");
        }

        outputStream.println("</table><input type=hidden name=page value=rotationbuilder><input type=hidden name=account value=" + request.getAccount() + ">" + "<input type=hidden name=last value=" + (java.lang.String)hashmap.get("last") + ">" + "<table border=0>" + "<tr><td>rotation Name</td><td><input type=text size=50 name=rotationname value=" + (java.lang.String)hashmap.get("rotationname") + "></td></tr>" + "<tr><td>Load Config file</td><td>");
        printConfigSelect();
        outputStream.println("<input type=submit value=\"Update\"></td></tr></table>");
    }

    public void writerotation(java.io.PrintWriter printwriter, jgl.HashMap hashmap, int i)
    {
        int j;
        if(i == com.dragonflow.Utils.TextUtils.toInt((java.lang.String)hashmap.get("last")) - 1)
        {
            j = 1;
        } else
        {
            j = i + 1;
        }
        java.lang.String s = (java.lang.String)hashmap.get("rotationname");
        java.lang.String s1 = (java.lang.String)hashmap.get("account");
        java.lang.String s2 = "/SiteView/htdocs/" + s + "_" + j + "_" + s1 + ".htm";
        java.lang.String s3 = (java.lang.String)hashmap.get("refresh" + i);
        if(s3.equals(""))
        {
            s3 = "60";
        }
        java.lang.String s4 = (java.lang.String)hashmap.get("title" + i);
        if(s4.equals(""))
        {
            s4 = "" + s + "_" + i + "_" + s1 + ".htm";
        }
        printwriter.println("<html>\r<head>\r<title>" + s4 + "</title>\r" + "<meta http-equiv=\"Expires\" content=\"0\">\r" + "<meta http-equiv=\"Pragma\" content=\"no-cache\">\r" + "<meta HTTP-EQUIV=\"Refresh\" CONTENT=\"" + s3 + "; URL=" + s2 + "\">\r" + "</head>\r" + "<frameset cols=\"*\">\r" + "<frame src=\"" + (java.lang.String)hashmap.get("URL" + i) + "\" scrolling=no>\r" + "</frameset>\r" + "</html>\r");
    }

    public void saveConfig(jgl.HashMap hashmap, java.lang.String s)
    {
        jgl.Array array = new Array();
        array.add(hashmap);
        try
        {
            com.dragonflow.Properties.FrameFile.writeToFile(com.dragonflow.SiteView.Platform.getRoot() + "/templates.view/" + s + "", array, "", true, true);
        }
        catch(java.io.IOException ioexception)
        {
            ioexception.printStackTrace();
        }
    }

    public jgl.HashMap updateHashMap(java.util.Enumeration enumeration, jgl.HashMap hashmap)
    {
        java.lang.String s;
        for(; enumeration.hasMoreElements(); hashmap.put(s, request.getValue(s)))
        {
            s = (java.lang.String)enumeration.nextElement();
        }

        int i = com.dragonflow.Utils.TextUtils.toInt((java.lang.String)hashmap.get("last"));
        if(!((java.lang.String)hashmap.get("URL" + i)).equals(""))
        {
            hashmap.put("last", "" + (i + 1));
            hashmap.put("URL" + (i + 1), "");
            hashmap.put("refresh" + (i + 1), "");
            hashmap.put("title" + (i + 1), "");
            hashmap.put("delete" + (i + 1), "");
        }
        int j = 0;
        i = com.dragonflow.Utils.TextUtils.toInt((java.lang.String)hashmap.get("last"));
        for(int k = 1; k <= i; k++)
        {
            java.lang.String s1 = "";
            if(hashmap.get("delete" + k) != null)
            {
                s1 = (java.lang.String)hashmap.get("delete" + k);
                hashmap.put("delete" + k, "");
            } else
            {
                s1 = "";
            }
            if(s1.equals("on"))
            {
                j++;
                hashmap.put("last", "" + (com.dragonflow.Utils.TextUtils.toInt((java.lang.String)hashmap.get("last")) - 1));
                continue;
            }
            if(j > 0)
            {
                hashmap.put("URL" + (k - j), (java.lang.String)hashmap.get("URL" + k));
                hashmap.put("refresh" + (k - j), (java.lang.String)hashmap.get("refresh" + k));
                hashmap.put("title" + (k - j), (java.lang.String)hashmap.get("title" + k));
                hashmap.put("URL" + k, "");
                hashmap.put("refresh" + k, "");
                hashmap.put("title" + k, "");
            }
        }

        return hashmap;
    }

    public jgl.HashMap loadConfig(jgl.HashMap hashmap, java.lang.String s)
    {
        try
        {
            jgl.Array array = com.dragonflow.Properties.FrameFile.readFromFile(com.dragonflow.SiteView.Platform.getRoot() + "/templates.view/" + s + "");
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
        com.dragonflow.Page.rotationbuilderPage rotationbuilderpage = new rotationbuilderPage();
        if(args.length > 0)
        {
            rotationbuilderpage.args = args;
        }
        rotationbuilderpage.handleRequest();
    }
}
