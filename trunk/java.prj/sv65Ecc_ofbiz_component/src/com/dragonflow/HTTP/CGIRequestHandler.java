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

import com.dragonflow.Utils.CommandLine;

// Referenced classes of package com.dragonflow.HTTP:
// HTTPRequestHandler, HTTPRequestException, HTTPRequest, HTTPServer

public class CGIRequestHandler extends com.dragonflow.HTTP.HTTPRequestHandler {

    com.dragonflow.HTTP.HTTPServer httpServer;

    public CGIRequestHandler(com.dragonflow.HTTP.HTTPServer httpserver) {
        httpServer = httpserver;
    }

    /**
     * CAUTION: Decompiled by hand.
     */
    public void handleRequest(com.dragonflow.HTTP.HTTPRequest httprequest) throws Exception {
        String s1;
        if (httprequest.getURL().indexOf("go.exe") < 0) {
            throw new HTTPRequestException(404, httprequest.getURL());
        }
        String s = com.dragonflow.Utils.I18N.toDefaultEncoding(httprequest.getValue("group"));
        if (s.length() > 0 && !com.dragonflow.Page.CGI.isGroupAllowedForAccount(s, httprequest)) {
            throw new HTTPRequestException(557);
        }
        s1 = httprequest.getValue("page");
        if (s1 == null || s1.length() == 0) {
            s1 = "index";
        }
        com.dragonflow.HTTP.HTTPRequest _tmp = httprequest;
        com.dragonflow.HTTP.HTTPRequest.noCache = true;
        if (s1.equals("perfex")) {
            printDebugHeader(httprequest, s1);
            outputStream.println("<PRE>");
            jgl.Array array = (new CommandLine()).exec(com.dragonflow.SiteView.Platform.getRoot() + "/tools/perfex " + httprequest.getValue("option"));
            for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); outputStream.println((String) enumeration.nextElement())) {
            }
            outputStream.println("</PRE>");
            printDebugFooter();
        } else if (s1.equals("r3starT")) {
            System.exit(0);
        } else if (s1.equals("shutd0wN")) {
            printDebugHeader(httprequest, s1);
            outputStream.println("<PRE>" + com.dragonflow.SiteView.Platform.productName + " shutting down. This might take a few minutes...");
            outputStream.flush();
            com.dragonflow.Log.LogManager.log("Error", com.dragonflow.SiteView.Platform.productName + " shutting down from browser");
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            boolean flag = httprequest.getValue("doQuick").toLowerCase().equals("true");
            siteviewgroup.stopSiteView(flag, null);
            outputStream.println(com.dragonflow.SiteView.Platform.productName + " shutdown complete");
            outputStream.flush();
            printDebugFooter();
            System.exit(0);
        } else if (s1.equals("SendModem")) {
            printDebugHeader(httprequest, s1);
            outputStream.println("<PRE>");
            jgl.Array array1 = (new CommandLine()).exec(com.dragonflow.SiteView.Platform.getRoot() + "/tools/SendModem " + httprequest.getValue("option"));
            for (java.util.Enumeration enumeration1 = array1.elements(); enumeration1.hasMoreElements(); outputStream.println((String) enumeration1.nextElement())) {
            }
            outputStream.println("</PRE>");
            printDebugFooter();
        } else if (s1.equals("dialup")) {
            printDebugHeader(httprequest, s1);
            outputStream.println("<PRE>");
            jgl.Array array2 = (new CommandLine()).exec(com.dragonflow.SiteView.Platform.getRoot() + "/tools/dialup " + httprequest.getValue("option"));
            for (java.util.Enumeration enumeration2 = array2.elements(); enumeration2.hasMoreElements(); outputStream.println((String) enumeration2.nextElement())) {
            }
            outputStream.println("</PRE>");
            printDebugFooter();
        } else if (s1.equals("DisplayHTML")) {
            outputStream.println(httprequest.getValue("displayString"));
        } else if (s1.equals("AckLog")) {
            String s2 = com.dragonflow.Utils.I18N.UnicodeToString(httprequest.getValue("monitor"), com.dragonflow.Utils.I18N.nullEncoding());
            String s3 = httprequest.getAccount();
            String s4 = com.dragonflow.SiteView.Platform.getDirectoryPath("logs", s3);
            StringBuffer stringbuffer = com.dragonflow.Utils.FileUtils.readFile(s4 + "/Operator.log");
            outputStream.println("<body><h1>Acknowledge Log</h1>\n");
            int i = 0;
            int j = 0;
            outputStream.println("<table border><tr><th><b>Date/Time</th><th>Operation</th><th>Who</th><th>Status</th><th>Message</th></tr></b>\n");
            while ((i = stringbuffer.toString().substring(j).indexOf("\n")) > -1) {
                String s5 = stringbuffer.toString().substring(j, j + i);
                if (s2 == null || s5.indexOf(s2) > -1 && s5.indexOf('\t') >= 0) {
                    outputStream.println("<tr>");
                    int k = 0;
                    boolean flag1 = false;
                    int l = 0;
                    for (l = 0; l < (flag1 ? 2 : 7); l ++) {
                        String s6 = com.dragonflow.Utils.I18N.StringToUnicode(s5.substring(k, s5.indexOf('\t', k)), com.dragonflow.Utils.I18N.nullEncoding());
                        if (l != 3 && l != 4 && l != 6) {
                            outputStream.println("<td>" + s6 + "</td>");
                        }
                        if (l == 1 && s6.compareTo("AcknowledgeClear") == 0) {
                            flag1 = true;
                        }
                        k = s5.indexOf('\t', k) + 1;
                    }

                    if (l > 2) {
                        outputStream.println("<td>" + s5.substring(k) + "</td>");
                    }
                    outputStream.println("</tr>");
                }
                if (stringbuffer.toString().substring(j + i).length() <= 1) {
                    j += i;
                    break;
                }
                j += i + 1;
            }
            outputStream.println("</table></body>");
        } else if (s1.equals("monitors")) {
            printDebugHeader(httprequest, s1);
            outputStream.println("<PRE>");
            outputStream.println(com.dragonflow.Utils.DebugWatcher.checkMonitors());
            outputStream.println("</PRE>");
            printDebugFooter();
        } else if (s1.equals("threads")) {
            printDebugHeader(httprequest, s1);
            outputStream.println("<PRE>");
            outputStream.flush();
            try {
                outputStream.println(com.dragonflow.Utils.DebugWatcher.checkThreads());
            } catch (Throwable throwable) {
                outputStream.println("error=" + throwable);
                throwable.printStackTrace();
            }
            outputStream.println("</PRE>");
            printDebugFooter();
        } else if (s1.endsWith("Scheduler")) {
            printDebugHeader(httprequest, s1);
            outputStream.println("<PRE>");
            outputStream.println(com.dragonflow.Utils.DebugWatcher.checkScheduler(s1));
            outputStream.println("</PRE>");
            printDebugFooter();
        } else if (s1.equalsIgnoreCase("runmonitor")) {
            printDebugHeader(httprequest, s1);
            outputStream.println("<PRE>");
            outputStream.println(com.dragonflow.Utils.DebugWatcher.lastLogLines());
            outputStream.println("</PRE>");
            printDebugFooter();
        }
		else
		{
            try 
			{
                Class class1 = Class.forName("com.dragonflow.Page." + s1 + "Page");
                com.dragonflow.Page.CGI cgi = (com.dragonflow.Page.CGI) class1.newInstance();
                cgi.initialize(httprequest, outputStream);
                cgi.printCGIHeader();
                cgi.printBody(outputStream);
                cgi.printCGIFooter();
            } catch (ClassNotFoundException classnotfoundexception) {
                throw new HTTPRequestException(404);
            } catch (NoClassDefFoundError noclassdeffounderror) {
                throw new HTTPRequestException(404);
            }
        }
    }

    private void printDebugHeader(com.dragonflow.HTTP.HTTPRequest httprequest, String s) {
        httprequest.printHeader(outputStream);
        outputStream.println("<HTML>");
        outputStream.println("<HEAD>");
        outputStream.println("<TITLE>" + s + "</TITLE></HEAD>");
        outputStream.println("<BODY BGCOLOR=\"#ffffff\">");
    }

    private void printDebugFooter() {
        outputStream.println("</BODY>");
        outputStream.println("</HTML>");
        outputStream.flush();
    }
}
