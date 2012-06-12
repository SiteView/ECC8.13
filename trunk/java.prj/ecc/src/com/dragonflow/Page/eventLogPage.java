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

import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequestException;
import com.dragonflow.Utils.CommandLine;

// Referenced classes of package com.dragonflow.Page:
// CGI, pingPage

public class eventLogPage extends com.dragonflow.Page.CGI
{

    public eventLogPage()
    {
    }

    public void printBody()
        throws java.lang.Exception
    {
        if(!request.actionAllowed("_tools"))
        {
            throw new HTTPRequestException(557);
        }
        java.lang.String s = request.getValue("machine");
        java.lang.String s1 = request.getValue("records");
        java.lang.String s2 = request.getValue("logName");
        if(s2.length() == 0)
        {
            s2 = "System";
        }
        java.lang.String s3 = s2.equals("Application") ? " selected" : "";
        java.lang.String s4 = s2.equals("System") ? " selected" : "";
        java.lang.String s5 = s2.equals("Security") ? " selected" : "";
        java.lang.String s6 = s2.equals("Directory Service") ? " selected" : "";
        java.lang.String s7 = s2.equals("DNS") ? " selected" : "";
        java.lang.String s8 = s2.equals("File Replication Service") ? " selected" : "";
        s = com.dragonflow.Utils.TextUtils.keepChars(s, ".-_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\\");
        if(s.length() > 0 && !s.startsWith("\\"))
        {
            s = "\\\\" + s;
        }
        printBodyHeader("NT Event Log");
        printButtonBar("NTEvtLog.htm", "");
        outputStream.println("<p>\n<CENTER><H2>Event Log</H2></CENTER><P>\n<p>\n" + getPagePOST("eventLog", "") + "The Event Log tool allows you to view the last event entries in an event log.\n" + "<p>\n");
        outputStream.println("<TABLE BORDER=0>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Server Name:</TD><TD><input type=text name=machine value=\"" + s + "\" size=40></TD></TR>\n" + "<TR><TD></TD><TD><FONT SIZE=-1>By default, it will show the event log for this server.  To view the " + "event log on another NT server, enter the name of that server.  For example, \\\\TEST</FONT></TD></TR>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Event Log:</TD><TD><select size=1 name=logName>\n<option value=System " + s4 + ">System\n" + "<option value=Application " + s3 + ">Application\n" + "<option value=Security " + s5 + ">Security\n" + "<option value=\"Directory Service\" " + s6 + ">Directory Service\n" + "<option value=DNS " + s7 + ">DNS\n" + "<option value=\"File Replication Service\" " + s8 + ">File Replication Service\n" + "</select></TD></TR>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Entries To Show:</TD><TD><input type=text name=records value=\"" + s1 + "\" size=10></TD></TR>\n" + "<TR><TD></TD><TD><FONT SIZE=-1>The number of entries to list for this event log - the last entry shown is the last" + "entry in the log. The default is 10.</FONT></TD></TR>");
        outputStream.println("</TABLE>");
        outputStream.println("<p>\n<input type=submit value=\"Show Event Log Entries\">\n</FORM>\n");
        if(!isPortalServerRequest())
        {
            printContentStartComment();
            if(s2.indexOf("Directory") >= 0)
            {
                s2 = "Directory Service";
            } else
            if(s2.indexOf("File") >= 0)
            {
                s2 = "File Replication Service";
            }
            java.lang.String s9 = com.dragonflow.SiteView.Platform.perfexCommand(s) + " -elast " + "\"" + s2 + "\"";
            com.dragonflow.Utils.CommandLine commandline = new CommandLine();
            jgl.Array array = commandline.exec(s9);
            int i = commandline.getExitValue();
            int j = -1;
            java.util.Enumeration enumeration = array.elements();
            do
            {
                if(!enumeration.hasMoreElements())
                {
                    break;
                }
                java.lang.String s11 = (java.lang.String)enumeration.nextElement();
                if(s11.startsWith(com.dragonflow.StandardMonitor.NTEventLogMonitor.NEXT_RECORD_LABEL))
                {
                    j = com.dragonflow.Utils.TextUtils.toInt(s11.substring(com.dragonflow.StandardMonitor.NTEventLogMonitor.NEXT_RECORD_LABEL.length()));
                }
            } while(true);
            int k = com.dragonflow.Utils.TextUtils.toInt(request.getValue("records"));
            if(k <= 0)
            {
                k = 10;
            }
            int l = j - k;
            if(l < 1)
            {
                l = 1;
            }
            s9 = com.dragonflow.SiteView.Platform.perfexCommand(s) + " -elog " + s2 + " " + l;
            array = commandline.exec(s9);
            boolean flag = true;
            enumeration = array.elements();
            do
            {
                if(!enumeration.hasMoreElements())
                {
                    break;
                }
                java.lang.String s12 = (java.lang.String)enumeration.nextElement();
                int i1 = s12.indexOf("Could not open the " + s2 + " event log");
                if(i1 == -1)
                {
                    continue;
                }
                outputStream.println("<p>\nSiteView was not able to open the Event log. Please check SiteView's permissions.<p>\n");
                outputStream.println("<br><p>To monitor a remote NT server, the SiteView service has to run as a user who has permission to monitor the remote machine.&nbsp; (This is generally an administrator account and is the same permission needed to access a remote server using the PerfMon tool)<P><br><DT>To change the user SiteView runs as:</DT><DD>1) Open the Services control panel</DD><DD>2) Select the SiteView service and press the Startup... button</DD><DD>3) Choose the Log On As This Account radio button</DD><DD>4) Enter a username and password that has access to the remote server</DD><DD>5) Press the OK button to close the Startup... dialog</DD><DD>6) Press the Stop button to stop the SiteView service</DD><DD>7) Press the Start button to start the SiteView service</DD><DD>8) Press the Close button to close the Services control panel</DD><DD>9) Choose the Open SiteView item from the Programs section of the Start Menu.</DD>");
                flag = false;
                break;
            } while(true);
            i = commandline.getExitValue();
            if(flag)
            {
                printEvents(array, outputStream);
            }
            printContentEndComment();
        } else
        {
            com.dragonflow.SiteView.PortalSiteView portalsiteview = (com.dragonflow.SiteView.PortalSiteView)getSiteView();
            if(portalsiteview != null)
            {
                java.lang.String s10 = portalsiteview.getURLContentsFromRemoteSiteView(request, "_centrascopeToolMatch");
                outputStream.println(s10);
            }
        }
        printFooter(outputStream);
    }

    void printEvents(jgl.Array array, java.io.PrintWriter printwriter)
    {
        printwriter.println("<FONT SIZE=-1><TABLE><TH><TH>Date<TH>Time<TH>Source<TH>Event<TH>Cat<TH>Message");
        jgl.Reversing.reverse(array);
        java.util.Enumeration enumeration = array.elements();
        jgl.HashMap hashmap = new HashMap();
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            java.lang.String s = (java.lang.String)enumeration.nextElement();
            int i = s.indexOf(':');
            if(i != -1)
            {
                java.lang.String s1 = s.substring(0, i).trim();
                java.lang.String s2 = s.substring(i + 1).trim();
                hashmap.put(s1, s2);
                if(s1.equals("Time"))
                {
                    java.util.Date date = com.dragonflow.Utils.TextUtils.stringToDate(s2);
                    java.lang.String s3 = com.dragonflow.Utils.TextUtils.prettyDateTime(date);
                    int j = s3.indexOf(' ');
                    if(j >= 0)
                    {
                        s3 = s3.substring(0, j) + ":" + com.dragonflow.Utils.TextUtils.numberToString(date.getSeconds()) + s3.substring(j);
                    }
                    hashmap.put("Time", s3);
                    hashmap.put("Date", com.dragonflow.Utils.TextUtils.prettyDateDate(date));
                }
                if(s1.equals("Type"))
                {
                    hashmap.put("Color", "BGCOLOR=#6666ff");
                    if(s2.equals("Warning"))
                    {
                        hashmap.put("Color", "BGCOLOR=#ffff22");
                    } else
                    if(s2.equals("Error"))
                    {
                        hashmap.put("Color", "BGCOLOR=#ff6666");
                    } else
                    if(s2.equals("AuditFailure"))
                    {
                        hashmap.put("Color", "BGCOLOR=#ff6666");
                    }
                }
                if(s1.equals("Type"))
                {
                    printwriter.println("<TR><TD width=10 " + hashmap.get("Color") + ">&nbsp;" + "<TD>" + hashmap.get("Date") + "<TD>" + hashmap.get("Time") + "<TD>" + hashmap.get("Source") + "<TD>" + hashmap.get("ID") + "<TD>" + hashmap.get("Category") + "<TD><FONT SIZE=-2>" + hashmap.get("Message") + "</FONT>" + "</TR>\n");
                    hashmap = new HashMap();
                }
            }
        } while(true);
        printwriter.println("</TABLE></FONT>");
    }

    public static void main(java.lang.String args[])
        throws java.io.IOException
    {
        com.dragonflow.Page.pingPage pingpage = new pingPage();
        if(args.length > 0)
        {
            pingpage.args = args;
        }
        pingpage.handleRequest();
    }
}
