/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.HTTP;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import jgl.Array;
import com.dragonflow.Properties.HashMapOrdered;

// Referenced classes of package com.dragonflow.HTTP:
// HTTPRequest

public class ProxyHandler {

    public static jgl.HashMap monitor = new HashMapOrdered(true);

    public static boolean started = false;

    public static int step = 0;

    public static java.lang.String groupID = "recorded";

    public ProxyHandler() {
    }

    public static void handleProxyRequest(com.dragonflow.HTTP.HTTPRequest httprequest, java.io.PrintWriter printwriter) {
        java.lang.String s = httprequest.rawURL;
        if (s.indexOf("siteviewRecordStart") >= 0) {
            started = true;
            groupID = com.dragonflow.Utils.I18N.toDefaultEncoding(httprequest.getValue("groupID"));
            if (groupID.length() == 0) {
                groupID = "recorded";
            }
            com.dragonflow.Utils.TextUtils.debugPrint("STARTING");
            java.lang.String s1 = "<HTML><HEAD><TITLE>Starting Recording</TITLE></HEAD>\n<BODY><H2>Starting Recording</H2></BODY></HTML>";
            com.dragonflow.HTTP.HTTPRequest _tmp = httprequest;
            com.dragonflow.HTTP.HTTPRequest.printHeader(printwriter, 200, "OK", "text/html", s1.length(), null, -1L, -1L);
            printwriter.print(s1);
            return;
        }
        if (s.indexOf("siteviewRecordStop") >= 0) {
            started = false;
            com.dragonflow.Utils.TextUtils.debugPrint("ENDING");
            java.lang.String s2 = "<HTML><HEAD><TITLE>Done Recording</TITLE></HEAD>\n<BODY><H2>Done Recording</H2>\n<P><A HREF=http://localhost:8888" + com.dragonflow.Page.CGI.getGroupDetailURL(httprequest, groupID) + ">Go to group</A>\n"
                    + "</BODY></HTML>";
            com.dragonflow.HTTP.HTTPRequest _tmp1 = httprequest;
            com.dragonflow.HTTP.HTTPRequest.printHeader(printwriter, 500, "Internal Server Error", "text/html", s2.length(), null, -1L, -1L);
            printwriter.print(s2);
            com.dragonflow.HTTP.ProxyHandler.saveMonitor();
            return;
        }
        com.dragonflow.Utils.TextUtils.debugPrint("Request\n" + httprequest.postDetails());
        java.lang.String s3 = "";
        java.lang.String s4 = "";
        java.lang.String s5 = "";
        java.lang.String s6 = "";
        java.lang.String s7 = "";
        if (s.indexOf(":443") >= 0) {
            s7 = "[NT]";
            if (httprequest.requestMethod.equals("CONNECT")) {
                com.dragonflow.HTTP.HTTPRequest _tmp2 = httprequest;
                com.dragonflow.HTTP.HTTPRequest.printHeader(printwriter, 200, "OK", "text/html", 0L, null, -1L, -1L);
                return;
            }
        }
        java.lang.String s8 = "";
        int i = 60000;
        com.dragonflow.Utils.TextUtils.debugPrint("userName=" + s7);
        com.dragonflow.Utils.TextUtils.debugPrint("method=" + httprequest.requestMethod);
        long l = 0xf4240L;
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        jgl.Array array = new Array();
        for (java.util.Enumeration enumeration = httprequest.getVariables(); enumeration.hasMoreElements();) {
            java.lang.String s9 = (java.lang.String) enumeration.nextElement();
            java.util.Enumeration enumeration2 = httprequest.getValues(s9);
            while (enumeration2.hasMoreElements()) {
                array.add(s9 + "=" + enumeration2.nextElement());
            }
        }

        if (array.size() == 0) {
            array = null;
        }
        com.dragonflow.Utils.TextUtils.debugPrint("GETTING URL=" + s);
        if (array != null) {
            for (java.util.Enumeration enumeration1 = array.elements(); enumeration1.hasMoreElements(); com.dragonflow.Utils.TextUtils.debugPrint((java.lang.String) enumeration1.nextElement())) {
            }
        }
        java.lang.StringBuffer stringbuffer1 = new StringBuffer("");
        com.dragonflow.Utils.SocketSession socketsession = com.dragonflow.Utils.SocketSession.getSession(null);
        long al[] = com.dragonflow.StandardMonitor.URLMonitor.checkURL(socketsession, s, s3, "", s4, s5, s6, array, s7, s8, "", stringbuffer, l, "", 100, i, null, stringbuffer1);
        socketsession.close();
        com.dragonflow.Utils.TextUtils.debugPrint("RESULT=" + al[0]);
        java.lang.String s10 = stringbuffer1.toString();
        int j = s10.indexOf("CONTENT-TYPE:");
        int k = -1;
        if (j >= 0) {
            k = s10.substring(j).toUpperCase().indexOf("TEXT");
            if (k < 0) {
                k = s10.substring(j).toUpperCase().indexOf("MULTIPART/X-MIXED-REPLACE");
            }
        }
        if (j >= 0 && k >= 0 && k - j < 40) {
            com.dragonflow.Utils.TextUtils.debugPrint("RESULT BUFFER=\n" + stringbuffer1.toString());
        }
        java.lang.String s11 = com.dragonflow.StandardMonitor.URLMonitor.getHTTPHeaders(stringbuffer.toString());
        if (started) {
            boolean flag = true;
            jgl.Array array1 = new Array();
            if (com.dragonflow.Utils.TextUtils.matchExpression(s11, "/content-type:\\s*(\\S*)/i", array1, new StringBuffer()) > 0) {
                java.lang.String s12 = (java.lang.String) array1.at(0);
                com.dragonflow.Utils.TextUtils.debugPrint("CONTENTTYPE=" + s12);
                if (!s12.equalsIgnoreCase("text/html")) {
                    flag = false;
                }
            }
            if (flag) {
                com.dragonflow.Utils.TextUtils.debugPrint("SAVING STEP");
                step ++;
                monitor.put("_referenceType" + step, "url");
                monitor.put("_reference" + step, s);
                if (array != null) {
                    for (int i1 = 0; i1 < array.size(); i1 ++) {
                        monitor.add("_postData" + step, array.at(i1));
                    }

                }
            }
        }
        com.dragonflow.Utils.TextUtils.debugPrint("HEADERS=\n" + s11 + "----------\n\n");
        printwriter.print(stringbuffer.toString());
    }

    static void saveMonitor() {
        monitor.put("_class", "URLSequenceMonitor");
        monitor.put("_id", "1");
        monitor.put("_timeout", "60");
        monitor.put("_frequency", "9000");
        com.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
        hashmapordered.put("_name", "config");
        hashmapordered.put("_nextID", "2");
        try {
            jgl.Array array = new Array();
            array.add(hashmapordered);
            array.add(monitor);
            java.lang.String s = com.dragonflow.SiteView.Platform.getRoot() + "/groups/" + groupID + ".mg";
            com.dragonflow.Utils.TextUtils.debugPrint("SAVING TO " + s);
            com.dragonflow.Properties.FrameFile.writeToFile(s, array);
        } catch (java.lang.Exception exception) {
            com.dragonflow.Log.LogManager.log("Error", "Error saving group " + exception.getMessage());
        }
        com.dragonflow.SiteView.SiteViewGroup.updateStaticPages(groupID);
    }

}
