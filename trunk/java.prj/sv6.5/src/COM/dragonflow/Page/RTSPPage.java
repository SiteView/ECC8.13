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

import COM.dragonflow.StandardMonitor.RTSPMonitor;

// Referenced classes of package COM.dragonflow.Page:
// CGI

public class RTSPPage extends COM.dragonflow.Page.CGI {

    public RTSPPage() {
    }

    public void printBody() {
        COM.dragonflow.StandardMonitor.RTSPMonitor rtspmonitor = new RTSPMonitor();
        outputStream.println("<pre>");
        outputStream.println("<H3><p align=\"center\">RTSP - Test Page</H3>");
        java.lang.String s = request.getValue("url");
        outputStream.println("<H4><p align=\"center\">URL: " + s + "</H4>");
        outputStream.println("<p align=\"left\">");
        rtspmonitor.testUpdate(outputStream, s);
        outputStream.println("<H4><p align=\"center\">JMF Log File</H4>");
        outputStream.println("<p align=\"left\">");
        try {
            java.lang.StringBuffer stringbuffer = COM.dragonflow.Utils.FileUtils
                    .readFile(COM.dragonflow.SiteView.Platform.getRoot()
                            + "/classes/jmf.log");
            jgl.Array array = COM.dragonflow.SiteView.Platform.split('\n',
                    stringbuffer.toString());
            java.lang.String s1;
            for (java.util.Enumeration enumeration = array.elements(); enumeration
                    .hasMoreElements(); outputStream.println("+\"" + s1.trim()
                    + "\"")) {
                s1 = (java.lang.String) enumeration.nextElement();
                s1 = COM.dragonflow.Utils.TextUtils.replaceChar(s1, '"', "\\\"");
            }

        } catch (java.lang.Exception exception) {
            outputStream.println("Exception: " + exception);
        }
        outputStream.println("<H4><p align=\"center\">*** END ***</H4>");
        outputStream.println("</pre>");
        outputStream.flush();
    }
}
