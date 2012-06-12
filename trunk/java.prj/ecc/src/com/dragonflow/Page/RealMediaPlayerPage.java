/*
 * 
 * Created on 2005-3-9 22:12:36
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Page;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

import jgl.Array;
import com.dragonflow.Utils.CommandLine;
import com.dragonflow.Utils.RealPlayerMonitorUtils;

// Referenced classes of package com.dragonflow.Page:
// CGI

public class RealMediaPlayerPage extends com.dragonflow.Page.CGI {

    private java.lang.String url;

    private java.lang.String duration;

    private static com.dragonflow.Utils.RealPlayerMonitorUtils realUtils = new RealPlayerMonitorUtils();

    private java.lang.String mediaLog;

    public RealMediaPlayerPage() {
        mediaLog = "";
    }

    public void printBody() {
        outputStream.println("<pre>");
        try {
            outputStream.println("<H2>Real Media Player Test Page</H2>");
            url = request.getValue("url");
            duration = request.getValue("duration");
            outputStream.println("<b>URL: </b>" + url);
            outputStream.println("<b>Duration: </b>" + duration);
            outputStream.flush();
            mediaLog = realUtils.getNewMediaLog();
            java.lang.String s = realUtils.getMediaCommand(url, duration,
                    mediaLog);
            outputStream.println("<b>Command: </b>" + s);
            outputStream.flush();
            jgl.Array array = new Array();
            long l = java.lang.System.currentTimeMillis();
            outputStream.println("Begin at " + l + " ms.");
            outputStream.println("Playing...");
            outputStream.flush();
            com.dragonflow.Utils.CommandLine commandline = new CommandLine();
            array = commandline.exec(s);
            long l1 = java.lang.System.currentTimeMillis();
            outputStream.println("Done.");
            outputStream.println("End at " + l1 + " ms.");
            outputStream.flush();
            long l2 = l1 - l;
            outputStream.println("<b>Elapsed: </b>" + l2 + " ms.");
            outputStream.flush();
            int i = commandline.getExitValue();
            outputStream.println("Exit Value: " + i);
            outputStream.flush();
            java.util.Enumeration enumeration = array.elements();
            outputStream.println("Results jgl.Array " + i);
            for (; enumeration.hasMoreElements(); outputStream
                    .println("Results: " + enumeration.nextElement())) {
            }
            outputStream.flush();
            if (i == 0) {
                outputStream.println("<p>");
                outputStream.println("<h4><u>Player Measurements</u></h4>");
                try {
                    java.io.BufferedReader bufferedreader = new BufferedReader(
                            new FileReader(mediaLog));
                    java.lang.String s1;
                    while ((s1 = bufferedreader.readLine()) != null) {
                        outputStream.println(s1);
                    }
                    outputStream.println("<p>");
                    outputStream.flush();
                } catch (java.io.FileNotFoundException filenotfoundexception) {
                    outputStream.println("Error Opening: " + mediaLog + " "
                            + filenotfoundexception);
                } catch (java.io.IOException ioexception) {
                    outputStream.println("Error reading: " + mediaLog + " "
                            + ioexception);
                }
                outputStream.flush();
            } else {
                outputStream.println("Player in Error");
                try {
                    java.io.BufferedReader bufferedreader1 = new BufferedReader(
                            new FileReader(mediaLog + "_"));
                    java.lang.String s2;
                    while ((s2 = bufferedreader1.readLine()) != null) {
                        outputStream.println(s2);
                    }
                } catch (java.io.FileNotFoundException filenotfoundexception1) {
                    outputStream
                            .println("File Not Found Exception occurrred while reading error log file.");
                } catch (java.io.IOException ioexception1) {
                    outputStream
                            .println("I/O Exception occurred while reading error log file.");
                }
            }
            outputStream.println("<br><h4><u>Player Log Data</u></h4>");
            try {
                java.io.BufferedReader bufferedreader2 = new BufferedReader(
                        new FileReader(mediaLog + "_"));
                java.lang.String s3;
                while ((s3 = bufferedreader2.readLine()) != null) {
                    outputStream.println(s3);
                }
                outputStream.println("<p>");
                outputStream.flush();
            } catch (java.io.FileNotFoundException filenotfoundexception2) {
                outputStream.println("Error Opening: " + mediaLog + " "
                        + filenotfoundexception2);
            } catch (java.io.IOException ioexception2) {
                outputStream.println("Error reading: " + mediaLog + " "
                        + ioexception2);
            }
            outputStream.flush();
            java.io.File file = new File(mediaLog);
            if (file != null) {
                try {
                    file.delete();
                } catch (java.lang.SecurityException securityexception) {
                    outputStream
                            .println("RealMediaPlayerMonitor Security Exception caught deleting temp file: "
                                    + mediaLog);
                }
            } else {
                outputStream
                        .println("RealMediaPlayerMonitor Error deleting temp file: "
                                + mediaLog);
            }
            file = new File(mediaLog);
            if (file != null) {
                try {
                    file.delete();
                } catch (java.lang.SecurityException securityexception1) {
                    outputStream
                            .println("RealMediaPlayerMonitor Security Exception caught deleting temp file: "
                                    + mediaLog);
                }
            } else {
                outputStream
                        .println("RealMediaPlayerMonitor Error deleting temp file: "
                                + mediaLog);
            }
        } catch (java.lang.Exception exception) {
            outputStream.println("Exception: " + exception);
        }
        outputStream.println("<p><b>Press Browser Back Key to Continue...</b>");
        outputStream.println("</pre>");
        outputStream.flush();
    }

}
