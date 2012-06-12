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

import java.util.Vector;

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequestException;
import com.dragonflow.Properties.HashMapOrdered;

// Referenced classes of package com.dragonflow.Page:
// settingsPrefsPage, CGI

public class mailPrefsPage extends com.dragonflow.Page.settingsPrefsPage
{

    public static java.lang.String type = "Mail";

    public mailPrefsPage()
    {
    }

    void printPreferencesSaved()
    {
        printRefreshPage(getPageLink("mailPrefs", "test"), 0);
    }

    public void saveAdditionalMailPrefs()
    {
        jgl.HashMap hashmap = null;
        java.lang.String s = request.getValue("additionalMail");
        if(!s.equals("new"))
        {
            hashmap = getAdditionalSettings(type, s);
        }
        if(hashmap == null)
        {
            hashmap = new HashMap();
        }
        hashmap.put("_name", request.getValue("additionalMailName"));
        hashmap.put("_disabled", request.getValue("additionalMailDisabled"));
        hashmap.put("_template", request.getValue("additionalMailTemplate"));
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.lang.String s1 = com.dragonflow.Properties.ScheduleProperty.requestToScheduleString(request, stringbuffer);
        if(stringbuffer.length() > 0)
        {
            printError("The schedule has an invalid time format", stringbuffer.toString(), getPageLink("mailPrefs", ""));
            return;
        }
        if(s1.length() > 0)
        {
            hashmap.put("_schedule", s1);
        }
        java.lang.String s2 = com.dragonflow.Utils.TextUtils.toEmailList(request.getValue("email"));
        hashmap.put("_email", s2);
        s = saveAdditionalPrefs(type, s, hashmap);
        printRefreshPage(getPageLink("mailPrefs", ""), 0);
    }

    void printDeleteForm(java.lang.String s)
    {
        java.lang.String s1 = request.getValue("additionalMail");
        jgl.HashMap hashmap = getSettings();
        jgl.HashMap hashmap1 = null;
        java.util.Enumeration enumeration = com.dragonflow.Page.mailPrefsPage.getValues(hashmap, "_additionalMail");
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            jgl.HashMap hashmap2 = com.dragonflow.Utils.TextUtils.stringToHashMap((java.lang.String)enumeration.nextElement());
            if(com.dragonflow.Page.mailPrefsPage.getValue(hashmap2, "_id").equals(s1))
            {
                hashmap1 = hashmap2;
            }
        } while(true);
        if(request.isPost())
        {
            deleteAdditionalSetting(type, s1);
            printRefreshPage(getPageLink("mailPrefs", "") + "#additionalMail", 0);
        } else
        {
            java.lang.String s2 = "";
            if(hashmap1 != null)
            {
                s2 = com.dragonflow.Page.mailPrefsPage.getValue(hashmap1, "_name");
            }
            outputStream.println("<FONT SIZE=+1>Are you sure you want to delete the e-mail settings for <B>" + s2 + "</B>?</FONT>" + "<p>" + getPagePOST("mailPrefs", s) + "<input type=hidden name=additionalMail value=\"" + s1 + "\">" + "<TABLE WIDTH=\"100%\" BORDER=0><TR>" + "<TD WIDTH=\"6%\"></TD><TD WIDTH=\"41%\"><input type=submit value=\"" + s + " E-mail Setting\"></TD>" + "<TD WIDTH=\"6%\"></TD><TD ALIGN=RIGHT WIDTH=\"41%\"><A HREF=" + getPageLink("mailPrefs", "") + ">Return to Mail Preferences</A></TD><TD WIDTH=\"6%\"></TD>" + "</TR></TABLE></FORM>");
            printFooter(outputStream);
        }
    }

    void savePreferences()
    {
        try
        {
            jgl.HashMap hashmap = getMasterConfig();
            hashmap.put("_mailServer", request.getValue("mailServer"));
            hashmap.put("_mailServerBackup", request.getValue("mailServerBackup"));
            hashmap.put("_fromAddress", com.dragonflow.Utils.TextUtils.toEmailList(request.getValue("fromAddress")));
            hashmap.put("_autoEmail", com.dragonflow.Utils.TextUtils.toEmailList(request.getValue("autoEmail")));
            hashmap.put("_autoDaily", request.getValue("autoDaily"));
            hashmap.put("_autoStartup", request.getValue("autoStartup"));
            saveMasterConfig(hashmap);
            printPreferencesSaved();
        }
        catch(java.io.IOException ioexception)
        {
            printError("The preferences could not be saved", "master.config file could not be saved", "10");
        }
    }

    void printForm()
    {
        jgl.HashMap hashmap = getSettings();
        printBodyHeader("E-mail Preferences");
        printButtonBar("MailPref.htm", "", getSecondNavItems(request));
        printPrefsBar("E-mail");
        outputStream.println("<p><CENTER><H2>E-mail Preferences</H2></CENTER><p>\n");
        if(request.isStandardAccount())
        {
            java.lang.String s = "";
            java.lang.String s1 = com.dragonflow.Page.mailPrefsPage.getValue(hashmap, "_mailServer");
            if(s1.length() == 0 || s1.equals("mail.dragonflow.com") || s1.equals("gateway.dragonflow.com") || s1.equals("gateway.Dragonflow.com"))
            {
                s = "<blockquote><B>Note: Please enter the name of your local mail server so " + com.dragonflow.SiteView.Platform.productName + " will be able to send email alerts and messages.</B></blockquote>";
            }
            outputStream.println(getPagePOST("mailPrefs", "save") + "<hr><TABLE border=0 width=100% cellspacing=0 cellpadding=5>" + "<TR><TD ALIGN=LEFT VALIGN=TOP WIDTH=20%><P>Mail Server Domain Name:</TD>" + "<TD VALIGN=TOP><input type=text name=mailServer size=35 value=\"" + com.dragonflow.Page.mailPrefsPage.getValue(hashmap, "_mailServer") + "\">\n" + "</TD><TD VALIGN=TOP>" + "Enter the domain name of the mail server to use for sending SiteView messages" + " and alerts.  This server should be an SMTP mail server. For example," + " gateway.this-company.com.</TD></TR>" + "<tr><td colspan=3><hr></td></tr>" + "<TR><TD ALIGN=LEFT VALIGN=TOP WIDTH=20%>" + "Administrator E-mail Address:</TD><TD VALIGN=TOP>" + "<input type=text name=autoEmail size=35 value=\"" + com.dragonflow.Page.mailPrefsPage.getValue(hashmap, "_autoEmail") + "\">\n" + "</TD><TD VALIGN=TOP>Enter the administrator e-mail address where " + com.dragonflow.SiteView.Platform.productName + " will send status messages." + " For example, " + com.dragonflow.SiteView.Platform.supportEmail + ".\n" + "</TD></TR>\n" + "<tr><td colspan=3><hr></td></tr>" + "<TR><TD ALIGN=LEFT VALIGN=TOP WIDTH=20%> " + com.dragonflow.SiteView.Platform.productName + " Status Messages</TD><TD VALIGN=TOP>" + "<input type=checkbox name=autoDaily value=checked " + com.dragonflow.Page.mailPrefsPage.getValue(hashmap, "_autoDaily") + ">Daily Status\n" + "<BR><input type=checkbox name=autoStartup value=checked " + com.dragonflow.Page.mailPrefsPage.getValue(hashmap, "_autoStartup") + "> " + com.dragonflow.SiteView.Platform.productName + " Starts/Restarts\n" + "</TD><TD VALIGN=TOP>" + "Select which regular" + com.dragonflow.SiteView.Platform.productName + " status messages you would like to receive.</TD></TR>" + "<tr><td colspan=3><hr></td></tr>");
            outputStream.println("<TR><TD ALIGN=LEFT VALIGN=TOP WIDTH=20%>From Email Address:</TD><TD VALIGN=TOP> <input type=text name=fromAddress size=35 value=\"" + com.dragonflow.Page.mailPrefsPage.getValue(hashmap, "_fromAddress") + "\">\n" + "</TD><TD VALIGN=TOP>(optional) Enter the email address used as the From Address for  " + com.dragonflow.SiteView.Platform.productName + " messages. " + "This is used to make it easier to browse or sort email generated by " + com.dragonflow.SiteView.Platform.productName + ".\n" + "For example, " + com.dragonflow.SiteView.Platform.supportEmail + ".</TD></TR>\n" + "<tr><td colspan=3><hr></td></tr>" + "<TR><TD ALIGN=LEFT VALIGN=TOP WIDTH=20%> Backup Mail Server Domain Name: </TD><TD VALIGN=TOP>" + " <input type=text name=mailServerBackup size=40 value=\"" + com.dragonflow.Page.mailPrefsPage.getValue(hashmap, "_mailServerBackup") + "\">\n" + "</TD><TD VALIGN=TOP>(optional) Enter the domain name of a backup mail server" + " to use for sending messages when the primary mail server cannot be reached." + " This server should be an SMTP mail server. For example," + com.dragonflow.SiteView.Platform.exampleMailServer + ".\n" + "</TD></TR></TABLE><hr>" + "<br><input type=submit value=\"Save Changes\">\n" + "<p>\n" + "</FORM>\n");
            outputStream.println("</TABLE></CENTER><P><A HREF=" + getPageLink("mailPrefs", "additionalMail") + "&additionalMail=new>Add</A> additional e-mail settings \n");
        }
        java.util.Enumeration enumeration = com.dragonflow.Page.mailPrefsPage.getValues(hashmap, "_additionalMail");
        outputStream.print("<p><HR><A NAME=additionalMail>Additional e-mail settings allow you to create <b>email list, template to use</b>, and <b>schedule</b>, which you can then specify\nwhen creating e-mail alerts.</A><P><CENTER>\n<TABLE WIDTH=\"100%\" BORDER=2 cellspacing=0><CAPTION align=left><font size=4><b>Additional E-mail Settings</b></font></CAPTION>\n<TR CLASS=\"tabhead\">\n<TH>Name</TH>\n<TH>Status</TH>\n<TH>E-mail</TH>\n<TH WIDTH=\"2%\">Edit</TH>\n<TH WIDTH=\"1%\">Del</TH>\n");
        if(!enumeration.hasMoreElements())
        {
            outputStream.println("<TR><TD COLSPAN=5 ALIGN=CENTER>no additional e-mail settings</TD></TR>\n");
        } else
        {
            jgl.HashMap hashmap1;
            for(; enumeration.hasMoreElements(); outputStream.println("<TD align=center><A HREF=" + getPageLink("mailPrefs", "Delete") + "&additionalMail=" + com.dragonflow.Page.mailPrefsPage.getValue(hashmap1, "_id") + ">X</TD></TR>"))
            {
                hashmap1 = com.dragonflow.Utils.TextUtils.stringToHashMap((java.lang.String)enumeration.nextElement());
                java.lang.String s2 = com.dragonflow.Page.mailPrefsPage.getValue(hashmap1, "_name");
                outputStream.println("<TR><TD><B>" + s2 + "</B></TD>");
                if(com.dragonflow.Page.mailPrefsPage.getValue(hashmap1, "_disabled").length() > 0)
                {
                    outputStream.println("<TD><B>disabled</B></TD>");
                } else
                if(com.dragonflow.Page.mailPrefsPage.getValue(hashmap1, "_schedule").length() > 0)
                {
                    outputStream.println("<TD>scheduled</TD>");
                } else
                {
                    outputStream.println("<TD>enabled</TD>");
                }
                outputStream.println("<TD>" + com.dragonflow.Page.mailPrefsPage.getValue(hashmap1, "_email") + "</TD>");
                outputStream.println("<TD align=center><A HREF=" + getPageLink("mailPrefs", "additionalMail") + "&additionalMail=" + com.dragonflow.Page.mailPrefsPage.getValue(hashmap1, "_id") + ">Edit</TD>");
            }

        }
        outputStream.println("</TABLE></CENTER><P><A HREF=" + getPageLink("mailPrefs", "additionalMail") + "&additionalMail=new>Add</A> additional e-mail setting like <b>email list, template to use, and schedule</b>");
        printFooter(outputStream);
    }

    void printAdditionalSettingForm()
    {
        java.lang.Object obj = getSettings();
        java.lang.String s = request.getValue("additionalMail");
        java.util.Enumeration enumeration = com.dragonflow.Page.mailPrefsPage.getValues(((jgl.HashMap) (obj)), "_additionalMail");
        obj = null;
        java.lang.Object obj1;
        if(!s.equals("new"))
        {
            do
            {
                if(!enumeration.hasMoreElements())
                {
                    break;
                }
                obj1 = com.dragonflow.Utils.TextUtils.stringToHashMap((java.lang.String)enumeration.nextElement());
                if(!com.dragonflow.Page.mailPrefsPage.getValue(((jgl.HashMap) (obj1)), "_id").equals(s))
                {
                    continue;
                }
                obj = obj1;
                break;
            } while(true);
        }
        if(obj == null)
        {
            obj = new HashMapOrdered(true);
        }
        if(s.equals("new"))
        {
            obj1 = "Add Additional E-mail Setting";
        } else
        {
            obj1 = "Edit Additional E-mail Setting";
        }
        printBodyHeader(((java.lang.String) (obj1)));
        java.lang.String s1 = "AddMail.htm";
        printButtonBar(s1, "", getSecondNavItems(request));
        printPrefsBar("Mail");
        outputStream.println("<p><CENTER><H2>" + obj1 + "</H2></CENTER><p>\n" + getPagePOST("mailPrefs", "saveAdditional") + "<input type=hidden name=additionalMail value=" + request.getValue("additionalMail") + ">\n");
        outputStream.println("The name of these e-mail settings is used to specify e-mail targets when adding alerts<BLOCKQUOTE>\nSetting Name <input type=text size=30 name=additionalMailName value=\"" + com.dragonflow.Page.mailPrefsPage.getValue(((jgl.HashMap) (obj)), "_name") + "\">\n" + "</BLOCKQUOTE>\n" + "The e-mail addresses that alerts will be sent to when using the e-mail setting. Separate multiple addresses with commas (example: " + com.dragonflow.SiteView.Platform.supportEmail + ", " + com.dragonflow.SiteView.Platform.salesEmail + ")" + "<BLOCKQUOTE>\n" + "E-mail To: <input type=text size=60 name=email value=\"" + com.dragonflow.Page.mailPrefsPage.getValue(((jgl.HashMap) (obj)), "_email") + "\">\n" + "</BLOCKQUOTE>\n" + "Disabling the e-mail settings prevents alert e-mail messages from being sent via that e-mail setting" + "<BLOCKQUOTE>\n" + "<input type=checkbox " + com.dragonflow.Page.mailPrefsPage.getValue(((jgl.HashMap) (obj)), "_disabled") + " name=additionalMailDisabled value=CHECKED>Disabled\n" + "</BLOCKQUOTE>\n");
        java.util.Vector vector = com.dragonflow.SiteView.SiteViewGroup.getTemplateList("templates.mail", request);
        java.util.Vector vector1 = new Vector();
        vector1.addElement("");
        vector1.addElement("use template from alert");
        for(int i = 0; i < vector.size(); i++)
        {
            vector1.addElement(vector.elementAt(i));
            vector1.addElement(vector.elementAt(i));
        }

        outputStream.println("<input type=submit value=\"Save Additional Setting\">\n<p><HR><CENTER><H3>Advanced Options</H3></CENTER><TABLE><TR><TD>Template</TD><TD><select size=1 name=additionalMailTemplate>" + com.dragonflow.Page.mailPrefsPage.getOptionsHTML(vector1, com.dragonflow.Page.mailPrefsPage.getValue(((jgl.HashMap) (obj)), "_template")) + "</SELECT></TD></TR>\n" + "<TR><TD COLSPAN=2>optional template to use with this e-mail settings - if a template is selected, this template will be used " + "for sending the alert to this e-mail setting.</TD></TR>");
        if(!request.getPermission("_mailSchedule").equals("hidden"))
        {
            outputStream.println("<TR><TD>Schedule</TD><TD>\n");
            com.dragonflow.Properties.ScheduleProperty.printScheduleTable(outputStream, com.dragonflow.Page.mailPrefsPage.getValue(((jgl.HashMap) (obj)), "_schedule"), "");
            outputStream.println("</TD></TR><TR><TD COLSPAN=2>optional schedule for these settings to be enabled - for example, enable Sunday from 10:00 to 22:00</TD></TR><TR></TR>");
        }
        outputStream.println("</TABLE><P>\n</FORM>\n");
        if(com.dragonflow.SiteView.Platform.isSiteSeerAccount(request.getAccount()))
        {
            outputStream.print("<BR><B>Note:</B> Times entered must be Mountain Time Zone in the U.S.");
        }
        printFooter(outputStream);
    }

    java.lang.String getAlertURL()
    {
        return getPageLink("alert", "List", request.getValue("view"));
    }

    void printTestForm()
	{
		
	    printBodyHeader("Mail Test");
	    jgl.HashMap hashmap = getMasterConfig();
	    printButtonBar("AlertMailto.htm", "");
	    outputStream.print("<CENTER><H2>Mail Test</H2></CENTER><P>\n" + getPagePOST("mailPrefs", "test", request.getValue("view")) + "Send a test message using e-mail.\n" + "<p>\n" + "Enter the e-mail address where the message will be sent.  For example, " + com.dragonflow.SiteView.Platform.supportEmail + ".  Separate multiple addresses using commas.\n" + "<p> E-mail Address: <input type=text name=email size=50>\n" + "<p> Mail Server: " + com.dragonflow.Page.mailPrefsPage.getValue(hashmap, "_mailServer") + "\n" + "<p> Backup Mail Server: " + com.dragonflow.Page.mailPrefsPage.getValue(hashmap, "_mailServerBackup") + "\n");
	    if(com.dragonflow.Page.mailPrefsPage.getValue(hashmap, "_mailAlertCC").length() > 0)
	    {
	        outputStream.print("<P> CC: " + com.dragonflow.Page.mailPrefsPage.getValue(hashmap, "_mailAlertCC") + "\n");
	    }
	    outputStream.print("<p>&nbsp;</p><TABLE border=\"0\" width=\"90%\"><tr><td>\n<input type=submit name=send value=\"Send\"> a test e-mail message</td><td width=\"25%\">&nbsp;</td>\n<td align=right><A HREF=" + getPageLink("mailPrefs", "") + ">Back to Mail Preferences</A></TD>" + "</TR></TABLE></FORM>\n");
	    printFooter(outputStream);
	}

    void testEmail()
    {
        outputStream.println("<CENTER><H2>Mail Test</H2></CENTER>\n<HR>\n");
        if(!isPortalServerRequest())
        {
            printContentStartComment();
            java.lang.String s = com.dragonflow.SiteView.Platform.productName + " test message";
            java.lang.String s1 = "This is a test.  This is only a test.\n\n - " + com.dragonflow.SiteView.Platform.productName;
            jgl.HashMap hashmap = getMasterConfig();
            java.lang.String s3 = com.dragonflow.Page.mailPrefsPage.getValue(hashmap, "_mailAlertCC");
            jgl.Array array = new Array();
            java.lang.String s4 = com.dragonflow.Utils.MailUtils.mail(hashmap, request.getValue("email"), s, s1, s3, array);
            if(s4.length() == 0)
            {
                outputStream.println("<h3>Mail Test Completed</h3><p>The test message was sent to " + request.getValue("email") + ".\n");
            } else
            {
                printBodyHeader("Mail Test");
                outputStream.println("<h3>Mail Test Completed</h3><p>The test message to " + request.getValue("email") + " could not be sent.\n" + "<p>\n" + "The error was: " + s4 + ".\n" + "<P>");
                if(request.getPermission("_support").equals("true"))
                {
                    outputStream.println(getPagePOST("support", "Send") + "<input type=submit\tvalue=\"Create Support Request\"><P>" + "If can't get your test e-mails to work, you can create a support request by\n" + "by clicking on the button above.\n" + "<input type=hidden name=attachPrefs value=true>" + "<input type=hidden name=format value=text>" + "<input type=hidden name=returnName value=\"" + com.dragonflow.Utils.TextUtils.escapeHTML("Back to Mail Preferences") + "\">" + "<input type=hidden name=returnURL value=\"" + com.dragonflow.Utils.TextUtils.escapeHTML(getPageLink("mailPrefs", "")) + "\">" + "<input type=hidden name=message value=\"" + com.dragonflow.Utils.TextUtils.escapeHTML("MAIL TEST FAILED\n\n" + s4) + "\"><BR>" + "</FORM>" + "<p>\n");
                }
            }
            outputStream.println("<p><PRE>\n");
            java.lang.String s5;
            for(java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); outputStream.println(com.dragonflow.Utils.TextUtils.escapeHTML(s5)))
            {
                s5 = (java.lang.String)enumeration.nextElement();
            }

            outputStream.println("\n</PRE>");
            printContentEndComment();
        } else
        {
            com.dragonflow.SiteView.PortalSiteView portalsiteview = (com.dragonflow.SiteView.PortalSiteView)getSiteView();
            if(portalsiteview != null)
            {
                java.lang.String s2 = portalsiteview.getURLContentsFromRemoteSiteView(request, "_centrascopeRefreshMatch");
                outputStream.println(s2);
            }
        }
        outputStream.println("<HR><A HREF=" + getAlertURL() + ">Back to Alerts</A><BR>\n" + "</BODY>\n");
    }

    public void printBody()
        throws java.lang.Exception
    {
        java.lang.String s = request.getValue("operation");
        if(s.equals("test"))
        {
            if(!request.actionAllowed("_preferenceTest"))
            {
                throw new HTTPRequestException(557);
            }
            if(request.isPost())
            {
                testEmail();
            } else
            {
                printTestForm();
            }
        } else
        {
            if(!request.actionAllowed("_preference"))
            {
                throw new HTTPRequestException(557);
            }
            if(s.equals("Delete"))
            {
                printDeleteForm(s);
            } else
            if(request.isPost())
            {
                if(s.equals("save") || s.equals("setup"))
                {
                    savePreferences();
                } else
                if(s.equals("test"))
                {
                    testEmail();
                } else
                if(s.equals("saveAdditional"))
                {
                    saveAdditionalMailPrefs();
                } else
                {
                    printError("The link was incorrect", "unknown operation", "/SiteView/" + request.getAccountDirectory() + "/SiteView.html");
                }
            } else
            if(s.equals("additionalMail"))
            {
                printAdditionalSettingForm();
            } else
            {
                printForm();
            }
        }
    }

    public static void main(java.lang.String args[])
        throws java.io.IOException
    {
        com.dragonflow.Page.mailPrefsPage mailprefspage = new mailPrefsPage();
        if(args.length > 0)
        {
            mailprefspage.args = args;
        }
        mailprefspage.handleRequest();
    }

}
