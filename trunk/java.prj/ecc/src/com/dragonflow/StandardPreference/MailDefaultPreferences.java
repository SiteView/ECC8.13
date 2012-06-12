/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.StandardPreference;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.util.Vector;

import jgl.Array;
import com.dragonflow.Properties.BooleanProperty;
import com.dragonflow.Properties.StringProperty;

public class MailDefaultPreferences extends com.dragonflow.SiteView.Preferences {

    public static com.dragonflow.Properties.StringProperty pMailServer;

    public static com.dragonflow.Properties.StringProperty pAutoEmail;

    public static com.dragonflow.Properties.StringProperty pAutoDaily;

    public static com.dragonflow.Properties.StringProperty pAutoStartup;

    public static com.dragonflow.Properties.StringProperty pFromAddress;

    public static com.dragonflow.Properties.StringProperty pMailServerBackup;

    public MailDefaultPreferences() {
    }

    public java.util.Vector test(java.lang.String s) throws java.lang.Exception {
        java.util.Vector vector = new Vector();
        java.lang.String s1 = com.dragonflow.SiteView.Platform.productName + " test message";
        java.lang.String s2 = "This is a test.  This is only a test.\n\n - " + com.dragonflow.SiteView.Platform.productName;
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        java.lang.String s5 = getValue("_mailAlertCC");
        java.lang.String s6 = "";
        if (!s.startsWith("_id:")) {
            s6 = s;
        } else {
            java.lang.String s7 = s.substring(4);
            java.util.Vector vector1 = getPreferenceProperties("MailInstancePreferences", "_additionalMail", "_id", s7, com.dragonflow.Api.APISiteView.FILTER_ALL);
            if (vector1 != null) {
                java.util.HashMap hashmap1 = (java.util.HashMap) vector1.get(0);
                s6 = (java.lang.String) hashmap1.get("_email");
            }
        }
        if (s6.length() == 0) {
            s2 = "Email address was not found or supplied!";
            throw new Exception(s2);
        }
        jgl.Array array = new Array();
        java.lang.String s8 = com.dragonflow.Utils.MailUtils.mail(hashmap, s6, s1, s2, s5, array);
        if (s8.length() == 0) {
            java.lang.String s3 = "Mail Test Completed! The test message was sent to " + s6;
            vector.add(s3);
        } else {
            java.lang.String s4 = "Mail Test Completed! The test message to " + s6 + " could not be sent." + " The error was: " + s8;
            throw new Exception(s4);
        }
        java.lang.String s9;
        for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); vector.add(com.dragonflow.Utils.TextUtils.escapeHTML(s9))) {
            s9 = (java.lang.String) enumeration.nextElement();
        }

        return vector;
    }

    static {
        pMailServer = new StringProperty("_mailServer");
        pMailServer.setDisplayText("Mail Server Domain Name", "   Enter the domain name of the mail server to use for sending messages. This server should be an SMTP mail server. For example, mail.this-company.com.");
        pMailServer.setParameterOptions(true, 1, false);
        pAutoEmail = new StringProperty("_autoEmail");
        pAutoEmail.setDisplayText("Administrator E-mail Address:", "Enter the administrator e-mail address where SiteView will send status messages. For example, sysadmin@this-company.com.");
        pAutoEmail.setParameterOptions(true, 2, false);
        pAutoDaily = new BooleanProperty("_autoDaily", "");
        pAutoDaily.setDisplayText("Send Daily status messages", "Select if you would like to receive this regular status message.");
        pAutoDaily.setParameterOptions(true, 3, false);
        pAutoStartup = new BooleanProperty("_autoStartup", "");
        pAutoStartup.setDisplayText("Send message whenever SiteView starts", "Select if you would like to receive this regular status message.");
        pAutoStartup.setParameterOptions(true, 4, false);
        pFromAddress = new StringProperty("_fromAddress");
        pFromAddress.setDisplayText("From Email Address",
                "(optional) Enter the email address used as the From Address for SiteView messages. This is used to make it easier to browse or sort email generated by SiteView. For example, sysadmin@this-company.com.");
        pFromAddress.setParameterOptions(true, 5, false);
        pMailServerBackup = new StringProperty("_mailServerBackup");
        pMailServerBackup.setDisplayText("Backup Mail Server Domain Name",
                "(optional) Enter the domain name of a backup mail server to use for sending messages when the primary mail server cannot be reached. This server should be an SMTP mail server. For example, mail.this-company.com.");
        pMailServerBackup.setParameterOptions(true, 6, false);
        com.dragonflow.Properties.StringProperty astringproperty[] = { pMailServer, pAutoEmail, pAutoDaily, pAutoStartup, pFromAddress, pMailServerBackup };
        com.dragonflow.StandardPreference.MailDefaultPreferences.addProperties("com.dragonflow.StandardPreference.MailDefaultPreferences", astringproperty);
    }
}
