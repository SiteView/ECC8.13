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

import java.io.File;

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequestException;
import com.dragonflow.Utils.Braf;

// Referenced classes of package com.dragonflow.Page:
// CGI

public class snmpTrapLogPage extends com.dragonflow.Page.CGI
{

    public snmpTrapLogPage()
    {
    }

    public void printBody()
        throws Exception
    {
        if(!request.actionAllowed("_tools"))
        {
            throw new HTTPRequestException(557);
        }
        String s = request.getValue("records");
        String s1 = request.getValue("match");
        printBodyHeader("SNMP Trap Log");
        printButtonBar("SNMPTrapLog.htm", "");
        String s2 = com.dragonflow.StandardMonitor.SNMPTrapMonitor.listenerStatus;
        if(com.dragonflow.StandardMonitor.SNMPTrapMonitor.listenerError != null)
        {
            s2 = s2 + "<br>(" + com.dragonflow.StandardMonitor.SNMPTrapMonitor.listenerError + ")";
        }
        outputStream.println("<p>\n<CENTER><H2>" + s2 + "</H2></CENTER><P>\n" + "<p>\n" + getPagePOST("snmpTrapLog", "") + "The SNMP Trap Log tool allows you to view the log of SNMP Traps received by SiteView.\n" + "<p>\n");
        outputStream.println("<TABLE BORDER=0>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Traps To Show:</TD><TD><input type=text name=records value=\"" + s + "\" size=10></TD></TR>\n" + "<TR><TD></TD><TD><FONT SIZE=-1>The number of SNMP Traps to list - the most recent SNMP Traps are displayed " + "The default is 10.</FONT></TD></TR>");
        outputStream.println("<TR><TD ALIGN=RIGHT>Content Match:</TD><TD><input type=text name=match value=\"" + s1 + "\" size=30></TD></TR>\n" + "<TR><TD></TD><TD><FONT SIZE=-1>Optional, only show the traps that match the text or regular expression entered</FONT></TD></TR>");
        outputStream.println("</TABLE>");
        outputStream.println("<p>\n<input type=submit value=\"Show SNMP Trap Log Entries\">\n</FORM>\n");
        if(!isPortalServerRequest())
        {
            printContentStartComment();
            int i = com.dragonflow.Utils.TextUtils.toInt(request.getValue("records"));
            if(i <= 0)
            {
                i = 10;
            }
            jgl.Array array = new Array();
            int j = 0;
            String s4 = com.dragonflow.StandardMonitor.SNMPTrapMonitor.getLogPath();
            java.io.File file = new File(s4);
            if(file.exists())
            {
                long l = file.length();
                long l1 = 200L;
                long l2 = l - (long)i * l1;
                if(l2 < 0L)
                {
                    l2 = 0L;
                }
                com.dragonflow.Utils.Braf braf = new Braf(s4, l2);
                String s5 = braf.readLine();
                if(s5 != null)
                {
                    do
                    {
                        String s6 = braf.readLine();
                        if(s6 == null)
                        {
                            break;
                        }
                        j++;
                        if(com.dragonflow.Utils.TextUtils.match(s6, s1))
                        {
                            array.add(s6);
                        }
                    } while(true);
                }
                braf.close();
            }
            if(j > i)
            {
                j = i;
            }
            int k = array.size();
            if(k > i)
            {
                k = i;
            }
            if(k != j)
            {
                outputStream.println("<h3>SNMP Trap Log (matched " + k + " of " + j + " traps)</h3>");
            } else
            {
                outputStream.println("<h3>SNMP Trap Log (" + j + " traps)</h3>");
            }
            printTraps(array, i, outputStream);
            printContentEndComment();
        } else
        {
            com.dragonflow.SiteView.PortalSiteView portalsiteview = (com.dragonflow.SiteView.PortalSiteView)getSiteView();
            if(portalsiteview != null)
            {
                String s3 = portalsiteview.getURLContentsFromRemoteSiteView(request, "_centrascopeToolMatch");
                outputStream.println(s3);
            }
        }
        printFooter(outputStream);
    }

    void printTraps(jgl.Array array, int i, java.io.PrintWriter printwriter)
    {
        printwriter.println("<table border=1 cellspacing=0><tr><th>Date<th>From<th>Message<th>Trap<th>Specific<th>OID<th>Agent<th>Community<th>Trap Time");
        jgl.Reversing.reverse(array);
        java.util.Enumeration enumeration = array.elements();
        int j = 0;
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            String s = (String)enumeration.nextElement();
            jgl.Array array1 = com.dragonflow.SiteView.Platform.split('\t', s);
            java.util.Enumeration enumeration1 = array1.elements();
            jgl.HashMap hashmap = new HashMap();
            int k = 0;
            do
            {
                if(!enumeration1.hasMoreElements())
                {
                    break;
                }
                String s1 = (String)enumeration1.nextElement();
                String s2 = "";
                String s3 = "";
                int l = s1.indexOf('=');
                if(l > 0)
                {
                    s2 = s1.substring(0, l);
                    s3 = s1.substring(l + 1);
                    if(s2.startsWith("var"))
                    {
                        s2 = "vars";
                    }
                    if(k == 0)
                    {
                        s2 = "date";
                    }
                } else
                if(k == 0)
                {
                    s2 = "date";
                    s3 = s1;
                }
                k++;
                if(s2.length() > 0)
                {
                    String s4 = com.dragonflow.Utils.TextUtils.getValue(hashmap, s2);
                    if(s4.length() > 0)
                    {
                        s3 = s4 + ", " + s3;
                    }
                    hashmap.put(s2, s3);
                }
            } while(true);
            printwriter.println("<tr><td>" + com.dragonflow.Utils.TextUtils.getValue(hashmap, "date") + "<td>" + com.dragonflow.Utils.TextUtils.getValue(hashmap, "from") + "<td>" + com.dragonflow.Utils.TextUtils.getValue(hashmap, "vars") + "<td>" + com.dragonflow.Utils.TextUtils.getValue(hashmap, "trap") + "<td>" + com.dragonflow.Utils.TextUtils.getValue(hashmap, "specific") + "<td>" + com.dragonflow.Utils.TextUtils.getValue(hashmap, "oid") + "<td>" + com.dragonflow.Utils.TextUtils.getValue(hashmap, "agent") + "<td>" + com.dragonflow.Utils.TextUtils.getValue(hashmap, "community") + "<td>" + com.dragonflow.Utils.TextUtils.getValue(hashmap, "traptime"));
        } while(++j < i);
        printwriter.println("</table>");
    }

    public static void main(String args[])
        throws java.io.IOException
    {
        com.dragonflow.Page.snmpTrapLogPage snmptraplogpage = new snmpTrapLogPage();
        if(args.length > 0)
        {
            snmptraplogpage.args = args;
        }
        snmptraplogpage.handleRequest();
    }
}
