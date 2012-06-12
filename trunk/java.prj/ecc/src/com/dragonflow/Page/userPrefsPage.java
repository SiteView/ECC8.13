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

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequestException;
import com.dragonflow.Properties.HashMapOrdered;

// Referenced classes of package com.dragonflow.Page:
// prefsPage, treeControl, portalChooserPage, CGI

public class userPrefsPage extends com.dragonflow.Page.prefsPage
{

    static final java.lang.String GROUPS = "_group";

    public userPrefsPage()
    {
    }

    java.lang.String getHelpPage()
    {
        return "UserPref.htm";
    }

    void printOption(boolean flag, jgl.HashMap hashmap, java.lang.String s, java.lang.String s1, java.lang.String s2)
    {
        java.lang.String s3 = "";
        if(flag || com.dragonflow.Page.userPrefsPage.getValue(hashmap, s1).length() > 0)
        {
            s3 = "CHECKED";
        }
        if(s2.length() < 1)
        {
            outputStream.println("<TR><TD align=\"left\" colspan=\"3\">" + s + "</TD></TR>");
        } else
        {
            outputStream.println("<TR><TD ALIGN=RIGHT>" + s + "</TD>" + "<TD ALIGN=LEFT><input type=checkbox name=" + s1 + " value=true " + s3 + "></TD>" + "<TD><FONT SIZE=-1>" + s2 + "</FONT></TD>" + "<TD><I></I></TD></TR>");
        }
    }

    java.lang.String getGroupsHTML(jgl.HashMap hashmap)
        throws java.lang.Exception
    {
        jgl.Array array = new Array();
        for(java.util.Enumeration enumeration = hashmap.values("_group"); enumeration.hasMoreElements(); array.add(enumeration.nextElement())) { }
        java.lang.String s = "<option value=\"\">all groups";
        if(array.size() == 0)
        {
            s = "<option selected value=\"\">all groups";
        }
        return "<select multiple name=_group size=4> " + s + getMonitorOptionsHTML(array, null, null, 2) + "</select>";
    }

    java.lang.String getGroupsHTML(java.lang.String s, java.lang.String s1, java.lang.String s2, jgl.HashMap hashmap)
        throws java.lang.Exception
    {
        jgl.Array array = new Array();
        java.util.Enumeration enumeration = hashmap.values("_group");
        if(!enumeration.hasMoreElements() && !request.isPost())
        {
            array.add("_master");
        } else
        {
            java.lang.String s3;
            for(; enumeration.hasMoreElements(); array.add(s3))
            {
                s3 = com.dragonflow.HTTP.HTTPRequest.decodeString((java.lang.String)enumeration.nextElement());
            }

        }
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        int i = 130;
        if(com.dragonflow.SiteView.Platform.isStandardAccount(request.getValue("account")))
        {
            i += 64;
        } else
        {
            i += 8;
        }
        com.dragonflow.Page.treeControl treecontrol = new treeControl(request, "_group", false);
        treecontrol.process(s, s1, s2, array, null, null, i, this, stringbuffer);
        return stringbuffer.toString();
    }

    void printForm(java.lang.String s, jgl.Array array, jgl.HashMap hashmap)
        throws java.lang.Exception
    {
        java.lang.String s1 = request.getValue("user");
        java.lang.String s2 = s;
        boolean flag = false;
        jgl.HashMap hashmap1;
        if(s.equals("Edit"))
        {
            s2 = "Update";
            hashmap1 = com.dragonflow.SiteView.User.findUser(array, s1);
        } else
        {
            s2 = "Add";
            hashmap1 = new HashMap();
            flag = true;
        }
        java.lang.String s3 = s2 + " User";
        printBodyHeader(s3);
        printButtonBar(getHelpPage(), "", getSecondNavItems(request));
        printPrefsBar("Users");
        outputStream.println("<p><H2>" + s3 + "</H2>\n" + getPagePOST(request.getValue("page"), s) + "<input type=hidden name=user value=" + s1 + ">\n");
        printAccessFields(s1, hashmap, hashmap1);
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.lang.StringBuffer stringbuffer1 = new StringBuffer();
        com.dragonflow.Properties.StringProperty.getPrivate(com.dragonflow.Page.userPrefsPage.getValue(hashmap1, "_password"), "_password", "userSuff", stringbuffer, stringbuffer1);
        java.lang.StringBuffer stringbuffer2 = new StringBuffer();
        java.lang.StringBuffer stringbuffer3 = new StringBuffer();
        com.dragonflow.Properties.StringProperty.getPrivate(com.dragonflow.Page.userPrefsPage.getValue(hashmap1, "_password"), "password2", "userSuff2", stringbuffer2, stringbuffer3);
        outputStream.println("<TABLE>\n<TR><TD ALIGN=RIGHT>Login name</TD><TD><TABLE><TR><TD ALIGN=LEFT><input type=text name=_login size=50 value=\"" + com.dragonflow.Page.userPrefsPage.getValue(hashmap1, "_login") + "\"></TD></TR>" + "<TR><TD><FONT SIZE=-1>the login name for this user, if empty, no login name is required</FONT></TD></TR>" + "</TABLE></TD><TD><I>" + com.dragonflow.Page.userPrefsPage.getValue(hashmap, "login") + "</I></TD></TR>" + "<TR><TD ALIGN=RIGHT>Password</TD>" + "<TD><TABLE><TR><TD ALIGN=LEFT>" + stringbuffer.toString() + " size=50></TD></TR>" + stringbuffer1.toString() + "<TR><TD><FONT SIZE=-1>the login password for this user.  if empty, no password is required</FONT></TD></TR>" + "<TR><TD><FONT SIZE=-1>If using LDAP Authentication then this field is not used.\n</FONT></TD></TR>" + "</TABLE></TD><TD><I>" + com.dragonflow.Page.userPrefsPage.getValue(hashmap, "password") + "</I></TD></TR>" + "<TR><TD ALIGN=RIGHT>Password (again)</TD>" + "<TD><TABLE><TR><TD ALIGN=LEFT>" + stringbuffer2.toString() + " size=50></TD></TR>" + stringbuffer3.toString() + "<TR><TD><FONT SIZE=-1>enter the login password for this user again</FONT></TD></TR>" + "</TABLE></TD><TD><I>" + com.dragonflow.Page.userPrefsPage.getValue(hashmap, "password2") + "</I></TD></TR>");
        outputStream.println("<TR><TD ALIGN=RIGHT>LDAP service provider</TD><TD><TABLE><TR><TD ALIGN=LEFT><input type=text name=_ldapserver size=50 value=\"" + com.dragonflow.Page.userPrefsPage.getValue(hashmap1, "_ldapserver") + "\"></TD></TR>" + "<TR><TD><FONT SIZE=-1>the LDAP server to connect to (example: ldap://ldap.this-company.com:389) for authentication</FONT></TD></TR>" + "</TABLE></TD><TD><I>" + com.dragonflow.Page.userPrefsPage.getValue(hashmap, "ldapserver") + "</I></TD></TR>");
        outputStream.println("<TR><TD ALIGN=RIGHT>LDAP Security Principal</TD><TD><TABLE><TR><TD ALIGN=LEFT><input type=text name=_securityprincipal size=50 value=\"" + com.dragonflow.Page.userPrefsPage.getValue(hashmap1, "_securityprincipal") + "\"></TD></TR>" + "<TR><TD><FONT SIZE=-1>If using LDAP Authentication then this field is the Security Principal of\n</FONT></TD></TR>" + "<TR><TD><FONT SIZE=-1>the type \" uid=testuser,ou=TEST,o=this-company.com\".</FONT></TD></TR>" + "</TABLE></TD><TD><I>" + com.dragonflow.Page.userPrefsPage.getValue(hashmap, "securityprincipal") + "</I></TD></TR>");
        java.lang.String s4 = "";
        if(flag)
        {
            s4 = "";
        } else
        if(com.dragonflow.Page.userPrefsPage.getValue(hashmap1, "_disabled").length() > 0)
        {
            s4 = "CHECKED";
        }
        if(s1.equals("administrator"))
        {
            outputStream.println("<input type=hidden name=_disabled value=\"\">");
        } else
        {
            outputStream.println("<TR><TD ALIGN=RIGHT>Disabled</TD><TD><TABLE><TR><TD ALIGN=LEFT><input type=checkbox name=_disabled value=true " + s4 + "></TD></TR>" + "<TR><TD><FONT SIZE=-1>Disable logins for this user</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        }
        if(s1.equals("user") || s1.equals("administrator"))
        {
            outputStream.println("<TR><TD ALIGN=RIGHT>Title</TD><TD><TABLE><TR><TD ALIGN=LEFT>" + getUserTitle(hashmap1) + "</TD></TR>" + "<input type=hidden name=_realName size=50 value=\"" + getUserTitle(hashmap1) + "\">" + "<TR><TD><FONT SIZE=-1> </FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        } else
        {
            outputStream.println("<TR><TD ALIGN=RIGHT>Title</TD><TD><TABLE><TR><TD ALIGN=LEFT><input type=text name=_realName size=50 value=\"" + getUserTitle(hashmap1) + "\">" + "</TD></TR>" + "<TR><TD><FONT SIZE=-1>optional title for this user. the title will appear in the Name field of the User Preference table.   the default title is the login name</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        }
        outputStream.println("</TABLE>");
        outputStream.println("<TABLE WIDTH=100%><TR><TD><input type=submit value=\"" + s2 + "\"> User\n" + "</TD></TR></TABLE>");
        printPermissions(s1, flag, s2, hashmap, hashmap1);
        outputStream.println("</FORM>");
        printFooter(outputStream);
    }

    void printAccessFields(java.lang.String s, jgl.HashMap hashmap, jgl.HashMap hashmap1)
        throws java.lang.Exception
    {
        if(s.equals("administrator") || s.equals("user"))
        {
            outputStream.println("<TR><TD ALIGN=RIGHT>Groups</TD><TD><TABLE><TR><TD ALIGN=LEFT>all groups</TD></TR><TR><TD><FONT SIZE=-1>access is allowed to all groups</FONT></TD></TR></TABLE></TD><TD><I>" + com.dragonflow.Page.userPrefsPage.getValue(hashmap, "_group") + "</I></TD></TR>");
        } else
        if(com.dragonflow.Page.treeControl.useTree())
        {
            outputStream.println(getGroupsHTML("Groups", com.dragonflow.Page.userPrefsPage.getValue(hashmap, "_group"), "optional, restrict access to the selected groups - the default allows access to all groups", hashmap1));
        } else
        {
            outputStream.println("<TR><TD ALIGN=RIGHT>Groups</TD><TD><TABLE><TR><TD ALIGN=LEFT>" + getGroupsHTML(hashmap1) + "</TD></TR>" + "<TR><TD><FONT SIZE=-1>optional, restrict access to the selected groups - the default allows access to all groups</FONT></TD></TR>" + "</TABLE></TD><TD><I>" + com.dragonflow.Page.userPrefsPage.getValue(hashmap, "_group") + "</I></TD></TR>");
        }
    }

    void printPermissions(java.lang.String s, boolean flag, java.lang.String s1, jgl.HashMap hashmap, jgl.HashMap hashmap1)
    {
        if(s.equals("administrator"))
        {
            outputStream.println("<BLOCKQUOTE>");
            outputStream.println("<br><br><h3>Permissions</h3>The " + com.dragonflow.SiteView.Platform.productName + " Administrator is a builtin account with permissions to view and make changes on any pages.");
            outputStream.println("</BLOCKQUOTE>");
        } else
        {
            outputStream.println("<BLOCKQUOTE>");
            outputStream.println("<br><h3>Permissions</h3><TABLE>");
            printPermissionsCheckBoxes(flag, hashmap1);
            outputStream.println("</TABLE>");
            outputStream.println("</BLOCKQUOTE>");
            outputStream.println("<TABLE WIDTH=100%><TR><TD><input type=submit value=\"" + s1 + "\"> User\n" + "</TD></TR></TABLE>");
        }
    }

    void printPermissionsCheckBoxes(boolean flag, jgl.HashMap hashmap)
    {
        printOption(flag, hashmap, "<hr><p><b>Group Actions</b></p>", "", "");
        printOption(flag, hashmap, "Edit Groups", "_groupEdit", "add, rename, copy, or delete groups");
        printOption(flag, hashmap, "Refresh Groups", "_groupRefresh", "refresh groups");
        printOption(flag, hashmap, "Disable Groups", "_groupDisable", "disable or enable groups");
        printOption(flag, hashmap, "<hr><p><b>Monitor Actions</b></p>", "", "");
        printOption(flag, hashmap, "Edit Monitors", "_monitorEdit", "add, edit, or delete monitors");
        printOption(flag, hashmap, "Refresh Monitors", "_monitorRefresh", "refresh monitors");
        printOption(flag, hashmap, "Acknowledge Monitors", "_monitorAcknowledge", "acknowledge monitors");
        printOption(flag, hashmap, "Disable Monitors", "_monitorDisable", "disable or enable monitors");
        printOption(flag, hashmap, "Use Monitor Tools", "_monitorTools", "use the Tools form for a monitor");
        printOption(flag, hashmap, "Use Tools", "_tools", "use the generic Tools forms");
        printOption(flag, hashmap, "<hr><p><b>Alert Actions</b></p>", "", "");
        printOption(flag, hashmap, "View Alerts List", "_alertList", "view the list of the alerts in the alert page");
        printOption(flag, hashmap, "Edit Alerts", "_alertEdit", "add, edit, or delete alerts");
        printOption(flag, hashmap, "Test Alerts", "_alertTest", "test an alert");
        printOption(flag, hashmap, "Disable Alerts Indefinitely", "_alertDisable", "disable or enable alerts indefinitely");
        printOption(flag, hashmap, "Disable Alerts Temporarily", "_alertTempDisable", "disable or enable alerts temporarily");
        printOption(flag, hashmap, "View Alert History Report", "_alertRecentReport", "view the recent history report for an alert");
        printOption(flag, hashmap, "Create Adhoc Alert Reports", "_alertAdhocReport", "create adhoc alert reports");
        printOption(flag, hashmap, "<hr><p><b>Report Actions</b></p>", "", "");
        printOption(flag, hashmap, "Generate Reports", "_reportGenerate", "generate a scheduled report manually");
        printOption(flag, hashmap, "Show Report Toolbar", "_reportToolbar", "include links at the top on reports");
        printOption(flag, hashmap, "Edit Reports", "_reportEdit", "add, edit, or delete reports");
        printOption(flag, hashmap, "Create Adhoc Reports", "_reportAdhoc", "create adhoc reports");
        printOption(flag, hashmap, "Disable Reports", "_reportDisable", "disable or enable reports");
        printOption(flag, hashmap, "View Monitor History Report", "_monitorRecent", "view the recent history report for a monitor");
        printOption(flag, hashmap, "<hr><p><b>Preference Actions</b></p>", "", "");
        printOption(flag, hashmap, "Edit Preferences", "_preference", "use any of the Preference forms");
        printOption(flag, hashmap, "Test Preferences", "_preferenceTest", "test a preference setting");
        printOption(flag, hashmap, "<hr><p><b>Other Options</b></p>", "", "");
        printOption(flag, hashmap, "Edit Multi-View", "_multiEdit", "add, edit or delete items on the Multi-View page");
        printOption(flag, hashmap, "Use Browse and Summary", "_browse", "use the Browse Monitor form and Monitor Description Report");
        printOption(flag, hashmap, "View Progress", "_progress", "view the Progress page showing monitors that are running");
//        printOption(flag, hashmap, "View " + com.dragonflow.SiteView.TopazInfo.getTopazName() + " Configuration Changes", "_topazConfigChangesReport", "View the configuration changes reported to " + com.dragonflow.SiteView.TopazInfo.getTopazName());
        printOption(flag, hashmap, "View Logs", "_logs", "view the raw data for monitors, alerts and other logs");
        printOption(flag, hashmap, "View Health Page", "_healthView", "View the SiteView Health (self-monitoring) page");
        printOption(flag, hashmap, "Edit Health Parameters", "_healthEdit", "Edit SiteView Health parameters");
        printOption(flag, hashmap, "Disable/Enable Application Health Monitors", "_healthDisable", "Enable/Disable SiteView Health monitoring");
        printOption(flag, hashmap, "Use the Support Tool", "_support", "use the Send Support Request form");
    }

    void printAddForm(java.lang.String s)
        throws java.lang.Exception
    {
        if(!request.getAccount().equals("administrator"))
        {
            outputStream.println("<hr>Administrator access only<hr>");
            return;
        }
        jgl.Array array = getUserFrames();
        if(request.isPost() && com.dragonflow.Page.treeControl.notHandled(request))
        {
            java.lang.String s1 = request.getValue("user");
            jgl.HashMap hashmap = new HashMap();
            java.lang.String s2 = request.getValue("_login");
            for(int i = 1; i < array.size(); i++)
            {
                jgl.HashMap hashmap1 = (jgl.HashMap)array.at(i);
                java.lang.String s5 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_id");
                if(s5.equals(s1))
                {
                    continue;
                }
                java.lang.String s7 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_login");
                if(!s7.equalsIgnoreCase(s2) || request.getAccount().equals("administrator") && s7.length() <= 0)
                {
                    continue;
                }
                hashmap.put("login", "login is already in use - please choose another login");
                break;
            }

            java.lang.String s3 = com.dragonflow.Properties.StringProperty.getPrivate(request, "_password", "userSuff", null, null);
            java.lang.String s4 = com.dragonflow.Properties.StringProperty.getPrivate(request, "password2", "userSuff2", null, null);
            java.lang.String s6 = com.dragonflow.SiteView.User.checkPassword(getMasterConfig(), s3, s4);
            if(s6.length() > 0)
            {
                hashmap.put("password", s6);
            }
            if(hashmap.size() > 0)
            {
                super.printCGIHeader();
                printForm(s, array, hashmap);
                return;
            }
            if(s1.equals("user") && request.getValue("disabled").length() == 0)
            {
                com.dragonflow.SiteView.Platform.enableUserAccess();
            }
            java.lang.Object obj = null;
            if(s.equals("Add"))
            {
                jgl.HashMap hashmap2 = (jgl.HashMap)array.at(0);
                s1 = (java.lang.String)hashmap2.get("_nextID");
                if(s1 == null)
                {
                    s1 = "1";
                }
                obj = new HashMapOrdered(true);
                ((jgl.HashMap) (obj)).put("_id", "login" + s1);
                array.add(obj);
                hashmap2.put("_nextID", com.dragonflow.Utils.TextUtils.increment(s1));
            } else
            {
                obj = com.dragonflow.SiteView.User.findUser(array, s1);
            }
            ((jgl.HashMap) (obj)).put("_login", request.getValue("_login"));
            ((jgl.HashMap) (obj)).put("_password", s3);
            ((jgl.HashMap) (obj)).put("_ldapserver", request.getValue("_ldapserver"));
            ((jgl.HashMap) (obj)).put("_securityprincipal", request.getValue("_securityprincipal"));
            ((jgl.HashMap) (obj)).put("_realName", request.getValue("_realName"));
            ((jgl.HashMap) (obj)).put("_disabled", request.getValue("_disabled"));
            if(com.dragonflow.SiteView.Platform.isPortal())
            {
                ((jgl.HashMap) (obj)).put("_homeView", request.getValue("_homeView"));
                ((jgl.HashMap) (obj)).put("_buttonBar", request.getValue("_buttonBar"));
                ((jgl.HashMap) (obj)).put("_query", com.dragonflow.Page.portalChooserPage.getQueryChooseListSelectedItem(request));
            }
            ((jgl.HashMap) (obj)).put("_progress", request.getValue("_progress"));
            ((jgl.HashMap) (obj)).put("_topazConfigChangesReport", request.getValue("_topazConfigChangesReport"));
            ((jgl.HashMap) (obj)).put("_alertList", request.getValue("_alertList"));
            ((jgl.HashMap) (obj)).put("_browse", request.getValue("_browse"));
            ((jgl.HashMap) (obj)).put("_tools", request.getValue("_tools"));
            ((jgl.HashMap) (obj)).put("_support", request.getValue("_support"));
            ((jgl.HashMap) (obj)).put("_preference", request.getValue("_preference"));
            ((jgl.HashMap) (obj)).put("_preferenceTest", request.getValue("_preferenceTest"));
            ((jgl.HashMap) (obj)).put("_logs", request.getValue("_logs"));
            ((jgl.HashMap) (obj)).put("_multiEdit", request.getValue("_multiEdit"));
            ((jgl.HashMap) (obj)).put("_groupEdit", request.getValue("_groupEdit"));
            ((jgl.HashMap) (obj)).put("_groupDisable", request.getValue("_groupDisable"));
            ((jgl.HashMap) (obj)).put("_groupRefresh", request.getValue("_groupRefresh"));
            ((jgl.HashMap) (obj)).put("_monitorEdit", request.getValue("_monitorEdit"));
            ((jgl.HashMap) (obj)).put("_monitorDisable", request.getValue("_monitorDisable"));
            ((jgl.HashMap) (obj)).put("_monitorRefresh", request.getValue("_monitorRefresh"));
            ((jgl.HashMap) (obj)).put("_monitorAcknowledge", request.getValue("_monitorAcknowledge"));
            ((jgl.HashMap) (obj)).put("_monitorRecent", request.getValue("_monitorRecent"));
            ((jgl.HashMap) (obj)).put("_monitorTools", request.getValue("_monitorTools"));
            ((jgl.HashMap) (obj)).put("_alertEdit", request.getValue("_alertEdit"));
            ((jgl.HashMap) (obj)).put("_alertDisable", request.getValue("_alertDisable"));
            ((jgl.HashMap) (obj)).put("_alertTempDisable", request.getValue("_alertTempDisable"));
            ((jgl.HashMap) (obj)).put("_alertRecentReport", request.getValue("_alertRecentReport"));
            ((jgl.HashMap) (obj)).put("_alertAdhocReport", request.getValue("_alertAdhocReport"));
            ((jgl.HashMap) (obj)).put("_alertTest", request.getValue("_alertTest"));
            ((jgl.HashMap) (obj)).put("_reportEdit", request.getValue("_reportEdit"));
            ((jgl.HashMap) (obj)).put("_reportDisable", request.getValue("_reportDisable"));
            ((jgl.HashMap) (obj)).put("_reportAdhoc", request.getValue("_reportAdhoc"));
            ((jgl.HashMap) (obj)).put("_reportToolbar", request.getValue("_reportToolbar"));
            ((jgl.HashMap) (obj)).put("_reportGenerate", request.getValue("_reportGenerate"));
            ((jgl.HashMap) (obj)).put("_healthView", request.getValue("_healthView"));
            ((jgl.HashMap) (obj)).put("_healthEdit", request.getValue("_healthEdit"));
            ((jgl.HashMap) (obj)).put("_healthDisable", request.getValue("_healthDisable"));
            ((jgl.HashMap) (obj)).remove("_group");
            java.util.Enumeration enumeration = request.getValues("_group");
            boolean flag = false;
            if(!com.dragonflow.Page.treeControl.useTree())
            {
                for(; enumeration.hasMoreElements(); ((jgl.HashMap) (obj)).add("_group", (java.lang.String)enumeration.nextElement())) { }
            } else
            {
                do
                {
                    if(!enumeration.hasMoreElements())
                    {
                        break;
                    }
                    java.lang.String s8 = com.dragonflow.HTTP.HTTPRequest.decodeString((java.lang.String)enumeration.nextElement());
                    if(!s8.equals("_master"))
                    {
                        continue;
                    }
                    flag = true;
                    break;
                } while(true);
                if(!flag)
                {
                    for(java.util.Enumeration enumeration1 = request.getValues("_group"); enumeration1.hasMoreElements(); ((jgl.HashMap) (obj)).add("_group", com.dragonflow.HTTP.HTTPRequest.decodeString((java.lang.String)enumeration1.nextElement()))) { }
                }
            }
            ((jgl.HashMap) (obj)).put("_demo", request.getValue("_demo"));
            ((jgl.HashMap) (obj)).put("_license", request.getValue("_license"));
            saveUserFrames(array);
            if(request.usesCookieLogin())
            {
                request.addOtherHeader("Set-Cookie: value=" + com.dragonflow.Utils.TextUtils.getValue(((jgl.HashMap) (obj)), "_id") + "|" + com.dragonflow.Utils.TextUtils.getValue(((jgl.HashMap) (obj)), "_login") + "|" + com.dragonflow.Utils.TextUtils.obscure(s3) + "; path=/");
            }
            super.printCGIHeader();
            printRefreshPage(getPageLink(request.getValue("page"), ""), 0);
        } else
        {
            printForm(s, array, new HashMap());
        }
    }

    java.lang.String getUserTitle(jgl.HashMap hashmap)
    {
        java.lang.String s = com.dragonflow.Page.userPrefsPage.getValue(hashmap, "_realName");
        if(s.length() == 0)
        {
            s = com.dragonflow.Page.userPrefsPage.getValue(hashmap, "_login");
        }
        return s;
    }

    void printListForm(java.lang.String s)
        throws java.io.IOException
    {
        java.lang.String s1 = "User Preferences";
        printBodyHeader(s1);
        printButtonBar(getHelpPage(), "", getSecondNavItems(request));
        printPrefsBar("Users");
        outputStream.println("<H2>User Profiles</H2><p>User profiles control viewing and editing permissions on this SiteView installation.</p><TABLE WIDTH=100% BORDER=1 cellspacing=0><TR CLASS=\"tabhead\"><TH align=left>Name</TH><TH>Login URL</TH>\n");
        if(request.actionAllowed("_users"))
        {
            outputStream.println("<TH WIDTH=10%>Edit</TH><TH WIDTH=3%>Del</TH>");
        }
        outputStream.println("</TR>");
        jgl.Array array = getUserFrames();
        java.util.Enumeration enumeration = array.elements();
        if(enumeration.hasMoreElements())
        {
            enumeration.nextElement();
        }
        while(enumeration.hasMoreElements()) 
        {
            jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
            java.lang.String s2 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_id");
            java.lang.String s3 = getUserTitle(hashmap);
            if(com.dragonflow.Utils.TextUtils.getValue(hashmap, "_disabled").length() > 0)
            {
                s3 = s3 + " (disabled)";
            }
            java.lang.String s4 = "/SiteView?account=" + s2;
            if(request.actionAllowed("_users"))
            {
                java.lang.String s5 = getPageLink(request.getValue("page"), "") + "&user=" + s2;
                java.lang.String s6 = "<A href=" + s5 + "&operation=Delete>X</a>";
                if(s2.equals("user") || s2.equals("administrator"))
                {
                    s6 = "&nbsp;";
                }
                outputStream.println("<TR><TD align=left>" + s3 + "</TD>");
                if(com.dragonflow.Utils.TextUtils.getValue(hashmap, "_disabled").length() <= 0)
                {
                    outputStream.println("<TD><A href=" + s4 + ">" + s4 + "</a></TD>");
                } else
                {
                    outputStream.println("<TD>" + s4 + " </TD>");
                }
                outputStream.println("<TD><A href=" + s5 + "&operation=Edit>Edit</a></TD>" + "<TD>" + s6 + "</TD>" + "</TR>\n");
            } else
            {
                outputStream.println("<TR><TD align=left>" + s3 + "</TD>" + "<TD><A href=" + s4 + ">" + s4 + "</a></TD>" + "</TR>\n");
            }
        }
        outputStream.println("</TABLE><BR>");
        if(request.actionAllowed("_users"))
        {
            outputStream.println("<A HREF=" + getPageLink(request.getValue("page"), "Add") + ">Add</A> New User Profile\n" + "<br><br>\n");
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
        java.lang.String s1 = request.getValue("user");
        jgl.Array array = getUserFrames();
        jgl.HashMap hashmap = com.dragonflow.SiteView.User.findUser(array, s1);
        if(request.isPost())
        {
            try
            {
                array.remove(hashmap);
                saveUserFrames(array);
                printRefreshPage(getPageLink(request.getValue("page"), "List"), 0);
            }
            catch(java.lang.Exception exception)
            {
                printError("There was a problem deleting the user.", exception.toString(), "/SiteView/" + request.getAccountDirectory() + "/SiteView.html");
            }
        } else
        {
            printBodyHeader("Delete Confirmation");
            outputStream.println("<FONT SIZE=+1>Are you sure you want to remove the user <B>" + getUserTitle(hashmap) + "</B>?</FONT>" + "<p>" + getPagePOST(request.getValue("page"), s) + "<input type=hidden name=user value=" + s1 + ">\n" + "<TABLE WIDTH=100% BORDER=0><TR>" + "<TD WIDTH=6%></TD><TD WIDTH=41%><input type=submit value=\"" + s + "\"></TD>" + "<TD WIDTH=6%></TD><TD ALIGN=RIGHT WIDTH=41%><A HREF=" + getPageLink(request.getValue("page"), "") + ">Return to Detail</A></TD><TD WIDTH=6%></TD>" + "</TR></TABLE></FORM>");
            printFooter(outputStream);
        }
    }

    void printPreferencesSaved()
    {
        printPreferencesSaved("/SiteView/" + request.getAccountDirectory() + "/SiteView.html", "", 0);
    }

    void printErrorPage(java.lang.String s)
    {
        printBodyHeader("User Preferences");
        outputStream.println("<p><CENTER><H2></H2></CENTER>\n<HR>There were errors in the entered information.  Use your browser's back button to return\nthe general preferences editing page\n");
        java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s, "\t");
        outputStream.print("<UL>\n");
        for(int i = 0; i < as.length; i++)
        {
            if(as[i].length() > 0)
            {
                outputStream.print("<LI><B>" + as[i] + "</B>\n");
            }
        }

        outputStream.print("</UL><HR></BODY>\n");
    }

    public void printBody()
        throws java.lang.Exception
    {
        java.lang.String s = request.getValue("operation");
        if(s.length() == 0)
        {
            s = "List";
        }
        if(s.equals("List"))
        {
            if(!request.actionAllowed("_preference"))
            {
                throw new HTTPRequestException(557);
            }
            printListForm(s);
        } else
        {
            if(!request.actionAllowed("_users"))
            {
                throw new HTTPRequestException(557);
            }
            if(s.equals("Add"))
            {
                printAddForm(s);
            } else
            if(s.equals("Delete"))
            {
                printDeleteForm(s);
            } else
            if(s.equals("Edit"))
            {
                printAddForm(s);
            } else
            {
                printError("The link was incorrect", "unknown operation", "/SiteView/" + request.getAccountDirectory() + "/SiteView.html");
            }
        }
    }

    public void printCGIHeader()
    {
        if(request.isPost() && (request.getValue("operation").equals("Add") || request.getValue("operation").equals("Edit")))
        {
            return;
        } else
        {
            super.printCGIHeader();
            return;
        }
    }

    jgl.Array getUserFrames()
        throws java.io.IOException
    {
        jgl.Array array = null;
        if(isPortalServerRequest())
        {
            try
            {
                array = ReadGroupFrames("_users");
            }
            catch(java.lang.Exception exception)
            {
                array = new Array();
            }
            jgl.HashMap hashmap = getMasterConfig();
            com.dragonflow.SiteView.User.initializeUsersList(array, hashmap);
        } else
        {
            array = com.dragonflow.SiteView.User.readUsers();
        }
        return array;
    }

    void saveUserFrames(jgl.Array array)
        throws java.io.IOException
    {
        if(isPortalServerRequest())
        {
            WriteGroupFrames("_users", array);
            return;
        } else
        {
            com.dragonflow.SiteView.User.writeUsers(array);
            return;
        }
    }

    public static void main(java.lang.String args[])
        throws java.io.IOException
    {
        com.dragonflow.Page.userPrefsPage userprefspage = new userPrefsPage();
        if(args.length > 0)
        {
            userprefspage.args = args;
        }
        userprefspage.handleRequest();
    }
}
