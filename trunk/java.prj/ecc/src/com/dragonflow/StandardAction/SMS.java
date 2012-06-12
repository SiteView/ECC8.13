/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.StandardAction;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.io.File;

import jgl.Array;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.Utils.CommandLine;

public class SMS extends com.dragonflow.SiteView.Action {

    static com.dragonflow.Properties.StringProperty pPhoneNumber;

    static java.lang.String SMS_BAT_FILE = "SMS.bat";

    public SMS() {
        runType = 2;
    }

    public boolean execute() {
        return executeSync();
    }

    public java.lang.String getActionString() {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append("SMS");
        java.lang.String s = getProperty(pPhoneNumber);
        if (s.length() > 0) {
            stringbuffer.append(" ");
            stringbuffer.append(s);
        }
        return stringbuffer.toString();
    }

    public void initializeFromArguments(jgl.Array array, jgl.HashMap hashmap) {
        if (array.size() > 0) {
            setProperty(pPhoneNumber, array.at(0));
        }
    }

    public java.lang.String verify(com.dragonflow.Properties.StringProperty stringproperty, java.lang.String s, com.dragonflow.HTTP.HTTPRequest httprequest, jgl.HashMap hashmap) {
        if (stringproperty == pPhoneNumber && s.length() <= 0) {
            hashmap.put(stringproperty, "Need a phone number");
        }
        return super.verify(stringproperty, s, httprequest, hashmap);
    }

    public java.lang.String getActionDescription() {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append((java.lang.String) getClassProperty("label"));
        java.lang.String s = getProperty(pPhoneNumber);
        if (s.length() > 0) {
            stringbuffer.append(" \"" + s + "\"");
        }
        return stringbuffer.toString();
    }

    public boolean executeSync() {
        boolean flag = false;
        try {
            java.lang.String s = "";
            long l = -1L;
            java.lang.String s1 = "";
            java.lang.String s3 = args[0];
            if (s.length() == 0) {
                java.lang.String s4 = "";
                boolean flag1 = true;
                java.io.File file = new File(com.dragonflow.SiteView.Platform.getRoot() + "/tools/" + SMS_BAT_FILE);
                s4 = file.getAbsolutePath();
                flag1 = file.exists();
                if (flag1) {
                    com.dragonflow.Utils.CommandLine commandline = new CommandLine();
                    java.lang.String s8 = monitor.getProperty(com.dragonflow.SiteView.Monitor.pName);
                    java.lang.String s9 = monitor.getProperty(com.dragonflow.SiteView.Monitor.pStateString);
                    s9 = com.dragonflow.Utils.TextUtils.parseNonPrintableCharacters(s9);
                    java.lang.String s10 = monitor.getOwner().getProperty(com.dragonflow.SiteView.Monitor.pName);
                    if (com.dragonflow.Utils.TextUtils.hasSpaces(s8)) {
                        s8 = "\"" + s8 + "\"";
                    }
                    if (com.dragonflow.Utils.TextUtils.hasSpaces(s10)) {
                        s10 = "\"" + s10 + "\"";
                    }
                    s9 = "\"" + s9 + "\"";
                    boolean flag2 = true;
                    boolean flag3 = true;
                    jgl.Array array1 = new Array();
                    java.lang.String s2 = com.dragonflow.SiteView.Platform.getRoot() + "/tools/" + SMS_BAT_FILE;
                    if (flag3) {
                        s2 = s2 + " " + s3;
                        if (com.dragonflow.Utils.TextUtils.hasChars(s8, "`;&|<>")) {
                            com.dragonflow.Log.LogManager.log("Error", "Removed illegal characters from monitor name \"" + s8 + "\" before running script");
                            s8 = com.dragonflow.Utils.TextUtils.removeChars(s8, "`;&|<>");
                        }
                        s2 = s2 + " " + s8;
                        s2 = s2 + " " + s9;
                    }
                    jgl.Array array = commandline.exec(s2);
                    l = commandline.getExitValue();
                    s = s2 + " (" + l + ")";
                    if (l == 0L) {
                        flag = true;
                    } else if (l == 4000L) {
                        monitor.signalMonitor();
                        s = s + ", re-running monitor";
                    }
                    for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements();) {
                        s1 = s1 + (java.lang.String) enumeration.nextElement() + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
                    }

                } else {
                    s = "file missing: " + s4;
                }
            }
            java.lang.String s5 = "SMS alert performed";
            if (!flag) {
                s5 = "SMS ALERT ERROR RESULT";
                java.lang.String s6 = getSetting("_autoEmail");
                java.lang.String s7 = "There was a problem performing SMS alert." + com.dragonflow.SiteView.Platform.FILE_NEWLINE + com.dragonflow.SiteView.Platform.FILE_NEWLINE + baseAlertLogEntry(s5, s, flag) + " alert-result: " + l
                        + com.dragonflow.SiteView.Platform.FILE_NEWLINE + " alert-output: " + s1 + com.dragonflow.SiteView.Platform.FILE_NEWLINE + com.dragonflow.SiteView.Platform.FILE_NEWLINE + com.dragonflow.SiteView.Platform.FILE_NEWLINE
                        + com.dragonflow.SiteView.Platform.FILE_NEWLINE + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
                if (s6.length() != 0) {
                    com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                    siteviewgroup.simpleMail(s6, "SiteView " + s5, s7);
                }
            }
            messageBuffer.append(s5 + ", " + s);
            logAlert(baseAlertLogEntry(s5, s, flag) + " alert-result: " + l + com.dragonflow.SiteView.Platform.FILE_NEWLINE + " alert-output: " + s1 + com.dragonflow.SiteView.Platform.FILE_NEWLINE + com.dragonflow.SiteView.Platform.FILE_NEWLINE);
        } catch (java.lang.Exception exception) {
            exception.printStackTrace();
        }
        return flag;
    }

    static {
        pPhoneNumber = new StringProperty("_phoneNumber", "");
        pPhoneNumber.setDisplayText("SMS Number", "The phone number that will receive the sms alert.");
        pPhoneNumber.setParameterOptions(true, 1, false);
        com.dragonflow.Properties.StringProperty astringproperty[] = { pPhoneNumber };
        com.dragonflow.StandardAction.SMS.addProperties("com.dragonflow.StandardAction.SMS", astringproperty);
        com.dragonflow.StandardAction.SMS.setClassProperty("com.dragonflow.StandardAction.SMS", "description", "Send an alert using wireless Short Message Service.");
        com.dragonflow.StandardAction.SMS.setClassProperty("com.dragonflow.StandardAction.SMS", "help", "AlertSMS.htm");
        com.dragonflow.StandardAction.SMS.setClassProperty("com.dragonflow.StandardAction.SMS", "title", "Send SMS Message");
        com.dragonflow.StandardAction.SMS.setClassProperty("com.dragonflow.StandardAction.SMS", "label", "SMS");
        com.dragonflow.StandardAction.SMS.setClassProperty("com.dragonflow.StandardAction.SMS", "name", "SMS");
        com.dragonflow.StandardAction.SMS.setClassProperty("com.dragonflow.StandardAction.SMS", "class", "SMS");
        com.dragonflow.StandardAction.SMS.setClassProperty("com.dragonflow.StandardAction.SMS", "prefs", "");
        com.dragonflow.StandardAction.SMS.setClassProperty("com.dragonflow.StandardAction.SMS", "classType", "advanced");
        if (com.dragonflow.SiteView.Platform.isWindows()) {
            com.dragonflow.StandardAction.SMS.setClassProperty("com.dragonflow.StandardAction.SMS", "loadable", "true");
        } else {
            com.dragonflow.StandardAction.SMS.setClassProperty("com.dragonflow.StandardAction.SMS", "loadable", "false");
        }
    }
}
