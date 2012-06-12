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

import java.util.Vector;

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.Properties.ScalarProperty;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.Utils.CommandLine;

public class Page extends com.dragonflow.SiteView.Action {

    public static com.dragonflow.Properties.StringProperty pMessage;

    public static com.dragonflow.Properties.StringProperty pTemplate;

    public static com.dragonflow.Properties.StringProperty pPager;

    public static com.dragonflow.Properties.StringProperty pPagerType;

    public static com.dragonflow.Properties.StringProperty pAlphaPhone;

    public static com.dragonflow.Properties.StringProperty pAlphaPIN;

    public static com.dragonflow.Properties.StringProperty pDirectPhone;

    public static com.dragonflow.Properties.StringProperty pOptionPhone;

    public static com.dragonflow.Properties.StringProperty pOption;

    public static com.dragonflow.Properties.StringProperty pCustom;

    static jgl.HashMap portLocks = new HashMap();

    public void initializeFromArguments(jgl.Array array, jgl.HashMap hashmap) {
        if (array.size() > 0) {
            setProperty(pMessage, ((java.lang.String) array.at(0)).replace('_', ' '));
        }
        if (array.size() > 1) {
            setProperty(pTemplate, array.at(1));
        } else {
            setProperty(pTemplate, "Default");
        }
        unsetProperty(pPager);
        for (java.util.Enumeration enumeration = hashmap.values("_id"); enumeration.hasMoreElements(); addProperty(pPager, (java.lang.String) enumeration.nextElement())) {
        }
        java.util.Enumeration enumeration1 = hashmap.keys();
        while (enumeration1.hasMoreElements()) {
            java.lang.String s = (java.lang.String) enumeration1.nextElement();
            if (s.startsWith("_pager")) {
                setProperty(s, (java.lang.String) hashmap.get(s));
            }
        } 
        if (getProperty(pPagerType).equals("direct")) {
            setProperty(pPagerType, "option");
            setProperty(pOptionPhone, getProperty(pDirectPhone));
        }
        if (getProperty(pPagerType).equals("option")) {
            setProperty(pAlphaPhone, getProperty(pOptionPhone));
            setProperty(pAlphaPIN, getProperty(pOption));
        }
    }

    public java.lang.String getActionString() {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append("page");
        java.lang.String s = getProperty(pMessage);
        java.lang.String s1 = getProperty(pTemplate);
        if (s1.length() > 0 && s.length() == 0) {
            s = " ";
        }
        if (s.length() > 0) {
            stringbuffer.append(" ");
            stringbuffer.append(s.replace(' ', '_'));
            if (s1.length() > 0) {
                stringbuffer.append(" ");
                stringbuffer.append(s1);
            }
        }
        if (getProperty(pPagerType).length() == 0) {
            for (java.util.Enumeration enumeration = getMultipleValues(pPager); enumeration.hasMoreElements(); stringbuffer.append((java.lang.String) enumeration.nextElement())) {
                stringbuffer.append(" _id=");
            }

        } else {
            if (getProperty(pPagerType).equals("option")) {
                setProperty(pOptionPhone, getProperty(pAlphaPhone));
                setProperty(pOption, getProperty(pAlphaPIN));
                setProperty(pAlphaPhone, "");
                setProperty(pAlphaPIN, "");
                if (getProperty(pOption).length() == 0) {
                    setProperty(pPagerType, "direct");
                    setProperty(pDirectPhone, getProperty(pOptionPhone));
                    setProperty(pOptionPhone, "");
                }
            }
            appendProperty(stringbuffer, pPagerType);
            appendProperty(stringbuffer, pAlphaPhone);
            appendProperty(stringbuffer, pAlphaPIN);
            appendProperty(stringbuffer, pDirectPhone);
            appendProperty(stringbuffer, pOptionPhone);
            appendProperty(stringbuffer, pOption);
            appendProperty(stringbuffer, pCustom);
        }
        return stringbuffer.toString();
    }

    public java.lang.String getActionDescription() {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append((java.lang.String) getClassProperty("label"));
        java.lang.String s = getProperty(pMessage);
        if (s.length() > 0 && !s.equals(" ")) {
            stringbuffer.append(" \"" + getProperty(pMessage) + "\"");
        }
        java.lang.String s1 = getProperty(pTemplate);
        if (s1.length() > 0 && !s1.equals("Default")) {
            stringbuffer.append(" " + s1);
        }
        if (getProperty(pPagerType).length() == 0) {
            java.lang.String s2 = "_name=";
            java.util.Enumeration enumeration = getMultipleValues(pPager);
            boolean flag = true;
            boolean flag1 = false;
            while (enumeration.hasMoreElements()) {
                java.lang.String s3 = (java.lang.String) enumeration.nextElement();
                java.lang.String s4 = "";
                if (!s3.equals("default")) {
                    java.lang.String s5 = getOwner().getPagerSettings(s3);
                    if (s5.length() > 0) {
                        int i = s5.indexOf(s2);
                        if (i >= 0) {
                            int j = s5.indexOf(" ", i);
                            if (j == -1) {
                                j = s5.length();
                            }
                            s4 = s5.substring(i + s2.length(), j);
                            s4 = com.dragonflow.Utils.TextUtils.storedValueToValue(s4);
                        }
                    }
                    if (s4.length() > 0) {
                        if (!flag) {
                            stringbuffer.append(", ");
                        } else {
                            stringbuffer.append(" to ");
                            if (flag1) {
                                stringbuffer.append("Default, ");
                            }
                            flag = false;
                        }
                        stringbuffer.append(s4);
                    }
                } else {
                    flag1 = true;
                }
            } 
        }
        return stringbuffer.toString();
    }

    public boolean defaultsAreSet(jgl.HashMap hashmap) {
        return hashmap.get("_pagerType") != null;
    }

    public boolean showOptionalProperties() {
        return getProperty(pPagerType).length() > 0;
    }

    public java.lang.String verify(com.dragonflow.Properties.StringProperty stringproperty, java.lang.String s, com.dragonflow.HTTP.HTTPRequest httprequest, jgl.HashMap hashmap) {
        return super.verify(stringproperty, s, httprequest, hashmap);
    }

    public java.util.Vector getScalarValues(com.dragonflow.Properties.ScalarProperty scalarproperty, com.dragonflow.HTTP.HTTPRequest httprequest, com.dragonflow.Page.CGI cgi) throws com.dragonflow.SiteViewException.SiteViewException {
        if (scalarproperty == pTemplate) {
            java.util.Vector vector = com.dragonflow.SiteView.SiteViewGroup.getTemplateList("templates.page", httprequest);
            java.util.Vector vector2 = new Vector();
            for (int i = 0; i < vector.size(); i ++) {
                vector2.addElement(vector.elementAt(i));
                vector2.addElement(vector.elementAt(i));
            }

            return vector2;
        }
        if (scalarproperty == pPager) {
            java.util.Enumeration enumeration = null;
            if (httprequest.isStandardAccount()) {
                jgl.HashMap hashmap = cgi.getMasterConfig();
                enumeration = hashmap.values("_additionalPager");
            } else {
                com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                com.dragonflow.SiteView.SiteViewObject siteviewobject = siteviewgroup.getElement(httprequest.getAccount());
                enumeration = siteviewobject.getMultipleValues("_additionalPager");
            }
            java.util.Vector vector3 = new Vector();
            vector3.addElement("default");
            vector3.addElement("Default");
            jgl.HashMap hashmap1;
            for (; enumeration.hasMoreElements(); vector3.addElement(hashmap1.get("_name"))) {
                hashmap1 = com.dragonflow.Utils.TextUtils.stringToHashMap((java.lang.String) enumeration.nextElement());
                vector3.addElement(hashmap1.get("_id"));
            }

            return vector3;
        }
        if (scalarproperty == pPagerType) {
            java.util.Vector vector1 = new Vector();
            vector1.addElement("alpha");
            vector1.addElement("Alphanumeric Pager");
            vector1.addElement("option");
            vector1.addElement("Numeric Pager");
            vector1.addElement("custom");
            vector1.addElement("Custom Modem String");
            return vector1;
        } else {
            return super.getScalarValues(scalarproperty, httprequest, cgi);
        }
    }

    static synchronized java.lang.Object getPagerPortLock(java.lang.String s) {
        java.lang.Object obj = portLocks.get(s);
        if (obj == null) {
            com.dragonflow.Log.LogManager.log("RunMonitor", "using pager port: " + s);
            obj = new Object();
            portLocks.put(s, obj);
        }
        return obj;
    }

    public Page() {
        runType = 3;
    }

    public boolean execute() {
        boolean flag = false;
        if (hasValue("_id")) {
            jgl.Array array = new Array();
            java.util.Enumeration enumeration = getMultipleValues("_id");
            int i = 0;
            while (enumeration.hasMoreElements()) {
                java.lang.String s = (java.lang.String) enumeration.nextElement();
                boolean flag1 = true;
                boolean flag2 = false;
                java.lang.String s1 = "default";
                if (s.equals("default")) {
                    jgl.Array array1 = getCurrentPropertyNames();
                    for (int j = 0; j < array1.size(); j ++) {
                        java.lang.String s4 = (java.lang.String) array1.at(j);
                        if (s4.startsWith("_pager") && !s4.equals("_pagerPort")) {
                            unsetProperty(s4);
                        }
                    }

                } else {
                    java.lang.String s2 = getOwner().getPagerSettings(s);
                    if (s2.length() > 0) {
                        jgl.HashMap hashmap = com.dragonflow.Utils.TextUtils.stringToHashMap(s2);
                        s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_name");
                        java.util.Enumeration enumeration2 = hashmap.keys();
                        while (enumeration2.hasMoreElements()) {
                            java.lang.String s5 = (java.lang.String) enumeration2.nextElement();
                            if (s5.startsWith("_pager")) {
                                setProperty(s5, com.dragonflow.Utils.TextUtils.getValue(hashmap, s5));
                            }
                        } 
                        flag2 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_disabled").length() > 0;
                        if (!flag2) {
                            java.lang.String s6 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_schedule");
                            if (s6.length() > 0) {
                                flag2 = !com.dragonflow.Properties.ScheduleProperty.isEnabled(s6);
                            }
                        }
                    } else {
                        flag1 = false;
                    }
                }
                if (flag1) {
                    if (!flag2) {
                        messageBuffer = new StringBuffer();
                        i ++;
                        boolean flag3 = execute1(s1);
                        java.lang.String s3 = messageBuffer.toString();
                        if (!flag3) {
                            array.add(s);
                            com.dragonflow.Log.LogManager.log(getSetting(com.dragonflow.SiteView.Monitor.pErrorLogName), s3 + ", " + monitor.getProperty(com.dragonflow.SiteView.Monitor.pName) + " "
                                    + monitor.getProperty(com.dragonflow.SiteView.SiteViewObject.pOwnerID));
                        }
                        com.dragonflow.Log.LogManager.log("Progress", monitor.getProperty(com.dragonflow.SiteView.SiteViewObject.pOwnerID) + "\t" + monitor.getProperty(com.dragonflow.SiteView.Monitor.pName) + "\t" + s3);
                    }
                } else {
                    com.dragonflow.Log.LogManager.log(getSetting(com.dragonflow.SiteView.Monitor.pErrorLogName), "Missing page setting id " + s + ", " + monitor.getProperty(com.dragonflow.SiteView.Monitor.pName) + " "
                            + monitor.getProperty(com.dragonflow.SiteView.SiteViewObject.pOwnerID));
                }
            } 
            messageBuffer.setLength(0);
            unsetProperty("_id");
            for (java.util.Enumeration enumeration1 = array.elements(); enumeration1.hasMoreElements(); addProperty("_id", (java.lang.String) enumeration1.nextElement())) {
            }
            flag = array.size() == 0;
        } else {
            flag = execute1("");
        }
        return flag;
    }

    public boolean execute1(java.lang.String s) {
        boolean flag = false;
        java.lang.String s1 = "";
        maxRuns = getSettingAsLong("_pagerAttempts", 4);
        attemptDelay = getSettingAsLong("_pagerAttemptDelay", 120);
        if (attemptDelay < 10L) {
            attemptDelay = 10L;
        }
        attemptDelay *= 1000L;
        java.lang.String s2 = "1234";
        if (args.length > 0) {
            s2 = args[0];
        }
        java.lang.String s3 = "Default";
        if (args.length > 1) {
            s3 = args[1];
        }
        java.lang.String s4 = getSetting("_pagerType");
        if (s4.equalsIgnoreCase("alpha")) {
            java.lang.StringBuffer stringbuffer = new StringBuffer();
            s1 = createMessage(stringbuffer, "templates.page", s3);
            if (s1.length() == 0) {
                if (s2.length() > 0) {
                    s2 = s2 + " ";
                }
                s2 = s2 + stringbuffer.toString();
            }
            int i = getSettingAsLong("_pagerAlphaMax", 128);
            if (s2.length() > i) {
                com.dragonflow.Log.LogManager.log("RunMonitor", "Pager Alert message truncated: " + s2);
                s2 = s2.substring(0, i);
            }
        } else {
            s2 = com.dragonflow.Utils.TextUtils.keepChars(s2, "0123456789#*");
            if (s2.length() == 0) {
                s2 = "1234";
            }
        }
        jgl.Array array = new Array();
        if (s1.length() == 0) {
            array = pagerSend(s2);
            flag = array == null;
            s1 = s2;
        }
        java.lang.String s5 = "";
        if (!flag) {
            for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements();) {
                s5 = s5 + (java.lang.String) enumeration.nextElement() + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
            }

        }
        java.lang.String s6 = "Pager alert sent";
        if (!flag) {
            java.lang.String s7 = "(" + triggerCount + "/" + maxRuns + ")";
            if (triggerCount >= maxRuns) {
                s6 = "PAGER ALERT NOT SENT " + s7;
            } else {
                s6 = "Pager alert retry " + s7;
            }
        }
        if (s.length() != 0 && !s.equals("default")) {
            s6 = s6 + ", " + s;
        }
        if (!flag) {
            java.lang.String s8 = getSetting("_autoEmail");
            if (s8.length() != 0) {
                java.lang.String s9 = "There was a problem sending a SiteView pager alert." + com.dragonflow.SiteView.Platform.FILE_NEWLINE + com.dragonflow.SiteView.Platform.FILE_NEWLINE + s1 + com.dragonflow.SiteView.Platform.FILE_NEWLINE
                        + com.dragonflow.SiteView.Platform.FILE_NEWLINE + "output: " + s5 + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
                com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                siteviewgroup.simpleMail(s8, com.dragonflow.SiteView.Platform.productName + " " + s6, s9);
            }
        }
        messageBuffer.append(s6 + ", " + s1);
        logAlert(baseAlertLogEntry(s6, s1, flag) + " alert-output: " + s5 + com.dragonflow.SiteView.Platform.FILE_NEWLINE);
        return flag;
    }

    public jgl.Array pagerExec(java.lang.String s, java.lang.String s1, int i, java.lang.String s2, java.lang.String s3, java.lang.String s4) {
        jgl.Array array = null;
        com.dragonflow.Log.LogManager.log("RunMonitor", "pager begin, " + s + ", " + s2 + ", " + s3 + ", " + s4);
        synchronized (com.dragonflow.StandardAction.Page.getPagerPortLock(s)) {
            com.dragonflow.Log.LogManager.log("RunMonitor", "pager send, " + s + ", " + s2 + ", " + s3 + ", " + s4);
            if (s.startsWith("http")) {
                java.lang.String s5 = "";
                java.lang.String s7 = getSetting("_pagerProxy");
                java.lang.String s9 = getSetting("_pagerProxyUsername");
                java.lang.String s10 = getSetting("_pagerProxyPassword");
                java.lang.String s11 = getSetting("_pagerUsername");
                java.lang.String s12 = getSetting("_pagerPassword");
                java.lang.StringBuffer stringbuffer = new StringBuffer();
                long l = 50000L;
                java.lang.String s13 = s + "&speed=" + java.net.URLEncoder.encode(s1) + "&init=" + java.net.URLEncoder.encode(s2) + "&dial=" + java.net.URLEncoder.encode(s3) + "&hangup=" + java.net.URLEncoder.encode(s4);
                com.dragonflow.Utils.SocketSession socketsession = com.dragonflow.Utils.SocketSession.getSession(null);
                long al[] = com.dragonflow.StandardMonitor.URLMonitor.checkURL(socketsession, s13, s5, "", s7, s9, s10, null, s11, s12, "", stringbuffer, l, "", 0, i * 1000, null);
                java.lang.String s14 = stringbuffer.toString();
                java.lang.String s15 = "<PRE>";
                java.lang.String s16 = "</PRE>";
                int j = s14.indexOf(s15);
                int k = s14.indexOf(s16);
                long l1 = al[0];
                java.lang.String s17 = "ok";
                if (l1 != 200L) {
                    s17 = "ERROR: connecting to modem (" + com.dragonflow.SiteView.Monitor.lookupStatus(l1) + ")";
                    array = com.dragonflow.SiteView.Platform.split('\n', s14);
                    array.pushFront(s17);
                } else if (j != -1 && k != -1) {
                    s14 = s14.substring(j + s15.length(), k);
                    array = com.dragonflow.SiteView.Platform.split('\n', s14);
                } else {
                    s17 = "ERROR: receiving modem reply";
                    array = com.dragonflow.SiteView.Platform.split('\n', s14);
                    array.pushFront(s17);
                }
                java.lang.String s18 = s14;
                if (s18.length() > 500) {
                    s18 = s14.substring(0, 500);
                }
                com.dragonflow.Log.LogManager.log("RunMonitor", "connecting to remote pager, status=" + l1 + ", url=" + s13 + ", result=" + s17 + ", details=" + s18);
                socketsession.close();
                com.dragonflow.SiteView.Platform.sleep(1000L);
            } else {
                java.lang.String s6 = getSetting("_pagerPassword");
                if (s6.length() > 0) {
                    s6 = " -password " + s6;
                }
                java.lang.String s8 = com.dragonflow.SiteView.Platform.sendModemCommand() + " " + s1 + s6 + " " + s + " ";
                com.dragonflow.Utils.CommandLine commandline = new CommandLine();
                array = commandline.exec(s8 + s2);
                if (commandline.getExitValue() != 0) {
                    array.pushFront("ERROR: connecting to modem");
                } else {
                    com.dragonflow.Utils.CommandLine commandline1 = new CommandLine();
                    array = commandline1.exec(s8 + s3);
                    if (commandline1.getExitValue() != 0) {
                        array.pushFront("ERROR: dialing");
                    }
                    if (s4.length() > 0) {
                        com.dragonflow.Utils.CommandLine commandline2 = new CommandLine();
                        commandline2.exec(s8 + s4);
                        if (commandline2.getExitValue() != 0) {
                            array.pushFront("ERROR: hanging up");
                        }
                    }
                }
                com.dragonflow.SiteView.Platform.sleep(getSettingAsLong("_delayBetweenPages") * 1000L);
            }
            com.dragonflow.Log.LogManager.log("RunMonitor", "pager end, " + s + ", " + s2 + ", " + s3 + ", " + s4);
            if (array.size() > 0) {
                com.dragonflow.Log.LogManager.log("RunMonitor", "pager result, " + array.at(0));
            }
        }
        return array;
    }

    public jgl.Array pagerSend(java.lang.String s) {
        jgl.Array array = null;
        s = s.replace(' ', '_');
        s = s.replace('\n', '*');
        java.lang.String s1 = getSetting("_pagerPort");
        java.lang.String s3 = getSetting("_pagerSpeed");
        if (s3.equals("1200") || s3.equals("")) {
            s3 = "";
        } else {
            s3 = "-" + s3 + " ";
        }
        java.lang.String s4 = "AT" + getSetting("_pagerInitOptions") + " 3";
        java.lang.String s5 = getPagerDial(s);
        java.lang.String s6 = getSetting("_pagerHangupCmd");
        if (s6.length() > 0) {
            s6 = s6 + " 3";
        } else if (!getSetting("_pagerType").equals("alpha")) {
            s6 = "ATH 3";
        }
        int i = 2 * (getSettingAsLong("_pagerTimeout", 30) + 3 + 3);
        array = pagerExec(s1, s3, i, s4, s5, s6);
        java.lang.String s7 = (java.lang.String) array.popFront();
        if (s7.startsWith("ERROR: connecting to modem")) {
            array.pushFront("Modem Not Responding" + com.dragonflow.SiteView.Platform.FILE_NEWLINE);
            java.lang.String s2 = getSetting("_pagerPortBackup");
            if (s2.length() > 0) {
                jgl.Array array1 = array;
                array = pagerExec(s2, s3, i, s4, s5, s6);
                s7 = (java.lang.String) array.popFront();
                if (s7.startsWith("ERROR: connecting")) {
                    array.pushFront(s7);
                    array.pushFront("Modem Not Responding" + com.dragonflow.SiteView.Platform.FILE_NEWLINE);
                    com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                    java.lang.String s8 = getSetting("_autoEmail");
                    java.lang.String s10 = com.dragonflow.SiteView.Platform.productName + " Modem Pager Backup Port failed : " + s2;
                    java.lang.String s12 = "Backup modem pager port failed (" + s2 + ")  Primary modem pager port (" + getSetting("_pagerPort") + ") was not responding." + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
                    s12 = s12 + "init: " + s4 + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
                    s12 = s12 + "dial: " + s5 + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
                    if (s6 != null) {
                        s12 = s12 + "hangup: " + s6 + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
                    }
                    for (java.util.Enumeration enumeration = array1.elements(); enumeration.hasMoreElements();) {
                        s12 = s12 + (java.lang.String) enumeration.nextElement() + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
                    }

                    if (s8.length() > 0) {
                        siteviewgroup.simpleMail(s8, s10, s12);
                    }
                    com.dragonflow.Log.LogManager.log(getSetting(com.dragonflow.SiteView.Monitor.pErrorLogName), "PAGER PORT BACKUP FAILED: " + s10);
                } else {
                    com.dragonflow.SiteView.SiteViewGroup siteviewgroup1 = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                    java.lang.String s9 = getSetting("_autoEmail");
                    java.lang.String s11 = com.dragonflow.SiteView.Platform.productName + " Modem Pager Backup Port used : " + s2;
                    java.lang.String s13 = "Alternate modem page port was used (" + s2 + ") because the primary port (" + getSetting("_pagerPort") + ") was not responding." + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
                    s13 = s13 + "init: " + s4 + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
                    s13 = s13 + "dial: " + s5 + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
                    if (s6 != null) {
                        s13 = s13 + "hangup: " + s6 + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
                    }
                    for (java.util.Enumeration enumeration1 = array1.elements(); enumeration1.hasMoreElements();) {
                        s13 = s13 + (java.lang.String) enumeration1.nextElement() + com.dragonflow.SiteView.Platform.FILE_NEWLINE;
                    }

                    if (s9.length() > 0) {
                        siteviewgroup1.simpleMail(s9, s11, s13);
                    }
                    com.dragonflow.Log.LogManager.log(getSetting(com.dragonflow.SiteView.Monitor.pErrorLogName), "PAGER PORT BACKUP USED: " + s11);
                }
            }
        }
        if (!s7.startsWith("ERROR")) {
            array = null;
        }
        return array;
    }

    public java.lang.String getPagerCommand(java.lang.String s) {
        return getPagerCommand(s, "");
    }

    public java.lang.String getPagerCommand(java.lang.String s, java.lang.String s1) {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        if (getSetting("_pagerSpeed").length() > 0 && !getSetting("_pagerSpeed").equals("1200")) {
            stringbuffer.append("-");
            stringbuffer.append(getSetting("_pagerSpeed"));
            stringbuffer.append(" ");
        }
        java.lang.String s2 = getSetting("_pagerSendOptions");
        if (s2.length() > 0) {
            s2 = s2 + " ";
        }
        stringbuffer.append(s2);
        if (s1.length() == 0) {
            s1 = getSetting("_pagerPort");
        }
        if (s1.startsWith("http")) {
            s1 = "";
        }
        stringbuffer.append(s1 + " " + getPagerDial(s));
        return stringbuffer.toString();
    }

    public java.lang.String getPagerDial(java.lang.String s) {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.lang.String s1 = getSetting("_pagerType");
        java.lang.String s2 = "\"";
        if (com.dragonflow.SiteView.Platform.isUnix()) {
            s2 = "";
        }
        stringbuffer.append(s2);
        if (s1.equalsIgnoreCase("alpha")) {
            stringbuffer.append("ATDT");
            stringbuffer.append(getSetting("_pagerAlphaPhone"));
        } else if (s1.equalsIgnoreCase("direct")) {
            stringbuffer.append("ATDT");
            stringbuffer.append(getSetting("_pagerDirectPhone"));
            stringbuffer.append(",,,");
            stringbuffer.append(s);
            stringbuffer.append('#');
        } else if (s1.equalsIgnoreCase("option")) {
            stringbuffer.append("ATDT");
            stringbuffer.append(getSetting("_pagerOptionPhone"));
            stringbuffer.append(",,");
            stringbuffer.append(getSetting("_pagerOption"));
            stringbuffer.append(",,,");
            stringbuffer.append(s);
            stringbuffer.append('#');
        } else if (s1.equalsIgnoreCase("custom")) {
            java.lang.String s3 = getSetting("_pagerCustom");
            java.lang.String s4 = "$message";
            int j = s3.indexOf(s4);
            if (j >= 0) {
                stringbuffer.append(s3.substring(0, j));
                stringbuffer.append(s);
                stringbuffer.append(s3.substring(j + s4.length()));
            } else {
                stringbuffer.append(s3);
            }
        }
        int i = getSettingAsLong("_pagerTimeout", 30);
        if (s1.equalsIgnoreCase("alpha")) {
            stringbuffer.append(s2 + " " + i);
            stringbuffer.append(" " + s2 + getSetting("_pagerAlphaPIN") + s2);
            stringbuffer.append(" " + s2 + s + s2);
        } else {
            stringbuffer.append(";" + s2 + " " + i);
        }
        return stringbuffer.toString();
    }

    public java.lang.String toString() {
        return "pager action";
    }

    static {
        pMessage = new StringProperty("_message", "", "");
        pMessage.setDisplayText("Message", "optional prefix to pager message, numeric pagers are limited to 32 digits maximum");
        pMessage.setParameterOptions(true, 1, false);
        pTemplate = new ScalarProperty("_template", "Default");
        pTemplate.setDisplayText("Template", "the template used to create the pager message.");
        pTemplate.setParameterOptions(true, 2, false);
        pPager = new ScalarProperty("_pager", "");
        pPager.setDisplayText("To", "pagers to send this alert to - you can send it to multiple pagers by selecting multiple items.");
        pPager.setParameterOptions(true, 3, false);
        ((com.dragonflow.Properties.ScalarProperty) pPager).multiple = true;
        pPagerType = new ScalarProperty("_pagerType", "");
        pPagerType.setDisplayText("Pager Type", "");
        pPagerType.setParameterOptions(true, 4, true);
        pPagerType.isOptional = true;
        pAlphaPhone = new StringProperty("_pagerAlphaPhone", "");
        pAlphaPhone.setDisplayText("Pager Phone", "The phone number that the modem will dial to send the page.");
        pAlphaPhone.setParameterOptions(true, 5, true);
        pAlphaPhone.isOptional = true;
        pAlphaPIN = new StringProperty("_pagerAlphaPIN", "");
        pAlphaPIN.setDisplayText("PIN or Command", "The PIN number or the command (if required) - leave this field blank if the modem number is a direct number.");
        pAlphaPIN.setParameterOptions(true, 6, true);
        pAlphaPIN.isOptional = true;
        pDirectPhone = new StringProperty("_pagerDirectPhone", "");
        pDirectPhone.setDisplayText("Direct Numeric Pager Phone", "");
        pDirectPhone.setParameterOptions(false, 7, true);
        pDirectPhone.isOptional = true;
        pOptionPhone = new StringProperty("_pagerOptionPhone", "");
        pOptionPhone.setDisplayText("Numeric Pager Phone", "");
        pOptionPhone.setParameterOptions(false, 8, true);
        pOptionPhone.isOptional = true;
        pOption = new StringProperty("_pagerOption", "");
        pOption.setDisplayText("Numeric PIN or Command", "");
        pOption.setParameterOptions(false, 9, true);
        pOption.isOptional = true;
        pCustom = new StringProperty("_pagerCustom", "");
        pCustom
                .setDisplayText(
                        "Custom Modem Command",
                        "optional - use this only if your paging company uses special commands.\nThe modem command should contain the phone number to dial, any additional digits, followed by $message.  SiteView\nreplaces $message with the message specified for each Alert.\nwhere the message should be inserted.  The comma character creates a short pause.<p>\nFor example, if the pager company's number is 123-4567, your pager PIN is 333-3333, and each command must be followed by the # key, the command\nmight look like \"ATDT 123-4567,,333-3333#,,$message#\"\n");
        pCustom.setParameterOptions(true, 10, true);
        pCustom.isOptional = true;
        com.dragonflow.Properties.StringProperty astringproperty[] = { pMessage, pTemplate, pPager, pPagerType, pAlphaPhone, pAlphaPIN, pDirectPhone, pOptionPhone, pOption, pCustom };
        com.dragonflow.StandardAction.Page.addProperties("com.dragonflow.StandardAction.Page", astringproperty);
        com.dragonflow.StandardAction.Page.setClassProperty("com.dragonflow.StandardAction.Page", "description", "Sends an alert message via a alphanumeric or numeric pager.");
        com.dragonflow.StandardAction.Page.setClassProperty("com.dragonflow.StandardAction.Page", "help", "AlertPage.htm");
        com.dragonflow.StandardAction.Page.setClassProperty("com.dragonflow.StandardAction.Page", "title", "Send Page");
        com.dragonflow.StandardAction.Page.setClassProperty("com.dragonflow.StandardAction.Page", "name", "Pager");
        com.dragonflow.StandardAction.Page.setClassProperty("com.dragonflow.StandardAction.Page", "class", "Page");
        com.dragonflow.StandardAction.Page.setClassProperty("com.dragonflow.StandardAction.Page", "label", "Send Pager Message");
        com.dragonflow.StandardAction.Page.setClassProperty("com.dragonflow.StandardAction.Page", "prefs", "pagerPrefs");
        com.dragonflow.StandardAction.Page.setClassProperty("com.dragonflow.StandardAction.Page", "accountPrefs", "pagerPrefs");
        com.dragonflow.StandardAction.Page.setClassProperty("com.dragonflow.StandardAction.Page", "loadable", "true");
    }
}
