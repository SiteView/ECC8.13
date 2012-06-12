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

import jgl.HashMap;
import com.dragonflow.Properties.ScalarProperty;
import com.dragonflow.Properties.StringProperty;

public class Disable extends com.dragonflow.SiteView.Action {

    static com.dragonflow.Properties.StringProperty pAction;

    static com.dragonflow.Properties.StringProperty pTarget;

    static com.dragonflow.Properties.StringProperty pTargetMatch;

    public void initializeFromArguments(jgl.Array array, jgl.HashMap hashmap) {
        if (array.size() > 0) {
            setProperty(pAction, array.at(0));
        }
        if (array.size() > 1) {
            for (int i = 1; i < array.size(); i ++) {
                addProperty(pTarget, (java.lang.String) array.at(i));
            }

        }
        setProperty(pTargetMatch, com.dragonflow.Utils.TextUtils.getValue(hashmap, "_targetMatch").replace('_', ' '));
    }

    public java.lang.String getActionString() {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append("disable");
        stringbuffer.append(" ");
        stringbuffer.append(getProperty(pAction));
        if (getProperty(pTargetMatch).length() > 0) {
            stringbuffer.append(" _targetMatch=");
            stringbuffer.append(getProperty(pTargetMatch).replace(' ', '_'));
        }
        java.lang.String s;
        for (java.util.Enumeration enumeration = getMultipleValues(pTarget); enumeration.hasMoreElements(); stringbuffer.append(s)) {
            s = (java.lang.String) enumeration.nextElement();
            stringbuffer.append(" ");
        }

        return stringbuffer.toString();
    }

    public java.lang.String getActionDescription() {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        if (getProperty(pAction).startsWith("enable")) {
            stringbuffer.append("Enable ");
        } else {
            stringbuffer.append("Disable ");
        }
        if (getProperty(pTargetMatch).length() > 0) {
            stringbuffer.append(" names matching \"");
            stringbuffer.append(getProperty(pTargetMatch));
            stringbuffer.append("\" in ");
        }
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        java.util.Enumeration enumeration = getMultipleValues(pTarget);
        for (java.lang.String s = ""; enumeration.hasMoreElements(); s = ", ") {
            java.lang.String s1 = (java.lang.String) enumeration.nextElement();
            if (s1.equals("_groupWithMonitorName_")) {
                stringbuffer.append("group with file name matching the triggering monitor's name");
                continue;
            }
            if (s1.equals("_groupContainingMonitor_")) {
                stringbuffer.append("the group containing the triggering monitor");
                continue;
            }
            com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor) siteviewgroup.getElement(s1);
            if (monitor == null) {
                continue;
            }
            stringbuffer.append(s);
            stringbuffer.append(monitor.getProperty(com.dragonflow.SiteView.Monitor.pName));
            if (s1.indexOf("/") == -1) {
                stringbuffer.append(" Group");
            }
        }

        return stringbuffer.toString();
    }

    public java.lang.String verify(com.dragonflow.Properties.StringProperty stringproperty, java.lang.String s, com.dragonflow.HTTP.HTTPRequest httprequest, jgl.HashMap hashmap) {
        if (stringproperty == pTargetMatch) {
            java.lang.String s1 = com.dragonflow.Utils.TextUtils.legalMatchString(s);
            if (s1.length() > 0) {
                hashmap.put(stringproperty, s1);
            }
            return s;
        } else {
            return super.verify(stringproperty, s, httprequest, hashmap);
        }
    }

    public java.util.Vector getScalarValues(com.dragonflow.Properties.ScalarProperty scalarproperty, com.dragonflow.HTTP.HTTPRequest httprequest, com.dragonflow.Page.CGI cgi) throws com.dragonflow.SiteViewException.SiteViewException {
        if (scalarproperty == pAction) {
            java.util.Vector vector = new Vector();
            vector.addElement("disable");
            vector.addElement("Disable");
            vector.addElement("enable");
            vector.addElement("Enable");
            return vector;
        }
        if (scalarproperty == pTarget) {
            java.util.Vector vector1 = new Vector();
            java.util.Vector vector2 = new Vector();
            jgl.Array array = com.dragonflow.Page.CGI.getAllowedGroupIDsForAccount(httprequest);
            java.util.Enumeration enumeration = array.elements();
            while (enumeration.hasMoreElements()) {
                java.lang.String s = (java.lang.String) enumeration.nextElement();
                jgl.Array array1 = null;
                try {
                    array1 = com.dragonflow.Page.CGI.ReadGroupFrames(s, null);
                } catch (java.io.IOException ioexception) {
                    continue;
                }
                java.util.Enumeration enumeration2 = com.dragonflow.Page.CGI.getMonitors(array1);
                jgl.HashMap hashmap = (jgl.HashMap) enumeration2.nextElement();
                java.lang.String s1 = com.dragonflow.Page.CGI.getGroupName(hashmap, s);
                vector1.addElement(s);
                vector1.addElement(s1);
                while (enumeration2.hasMoreElements()) {
                    jgl.HashMap hashmap1 = (jgl.HashMap) enumeration2.nextElement();
                    java.lang.String s2 = s + "/" + hashmap1.get("_id");
                    vector2.addElement(s2);
                    vector2.addElement(s1 + ": " + com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_name"));
                }
            } 
            for (java.util.Enumeration enumeration1 = vector2.elements(); enumeration1.hasMoreElements(); vector1.addElement(enumeration1.nextElement())) {
            }
            vector1.addElement("_groupWithMonitorName_");
            vector1.addElement("group with file name matching the triggering monitor's name");
            vector1.addElement("_groupContainingMonitor_");
            vector1.addElement("the group containing the triggering monitor");
            return vector1;
        } else {
            return super.getScalarValues(scalarproperty, httprequest, cgi);
        }
    }

    public Disable() {
        runType = 2;
    }

    /**
     * CAUTION: Decompiled by hand.
     */
    public boolean execute() {
        java.lang.String s = "true";
        java.lang.String s1 = "Disabled ";
        if (args.length > 0 && args[0].startsWith("enable")) {
            s = "";
            java.lang.String s2 = "Enabled ";
        }
        java.lang.String s3 = getProperty("_targetMatch").replace('_', ' ');
        jgl.HashMap hashmap = new HashMap();
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.lang.StringBuffer stringbuffer1 = new StringBuffer();
        for (int i = 1; i < args.length; i ++) {
            java.lang.String s4 = args[i];
            java.lang.String s7 = s4;
            java.lang.String s8 = "";
            if (s4.equals("_groupWithMonitorName_")) {
                s7 = com.dragonflow.Utils.I18N.toDefaultEncoding(monitor.getProperty(com.dragonflow.SiteView.Monitor.pName));
            } else if (s4.equals("_groupContainingMonitor_")) {
                s7 = com.dragonflow.Utils.I18N.toDefaultEncoding(monitor.getProperty(com.dragonflow.SiteView.Monitor.pGroupID));
            } else {
                int j = s4.indexOf("/");
                if (j >= 0) {
                    s7 = com.dragonflow.Utils.I18N.toDefaultEncoding(s4.substring(0, j));
                    s8 = s4.substring(j + 1);
                }
            }
            try {
                jgl.Array array = (jgl.Array) hashmap.get(s7);
                if (array == null) {
                    array = com.dragonflow.Page.CGI.ReadGroupFrames(s7, null);
                }
                if (array != null) {
                    hashmap.put(s7, array);
                    if (array.size() <= 0) {
                        continue;
                    }
                    java.lang.String s11 = com.dragonflow.Page.CGI.getGroupName((jgl.HashMap) array.at(0), s7);
                    java.util.Enumeration enumeration1 = com.dragonflow.Page.CGI.getMonitors(array);
                    if (enumeration1.hasMoreElements()) {
                        enumeration1.nextElement();
                    }
                        jgl.HashMap hashmap1;
                        java.lang.String s13;
                        while (enumeration1.hasMoreElements()) {
                            hashmap1 = (jgl.HashMap) enumeration1.nextElement();
                            s13 = "";
                        if (s8.length() != 0 && !com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_id").equals(s8)) {
                        if (s3.length() > 0) {
                            s13 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, com.dragonflow.SiteView.Monitor.pName.getName());
                            if (!com.dragonflow.Utils.TextUtils.match(s13, s3)) {
                                continue;
                            }
                        }
                        hashmap1.put(com.dragonflow.SiteView.Monitor.pDisabled.getName(), s);
                        com.dragonflow.SiteView.Platform.sleep(1000L);
                        if (s13.length() > 0) {
                            addToBuffer(stringbuffer, s13);
                        } else if (s11.length() > 0) {
                            addToBuffer(stringbuffer, s11);
                        }
                        if (s8.length() != 0) {
                            break;
                        }
                        s11 = "";
                        }
                    } 
                }
                else {
                addToBuffer(stringbuffer1, "could not read group " + s7);
                }
            } catch (java.lang.Exception exception1) {
                addToBuffer(stringbuffer1, "error " + exception1.getMessage());
            }
        }

        java.util.Enumeration enumeration = hashmap.keys();
        java.lang.String s5 = "";
        java.lang.String s6;
        for (; enumeration.hasMoreElements(); com.dragonflow.SiteView.SiteViewGroup.updateStaticPages(s6)) {
            s6 = (java.lang.String) enumeration.nextElement();
            try {
                com.dragonflow.Page.CGI.WriteGroupFrames(s6, (jgl.Array) hashmap.get(s6), null);
            } catch (java.lang.Exception exception) {
                addToBuffer(stringbuffer1, "error writing group file " + s6 + "  " + exception.getMessage());
            }
        }

        com.dragonflow.SiteView.SiteViewGroup.updateStaticPages();
        boolean flag = stringbuffer1.length() == 0;
        java.lang.String s9 = stringbuffer.toString();
        java.lang.String s10 = "Disable";
        if (s.length() == 0) {
            s10 = "Enable";
        }
        java.lang.String s12 = s10 + " alert performed";
        if (!flag) {
            s12 = s10.toUpperCase() + " ALERT NOT PERFORMED";
            s9 = stringbuffer1.toString();
        }
        messageBuffer.append(s12 + ", " + s9);
        logAlert(baseAlertLogEntry(s12, s9, flag));
        return flag;
    }

    void addToBuffer(java.lang.StringBuffer stringbuffer, java.lang.String s) {
        if (stringbuffer.length() > 0) {
            stringbuffer.append(", ");
        }
        stringbuffer.append(s);
    }

    static {
        pAction = new ScalarProperty("_action", "disable");
        pAction.setDisplayText("Action", "disable or enable the target groups and monitors.");
        pAction.setParameterOptions(true, 1, false);
        pTarget = new ScalarProperty("_target", "");
        pTarget.setDisplayText("Target(s)", "the group(s) and/or monitor(s) to enable or disable - to select several items, hold down the Control key (on most platforms) while clicking item names.");
        pTarget.setParameterOptions(true, 2, false);
        ((com.dragonflow.Properties.ScalarProperty) pTarget).multiple = true;
        ((com.dragonflow.Properties.ScalarProperty) pTarget).listSize = 5;
        pTargetMatch = new StringProperty("_targetMatch", "");
        pTargetMatch.setDisplayText("Target Name Match", "optional text to match against the monitor names that will be disabled or enabled.");
        pTargetMatch.setParameterOptions(true, 3, true);
        com.dragonflow.Properties.StringProperty astringproperty[] = { pAction, pTarget };
        com.dragonflow.StandardAction.Disable.addProperties("com.dragonflow.StandardAction.Disable", astringproperty);
        com.dragonflow.StandardAction.Disable.setClassProperty("com.dragonflow.StandardAction.Disable", "description", "Disables or enables a set of groups or monitors.");
        com.dragonflow.StandardAction.Disable.setClassProperty("com.dragonflow.StandardAction.Disable", "help", "AlertDisable.htm");
        com.dragonflow.StandardAction.Disable.setClassProperty("com.dragonflow.StandardAction.Disable", "title", "Disable or Enable Monitor(s)");
        com.dragonflow.StandardAction.Disable.setClassProperty("com.dragonflow.StandardAction.Disable", "label", "Disable or Enable Monitor(s)");
        com.dragonflow.StandardAction.Disable.setClassProperty("com.dragonflow.StandardAction.Disable", "name", "Disable or Enable Monitor(s)");
        com.dragonflow.StandardAction.Disable.setClassProperty("com.dragonflow.StandardAction.Disable", "class", "Disable");
        com.dragonflow.StandardAction.Disable.setClassProperty("com.dragonflow.StandardAction.Disable", "loadable", "true");
        com.dragonflow.StandardAction.Disable.setClassProperty("com.dragonflow.StandardAction.Disable", "classType", "advanced");
    }
}
