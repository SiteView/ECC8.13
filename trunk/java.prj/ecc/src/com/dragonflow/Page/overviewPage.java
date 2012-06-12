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
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.StringBufferInputStream;

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.Properties.LessEqualPropertyName;

// Referenced classes of package com.dragonflow.Page:
// CGI

public class overviewPage extends com.dragonflow.Page.CGI
{

    static final java.lang.String CURRENT_STATE_START = "<!--CURRENTSTATE\n";
    static final java.lang.String CURRENT_STATE_END = "ENDCURRENTSTATE-->\n";
    public static java.lang.String customCacheHeader = "<meta http-equiv=\"Expires\" content=\"0\">\n";
    int monitorCount;
    static final int GROUP = 0;
    static final int ID = 1;
    static final int NAME = 2;
    static final int CATEGORY = 3;
    static final int STATUS = 4;
    static final int LEVEL = 5;
    public static boolean debug = true;
    static jgl.HashMap EXCLUDE_MAP;
    public static java.lang.String OPEN_VARIABLE = "open";
    public static java.lang.String CLOSE_VARIABLE = "close";

    public overviewPage()
    {
        monitorCount = 0;
    }

    public com.dragonflow.Page.CGI.menus getNavItems(com.dragonflow.HTTP.HTTPRequest httprequest)
    {
        com.dragonflow.Page.CGI.menus menus1 = new CGI.menus();
        if(httprequest.actionAllowed("_browse"))
        {
            menus1.add(new CGI.menuItems("Browse", "browse", "", "page", "Browse Monitors"));
        }
        if(httprequest.actionAllowed("_preference"))
        {
            menus1.add(new CGI.menuItems("Remote UNIX", "machine", "", "page", "Add/Edit Remote UNIX/Linux profiles"));
            menus1.add(new CGI.menuItems("Remote NT", "ntmachine", "", "page", "Add/Edit Remote Win NT/2000 profiles"));
        }
        if(httprequest.actionAllowed("_tools"))
        {
            menus1.add(new CGI.menuItems("Tools", "monitor", "Tools", "operation", "Use monitor diagnostic tools"));
        }
        if(httprequest.actionAllowed("_progress"))
        {
            menus1.add(new CGI.menuItems("Progress", "Progress", "", "url", "View current monitoring progress"));
        }
        if(httprequest.actionAllowed("_browse"))
        {
            menus1.add(new CGI.menuItems("Summary", "monitorSummary", "", "page", "View current monitor settings"));
        }
        return menus1;
    }

    void printForm(java.lang.String s, jgl.Array array, jgl.HashMap hashmap)
        throws java.lang.Exception
    {
        java.lang.String s1 = request.getValue("server");
        java.lang.String s2 = s;
        jgl.HashMap hashmap1;
        if(s.equals("Edit"))
        {
            s2 = "Update";
            hashmap1 = com.dragonflow.SiteView.Server.findServer(array, s1);
        } else
        {
            s2 = "Add to ";
            hashmap1 = new HashMap();
        }
        java.lang.String s3 = s2 + " SiteView Server list";
        if(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "timeout").length() == 0)
        {
            hashmap1.put("timeout", "60");
        }
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.lang.StringBuffer stringbuffer1 = new StringBuffer();
        java.lang.StringBuffer stringbuffer2 = new StringBuffer();
        java.lang.StringBuffer stringbuffer3 = new StringBuffer();
        com.dragonflow.Properties.StringProperty.getPrivate(com.dragonflow.Page.overviewPage.getValue(hashmap1, "password"), "password", "overSuff", stringbuffer, stringbuffer1);
        com.dragonflow.Properties.StringProperty.getPrivate(com.dragonflow.Page.overviewPage.getValue(hashmap1, "proxypassword"), "proxypassword", "pOverSuff", stringbuffer2, stringbuffer3);
        printBodyHeader(s3);
        com.dragonflow.Page.CGI.menus menus1 = getNavItems(request);
        printButtonBar("MultiServ.htm", "", menus1);
        outputStream.println("<p><H2>" + s3 + "</H2>\n");
        outputStream.println("<FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST>\n<input type=hidden name=page value=overview>\n<input type=hidden name=account value=" + request.getAccount() + ">\n" + "<input type=hidden name=parent value=" + request.getValue("parent") + ">\n" + "<input type=hidden name=originalServer value=" + s1 + ">\n" + "<input type=hidden name=operation value=" + s + ">\n");
        outputStream.println("<TABLE>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Server Address</TD><TD><TABLE><TR><TD ALIGN=LEFT><input type=text name=server size=50 value=\"" + s1 + "\"></TD></TR>" + "<TR><TD><FONT SIZE=-1>the server address and SiteView port of the server (for example, demo." + com.dragonflow.SiteView.Platform.exampleDomain + ":8888)</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Title</TD><TD><TABLE><TR><TD ALIGN=LEFT><input type=text name=title size=50 value=\"" + com.dragonflow.Page.overviewPage.getValue(hashmap1, "title") + "\"></TD></TR>" + "<TR><TD><FONT SIZE=-1>optional title for this item in the Multi-View window, the default title is the server address</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        outputStream.println("</TABLE>");
        outputStream.println("<TABLE WIDTH=100%><TR><TD><input type=submit value=\"" + s2 + "\"> Server\n" + "</TD></TR></TABLE>");
        outputStream.println("<br><h3>Advanced Options</h3><TABLE>");
        outputStream.println("<TR><TD ALIGN=RIGHT>User Name</TD><TD><TABLE><TR><TD ALIGN=LEFT><input type=text name=username size=50 value=\"" + com.dragonflow.Page.overviewPage.getValue(hashmap1, "username") + "\"></TD></TR>" + "<TR><TD><FONT SIZE=-1>optional user name for connecting to the SiteView server, the default is to use the administrator user name</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Password</TD><TD><TABLE><TR><TD ALIGN=LEFT>" + stringbuffer.toString() + " size=50></TD></TR>" + stringbuffer1.toString() + "<TR><TD><FONT SIZE=-1>optional password for connecting to the SiteView server, the default is to use the administrator password</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Proxy</TD><TD><TABLE><TR><TD ALIGN=LEFT><input type=text name=proxy size=50 value=\"" + com.dragonflow.Page.overviewPage.getValue(hashmap1, "proxy") + "\"></TD></TR>" + "<TR><TD><FONT SIZE=-1>optional proxy server to use including port number (for example, proxy." + com.dragonflow.SiteView.Platform.exampleDomain + ":8080)</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Proxy User Name</TD><TD><TABLE><TR><TD ALIGN=LEFT><input type=text name=proxyusername size=50 value=\"" + com.dragonflow.Page.overviewPage.getValue(hashmap1, "proxyusername") + "\"></TD></TR>" + "<TR><TD><FONT SIZE=-1>optional user name for connecting through a proxy server</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Proxy Password</TD><TD><TABLE><TR><TD ALIGN=LEFT>" + stringbuffer2.toString() + " size=50></TD></TR>" + stringbuffer3.toString() + "<TR><TD><FONT SIZE=-1>optional password for connecting through a proxy server</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Timeout</TD><TD><TABLE><TR><TD ALIGN=LEFT><input type=text name=timeout size=10 value=\"" + com.dragonflow.Page.overviewPage.getValue(hashmap1, "timeout") + "\"></TD></TR>" + "<TR><TD><FONT SIZE=-1>optional timeout for retrieving information from the SiteView server</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Enable HTTPS</TD><TD><TABLE><TR><TD ALIGN=LEFT><input type=checkbox name=securehttp size=50 " + (com.dragonflow.Page.overviewPage.getValue(hashmap1, "securehttp").length() <= 0 ? "" : "checked") + "></TD></TR>" + "<TR><TD><FONT SIZE=-1>optional use for secure http server</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        outputStream.println("</TABLE>");
        outputStream.println("<TABLE WIDTH=100%><TR><TD><input type=submit value=\"" + s2 + "\"> Server\n" + "</TD></TR></TABLE>");
        outputStream.println("</FORM>");
        printFooter(outputStream);
    }

    void printGroupForm(java.lang.String s, jgl.Array array, jgl.HashMap hashmap)
        throws java.lang.Exception
    {
        java.lang.String s1 = request.getValue("server");
        java.lang.String s3 = s;
        jgl.HashMap hashmap1;
        java.lang.String s2;
        if(s.equals("AddGroup"))
        {
            s3 = "Add Group";
            hashmap1 = new HashMap();
            s2 = "Add Group to SiteView Server list";
        } else
        if(s.equals("EditGroup"))
        {
            s3 = "Update Group";
            hashmap1 = com.dragonflow.SiteView.Server.findServer(array, s1);
            s2 = "Edit Group in SiteView Server list";
        } else
        {
            throw new Exception("unknown operation: " + s);
        }
        printBodyHeader(s2);
        com.dragonflow.Page.CGI.menus menus1 = getNavItems(request);
        printButtonBar("MultiServ.htm", "", menus1);
        outputStream.println("<p><H2>" + s2 + "</H2>\n");
        outputStream.println("<FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST>\n<input type=hidden name=page value=overview>\n<input type=hidden name=account value=" + request.getAccount() + ">\n" + "<input type=hidden name=originalServer value=" + s1 + ">\n" + "<input type=hidden name=server value=\"" + s1 + "\">\n" + "<input type=hidden name=parent value=\"" + request.getValue("parent") + "\">\n" + "<input type=hidden name=operation value=" + s + ">\n");
        outputStream.println("<TABLE>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Group Name</TD><TD><TABLE><TR><TD ALIGN=LEFT><input type=text name=title size=50 value=\"" + com.dragonflow.Page.overviewPage.getValue(hashmap1, "title") + "\"></TD></TR>" + "<TR><TD><FONT SIZE=-1></FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        outputStream.println("</TABLE>");
        outputStream.println("<TABLE WIDTH=100%><TR><TD><input type=submit value=\"" + s3 + "\">\n" + "</TD></TR></TABLE>");
        outputStream.println("</FORM>");
        printFooter(outputStream);
    }

    void printAddForm(java.lang.String s)
        throws java.lang.Exception
    {
        if(!request.getAccount().equals("administrator"))
        {
            outputStream.println("<hr>Administrator access only<hr>");
            return;
        }
        java.lang.String s1 = request.getValue("server");
        jgl.Array array = com.dragonflow.SiteView.Server.readServers();
        if(request.isPost())
        {
            jgl.HashMap hashmap = new HashMap();
            hashmap.put("server", s1);
            hashmap.put("username", request.getValue("username"));
            hashmap.put("password", com.dragonflow.Properties.StringProperty.getPrivate(request, "password", "overSuff", null, null));
            hashmap.put("title", request.getValue("title"));
            hashmap.put("proxy", request.getValue("proxy"));
            hashmap.put("proxyusername", request.getValue("proxyusername"));
            hashmap.put("proxypassword", com.dragonflow.Properties.StringProperty.getPrivate(request, "proxypassword", "pOverSuff", null, null));
            hashmap.put("timeout", request.getValue("timeout"));
            hashmap.put("parent", request.getValue("parent"));
            hashmap.put("usage", request.getValue("usage"));
            hashmap.put("securehttp", request.getValue("securehttp"));
            if(s.equals("Add"))
            {
                array.add(hashmap);
            } else
            {
                jgl.HashMap hashmap1 = com.dragonflow.SiteView.Server.findServer(array, request.getValue("originalServer"));
                array.remove(hashmap1);
                array.add(hashmap);
            }
            com.dragonflow.SiteView.Server.writeServers(array);
            java.lang.String s2 = "/SiteView/cgi/go.exe/SiteView?page=overview&operation=List&parent=" + request.getValue("parent") + "&account=" + request.getAccount();
            printRefreshPage(s2, 0);
        } else
        {
            printForm(s, array, new HashMap());
        }
    }

    void printAddGroupForm(java.lang.String s)
        throws java.lang.Exception
    {
        if(!request.getAccount().equals("administrator"))
        {
            outputStream.println("<hr>Administrator access only<hr>");
            return;
        }
        java.lang.String s1 = request.getValue("server");
        jgl.Array array = com.dragonflow.SiteView.Server.readServers();
        if(request.isPost())
        {
            jgl.HashMap hashmap = new HashMap();
            hashmap.put("server", s1);
            hashmap.put("title", request.getValue("title"));
            hashmap.put("parent", request.getValue("parent"));
            if(s.equals("AddGroup"))
            {
                java.lang.String s2 = com.dragonflow.Utils.TextUtils.keepChars(request.getValue("title"), "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
                hashmap.put("server", s2);
                hashmap.put("class", "Group");
                array.add(hashmap);
            } else
            {
                jgl.HashMap hashmap1 = com.dragonflow.SiteView.Server.findServer(array, request.getValue("originalServer"));
                array.remove(hashmap1);
                array.add(hashmap);
            }
            com.dragonflow.SiteView.Server.writeServers(array);
            java.lang.String s3 = "/SiteView/cgi/go.exe/SiteView?page=overview&operation=List&parent=" + request.getValue("parent") + "&account=" + request.getAccount();
            printRefreshPage(s3, 0);
        } else
        {
            printGroupForm(s, array, new HashMap());
        }
    }

    void printOpenCloseForm(java.lang.String s)
        throws java.lang.Exception
    {
        java.lang.String s1 = request.getValue("server");
        java.lang.String s2 = request.getValue("group");
        jgl.Array array = com.dragonflow.SiteView.Server.readServers();
        jgl.HashMap hashmap = com.dragonflow.SiteView.Server.findServer(array, s1);
        hashmap.remove(s2);
        hashmap.add(s2, s);
        java.lang.String s3 = "/SiteView/cgi/go.exe/SiteView?page=overview&account=" + request.getAccount();
        printRefreshPage(s3, 0);
    }

    void printListForm(java.lang.String s)
        throws java.io.IOException
    {
        if(!request.getAccount().equals("administrator"))
        {
            outputStream.println("<hr><h2>Administrator access only</h2><hr>");
            return;
        }
        java.lang.String s1 = "Servers";
        java.lang.String s2 = "MultiEdit.htm";
        if(request.getValue("server").length() > 0)
        {
            s2 = "MultiServ.htm";
        }
        printBodyHeader(s1);
        printButtonBar(s2, "");
        java.lang.String s3 = request.getValue("parent");
        if(s3.length() > 0)
        {
            jgl.HashMap hashmap = com.dragonflow.SiteView.Server.findServer(com.dragonflow.SiteView.Server.readServers(), s3);
            java.lang.String s4 = "";
            java.lang.String s5 = "Servers";
            java.lang.String s6 = s3;
            if(hashmap != null)
            {
                s6 = com.dragonflow.Page.overviewPage.getValue(hashmap, "title");
                s4 = com.dragonflow.Page.overviewPage.getValue(hashmap, "parent");
                jgl.HashMap hashmap3 = com.dragonflow.SiteView.Server.findServer(com.dragonflow.SiteView.Server.readServers(), s4);
                if(hashmap3 != null)
                {
                    s5 = com.dragonflow.Page.overviewPage.getValue(hashmap3, "title");
                }
            }
            java.lang.String s7 = "/SiteView/cgi/go.exe/SiteView?page=overview&operation=List&parent=" + s4 + "&account=" + request.getAccount();
            outputStream.println("<p><H2><a href=" + s7 + ">" + s5 + "</a>: " + s6 + "</H2><TABLE WIDTH=100% BORDER=2 cellspacing=0>" + "<TR><TH align=left>Name</TH>\n");
        } else
        {
            outputStream.println("<p><H2>SiteView Server List</H2><TABLE WIDTH=100% BORDER=2 cellspacing=0><TR><TH align=left>Name</TH>\n");
        }
        if(request.actionAllowed("_multiEdit"))
        {
            outputStream.println("<TH WIDTH=10%>Edit</TH><TH WIDTH=3%>Del</TH>");
        }
        outputStream.println("</TR>");
        jgl.Array array = com.dragonflow.SiteView.Server.getServers(s3, true);
        jgl.HashMap hashmap1 = getMasterConfig();
        java.util.Enumeration enumeration = array.elements();
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            jgl.HashMap hashmap2 = (jgl.HashMap)enumeration.nextElement();
            if(com.dragonflow.Utils.TextUtils.getValue(hashmap2, "hidden").length() == 0)
            {
                java.lang.String s8 = "";
                if(com.dragonflow.Page.overviewPage.getValue(hashmap2, "class").length() > 0)
                {
                    s8 = " CLASS=subgroup";
                }
                java.lang.String s9 = com.dragonflow.Utils.TextUtils.getValue(hashmap2, "server");
                java.lang.String s10 = com.dragonflow.Page.overviewPage.getValue(hashmap2, "title");
                if(request.actionAllowed("_multiEdit"))
                {
                    java.lang.String s11 = "/SiteView/cgi/go.exe/SiteView?page=overview&server=" + s9 + "&account=" + request.getAccount();
                    java.lang.String s12 = "<A href=" + s11 + "&operation=Delete&parent=" + s3 + ">X</a>";
                    java.lang.String s13 = "<A href=" + s11 + "&operation=Edit&parent=" + s3 + ">Edit</a>";
                    if(com.dragonflow.Page.overviewPage.getValue(hashmap2, "class").length() > 0)
                    {
                        s13 = "<A href=" + s11 + "&operation=List&parent=" + s9 + ">Edit</a>";
                        s12 = "<A href=" + s11 + "&operation=DeleteGroup>X</a>";
                    }
                    if(s9.equals("_local"))
                    {
                        s12 = "&nbsp;";
                    }
                    outputStream.println("<TR><TD" + s8 + " align=left>" + s10 + "</TD>" + "<TD" + s8 + ">" + s13 + "</TD>" + "<TD" + s8 + ">" + s12 + "</TD>" + "</TR>\n");
                } else
                {
                    outputStream.println("<TR><TD" + s8 + " align=left>" + s10 + "</TD>" + "</TR>\n");
                }
            }
        } while(true);
        outputStream.println("</TABLE><BR>");
        if(request.actionAllowed("_multiEdit"))
        {
            outputStream.println("\n<A HREF=/SiteView/cgi/go.exe/SiteView?page=overview&operation=Add&parent=" + s3 + "&account=" + request.getAccount() + ">Add</A> to the SiteView server list\n" + "\n<BR><A HREF=/SiteView/cgi/go.exe/SiteView?page=overview&operation=AddGroup&parent=" + s3 + "&account=" + request.getAccount() + ">Add</A> a group to the SiteView server list\n" + "\n<BR>");
            if(request.getValue("server").length() <= 0)
            {
                outputStream.println("<hr><h3>Multi-View Preferences</h3>");
                outputStream.println("<p><FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST><input type=hidden name=\"page\" value=\"overview\"><input type=hidden name=\"operation\" value=\"updateSettings\"><input type=hidden name=\"account\" value=" + request.getAccount() + ">");
                outputStream.println("<table align=\"left\" border=\"0\"><TR><TD></TD><TD></TD><TD WIDTH=\"50\"></TD></TR>\n");
                outputStream.println("<tr><td align=\"right\">Number of Columns:</td><td align=\"left\"><input type=\"text\" size=\"1\" max=\"2\" name=\"columns\" value=\"" + com.dragonflow.Page.overviewPage.getValue(hashmap1, "_overviewColumns") + "\"</td><td></td></tr>");
                outputStream.println("<tr><td align=\"right\">Refresh Rate:</td><td align=\"left\"><input type=\"text\" size=\"4\" max=\"6\" name=\"refresh\" value=\"" + com.dragonflow.Page.overviewPage.getValue(hashmap1, "_overviewRefreshRate") + "\"</td><td></td></tr>");
                outputStream.println("<tr><td align=\"right\">Multi-view Window Options:</td><td align=\"left\"><input type=\"text\" size=\"72\" name=\"ovrwindow\" value=\"" + com.dragonflow.Page.overviewPage.getValue(hashmap1, "_overviewOptions") + "\"</td><td></td></tr>");
                outputStream.println("<tr><td align=\"right\">Table Options:</td><td align=\"left\"><input type=\"text\" size=\"56\" name=\"taboptions\" value=\"" + com.dragonflow.Page.overviewPage.getValue(hashmap1, "_overviewTableOptions") + "\"</td><td></td></tr>");
                outputStream.println("<tr><td align=\"right\">Background Color:</td><td align=\"left\"><input type=\"text\" size=\"7\" max=\"7\" name=\"bgcolor\" value=\"" + com.dragonflow.Page.overviewPage.getValue(hashmap1, "_overviewBGColor") + "\"</td><td></td></tr>");
                outputStream.println("</table><br clear=all><hr><p><input type=submit name=\"savechanges\" value=\"Update\"> the Multi-view Settings</p>");
            }
        }
        printFooter(outputStream);
    }

    void updateSettings(java.lang.String s)
        throws java.lang.Exception
    {
        if(!request.getAccount().equals("administrator"))
        {
            outputStream.println("<hr>Administrator access only<hr>");
            return;
        }
        jgl.HashMap hashmap = getMasterConfig();
        if(request.getValue("columns").length() > 0 && com.dragonflow.Utils.TextUtils.isInteger(request.getValue("refresh")))
        {
            hashmap.put("_overviewColumns", request.getValue("columns"));
        }
        if(request.getValue("refresh").length() > 0 && com.dragonflow.Utils.TextUtils.isInteger(request.getValue("refresh")))
        {
            hashmap.put("_overviewRefreshRate", request.getValue("refresh"));
        }
        if(request.getValue("ovrwindow").length() > 0 || !request.getValue("ovrwindow").equals(hashmap.get("_overviewOptions").toString()))
        {
            hashmap.put("_overviewOptions", request.getValue("ovrwindow"));
        }
        if(request.getValue("taboptions").length() >= 0 || !request.getValue("taboptions").equals(hashmap.get("_overviewTableOptions").toString()))
        {
            hashmap.put("_overviewTableOptions", request.getValue("taboptions"));
        }
        if(request.getValue("bgcolor").length() >= 0 && request.getValue("bgcolor").length() <= 7)
        {
            hashmap.put("_overviewBGColor", request.getValue("bgcolor"));
        }
        java.lang.String s1 = "Servers";
        printBodyHeader(s1);
        printButtonBar("Multiview.htm", "");
        try
        {
            com.dragonflow.Page.overviewPage.saveMasterConfig(hashmap, request);
            printRefreshPage("/SiteView/cgi/go.exe/SiteView?page=overview&operation=List&account=" + request.getAccount(), 2);
            outputStream.println("<br><br><p>Saving Settings...</p>");
        }
        catch(java.lang.Exception exception)
        {
            printError("There was a problem writing the settings.", exception.toString(), "/SiteView/" + request.getAccountDirectory() + "/SiteView.html");
        }
        printFooter(outputStream);
    }

    void printDeleteForm(java.lang.String s)
        throws java.lang.Exception
    {
        if(!request.getAccount().equals("administrator"))
        {
            outputStream.println("<hr>Administrator access only<hr>");
            return;
        }
        java.lang.String s1 = request.getValue("server");
        jgl.Array array = com.dragonflow.SiteView.Server.readServers();
        jgl.HashMap hashmap = com.dragonflow.SiteView.Server.findServer(array, s1);
        java.lang.String s2 = com.dragonflow.Page.overviewPage.getValue(hashmap, "title");
        if(request.isPost())
        {
            try
            {
                array.remove(hashmap);
                com.dragonflow.SiteView.Server.writeServers(array);
                printRefreshPage("/SiteView/cgi/go.exe/SiteView?page=overview&operation=List&parent=" + request.getValue("parent") + "&account=" + request.getAccount(), 0);
            }
            catch(java.lang.Exception exception)
            {
                printError("There was a problem deleting the server.", exception.toString(), "/SiteView/" + request.getAccountDirectory() + "/SiteView.html");
            }
        } else
        {
            printBodyHeader("Delete Confirmation");
            outputStream.println("<FONT SIZE=+1>Are you sure you want to remove the server <B>" + s2 + "</B> from the SiteView Server list?</FONT>" + "<p><FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST>" + "<input type=hidden name=page value=overview>" + "<input type=hidden name=operation value=\"" + s + "\">" + "<input type=hidden name=parent value=\"" + request.getValue("parent") + "\">" + "<input type=hidden name=server value=\"" + s1 + "\">" + "<input type=hidden name=account value=" + request.getAccount() + ">" + "<TABLE WIDTH=100% BORDER=0><TR>" + "<TD WIDTH=6%></TD><TD WIDTH=41%><input type=submit value=\"" + s + "\"></TD>" + "<TD WIDTH=6%></TD><TD ALIGN=RIGHT WIDTH=41%><A HREF=/SiteView/cgi/go.exe/SiteView?page=overview&operation=List&account=" + request.getAccount() + ">Return to Detail</A></TD><TD WIDTH=6%></TD>" + "</TR></TABLE></FORM>");
            printFooter(outputStream);
        }
    }

    boolean isRelated(jgl.HashMap hashmap, java.lang.String s, jgl.Array array)
    {
        if(com.dragonflow.Page.overviewPage.getValue(hashmap, "server").equals(s))
        {
            return true;
        }
        java.lang.String s1 = com.dragonflow.Page.overviewPage.getValue(hashmap, "parent");
        if(s1.length() == 0)
        {
            return false;
        }
        jgl.HashMap hashmap1 = com.dragonflow.SiteView.Server.findServer(array, s);
        if(hashmap1 == null)
        {
            return false;
        } else
        {
            return isRelated(hashmap1, s, array);
        }
    }

    void printDeleteGroupForm(java.lang.String s)
        throws java.lang.Exception
    {
        if(!request.getAccount().equals("administrator"))
        {
            outputStream.println("<hr>Administrator access only<hr>");
            return;
        }
        java.lang.String s1 = request.getValue("server");
        jgl.Array array = com.dragonflow.SiteView.Server.readServers();
        jgl.HashMap hashmap = com.dragonflow.SiteView.Server.findServer(array, s1);
        java.lang.String s2 = s1;
        if(hashmap != null)
        {
            s2 = com.dragonflow.Page.overviewPage.getValue(hashmap, "title");
        }
        if(request.isPost())
        {
            try
            {
                jgl.Array array1 = new Array();
                java.util.Enumeration enumeration = array.elements();
                do
                {
                    if(!enumeration.hasMoreElements())
                    {
                        break;
                    }
                    jgl.HashMap hashmap1 = (jgl.HashMap)enumeration.nextElement();
                    if(!isRelated(hashmap1, s1, array))
                    {
                        array1.add(hashmap1);
                    }
                } while(true);
                com.dragonflow.SiteView.Server.writeServers(array1);
                printRefreshPage("/SiteView/cgi/go.exe/SiteView?page=overview&operation=List&parent=" + request.getValue("parent") + "&account=" + request.getAccount(), 0);
            }
            catch(java.lang.Exception exception)
            {
                printError("There was a problem deleting the server.", exception.toString(), "/SiteView/" + request.getAccountDirectory() + "/SiteView.html");
            }
        } else
        {
            printBodyHeader("Delete Confirmation");
            outputStream.println("<FONT SIZE=+1>Are you sure you want to remove the group <B>" + s2 + "</B> from the SiteView Server list?</FONT>" + "<p><FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST>" + "<input type=hidden name=page value=overview>" + "<input type=hidden name=operation value=\"" + s + "\">" + "<input type=hidden name=parent value=\"" + request.getValue("parent") + "\">" + "<input type=hidden name=server value=\"" + s1 + "\">" + "<input type=hidden name=account value=" + request.getAccount() + ">" + "<TABLE WIDTH=100% BORDER=0><TR>" + "<TD WIDTH=6%></TD><TD WIDTH=41%><input type=submit value=\"Delete\"></TD>" + "<TD WIDTH=6%></TD><TD ALIGN=RIGHT WIDTH=41%><A HREF=/SiteView/cgi/go.exe/SiteView?page=overview&operation=List&account=" + request.getAccount() + ">Return to Detail</A></TD><TD WIDTH=6%></TD>" + "</TR></TABLE></FORM>");
            printFooter(outputStream);
        }
    }

    public void printBody()
        throws java.lang.Exception
    {
        java.lang.String s = request.getValue("operation");
        if(s.length() == 0)
        {
            s = "Servers";
        }
        if(s.equals("Servers"))
        {
            printServers();
        } else
        if(s.equals("List"))
        {
            printListForm(s);
        } else
        if(s.equals("updateSettings"))
        {
            updateSettings(s);
        } else
        if(s.equals("Add"))
        {
            printAddForm(s);
        } else
        if(s.equals("DeleteGroup"))
        {
            printDeleteGroupForm(s);
        } else
        if(s.equals("AddGroup"))
        {
            printAddGroupForm(s);
        } else
        if(s.equals("Delete"))
        {
            printDeleteForm(s);
        } else
        if(s.equals("Edit"))
        {
            printAddForm(s);
        } else
        if(s.equals("open"))
        {
            printOpenCloseForm(s);
        } else
        if(s.equals("closed"))
        {
            printOpenCloseForm(s);
        } else
        if(s.equals("Replace Configuration File"))
        {
            printManageForm(s);
        } else
        if(s.equals("Replace Preference"))
        {
            printManageForm(s);
        } else
        {
            printError("The link was incorrect", "unknown operation", "/SiteView/" + request.getAccountDirectory() + "/SiteView.html");
        }
    }

    java.lang.String fontSize(long l)
    {
        if(l < 0L)
        {
            return "" + l;
        } else
        {
            return "+" + l;
        }
    }

    public void printServers()
    {
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        jgl.HashMap hashmap = getMasterConfig();
        int i = siteviewgroup.getSettingAsLong("_overviewRefreshRate", 60);
        java.lang.String s = fontSize(siteviewgroup.getSettingAsLong("_overviewServerFont", 0));
        java.lang.String s1 = fontSize(siteviewgroup.getSettingAsLong("_overviewGroupFont", -1));
        boolean flag = siteviewgroup.getSetting("_overviewHideTree").length() == 0;
        if(request.getValue("hideTree").length() != 0)
        {
            flag = false;
        }
        boolean flag1 = request.getValue("hideFrame").length() > 0;
        boolean flag2 = false;
        if(!request.actionAllowed("_multiEdit") && com.dragonflow.Page.overviewPage.getValue(hashmap, "_overviewHideUserLinks").length() != 0)
        {
            flag2 = true;
        }
        outputStream.println("<HEAD>\n<TITLE>" + com.dragonflow.SiteView.Platform.productName + " Overview</TITLE>\n" + siteviewgroup.refreshTag(i, "/SiteView/cgi/go.exe/SiteView?page=overview&category=" + request.getValue("category") + "&account=" + request.getAccount()) + com.dragonflow.SiteView.Platform.charSetTag + customCacheHeader + "<link rel=\"stylesheet\" type=\"text/css\" href=\"/SiteView/htdocs/artwork/siteviewUI.css\">\n" + "<link rel=\"stylesheet\" type=\"text/css\" href=\"/SiteView/htdocs/artwork/user.css\">\n" + "</HEAD>");
        java.lang.String s2 = "";
        if(com.dragonflow.Page.overviewPage.getValue(hashmap, "_overviewBGColor").length() > 5)
        {
            s2 = "BGCOLOR=" + com.dragonflow.Page.overviewPage.getValue(hashmap, "_overviewBGColor");
        }
        outputStream.println("<BODY " + s2 + " link=\"#6699cc\" alink=\"#6699cc\" vlink=\"#6699cc\">\n<FONT COLOR=\"#6699cc\">");
        com.dragonflow.SiteView.Server.startUpdating();
        java.lang.String s3 = com.dragonflow.SiteView.Monitor.NODATA_CATEGORY;
        jgl.Array array = new Array();
        jgl.Array array1 = com.dragonflow.SiteView.Server.getServers("", true);
        java.util.Enumeration enumeration = array1.elements();
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            jgl.HashMap hashmap1 = (jgl.HashMap)enumeration.nextElement();
            if(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "hidden").length() == 0)
            {
                java.lang.String s4;
                if(request.actionAllowed("_multiEdit"))
                {
                    s4 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "overviewHideAdminGroups");
                } else
                {
                    s4 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "overviewHideUserGroups");
                }
                if(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "usage").indexOf("monitorcount") < 0)
                {
                    if(com.dragonflow.Page.overviewPage.getValue(hashmap1, "class").length() > 0)
                    {
                        jgl.Array array2 = (jgl.Array)hashmap1.get("_items");
                        java.util.Enumeration enumeration1 = array2.elements();
                        while(enumeration1.hasMoreElements()) 
                        {
                            jgl.HashMap hashmap2 = (jgl.HashMap)enumeration1.nextElement();
                            s3 = printSiteView(array, flag, flag1, hashmap, hashmap2, request, s, s1, flag2, s4, s3);
                        }
                    } else
                    {
                        s3 = printSiteView(array, flag, flag1, hashmap, hashmap1, request, s, s1, flag2, s4, s3);
                    }
                }
            }
        } while(true);
        java.lang.String s5 = "overviewTitle" + s3.substring(0, 4) + ".gif";
        java.lang.String s6 = "";
        if(s3.length() != 0)
        {
            s6 = "<A href=/SiteView/cgi/go.exe/SiteView?page=overview&account=" + request.getAccount() + "><IMG border=0 src=/SiteView/htdocs/artwork/" + s5 + "></a>";
        }
        if(flag1)
        {
            s6 = "";
        }
        outputStream.println(com.dragonflow.Page.overviewPage.getValue(hashmap, "_overviewHTML"));
        outputStream.println("<table border=\"0\" align=\"center\" cellspacing=\"0\" cellpadding=\"2\"><tr bgcolor=\"#000000\"><td align=center>" + s6 + "</td>");
        if(!flag1)
        {
            if(request.actionAllowed("_multiEdit"))
            {
                outputStream.println("<td><a href=/SiteView/cgi/go.exe/SiteView?page=overview&operation=List&account=" + request.getAccount() + " TARGET=MAIN><IMG border=0 src=/SiteView/htdocs/artwork/overviewEdit.gif></a></td>");
            }
            java.lang.String s7 = "Multiview.htm";
            if(!flag2)
            {
                outputStream.println("<td><a href=/SiteView/docs/" + s7 + " TARGET=Help><IMG border=0 src=/SiteView/htdocs/artwork/overviewHelp.gif></a></td>");
            }
        }
        outputStream.println("</tr></table>\n");
        outputStream.println("<TABLE " + com.dragonflow.Page.overviewPage.getValue(hashmap, "_overviewTableOptions") + ">");
        java.lang.String s8 = "<td></td>";
        outputStream.println("<tr>");
        int j = java.lang.Integer.valueOf(com.dragonflow.Page.overviewPage.getValue(hashmap, "_overviewColumns")).intValue();
        if(j < 0)
        {
            j = -j;
        }
        if(j == 0)
        {
            j = 1;
        }
        for(int k = 1; k <= j; k++)
        {
            outputStream.println(s8);
        }

        outputStream.println("</tr>\n");
        java.util.Enumeration enumeration2 = array.elements();
label0:
        do
        {
            if(!enumeration2.hasMoreElements())
            {
                break;
            }
            java.lang.Object obj = enumeration2.nextElement();
            if(obj instanceof java.lang.String)
            {
                outputStream.println("<TR>" + obj + "</TR>");
                continue;
            }
            jgl.Array array3 = (jgl.Array)obj;
            int l = array3.size();
            int i1 = com.dragonflow.Utils.TextUtils.toInt(com.dragonflow.Page.overviewPage.getValue(hashmap, "_overviewColumns"));
            if(i1 < 0)
            {
                i1 = -i1;
                int j1 = ((l + i1) - 1) / i1;
                int l1 = 0;
                int j2 = 0;
                do
                {
                    do
                    {
                        if(l1 >= j1)
                        {
                            continue label0;
                        }
                        if(j2 == 0)
                        {
                            outputStream.print("\n<TR>");
                        }
                        int k2 = j2 * j1 + l1;
                        java.lang.String s13 = "";
                        if(k2 < l)
                        {
                            s13 = (java.lang.String)array3.at(k2);
                        }
                        outputStream.print(s13);
                    } while(++j2 < i1);
                    outputStream.print("</TR>");
                    l1++;
                    j2 = 0;
                } while(true);
            }
            if(i1 <= 0)
            {
                i1 = 1;
            }
            int k1 = 0;
            int i2 = 0;
            while(i2 < l) 
            {
                if(k1 == 0)
                {
                    outputStream.print("\n<TR>");
                }
                java.lang.String s12 = (java.lang.String)array3.at(i2);
                outputStream.print(s12);
                if(++k1 >= i1)
                {
                    outputStream.print("</TR>");
                    k1 = 0;
                }
                i2++;
            }
        } while(true);
        outputStream.println("\n</TABLE>");
        if(!flag1)
        {
            java.lang.String s9 = "multiLogo.gif";
            outputStream.println("<p><br><hr><br></p><table align=\"center\"><tr><td align=\"center\"><IMG border=0 src=/SiteView/htdocs/artwork/" + s9 + "></td></tr></table>");
        }
        com.dragonflow.SiteView.MonitorGroup.printCategoryInsertHTML(s3, siteviewgroup, outputStream);
        if(com.dragonflow.Page.overviewPage.getValue(hashmap, "_overviewHideLicense").length() <= 0)
        {
            java.lang.String s10 = com.dragonflow.Utils.LUtils.getLicenseKey();
            if(s10.length() == 0 && com.dragonflow.SiteView.Platform.isDemo())
            {
                s10 = com.dragonflow.Utils.LUtils.generateLicenseKey(25, 1, 99, 10);
            }
            java.lang.String s11 = com.dragonflow.Utils.LUtils.getLicenseSummary(s10, true, com.dragonflow.SiteView.Platform.productName, false);
            if(s11.length() > 0)
            {
                outputStream.println("<P align=\"center\" style=\"color:#888888\">(" + s11 + ")</p>");
            }
        }
        outputStream.println("</BODY>");
    }

    static long fetchSiteSeerState(jgl.HashMap hashmap, java.lang.StringBuffer stringbuffer)
    {
        jgl.HashMap hashmap1 = new HashMap();
        hashmap1.put("account", com.dragonflow.Utils.TextUtils.getValue(hashmap, "_siteseerAccount"));
        hashmap1.put("username", com.dragonflow.Utils.TextUtils.getValue(hashmap, "_siteseerUsername"));
        hashmap1.put("password", com.dragonflow.Utils.TextUtils.getValue(hashmap, "_siteseerPassword"));
        hashmap1.put("title", com.dragonflow.Utils.TextUtils.getValue(hashmap, "_siteseerTitle"));
        hashmap1.put("server", com.dragonflow.Utils.TextUtils.getValue(hashmap, "_siteseerHost"));
        hashmap1.put("proxy", com.dragonflow.Utils.TextUtils.getValue(hashmap, "_siteseerProxy"));
        hashmap1.put("proxyusername", com.dragonflow.Utils.TextUtils.getValue(hashmap, "_siteseerProxyUsername"));
        hashmap1.put("proxypassword", com.dragonflow.Utils.TextUtils.getValue(hashmap, "_siteseerProxyPassword"));
        return com.dragonflow.SiteView.Server.fetchServerState(hashmap, hashmap1, stringbuffer);
    }

    public static java.lang.String fetchSiteSeerCategory(jgl.HashMap hashmap)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.lang.String s = "nodata";
        long l = com.dragonflow.Page.overviewPage.fetchSiteSeerState(hashmap, stringbuffer);
        if(l == 200L)
        {
            java.lang.String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_siteseerAccount");
            java.lang.String s2 = stringbuffer.toString();
            int i = s2.indexOf("<!--CURRENTSTATE\n");
            int j = s2.indexOf("ENDCURRENTSTATE-->\n");
            if(i >= 0 && j >= 0)
            {
                s2 = s2.substring(i + "<!--CURRENTSTATE\n".length(), j);
                java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s2, "\n");
                for(int k = 0; k < as.length; k++)
                {
                    jgl.Array array = com.dragonflow.SiteView.Platform.split('\t', as[k]);
                    if(array.size() <= 3)
                    {
                        continue;
                    }
                    java.lang.String s3 = (java.lang.String)array.at(1);
                    if(!s3.equals(s1))
                    {
                        continue;
                    }
                    s = (java.lang.String)array.at(3);
                    break;
                }

            }
        }
        return s;
    }

    java.lang.String printSiteView(jgl.Array array, boolean flag, boolean flag1, jgl.HashMap hashmap, jgl.HashMap hashmap1, com.dragonflow.HTTP.HTTPRequest httprequest, java.lang.String s, 
            java.lang.String s1, boolean flag2, java.lang.String s2, java.lang.String s3)
    {
        java.lang.String s4 = com.dragonflow.Page.overviewPage.getValue(hashmap1, "server");
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.lang.StringBuffer stringbuffer1 = new StringBuffer();
        long l1 = 200L;
        java.lang.String s5 = com.dragonflow.Page.overviewPage.getValue(hashmap1, "title");
        boolean flag3 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_siteseerAccount").length() > 0 && com.dragonflow.Utils.TextUtils.getValue(hashmap, "_siteseerDisabled").length() == 0 && s4.equals("_local");
        long l;
        java.lang.String s6;
        if(s4.equals("_local"))
        {
            s6 = "/SiteView/" + httprequest.getAccountDirectory();
            l = 200L;
            try
            {
                com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                if(siteviewgroup.internalServerActive())
                {
                    java.io.ByteArrayOutputStream bytearrayoutputstream = new ByteArrayOutputStream();
                    java.io.PrintWriter printwriter = com.dragonflow.Utils.FileUtils.MakeUTF8OutputWriter(bytearrayoutputstream);
                    siteviewgroup.printSpecial("Progress.html", printwriter, httprequest);
                    printwriter.flush();
                    stringbuffer = new StringBuffer(bytearrayoutputstream.toString("UTF-8"));
                } else
                {
                    stringbuffer = com.dragonflow.Utils.FileUtils.readCharFile(com.dragonflow.SiteView.Platform.getRoot() + "/htdocs/Progress.html");
                }
                if(flag3)
                {
                    l1 = com.dragonflow.Page.overviewPage.fetchSiteSeerState(hashmap, stringbuffer1);
                }
            }
            catch(java.lang.Exception exception)
            {
                com.dragonflow.Log.LogManager.log("Error", "Overview page error: " + exception + ", details: " + com.dragonflow.Utils.FileUtils.stackTraceText(exception));
            }
        } else
        {
            l = com.dragonflow.Utils.TextUtils.toLong(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_status"));
            stringbuffer.append(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_contents"));
            java.lang.String s8 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "securehttp");
            if(s8.length() > 0)
            {
                s6 = "https://" + s4 + "/SiteView/" + httprequest.getAccountDirectory();
            } else
            {
                s6 = "http://" + s4 + "/SiteView/" + httprequest.getAccountDirectory();
            }
        }
        java.lang.String s9 = "<b><FONT SIZE=" + s + ">" + s5 + "</FONT></b>";
        if(!flag2)
        {
            s9 = "<span class=titletext><A href=" + s6 + "/SiteView.html TARGET=MAIN>" + s9 + "</A></span>";
        }
        array.add("<td COLSPAN=4>" + s9 + "</td>");
        if(l == 200L)
        {
            java.lang.String s10 = stringbuffer.toString();
            int i = s10.indexOf("<!--CURRENTSTATE\n");
            int k = s10.indexOf("ENDCURRENTSTATE-->\n");
            if(i >= 0 && k >= 0)
            {
                s3 = processCurrentState(array, "", "", flag, s4, s6, httprequest, s10.substring(i + "<!--CURRENTSTATE\n".length(), k), s1, flag2, s2, s3);
                if(flag3)
                {
                    java.lang.String s11 = stringbuffer1.toString();
                    int j = s11.indexOf("<!--CURRENTSTATE\n");
                    int i1 = s11.indexOf("ENDCURRENTSTATE-->\n");
                    if(l1 != 200L)
                    {
                        array.add("<td colspan=2><img width=10 height=20 src=/SiteView/htdocs/artwork/empty1020.gif><FONT SIZE=" + s1 + " COLOR=#6699cc><B>SiteSeer not available - " + com.dragonflow.StandardMonitor.URLMonitor.lookupStatus(l1) + "</B></FONT></TD>");
                    } else
                    if(j >= 0 && i1 >= 0)
                    {
                        java.lang.String s7 = "http://" + com.dragonflow.Page.overviewPage.getValue(hashmap, "_siteseerHost") + "/SiteView/accounts/" + com.dragonflow.Page.overviewPage.getValue(hashmap, "_siteseerAccount") + "/htdocs";
                        java.lang.String s13 = com.dragonflow.Page.overviewPage.getValue(hashmap, "_siteseerAccount");
                        java.lang.String s14 = com.dragonflow.Page.overviewPage.getValue(hashmap, "_siteseerTitle");
                        s3 = processCurrentState(array, s13, s14, flag, s4, s7, httprequest, s11.substring(j + "<!--CURRENTSTATE\n".length(), i1), s1, flag2, s2, s3);
                    } else
                    {
                        com.dragonflow.Log.LogManager.log("RunMonitor", "unknown multi-view page error, " + com.dragonflow.Utils.TextUtils.getValue(hashmap, "_siteseerAccount") + ", " + stringbuffer1);
                        array.add("<td colspan=2><img width=10 height=20 src=/SiteView/htdocs/artwork/empty1020.gif><FONT SIZE=" + s1 + " COLOR=#6699cc><B>SiteSeer not available - missing account status</B></FONT></TD>");
                    }
                }
            } else
            {
                array.add("<td colspan=2><img width=10 height=20 src=/SiteView/htdocs/artwork/empty1020.gif><FONT SIZE=" + s1 + " COLOR=#6699cc><B>summary not available</B></FONT></TD>");
            }
        } else
        {
            java.lang.String s12 = "";
            if(l == -1L)
            {
                s12 = "checking...";
            } else
            if(l == 4040L)
            {
                s12 = "SiteView not found";
            } else
            {
                s12 = com.dragonflow.StandardMonitor.URLMonitor.lookupStatus(l);
            }
            array.add("<td colspan=2><img width=10 height=20 src=/SiteView/htdocs/artwork/empty1020.gif><FONT SIZE=" + s1 + " COLOR=#6699cc><B>" + s12 + "</B></FONT></TD>");
        }
        return s3;
    }

    java.lang.String altText(jgl.Array array)
    {
        return com.dragonflow.Utils.TextUtils.escapeHTML(array.at(2) + ", " + array.at(3) + ", " + array.at(4));
    }

    int groupLevel(jgl.Array array)
    {
        int i = 0;
        if(array != null && array.size() > 0)
        {
            jgl.Array array1 = (jgl.Array)array.at(0);
            if(array1.size() >= 6)
            {
                i = com.dragonflow.Utils.TextUtils.toInt((java.lang.String)array1.at(5));
            }
        }
        return i;
    }

    java.lang.String processCurrentState(jgl.Array array, java.lang.String s, java.lang.String s1, boolean flag, java.lang.String s2, java.lang.String s3, com.dragonflow.HTTP.HTTPRequest httprequest, 
            java.lang.String s4, java.lang.String s5, boolean flag1, java.lang.String s6, java.lang.String s7)
    {
        java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s4, "\n");
        jgl.Array array1 = new Array();
        jgl.Array array2 = new Array();
        jgl.HashMap hashmap = new HashMap();
        jgl.Array array3 = com.dragonflow.SiteView.Server.readServers();
        jgl.HashMap hashmap1 = com.dragonflow.SiteView.Server.findServer(array3, s2);
        java.lang.String s8 = httprequest.getValue("default");
        if(s8.length() == 0)
        {
            s8 = "show";
        }
        java.lang.String s9 = httprequest.getValue("category");
        java.lang.String s10 = "";
        for(int i = 0; i < as.length; i++)
        {
            jgl.Array array4 = com.dragonflow.SiteView.Platform.split('\t', as[i]);
            if(array4.size() < 3)
            {
                continue;
            }
            if(array4.size() != 5)
            {
                array2 = new Array();
                array1.add(array2);
                s10 = (java.lang.String)array4.at(1);
                if(hashmap1.get(s10) != null)
                {
                    hashmap.add(s10, hashmap1.get(s10));
                } else
                {
                    hashmap.add(s10, "open");
                }
            }
            if(s6.indexOf(s10) == -1)
            {
                array2.add(array4);
            }
            monitorCount++;
        }

        int j = 0;
        int k = -1;
        int l = -1;
        int i1 = 0;
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        jgl.Array array5 = new Array();
label0:
        for(int j1 = 0; j1 < array1.size(); j1++)
        {
            jgl.Array array6 = (jgl.Array)array1.at(j1);
            jgl.Array array7 = null;
            if(j1 + 1 < array1.size())
            {
                array7 = (jgl.Array)array1.at(j1 + 1);
            }
            java.util.Enumeration enumeration = array6.elements();
            do
            {
                if(!enumeration.hasMoreElements())
                {
                    continue label0;
                }
                jgl.Array array8 = (jgl.Array)enumeration.nextElement();
                if(array8.size() == 5)
                {
                    if(l == -1 || l > i1)
                    {
                        stringbuffer.append("<IMG SRC=" + com.dragonflow.SiteView.MonitorGroup.getTinyCategoryArt((java.lang.String)array8.at(3)) + " ALT=\"" + altText(array8) + "\">");
                        if(++j % 10 == 0)
                        {
                            stringbuffer.append("<BR>");
                        }
                    }
                } else
                {
                    if(stringbuffer.length() > 0)
                    {
                        array5.add(stringbuffer + "</td>");
                    }
                    stringbuffer = new StringBuffer();
                    int k1 = 0;
                    if(array8.size() >= 6)
                    {
                        k1 = com.dragonflow.Utils.TextUtils.toInt((java.lang.String)array8.at(5));
                    }
                    i1 = k1;
                    if(k == -1 || k >= k1)
                    {
                        boolean flag2 = groupLevel(array7) > k1;
                        k = -1;
                        l = -1;
                        java.lang.String s11 = (java.lang.String)array8.at(1);
                        java.lang.String s12 = (java.lang.String)hashmap.get(s11);
                        java.lang.String s13 = (java.lang.String)array8.at(3);
                        if(s9.length() > 0 && s9.indexOf(s13) == -1)
                        {
                            s12 = "hidden";
                        }
                        if(s12.equals("hidden"))
                        {
                            k = k1;
                            l = k1;
                        } else
                        {
                            boolean flag3 = true;
                            if(s12.equals("closed"))
                            {
                                flag3 = false;
                                l = k1 + 1;
                                k = k1;
                            }
                            j = 0;
                            java.lang.String s14 = s3 + "/Detail" + com.dragonflow.HTTP.HTTPRequest.encodeString(s11) + ".html";
                            java.lang.String s15 = "" + array8.at(2);
                            if(k1 == 0 && s.length() > 0)
                            {
                                s14 = s3 + "/SiteView.html?account=" + s;
                                s15 = s1;
                            }
                            java.lang.String s16 = "";
                            for(; k1 > 0; k1--)
                            {
                                s16 = s16 + "&nbsp;&nbsp;";
                            }

                            java.lang.String s17 = "<B>" + s15 + "</B></FONT>";
                            if(!flag1)
                            {
                                s17 = "<A HREF=" + s14 + " TARGET=MAIN>" + s17 + "</A>";
                                if(s14.indexOf("/Detail") >= 0)
                                {
                                    s17 = "<span class=groupname>" + s17 + "</span>";
                                }
                                if(flag2 && flag)
                                {
                                    if(flag3)
                                    {
                                        s17 = "<A HREF=/SiteView/cgi/go.exe/SiteView?page=overview&operation=closed&account=" + httprequest.getAccount() + "&server=" + s2 + "&group=" + s11 + "><img src=/SiteView/htdocs/artwork/close.gif border=0></a> " + s17;
                                    } else
                                    {
                                        s17 = "<A HREF=/SiteView/cgi/go.exe/SiteView?page=overview&operation=open&account=" + httprequest.getAccount() + "&server=" + s2 + "&group=" + s11 + "><img src=/SiteView/htdocs/artwork/open.gif border=0></a> " + s17;
                                    }
                                }
                            }
                            s17 = "<FONT SIZE=" + s5 + ">" + s17 + "</FONT>";
                            s7 = com.dragonflow.SiteView.Monitor.getWorstCategory(s7, s13);
                            stringbuffer.append("<TD WIDTH=14>&nbsp;<IMG SRC=" + com.dragonflow.SiteView.MonitorGroup.getSmallCategoryArt((java.lang.String)array8.at(3)) + ">" + "</TD><TD>&nbsp;" + s16 + s17 + "</TD>" + "<TD><IMG WIDTH=3 HEIGHT=5 " + "SRC=/SiteView/htdocs/artwork/empty35.gif>" + "</TD><TD>");
                        }
                    }
                }
            } while(true);
        }

        if(stringbuffer.length() > 0)
        {
            array5.add(stringbuffer.toString());
        }
        array.add(array5);
        return s7;
    }

    java.lang.String getPreferenceOptionsHTML()
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        java.util.Enumeration enumeration = hashmap.keys();
        jgl.Array array = new Array();
        for(; enumeration.hasMoreElements(); array.add(enumeration.nextElement())) { }
        jgl.Sorting.sort(array, new LessEqualPropertyName());
        java.lang.String s;
        java.lang.String s1;
        for(java.util.Enumeration enumeration1 = array.elements(); enumeration1.hasMoreElements(); stringbuffer.append("<option value=\"" + s + "\">" + s + "=" + s1 + ""))
        {
            s = (java.lang.String)enumeration1.nextElement();
            s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, s);
            if(s.length() + s1.length() > 50)
            {
                s1 = "...";
            }
        }

        return stringbuffer.toString();
    }

    void addFiles(java.lang.String s, java.lang.StringBuffer stringbuffer, java.lang.String s1)
    {
        java.io.File file = new File(com.dragonflow.SiteView.Platform.getRoot() + s);
        java.lang.String as[] = file.list();
        if(as != null)
        {
            for(int i = 0; i < as.length; i++)
            {
                java.lang.String s2 = as[i];
                if(s1.length() <= 0 || s2.endsWith(s1))
                {
                    stringbuffer.append("<option value=\"" + s + s2 + "\">" + s + s2);
                }
            }

        }
    }

    java.lang.String getConfigurationFileOptionsHTML()
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        addFiles("/groups/", stringbuffer, ".mg");
        addFiles("/templates.eventlog/", stringbuffer, "");
        addFiles("/templates.history/", stringbuffer, "");
        addFiles("/templates.mail/", stringbuffer, "");
        addFiles("/templates.os/", stringbuffer, "");
        addFiles("/templates.page/", stringbuffer, "");
        addFiles("/templates.perfmon/", stringbuffer, "");
        addFiles("/templates.post/", stringbuffer, "");
        addFiles("/templates.script/", stringbuffer, "");
        addFiles("/templates.snmp/", stringbuffer, "");
        addFiles("/templates.sound/", stringbuffer, "");
        return stringbuffer.toString();
    }

    void printManageForm(java.lang.String s)
        throws java.lang.Exception
    {
        java.lang.String s1 = com.dragonflow.Utils.LUtils.getLicenseKey();
        if(com.dragonflow.Utils.LUtils.isSubscriptionLicense(s1))
        {
            outputStream.println("The " + s + " command is a feature that requires a CentraScope license.");
            return;
        }
        if(request.getValue("command").length() > 0)
        {
            if(debug)
            {
                com.dragonflow.Utils.TextUtils.debugPrint("IS POST TO MANAGE PAGE");
            }
            printProgressMessage("<P><FONT SIZE=+1><B>Saving Changes</B></FONT><P>");
            try
            {
                jgl.Array array = new Array();
                java.lang.String s4;
                for(java.util.Enumeration enumeration = request.getValues("item"); enumeration.hasMoreElements(); com.dragonflow.SiteView.Server.addServers(s4, array))
                {
                    s4 = (java.lang.String)enumeration.nextElement();
                }

                if(s.equals("Replace Preference"))
                {
                    java.util.Enumeration enumeration1 = array.elements();
                    java.lang.String s5 = request.getValue("preferenceName");
                    java.lang.String s7 = request.getValue("preferenceValue");
                    java.lang.String s9 = "Replacing preferences, " + s5 + "=" + s7;
                    com.dragonflow.Log.LogManager.log("RunMonitor", s9);
                    printProgressMessage(s9 + "<BR>");
                    int i = 0;
                    int j = 0;
                    while(enumeration1.hasMoreElements()) 
                    {
                        i++;
                        jgl.HashMap hashmap1 = (jgl.HashMap)enumeration1.nextElement();
                        s9 = "Replacing preference on " + com.dragonflow.Page.overviewPage.getValue(hashmap1, "title");
                        com.dragonflow.Log.LogManager.log("RunMonitor", s9);
                        printProgressMessage(s9 + "<BR>");
                        java.lang.StringBuffer stringbuffer1 = new StringBuffer();
                        java.lang.StringBuffer stringbuffer2 = new StringBuffer();
                        long l1 = com.dragonflow.SiteView.Server.remoteOp(hashmap1, "get", "/groups/master.config", stringbuffer1, stringbuffer2);
                        if(l1 != 200L)
                        {
                            s9 = "Error reading preferences, " + com.dragonflow.Page.overviewPage.getValue(hashmap1, "title") + ", " + com.dragonflow.StandardMonitor.URLMonitor.lookupStatus(l1);
                            printProgressMessage("<b>" + s9 + "</b><BR>");
                            com.dragonflow.Log.LogManager.log("Error", s9);
                        } else
                        {
                            java.io.StringBufferInputStream stringbufferinputstream = new StringBufferInputStream(stringbuffer2.toString());
                            java.io.BufferedReader bufferedreader = com.dragonflow.Utils.FileUtils.MakeInputReader(stringbufferinputstream);
                            jgl.Array array3 = com.dragonflow.Properties.FrameFile.readFrames(bufferedreader);
                            bufferedreader.close();
                            stringbufferinputstream.close();
                            if(array3.size() != 1)
                            {
                                s9 = "Error reading preferences, " + com.dragonflow.Page.overviewPage.getValue(hashmap1, "title") + ", expected 1 record, found " + array3.size();
                                printProgressMessage("<b>" + s9 + "</b><BR>");
                                com.dragonflow.Log.LogManager.log("Error", s9);
                            } else
                            {
                                jgl.HashMap hashmap6 = (jgl.HashMap)array3.at(0);
                                if(hashmap6.size() < 130)
                                {
                                    s9 = "Error reading preferences, " + com.dragonflow.Page.overviewPage.getValue(hashmap1, "title") + ", missing data, " + hashmap6.size() + " settings";
                                    printProgressMessage("<b>" + s9 + "</b><BR>");
                                    com.dragonflow.Log.LogManager.log("Error", s9);
                                } else
                                {
                                    hashmap6.remove(s5);
                                    hashmap6.put(s5, s7);
                                    java.io.ByteArrayOutputStream bytearrayoutputstream = new ByteArrayOutputStream();
                                    java.io.PrintWriter printwriter = com.dragonflow.Utils.FileUtils.MakeOutputWriter(bytearrayoutputstream);
                                    com.dragonflow.Properties.FrameFile.printFrames(printwriter, array3, null, false, true);
                                    printwriter.flush();
                                    bytearrayoutputstream.flush();
                                    java.lang.StringBuffer stringbuffer4 = new StringBuffer();
                                    stringbuffer4.append(bytearrayoutputstream.toString());
                                    printwriter.close();
                                    bytearrayoutputstream.close();
                                    java.lang.StringBuffer stringbuffer5 = new StringBuffer();
                                    long l2 = com.dragonflow.SiteView.Server.remoteOp(hashmap1, "put", "/groups/master.config", stringbuffer4, stringbuffer5);
                                    if(l2 != 200L)
                                    {
                                        s9 = "Error writing preferences, " + com.dragonflow.Page.overviewPage.getValue(hashmap1, "title") + ", " + com.dragonflow.StandardMonitor.URLMonitor.lookupStatus(l2);
                                        printProgressMessage("<b>" + s9 + "</b><BR>");
                                        com.dragonflow.Log.LogManager.log("Error", s9);
                                    } else
                                    {
                                        java.lang.String s20 = stringbuffer5.toString();
                                        int k1 = s20.indexOf("error:");
                                        if(k1 != -1)
                                        {
                                            s9 = "Error writing preferences, " + com.dragonflow.Page.overviewPage.getValue(hashmap1, "title") + ", " + s20.substring(k1);
                                            printProgressMessage("<b>" + s9 + "</b><BR>");
                                            com.dragonflow.Log.LogManager.log("Error", s9);
                                        } else
                                        {
                                            j++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    s9 = "Replacing Preferences complete, " + i + " total, " + (i - j) + " errors";
                    printProgressMessage("<BR>" + s9 + "<BR>");
                    com.dragonflow.Log.LogManager.log("RunMonitor", s9);
                    if(i != j)
                    {
                        com.dragonflow.Log.LogManager.log("Error", s9);
                    }
                } else
                if(s.equals("Replace Configuration File"))
                {
                    java.util.Enumeration enumeration2 = array.elements();
                    java.lang.String s6 = request.getValue("filename");
                    java.lang.String s8 = request.getValue("filename");
                    java.lang.String s10 = "Replacing configuration file, " + s6;
                    com.dragonflow.Log.LogManager.log("RunMonitor", s10);
                    printProgressMessage(s10 + "<BR>");
                    java.lang.StringBuffer stringbuffer = new StringBuffer();
                    s10 = "";
                    try
                    {
                        stringbuffer = com.dragonflow.Utils.FileUtils.readFile(com.dragonflow.SiteView.Platform.getRoot() + s6);
                    }
                    catch(java.lang.Exception exception2)
                    {
                        s10 = exception2.toString();
                    }
                    if(s10.length() != 0)
                    {
                        s10 = "Error reading configuration file, " + s6 + ", " + s10;
                        printProgressMessage("<b>" + s10 + "</b><BR>");
                        com.dragonflow.Log.LogManager.log("Error", s10);
                    } else
                    {
                        int k = 0;
                        int i1 = 0;
                        while(enumeration2.hasMoreElements()) 
                        {
                            k++;
                            jgl.HashMap hashmap4 = (jgl.HashMap)enumeration2.nextElement();
                            java.lang.String s11 = "Replacing configuration file on " + com.dragonflow.Page.overviewPage.getValue(hashmap4, "title");
                            com.dragonflow.Log.LogManager.log("RunMonitor", s11);
                            printProgressMessage(s11 + "<BR>");
                            java.lang.StringBuffer stringbuffer3 = new StringBuffer();
                            long l3 = com.dragonflow.SiteView.Server.remoteOp(hashmap4, "put", s8, stringbuffer, stringbuffer3);
                            if(l3 != 200L)
                            {
                                java.lang.String s12 = "Error writing configuration file, " + com.dragonflow.Page.overviewPage.getValue(hashmap4, "title") + ", " + s8 + ", " + com.dragonflow.StandardMonitor.URLMonitor.lookupStatus(l3);
                                printProgressMessage("<b>" + s12 + "</b><BR>");
                                com.dragonflow.Log.LogManager.log("Error", s12);
                            } else
                            {
                                java.lang.String s19 = stringbuffer3.toString();
                                int j1 = s19.indexOf("error:");
                                if(j1 != -1)
                                {
                                    java.lang.String s13 = "Error writing configuration file, " + com.dragonflow.Page.overviewPage.getValue(hashmap4, "title") + ", " + s8 + ", " + s19.substring(j1);
                                    printProgressMessage("<b>" + s13 + "</b><BR>");
                                    com.dragonflow.Log.LogManager.log("Error", s13);
                                } else
                                {
                                    i1++;
                                }
                            }
                        }
                        java.lang.String s14 = "Replacing Configuration File complete, " + k + " total, " + (k - i1) + " errors";
                        printProgressMessage("<BR>" + s14 + "<BR>");
                        com.dragonflow.Log.LogManager.log("RunMonitor", s14);
                        if(k != i1)
                        {
                            com.dragonflow.Log.LogManager.log("Error", s14);
                        }
                    }
                } else
                {
                    throw new Exception("unknown operation: " + s);
                }
                printProgressMessage("<P><B>Done</B><P>");
                outputStream.println("<A HREF=" + getReturnURL() + ">" + getReturnLabel() + "</A><P>");
                outputStream.println("</BODY></HTML>");
            }
            catch(java.lang.Exception exception)
            {
                java.lang.System.out.println("Problem with " + s + ": " + exception);
                exception.printStackTrace();
                printError("There was a problem with the " + s + ".", exception.toString(), "/SiteView/" + request.getAccountDirectory() + "/SiteView.html");
            }
        } else
        {
            java.lang.String s2 = com.dragonflow.SiteView.Platform.getDirectoryPath("groups", request.getAccount());
            java.lang.String s3 = s2 + java.io.File.separator + "trees.dyn";
            printBodyHeader(s);
            com.dragonflow.Page.CGI.menus menus1 = getNavItems(request);
            printButtonBar("ManageServer.htm", "", menus1);
            outputStream.print("<FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST><INPUT TYPE=HIDDEN NAME=operation VALUE=\"" + s + "\">" + "<INPUT TYPE=HIDDEN NAME=page VALUE=overview>" + "<INPUT TYPE=HIDDEN NAME=save VALUE=true>" + "<INPUT TYPE=HIDDEN NAME=account VALUE=" + request.getAccount() + ">" + "<INPUT TYPE=HIDDEN NAME=returnURL VALUE=" + request.getValue("returnURL") + ">" + "<INPUT TYPE=HIDDEN NAME=returnLabel VALUE=\"" + request.getValue("returnLabel") + "\">");
            if(s.equals("Replace Configuration File"))
            {
                outputStream.println("<H2>" + s + "</H2><p>" + "<b>Beta: This is a beta feature and is still being tested.</b>" + "Replace a configuration file on one or more servers." + "<p><br>" + "Choose the configuration file that will be transferred to each of the servers." + "<blockquote><P>Configuration File: <select name=filename size=1>" + getConfigurationFileOptionsHTML() + "</select>" + "</BLOCKQUOTE>");
            } else
            if(s.equals("Replace Preference"))
            {
                outputStream.println("<H2>" + s + "</H2><p>" + "Replace a preference on one or more servers." + "<P><br>" + "Choose the preference you wish to change and enter the new value for the preference." + "<BLOCKQUOTE><p>" + "Preference: <select name=preferenceName size=1>" + getPreferenceOptionsHTML() + "</select>" + "<p>" + "New Value: <input type=text size=50 name=preferenceValue>" + "</BLOCKQUOTE>");
            } else
            {
                throw new Exception("unknown operation: " + s);
            }
            jgl.Array array1 = null;
            try
            {
                array1 = com.dragonflow.Properties.FrameFile.readFromFile(s3);
            }
            catch(java.lang.Exception exception1)
            {
                array1 = new Array();
            }
            jgl.HashMap hashmap = null;
            java.lang.String s15 = request.getAccount();
            boolean flag = false;
            for(int l = 0; l < array1.size(); l++)
            {
                jgl.HashMap hashmap2 = (jgl.HashMap)array1.at(l);
                if(com.dragonflow.Utils.TextUtils.getValue(hashmap2, "_user").equals(s15))
                {
                    hashmap = hashmap2;
                }
            }

            if(hashmap == null)
            {
                hashmap = new HashMap();
                array1.add(hashmap);
                hashmap.put("_user", s15);
            }
            java.util.Enumeration enumeration3 = request.getVariables();
            do
            {
                if(!enumeration3.hasMoreElements())
                {
                    break;
                }
                java.lang.String s16 = (java.lang.String)enumeration3.nextElement();
                if(s16.startsWith(OPEN_VARIABLE))
                {
                    java.lang.String s17 = s16.substring(OPEN_VARIABLE.length(), s16.length() - 2);
                    if(!com.dragonflow.Utils.TextUtils.getValue(hashmap, s17).equals("open"))
                    {
                        hashmap.put(s17, "open");
                        flag = true;
                    }
                }
                if(s16.startsWith(CLOSE_VARIABLE))
                {
                    java.lang.String s18 = s16.substring(CLOSE_VARIABLE.length(), s16.length() - 2);
                    if(!com.dragonflow.Utils.TextUtils.getValue(hashmap, s18).equals("close"))
                    {
                        hashmap.remove(s18);
                        flag = true;
                    }
                }
            } while(true);
            jgl.HashMap hashmap3 = new HashMap();
            for(java.util.Enumeration enumeration4 = request.getValues("item"); enumeration4.hasMoreElements(); hashmap3.put(enumeration4.nextElement(), "checked")) { }
            outputStream.println("<p>Select one or more servers:<blockquote>(Click the <img src=/SiteView/htdocs/artwork/Plus.gif alt=\"open\"> to expand an item, and the <img src=/SiteView/htdocs/artwork/Minus.gif alt=\"close\"> to collapse an item).<P><TABLE BORDER=0>");
            jgl.Array array2 = com.dragonflow.SiteView.Server.getServers("", false);
            jgl.HashMap hashmap5;
            for(java.util.Enumeration enumeration5 = array2.elements(); enumeration5.hasMoreElements(); printItem(hashmap5, hashmap, hashmap3, 0))
            {
                hashmap5 = (jgl.HashMap)enumeration5.nextElement();
            }

            outputStream.println("</TABLE></blockquote>");
            outputStream.println("<P><input type=submit NAME=command VALUE=\"" + s + "\"></FORM>");
            outputStream.println("</FORM>");
            printFooter(outputStream);
            if(flag)
            {
                if(debug)
                {
                    com.dragonflow.Utils.TextUtils.debugPrint("SAVING TREE STATE");
                }
                com.dragonflow.Properties.FrameFile.writeToFile(s3, array1);
            }
        }
    }

    java.lang.String getReturnURL()
    {
        java.lang.String s = request.getValue("returnURL");
        if(s.length() == 0)
        {
            s = "/SiteView/cgi/go.exe/SiteView?page=overview&operation=List";
        } else
        if(s.startsWith("Detail") || s.equals("SiteView"))
        {
            s = com.dragonflow.SiteView.Platform.getURLPath("htdocs", request.getAccount()) + "/" + s + ".html";
        }
        return s;
    }

    java.lang.String getReturnLabel()
    {
        java.lang.String s = request.getValue("returnLabel");
        if(s.length() == 0)
        {
            s = "Return to Servers";
        } else
        {
            s = "Return to " + s;
        }
        return s;
    }

    void printMultiButton(java.lang.String s, java.lang.String s1, java.lang.String s2)
    {
        outputStream.println("<P><DT><TABLE WIDTH=500 BORDER=0><TR><TD><input type=submit name=operation value=\"" + s + "\"> on Selected Servers" + "<TD ALIGN=RIGHT><A HREF=/SiteView/docs/" + s1 + " TARGET=Help>Help</A></TR></TABLE>" + "<DD>" + s2);
    }

    java.lang.String getIndentHTML(int i)
    {
        int j = i * 11;
        if(j == 0)
        {
            j = 1;
        }
        return "<img src=/SiteView/htdocs/artwork/empty1111.gif height=11 width=" + j + " border=0>";
    }

    private void printItem(jgl.HashMap hashmap, jgl.HashMap hashmap1, jgl.HashMap hashmap2, int i)
    {
        java.lang.String s = com.dragonflow.SiteView.Server.getPath(hashmap);
        java.lang.String s1 = com.dragonflow.SiteView.Server.getTitle(hashmap);
        jgl.Array array = com.dragonflow.SiteView.Server.loadItems(hashmap);
        boolean flag = hashmap1.get(s) != null;
        java.lang.String s2 = getIndentHTML(i);
        outputStream.print("<TR><TD>");
        outputStream.print(s2);
        if(array.size() > 0)
        {
            if(flag)
            {
                outputStream.print("<input type=image name=\"close" + s + "\" src=/SiteView/htdocs/artwork/Minus.gif alt=\"close\" border=0>");
            } else
            {
                outputStream.print("<input type=image name=\"open" + s + "\" src=/SiteView/htdocs/artwork/Plus.gif alt=\"open\" border=0>");
            }
        } else
        {
            outputStream.print("<img src=/SiteView/htdocs/artwork/empty1111.gif>");
        }
        outputStream.print("<input type=checkbox name=item value=\"" + s + "\" " + com.dragonflow.Utils.TextUtils.getValue(hashmap2, s) + "><B>");
        outputStream.print(s1 + "</B></TD></TR>");
        s2 = getIndentHTML(i + 3);
        if(flag)
        {
            jgl.HashMap hashmap3;
            for(java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); printItem(hashmap3, hashmap1, hashmap2, i + 2))
            {
                hashmap3 = (jgl.HashMap)enumeration.nextElement();
            }

        }
    }

    public static void main(java.lang.String args[])
    {
        (new overviewPage()).handleRequest();
    }

    static 
    {
        EXCLUDE_MAP = null;
        EXCLUDE_MAP = new HashMap();
        EXCLUDE_MAP.put("_parent", "exclude");
        EXCLUDE_MAP.put("_group", "exclude");
        EXCLUDE_MAP.put("_class", "exclude");
        EXCLUDE_MAP.put("_id", "exclude");
        EXCLUDE_MAP.put("_frequency", "exclude");
        EXCLUDE_MAP.put("_nextID", "exclude");
        EXCLUDE_MAP.put("_nextConditionID", "exclude");
        EXCLUDE_MAP.put("_timeout", "exclude");
    }
}
