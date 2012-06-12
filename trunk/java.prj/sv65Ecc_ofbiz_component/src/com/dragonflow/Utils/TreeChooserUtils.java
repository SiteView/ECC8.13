/*
 * Created on 2005-2-9 3:06:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Utils;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */
import jgl.Array;
import jgl.HashMap;
import jgl.LessString;
import com.dragonflow.Properties.HashMapOrdered;

// Referenced classes of package com.dragonflow.Utils:
// TextUtils, I18N

public class TreeChooserUtils {

    private com.dragonflow.HTTP.HTTPRequest request;

    private java.io.PrintWriter outputStream;

    private jgl.HashMap groupHashMap;

    private jgl.Array conditions;

    com.dragonflow.SiteView.SiteViewObject siteview;

    public TreeChooserUtils(com.dragonflow.HTTP.HTTPRequest httprequest, java.io.PrintWriter printwriter, jgl.Array array) {
        request = null;
        outputStream = null;
        groupHashMap = null;
        conditions = null;
        siteview = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        request = httprequest;
        outputStream = printwriter;
        conditions = array;
    }

    public TreeChooserUtils(com.dragonflow.HTTP.HTTPRequest httprequest, java.io.PrintWriter printwriter, jgl.HashMap hashmap) {
        request = null;
        outputStream = null;
        groupHashMap = null;
        conditions = null;
        siteview = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        request = httprequest;
        outputStream = printwriter;
        groupHashMap = hashmap;
    }

    public void createTree() {
        String s = request.getValue("page");
        String s1 = request.getValue("view");
        jgl.Array array = new Array();
        jgl.HashMap hashmap = new HashMap();
        String s2 = prepareTree(s, s1, array, hashmap);
        jgl.HashMap hashmap1 = new HashMap();
        String s3;
        for (java.util.Enumeration enumeration = request.getValues("monitorID"); enumeration.hasMoreElements(); hashmap1.put(s3, "checked")) {
            s3 = (String) enumeration.nextElement();
        }

        String s4;
        for (java.util.Enumeration enumeration1 = request.getValues("groupID"); enumeration1.hasMoreElements(); hashmap1.put(s4, "checked")) {
            s4 = (String) enumeration1.nextElement();
        }

        if (s.equals("alert")) {
            if (s1.equals("Group")) {
                outputStream
                        .println("Select one or more groups and monitors and then click the <input type=\"button\" value=\"Add\"> button below. The Alert Utilities do not apply to the selected groups and monitors, but perform general functions.  Click the <img src=/SiteView/htdocs/artwork/Plus.gif alt=\"open\"> to expand a group and the <img src=/SiteView/htdocs/artwork/Minus.gif alt=\"close\"> to collapse a group.<br><br>");
                outputStream.println("<table>");
                processGroupView(hashmap, hashmap1);
            } else if (s1.equals("Alert")) {
                outputStream
                        .println("Select one or more alerts and then click the <input type=\"button\" value=\"Disable\"> or the<input type=\"button\" value=\"Enable\"> buttons below.  The Alert Utilities do not apply to the selected alerts, but perform general functions.  Click the <img src=/SiteView/htdocs/artwork/Plus.gif alt=\"open\"> to expand an alert and the <img src=/SiteView/htdocs/artwork/Minus.gif alt=\"close\"> to collapse a alert.<br><br>");
                outputStream.println("<table border=\"2\" cellspacing=\"0\" width=\"100%\">");
                outputStream.println("<tr class=\"tabhead\"><th>On</th><th>Group</th><th>For</th><th>Do</th><th>History</th><th>Edit</th><th>Test</th><th>Delete</th></tr>");
                processAlertView(hashmap, hashmap1);
            }
        } else if (s.equals("report")) {
            if (s1.equals("Group")) {
                outputStream.println("<br>To view management reports and summaries, click the link in the <b>Report</b> field of each description.");
                outputStream
                        .println("<br>Select one or more groups and monitors and then click the <input type=\"button\" value=\"Add\"> or the<input type=\"button\" value=\"Quick\"> buttons below. The Report Utilities do not apply to the selected groups and monitors, but perform general functions.  Click the <img src=/SiteView/htdocs/artwork/Plus.gif alt=\"open\"> to expand a group and the <img src=/SiteView/htdocs/artwork/Minus.gif alt=\"close\"> to collapse a group.<br><br>");
                outputStream.println("<table>");
                processGroupView(hashmap, hashmap1);
            } else if (s1.equals("Report")) {
                outputStream.println("<br>To view management reports and summaries, click the link in the <b>Report</b> field of each description.");
                outputStream.println("Click the <img src=/SiteView/htdocs/artwork/Plus.gif alt=\"open\"> to expand an report and the <img src=/SiteView/htdocs/artwork/Minus.gif alt=\"close\"> to collapse a report.<br><br>");
                outputStream.println("<table border=\"1\" cellspacing=\"0\" width=\"100%\">");
                outputStream.println("<tr class=\"tabhead\"><th width=\"50%\">Reports</th><th>Time Period</th><th>Edit</th><th>Delete</th></tr>");
                processReportView(hashmap, hashmap1);
            }
        }
        outputStream.println("</table>");
        try {
            com.dragonflow.Properties.FrameFile.writeToFile(s2, array);
        } catch (Exception ioexception) {
        }
    }

    private String prepareTree(String s, String s1, jgl.Array array, jgl.HashMap hashmap) {
        String s2;
        if (com.dragonflow.SiteView.Platform.isStandardAccount(request.getAccount())) {
            s2 = com.dragonflow.SiteView.Platform.getDirectoryPath("groups", request.getAccount());
        } else {
            s2 = com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "accounts" + java.io.File.separator + request.getAccount();
        }
        String s3 = s2 + java.io.File.separator + s + s1 + "Tree.dyn";
        try {
            jgl.Array array1 = com.dragonflow.Properties.FrameFile.readFromFile(s3);
            for (int i = 0; i < array1.size(); i ++) {
                array.add(array1.at(i));
            }

        } catch (Exception exception) {
        }
        updateCurrentStateFrames(array, hashmap);
        return s3;
    }

    private void updateCurrentStateFrames(jgl.Array array, jgl.HashMap hashmap) {
        String s = request.getAccount();
        jgl.HashMap hashmap1 = new HashMap();
        for (int i = 0; i < array.size(); i ++) {
            jgl.HashMap hashmap2 = (jgl.HashMap) array.at(i);
            if (com.dragonflow.Utils.TextUtils.getValue(hashmap2, "_user").equals(s)) {
                hashmap1 = hashmap2;
            }
        }

        if (hashmap1.isEmpty()) {
            array.add(hashmap1);
            hashmap1.put("_user", s);
        }
        java.util.Enumeration enumeration = request.getVariables();
        while (enumeration.hasMoreElements()) {
            String s1 = com.dragonflow.HTTP.HTTPRequest.decodeString((String) enumeration.nextElement(), com.dragonflow.Utils.I18N.nullEncoding());
            if (s1.startsWith(com.dragonflow.Page.managePage.OPEN_VARIABLE)) {
                String s2 = s1.substring(com.dragonflow.Page.managePage.OPEN_VARIABLE.length(), s1.length() - 2);
                if (!com.dragonflow.Utils.TextUtils.getValue(hashmap1, s2).equals("open")) {
                    hashmap1.put(s2, "open");
                }
            }
            if (s1.startsWith(com.dragonflow.Page.managePage.CLOSE_VARIABLE)) {
                String s3 = s1.substring(com.dragonflow.Page.managePage.CLOSE_VARIABLE.length(), s1.length() - 2);
                if (!com.dragonflow.Utils.TextUtils.getValue(hashmap1, s3).equals("close")) {
                    hashmap1.remove(s3);
                }
            }
        } 
        String s4;
        for (java.util.Enumeration enumeration1 = hashmap1.keys(); enumeration1.hasMoreElements(); hashmap.put(s4, hashmap1.get(s4))) {
            s4 = (String) enumeration1.nextElement();
        }

    }

    private void processGroupView(jgl.HashMap hashmap, jgl.HashMap hashmap1) {
        com.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
        jgl.Array array = getGroupNameList(hashmapordered);
        for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements();) {
            String s = (String) enumeration.nextElement();
            java.util.Enumeration enumeration1 = hashmapordered.values(s);
            while (enumeration1.hasMoreElements()) {
                com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup) enumeration1.nextElement();
                String s2 = monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pID);
                String s1 = monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pName);
                printGroupGroupView(s2, s1, hashmap, hashmap1, 0, "Group");
            }
        }

    }

    private void processAlertView(jgl.HashMap hashmap, jgl.HashMap hashmap1) {
        java.util.Enumeration enumeration = conditions.elements();
        while (enumeration.hasMoreElements()) {
            jgl.HashMap hashmap2 = (jgl.HashMap) enumeration.nextElement();
            jgl.Array array = (jgl.Array) hashmap2.get("printable");
            String s = (String) hashmap2.get("fullID");
            boolean flag = hashmap.get(s) != null;
            int i = 0;
            String s1 = getIndentHTML(i);
            outputStream.print("<tr><td><table><tr><td>" + s1 + "</td><td>");
            printOpenClose(flag, s);
            outputStream.print("</td><td><input type=checkbox name=alert value=\"" + s + "\"></td><td>" + array.at(0) + "</td></tr></table></td>");
            for (int j = 1; j < array.size(); j ++) {
                outputStream.print(array.at(j));
            }

            outputStream.println("</tr>");
            if (flag) {
                String s2 = (String) hashmap2.get("group");
                jgl.Array array1 = new Array();
                if (s2.equals("_master")) {
                    String s3 = (String) hashmap2.get("contents");
                    if (s3 != null) {
                        jgl.Array array2 = com.dragonflow.SiteView.Platform.split(',', s3);
                        for (int l = 0; l < array2.size(); l ++) {
                            jgl.Array array3 = com.dragonflow.SiteView.Platform.split(' ', (String) array2.at(l));
                            if (!array1.contains(array3.at(0))) {
                                array1.add(array3.at(0));
                            }
                        }

                    } else {
                        com.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
                        jgl.Array array4 = getGroupNameList(hashmapordered);
                        for (java.util.Enumeration enumeration1 = array4.elements(); enumeration1.hasMoreElements();) {
                            String s5 = (String) enumeration1.nextElement();
                            java.util.Enumeration enumeration2 = hashmapordered.values(s5);
                            while (enumeration2.hasMoreElements()) {
                                com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup) enumeration2.nextElement();
                                array1.add(monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pName));
                            }
                        }

                    }
                } else {
                    array1 = com.dragonflow.SiteView.Platform.split(',', s2);
                }
                outputStream.println("<tr><td colspan=\"8\"><table width=\"100%\">");
                for (int k = 0; k < array1.size(); k ++) {
                    String s4 = (String) array1.at(k);
                    printGroupAlertView(s + "/" + s4, hashmap2, hashmap, hashmap1, i + 4, "Alert");
                }

                outputStream.println("</table></td></tr>");
            }
        } 
    }

    private void processReportView(jgl.HashMap hashmap, jgl.HashMap hashmap1) {
        java.util.Enumeration enumeration = conditions.elements();
        while (enumeration.hasMoreElements()) {
            jgl.HashMap hashmap2 = (jgl.HashMap) enumeration.nextElement();
            jgl.Array array = (jgl.Array) hashmap2.get("printable");
            String s = (String) hashmap2.get("id");
            boolean flag = hashmap.get(s) != null;
            int i = 0;
            String s1 = getIndentHTML(i);
            outputStream.print("<tr><td><table><tr><td>" + s1 + "</td><td>");
            printOpenClose(flag, s);
            outputStream.print("</td><td>" + array.at(0) + "</td></tr></table></td>");
            for (int j = 1; j < array.size(); j ++) {
                outputStream.print(array.at(j));
            }

            outputStream.println("</tr>");
            if (flag) {
                jgl.Array array1 = new Array();
                try {
                    String s2 = (String) hashmap2.get("monitors");
                    jgl.Array array2 = com.dragonflow.SiteView.Platform.split(' ', s2);
                    if (array2.size() == 1) {
                        array1.add(s2);
                    } else {
                        array1.add(array2.at(1));
                    }
                } catch (ClassCastException classcastexception) {
                    jgl.Array array3 = (jgl.Array) hashmap2.get("monitors");
                    java.util.Enumeration enumeration1 = array3.elements();
                    while (enumeration1.hasMoreElements()) {
                        String s4 = (String) enumeration1.nextElement();
                        jgl.Array array4 = com.dragonflow.SiteView.Platform.split(' ', s4);
                        if (array4.size() == 1) {
                            if (!array1.contains(s4)) {
                                array1.add(s4);
                            }
                        } else if (!array1.contains(array4.at(1))) {
                            array1.add(array4.at(1));
                        }
                    }
                }
                outputStream.println("<tr><td colspan=\"8\"><table width=\"100%\">");
                for (int k = 0; k < array1.size(); k ++) {
                    String s3 = (String) array1.at(k);
                    printGroupReportView(s + "/" + s3, hashmap2, hashmap, hashmap1, i + 4, "Report");
                }

                outputStream.println("</table></td></tr>");
            }
        } 
    }

    private jgl.Array getGroupNameList(jgl.HashMap hashmap) {
        boolean flag = true;
        jgl.Array array = null;
        array = com.dragonflow.Page.CGI.getAllowedGroupIDsForAccount(request);
        java.util.Enumeration enumeration = array.elements();
        jgl.Array array1 = new Array();
        String s = "";
        while (enumeration.hasMoreElements()) {
            String s1 = (String) enumeration.nextElement();
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup) siteview.getElement(s1);
            if (monitorgroup != null && (!flag || monitorgroup.getProperty(com.dragonflow.SiteView.MonitorGroup.pParent).length() <= 0)) {
                String s2 = com.dragonflow.Page.CGI.getGroupPath(monitorgroup, com.dragonflow.Page.CGI.getGroupIDFull(s1, siteview), false);
                hashmap.add(s2 + " (" + s1 + ")", monitorgroup);
                if (!s1.equals(s)) {
                    array1.add(s2 + " (" + s1 + ")");
                }
                s = s1;
            }
        } 
        jgl.Sorting.sort(array1, new LessString());
        return array1;
    }

    private void printGroupGroupView(String s, String s1, jgl.HashMap hashmap, jgl.HashMap hashmap1, int i, String s2) {
        String s3 = printGroup(s, s1, hashmap, hashmap1, i, s2);
        boolean flag = hashmap.get(s) != null;
        if (flag) {
            jgl.Array array = (jgl.Array) groupHashMap.get(s);
            if (array != null) {
                outputStream.println("<tr><td><table cellpadding=\"0\">");
                for (int j = 0; j < array.size(); j ++) {
                    printAlertOrReport((jgl.Array) array.at(j), s3);
                }

                outputStream.println("</table></td></tr>");
            }
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup) siteview.getElement(s);
            java.util.Enumeration enumeration = monitorgroup.getMonitors();
            while (enumeration.hasMoreElements()) {
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor) enumeration.nextElement();
                if (monitor instanceof com.dragonflow.SiteView.SubGroup) {
                    String s4 = com.dragonflow.Utils.I18N.toDefaultEncoding(monitor.getProperty(com.dragonflow.SiteView.SubGroup.pGroup));
                    com.dragonflow.SiteView.MonitorGroup monitorgroup1 = (com.dragonflow.SiteView.MonitorGroup) siteview.getElement(s4);
                    String s6 = monitorgroup1.getProperty(com.dragonflow.SiteView.Monitor.pName);
                    if (monitorgroup1 != null) {
                        printGroupGroupView(s4, s6, hashmap, hashmap1, i + 2, s2);
                    }
                } else {
                    printMonitor(monitor, hashmap1, s, s2, s3);
                    String s5 = s + " " + monitor.getProperty(com.dragonflow.SiteView.Monitor.pID);
                    jgl.Array array1 = (jgl.Array) groupHashMap.get(s5);
                    if (array1 != null) {
                        outputStream.println("<tr><td><table cellpadding=\"0\">");
                        for (int k = 0; k < array1.size(); k ++) {
                            printAlertOrReport((jgl.Array) array1.at(k), getIndentHTML(i + 6));
                        }

                        outputStream.println("</table></td></tr>");
                    }
                }
            }
        }
    }

    private void printGroupAlertView(String s, jgl.HashMap hashmap, jgl.HashMap hashmap1, jgl.HashMap hashmap2, int i, String s1) {
        String s2 = s.substring(0, s.lastIndexOf('/'));
        String s3 = s.substring(s.lastIndexOf('/') + 1);
        String s4 = com.dragonflow.Page.CGI.getGroupFullName(com.dragonflow.Utils.I18N.toDefaultEncoding(com.dragonflow.Page.CGI.getGroupIDFull(s3, siteview)));
        printGroup(s, s4, hashmap1, hashmap2, i, s1);
        boolean flag = hashmap1.get(s) != null;
        if (flag) {
            String s5 = (String) hashmap.get("monitor");
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup) siteview.getElement(s3);
            jgl.Array array = new Array();
            if (s5.equals("_config")) {
                String s6 = (String) hashmap.get("contents");
                if (s6 == null || s6.length() == 0) {
                    com.dragonflow.SiteView.Monitor monitor1;
                    for (java.util.Enumeration enumeration = monitorgroup.getMonitors(); enumeration.hasMoreElements(); array.add(monitor1)) {
                        monitor1 = (com.dragonflow.SiteView.Monitor) enumeration.nextElement();
                    }

                } else {
                    jgl.Array array1 = com.dragonflow.SiteView.Platform.split(',', s6);
                    for (int k = 0; k < array1.size(); k ++) {
                        if (((String) array1.at(k)).indexOf(s3) >= 0) {
                            jgl.Array array2 = com.dragonflow.SiteView.Platform.split(' ', (String) array1.at(k));
                            if (array2.size() > 1) {
                                com.dragonflow.SiteView.Monitor monitor3 = (com.dragonflow.SiteView.Monitor) monitorgroup.getElementByID((String) array2.at(1));
                                array.add(monitor3);
                            } else {
                                com.dragonflow.SiteView.Monitor monitor4;
                                for (java.util.Enumeration enumeration1 = monitorgroup.getMonitors(); enumeration1.hasMoreElements(); array.add(monitor4)) {
                                    monitor4 = (com.dragonflow.SiteView.Monitor) enumeration1.nextElement();
                                }

                            }
                        }
                    }

                }
            } else {
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor) monitorgroup.getElementByID(s5);
                array.add(monitor);
            }
            String s7 = getIndentHTML(i + 2);
            for (int j = 0; j < array.size(); j ++) {
                com.dragonflow.SiteView.Monitor monitor2 = (com.dragonflow.SiteView.Monitor) array.at(j);
                if (monitor2 instanceof com.dragonflow.SiteView.SubGroup) {
                    String s8 = com.dragonflow.Utils.I18N.toDefaultEncoding(monitor2.getProperty(com.dragonflow.SiteView.SubGroup.pGroup));
                    com.dragonflow.SiteView.MonitorGroup monitorgroup1 = (com.dragonflow.SiteView.MonitorGroup) siteview.getElement(s8);
                    if (monitorgroup1 != null) {
                        hashmap.remove("contents");
                        printGroupAlertView(s2 + "/" + s8, hashmap, hashmap1, hashmap2, i + 2, s1);
                    }
                } else {
                    printMonitor(monitor2, hashmap2, s3, s1, s7);
                }
            }

        }
    }

    private void printGroupReportView(String s, jgl.HashMap hashmap, jgl.HashMap hashmap1, jgl.HashMap hashmap2, int i, String s1) {
        String s2 = s.substring(0, s.lastIndexOf('/'));
        String s3 = s.substring(s.lastIndexOf('/') + 1);
        String s4 = com.dragonflow.Page.CGI.getGroupFullName(com.dragonflow.Utils.I18N.toDefaultEncoding(com.dragonflow.Page.CGI.getGroupIDFull(s3, siteview)));
        printGroup(s, s4, hashmap1, hashmap2, i, s1);
        boolean flag = hashmap1.get(s) != null;
        if (flag) {
            jgl.Array array = new Array();
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup) siteview.getElementByID(s3);
            try {
                String s5 = (String) hashmap.get("monitors");
                getReportMonitors(s5, monitorgroup, array);
            } catch (ClassCastException classcastexception) {
                jgl.Array array1 = (jgl.Array) hashmap.get("monitors");
                String s7;
                for (java.util.Enumeration enumeration = array1.elements(); enumeration.hasMoreElements(); getReportMonitors(s7, monitorgroup, array)) {
                    s7 = (String) enumeration.nextElement();
                }

            }
            String s6 = getIndentHTML(i + 2);
            for (int j = 0; j < array.size(); j ++) {
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor) array.at(j);
                if (monitor instanceof com.dragonflow.SiteView.SubGroup) {
                    String s8 = com.dragonflow.Utils.I18N.toDefaultEncoding(monitor.getProperty(com.dragonflow.SiteView.SubGroup.pGroup));
                    com.dragonflow.SiteView.MonitorGroup monitorgroup1 = (com.dragonflow.SiteView.MonitorGroup) siteview.getElement(s8);
                    if (monitorgroup1 != null) {
                        hashmap.remove("monitors");
                        printGroupReportView(s2 + "/" + s8, hashmap, hashmap1, hashmap2, i + 2, s1);
                    }
                } else {
                    printMonitor(monitor, hashmap2, s3, s1, s6);
                }
            }

        }
    }

    private void getReportMonitors(String s, com.dragonflow.SiteView.MonitorGroup monitorgroup, jgl.Array array) {
        if (s != null) {
            jgl.Array array1 = com.dragonflow.SiteView.Platform.split(' ', s);
            if (array1.size() == 1) {
                if (s.equals(monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pID))) {
                    com.dragonflow.SiteView.Monitor monitor2;
                    for (java.util.Enumeration enumeration1 = monitorgroup.getMonitors(); enumeration1.hasMoreElements(); array.add(monitor2)) {
                        monitor2 = (com.dragonflow.SiteView.Monitor) enumeration1.nextElement();
                    }

                }
            } else if (array1.at(1).equals(monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pID))) {
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor) monitorgroup.getElementByID((String) array1.at(0));
                array.add(monitor);
            }
        } else {
            com.dragonflow.SiteView.Monitor monitor1;
            for (java.util.Enumeration enumeration = monitorgroup.getMonitors(); enumeration.hasMoreElements(); array.add(monitor1)) {
                monitor1 = (com.dragonflow.SiteView.Monitor) enumeration.nextElement();
            }

        }
    }

    private String getIndentHTML(int i) {
        int j = i * 11;
        if (j == 0) {
            j = 1;
        }
        return "<img src=/SiteView/htdocs/artwork/empty1111.gif height=11 width=" + j + " border=0>";
    }

    private void printOpenClose(boolean flag, String s) {
        if (flag) {
            outputStream.print("<input type=image name=close" + s + " src=/SiteView/htdocs/artwork/Minus.gif alt=\"close\" border=0>");
        } else {
            outputStream.print("<input type=image name=open" + s + " src=/SiteView/htdocs/artwork/Plus.gif alt=\"open\" border=0>");
        }
    }

    private String printGroup(String s, String s1, jgl.HashMap hashmap, jgl.HashMap hashmap1, int i, String s2) {
        boolean flag = hashmap.get(s) != null;
        String s3 = getIndentHTML(i);
        String s4 = com.dragonflow.SiteView.Platform.getURLPath("htdocs", request.getAccount()) + "/Detail";
        outputStream.print("<TR><TD>");
        outputStream.print(s3);
        printOpenClose(flag, s);
        if (s2.equals("Group")) {
            outputStream.print("<input type=checkbox name=groupID value=\"" + s + "\" " + com.dragonflow.Utils.TextUtils.getValue(hashmap1, s) + ">");
            outputStream.print("<B><A HREF=" + s4 + com.dragonflow.HTTP.HTTPRequest.encodeString(com.dragonflow.Utils.I18N.toDefaultEncoding(s)) + ".html>" + s1);
        } else {
            String s5 = s.substring(s.lastIndexOf('/') + 1);
            outputStream.print("<B><A HREF=" + s4 + com.dragonflow.HTTP.HTTPRequest.encodeString(com.dragonflow.Utils.I18N.toDefaultEncoding(s5)) + ".html>" + s1);
        }
        outputStream.println("</A></B></TD></TR>");
        s3 = getIndentHTML(i + 3);
        return s3;
    }

    private void printMonitor(com.dragonflow.SiteView.Monitor monitor, jgl.HashMap hashmap, String s, String s1, String s2) {
        outputStream.print("<TR><TD>");
        outputStream.print(s2);
        String s3 = s + " " + monitor.getProperty(com.dragonflow.SiteView.Monitor.pID);
        if (s1.equals("Group")) {
            outputStream.print("<input type=checkbox name=monitorID value=\"" + s3 + "\" " + com.dragonflow.Utils.TextUtils.getValue(hashmap, s3) + ">");
        }
        outputStream.print(monitor.getProperty(com.dragonflow.SiteView.Monitor.pName));
        if (monitor.getProperty(com.dragonflow.SiteView.Monitor.pDisabled).length() > 0) {
            outputStream.println(" <B>(disabled)</B>");
        }
//		else if (com.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazServerSettings().isConnected() && monitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pNotLogToTopaz).length() > 0) {
//            outputStream.println(" <B>(logging to " + com.dragonflow.SiteView.TopazInfo.getTopazName() + " disabled)</B>");
//        }
        outputStream.println("</TD></TR>");
    }

    private void printAlertOrReport(jgl.Array array, String s) {
        outputStream.println("<tr>");
        outputStream.println("<td>" + s + "</td>");
        for (int i = 0; i < array.size(); i ++) {
            outputStream.println((String) array.at(i));
            outputStream.println("<td>&nbsp;&nbsp;</td>");
        }

        outputStream.println("</tr>");
    }
}
