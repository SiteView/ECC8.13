/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Api;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.io.File;
import java.io.PrintWriter;
import java.util.Date;
import java.util.Vector;

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Properties.HashMapOrdered;
import com.dragonflow.SiteView.HistoryReport;
import com.dragonflow.SiteViewException.SiteViewOperationalException;
import com.dragonflow.SiteViewException.SiteViewParameterException;

// Referenced classes of package com.dragonflow.Api:
// APISiteView

public class APIReport extends com.dragonflow.Api.APISiteView {

    public static final java.lang.String TYPE_REPORTQUICK = "ReportQuick";

    public static final java.lang.String TYPE_REPORTMANAGEMENT = "ReportManagement";

    public static final java.lang.String SITEVIEW_ROOT = "_SiteViewRoot_";

    public static final java.lang.String IS_QUICK = "isQuick";

    static final int MINUTE_SECONDS = 60;

    static final int HOUR_SECONDS = 3600;

    static final int DAY_SECONDS = 0x15180;

    static final int WEEK_SECONDS = 0x93a80;

    static final int MONTH_SECONDS = 0x278d00;

    public static final java.lang.String SSPARAM_TO = "_to";

    public static final java.lang.String SSPARAM_MACHINE = "_machine";

    static final java.lang.String encoding = com.dragonflow.Utils.I18N.nullEncoding();

    static jgl.Array conditions = null;

    static final boolean $assertionsDisabled; /* synthetic field */

    public APIReport() {
    }

    public java.lang.String create(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap) throws com.dragonflow.SiteViewException.SiteViewException {
        return create(s, s1, hashmap, null, null);
    }

    public java.lang.String create(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap, com.dragonflow.HTTP.HTTPRequest httprequest, java.io.PrintWriter printwriter) throws com.dragonflow.SiteViewException.SiteViewException {
        if (httprequest == null) {
            httprequest = new HTTPRequest();
            httprequest.setUser(account);
            java.lang.String s2;
            for (java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements(); httprequest.setValue(s2, com.dragonflow.Utils.TextUtils.getValue(hashmap, s2))) {
                s2 = (java.lang.String) enumeration.nextElement();
            }

            java.lang.String s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "monitors");
            if (s3.length() != 0) {
                java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s3, ",");
                if (as.length > 1) {
                    jgl.Array array = new Array();
                    for (int i = 0; i < as.length; i ++) {
                        array.add(as[i]);
                    }

                    httprequest.setValues("monitors", array.elements());
                }
                hashmap.put("monitors", as);
            }
            if (!s.equals("ReportQuick")) {
                httprequest.setValue("startDay", "today");
            } else {
                httprequest.setValue("isadhoc", "true");
            }
            httprequest.setValue("isFlipper", "true");
            java.lang.String s5 = (java.lang.String) hashmap.get("showAlerts");
            java.lang.String s8 = (java.lang.String) hashmap.get("alertDetailLevel");
            if ((s5 == null || s5.length() == 0) && s8 != null && !s8.equals("none")) {
                httprequest.setValue("showAlerts", "checked");
            }
            java.lang.String s11 = (java.lang.String) hashmap.get("tabfile");
            java.lang.String s13 = (java.lang.String) hashmap.get("emailData");
            if ((s11 == null || s11.length() == 0) && s13 != null && s13.length() > 0) {
                httprequest.setValue("tabfile", "checked");
            }
            java.lang.String s14 = (java.lang.String) hashmap.get("xmlfile");
            java.lang.String s15 = (java.lang.String) hashmap.get("xmlEmailData");
            if ((s14 == null || s14.length() == 0) && s15 != null && s15.length() > 0) {
                httprequest.setValue("xmlfile", "checked");
            }
            java.lang.String s16 = (java.lang.String) hashmap.get("reportType");
            if (s16 != null && !s16.equals("none")) {
                httprequest.setValue("showGraphs", "checked");
            } else {
                httprequest.setValue("reportType", "barGraph");
            }
            if (s1 != null) {
                s1 = s1.trim();
                if (s1.length() > 0) {
                    java.lang.String as1[] = com.dragonflow.Utils.TextUtils.split(s1, ",");
                    if (as1.length > 1) {
                        jgl.Array array2 = new Array();
                        for (int k = 0; k < as1.length; k ++) {
                            array2.add(invert(as1[k]));
                        }

                        httprequest.setValues("monitors", array2.elements());
                    } else {
                        httprequest.setValue("monitors", invert(as1[0]));
                    }
                    hashmap.put("monitors", as1);
                }
            }
            java.lang.String s17 = (java.lang.String) hashmap.get("context");
            if (s17 != null && s17.length() > 0) {
                httprequest.setValue("context", invert(s17));
            }
        }
        if (printwriter == null) {
            printwriter = new PrintWriter(java.lang.System.out);
        }
        com.dragonflow.SiteView.HistoryReport historyreport = null;
        if (httprequest.hasValue("queryID")) {
            if (!httprequest.actionAllowed("_reportGenerate")) {
                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_NOT_AUTHORIZED);
            }
            if (s.equals("ReportManagement")) {
                updateManagementConfig(httprequest);
            }
            historyreport = com.dragonflow.SiteView.HistoryReport.returnGenerateReportFromQueryID(httprequest.getValue("queryID"), printwriter, httprequest.getAccount());
        } else {
            if (!httprequest.actionAllowed("_reportAdhoc") && !httprequest.actionAllowed("_monitorRecent")) {
                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_NOT_AUTHORIZED, null);
            }
            if (httprequest.getValue("startDay").length() <= 0 || httprequest.getValue("startHour").length() <= 0 || httprequest.getValue("window").length() <= 0) {
                if (!httprequest.getValues("groups").hasMoreElements() && !httprequest.getValues("monitors").hasMoreElements()) {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_REPORT_NO_MONITORS);
                }
                long l = com.dragonflow.Utils.TextUtils.toLong(httprequest.getUserSetting("_timeOffset")) * 1000L;
                if (httprequest.getValue("startTimeDate").length() > 0) {
                    if (com.dragonflow.Utils.TextUtils.isDateStringValid(httprequest.getValue("startTimeDate")) && com.dragonflow.Utils.TextUtils.isTimeStringValid(httprequest.getValue("startTimeTime"))
                            && com.dragonflow.Utils.TextUtils.isDateStringValid(httprequest.getValue("endTimeDate")) && com.dragonflow.Utils.TextUtils.isTimeStringValid(httprequest.getValue("endTimeTime"))) {
                        long l1 = com.dragonflow.Utils.TextUtils.dateStringToSeconds(httprequest.getValue("startTimeDate"), httprequest.getValue("startTimeTime"));
                        long l2 = com.dragonflow.Utils.TextUtils.dateStringToSeconds(httprequest.getValue("endTimeDate"), httprequest.getValue("endTimeTime"));
                        long l3 = l1 * 1000L - l;
                        long l4 = l2 * 1000L - l;
                        java.util.Date date = new Date(l4);
                        httprequest.setValue("startHour", date.getHours() + ":" + com.dragonflow.Utils.TextUtils.numberToString(date.getMinutes()));
                        httprequest.setValue("startDay", "" + (date.getMonth() + 1) + "/" + date.getDate() + "/" + (date.getYear() + 1900));
                        long l5 = (l4 - l3) / 1000L;
                        long l6 = 0x1e28500L;
                        if (l5 > l6) {
                            l5 = l6;
                        }
                        httprequest.setValue("window", "" + l5);
                    } else {
                        throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_REPORT_INVALID_TIME);
                    }
                }
            }
            java.lang.String s4 = "";
            if (httprequest.isGet() && httprequest.getValue("isFlipper").length() == 0) {
                s4 = "<a href=\"javascript:window.close()\">Close Window</a>";
            } else if (httprequest.getValue("isFlipper").length() == 0) {
                s4 = "<a href=\"/SiteView/cgi/go.exe/SiteView?page=report&account=" + httprequest.getAccount() + "&operation=adhoc\">Quick Report Form</a>";
            }
            if (s.equals("ReportQuick")) {
                httprequest.setValue("isadhoc", "true");
                historyreport = com.dragonflow.SiteView.HistoryReport.returnReportFromRequest(httprequest, printwriter, s4);
            } else if (s.equals("ReportManagement")) {
                adjustHistoryConfig(httprequest, null, null);
                java.lang.String s6 = httprequest.getValue("id");
                httprequest.setValue("queryID", s6);
                httprequest.setValue("startDay", "today");
                com.dragonflow.SiteView.HistoryReport.generateIndexPage("administrator", s6, "");
                historyreport = new HistoryReport();
                historyreport.setProperty(com.dragonflow.SiteView.HistoryReport.pQueryID, s6);
                historyreport.setProperty(com.dragonflow.SiteView.HistoryReport.pFilePath, com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "htdocs" + java.io.File.separator + "Reports-" + s6 + java.io.File.separator + "Findex.html");
            }
        }
        com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
        detectconfigurationchange.setConfigChangeFlag();
        java.lang.String s7 = "";
        if (s.equals("ReportQuick") && hashmap != null) {
            java.lang.String s9 = historyreport.getProperty(com.dragonflow.SiteView.HistoryReport.pFilePath);
            s9 = s9.replaceAll("\\\\", "/");
            s9 = "/SiteView/htdocs/Reports-0" + s9.substring(s9.lastIndexOf("/"));
            java.lang.String s12 = (java.lang.String) hashmap.get("oldID");
            jgl.HashMap hashmap1 = new HashMap();
            hashmap1.put("isQuick", "true");
            hashmap1.put("path", s9);
            s7 = (java.lang.String) hashmap.get("qID");
            if (s12 != null && s12.length() > 0) {
                if (s12.indexOf(s9) < 0) {
                    jgl.Array array1 = com.dragonflow.Api.APIReport.getReportFrames();
                    int j = 0;
                    do {
                        if (j >= array1.size()) {
                            break;
                        }
                        jgl.HashMap hashmap2 = (jgl.HashMap) array1.at(j);
                        if (hashmap2.get("isQuick") != null && ((java.lang.String) hashmap2.get("isQuick")).length() > 0) {
                            java.lang.String s18 = (java.lang.String) hashmap2.get("id");
                            if (s18.equals(s7)) {
                                hashmap2.put("path", s9);
                                com.dragonflow.Api.APIReport.saveReportFrames(array1);
                                break;
                            }
                        }
                        j ++;
                    } while (true);
                }
            } else {
                s7 = adjustHistoryConfig(httprequest, hashmap1, null);
            }
            if (s7.length() > 0) {
                hashmap.put("_id", s7);
            }
            hashmap.put("_HTMLpath", s9);
            return s9;
        }
        java.lang.String s10 = "";
        if (historyreport != null) {
            s7 = historyreport.getProperty(com.dragonflow.SiteView.HistoryReport.pQueryID);
            s10 = "/SiteView/htdocs/Reports-" + s7 + "/Findex.html";
        }
        if (s7.length() > 0) {
            hashmap.put("_id", s7);
        }
        hashmap.put("_HTMLpath", s10);
        return s10;
    }

    public void updateManagementConfig(com.dragonflow.HTTP.HTTPRequest httprequest) throws com.dragonflow.SiteViewException.SiteViewException {
        java.lang.String s = new String();
        httprequest.setValue("startDay", "today");
        jgl.HashMap hashmap = getHistoryMap(httprequest, httprequest.getValue("queryID"), s);
        adjustHistoryConfig(httprequest, hashmap, httprequest.getValue("queryID"));
    }

    public java.lang.String update(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap) throws com.dragonflow.SiteViewException.SiteViewException {
        return update(s, s1, hashmap, null, null);
    }

    public java.lang.String update(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap, com.dragonflow.HTTP.HTTPRequest httprequest, java.io.PrintWriter printwriter) throws com.dragonflow.SiteViewException.SiteViewException {
        java.lang.String s2 = s;
        java.lang.String s3 = null;
        int i = -1;
        if (httprequest == null) {
            s3 = (java.lang.String) hashmap.get("_class");
            if (s2 != null && s2.length() > 0 && s2.indexOf("Reports-") >= 0) {
                int j = s2.indexOf("Reports-") + 8;
                i = com.dragonflow.Utils.TextUtils.readInteger(s2, j);
            } else if (com.dragonflow.Utils.TextUtils.isInteger(s)) {
                i = com.dragonflow.Utils.TextUtils.toInt(s);
            }
            if (s3.equals("ReportManagement")) {
                hashmap.put("queryID", "" + i);
                hashmap.put("id", "" + i);
                hashmap.put("relative", "-1");
            } else {
                hashmap.put("qID", "" + i);
            }
        } else {
            s3 = s;
        }
        return create(s3, s1, hashmap, httprequest, printwriter);
    }

    public void delete(java.lang.String s, java.lang.String s1) throws com.dragonflow.SiteViewException.SiteViewException {
        delete(s, s1, -1);
    }

    public void delete(java.lang.String s, java.lang.String s1, int i) throws com.dragonflow.SiteViewException.SiteViewException {
        if (s != null && s.length() > 0 && s.indexOf("Reports-") >= 0 || i >= 0) {
            if (i < 0) {
                int j = s.indexOf("Reports-") + 8;
                i = com.dragonflow.Utils.TextUtils.readInteger(s, j);
            }
            adjustHistoryConfig(null, null, java.lang.Integer.toString(i));
        }
    }

    public java.util.Vector getInstances(java.lang.String s, java.lang.String s1, int i) throws com.dragonflow.SiteViewException.SiteViewException {
        java.util.Vector vector = new Vector();
        updateContext();
        jgl.Array array = com.dragonflow.Api.APIReport.getReportFrames();
        for (int j = 0; j < array.size(); j ++) {
            jgl.HashMap hashmap = (jgl.HashMap) array.at(j);
            if (com.dragonflow.Utils.TextUtils.getValue(hashmap, "isQuick").length() > 0) {
                continue;
            }
            jgl.Array array1 = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmap, "monitors");
            if (array1.size() > 1) {
                hashmap.remove("monitors");
                java.lang.String as[] = new java.lang.String[array1.size()];
                for (int k = 0; k < array1.size(); k ++) {
                    as[k] = invert((java.lang.String) array1.at(k));
                }

                hashmap.put("monitors", as);
            } else if (array1.size() == 1) {
                hashmap.put("monitors", invert((java.lang.String) array1.at(0)));
            }
            java.lang.String s2 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "context");
            if (s2.length() > 0) {
                hashmap.put("context", invert(s2));
            }
            java.lang.String s3 = "/SiteView/htdocs/Reports-" + hashmap.get("id") + "/Findex.html";
            java.lang.String s4 = generateName(hashmap);
            if (s4 == null) {
                continue;
            }
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "_hideReportSummary", "showSummaryTable", true, "on");
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "_hideReportTables", "showTables", true, "on");
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "_hideReportErrors", "showErrors", true, "on");
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "_hideReportWarnings", "showWarnings", true, "on");
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "_hideReportGoods", "showGoods", true, "on");
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "basic", "detailed", true, "on");
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "_showReportThresholdSummary", "showThresholdSummary", false, "on");
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "_upTimeIncludeWarning", "upTimeIncludeWarning", false, "on");
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "_warningNotIncluded", "warningNotIncluded", false, "on");
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "_failureNotIncluded", "failureNotIncluded", false, "on");
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "_showReportErrorTimeSummary", "showErrorTimeSummary", false, "on");
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "bestCaseCalc", "bestCaseCalc", false, "on");
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "attachReport", "attachReport", false, "on");
            com.dragonflow.Api.APIReport.mapCheckProps(hashmap, "disabled", "disabled", false, "on");
            java.lang.String s5 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "reportType");
            if (com.dragonflow.Utils.TextUtils.getValue(hashmap, "_hideReportCharts").length() == 0) {
                hashmap.put("reportType", s5);
            } else {
                hashmap.put("reportType", "none");
            }
            hashmap.remove("_hideReportCharts");
            java.lang.String s6 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_showReportAlerts");
            if (s6.length() > 0) {
                hashmap.put("alertDetailLevel", s6);
            } else {
                hashmap.put("alertDetailLevel", "none");
            }
            hashmap.remove("_showReportAlerts");
            java.lang.String s7 = (java.lang.String) hashmap.get("schedule");
            java.lang.String as1[] = com.dragonflow.Utils.TextUtils.split(s7, "\t");
            java.lang.String s8 = "00:00";
            if (as1.length == 3) {
                try {
                    int l = java.lang.Integer.parseInt(as1[2]);
                    java.lang.String s9 = java.lang.String.valueOf(l / 3600);
                    s9 = com.dragonflow.Api.APIReport.zeroFill(s9);
                    java.lang.String s10 = java.lang.String.valueOf((l % 3600) / 60);
                    s10 = com.dragonflow.Api.APIReport.zeroFill(s10);
                    s8 = s9 + ":" + s10;
                } catch (java.lang.Exception exception) {
                }
            }
            hashmap.put("hoursMinutes", s8);
            hashmap.remove("schedule");
            hashmap.put("_name", s4);
            hashmap.put("_class", "ReportManagement");
            hashmap.put("_id", hashmap.get("id"));
            hashmap.put("_HTMLpath", s3);
            vector.add(hashmap);
        }

        return vector;
    }

    private static void mapCheckProps(jgl.HashMap hashmap, java.lang.String s, java.lang.String s1, boolean flag, java.lang.String s2) {
        java.lang.String s3 = (java.lang.String) hashmap.get(s);
        java.lang.String s4 = "";
        if (flag) {
            if (s3 == null || s3.length() == 0) {
                s4 = s2;
            }
        } else if (s3 != null) {
            s4 = s2;
        }
        hashmap.put(s1, s4);
        if (!s.equals(s1)) {
            hashmap.remove(s);
        }
    }

    private static java.lang.String zeroFill(java.lang.String s) {
        if (s.length() == 1) {
            s = "0" + s;
        }
        return s;
    }

    public java.util.Vector getTemplateList() throws com.dragonflow.SiteViewException.SiteViewException {
        java.util.Vector vector = new Vector();
        java.lang.String s = "";
        java.lang.String s1 = "";
        s = com.dragonflow.SiteView.Platform.getRoot() + s1 + java.io.File.separator + "templates.history";
        java.io.File file = new File(s);
        java.lang.String as[] = file.list();
        for (int i = 0; i < as.length; i ++) {
            java.lang.String as1[] = new java.lang.String[2];
            as1[0] = as[i];
            as1[1] = as[i];
            vector.addElement(as1);
        }

        return vector;
    }

    public static void deleteQuickReports() {
        jgl.Array array = com.dragonflow.Api.APIReport.getReportFrames();
        for (int i = 0; array != null && i < array.size(); i ++) {
            jgl.HashMap hashmap = (jgl.HashMap) array.at(i);
            if (com.dragonflow.Utils.TextUtils.getValue(hashmap, "isQuick").length() > 0) {
                array.remove(i --);
            }
        }

        com.dragonflow.Api.APIReport.saveReportFrames(array);
    }

    private java.lang.String invert(java.lang.String s) {
        java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s, " ");
        if (as.length == 2) {
            return as[1] + " " + as[0];
        } else {
            return s;
        }
    }

    private void updateContext() {
        jgl.Array array = com.dragonflow.Api.APIReport.getReportFrames();
        for (int i = 0; i < array.size(); i ++) {
            jgl.HashMap hashmap = (jgl.HashMap) array.at(i);
            java.lang.String s = com.dragonflow.Utils.TextUtils.getValue(hashmap, "context");
            if (com.dragonflow.Utils.TextUtils.getValue(hashmap, "isQuick").length() <= 0) {
                jgl.Array array1 = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmap, "monitors");
                java.lang.String s1 = com.dragonflow.Api.APIReport.getContext(array1, s);
                hashmap.put("context", s1.length() != 0 ? ((java.lang.Object) (s1)) : "_SiteViewRoot_");
            }
        }

        com.dragonflow.Api.APIReport.saveReportFrames(array);
    }

    private java.lang.String getMonitor(java.lang.String s) {
        java.lang.String s1 = new String(s == null ? "" : s);
        java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s1, " ");
        if (as.length == 2) {
            s1 = as[1];
        }
        return s1;
    }

    private jgl.HashMap getHistoryMap(com.dragonflow.HTTP.HTTPRequest httprequest, java.lang.String s, java.lang.String s1) throws com.dragonflow.SiteViewException.SiteViewException {
        com.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
        int i = com.dragonflow.Utils.TextUtils.toInt(httprequest.getUserSetting("_timeOffset"));
        boolean flag = com.dragonflow.Page.reportPage.setReportOptions(httprequest, hashmapordered);
        java.util.Enumeration enumeration = httprequest.getValues("monitors");
        if (!enumeration.hasMoreElements() && !flag && httprequest.getValue("query").length() == 0) {
            s1 = s1 + "\tNo monitors were selected for this report";
            throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_REPORT_NO_MONITORS);
        }
        while (enumeration.hasMoreElements()) {
            java.lang.String s2 = (java.lang.String) enumeration.nextElement();
            java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s2, ",");
            int k = 0;
            while (as != null && k < as.length) {
                jgl.Array array = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmapordered, "monitors");
                boolean flag1 = false;
                int j1 = 0;
                do {
                    if (j1 >= array.size()) {
                        break;
                    }
                    if (as[k].equals(array.at(j1))) {
                        flag1 = true;
                        break;
                    }
                    j1 ++;
                } while (true);
                if (!flag1) {
                    hashmapordered.add("monitors", as[k]);
                }
                k ++;
            }
        }
        if (s.length() > 0) {
            hashmapordered.put("id", s);
        }
        hashmapordered.put("window", httprequest.getValue("window"));
        hashmapordered.put("precision", httprequest.getValue("precision"));
        hashmapordered.put("format", httprequest.getValue("format"));
        hashmapordered.put("vmax", httprequest.getValue("vmax"));
        java.lang.String s3 = httprequest.getValue("startHour");
        if (!s3.equals("now")) {
            s3 = java.lang.String.valueOf(com.dragonflow.Utils.TextUtils.toLong(s3) - (long) i);
        }
        hashmapordered.put("startHour", s3);
        hashmapordered.put("startDay", httprequest.getValue("startDay"));
        hashmapordered.put("relative", httprequest.getValue("relative"));
        hashmapordered.put("email", com.dragonflow.Utils.TextUtils.toEmailList(httprequest.getValue("email")));
        hashmapordered.put("emailData", com.dragonflow.Utils.TextUtils.toEmailList(httprequest.getValue("emailData")));
        hashmapordered.put("xmlEmailData", com.dragonflow.Utils.TextUtils.toEmailList(httprequest.getValue("xmlEmailData")));
        hashmapordered.put("mailTemplate", httprequest.getValue("mailTemplate"));
        hashmapordered.put("title", httprequest.getValue("title"));
        hashmapordered.put("description", httprequest.getValue("description"));
        hashmapordered.put("statusFilter", httprequest.getValue("statusFilter"));
        hashmapordered.put("schedFilter", httprequest.getValue("schedFilter"));
        if (httprequest.getValue("context").length() > 0) {
            hashmapordered.put("context", httprequest.getValue("context"));
        }
        if (com.dragonflow.Utils.TextUtils.getValue(hashmapordered, "mailTemplate").equals("HistoryMail")) {
            hashmapordered.remove("mailTemplate");
        }
        hashmapordered.put("noSlotFilter", "true");
        if (httprequest.getValue("tabfile").length() > 0) {
            hashmapordered.put("tabfile", "yes");
        }
        if (httprequest.getValue("xmlfile").length() > 0) {
            hashmapordered.put("xmlfile", "yes");
        }
        if (httprequest.getValue("disabled").length() > 0) {
            hashmapordered.put("disabled", "checked");
        }
        if (httprequest.getValue("detailed").length() == 0) {
            hashmapordered.put("basic", "checked");
        }
        if (httprequest.getValue("attachReport").length() > 0) {
            hashmapordered.put("attachReport", "checked");
        }
        if (httprequest.getValue("bestCaseCalc").length() > 0) {
            hashmapordered.put("bestCaseCalc", "checked");
        }
        int j = 0x15180;
        int l = 1;
        int i1 = 0;
        java.lang.String s4 = httprequest.getValue("hoursMinutes");
        try {
            j = com.dragonflow.Utils.TextUtils.toInt(httprequest.getValue("window"));
            if (s4 != null && s4.length() > 0) {
                java.lang.String as1[] = com.dragonflow.Utils.TextUtils.split(s4, ":");
                if (as1.length == 2) {
                    l = com.dragonflow.Utils.TextUtils.toInt(as1[0]) * 3600;
                    i1 = com.dragonflow.Utils.TextUtils.toInt(as1[1]) * 60;
                } else {
                    com.dragonflow.Log.LogManager.log("Error", "Reports - Unable to recognize 'Generate this report at: " + s4);
                }
            } else {
                l = com.dragonflow.Utils.TextUtils.toInt(httprequest.getValue("hours"));
                i1 = com.dragonflow.Utils.TextUtils.toInt(httprequest.getValue("minutes"));
            }
        } catch (java.lang.NumberFormatException numberformatexception) {
            com.dragonflow.Log.LogManager.log("Error", "A number was passed from the browser reportPage that did not parse as an integer. It was 'window', 'hours', or 'minutes': " + numberformatexception.toString());
            com.dragonflow.Log.LogManager.log("Error", "reportPage is unhappy: " + com.dragonflow.Utils.FileUtils.stackTraceText(numberformatexception));
        }
        int k1 = (l + i1) - i;
        java.lang.String s5;
        if (j == 0x278d00) {
            s5 = "monthday\t1\t" + k1;
        } else if (j == 0x93a80) {
            s5 = "weekday\tU\t" + k1;
        } else {
            s5 = "weekday\tM,T,W,R,F,S,U\t" + k1;
        }
        hashmapordered.put("schedule", s5);
        return hashmapordered;
    }

    private java.lang.String adjustHistoryConfig(com.dragonflow.HTTP.HTTPRequest httprequest, jgl.HashMap hashmap, java.lang.String s) throws com.dragonflow.SiteViewException.SiteViewException {
        jgl.Array array = com.dragonflow.Api.APIReport.getReportFrames();
        if (s != null && s.length() > 0) {
            for (int i = 0; i < array.size(); i ++) {
                jgl.HashMap hashmap1 = (jgl.HashMap) array.at(i);
                java.lang.String s2 = (java.lang.String) hashmap1.get("id");
                if (s2 == null || !s2.equals(s)) {
                    continue;
                }
                if (hashmap != null) {
                    hashmap.put("id", s2);
                    array.replace(hashmap1, hashmap);
                } else {
                    array.remove(i --);
                }
            }

            com.dragonflow.Api.APIReport.saveReportFrames(array);
        } else {
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            s = siteviewgroup.getValue("_nextReportID");
            if (s.length() == 0) {
                s = "10";
            }
            siteviewgroup.setProperty("_nextReportID", com.dragonflow.Utils.TextUtils.increment(s));
            siteviewgroup.saveSettings();
            if (hashmap != null && hashmap.get("isQuick") != null && ((java.lang.String) hashmap.get("isQuick")).length() > 0) {
                hashmap.put("id", s);
                array.add(hashmap);
                com.dragonflow.Api.APIReport.saveReportFrames(array);
            } else {
                httprequest.setValue("id", s);
                java.lang.String s1 = new String();
                jgl.HashMap hashmap2 = getHistoryMap(httprequest, s, s1);
                hashmap2.add("relative", "-1");
                array.add(hashmap2);
                com.dragonflow.Api.APIReport.saveReportFrames(array);
            }
        }
        return s;
    }

    private static jgl.Array getReportFrames() {
        jgl.Array array = null;
        try {
            java.lang.String s = com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "groups" + java.io.File.separator + "history.config";
            java.io.File file = new File(s);
            if (!file.exists()) {
                array = new Array();
            } else {
                array = com.dragonflow.Properties.FrameFile.readFromFile(s);
            }
        } catch (java.io.IOException ioexception) {
            array = new Array();
        }
        return array;
    }

    private static void saveReportFrames(jgl.Array array) {
        try {
            com.dragonflow.Properties.FrameFile.writeToFile(com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "groups" + java.io.File.separator + "history.config", array);
            com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        } catch (java.io.IOException ioexception) {
            com.dragonflow.Log.LogManager.log("Error", "reportPage.saveReportFrameList() cannot write the report config file, history.config: " + ioexception.toString());
            com.dragonflow.Log.LogManager.log("Error", "reportPage.saveReportFrameList(): " + com.dragonflow.Utils.FileUtils.stackTraceText(ioexception));
        }
    }

    private java.lang.String generateName(jgl.HashMap hashmap) {
        java.lang.Object obj = hashmap.get("monitors");
        if (obj instanceof java.lang.String) {
            return nameFromString(obj);
        }
        if (obj instanceof java.lang.String[]) {
            java.lang.String as[] = (java.lang.String[]) obj;
            java.lang.StringBuffer stringbuffer = new StringBuffer();
            for (int i = 0; i < as.length; i ++) {
                if (i == 1) {
                    stringbuffer.append(" and ");
                } else if (i > 1) {
                    stringbuffer.append(", ");
                }
                java.lang.String s = nameFromString(as[i]);
                if (s == null) {
                    return null;
                }
                stringbuffer.append(s);
            }

            return stringbuffer.toString();
        } else {
            return null;
        }
    }

    private java.lang.String nameFromString(java.lang.Object obj) {
        java.lang.String s = (java.lang.String) obj;
        java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s, " ");
        if (as.length > 1) {
            com.dragonflow.SiteView.MonitorGroup monitorgroup = com.dragonflow.SiteView.MonitorGroup.getMonitorGroup(as[0]);
            if (!$assertionsDisabled && monitorgroup == null) {
                throw new AssertionError();
            }
            if (monitorgroup == null) {
                com.dragonflow.Log.LogManager.log("error", "Report group unknown. Group:" + as[0]);
                return null;
            }
            com.dragonflow.SiteView.SiteViewObject siteviewobject = monitorgroup.getElementByID(as[1]);
            if (!$assertionsDisabled && siteviewobject == null) {
                throw new AssertionError();
            }
            if (siteviewobject == null) {
                com.dragonflow.Log.LogManager.log("error", "Report monitor unknown. Group:" + as[0] + " Monior:" + as[1]);
                return null;
            } else {
                return siteviewobject.getProperty("_name") + " Monitor";
            }
        }
        if (as[0].equals("_master")) {
            return "All monitors";
        } else {
            return as[0] + " Group";
        }
    }

    static {
        $assertionsDisabled = !(com.dragonflow.Api.APIReport.class).desiredAssertionStatus();
    }
}
