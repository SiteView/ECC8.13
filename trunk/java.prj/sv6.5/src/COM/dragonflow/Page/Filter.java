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

import java.util.Enumeration;

import jgl.Array;
import jgl.HashMap;
import COM.dragonflow.HTTP.HTTPRequest;
import COM.dragonflow.SiteView.AtomicMonitor;
import COM.dragonflow.SiteView.Monitor;
import COM.dragonflow.SiteView.MonitorGroup;
import COM.dragonflow.SiteView.SiteViewGroup;
import COM.dragonflow.Utils.TextUtils;

// Referenced classes of package COM.dragonflow.Page:
// monitorPage

public class Filter {

    private HTTPRequest request;

    private static jgl.Array monitorClasses = null;

    public Filter(COM.dragonflow.HTTP.HTTPRequest httprequest) {
        request = httprequest;
    }

    public void burnCache() {
        monitorClasses = null;
    }

    public String createHeader() {
        return printBrowseFilterOptionForm();
    }

    public boolean isFiltered(COM.dragonflow.SiteView.Monitor monitor,
            java.lang.String s) {
        return false;
    }

    private jgl.Array _getUsedMonitorClasses() {
        jgl.Array array = new Array();
        SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup
                .currentSiteView();
        Enumeration enumeration = siteviewgroup.getGroupIDs().elements();
        jgl.HashMap hashmap = new HashMap();
        while (enumeration.hasMoreElements()) {
            MonitorGroup monitorgroup = COM.dragonflow.SiteView.SiteViewGroup
                    .currentSiteView().getGroup(
                            COM.dragonflow.Utils.I18N
                                    .toDefaultEncoding(enumeration
                                            .nextElement().toString()));
            Enumeration enumeration1 = monitorgroup.getMonitors();
            while (enumeration1.hasMoreElements()) {
                Monitor monitor = (COM.dragonflow.SiteView.Monitor) enumeration1
                        .nextElement();
                java.lang.String s = monitor.getClass().getName();
                s = s.substring(s.lastIndexOf(".") + 1);
                hashmap.put(s, "");
            }
        }
        array = TextUtils.enumToArray(hashmap.keys());
        return array;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @return
     */
    private String printBrowseFilterOptionForm() {
        StringBuffer stringbuffer;
        Enumeration enumeration;
        String s = "";
        String s1 = "";
        stringbuffer = new StringBuffer();
        stringbuffer.append("<p><b>View Filter:</b></p>");
        stringbuffer
                .append("<FORM METHOD=GET ACTION=/SiteView/cgi/go.exe/SiteView><INPUT TYPE=HIDDEN NAME=page VALUE=manage><INPUT TYPE=HIDDEN NAME=account VALUE="
                        + request.getAccount() + ">");
        stringbuffer
                .append("<table border=\"0\" width=\"98%\" cellpadding=\"3\" cellspacing=\"0\"><tr><td align=\"right\" valign=\"top\">Match Name:</td><td align=\"left\"valign=\"top\"><input type=text name=monitorNameSelect size=15 value=\""
                        + s + "\"></td>");
        stringbuffer
                .append("<td align=\"right\" valign=\"top\">Match Machine:</td><td align=\"left\"valign=\"top\"><input type=text name=machineNameSelect size=15 value=\""
                        + s1 + "\"></td>");
        stringbuffer
                .append("<td align=\"right\" valign=\"top\">For Monitor Type: </td><td align=\"left\"valign=\"top\"><SELECT NAME=monitorTypeSelect><option value=\"\">All types</option>\n");
        jgl.Array array = COM.dragonflow.Page.monitorPage.getMonitorClasses();
        enumeration = array.elements();
        if (monitorClasses == null) {
            monitorClasses = _getUsedMonitorClasses();
        }

        while (enumeration.hasMoreElements()) {
            Class class1 = (Class) enumeration.nextElement();
            AtomicMonitor atomicmonitor;
            try {
                atomicmonitor = (AtomicMonitor) class1.newInstance();
                String s3 = request.getPermission("_monitorType",
                        (java.lang.String) atomicmonitor
                                .getClassProperty("class"));
                if (s3.length() == 0) {
                    s3 = request.getPermission("_monitorType", "default");
                }
                if (!s3.equals("hidden")) {
                    String s4 = (String) atomicmonitor
                            .getClassProperty("title");
                    String s5 = (String) atomicmonitor
                            .getClassProperty("class");
                    if (monitorClasses.indexOf(s5) != -1) {
                        java.lang.String s2 = "";
                        stringbuffer.append("<option value=" + s5 + s2 + ">"
                                + s4 + "</option>\n");
                    }
                }
            } catch (Exception exception) {
                System.out.println("Could not create instance of " + class1);
            }
        }

        stringbuffer.append("</select></td>\n");
        stringbuffer
                .append("<td align=\"left\"valign=\"top\"><input type=submit name=operation VALUE=\"Apply Filter\"></td></tr></table></FORM>");
        return stringbuffer.toString();
    }

}
