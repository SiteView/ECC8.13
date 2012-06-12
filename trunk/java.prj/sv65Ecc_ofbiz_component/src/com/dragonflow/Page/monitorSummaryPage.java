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

import jgl.Array;
import com.dragonflow.HTTP.HTTPRequestException;

// Referenced classes of package com.dragonflow.Page:
// CGI, treeControl

public class monitorSummaryPage extends com.dragonflow.Page.CGI
    implements jgl.BinaryPredicate
{

    static final int daySeconds = 0x15180;
    static final int hourSeconds = 3600;
    static final int minuteSeconds = 60;
    public static final int SORT_GROUP = 1;
    public static final int SORT_NAME = 2;
    public static final int SORT_MONITOR_TYPE = 3;
    public static final int SORT_UPDATE = 4;
    public static final int SORT_DEPENDS = 5;
    public static final String TAB_DELIMIT = "\t";
    public static final String COMMA_DELIMIT = ",";
    boolean sortOrder;
    int sortKey;
    int secondaryKey;

    public monitorSummaryPage()
    {
        sortOrder = false;
        sortKey = 2;
        secondaryKey = 1;
    }

    public static int toSeconds(int i, String s)
    {
        if(s.equals("days"))
        {
            return i * 0x15180;
        }
        if(s.equals("hours"))
        {
            return i * 3600;
        }
        if(s.equals("minutes"))
        {
            return i * 60;
        } else
        {
            return i;
        }
    }

    public com.dragonflow.Page.CGI.menus getNavItems(com.dragonflow.HTTP.HTTPRequest httprequest)
    {
        com.dragonflow.Page.CGI.menus menus1 = new CGI.menus();
        if(httprequest.actionAllowed("_browse"))
        {
            menus1.add(new CGI.menuItems("Browse", "browse", "", "page", "Browse Monitors"));
        }
        if(httprequest.actionAllowed("_preference"))
        {
            menus1.add(new CGI.menuItems("Remote UNIX", "machine", "", "page", "Add/Edit Remote UNIX/Linux profiles"));
            menus1.add(new CGI.menuItems("Remote NT", "ntmachine", "", "page", "Add/Edit Remote Win NT/2000 profiles"));
        }
        if(httprequest.actionAllowed("_tools"))
        {
            menus1.add(new CGI.menuItems("Tools", "monitor", "Tools", "operation", "Use monitor diagnostic tools"));
        }
        if(httprequest.actionAllowed("_progress"))
        {
            menus1.add(new CGI.menuItems("Progress", "Progress", "", "url", "View current monitoring progress"));
        }
        if(httprequest.actionAllowed("_browse"))
        {
            menus1.add(new CGI.menuItems("Summary", "monitorSummary", "", "page", "View current monitor settings"));
        }
        if(httprequest.actionAllowed("_reportAdhoc"))
        {
            menus1.add(new CGI.menuItems("Quick Report", "report", "adhoc", "operation", "Create an adhoc report"));
        }
        return menus1;
    }

    public String prettyFrequency(long l)
    {
        String s;
        if(l == 0L)
        {
            s = "";
        } else
        if(l % 0x15180L == 0L)
        {
            l /= 0x15180L;
            s = l + " days";
        } else
        if(l % 3600L == 0L)
        {
            l /= 3600L;
            s = l + " hours";
        } else
        if(l % 60L == 0L)
        {
            l /= 60L;
            s = l + " minutes";
        } else
        {
            s = l + " seconds";
        }
        if(l == 1L)
        {
            s = s.substring(0, s.length() - 1);
        }
        return s;
    }

    boolean columnMatch(String s, com.dragonflow.SiteView.AtomicMonitor atomicmonitor)
    {
        for(java.util.Enumeration enumeration = request.getValues("column"); enumeration.hasMoreElements();)
        {
            String s1 = (String)enumeration.nextElement();
            int i = s1.indexOf(' ');
            if(i != -1)
            {
                s1 = s1.substring(0, i);
            }
            String s2 = columnName(s1, atomicmonitor);
            if(s2.equals("Monitor"))
            {
                s2 = "Title";
            }
            if(s.startsWith(s2))
            {
                return true;
            }
        }

        return false;
    }

    String columnName(String s, com.dragonflow.SiteView.AtomicMonitor atomicmonitor)
    {
        if(s.equals("group"))
        {
            return "Group";
        }
        if(s.equals("_class"))
        {
            return "Type";
        }
        if(s.equals("_name"))
        {
            return "Monitor";
        }
        if(atomicmonitor != null)
        {
            com.dragonflow.Properties.StringProperty stringproperty = atomicmonitor.getPropertyObject(s);
            if(stringproperty != null)
            {
                return stringproperty.getLabel();
            }
        }
        return s;
    }

    /**
     * CAUTION: Decompiled by hand.
     */
    public void printBody()
        throws Exception
    {
        if(!request.actionAllowed("_browse"))
        {
            throw new HTTPRequestException(557);
        }
        sortKey = com.dragonflow.Page.monitorSummaryPage.sortType(request.getValue("sort"));
        if(request.getValue("sortorder").indexOf("desc") != -1)
        {
            sortOrder = true;
        } else
        {
            sortOrder = false;
        }
        String s = request.getValue("categorySelect");
        if(s.length() == 0)
        {
            s = com.dragonflow.SiteView.Monitor.ERROR_CATEGORY + com.dragonflow.SiteView.Monitor.WARNING_CATEGORY;
        }
        java.util.Enumeration enumeration = request.getValues("monitorTypeSelect");
        for(String s1 = ""; enumeration.hasMoreElements(); s1 = s1 + enumeration.nextElement()) { }
        boolean flag = request.getValue("showParameters").length() > 0;
        boolean flag1 = request.getValue("writeExport").length() > 0;
        String s2 = request.getValue("writeName");
        String s3 = request.getValue("writeType");
        String s4 = "</td><td>";
        if(s3.indexOf("comma") != -1)
        {
            s4 = ",";
        } else
        if(s3.indexOf("tab") != -1)
        {
            s4 = "\t";
        } else
        {
            s4 = "</td><td>";
        }
        String s5 = com.dragonflow.SiteView.Platform.productName + " Monitor Summary Report";
        printBodyHeader(s5);
        com.dragonflow.Page.CGI.menus menus1 = getNavItems(request);
        printButtonBar("MonitorDescription.htm", "", menus1);
        outputStream.println("<h2>" + s5 + "</h2>");
        jgl.Array array = new Array();
        if(s3.indexOf("html") != -1)
        {
            array.add("<h2>" + s5 + "</h2>\n\n");
        } else
        {
            array.add(s5 + s4 + "\r\n");
        }
        if(request.isPost() && com.dragonflow.Page.treeControl.notHandled(request))
        {
            jgl.Array array1 = getAllowedGroupIDs();
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            jgl.Array array2 = new Array();
            int i = 0;
            for(int j = 0; j < array1.size(); j++)
            {
                String s10 = (String)array1.at(j);
                boolean flag2 = true;
                java.util.Enumeration enumeration3 = request.getValues("_group");
                while(enumeration3.hasMoreElements())
                    {
                    String s11 = com.dragonflow.Utils.I18N.toDefaultEncoding((String)enumeration3.nextElement());
                    if(s11.equals("all"))
                    {
                        flag2 = false;
                    } else
                    if(com.dragonflow.Page.CGI.isRelated(s10, s11))
                    {
                        flag2 = false;
                    }
                } 
                
                if(flag2)
                {
                    continue;
                }
                com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s10);
                if(monitorgroup == null)
                {
                    continue;
                }
                java.util.Enumeration enumeration6 = monitorgroup.getMonitors();
                com.dragonflow.SiteView.Monitor monitor;
                while(enumeration6.hasMoreElements())
                        {
                        monitor = (com.dragonflow.SiteView.Monitor)enumeration6.nextElement();
                    if (monitor instanceof com.dragonflow.SiteView.SubGroup) {
                    i++;
                    array2.add(monitor);
                    }
                }

            jgl.Sorting.sort(array2, this);
            String s6 = request.getValue("tableWidth");
            if(s6.length() > 0)
            {
                s6 = " width=\"" + s6 + "\"";
            } else
            {
                s6 = " width=\"98%\"";
            }
            if(s3.indexOf("html") != -1 || !flag1)
            {
                array.add("<TABLE border=1 cellspacing=0" + s6 + ">\n");
            }
            StringBuffer stringbuffer1 = new StringBuffer();
            if(s3.indexOf("html") != -1)
            {
                stringbuffer1.append("<tr>\n");
            } else
            {
                stringbuffer1.append("\r\n");
            }
            java.util.Enumeration enumeration1 = array2.elements();
            com.dragonflow.SiteView.AtomicMonitor atomicmonitor = null;
            if(enumeration1.hasMoreElements())
            {
                atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)enumeration1.nextElement();
            }
            for(java.util.Enumeration enumeration4 = request.getValues("column"); enumeration4.hasMoreElements();)
            {
                String s12 = (String)enumeration4.nextElement();
                String s7 = "";
                int l = s12.indexOf(' ');
                if(l != -1)
                {
                    s7 = " width=\"" + s12.substring(l + 1) + "\"";
                    s12 = s12.substring(0, l);
                }
                if(s12.indexOf("_") != -1)
                {
                    s12 = s12.substring(1);
                }
                if(s3.indexOf("html") != -1 || !flag1)
                {
                    stringbuffer1.append("<TH" + s7 + ">" + columnName(s12, atomicmonitor) + "</TH>");
                } else
                {
                    stringbuffer1.append(columnName(s12, atomicmonitor) + s4);
                }
            }

            if(flag)
            {
                String s8 = request.getValue("paramWidth");
                if(s8.length() > 0)
                {
                    s8 = " width=\"" + s8 + "\"";
                }
                if(s3.indexOf("html") != -1 || !flag1)
                {
                    stringbuffer1.append("<TH" + s8 + ">Parameters</TH>");
                } else
                {
                    stringbuffer1.append("Parameters" + s4);
                }
            }
            if(s3.indexOf("html") != -1 || !flag1)
            {
                stringbuffer1.append("</tr>\n");
            } else
            {
                stringbuffer1.append("\n");
            }
            array.add(stringbuffer1.toString());
            StringBuffer stringbuffer2;
            
            java.util.Enumeration enumeration2 = array2.elements(); 
            while(enumeration2.hasMoreElements()) {
                stringbuffer2 = new StringBuffer();
                if(s3.indexOf("html") != -1 || !flag1)
                {
                    stringbuffer2.append("<tr>\n");
                } else
                {
                    stringbuffer2.append("");
                }
                com.dragonflow.SiteView.AtomicMonitor atomicmonitor1 = (com.dragonflow.SiteView.AtomicMonitor)enumeration2.nextElement();
                for(java.util.Enumeration enumeration5 = request.getValues("column"); enumeration5.hasMoreElements();)
                {
                    String s14 = (String)enumeration5.nextElement();
                    String s9 = "";
                    int j1 = s14.indexOf(' ');
                    if(j1 != -1)
                    {
                        s9 = " width=\"" + s14.substring(j1 + 1) + "\"";
                        s14 = s14.substring(0, j1);
                    }
                    if(s14.equals("group"))
                    {
                        if(s3.indexOf("html") != -1 || !flag1)
                        {
                            stringbuffer2.append("<TD" + s9 + ">" + CGI.getGroupFullName(com.dragonflow.Utils.I18N.toDefaultEncoding(atomicmonitor1.getOwner().getProperty(com.dragonflow.SiteView.AtomicMonitor.pID))) + "</TD>");
                        } else
                        {
                            stringbuffer2.append(CGI.getGroupFullName(com.dragonflow.Utils.I18N.toDefaultEncoding(atomicmonitor1.getOwner().getProperty(com.dragonflow.SiteView.AtomicMonitor.pID))) + s4);
                        }
                    } else
                    if(s14.equals("points"))
                    {
                        if(s3.indexOf("html") != -1 || !flag1)
                        {
                            stringbuffer2.append("<TD" + s9 + ">" + atomicmonitor1.getCostInLicensePoints() + "</TD>");
                        } else
                        {
                            stringbuffer2.append(atomicmonitor1.getCostInLicensePoints() + s4);
                        }
                    } else
                    if(s14.equals("_class"))
                    {
                        if(s3.indexOf("html") != -1 || !flag1)
                        {
                            stringbuffer2.append("<TD" + s9 + ">" + atomicmonitor1.getClassProperty("title") + "</TD>");
                        } else
                        {
                            stringbuffer2.append(atomicmonitor1.getClassProperty("title") + s4);
                        }
                    } else
                    if(s14.equals("_frequency"))
                    {
                        com.dragonflow.SiteView.AtomicMonitor _tmp = atomicmonitor1;
                        long l1 = atomicmonitor1.getPropertyAsLong(com.dragonflow.SiteView.AtomicMonitor.pFrequency);
                        if(s3.indexOf("html") != -1 || !flag1)
                        {
                            stringbuffer2.append("<TD" + s9 + ">" + prettyFrequency(l1) + "</TD>");
                        } else
                        {
                            stringbuffer2.append(prettyFrequency(l1) + s4);
                        }
                    } else
                    if(s14.equals("_disabled"))
                    {
                        if(atomicmonitor1.isDisabled())
                        {
                            if(s3.indexOf("html") != -1 || !flag1)
                            {
                                stringbuffer2.append("<TD" + s9 + ">disabled</TD>");
                            } else
                            {
                                stringbuffer2.append("disabled" + s4);
                            }
                        } else
                        if(s3.indexOf("html") != -1 || !flag1)
                        {
                            stringbuffer2.append("<TD" + s9 + ">&nbsp;</TD>");
                        } else
                        {
                            stringbuffer2.append(" " + s4);
                        }
                    } else
                    if(s14.equals("_schedule"))
                    {
                        com.dragonflow.SiteView.AtomicMonitor _tmp1 = atomicmonitor1;
                        String s16 = atomicmonitor1.getProperty(com.dragonflow.SiteView.AtomicMonitor.pSchedule);
                        if(s16.length() > 0)
                        {
                            int k1 = s16.indexOf("_id=");
                            if(k1 != -1)
                            {
                                String s18 = s16.substring(k1 + 4);
                                s16 = atomicmonitor1.getScheduleSettings(s18);
                                jgl.HashMap hashmap = com.dragonflow.Utils.TextUtils.stringToHashMap(s16);
                                s16 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_name");
                            }
                        }
                        if(s16.length() > 0)
                        {
                            if(s3.indexOf("html") != -1 || !flag1)
                            {
                                stringbuffer2.append("<TD" + s9 + ">" + s16 + "</TD>");
                            } else
                            {
                                stringbuffer2.append(s16 + s4);
                            }
                        } else
                        if(s3.indexOf("html") != -1 || !flag1)
                        {
                            stringbuffer2.append("<TD" + s9 + ">&nbsp;</TD>");
                        } else
                        {
                            stringbuffer2.append(" " + s4);
                        }
                    } else
                    if(s14.equals("_dependsOn"))
                    {
                        jgl.Array array4 = new Array();
                        jgl.Array array5 = new Array();
                        atomicmonitor1.getDependencies(array4, array5);
                        boolean flag3 = true;
                        StringBuffer stringbuffer5 = new StringBuffer();
                        for(int i2 = 0; i2 < array4.size(); i2++)
                        {
                            String s20 = (String)array4.at(i2);
                            String s21 = com.dragonflow.Page.monitorSummaryPage.getLogicalDependencyName(s20);
                            if(s21 == null)
                            {
                                continue;
                            }
                            if(!flag3)
                            {
                                if(s3.indexOf("html") != -1 || !flag1)
                                {
                                    stringbuffer5.append("<BR>");
                                } else
                                {
                                    stringbuffer5.append(" | ");
                                }
                            } else
                            {
                                flag3 = false;
                            }
                            stringbuffer5.append(s21);
                        }

                        if(s3.indexOf("html") != -1 || !flag1)
                        {
                            stringbuffer2.append("<TD" + s9 + ">" + stringbuffer5 + "</TD>");
                        } else
                        {
                            stringbuffer2.append(stringbuffer5.toString() + s4);
                        }
                    } else
                    {
                        String s17 = atomicmonitor1.getProperty(s14);
                        if(s3.indexOf("html") != -1 || !flag1)
                        {
                            if(s17.length() == 0)
                            {
                                s17 = "&nbsp;";
                            }
                            stringbuffer2.append("<TD" + s9 + ">" + s17 + "</TD>");
                        } else
                        {
                            if(s17.length() == 0)
                            {
                                s17 = " ";
                            }
                            stringbuffer2.append(s17 + s4);
                        }
                    }
                    
                    array.add(stringbuffer2.toString());
                }

                if(flag)
                {
                    String s15 = atomicmonitor1.createFromTemplate("<mainParameters>", false);
                    jgl.Array array3 = com.dragonflow.SiteView.Platform.split('\n', s15);
                    StringBuffer stringbuffer4 = new StringBuffer();
                    java.util.Enumeration enumeration7 = array3.elements();
                    while(enumeration7.hasMoreElements())
                        {
                        String s19 = (String)enumeration7.nextElement();
                        if(!columnMatch(s19, atomicmonitor1))
                        {
                            if(s3.indexOf("html") != -1 || !flag1)
                            {
                                stringbuffer4.append(com.dragonflow.Utils.TextUtils.escapeHTML(s19) + "<br>");
                            } else
                            {
                                stringbuffer4.append(com.dragonflow.Utils.TextUtils.escapeHTML(s19) + s4);
                            }
                        }
                    }
                    
                    if(stringbuffer4.length() == 0)
                    {
                        stringbuffer4.append(" ");
                    }
                    if(s3.indexOf("html") != -1 || !flag1)
                    {
                        stringbuffer2.append("<TD>" + stringbuffer4.toString() + "</TD>");
                    } else
                    {
                        stringbuffer2.append(stringbuffer4.toString() + s4);
                    }
                }
                if(s3.indexOf("html") != -1 || !flag1)
                {
                    stringbuffer2.append("</tr>\n");
                } else
                {
                    stringbuffer2.append("\n");
                }
            }
            }

            if(s3.equals("html") || !flag1)
            {
                array.add("</table>\n");
            }
            if(!flag1)
            {
                array.add("<p>Select a <A HREF=/SiteView/cgi/go.exe/SiteView?page=monitorSummary&account=" + request.getAccount() + ">new report</A></p>\n");
            }
            if(flag1)
            {
                String s13 = com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "htdocs" + java.io.File.separator + s2;
                try
                {
                    StringBuffer stringbuffer3 = new StringBuffer();
                    for(int i1 = 0; i1 < array.size(); i1++)
                    {
                        stringbuffer3.append(array.at(i1).toString());
                    }

                    com.dragonflow.Utils.FileUtils.writeFile(s13, stringbuffer3.toString());
                    if(!request.getAccount().equalsIgnoreCase("administrator"))
                    {
                        outputStream.println("<p align=\"center\"><b>Report written to:</b></p><p align=\"center\"><a href=\"/SiteView/accounts/" + request.getAccount() + "/htdocs/" + s2 + "\"><b>" + s13 + "</b></a></p>");
                    } else
                    {
                        outputStream.println("<p align=\"center\"><b>Report written to:</b></p><p align=\"center\"><a href=\"/SiteView/htdocs/" + s2 + "\"><b>" + s13 + "</b></a></p>");
                    }
                }
                catch(java.io.IOException ioexception)
                {
                    outputStream.println("\nReport export to: " + s13 + " failed: " + ioexception);
                }
            } else
            {
                for(int k = 0; k < array.size(); k++)
                {
                    outputStream.println(array.at(k));
                }

            }
        } else
        {
            outputStream.println("<FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST><input type=hidden name=\"page\" value=\"monitorSummary\"><input type=hidden name=\"account\" value=\"" + request.getAccount() + "\">" + "<input type=hidden name=\"operation\" value=\"show\">" + "<TABLE BORDER=\"0\">" + "<TR><TD><B>Report Subject(s)</B></TD><TD VALIGN=TOP>Select the items in the report</TD></TR>" + "<TR><TD><IMG SRC=/SiteView/htdocs/artwork/empty1111.gif WIDTH=25></TD>");
            if(com.dragonflow.Page.treeControl.useTree())
            {
                StringBuffer stringbuffer = new StringBuffer();
                com.dragonflow.Page.treeControl treecontrol = new treeControl(request, "_group", false);
                treecontrol.process("Groups", "", "To select several items, hold down the Control key (on most platforms) while clicking item names.", null, null, null, 2, this, stringbuffer);
                outputStream.println(stringbuffer + "<hr>");
            } else
            {
                outputStream.println("<TD><select multiple name=\"_group\" size=\"4\"><option selected value=\"all\">all groups" + getMonitorOptionsHTML("", "", 2) + "</select></TD></TR>" + "<TR><td><IMG SRC=\"/SiteView/htdocs/artwork/empty1111.gif\" HEIGHT=20 WIDTH=150></td>" + "<TD>To select several items, hold down the Control key (on most platforms) while clicking " + " item names.</TD></TR></TABLE><hr>");
            }
            outputStream.println("<TABLE BORDER=\"0\"><TR><TD><B>Display Columns</B></TD><TD VALIGN=TOP>Select the columns to display</TD></TR><TR><TR><TD><IMG SRC=/SiteView/htdocs/artwork/empty1111.gif WIDTH=25></TD><TD><select multiple name=\"column\" size=\"8\"><option selected value=\"group 120\">Group<option selected value=\"_name 300\">Monitor Title<option selected value=\"_class 120\">Monitor Type<option selected value=\"_frequency 80\">Frequency<option value=\"_dependsOn 120\">Depends On<option value=\"points 80\">Points<option value=\"_url 200\">URL<option value=\"_host 120\">Host<option value=\"_machine 80\">Machine<option value=\"_oid 80\">OID<option value=\"_disabled 80\">Disabled<option value=\"_schedule 80\">Schedule<option value=\"_errorFrequency 120\">Error Frequency<option value=\"_timeout 80\">Timeout<option value=\"_verifyError 80\">Verify Error<option value=\"_description 120\">Report Description<option value=\"_monitorDescription 120\">Monitor Description<option value=\"_username 120\">Username<option value=\"_proxy 200\">Proxy</select></TD></TR><TR><td><IMG SRC=/SiteView/htdocs/artwork/empty1111.gif HEIGHT=20 WIDTH=150></td><TD>To select several items, hold down the Control key (on most platforms) while clicking item names.</TD></TR></TABLE>");
            outputStream.println("<DL><DT><input type=checkbox name=showParameters><b>Show Parameters</b></DT><DD>Check this box to include a column of detailed monitor parameter settings.</DD></DL><hr>");
            outputStream.println("<TABLE BORDER=\"0\"><TR><TD><B>Sort By:</B></TD><TD VALIGN=TOP>Select the sort key for the report</TD></TR><TR><TD><IMG SRC=/SiteView/htdocs/artwork/empty1111.gif WIDTH=25></TD><TD><select name=\"sort\" size=\"3\"><option value=\"group\">Group<option value=\"_name\">Monitor Title<option selected value=\"_class\">Monitor Type<option value=\"_frequency\">Frequency<option value=\"_dependsOn\">Dependency</select></TD></TR><TR><td><IMG SRC=/SiteView/htdocs/artwork/empty1111.gif HEIGHT=20 WIDTH=150></td><td><input type=\"radio\" name=\"sortorder\" value=\"ascend\" checked>Ascending <br><input type=\"radio\" name=\"sortorder\" value=\"descend\">Descending </td></tr><TR><td><IMG SRC=/SiteView/htdocs/artwork/empty1111.gif HEIGHT=20 WIDTH=150></td><TD>Select one sort key and select the sort order.</TD></TR></TABLE><hr>");
            outputStream.println("<table border=\"0\"><tr><TD><input type=checkbox name=writeExport><b>Export to File</b></td><TD><IMG SRC=/SiteView/htdocs/artwork/empty1111.gif WIDTH=25></TD><TD>File Name:&nbsp;<input type=text name=\"writeName\" value=\"monSummary.csv\"></td><TD><IMG SRC=/SiteView/htdocs/artwork/empty1111.gif WIDTH=25></TD><TD>File Format:&nbsp;<select name=\"writeType\" size=\"1\"><option selected value=\"comma\">Comma-delimited (csv)<option value=\"tab\">Tab-delimited (txt)<option value=\"html\">HTML<!--option value=\"space\">Space-delimited (prn)--></select></TD></TR><tr><td colspan=\"3\">Check <b>Export to File</b> and enter a filename and format to have the report saved to text file.</td></tr></TABLE><hr>");
            outputStream.println("<input type=hidden name=\"paramWidth\" value=\"300\"><input type=hidden name=\"tableWidth\" value=\"640\"><input type=hidden name=\"categorySelect\" value=\"ALL\"></blockquote><input type=submit value=\"Show Report\"></FORM>");
        }
        outputStream.println("<BR>&nbsp;<BR>&nbsp;<BR>");
        printFooter(outputStream);
    }

    private static String getLogicalDependencyName(String s)
    {
        String s1 = null;
        int i = s.indexOf(' ');
        if(i != -1)
        {
            String s2 = s.substring(i + 1);
            String s3 = s.substring(0, i);
            com.dragonflow.SiteView.SiteViewObject siteviewobject = com.dragonflow.SiteView.SiteViewGroup.currentSiteView().getElement(s3);
            if(s != null)
            {
                com.dragonflow.SiteView.SiteViewObject siteviewobject1 = siteviewobject.getElementByID(s2);
                if(siteviewobject1 != null)
                {
                    s1 = s3 + ":" + siteviewobject1.getProperty("_name");
                }
            }
        }
        return s1;
    }

    public void printCGIHeader()
    {
        request.printHeader(outputStream);
    }

    public void printCGIFooter()
    {
        outputStream.println("");
    }

    public static void main(String args[])
        throws java.io.IOException
    {
        com.dragonflow.Page.monitorSummaryPage monitorsummarypage = new monitorSummaryPage();
        if(args.length > 0)
        {
            monitorsummarypage.args = args;
        }
        monitorsummarypage.handleRequest();
    }

    public static int sortType(String s)
    {
        if(s.equals("group"))
        {
            return 1;
        }
        if(s.equals("_name"))
        {
            return 2;
        }
        if(s.equals("_class"))
        {
            return 3;
        }
        if(s.equals("_frequency"))
        {
            return 4;
        }
        return !s.equals("_dependsOn") ? 2 : 5;
    }

    public boolean execute(Object obj, Object obj1)
    {
        com.dragonflow.SiteView.Monitor monitor = null;
        com.dragonflow.SiteView.Monitor monitor1 = null;
        if(sortOrder)
        {
            monitor1 = (com.dragonflow.SiteView.Monitor)obj;
            monitor = (com.dragonflow.SiteView.Monitor)obj1;
        } else
        {
            monitor = (com.dragonflow.SiteView.Monitor)obj;
            monitor1 = (com.dragonflow.SiteView.Monitor)obj1;
        }
        int i = compareMonitors(monitor, monitor1, sortKey);
        if(i == 0)
        {
            i = compareMonitors(monitor, monitor1, secondaryKey);
        }
        return i > 0;
    }

    public int compareMonitors(com.dragonflow.SiteView.Monitor monitor, com.dragonflow.SiteView.Monitor monitor1, int i)
    {
        int j = 0;
        switch(i)
        {
        case 1: // '\001'
            String s = com.dragonflow.Page.monitorSummaryPage.getGroupFullName(com.dragonflow.Utils.I18N.toDefaultEncoding(monitor1.getProperty(com.dragonflow.SiteView.Monitor.pGroupID)));
            j = s.compareTo(com.dragonflow.Page.monitorSummaryPage.getGroupFullName(com.dragonflow.Utils.I18N.toDefaultEncoding(monitor.getProperty(com.dragonflow.SiteView.Monitor.pGroupID))));
            break;

        case 2: // '\002'
            String s1 = monitor1.getProperty(com.dragonflow.SiteView.Monitor.pName).toLowerCase();
            String s2 = monitor.getProperty(com.dragonflow.SiteView.Monitor.pName).toLowerCase();
            j = s1.compareTo(s2);
            break;

        case 3: // '\003'
            String s3 = monitor1.getProperty(com.dragonflow.SiteView.AtomicMonitor.pClass).toLowerCase();
            j = s3.compareTo(monitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pClass).toLowerCase());
            break;

        case 4: // '\004'
            String s4 = monitor1.getProperty(com.dragonflow.SiteView.AtomicMonitor.pFrequency);
            j = s4.compareTo(monitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pFrequency));
            break;

        case 5: // '\005'
            String s5 = monitor1.getProperty(com.dragonflow.SiteView.AtomicMonitor.pDependsOn);
            j = s5.compareTo(monitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pDependsOn));
            break;
        }
        return j;
    }
}
