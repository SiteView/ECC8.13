/**
 * 
 * Created on 2005-3-9 22:12:36
 *
 * managePage.java
 *
 * History:
 *
 */
package com.dragonflow.Page;

import java.io.File;
import java.io.PrintWriter;
import java.util.Date;
import java.util.Hashtable;

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequestException;
import com.dragonflow.Properties.HashMapOrdered;
import com.dragonflow.SiteView.SampleCollector;
import com.dragonflow.SiteView.SiteViewLogReader;

// Referenced classes of package com.dragonflow.Page:
// CGI, treeControl, monitorPage, portalPreferencePage,
// portalServerPage

public class managePage extends com.dragonflow.Page.CGI
{

    private com.dragonflow.SiteView.Monitor infoMonitor;
    private jgl.HashMap infoState;
    private com.dragonflow.SiteView.MonitorGroup infoGroup;
    private static final String DISABLE_OP = "Disable";
    private static final String ENABLE_OP = "Enable";
    private static final String TEMP_ALERT_DISABLE_CHOICE = "tenp_alert_disable_choice";
    private static final String ALERT_TEMP_DISABLE_TIMED = "timed_alert_disable";
    private static final String ALERT_TEMP_DISABLE_SCHEDULED = "scheduled_alert_disable";
    private static final String UNDO_ALERT_TEMP_DISABLE = "undo_temp_alert_disable";
    private static final String DISABLE_ALERT_TIME = "disable_alert_time";
    private static final String DISABLE_ALERT_UNITS = "disable_alert_units";
    private static final String DISABLE_CHOICE = "disable_choice";
    private static final String PERMANENT_DISABLE = "permanent_disable";
    private static final String TIMED_DISABLE = "timed_disable";
    private static final String SCHEDULED_DISABLE = "scheduled_disable";
    private static final String UNDO_DISABLE = "undo_disable";
    private static final String ENABLE_TEMP_ONLY = "enable_temp_only";
    private static final String ENABLE_TEMP_ALERTS_ONLY = "enable_temp_alerts_only";
//    public static final String TOPAZ_LOGGING_OP = com.dragonflow.SiteView.TopazInfo.getTopazNameShort() + " Logging Options";
    public static boolean debug = false;
    static jgl.HashMap EXCLUDE_MAP;
    jgl.HashMap groups;
    public static String OPEN_VARIABLE = "open";
    public static String CLOSE_VARIABLE = "close";
    int groupCount;

    public managePage()
    {
        groups = new HashMap();
        groupCount = 0;
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
        return menus1;
    }

    String[] getReplaces()
    {
        String as[] = new String[0];
        String s = request.getValue("find");
        String s1 = request.getValue("replace");
        if(s.length() > 0)
        {
            as = new String[2];
            as[0] = s;
            as[1] = s1;
            com.dragonflow.SiteView.Machine machine = com.dragonflow.SiteView.Machine.getMachineByName(s);
            if(machine != null)
            {
                com.dragonflow.SiteView.Machine machine1 = com.dragonflow.SiteView.Machine.getMachineByName(s1);
                if(machine1 != null)
                {
                    as = new String[6];
                    as[0] = s;
                    as[1] = com.dragonflow.SiteView.Machine.REMOTE_PREFIX + machine.getProperty(com.dragonflow.SiteView.Machine.pID);
                    as[2] = machine.getProperty(com.dragonflow.SiteView.Machine.pHost);
                    as[3] = s1;
                    as[4] = com.dragonflow.SiteView.Machine.REMOTE_PREFIX + machine1.getProperty(com.dragonflow.SiteView.Machine.pID);
                    as[5] = machine1.getProperty(com.dragonflow.SiteView.Machine.pHost);
                }
            }
        } else
        {
            as = new String[0];
        }
        return as;
    }

    String getTimedDisable(String s)
    {
        String s1 = "";
        String s2 = "";
        String s5 = "";
        if(s.equals("timed_disable"))
        {
            if(request.getValue("disableTime").length() > 0)
            {
                long l = com.dragonflow.Utils.TextUtils.toLong(request.getValue("disableTime"));
                long l2 = com.dragonflow.SiteView.Platform.timeMillis();
                if(l > 0L)
                {
                    String s8 = request.getValue("disableUnits");
                    if(s8.equals("minutes"))
                    {
                        l *= com.dragonflow.Utils.TextUtils.MINUTE_SECONDS;
                    } else
                    if(s8.equals("hours"))
                    {
                        l *= com.dragonflow.Utils.TextUtils.HOUR_SECONDS;
                    } else
                    if(s8.equals("days"))
                    {
                        l *= com.dragonflow.Utils.TextUtils.DAY_SECONDS;
                    }
                    String s3 = com.dragonflow.Utils.TextUtils.dateToString(l2);
                    String s6 = com.dragonflow.Utils.TextUtils.dateToString(l2 + l * 1000L);
                    s1 = s3 + ";" + s6;
                }
            }
        } else
        if(s.equals("scheduled_disable"))
        {
            long l1 = com.dragonflow.Utils.TextUtils.toLong(request.getUserSetting("_timeOffset")) * 1000L;
            long l3 = com.dragonflow.Utils.TextUtils.dateStringToSeconds(request.getValue("startTimeDate"), request.getValue("startTimeTime"));
            long l4 = com.dragonflow.Utils.TextUtils.dateStringToSeconds(request.getValue("endTimeDate"), request.getValue("endTimeTime"));
            String s4 = com.dragonflow.Utils.TextUtils.dateToString(l3 * 1000L - l1);
            String s7 = com.dragonflow.Utils.TextUtils.dateToString(l4 * 1000L - l1);
            s1 = s4 + ";" + s7;
        }
        return s1;
    }

    String getAlertTimedDisable()
    {
        String s = "";
        String s1 = "";
        if(request.getValue("alertDisableDescription").length() > 0)
        {
            s1 = "*" + request.getValue("alertDisableDescription");
        }
        String s2 = request.getValue("tenp_alert_disable_choice");
        if(s2.equals("timed_alert_disable"))
        {
            long l = com.dragonflow.Utils.TextUtils.toLong(request.getValue("disable_alert_time"));
            if(l <= 0L)
            {
                return "";
            }
            if(l > 0L)
            {
                String s5 = request.getValue("disable_alert_units");
                if(s5.equals("minutes"))
                {
                    l *= com.dragonflow.Utils.TextUtils.MINUTE_SECONDS;
                } else
                if(s5.equals("hours"))
                {
                    l *= com.dragonflow.Utils.TextUtils.HOUR_SECONDS;
                } else
                if(s5.equals("days"))
                {
                    l *= com.dragonflow.Utils.TextUtils.DAY_SECONDS;
                }
                s = com.dragonflow.Utils.TextUtils.dateToString(com.dragonflow.SiteView.Platform.timeMillis() + l * 1000L);
            }
        } else
        if(s2.equals("scheduled_alert_disable"))
        {
            String s3 = request.getValue("startTimeDate");
            String s4 = request.getValue("startTimeTime");
            String s6 = request.getValue("endTimeDate");
            String s7 = request.getValue("endTimeTime");
            if(com.dragonflow.Utils.TextUtils.isDateStringValid(s3) && com.dragonflow.Utils.TextUtils.isTimeStringValid(s4) && com.dragonflow.Utils.TextUtils.isDateStringValid(s6) && com.dragonflow.Utils.TextUtils.isTimeStringValid(s7))
            {
                long l1 = com.dragonflow.Utils.TextUtils.toLong(request.getUserSetting("_timeOffset")) * 1000L;
                long l2 = com.dragonflow.Utils.TextUtils.dateStringToSeconds(s3, s4);
                long l3 = com.dragonflow.Utils.TextUtils.dateStringToSeconds(s6, s7);
                String s8 = com.dragonflow.Utils.TextUtils.dateToString(l2 * 1000L - l1);
                String s9 = com.dragonflow.Utils.TextUtils.dateToString(l3 * 1000L - l1);
                s = s8 + ";" + s9;
            }
        } else
        if(s2.equals("undo_temp_alert_disable"))
        {
            return "undo_temp_alert_disable";
        }
        s = s + s1;
        return s;
    }

    void printManageForm(String s)
        throws Exception
    {
        boolean flag = false;
        if(request.hasValue("needVerify"))
        {
            flag = true;
        }
        if(request.isGet())
        {
            flag = true;
        }
        if(!flag && com.dragonflow.Page.treeControl.notHandled(request))
        {
            doCommit(s);
        } else
        {
            doVerify(s);
        }
        printFooter(outputStream);
    }

    private boolean isAncestor(com.dragonflow.SiteView.MonitorGroup monitorgroup, com.dragonflow.SiteView.SiteViewGroup siteviewgroup, jgl.HashMap hashmap)
    {
        if(monitorgroup == null)
        {
            return false;
        }
        String s = com.dragonflow.Utils.I18N.toDefaultEncoding(monitorgroup.getProperty("_parent"));
        do
        {
            if(s.length() <= 0)
            {
                break;
            }
            com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(s);
            if(monitor == null)
            {
                break;
            }
            if(hashmap.get(s) != null)
            {
                return true;
            }
            s = com.dragonflow.Utils.I18N.toDefaultEncoding(monitor.getProperty("_parent"));
        } while(true);
        return false;
    }

    private com.dragonflow.SiteView.MonitorGroup findGroup(com.dragonflow.SiteView.Monitor monitor, com.dragonflow.SiteView.SiteViewGroup siteviewgroup)
    {
        if(monitor == null)
        {
            return null;
        }
        if(monitor instanceof com.dragonflow.SiteView.SubGroup)
        {
            String s = monitor.getProperty(com.dragonflow.SiteView.SubGroup.pGroup);
            monitor = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s);
            if(monitor == null)
            {
                return null;
            }
        } else
        if(!(monitor instanceof com.dragonflow.SiteView.MonitorGroup))
        {
            return null;
        }
        return (com.dragonflow.SiteView.MonitorGroup)monitor;
    }

    private int addToList(String s, com.dragonflow.SiteView.Monitor monitor, boolean flag, boolean flag1, int i, jgl.Array array, StringBuffer stringbuffer, 
            String s1)
    {
        boolean flag2 = false;
        if(monitor instanceof com.dragonflow.SiteView.MonitorGroup)
        {
            flag2 = true;
        }
        String s2 = flag2 ? "groupName" : "monitorName";
        String s3 = flag2 ? "group" : "monitor";
        String s4 = flag2 ? s : s1;
        String s5 = com.dragonflow.Page.managePage.getGroupFullName(com.dragonflow.Utils.I18N.toDefaultEncoding(s));
        String s6 = monitor.getProperty(com.dragonflow.SiteView.Monitor.pName);
        if(!flag2)
        {
            s5 = s5 + ": <B>" + s6 + "</B>";
        }
        if(flag)
        {
            if(flag1)
            {
                s6 = "Copy of " + s6;
            }
            s5 = s5 + "<TD><input type=text size=50 name=" + s2 + i + " value=\"" + s6 + "\"></TD>\n";
        }
        array.add(s5);
        stringbuffer.append("\n<INPUT TYPE=HIDDEN NAME=" + s3 + i + " VALUE=\"" + s4 + "\">");
        return ++i;
    }

    private void doVerify(String s)
        throws Exception
    {
        String s1 = com.dragonflow.Utils.I18N.toDefaultEncoding(request.getValue("toGroupID"));
        boolean flag = true;
        boolean flag1 = true;
        boolean flag2 = true;
        boolean flag3 = false;
        flag2 = request.actionAllowed("_alertTempDisable");
        boolean flag8 = request.getValue("fromDetail").equals("true");
        boolean flag4;
        boolean flag5;
        boolean flag6;
        boolean flag7;
        if(flag8)
        {
            flag3 = true;
            if(request.getValue("disabled").equals("true"))
            {
                flag4 = false;
                flag5 = true;
            } else
            {
                flag4 = true;
                flag5 = false;
            }
            if(flag2)
            {
                if(request.getValue("alertTempDisabled").equals("true"))
                {
                    flag6 = false;
                    flag7 = true;
                } else
                {
                    flag6 = true;
                    flag7 = false;
                }
            } else
            {
                flag6 = false;
                flag7 = false;
            }
        } else
        if(s.equals("Disable"))
        {
            flag3 = true;
            flag4 = true;
            flag5 = false;
            if(flag2)
            {
                flag6 = true;
                flag7 = false;
            } else
            {
                flag6 = false;
                flag7 = false;
            }
        } else
        if(s.equals("Enable"))
        {
            flag3 = true;
            flag4 = false;
            flag5 = true;
            if(flag2)
            {
                flag6 = false;
                flag7 = true;
            } else
            {
                flag6 = false;
                flag7 = false;
            }
        } else
        {
            flag4 = false;
            flag5 = false;
            flag6 = false;
            flag7 = false;
            flag6 = false;
            flag7 = false;
        }
        if(flag4 || flag5)
        {
            flag = request.actionAllowed("_groupDisable");
            flag1 = request.actionAllowed("_monitorDisable");
        }
        jgl.Array array = new Array();
        jgl.Array array1 = new Array();
        String s2 = "";
        if(request.getValue("_health").length() > 0)
        {
            s2 = s2 + "<input type=hidden name=_health value=true>\n";
        }
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        jgl.Array array2 = new Array();
        jgl.Array array3 = new Array();
        boolean flag9 = s.startsWith("Duplicate") || s.startsWith("Copy");
        boolean flag10 = s.startsWith("Duplicate");
        boolean flag11 = s.startsWith("Replace");
        if(s1.length() > 0)
        {
            array3.add(com.dragonflow.Utils.I18N.toNullEncoding(s1));
        }
        String s3 = "";
        String s4 = "";
        String s5 = "";
        String s6 = new String("");
        jgl.Array array4 = new Array();
        Object obj = null;
        if(com.dragonflow.Page.treeControl.useTree())
        {
            int i = 1;
            jgl.HashMap hashmap = new HashMap();
            jgl.Array array5 = new Array();
label0:
            do
            {
                String s12;
label1:
                do
                {
                    for(java.util.Enumeration enumeration3 = request.getVariables(); enumeration3.hasMoreElements();)
                    {
                        s12 = (String)enumeration3.nextElement();
                        if(!s12.startsWith("group"))
                        {
                            continue label1;
                        }
                        jgl.Array array6 = com.dragonflow.Utils.TextUtils.getMultipleValues(request.variables, s12);
                        int i2 = 0;
                        while(i2 < array6.size()) 
                        {
                            boolean flag13 = false;
                            int j3 = 0;
                            do
                            {
                                if(j3 >= array5.size())
                                {
                                    break;
                                }
                                String s29 = (String)array5.at(j3);
                                if(s29.equals(array6.at(i2)))
                                {
                                    flag13 = true;
                                    break;
                                }
                                j3++;
                            } while(true);
                            if(!flag13)
                            {
                                array5.add(array6.at(i2));
                            }
                            i2++;
                        }
                    }

                    break label0;
                } while(!s12.startsWith("monitor"));
                jgl.Array array7 = com.dragonflow.Utils.TextUtils.getMultipleValues(request.variables, s12);
                int j2 = 0;
                while(j2 < array7.size()) 
                {
                    boolean flag14 = false;
                    int k3 = 0;
                    do
                    {
                        if(k3 >= array5.size())
                        {
                            break;
                        }
                        String s30 = (String)array5.at(k3);
                        if(s30.equals(array7.at(j2)))
                        {
                            flag14 = true;
                            break;
                        }
                        k3++;
                    } while(true);
                    if(!flag14)
                    {
                        array5.add(array7.at(j2));
                    }
                    j2++;
                }
            } while(true);
            int j1 = 1;
            int k1 = 0;
            do
            {
                if(k1 >= array5.size())
                {
                    break;
                }
                com.dragonflow.SiteView.MonitorGroup monitorgroup = null;
                String s31 = (String)array5.at(k1);
                String s37 = com.dragonflow.HTTP.HTTPRequest.decodeString(s31);
                int k4 = s37.indexOf(' ');
                if(s31.equals("_master"))
                {
                    s2 = s2 + "<INPUT TYPE=HIDDEN NAME=group1 VALUE=" + com.dragonflow.HTTP.HTTPRequest.encodeString(s37) + ">";
                    i++;
                    array.add(s31);
                    break;
                }
                String s45 = null;
                if(k4 > 0)
                {
                    s45 = s31.substring(0, k4);
                } else
                {
                    s45 = new String(s31);
                }
                com.dragonflow.SiteView.Monitor monitor2 = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(com.dragonflow.Utils.I18N.toDefaultEncoding(s45));
                monitorgroup = findGroup(monitor2, siteviewgroup);
                if(monitorgroup == null || !isAncestor(monitorgroup, siteviewgroup, hashmap))
                {
                    com.dragonflow.SiteView.Monitor monitor1 = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(com.dragonflow.Utils.I18N.toDefaultEncoding(s37.replace(' ', '/')));
                    if(monitor1 != null)
                    {
                        com.dragonflow.SiteView.MonitorGroup monitorgroup1 = findGroup(monitor1, siteviewgroup);
                        StringBuffer stringbuffer1 = new StringBuffer();
                        s2 = s2 + "<INPUT TYPE=HIDDEN NAME=monitor VALUE=" + com.dragonflow.HTTP.HTTPRequest.encodeString(s37) + ">";
                        if(monitorgroup1 != null)
                        {
                            if(!isAncestor(monitorgroup1, siteviewgroup, hashmap))
                            {
                                s45 = monitorgroup1.getProperty(com.dragonflow.SiteView.SiteViewGroup.pGroupID);
                                hashmap.put(s45, "found");
                                i = addToList(s45, monitorgroup1, flag9, flag10, i, array, stringbuffer1, s31);
                                s3 = s3 + stringbuffer1.toString();
                                excludeAllSubGroups(monitorgroup1, array2);
                            }
                        } else
                        {
                            s6 = monitor1.getFullID();
                            String s49 = "SiteView/";
                            String s50 = s6.substring(s49.length(), s6.length());
                            s50 = com.dragonflow.Utils.TextUtils.replaceString(s50, "/", " ");
                            array4.add(monitor1);
                            s4 = monitor1.getProperty(com.dragonflow.SiteView.Monitor.pAcknowledgeComment);
                            j1 = addToList(s45, monitor1, flag9, flag10, j1, array1, stringbuffer1, s31);
                            s5 = s5 + stringbuffer1.toString();
                        }
                    }
                }
                k1++;
            } while(true);
        } else
        {
            java.util.Enumeration enumeration = request.getValues("monitor");
            int j = 1;
            do
            {
                if(!enumeration.hasMoreElements())
                {
                    break;
                }
                String s8 = (String)enumeration.nextElement();
                int l = s8.indexOf(' ');
                String s10 = "";
                String s13 = "";
                if(l >= 0)
                {
                    String s11 = s8.substring(0, l);
                    String s14 = s8.substring(l + 1);
                    if(array3.size() == 0)
                    {
                        array3.add(s11);
                    }
                    com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(com.dragonflow.Utils.I18N.toDefaultEncoding(s8.replace(' ', '/')));
                    if(monitor != null)
                    {
                        s6 = monitor.getFullID();
                        String s16 = "SiteView/";
                        String s23 = s6.substring(s16.length(), s6.length());
                        s23 = com.dragonflow.Utils.TextUtils.replaceString(s23, "/", " ");
                        array4.add(monitor);
                        s4 = monitor.getProperty(com.dragonflow.SiteView.Monitor.pAcknowledgeComment);
                        String s25 = com.dragonflow.Page.managePage.getGroupFullName(com.dragonflow.Utils.I18N.toDefaultEncoding(s11)) + ": <B>" + monitor.getProperty(com.dragonflow.SiteView.Monitor.pName) + "</B>";
                        if(flag9)
                        {
                            String s32 = monitor.getProperty(com.dragonflow.SiteView.Monitor.pName);
                            if(flag10)
                            {
                                s32 = "Copy of " + s32;
                            }
                            s25 = s25 + "<TD><input type=text size=50 name=monitorName" + j + " value=\"" + s32 + "\"></TD>\n";
                        }
                        array1.add(s25);
                        s5 = s5 + "\n<INPUT TYPE=HIDDEN NAME=monitor" + j + " VALUE=\"" + s8 + "\">";
                        j++;
                    }
                }
            } while(true);
            if(flag1)
            {
                s2 = s2 + s5;
            }
            s3 = "";
            enumeration = request.getValues("group");
            int k = 1;
            int i1 = -1;
            java.util.Hashtable hashtable = new Hashtable();
            java.util.Enumeration enumeration4 = request.getVariables();
            int l1 = 0;
            do
            {
                if(!enumeration4.hasMoreElements())
                {
                    break;
                }
                String s17 = (String)enumeration4.nextElement();
                if(s17.startsWith("group"))
                {
                    l1++;
                }
            } while(true);
            int k2 = 0;
            do
            {
                if(k2 >= l1)
                {
                    break;
                }
                String s24 = null;
                s24 = i1 != -1 ? request.getValue("group" + i1) : request.getValue("group");
                i1++;
                if(s24.length() > 0)
                {
                    k2++;
                    com.dragonflow.SiteView.MonitorGroup monitorgroup2;
                    if(!isPortalServerRequest())
                    {
                        monitorgroup2 = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(com.dragonflow.Utils.I18N.toDefaultEncoding(s24));
                    } else
                    {
                        monitorgroup2 = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(com.dragonflow.Utils.I18N.toDefaultEncoding(s24));
                    }
                    if(monitorgroup2 != null)
                    {
                        String s33 = com.dragonflow.Utils.I18N.toDefaultEncoding(monitorgroup2.getProperty("_parent"));
                        boolean flag15 = false;
                        do
                        {
                            if(s33.length() <= 0)
                            {
                                break;
                            }
                            com.dragonflow.SiteView.Monitor monitor3 = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(s33);
                            if(monitor3 == null)
                            {
                                break;
                            }
                            if(hashtable.containsKey(s33))
                            {
                                flag15 = true;
                                break;
                            }
                            s33 = com.dragonflow.Utils.I18N.toDefaultEncoding(monitor3.getProperty("_parent"));
                        } while(true);
                        if(!flag15)
                        {
                            hashtable.put(s24, enumeration);
                            if(array3.size() == 0)
                            {
                                array3.add(s24);
                            }
                            String s42 = com.dragonflow.Page.managePage.getGroupFullName(com.dragonflow.Utils.I18N.toDefaultEncoding(s24));
                            if(flag9)
                            {
                                String s46 = monitorgroup2.getProperty(com.dragonflow.SiteView.Monitor.pName);
                                if(flag10)
                                {
                                    s46 = "Copy of " + s46;
                                }
                                s42 = s42 + "<TD><input type=text size=50 name=groupName" + k + " value=\"" + s46 + "\"></TD>\n";
                            }
                            array.add(s42);
                            s3 = s3 + "\n<INPUT TYPE=HIDDEN NAME=group" + k + " VALUE=\"" + s24 + "\">";
                            k++;
                            excludeAllSubGroups(monitorgroup2, array2);
                        }
                    }
                }
            } while(true);
        }
        if(flag1)
        {
            s2 = s2 + s5;
        }
        if(flag)
        {
            s2 = s2 + s3;
        }
        if(flag5)
        {
            s = "Enable";
        } else
        if(flag4)
        {
            s = "Disable";
        }
        String s7 = "Item";
        boolean flag12 = true;
        if(array.size() == 0)
        {
            s7 = "Monitor";
            flag12 = false;
        } else
        if(array1.size() == 0)
        {
            s7 = "Group";
            flag12 = false;
        }
        if(array.size() + array1.size() > 1)
        {
            s7 = s7 + "s";
        }
        String s9 = s + " " + s7;
        printBodyHeader(s9);
        com.dragonflow.Page.CGI.menus menus1 = getNavItems(request);
        String as[] = com.dragonflow.Utils.TextUtils.split(s);
        String s15 = as[0].toLowerCase();
        if(s.startsWith("Acknowledge"))
        {
            printButtonBar("Group.htm#acknowledge", "", menus1);
        } else
        {
            printButtonBar("ManageMon.htm#" + s15, "", menus1);
        }
        if(s.equals("AcknowledgeClear"))
        {
            outputStream.println("<H3>Update Acknowledge on the " + s7 + ":</H3>");
        } else
        {
            outputStream.println("<H3>" + s + " the " + s7 + ":</H3>");
        }
        printMonitorGroupTable(s7, flag9, array, flag12, flag, array1, flag1);
        if(s.startsWith("Move") || s.startsWith("Duplicate") || s.startsWith("Copy"))
        {
            String s18 = "into";
            if(s.startsWith("Move"))
            {
                s18 = "to";
            }
            int i3 = 2;
            if(com.dragonflow.Page.treeControl.useTree())
            {
                StringBuffer stringbuffer = new StringBuffer();
                com.dragonflow.Page.treeControl treecontrol = new treeControl(request, "toGroupID", false, false);
                treecontrol.process(s18 + " Group ", "", "", null, null, null, i3, this, stringbuffer);
                outputStream.println(stringbuffer);
            } else
            {
                if(array1.size() == 0 && com.dragonflow.SiteView.Platform.isStandardAccount(request.getAccount()))
                {
                    i3 += 16;
                }
                outputStream.println("<P>" + s18 + " Group <select name=toGroupID size=1>" + getMonitorOptionsHTML(array3, array2, null, i3) + "</select>");
            }
        } else
        if(s.startsWith("Disable"))
        {
            String s19 = "";
            jgl.HashMap hashmap1 = getMasterConfig();
            s19 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_defaultDisableTime");
            int l3 = com.dragonflow.Utils.TextUtils.toInt(request.getUserSetting("_timeOffset"));
            String s34 = com.dragonflow.Page.managePage.getStartTimeHTML(l3);
            String s38 = com.dragonflow.Page.managePage.getEndTimeHTML(l3);
            java.util.Enumeration enumeration5 = getExistingSchedule(siteviewgroup);
            if(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_noPermanentDisable").length() == 0)
            {
                outputStream.println("<P><INPUT TYPE=RADIO NAME=disable_choice VALUE=permanent_disable>\nDisable permanently\n");
            }
            outputStream.println("<P><INPUT TYPE=RADIO NAME=disable_choice VALUE=scheduled_disable checked>\nDisable on a one-time schedule from " + s34 + " to " + s38 + "<P>Disable Description (optional) <INPUT TYPE=TEXT SIZE=50 NAME=disabledDescription>\n");
            if(enumeration5.hasMoreElements())
            {
                outputStream.print("<P><INPUT TYPE=RADIO NAME=disable_choice VALUE=undo_disable >\nUndo one-time schedule<BR><BR><P><font size = +1><B>Warning</B></font><BR><B>The following one-time schedules will be changed or deleted if you continue:</B>");
                do
                {
                    if(!enumeration5.hasMoreElements())
                    {
                        break;
                    }
                    String s47 = enumeration5.nextElement().toString();
                    if(!s47.equals(""))
                    {
                        outputStream.println("<DD>" + s47);
                    }
                } while(true);
            }
        } else
        if(s.startsWith("Baseline"))
        {
            String s20 = "5";
            outputStream.println("<P>Compute a fixed performance baseline using data from the last <INPUT TYPE=TEXT SIZE=2 NAME=baselineDays VALUE=" + s20 + "> days\n</p>" + "<p><b>Notes:</b> The monitor(s) must have accumulated data for " + " at least the interval specified here before a baseline becomes active.</p> ");
        } else
        if(s.startsWith("Acknowledge"))
        {
            outputStream.println("<SCRIPT  language=\"JavaScript\"><!--- Hide script from old browsers\nfunction doWin() {\n          homeWindow=window.open(\"/SiteView?page=AckLog&monitor=" + s6 + "\"," + "\"AcknowlegeLog\"," + "\"toolbar=0," + "location=0," + "directories=0," + "status=0," + "menubar=0," + "resizable=1," + "scrollbars=1," + "width=550,height=425\")" + "}// end hiding from old browsers -->" + "</SCRIPT>");
            if(s.equals("AcknowledgeClear"))
            {
                if(isPortalServerRequest() && request.getValue("comment").length() > 0)
                {
                    s4 = request.getValue("comment");
                }
                outputStream.println("<P>Acknowledge Comment <INPUT TYPE=TEXT SIZE=50 NAME=acknowledgeComment VALUE=\"" + s4 + "\"\n");
            } else
            {
                outputStream.println("<P>Acknowledge Comment <INPUT TYPE=TEXT SIZE=50 NAME=acknowledgeComment\n");
            }
            String s21 = "";
            jgl.HashMap hashmap2 = getMasterConfig();
            s21 = com.dragonflow.Utils.TextUtils.getValue(hashmap2, "_defaultDisableAlertTime");
            java.util.Enumeration enumeration1 = request.getValues("monitor");
            String s26 = new String("");
            if(enumeration1.hasMoreElements())
            {
                s26 = (String)enumeration1.nextElement();
            } else
            {
                java.util.Enumeration enumeration2 = request.getValues("group");
                if(enumeration2.hasMoreElements())
                {
                    s26 = (String)enumeration2.nextElement();
                }
            }
            if(s26.length() > 0)
            {
                getMonitorInfo(s26);
                if(infoState != null)
                {
                    Object obj1 = infoState.get("_alertDisabled");
                    if(obj1 != null)
                    {
                        String s39 = obj1.toString();
                        if(s39.length() > 0)
                        {
                            java.util.Date date1 = new Date();
                            if(s39.indexOf("*") >= 0)
                            {
                                s39 = s39.substring(0, s39.indexOf("*"));
                            }
                            if(s39.indexOf(";") >= 0)
                            {
                                s39 = s39.substring(s39.indexOf(";") + 1);
                            }
                            date1 = com.dragonflow.Utils.TextUtils.stringToDate(s39);
                            if(date1.getTime() > com.dragonflow.SiteView.Platform.timeMillis())
                            {
                                long l5 = (date1.getTime() - com.dragonflow.SiteView.Platform.timeMillis()) / 60000L;
                                s21 = String.valueOf(l5);
                            }
                        }
                    }
                }
            }
            if(isPortalServerRequest() && request.getValue("disableAlert").length() > 0)
            {
                String s35 = request.getValue("disableAlert");
                java.util.Date date = com.dragonflow.Utils.TextUtils.stringToDate(s35);
                if(date.getTime() > com.dragonflow.SiteView.Platform.timeMillis())
                {
                    long l4 = (date.getTime() - com.dragonflow.SiteView.Platform.timeMillis()) / 60000L;
                    s21 = String.valueOf(l4);
                }
            }
            String s36 = com.dragonflow.Utils.TextUtils.getValue(hashmap2, "_defaultDisableTime");
            if(s36.equals(""))
            {
                s36 = "60";
            }
            if(s21.equals(""))
            {
                s21 = s36;
            }
            if(request.actionAllowed("_alertTempDisable"))
            {
                outputStream.println("<p><P><INPUT TYPE=radio NAME=tenp_alert_disable_choice  VALUE=timed_alert_disable checked> Disable alerts for the next \n<INPUT TYPE=TEXT SIZE=5 NAME=disable_alert_time  VALUE=" + s21 + ">" + "\n<SELECT SIZE=1 NAME=" + "disable_alert_units" + " >" + "\n<OPTION>seconds<OPTION SELECTED>minutes<OPTION>hours<OPTION>days\n" + "</SELECT>");
                int j4 = com.dragonflow.Utils.TextUtils.toInt(request.getUserSetting("_timeOffset"));
                String s43 = com.dragonflow.Page.managePage.getStartTimeHTML(j4);
                String s48 = com.dragonflow.Page.managePage.getEndTimeHTML(j4);
                outputStream.println("<P>\n<INPUT TYPE=RADIO NAME=tenp_alert_disable_choice  VALUE=scheduled_alert_disable >\nDisable on a one-time schedule from " + s43 + " to " + s48 + "<P>\n<INPUT TYPE=RADIO NAME=" + "tenp_alert_disable_choice" + "  VALUE=" + "undo_temp_alert_disable" + ">\n" + "Undo one-time schedule\n" + "<P>\nAlert Disable Description (optional)" + "\n<INPUT TYPE=TEXT NAME=alertDisableDescription SIZE=50 VALUE=>");
            }
            String s40 = com.dragonflow.SiteView.Platform.getDirectoryPath("logs", request.getAccount());
            java.io.File file = new File(s40 + "/Operator.log");
            if(!file.exists())
            {
                outputStream.println("<p><p>Acknowledge Log<B>(Empty)</B>");
            } else
            {
                outputStream.println("<p><p><a href=\"javascript:void(0)\" onClick=\"doWin()\">View Acknowledge Log</a>");
            }
        }
        if(flag5)
        {
            outputStream.println("<P><input type=checkbox name=enable_temp_only>Only enable items that are temporarily disabled");
        }
        if(flag9)
        {
            outputStream.println("<p><HR><H3>Advanced Options</H3>");
        }
        if(flag9 || flag11)
        {
            outputStream.println("<P><TABLE BORDER=0><TR><TD ALIGN=RIGHT><B>Find</B></TD><TD><INPUT TYPE=text size=50 name=find></TD></TR><TR><TD ALIGN=RIGHT><B>Replace With</B></TD><TD><INPUT TYPE=text size=50 name=replace></TD></TR><TR><TD>&nbsp;<TD><FONT SIZE=-1>find and replace text in monitors and groups\n- for example, replace server1.mycompany.com with server2.mycompany.com, or replace \\\\SERVER1 with \\\\SERVER2</TD></TR></TABLE>");
        }
        if(s.equals("AcknowledgeClear"))
        {
            System.out.println("**** FIRST ACK Clear ****  getreturnURL = " + getReturnURL(true) + " and  request value = " + request.getValue("returnURL"));
            outputStream.println("<P><TABLE WIDTH=100% BORDER=0><TR><INPUT TYPE=HIDDEN NAME=operation VALUE=\"Acknowledge\"><INPUT TYPE=HIDDEN NAME=page VALUE=manage><INPUT TYPE=HIDDEN NAME=account VALUE=" + request.getAccount() + ">" + "<INPUT TYPE=HIDDEN NAME=returnURL VALUE=" + request.getValue("returnURL") + ">" + "<INPUT TYPE=HIDDEN NAME=returnLabel VALUE=\"" + request.getValue("returnLabel") + "\">" + s2 + "<TD WIDTH=6%></TD><TD WIDTH=41%><input type=submit VALUE=\"Update Acknowledge \"></FORM></TD>");
            outputStream.println("<FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST><INPUT TYPE=HIDDEN NAME=operation VALUE=\"" + s + "\">" + "<INPUT TYPE=HIDDEN NAME=page VALUE=manage>" + "<INPUT TYPE=HIDDEN NAME=account VALUE=" + request.getAccount() + ">" + "<INPUT TYPE=HIDDEN NAME=returnURL VALUE=" + request.getValue("returnURL") + ">" + "<INPUT TYPE=HIDDEN NAME=returnLabel VALUE=\"" + request.getValue("returnLabel") + "\">" + s2);
            if(flag2)
            {
                outputStream.println("<INPUT TYPE=HIDDEN NAME=enable_temp_alerts_only VALUE=\"true\">");
            }
            outputStream.println("<TD WIDTH=30%><input type=submit VALUE=\"Cancel Acknowledge \"></FORM></TD>");
        } else
        {
//            if(s.equals(TOPAZ_LOGGING_OP))
//            {
//                printMetricPerMinute(outputStream, array, array4);
//                printTopazLoggingOptions(outputStream, array, array4);
//                outputStream.println("<INPUT TYPE=HIDDEN NAME=page VALUE=manage><INPUT TYPE=HIDDEN NAME=account VALUE=" + request.getAccount() + ">" + "<INPUT TYPE=HIDDEN NAME=returnURL VALUE=" + request.getValue("returnURL") + ">" + "<INPUT TYPE=HIDDEN NAME=returnLabel VALUE=\"" + request.getValue("returnLabel") + "\">" + s2 + "<TR><TD WIDTH=6%></TD><TD WIDTH=30%><input type=submit name=operation VALUE=\"" + "Set Log Properties" + "\"></TD></TR>");
//            } else
            {
                if(s.startsWith("Delete"))
                {
                    for(int l2 = 0; l2 < array.size(); l2++)
                    {
                        if(((String)array.at(l2)).equalsIgnoreCase("Health"))
                        {
                            outputStream.println("<p><b>NOTE: Only the contents of the \"Health Group\" will be deleted by this operation. The \"Health Group\" will remain.<p>");
                        }
                    }

                }
                outputStream.println("<P><TABLE WIDTH=100% BORDER=0><TR><INPUT TYPE=HIDDEN NAME=operation VALUE=\"" + s + "\">" + "<INPUT TYPE=HIDDEN NAME=page VALUE=manage>" + "<INPUT TYPE=HIDDEN NAME=account VALUE=" + request.getAccount() + ">" + "<INPUT TYPE=HIDDEN NAME=returnURL VALUE=" + request.getValue("returnURL") + ">" + "<INPUT TYPE=HIDDEN NAME=returnLabel VALUE=\"" + request.getValue("returnLabel") + "\">" + s2 + "<TD WIDTH=6%></TD><TD WIDTH=30%><input type=submit VALUE=\"" + s + "\"></TD>");
            }
            outputStream.println("&nbsp");
        }
        outputStream.println("<TD ALIGN=RIGHT WIDTH=27%><b><A HREF=" + getReturnURL(false) + ">" + getReturnLabel() + "</A></b></TD><TD WIDTH=6%></TD>" + "</TR></TABLE></FORM>");
        String s22 = "";
        jgl.HashMap hashmap3 = getMasterConfig();
        s22 = com.dragonflow.Utils.TextUtils.getValue(hashmap3, "_defaultDisableAlertTime");
        if(flag6)
        {
            outputStream.println("<p><hr><P>\n<B><H3>Disable Alerts for the " + s7 + "</H3></B><br>\n");
            System.out.println("**** FOR DISABLE where getreturnURL = " + getReturnURL(true) + " and  request value = " + request.getValue("returnURL"));
            printMonitorGroupTable(s7, flag9, array, flag12, true, array1, true);
            outputStream.print("\n<FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST>\n<INPUT TYPE=HIDDEN NAME=operation VALUE=\"Disable\">\n<INPUT TYPE=HIDDEN NAME=page VALUE=manage>\n<INPUT TYPE=HIDDEN NAME=disableAlert VALUE=true>\n<INPUT TYPE=HIDDEN NAME=account VALUE=" + request.getAccount() + ">" + "\n<INPUT TYPE=HIDDEN NAME=returnURL VALUE=" + request.getValue("returnURL") + ">" + "\n<INPUT TYPE=HIDDEN NAME=returnLabel VALUE=\"" + request.getValue("returnLabel") + "\">\n" + s5 + s3);
            if(request.getValue("_health").length() > 0)
            {
                outputStream.print("<input type=hidden name=_health value=true>\n");
            }
            String s27 = com.dragonflow.Utils.TextUtils.getValue(hashmap3, "_defaultDisableTime");
            if(s27.equals(""))
            {
                s27 = "60";
            }
            if(s22.equals(""))
            {
                s22 = s27;
            }
            outputStream.println("<P>\n<INPUT TYPE=radio NAME=tenp_alert_disable_choice  VALUE=timed_alert_disable checked>\nDisable alerts for the next <INPUT TYPE=TEXT SIZE=5 NAME=disable_alert_time  VALUE=" + s22 + ">\n" + "<SELECT SIZE=1 NAME=" + "disable_alert_units" + " >\n" + "<OPTION>seconds<OPTION SELECTED>minutes<OPTION>hours<OPTION>days\n" + "</SELECT>");
            int i4 = com.dragonflow.Utils.TextUtils.toInt(request.getUserSetting("_timeOffset"));
            String s41 = com.dragonflow.Page.managePage.getStartTimeHTML(i4);
            String s44 = com.dragonflow.Page.managePage.getEndTimeHTML(i4);
            outputStream.println("<P>\n<INPUT TYPE=RADIO NAME=tenp_alert_disable_choice  VALUE=scheduled_alert_disable >\nDisable on a one-time schedule from " + s41 + " to " + s44 + "<P>\n<INPUT TYPE=RADIO NAME=" + "tenp_alert_disable_choice" + "  VALUE=" + "undo_temp_alert_disable" + " >\n" + "Undo one-time schedule\n" + "<P>\nAlert Disable Description (optional)" + "\n<INPUT TYPE=TEXT NAME=alertDisableDescription SIZE=50 VALUE=>");
            outputStream.println("<P><TABLE WIDTH=100% BORDER=0><TR><TD WIDTH=6%>&nbsp;</TD><TD WIDTH=41%><input type=submit VALUE=\"Disable Alerts\"></TD><TD WIDTH=6%>&nbsp;</TD><TD ALIGN=RIGHT WIDTH=41%><A HREF=" + getReturnURL(false) + ">" + getReturnLabel() + "</A></TD><TD WIDTH=6%></TD>" + "</TR></TABLE></FORM>");
        } else
        if(flag7)
        {
            String s28 = "";
            if(request.getValue("_health").length() > 0)
            {
                s28 = "<input type=hidden name=_health value=true>\n";
            }
            outputStream.println("<p><hr><P>\n<B><H3>Enable Alerts for the " + s7 + "</H3></B><br>\n");
            printMonitorGroupTable(s7, flag9, array, flag12, true, array1, true);
            outputStream.println("\n<FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST><P><input type=hidden name=enable_temp_alerts_only VALUE=true><b>Enable alerts that are temporarily disabled</b><P><TABLE WIDTH=100% BORDER=0><TR><INPUT TYPE=HIDDEN NAME=operation VALUE=Enable><INPUT TYPE=HIDDEN NAME=page VALUE=manage><INPUT TYPE=HIDDEN NAME=account VALUE=" + request.getAccount() + ">" + "<INPUT TYPE=HIDDEN NAME=returnURL VALUE=" + request.getValue("returnURL") + ">" + "<INPUT TYPE=HIDDEN NAME=returnLabel VALUE=\"" + request.getValue("returnLabel") + "\">" + s5 + s3 + s28 + "<TD WIDTH=6%></TD><TD WIDTH=30%><input type=submit VALUE=\"" + "Enable" + " " + s7 + "\"></FORM></TD>" + "</TR></TABLE></FORM>");
            outputStream.println("&nbsp");
            outputStream.println("<TD ALIGN=RIGHT WIDTH=27%><b><A HREF=" + getReturnURL(false) + ">" + getReturnLabel() + "</A></b></TD><TD WIDTH=6%></TD>" + "</TR></TABLE></FORM>");
        } else
        if(flag3)
        {
            outputStream.println("User does not have permission to enable/disable temporary alerts.");
            outputStream.println("<TD ALIGN=RIGHT WIDTH=27%><b><A HREF=" + getReturnURL(false) + ">" + getReturnLabel() + "</A></b></TD><TD WIDTH=6%></TD>" + "</TR></TABLE></FORM>");
        }
        if(isPortalServerRequest() && s.startsWith("Acknowledge"))
        {
            System.out.println("**** IN ACK return to previous, getReturnURL = " + getReturnURL(false) + " and  request value = " + request.getValue("returnURL"));
            outputStream.println("<TD ALIGN=RIGHT WIDTH=27%><b><A HREF=" + request.getValue("returnURL") + ">" + getReturnLabel() + "</A></b></TD><TD WIDTH=6%></TD>" + "</TR></TABLE></FORM>");
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param array
     */
    void completeGroupList(String s, jgl.Array array)
    {
        try
        {
            jgl.Array array1 = getGroupFrames(s);
            java.util.Enumeration enumeration = array1.elements();
            while (enumeration.hasMoreElements())
                {
                jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
                String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_class");
                if(s1.equals("SubGroup"))
                {
                    String s2 = com.dragonflow.Utils.I18N.toDefaultEncoding(com.dragonflow.Utils.TextUtils.getValue(hashmap, "_group"));
                    if(s2.length() != 0)
                    {
                        array.add(s2);
                        completeGroupList(s2, array);
                    }
                }
            } 
        }
        catch(Exception exception)
        {
            exception.printStackTrace();
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param atomicmonitor
     * @return
     */
    double getMonitorLoggingRate(com.dragonflow.SiteView.AtomicMonitor atomicmonitor)
    {
        double d = 0.0D;
        try {
        if(atomicmonitor == null || atomicmonitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pNotLogToTopaz).length() == 0 || atomicmonitor.isDisabled())
        {
            return 0.0D;
        }
		return 0.0D;
//        return com.dragonflow.SiteView.TopazAPI.getMonitorLogRate(atomicmonitor);
        }
        catch (Exception exception) {
        exception.printStackTrace();
        return 0.0D;
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param printwriter
     */
    void printBrowseFilterOptionForm(java.io.PrintWriter printwriter)
    {
        StringBuffer stringbuffer;
        java.util.Enumeration enumeration;
        jgl.Array array1;
        String s = "";
        if(request.getValue("monitorNameSelect").length() > 0)
        {
            s = request.getValue("monitorNameSelect");
        }
        String s1 = "";
        if(request.getValue("machineNameSelect").length() > 0)
        {
            s1 = request.getValue("machineNameSelect");
        }
        stringbuffer = new StringBuffer();
        stringbuffer.append("<FORM METHOD=GET ACTION=/SiteView/cgi/go.exe/SiteView><INPUT TYPE=HIDDEN NAME=page VALUE=manage><INPUT TYPE=HIDDEN NAME=account VALUE=" + request.getAccount() + ">");
        if(request.getValue("_health").length() > 0)
        {
            stringbuffer.append("<input type=hidden name=_health value=true>\n");
        }
        stringbuffer.append("<table border=\"0\" width=\"98%\" cellpadding=\"2\" cellspacing=\"0\">");
        stringbuffer.append("<tr><td align=\"left\"valign=\"top\" colspan=\"8\"><hr></td></tr><tr><td align=\"left\"valign=\"top\" colspan=\"8\"><b>Filter Settings:</b></td></tr>");
        stringbuffer.append("<tr><td align=\"right\" valign=\"top\">Match Name:</td><td align=\"left\"valign=\"top\"><input type=text name=monitorNameSelect size=15 value=\"" + s + "\"></td>");
        stringbuffer.append("<td align=\"right\" valign=\"top\">Match Machine:</td><td align=\"left\"valign=\"top\"><input type=text name=machineNameSelect size=15 value=\"" + s1 + "\"></td>");
        stringbuffer.append("<td align=\"right\" valign=\"top\">For Monitor Type: </td><td align=\"left\"valign=\"top\"><SELECT NAME=monitorTypeSelect><option value=\"\">All types</option>\n");
        jgl.Array array = com.dragonflow.Page.monitorPage.getMonitorClasses();
        enumeration = array.elements();
        array1 = _getUsedMonitorClasses();

        Class class1;
        while (enumeration.hasMoreElements())
        {
        class1 = (Class)enumeration.nextElement();
        com.dragonflow.SiteView.AtomicMonitor atomicmonitor;
        String s3;
        try
        {
        atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)class1.newInstance();
        s3 = request.getPermission("_monitorType", (String)atomicmonitor.getClassProperty("class"));
        if(s3.length() == 0)
        {
            s3 = request.getPermission("_monitorType", "default");
        }
        if(!s3.equals("hidden"))
        {
                String s4 = (String)atomicmonitor.getClassProperty("title");
                String s5 = (String)atomicmonitor.getClassProperty("class");
                if(array1.indexOf(s5) != -1)
                {
                    String s2 = "";
                    stringbuffer.append("<option value=" + s5 + s2 + ">" + s4 + "</option>\n");
                }
            }
        }
        catch(Exception exception)
        {
            System.out.println("Could not create instance of " + class1);
        }
        }
_L1:
        stringbuffer.append("</select></td>\n");
        stringbuffer.append("<td align=\"left\"valign=\"top\"><input type=submit name=operation VALUE=\"Apply Filter\"></td></tr></table></FORM>");
        printwriter.println(stringbuffer.toString());
        return;
    }

    void printTopazLoggingOptions(java.io.PrintWriter printwriter, jgl.Array array, jgl.Array array1)
    {
//        String s = "<p>";
//        int i = com.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazServerSettings().getTopazIntegrationVersion();
//        boolean flag = i >= 1;
//        s = s + "<TABLE><TR><TD><input type=radio name=\"logOptions\" value=\"notLogToTopaz\" checked></TD><TD ALIGN=LEFT><b>Do not report to " + com.dragonflow.SiteView.TopazInfo.getTopazName() + ".</b></TD></TR>\n";
//        s = s + "<TR><TD><input type=radio name=\"logOptions\" value=\"logToTopaz\" ></TD><TD ALIGN=LEFT>Report everything (all monitors and all measurements).</TD></TR>\n";
//        if(flag)
//        {
//            s = s + "<TR><TD><input type=radio name=\"logOptions\" value=\"logOnlyMonitorData\"></TD><TD ALIGN=LEFT>Report monitor level data (no measurements).</TD></TR>\n";
//            s = s + "<TR><TD><input type=radio name=\"logOptions\" value=\"logOnlyThresholdMeas\"></TD><TD ALIGN=LEFT>Report monitor level data and measurements with thresholds.</TD></TR>\n";
//            s = s + "<TR><TD><input type=radio name=\"logOptions\" value=\"onlyStatusChanges\"></TD><TD ALIGN=LEFT>Report status changes (no measurements).</TD</TR>";
//        }
//        s = s + "</table>\n";
//        printwriter.println(s);
    }

    void printMetricPerMinute(java.io.PrintWriter printwriter, jgl.Array array, jgl.Array array1)
    {
    }

    private void doCommit(String s)
    {
        String s1 = null;
        if(com.dragonflow.Page.treeControl.useTree())
        {
            s1 = com.dragonflow.HTTP.HTTPRequest.decodeString(com.dragonflow.Utils.I18N.toDefaultEncoding(request.getValue("toGroupID")));
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(com.dragonflow.Utils.I18N.toDefaultEncoding(s1.replace(' ', '/')));
            com.dragonflow.SiteView.MonitorGroup monitorgroup = findGroup(monitor, siteviewgroup);
            if(monitorgroup != null)
            {
                s1 = monitorgroup.getProperty(com.dragonflow.SiteView.SiteViewGroup.pGroupID);
            }
        } else
        {
            s1 = com.dragonflow.Utils.I18N.toDefaultEncoding(request.getValue("toGroupID"));
        }
        boolean flag = false;
        autoFollowPortalRefresh = false;
        printRefreshHeader(s + " Items", getReturnURL(false), 8);
        if(debug)
        {
            com.dragonflow.Utils.TextUtils.debugPrint("IS POST TO MANAGE PAGE");
        }
        printProgressMessage("<P><FONT SIZE=+1><B>" + s + "</B></FONT><P>");
        try
        {
            jgl.Array array = new Array();
            jgl.Array array1 = new Array();
            jgl.Array array2 = new Array();
            jgl.Array array3 = new Array();
            String s2 = "something";
            String s3 = "something";
            for(int i = 1; s2.length() > 0 || s3.length() > 0; i++)
            {
                s2 = request.getValue("group" + i);
                if(com.dragonflow.Page.treeControl.useTree())
                {
                    s2 = com.dragonflow.HTTP.HTTPRequest.decodeString(s2);
                }
                if(s2.length() > 0)
                {
                    array.add(s2);
                    array1.add(request.getValue("groupName" + i));
                }
                s3 = request.getValue("monitor" + i);
                if(com.dragonflow.Page.treeControl.useTree())
                {
                    s3 = com.dragonflow.HTTP.HTTPRequest.decodeString(s3);
                }
                if(s3.length() > 0)
                {
                    array2.add(s3);
                    array3.add(request.getValue("monitorName" + i));
                }
            }

            if(s.startsWith("Delete"))
            {
                jgl.Array array4 = new Array(com.dragonflow.Utils.I18N.toDefaultArray(array));
                com.dragonflow.SiteView.ConfigurationChanger.delete(array4, array2, request, outputStream);
            } else
            if(s.startsWith("Baseline"))
            {
                baselineMonitors(array2, array);
            } else
            if(s.startsWith("Replace") || s.startsWith("Disable") || s.startsWith("Enable") || s.startsWith("Refresh"))
            {
                boolean flag1 = request.getValue("disableAlert").equals("true");
                String s6 = "";
                String s8 = "";
                String s9 = "";
                if(s.startsWith("Disable"))
                {
                    s6 = "Disable";
                    s8 = request.getValue("disable_choice");
                    String s10 = request.getValue("tenp_alert_disable_choice");
                } else
                if(s.startsWith("Enable"))
                {
                    s6 = "Enable";
                } else
                if(s.startsWith("Refresh"))
                {
                    s6 = "Refresh";
                } else
                if(s.startsWith("Replace"))
                {
                    s6 = "Replace";
                }
                String as2[] = getReplaces();
                String s12 = "";
                String s15 = "";
                String s17 = "";
                if(s6.equals("Disable"))
                {
                    s17 = request.getValue("disabledDescription");
                    if(flag1)
                    {
                        s12 = getAlertTimedDisable();
                        if(s12.length() == 0)
                        {
                            com.dragonflow.Log.LogManager.log("RunMonitor", "Invalid date or time entered");
                            printProgressMessage("<HR><P><B>Invalid date or time entered");
                            s12 = "0";
                            flag = true;
                        }
                    }
                    if(s8.equals("permanent_disable"))
                    {
                        s15 = "";
                    } else
                    if(s8.equals("scheduled_disable"))
                    {
                        if(com.dragonflow.Utils.TextUtils.isDateStringValid(request.getValue("startTimeDate")) && com.dragonflow.Utils.TextUtils.isTimeStringValid(request.getValue("startTimeTime")) && com.dragonflow.Utils.TextUtils.isDateStringValid(request.getValue("endTimeDate")) && com.dragonflow.Utils.TextUtils.isTimeStringValid(request.getValue("endTimeTime")))
                        {
                            s15 = getTimedDisable(s8);
                        } else
                        {
                            com.dragonflow.Log.LogManager.log("RunMonitor", "Invalid date or time entered");
                            printProgressMessage("<HR><P><B>Invalid date or time entered</B><P><HR>");
                            s15 = "0";
                            flag = true;
                        }
                    } else
                    if(s8.equals("undo_disable"))
                    {
                        s15 = "0";
                    }
                } else
                if(s6.equals("Enable"))
                {
                    s15 = request.getValue("enable_temp_only");
                    s12 = request.getValue("enable_temp_alerts_only");
                }
                if(array2.size() > 0 && !flag)
                {
                    if(s15.equals("0"))
                    {
                        printProgressMessage("Undo schedule for monitor" + (array2.size() <= 1 ? "" : "s") + "<BR>");
                    } else
                    {
                        String s18 = "monitor";
                        if(request.getValue("tenp_alert_disable_choice").length() > 0 || request.getValue("enable_temp_alerts_only").equals("true"))
                        {
                            s18 = "alert";
                        }
                        printProgressMessage(s6 + " " + s18 + (array2.size() <= 1 ? "" : "s") + "<BR>");
                    }
                    for(int l = 0; l < array2.size(); l++)
                    {
                        String s20 = (String)array2.at(l);
                        performMonitorConfigChange(s20, s6, as2, s15, s12, s17);
                    }

                }
                if(array.size() > 0 && !flag)
                {
                    if(s15.equals("0"))
                    {
                        printProgressMessage("Undo schedule for group" + (array.size() <= 1 ? "" : "s") + "<BR>");
                    } else
                    {
                        printProgressMessage(s6 + " group" + (array.size() <= 1 ? "" : "s") + "<BR>");
                    }
                    for(int i1 = 0; i1 < array.size(); i1++)
                    {
                        String s21 = com.dragonflow.Utils.I18N.toDefaultEncoding((String)array.at(i1));
                        performGroupConfigChange(s21, s6, as2, s15, s12, s17);
                    }

                }
                if(!flag)
                {
                    saveGroups();
                }
            } else
            if(s.startsWith("Acknowledge"))
            {
                if(isPortalServerRequest())
                {
                    if(request.actionAllowed("_monitorAcknowledge"))
                    {
                        String s4 = acknowledgeFromPortal(s);
                        if(s4 != null)
                        {
                            printProgressMessage(s4);
                            syncWithSiteView();
                        } else
                        {
                            printProgressMessage("<FONT SIZE=+2><B>There was a problem with Acknowledge</B></FONT>");
                        }
                    } else
                    {
                        printProgressMessage("<FONT SIZE=+2><B>User does not have permission to acknowledge monitors</B></FONT>");
                    }
                } else
                {
                    String s5 = request.getValue("acknowledgeComment");
                    String s7 = getAlertTimedDisable();
                    String as1[] = getReplaces();
                    String s11 = request.getUsername();
                    if(s11.length() == 0)
                    {
                        s11 = request.getAccount();
                    }
                    if(array2.size() > 0)
                    {
                        printProgressMessage(s + " monitor" + (array2.size() <= 1 ? "" : "s") + "<BR>");
                        for(int j = 0; j < array2.size(); j++)
                        {
                            String s13 = (String)array2.at(j);
                            if(s7.length() > 0)
                            {
                                performMonitorConfigChange(s13, "Disable", as1, "", s7, "");
                            } else
                            {
                                getMonitorInfo(com.dragonflow.Utils.I18N.toNullEncoding(s13));
                                s7 = request.getValue("enable_temp_alerts_only");
                                if(infoMonitor != null)
                                {
                                    String s16 = infoMonitor.getProperty(com.dragonflow.SiteView.Monitor.pAcknowledgeAlertDisabled);
                                    if(s16.length() > 0)
                                    {
                                        performMonitorConfigChange(s13, "Enable", as1, "", s7, "");
                                    }
                                }
                            }
                            try
                            {
                                acknowledgeMonitor(s13, s11, request.remoteAddress, s5, s7, s.equals("Acknowledge"));
                                continue;
                            }
                            catch(Exception exception1)
                            {
                                printProgressMessage("<P><B>Error in Group" + exception1 + "</B><P>");
                            }
                            flag = true;
                        }

                    }
                    if(array.size() > 0)
                    {
                        printProgressMessage(s + " group" + (array.size() <= 1 ? "" : "s") + "<BR>");
                        for(int k = 0; k < array.size(); k++)
                        {
                            String s14 = com.dragonflow.Utils.I18N.toDefaultEncoding((String)array.at(k));
                            try
                            {
                                acknowledgeGroup(s14, s11, request.remoteAddress, s5, s7, s.equals("Acknowledge"));
                            }
                            catch(Exception exception2)
                            {
                                printProgressMessage("<P><B>Error in Group" + exception2 + "</B><P>");
                                flag = true;
                            }
                            if(s7.length() > 0)
                            {
                                performGroupConfigChange(s14, "Disable", as1, "", s7, "");
                            }
                            jgl.Array array5 = getGroupFrames(s14);
                            jgl.HashMap hashmap = (jgl.HashMap)array5.at(0);
                            String s19 = (String)hashmap.get("_parent");
                            if(s19 == null || s19.length() <= 0)
                            {
                                continue;
                            }
                            jgl.Array array6 = getGroupFrames(s19);
                            for(int j1 = 1; j1 < array6.size(); j1++)
                            {
                                jgl.HashMap hashmap1 = (jgl.HashMap)array6.at(j1);
                                String s22 = (String)hashmap1.get("_group");
                                if(s22 != null && s22.equals(s14))
                                {
                                    acknowledgeMonitor(s19 + " " + hashmap1.get("_id"), s11, request.remoteAddress, s5, s7, s.equals("Acknowledge"));
                                }
                            }

                        }

                    }
                    saveGroups();
                }
            } else
//            if(s.startsWith("Set") || s.equals(TOPAZ_LOGGING_OP))
//            {
//                if(com.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazServerSettings().isConnected())
//                {
//                    com.dragonflow.SiteView.ConfigurationChanger.change(s, array, array2, request, outputStream);
//                }
//            } else
            {
                boolean flag2 = s.startsWith("Move");
                String as[] = getReplaces();
                if(array.size() > 0)
                {
                    if(debug)
                    {
                        com.dragonflow.Utils.TextUtils.debugPrint(s + " GROUP(s) : ");
                    }
                    manageGroups(array, array1, s1, flag2, as);
                }
                if(array2.size() > 0)
                {
                    if(debug)
                    {
                        com.dragonflow.Utils.TextUtils.debugPrint(s + " MONITOR(s) : ");
                    }
                    manageMonitors(array2, array3, s1, flag2, as);
                }
            }
            if(flag)
            {
                printProgressMessage("<P><B>Error Found: " + s + " not completed</B><P>");
            } else
            {
                printProgressMessage("<P><B>Done</B><P>");
            }
            outputStream.println("<A HREF=" + getReturnURL(false) + ">" + getReturnLabel() + "</A><P>");
            outputStream.println("</BODY></HTML>");
        }
        catch(Exception exception)
        {
            exception.printStackTrace();
            printError("There was a problem with the " + s + ".", exception.toString(), "/SiteView/" + request.getAccountDirectory() + "/SiteView.html");
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @return
     */
    private boolean groupPassFilter(String s)
    {
        try {
        String s1 = request.getValue("monitorNameSelect");
        com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)com.dragonflow.SiteView.SiteViewGroup.cCurrentSiteView.getElementByID(s);
        if(s1.length() <= 0)
        {
            return false;
        }
        int i;
        String s2 = monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pName);
        jgl.Array array = new Array();
        i = com.dragonflow.Utils.TextUtils.matchExpression(s2, s1, array, new StringBuffer());
        if(i != com.dragonflow.SiteView.Monitor.kURLok)
        {
            i = com.dragonflow.Utils.TextUtils.matchExpression(s2, s1, array, new StringBuffer());
        }
        if(i != com.dragonflow.SiteView.Monitor.kURLok)
        {
            return false;
        }
        }
        catch (Exception exception) {
        exception.printStackTrace();
        }
        return true;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @return
     */
    private boolean monitorPassFilter(String s)
    {
        try {
        com.dragonflow.SiteView.AtomicMonitor atomicmonitor;
        int i = s.indexOf(' ');
        if(i >= 0)
        {
        String s1 = s.substring(0, i);
        String s2 = s.substring(i + 1);
        jgl.Array array = getGroupFrames(s1);
        jgl.HashMap hashmap = com.dragonflow.Page.CGI.findMonitor(array, s2);
        atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)com.dragonflow.SiteView.AtomicMonitor.createMonitor(hashmap, "");
        if(monitorPassFilter(atomicmonitor))
        {
            return true;
        }
        }
        }
        catch (Exception exception) {
        exception.printStackTrace();
        }
        return false;
    }

    private jgl.Array getFilteredGroupList()
    {
        boolean flag = true;
        jgl.Array array = new Array();
        if(request.getValue("monitorNameSelect").length() <= 0)
        {
            return array;
        }
        java.util.Enumeration enumeration = com.dragonflow.SiteView.SiteViewGroup.cCurrentSiteView.getMonitors();
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)enumeration.nextElement();
            String s = monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pID);
            if(groupPassFilter(s))
            {
                array.add(s);
            }
        } while(true);
        return array;
    }

    private void createFilteredMonitorList(com.dragonflow.SiteView.Monitor monitor, jgl.Array array)
    {
        try
        {
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            if(monitor != null)
            {
                java.util.Enumeration enumeration = monitor.getMonitors();
                do
                {
                    if(!enumeration.hasMoreElements())
                    {
                        break;
                    }
                    com.dragonflow.SiteView.Monitor monitor1 = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
                    if(monitor1 instanceof com.dragonflow.SiteView.SubGroup)
                    {
                        createFilteredMonitorList(monitor1, array);
                    } else
                    if(monitorPassFilter((com.dragonflow.SiteView.AtomicMonitor)monitor1))
                    {
                        array.add(monitor1);
                    }
                } while(true);
            }
        }
        catch(Exception exception)
        {
            exception.printStackTrace();
        }
    }

    private boolean monitorPassFilter(com.dragonflow.SiteView.AtomicMonitor atomicmonitor)
    {
        String s = request.getValue("monitorTypeSelect");
        String s1 = request.getValue("monitorNameSelect");
        String s2 = request.getValue("machineNameSelect");
        if(s1.length() > 0)
        {
            String s3 = atomicmonitor.getProperty(com.dragonflow.SiteView.Monitor.pName) + atomicmonitor.getProperty(com.dragonflow.SiteView.Monitor.pDescription);
            jgl.Array array = new Array();
            int i = com.dragonflow.Utils.TextUtils.matchExpression(s3, s1, array, new StringBuffer());
            if(i != com.dragonflow.SiteView.Monitor.kURLok)
            {
                i = com.dragonflow.Utils.TextUtils.matchExpression(s3, s1, array, new StringBuffer());
            }
            if(i != com.dragonflow.SiteView.Monitor.kURLok)
            {
                return false;
            }
        }
        if(s2.length() > 0)
        {
            String s4 = atomicmonitor.getHostname();
            jgl.Array array1 = new Array();
            int j = com.dragonflow.Utils.TextUtils.matchExpression(s4, s2, array1, new StringBuffer());
            if(j != com.dragonflow.SiteView.Monitor.kURLok)
            {
                j = com.dragonflow.Utils.TextUtils.matchExpression(s4, s2, array1, new StringBuffer());
            }
            if(j != com.dragonflow.SiteView.Monitor.kURLok)
            {
                return false;
            }
        }
        return s.length() <= 0 || s.indexOf((String)atomicmonitor.getClassProperty("class")) != -1;
    }

    private void printMonitorGroupTable(String s, boolean flag, jgl.Array array, boolean flag1, boolean flag2, jgl.Array array1, boolean flag3)
    {
        outputStream.print("<TABLE BORDER=1 cellspacing=0><TR CLASS=\"tabhead\"><TH>" + s + "</TH>" + "<FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST>");
        if(request.getValue("_health").length() > 0)
        {
            outputStream.print("<input type=hidden name=_health value=true>\n");
        }
        if(flag)
        {
            outputStream.print("<TH>New Name</TH>");
        }
        outputStream.println("</TR>");
        for(int i = 0; i < array.size(); i++)
        {
            String s1 = (String)array.at(i);
            outputStream.print("<TR><TD>");
            if(flag1)
            {
                outputStream.print("Group ");
            }
            if(s1.equals("_master"))
            {
                outputStream.print("All Groups and Monitors" + (flag2 ? "" : "<font color=red> Not Permitted</font>"));
            } else
            {
                outputStream.print((String)array.at(i) + (flag2 ? "" : "<font color=red> Not Permitted</font>"));
            }
            outputStream.println("</TD></TR>");
        }

        for(int j = 0; j < array1.size(); j++)
        {
            outputStream.print("<TR><TD>");
            if(flag1)
            {
                outputStream.print("Monitor ");
            }
            outputStream.print(array1.at(j) + (flag3 ? "" : "<font color=red> Not Permitted</font>"));
            outputStream.println("</TD></TR>");
        }

        outputStream.println("</TABLE>");
    }

    void excludeAllSubGroups(com.dragonflow.SiteView.Monitor monitor, jgl.Array array)
    {
        array.add(monitor.getProperty(com.dragonflow.SiteView.Monitor.pID));
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        java.util.Enumeration enumeration = monitor.getMonitors();
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            com.dragonflow.SiteView.Monitor monitor1 = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
            if(monitor1 instanceof com.dragonflow.SiteView.SubGroup)
            {
                com.dragonflow.SiteView.Monitor monitor2 = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(com.dragonflow.Utils.I18N.toDefaultEncoding(monitor1.getProperty(com.dragonflow.SiteView.SubGroup.pGroup)));
                if(monitor2 != null)
                {
                    excludeAllSubGroups(monitor2, array);
                }
            }
        } while(true);
    }

    private jgl.Array getGroupFrames(String s)
        throws Exception
    {
        jgl.Array array = (jgl.Array)groups.get(s);
        if(array == null)
        {
            array = com.dragonflow.Page.CGI.ReadGroupFrames(s, request);
            groups.put(s, array);
        }
        return array;
    }

    public void saveGroups()
        throws Exception
    {
        java.util.Enumeration enumeration = groups.keys();
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            String s = (String)enumeration.nextElement();
            jgl.Array array = (jgl.Array)groups.get(s);
            if(array != null)
            {
                printProgressMessage("Saving group configuration for " + com.dragonflow.Page.managePage.getGroupName(array, s) + "<BR>");
                WriteGroupFrames(s, array);
                if(debug)
                {
                    com.dragonflow.Utils.TextUtils.debugPrint("SAVED GROUP=" + s);
                }
            } else
            {
                System.out.println("TRIED TO SAVE OUT EMPTY GROUP=" + s);
            }
        } while(true);
        com.dragonflow.SiteView.SiteViewGroup.updateStaticPages();
        groups.clear();
    }

    boolean exceedsLicenseLimit(jgl.Array array, String s)
    {
        boolean flag = com.dragonflow.Utils.LUtils.wouldExceedLimit(array, s);
        if(flag)
        {
            String s1 = com.dragonflow.Utils.LUtils.getLicenseExceededHTML();
            outputStream.println(s1);
        }
        return flag;
    }

    public void manageMonitors(jgl.Array array, jgl.Array array1, String s, boolean flag, String as[])
        throws Exception
    {
        if(!flag)
        {
            if(exceedsLicenseLimit(array, null))
            {
                return;
            }
            if(request.getAccount().length() > 0 && com.dragonflow.SiteView.Platform.isSiteSeerAccount(request.getAccount()) && overMaximumMonitors(request.getAccount(), array.size()))
            {
                return;
            }
        }
        jgl.Array array2 = new Array();
        jgl.Array array3 = new Array();
        for(int i = 0; i < array.size(); i++)
        {
            String s1 = (String)array.at(i);
            String s2 = (String)array1.at(i);
            String s4 = s1.replace(' ', '/');
            array3.add(s4);
            if(debug)
            {
                com.dragonflow.Utils.TextUtils.debugPrint("MONITORSPEC=" + s1);
            }
            String s5 = "";
            String s6 = "";
            int l = s1.indexOf(' ');
            if(l < 0)
            {
                continue;
            }
            s5 = s1.substring(0, l);
            s6 = s1.substring(l + 1);
            if(flag && s5.equals(s))
            {
                if(debug)
                {
                    com.dragonflow.Utils.TextUtils.debugPrint("MOVING " + s1 + " TO SELF GROUP");
                }
                continue;
            }
            jgl.Array array5 = getGroupFrames(s5);
            int i1 = com.dragonflow.Page.managePage.findMonitorIndex(array5, s6);
            if(i1 < 1)
            {
                continue;
            }
            jgl.HashMap hashmap3 = (jgl.HashMap)array5.at(i1);
            if(flag)
            {
                if(debug)
                {
                    com.dragonflow.Utils.TextUtils.debugPrint("REMOVING MONITOR - INDEX=" + i1);
                }
                array5.remove(i1);
            } else
            {
                if(debug)
                {
                    com.dragonflow.Utils.TextUtils.debugPrint("COPYING MONITOR");
                }
                hashmap3 = com.dragonflow.Page.managePage.copyHashMap(hashmap3);
                hashmap3.put("_name", s2);
                hashmap3.remove(com.dragonflow.SiteView.AtomicMonitor.pUniqueInternalId.getName());
                if(as.length > 0 && com.dragonflow.SiteView.Monitor.isMonitorFrame(hashmap3))
                {
                    printProgressMessage(com.dragonflow.Utils.TextUtils.replaceInHashMap(hashmap3, as, EXCLUDE_MAP));
                }
            }
            array2.add(hashmap3);
//            if(flag && com.dragonflow.SiteView.TopazConfigurator.configInTopazAndRegistered())
//            {
//                com.dragonflow.SiteView.TopazConfigurator.moveMonitorInTopaz(s4, s5, s);
//            }
        }

        if(!flag && !com.dragonflow.SiteView.Platform.isStandardAccount(request.getAccount()) && overRemoteMonitorsLimit(request.getAccount(), array2))
        {
            return;
        }
        if(!com.dragonflow.SiteView.Platform.isStandardAccount(request.getAccount()) && overUrlLocationsMax(s, array2))
        {
            return;
        }
        jgl.Array array4 = getGroupFrames(s);
        if(debug)
        {
            com.dragonflow.Utils.TextUtils.debugPrint("READ TOGROUP=" + s);
        }
        jgl.HashMap hashmap = com.dragonflow.Page.managePage.findMonitor(array4, "_config");
        String s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_nextID");
        if(s3.length() == 0)
        {
            s3 = "1";
        }
        for(int j = 0; j < array2.size(); j++)
        {
            jgl.HashMap hashmap1 = (jgl.HashMap)array2.at(j);
            hashmap1.put("_id", s3);
            s3 = com.dragonflow.Utils.TextUtils.increment(s3);
            array4.add(hashmap1);
        }

        hashmap.put("_nextID", s3);
        printProgressMessage("Saving group configuration for " + com.dragonflow.Page.managePage.getGroupName(array4, s) + "<BR>");
        if(flag)
        {
            for(int k = 0; k < array2.size(); k++)
            {
                jgl.HashMap hashmap2 = (jgl.HashMap)((jgl.HashMap)array2.at(k)).clone();
                com.dragonflow.SiteView.AtomicMonitor atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)com.dragonflow.SiteView.AtomicMonitor.createMonitor(hashmap2, request.getPortalServer());
                atomicmonitor.notifyMove((String)array3.at(k));
//                if(com.dragonflow.SiteView.TopazConfigurator.configInTopazAndRegistered())
//                {
//                    String s7 = "SiteView/" + s + "/" + atomicmonitor.getFullID();
//                    jgl.Array array6 = new Array();
//                    jgl.Array array7 = new Array();
//                    array6.add(atomicmonitor);
//                    array7.add(s7);
//                    StringBuffer stringbuffer = new StringBuffer();
//                    com.dragonflow.SiteView.TopazAPI.updateConnInTopaz(array6, array7, array3, stringbuffer);
//                }
            }

            com.dragonflow.ConfigurationManager.InternalIdsManager.getInstance().markAsDestinationForMove(s);
        }
        WriteGroupFrames(s, array4);
        com.dragonflow.SiteView.SiteViewGroup.updateStaticPages(s);
        com.dragonflow.ConfigurationManager.InternalIdsManager.getInstance().markAsDestinationForMove(null);
        if(debug)
        {
            com.dragonflow.Utils.TextUtils.debugPrint("SAVED TOGROUP" + s);
        }
        groups.remove(s);
        if(flag)
        {
            saveGroups();
        }
    }

    public void manageGroups(jgl.Array array, jgl.Array array1, String s, boolean flag, String as[])
        throws Exception
    {
        jgl.Array array2 = new Array();
        jgl.Array array3 = new Array();
        for(int i = 0; i < array.size(); i++)
        {
            String s1 = com.dragonflow.Utils.I18N.toDefaultEncoding((String)array.at(i));
            String s2 = (String)array1.at(i);
            if(debug)
            {
                com.dragonflow.Utils.TextUtils.debugPrint("GROUPID=" + s1);
            }
            jgl.Array array4 = getGroupFrames(s1);
            if(!flag && exceedsLicenseLimit(array4, s1))
            {
                return;
            }
            jgl.HashMap hashmap1 = com.dragonflow.Page.managePage.findMonitor(array4, "_config");
            String s4 = com.dragonflow.Utils.I18N.toDefaultEncoding(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_parent"));
            Object obj = null;
            if(s4.length() > 0)
            {
                if(debug)
                {
                    com.dragonflow.Utils.TextUtils.debugPrint("PARENTID=" + s4);
                }
                jgl.Array array6 = getGroupFrames(s4);
                int k = com.dragonflow.Page.managePage.findSubGroupIndex(array6, com.dragonflow.Utils.I18N.toNullEncoding(s1));
                if(k >= 1)
                {
                    obj = (jgl.HashMap)array6.at(k);
                    if(flag)
                    {
                        if(debug)
                        {
                            com.dragonflow.Utils.TextUtils.debugPrint("REMOVING SUBGROUP - INDEX=" + k);
                        }
                        array6.remove(k);
                    }
                }
            }
            if(!flag)
            {
                hashmap1.put("_name", s2);
            }
            if(s.length() > 0)
            {
                if(debug)
                {
                    com.dragonflow.Utils.TextUtils.debugPrint("CREATING SUBGROUP FRAME");
                }
                obj = new HashMapOrdered(true);
                ((jgl.HashMap) (obj)).put("_name", com.dragonflow.Page.managePage.getGroupName(hashmap1, s1));
                ((jgl.HashMap) (obj)).put("_class", "SubGroup");
                ((jgl.HashMap) (obj)).put("_group", com.dragonflow.Utils.I18N.toNullEncoding(s1));
                array2.add(obj);
                hashmap1.put("_parent", com.dragonflow.Utils.I18N.toNullEncoding(s));
            } else
            {
                hashmap1.remove("_parent");
            }
            if(!com.dragonflow.SiteView.Platform.isStandardAccount(request.getAccount()))
            {
                jgl.HashMap hashmap3 = new HashMap();
                com.dragonflow.SiteView.monitorUtils.getGroupMonitors(hashmap3, null, array4, s1);
                java.util.Enumeration enumeration = hashmap3.keys();
                int i1 = 0;
                jgl.Array array8 = new Array();
                jgl.HashMap hashmap5;
                for(; enumeration.hasMoreElements(); array8.add(hashmap5))
                {
                    hashmap5 = (jgl.HashMap)enumeration.nextElement();
                    i1++;
                }

                if(!flag)
                {
                    if(overMaximumMonitors(request.getAccount(), i1))
                    {
                        return;
                    }
                    if(overRemoteMonitorsLimit(request.getAccount(), array8))
                    {
                        return;
                    }
                }
                if(overUrlLocationsMax(s, array8))
                {
                    return;
                }
            }
            if(!flag)
            {
                s1 = new String(com.dragonflow.Utils.I18N.toDefaultEncoding(s2));
                jgl.Array array7 = new Array();
                array7 = duplicateGroupFile(s1, array4, ((jgl.HashMap) (obj)), as, array7);
                for(int l = 0; l < array7.size(); l++)
                {
                    com.dragonflow.SiteView.SiteViewGroup.updateStaticPages((String)array7.at(l));
                }

                continue;
            }
//            if(!com.dragonflow.SiteView.TopazConfigurator.configInTopazAndRegistered())
//            {
//                continue;
//            }
            jgl.HashMap hashmap4 = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
//            if(com.dragonflow.Utils.TextUtils.getValue(hashmap4, "_topazGroupMoveHardSync").length() > 0)
//            {
//                com.dragonflow.SiteView.TopazConfigurator.hardSync = true;
//            }
//            com.dragonflow.SiteView.TopazConfigurator.moveGroupInTopaz(s1, s);
        }

        if(s.length() > 0)
        {
            jgl.Array array5 = getGroupFrames(s);
            if(debug)
            {
                com.dragonflow.Utils.TextUtils.debugPrint("READ TOGROUP=" + s);
            }
            jgl.HashMap hashmap = com.dragonflow.Page.managePage.findMonitor(array5, "_config");
            String s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_nextID");
            if(s3.length() == 0)
            {
                s3 = "1";
            }
            for(int j = 0; j < array2.size(); j++)
            {
                jgl.HashMap hashmap2 = (jgl.HashMap)array2.at(j);
                hashmap2.put("_id", s3);
                s3 = com.dragonflow.Utils.TextUtils.increment(s3);
                array5.add(hashmap2);
            }

            hashmap.put("_nextID", s3);
            printProgressMessage("Saving group configuration for " + com.dragonflow.Page.managePage.getGroupName(array5, s) + "<BR>");
            WriteGroupFrames(s, array5);
            com.dragonflow.SiteView.SiteViewGroup.updateStaticPages(s);
            groups.remove(s);
        }
        if(flag)
        {
            saveGroups();
        }
    }

    private boolean overRemoteMonitorsLimit(String s, jgl.Array array)
    {
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s);
        jgl.HashMap hashmap1 = monitorgroup.getValuesTable();
        int i = 0;
        int j = 0;
        int k = 0;
        String s1 = "";
        for(int l = 0; l < array.size(); l++)
        {
            jgl.HashMap hashmap = (jgl.HashMap)array.at(l);
            String s2 = (String)hashmap.get("_class");
            if(s2.equals("URLRemoteMonitor"))
            {
                i++;
                if(hashmap.get("_getImages") != null && ((String)hashmap.get("_getImages")).equals("on") || hashmap.get("_getFrames") != null && ((String)hashmap.get("_getFrames")).equals("on"))
                {
                    k++;
                }
            }
            if(!s2.equals("URLRemoteSequenceMonitor"))
            {
                continue;
            }
            j++;
            if(hashmap.get("_getImages") != null && ((String)hashmap.get("_getImages")).equals("on") || hashmap.get("_getFrames") != null && ((String)hashmap.get("_getFrames")).equals("on"))
            {
                k++;
            }
        }

        String s3 = com.dragonflow.SiteView.monitorUtils.getPermission(hashmap1, "_monitorType", "URLRemoteMonitor");
        int i1;
        if(s3 != null && s3.length() > 0 && !s3.equals("yes"))
        {
            i1 = (new Integer(s3)).intValue();
        } else
        {
            i1 = 0;
        }
        if(i1 > 0)
        {
            i += monitorgroup.countMonitorsOfClass("URLRemoteMonitor", s);
            if(i > i1)
            {
                printProgressMessage("<B>You have reached or will exceed your limit of " + i1 + " URL Remote monitors for this account.</B>");
                return true;
            }
        }
        String s4 = com.dragonflow.SiteView.monitorUtils.getPermission(hashmap1, "_monitorType", "URLRemoteSequenceMonitor");
        int j1;
        if(s4 != null && s4.length() > 0 && !s4.equals("yes"))
        {
            j1 = (new Integer(s4)).intValue();
        } else
        {
            j1 = 0;
        }
        if(j1 > 0)
        {
            j += monitorgroup.countMonitorsOfClass("URLRemoteSequenceMonitor", s);
            if(j > j1)
            {
                printProgressMessage("<B>You have reached or will exceed your limit of " + j1 + " URL Remote Sequence monitors for this account.</B>");
                return true;
            }
        }
        String s5 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_maximumFAndIMonitors");
        int k1 = com.dragonflow.Utils.TextUtils.toInt(s5);
        k += countFAndIMonitors(s);
        if(k1 > 0 && k > k1)
        {
            printProgressMessage("<B>You have reached or will exceed your limit of " + k1 + " frames and images for this account.</B>");
            return true;
        } else
        {
            return false;
        }
    }

    private int countFAndIMonitors(String s)
    {
        int i = 0;
        try
        {
            jgl.Array array = getGroupFrames(s);
            jgl.HashMap hashmap = new HashMap(true);
            com.dragonflow.SiteView.monitorUtils.getGroupMonitors(hashmap, null, array, s);
            java.util.Enumeration enumeration = hashmap.keys();
            String s1 = "";
            do
            {
                if(!enumeration.hasMoreElements())
                {
                    break;
                }
                jgl.HashMap hashmap1 = (jgl.HashMap)enumeration.nextElement();
                String s2 = (String)hashmap1.get("_class");
                if(s2.startsWith("URLRemote") && (hashmap1.get("_getImages") != null && ((String)hashmap1.get("_getImages")).equals("on") || hashmap1.get("_getFrames") != null && ((String)hashmap1.get("_getFrames")).equals("on")))
                {
                    i++;
                }
            } while(true);
        }
        catch(Exception exception)
        {
            com.dragonflow.Log.LogManager.log("RunMonitor", "An exception occurred counting F and I monitors: " + exception);
        }
        return i;
    }

    private boolean overMaximumMonitors(String s, int i)
    {
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s);
        int j = request.getPermissionAsInteger("_maximumMonitors");
        if(j > 0)
        {
            int k = monitorgroup.countMonitors(request.getAccount()) + i;
            if(k > j)
            {
                printProgressMessage("<B>You have reached or will exceed your limit of " + j + " monitors for this account.</B>");
                return true;
            } else
            {
                return false;
            }
        } else
        {
            printProgressMessage("<B>You have reached or will exceed your limit of " + j + " monitors for this account.</B>");
            return true;
        }
    }

    private boolean overUrlLocationsMax(String s, jgl.Array array)
    {
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElementByID(s);
        int i = (new Integer(monitorgroup.getTreeSetting("_URLRemoteLocationsMax"))).intValue();
        for(int j = 0; j < array.size(); j++)
        {
            jgl.HashMap hashmap = (jgl.HashMap)array.at(j);
            String s1 = (String)hashmap.get("_class");
            if(!s1.startsWith("URLRemote"))
            {
                continue;
            }
            java.util.Enumeration enumeration = hashmap.values("_location");
            int k = 0;
            boolean flag = false;
            do
            {
                if(!enumeration.hasMoreElements())
                {
                    break;
                }
                String s2 = (String)enumeration.nextElement();
                String s3 = (String)com.dragonflow.Utils.HTTPUtils.locationMap.get(s2);
                if(s3 != null && !s3.equals(""))
                {
                    int l = com.dragonflow.Utils.HTTPUtils.getDisplayOrder(s3);
                    if(l >= 0)
                    {
                        k++;
                    } else
                    {
                        String s4 = monitorgroup.getSetting("_allowInvalidNode");
                        String s5 = com.dragonflow.Utils.HTTPUtils.getLocationID(s3);
                        if(s4 != null && s4.indexOf(s5) >= 0)
                        {
                            k++;
                        }
                    }
                }
            } while(true);
            if(k > i)
            {
                printProgressMessage("<B>You are only allowed " + i + " locations for the remote monitors in the " + s + " group.  You are trying to move a monitor with " + k + " locations.</B>");
                return true;
            }
        }

        return false;
    }

    jgl.Array duplicateGroupFile(String s, jgl.Array array, jgl.HashMap hashmap, String as[], jgl.Array array1)
        throws Exception
    {
        if(debug)
        {
            com.dragonflow.Utils.TextUtils.debugPrint("DUPLICATING GROUP=" + s);
        }
        printProgressMessage("Duplicating group configuration for " + com.dragonflow.Page.managePage.getGroupName(array, s) + "<BR>");
        if(!com.dragonflow.SiteView.Platform.isStandardAccount(request.getAccount()) && s.indexOf("$") < 0)
        {
            s = computeGroupName(request.getAccount() + "$" + s);
        } else
        {
            s = computeGroupName(s);
        }
        array1.add(s);
        if(as.length > 0)
        {
            java.util.Enumeration enumeration = array.elements();
            do
            {
                if(!enumeration.hasMoreElements())
                {
                    break;
                }
                jgl.HashMap hashmap1 = (jgl.HashMap)enumeration.nextElement();
                if(as.length > 0 && com.dragonflow.SiteView.Monitor.isMonitorFrame(hashmap1))
                {
                    printProgressMessage(com.dragonflow.Utils.TextUtils.replaceInHashMap(hashmap1, as, EXCLUDE_MAP));
                }
            } while(true);
        }
        if(debug)
        {
            com.dragonflow.Utils.TextUtils.debugPrint("NEW GROUP ID=" + s);
        }
        if(hashmap != null)
        {
            hashmap.put("_group", com.dragonflow.Utils.I18N.toNullEncoding(s));
        }
        for(int i = 1; i < array.size(); i++)
        {
            jgl.HashMap hashmap2 = (jgl.HashMap)array.at(i);
            if(com.dragonflow.Utils.TextUtils.getValue(hashmap2, "_class").equals("SubGroup"))
            {
                String s1 = com.dragonflow.Utils.I18N.toDefaultEncoding(com.dragonflow.Utils.TextUtils.getValue(hashmap2, "_group"));
                jgl.Array array2 = null;
                try
                {
                    array2 = ReadGroupFrames(s1);
                    if(array2.size() > 0)
                    {
                        jgl.HashMap hashmap3 = (jgl.HashMap)array2.at(0);
                        String s2 = com.dragonflow.Utils.TextUtils.getValue(hashmap3, "_name");
                        if(s2 != null && s2.length() > 0 && s2.equalsIgnoreCase("config"))
                        {
                            hashmap3.put("_name", com.dragonflow.Utils.TextUtils.getValue(hashmap2, "_name"));
                        }
                    }
                }
                catch(Exception exception)
                {
                    array2 = null;
                }
                if(array2 != null && array2.size() > 0)
                {
                    jgl.HashMap hashmap4 = (jgl.HashMap)array2.at(0);
                    hashmap4.put("_parent", com.dragonflow.Utils.I18N.toNullEncoding(s));
                    duplicateGroupFile(s1, array2, hashmap2, as, array1);
                }
            } else
            {
                hashmap2.remove(com.dragonflow.SiteView.AtomicMonitor.pUniqueInternalId.getName());
            }
        }

        if(debug)
        {
            com.dragonflow.Utils.TextUtils.debugPrint("SAVING GROUPID=" + s);
        }
        WriteGroupFrames(s, array);
        return array1;
    }

    String getReturnURL(boolean flag)
    {
        String s = "";
        if(flag)
        {
            s = request.getValue("returnURL");
        } else
        {
            s = com.dragonflow.HTTP.HTTPRequest.encodeString(com.dragonflow.Utils.I18N.toDefaultEncoding(request.getValue("returnURL")));
        }
        if(s.length() == 0)
        {
            s = "/SiteView/cgi/go.exe/SiteView?page=manage&account=" + request.getAccount();
        } else
        {
            s = com.dragonflow.Page.CGI.getGroupDetailURL(request, request.getValue("returnURL"));
        }
        return s;
    }

    String getReturnLabel()
    {
        String s = request.getValue("returnLabel");
        if(s.length() == 0)
        {
            s = "Return to Previous";
        } else
        {
            s = "Return to : " + s;
        }
        return s;
    }

    public void printListForm()
        throws Exception
    {
        String s;
        if(com.dragonflow.SiteView.Platform.isStandardAccount(request.getAccount()))
        {
            s = com.dragonflow.SiteView.Platform.getDirectoryPath("groups", request.getAccount());
        } else
        {
            s = com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "accounts" + java.io.File.separator + request.getAccount();
        }
        String s1 = s + java.io.File.separator + "tree.dyn";
        printBodyHeader("Manage Monitors and Groups");
        com.dragonflow.Page.CGI.menus menus1 = getNavItems(request);
        printButtonBar("ManageMon.htm", "", menus1);
        outputStream.println("<H2>Manage Monitors and Groups</H2>");
        String s2 = "<p>Select one or more groups and monitors and then choose the action you wish to perform from the controls below the tree display.  Click the <img src=/SiteView/htdocs/artwork/Plus.gif alt=\"open\"> to expand a group, and the <img src=/SiteView/htdocs/artwork/Minus.gif alt=\"close\"> to collapse a group.  Use the <b>Filter Settings</b> to display a filtered list of groups and monitors.</p>";
        if(!com.dragonflow.Page.treeControl.useTree())
        {
            outputStream.println(s2);
        }
        boolean flag = false;
        jgl.Array array = null;
        if((request.getValue("monitorNameSelect").length() > 0 || request.getValue("machineNameSelect").length() > 0 || request.getValue("monitorTypeSelect").length() > 0) && request.getValue("operation").startsWith("Apply"))
        {
            printBrowseFilterOptionForm(outputStream);
            printFilteredList();
        } else
        {
            try
            {
                if(com.dragonflow.Page.treeControl.useTree())
                {
                    array = new Array();
                } else
                {
                    array = com.dragonflow.Properties.FrameFile.readFromFile(s1);
                }
            }
            catch(Exception exception)
            {
                array = new Array();
            }
            jgl.HashMap hashmap = null;
            String s3 = request.getAccount();
            for(int i = 0; i < array.size(); i++)
            {
                jgl.HashMap hashmap1 = (jgl.HashMap)array.at(i);
                if(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_user").equals(s3))
                {
                    hashmap = hashmap1;
                }
            }

            if(hashmap == null)
            {
                hashmap = new HashMap();
                array.add(hashmap);
                hashmap.put("_user", s3);
            }
            java.util.Enumeration enumeration = request.getVariables();
            do
            {
                if(!enumeration.hasMoreElements())
                {
                    break;
                }
                String s4 = com.dragonflow.HTTP.HTTPRequest.decodeString((String)enumeration.nextElement(), com.dragonflow.Utils.I18N.nullEncoding());
                if(s4.startsWith(OPEN_VARIABLE))
                {
                    String s5 = s4.substring(OPEN_VARIABLE.length(), s4.length() - 2);
                    if(debug)
                    {
                        com.dragonflow.Utils.TextUtils.debugPrint("OPEN " + s5);
                    }
                    if(!com.dragonflow.Utils.TextUtils.getValue(hashmap, s5).equals("open"))
                    {
                        hashmap.put(s5, "open");
                        flag = true;
                    }
                }
                if(s4.startsWith(CLOSE_VARIABLE))
                {
                    String s6 = s4.substring(CLOSE_VARIABLE.length(), s4.length() - 2);
                    if(debug)
                    {
                        com.dragonflow.Utils.TextUtils.debugPrint("CLOSE " + s6);
                    }
                    if(!com.dragonflow.Utils.TextUtils.getValue(hashmap, s6).equals("close"))
                    {
                        hashmap.remove(s6);
                        flag = true;
                    }
                }
            } while(true);
            jgl.Array array1 = new Array();
            jgl.HashMap hashmap2 = new HashMap();
            Object obj = null;
            if(com.dragonflow.Page.treeControl.useTree())
            {
                String s7;
                for(java.util.Enumeration enumeration1 = request.getValues("monitor"); enumeration1.hasMoreElements(); array1.add(s7))
                {
                    s7 = com.dragonflow.HTTP.HTTPRequest.decodeString((String)enumeration1.nextElement());
                    hashmap2.put(s7, "checked");
                }

                String s8;
                for(java.util.Enumeration enumeration2 = request.getValues("group"); enumeration2.hasMoreElements(); array1.add(s8))
                {
                    s8 = com.dragonflow.HTTP.HTTPRequest.decodeString((String)enumeration2.nextElement());
                    hashmap2.put(s8, "checked");
                }

            } else
            {
                for(java.util.Enumeration enumeration3 = request.getValues("monitor"); enumeration3.hasMoreElements(); hashmap2.put(enumeration3.nextElement(), "checked")) { }
                for(java.util.Enumeration enumeration4 = request.getValues("group"); enumeration4.hasMoreElements(); hashmap2.put(enumeration4.nextElement(), "checked")) { }
            }
            printBrowseFilterOptionForm(outputStream);
            outputStream.println("<FORM METHOD=POST ACTION=/SiteView/cgi/go.exe/SiteView><INPUT TYPE=HIDDEN NAME=level VALUE=first><INPUT TYPE=HIDDEN NAME=page VALUE=manage><INPUT TYPE=HIDDEN NAME=needVerify VALUE=true><INPUT TYPE=HIDDEN NAME=account VALUE=" + s3 + ">" + "<TABLE BORDER=\"0\" CELLSPACING=\"4\">");
            if(request.getValue("_health").length() > 0)
            {
                outputStream.print("<input type=hidden name=_health value=true>\n");
            }
            if(com.dragonflow.Page.treeControl.useTree())
            {
                StringBuffer stringbuffer = new StringBuffer();
                com.dragonflow.Page.treeControl treecontrol = new treeControl(request, "monitor", false, !com.dragonflow.Page.treeControl.notHandled(request));
                treecontrol.process("Groups:", "", s2, array1, null, null, 67, this, stringbuffer);
                outputStream.println(stringbuffer.toString());
                outputStream.println("</TABLE>");
            } else
            {
                com.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
                jgl.Array array2 = getGroupNameList(hashmapordered, null, null, true);
                for(java.util.Enumeration enumeration6 = array2.elements(); enumeration6.hasMoreElements();)
                {
                    String s9 = (String)enumeration6.nextElement();
                    java.util.Enumeration enumeration5 = hashmapordered.values(s9);
                    while(enumeration5.hasMoreElements()) 
                    {
                        com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)enumeration5.nextElement();
                        groupCount++;
                        printGroup(monitorgroup, hashmap, hashmap2, 0);
                    }
                }

                outputStream.println("</TABLE>");
            }
        }
        outputStream.println("<HR><TABLE WIDTH=98% BORDER=0 CELLPADDING=5>");
        if(request.actionAllowed("_groupEdit"))
        {
            printManageButton("Move", "ManageMon.htm#move", "For groups, make the selected groups a subgroup of another group.<BR>For monitors, move the selected monitors to a different group.");
            printManageButton("Copy", "ManageMon.htm#copy", "For groups, copy the selected groups and subgroups.<BR>For monitors, copy the selected monitors to a different group.");
            printManageButton("Duplicate", "ManageMon.htm#duplicate", "For groups, copy <u>and</u> rename the selected groups and subgroups.<BR>For monitors, copy and rename the selected monitors.");
            printManageButton("Delete", "ManageMon.htm#delete", "For groups, delete the selected groups and subgroups.<BR>For monitors, delete the selected monitors.");
        }
        if(request.actionAllowed("_groupDisable") || request.actionAllowed("_monitorDisable") || request.actionAllowed("_alertTempDisable"))
        {
            printManageButton("Disable", "ManageMon.htm#disable", "For groups, disable all monitors or alerts in the selected groups and their subgroups.<BR>For monitors, disable the selected monitors or alerts.");
            printManageButton("Enable", "ManageMon.htm#enable", "For groups, enable all monitors or alerts in the selected groups and their subgroups.<BR>For monitors, enable the selected monitors or alerts.");
        }
        if(request.actionAllowed("_groupRefresh"))
        {
            printManageButton("Refresh", "ManageMon.htm#refresh", "For groups, refresh all monitors in the selected groups and their subgroups.<BR>For monitors, refresh the selected monitors.");
        }
        if(request.actionAllowed("_groupEdit"))
        {
            printManageButton("Replace", "ManageMon.htm#replace", "Replace values in the selected groups and monitors");
            printManageButton("Baseline", "Baseline.htm", "Establish a fixed performance baseline for the selected monitors");
        }
//        if(request.actionAllowed("_groupEdit") && com.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazServerSettings().isConnected() && com.dragonflow.Properties.PropertiedObject.getPropertyMapByObject("com.dragonflow.SiteView.AtomicMonitor", "_notLogToTopaz") != null)
//        {
//            printManageButton(TOPAZ_LOGGING_OP, "sendToTopaz.htm", "Set different " + com.dragonflow.SiteView.TopazInfo.getTopazName() + " logging options.");
//        }
        outputStream.println("</TABLE>");
        outputStream.println("</FORM>");
        printFooter(outputStream);
        if(flag)
        {
            if(debug)
            {
                com.dragonflow.Utils.TextUtils.debugPrint("SAVING TREE STATE");
            }
            com.dragonflow.Properties.FrameFile.writeToFile(s1, array);
        }
    }

    void printManageButton(String s, String s1, String s2)
    {
        outputStream.println("<TR><TD valign=top align=left><input type=submit name=operation value=\"" + s + "\"> </TD>" + "<TD ALIGN=LEFT><p style=\"font-size:10pt\">" + s2 + "</p></TD></TR>");
    }

    String getIndentHTML(int i)
    {
        int j = i * 11;
        if(j == 0)
        {
            j = 1;
        }
        return "<img src=/SiteView/htdocs/artwork/empty1111.gif height=11 width=" + j + " border=0>";
    }

    private void printFilteredList()
    {
        String s = com.dragonflow.SiteView.Platform.getURLPath("htdocs", request.getAccount()) + "/Detail";
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        jgl.Array array = getFilteredGroupList();
        outputStream.println("<FORM METHOD=GET ACTION=/SiteView/cgi/go.exe/SiteView><INPUT TYPE=HIDDEN NAME=page VALUE=manage><INPUT TYPE=HIDDEN NAME=account VALUE=" + request.getAccount() + ">");
        if(request.getValue("_health").length() > 0)
        {
            outputStream.print("<input type=hidden name=_health value=true>\n");
        }
        if(array.size() > 0)
        {
            outputStream.print("<B>Groups:</B><BR>");
            outputStream.print("<table border=\"0\" cellspacing=\"0\" cellpadding=\"2\">");
            for(int i = 0; i < array.size(); i++)
            {
                String s1 = (String)array.at(i);
                com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s1);
                outputStream.println("<tr><td><input type=checkbox name=group" + i + " value=\"" + s1 + "\" " + "CHECKED" + "></td>");
                outputStream.print("<td><a href=\"" + s + com.dragonflow.HTTP.HTTPRequest.encodeString(com.dragonflow.Utils.I18N.toDefaultEncoding(monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pID))) + ".html\"><b>" + monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pName) + "</b></a></td></tr>");
            }

            outputStream.println("</table>");
        }
        jgl.Array array1 = new Array();
        com.dragonflow.SiteView.Monitor monitor;
        for(java.util.Enumeration enumeration = siteviewgroup.getMonitors(); enumeration.hasMoreElements(); createFilteredMonitorList(monitor, array1))
        {
            monitor = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
        }

        if(array1.size() > 0)
        {
            outputStream.print("<b>Monitors:</b><br>");
            outputStream.print("<table border=\"0\" cellspacing=\"0\" cellpadding=\"2\">");
            for(int j = 0; j < array1.size(); j++)
            {
                com.dragonflow.SiteView.Monitor monitor1 = (com.dragonflow.SiteView.Monitor)array1.at(j);
                String s2 = monitor1.getOwner().getProperty(com.dragonflow.SiteView.Monitor.pID) + " " + monitor1.getProperty(com.dragonflow.SiteView.Monitor.pID);
                outputStream.print("<tr><td><input type=checkbox name=monitor value=\"" + s2 + "\"+ CHECKED></td>");
                outputStream.print("<td><a href=\"" + s + com.dragonflow.HTTP.HTTPRequest.encodeString(com.dragonflow.Utils.I18N.toDefaultEncoding(monitor1.getOwner().getProperty(com.dragonflow.SiteView.Monitor.pID))) + ".html\">(" + monitor1.getOwner().getProperty(com.dragonflow.SiteView.Monitor.pName) + ")</a></td><td><b>" + monitor1.getProperty(com.dragonflow.SiteView.Monitor.pName) + "</b>");
                outputTopazLoggingStatus(monitor1);
                outputStream.print("</td></tr>");
            }

            outputStream.println("</table>");
        }
        if(array.size() <= 0 && array1.size() <= 0)
        {
            outputStream.print("<table border=\"0\" cellspacing=\"0\" cellpadding=\"5\" width=\"90%\">");
            outputStream.println("<tr><td align=\"center\"><p align=\"center\"><b>No matches found for current filter settings</b></p></td>");
            outputStream.println("</table>");
        }
    }

    private void printGroup(com.dragonflow.SiteView.MonitorGroup monitorgroup, jgl.HashMap hashmap, jgl.HashMap hashmap1, int i)
    {
        String s = monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pID);
        boolean flag = hashmap.get(s) != null;
        String s1 = getIndentHTML(i);
        String s2 = com.dragonflow.SiteView.Platform.getURLPath("htdocs", request.getAccount()) + "/Detail";
        outputStream.print("<TR><TD>");
        outputStream.print(s1);
        if(flag)
        {
            outputStream.print("<input type=image name=close" + s + " src=/SiteView/htdocs/artwork/Minus.gif alt=\"close\" border=0>");
        } else
        {
            outputStream.print("<input type=image name=open" + s + " src=/SiteView/htdocs/artwork/Plus.gif alt=\"open\" border=0>");
        }
        outputStream.print("<input type=checkbox name=group" + groupCount + " value=\"" + s + "\" " + com.dragonflow.Utils.TextUtils.getValue(hashmap1, s) + "><B>");
        outputStream.print("<A HREF=" + s2 + com.dragonflow.HTTP.HTTPRequest.encodeString(com.dragonflow.Utils.I18N.toDefaultEncoding(monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pID))) + ".html>" + monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pName));
        outputStream.println("</A></B></TD></TR>");
        s1 = getIndentHTML(i + 3);
        if(flag)
        {
            java.util.Enumeration enumeration = monitorgroup.getMonitors();
            do
            {
                if(!enumeration.hasMoreElements())
                {
                    break;
                }
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
                if(monitor instanceof com.dragonflow.SiteView.SubGroup)
                {
                    String s3 = com.dragonflow.Utils.I18N.toDefaultEncoding(monitor.getProperty(com.dragonflow.SiteView.SubGroup.pGroup));
                    com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                    com.dragonflow.SiteView.MonitorGroup monitorgroup1 = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s3);
                    if(monitorgroup1 != null)
                    {
                        groupCount++;
                        printGroup(monitorgroup1, hashmap, hashmap1, i + 2);
                    }
                } else
                {
                    outputStream.print("<TR><TD>");
                    outputStream.print(s1);
                    String s4 = s + " " + monitor.getProperty(com.dragonflow.SiteView.Monitor.pID);
                    outputStream.print("<input type=checkbox name=monitor value=\"" + s4 + "\" " + com.dragonflow.Utils.TextUtils.getValue(hashmap1, s4) + ">");
                    outputStream.print(monitor.getProperty(com.dragonflow.SiteView.Monitor.pName));
                    outputTopazLoggingStatus(monitor);
                    outputStream.println("</TD></TR>");
                }
            } while(true);
        }
    }

    protected void outputTopazLoggingStatus(com.dragonflow.SiteView.Monitor monitor)
    {
        if(monitor.getProperty(com.dragonflow.SiteView.Monitor.pDisabled).length() > 0)
        {
            outputStream.println(" <B>(disabled)</B>");
        } 
//		else
//        if(com.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazServerSettings().isConnected())
//        {
//            if(monitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pNotLogToTopaz).length() > 0)
//            {
//                outputStream.println(" <B>(logging to " + com.dragonflow.SiteView.TopazInfo.getTopazName() + " disabled)</B>");
//            } else
//            if(monitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pOnlyLogMonitorData).length() > 0)
//            {
//                outputStream.println(" <B>(logging only monitor data to " + com.dragonflow.SiteView.TopazInfo.getTopazName() + ")</B>");
//            } else
//            if(monitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pOnlyLogStatusChanges).length() > 0)
//            {
//                outputStream.println(" <B>(logging only status changes)</B>");
//            } else
//            if(monitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pOnlyLogThresholdMeas).length() > 0)
//            {
//                outputStream.println(" <B>(logging only measurements with thresholds)</B>");
//            } else
//            {
//                outputStream.println(" <B>(log everything to " + com.dragonflow.SiteView.TopazInfo.getTopazName() + ")</B>");
//            }
//        }
    }

    void baselineMonitors(jgl.Array array, jgl.Array array1)
        throws Exception
    {
        int i = com.dragonflow.Utils.TextUtils.toInt(request.getValue("baselineDays"));
        if(i == 0)
        {
            i = 5;
        }
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        jgl.Array array2 = new Array();
        String s = "administrator";
        Object obj = null;
        Object obj1 = null;
        Object obj2 = null;
        Object obj3 = null;
        Object obj4 = null;
        boolean flag = false;
label0:
        for(int j = 0; j < array.size(); j++)
        {
            String s1 = (String)array.at(j);
            printProgressMessage("Baselining monitor" + (array.size() <= 1 ? "" : "s") + "<BR>");
            String as[] = com.dragonflow.Utils.TextUtils.split(s1);
            String s3 = as[0] + com.dragonflow.SiteView.SiteViewGroup.ID_SEPARATOR + as[1];
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(as[0]);
            if(monitorgroup != null)
            {
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(s3);
                if(monitor != null)
                {
                    if(monitorgroup.getSetting("_logInGroup", false).length() > 0)
                    {
                        s = monitorgroup.getProperty("_name");
                    } else
                    if(monitorgroup.getProperty(com.dragonflow.SiteView.MonitorGroup.pAccountName).length() > 0)
                    {
                        s = monitorgroup.getProperty(com.dragonflow.SiteView.MonitorGroup.pAccountName);
                    }
                    if(as.length == 2)
                    {
                        java.util.Enumeration enumeration = monitor.getStatePropertyObjects(flag);
                        do
                        {
                            com.dragonflow.Properties.StringProperty stringproperty;
                            do
                            {
                                if(!enumeration.hasMoreElements())
                                {
                                    continue label0;
                                }
                                stringproperty = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
                            } while(!(stringproperty instanceof com.dragonflow.Properties.NumericProperty));
                            addCollector(array2, monitor, stringproperty);
                        } while(true);
                    }
                    com.dragonflow.Properties.StringProperty stringproperty1 = monitor.getPropertyObject(as[2]);
                    addCollector(array2, monitor, stringproperty1);
                } else
                {
                    com.dragonflow.Log.LogManager.log("Error", "\tMonitor in group: " + as[1] + "was missing");
                }
            } else
            {
                com.dragonflow.Log.LogManager.log("Error", "\tGroup was missing: " + as[0]);
            }
        }

label1:
        for(int k = 0; k < array1.size(); k++)
        {
            String s2 = (String)array1.at(k);
            com.dragonflow.SiteView.MonitorGroup monitorgroup1 = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s2);
            if(monitorgroup1 != null)
            {
                if(monitorgroup1.getSetting("_logInGroup", false).length() > 0)
                {
                    s = monitorgroup1.getProperty("_name");
                } else
                if(monitorgroup1.getProperty(com.dragonflow.SiteView.MonitorGroup.pAccountName).length() > 0)
                {
                    s = monitorgroup1.getProperty(com.dragonflow.SiteView.MonitorGroup.pAccountName);
                }
                java.util.Enumeration enumeration1 = monitorgroup1.getMonitors();
label2:
                do
                {
                    if(!enumeration1.hasMoreElements())
                    {
                        continue label1;
                    }
                    com.dragonflow.SiteView.Monitor monitor1 = (com.dragonflow.SiteView.Monitor)enumeration1.nextElement();
                    if(monitor1 instanceof com.dragonflow.SiteView.SubGroup)
                    {
                        array1.add(monitor1.getProperty(com.dragonflow.SiteView.SubGroup.pGroup));
                        continue;
                    }
                    java.util.Enumeration enumeration2 = monitor1.getStatePropertyObjects(flag);
                    if(enumeration2.hasMoreElements())
                    {
                        do
                        {
                            com.dragonflow.Properties.StringProperty stringproperty2;
                            do
                            {
                                if(!enumeration2.hasMoreElements())
                                {
                                    continue label2;
                                }
                                stringproperty2 = (com.dragonflow.Properties.StringProperty)enumeration2.nextElement();
                            } while(!(stringproperty2 instanceof com.dragonflow.Properties.NumericProperty));
                            addCollector(array2, monitor1, stringproperty2);
                        } while(true);
                    }
                    com.dragonflow.Log.LogManager.log("Error", "Monitor has no default property: " + monitor1);
                    printProgressMessage("Monitor has no default property: " + monitor1);
                } while(true);
            }
            com.dragonflow.Log.LogManager.log("Error", "\tGroup was missing: " + s2);
        }

        if(array2.size() < 1)
        {
            com.dragonflow.Log.LogManager.log("Error", "Monitors have no default numeric properties: nothing to baseline ");
            printProgressMessage("Monitors have no default numeric properties: nothing to baseline<BR>");
            return;
        }
        java.util.Date date = com.dragonflow.SiteView.Platform.makeDate();
        java.util.Date date1 = new Date(date.getTime() - (long)(i * com.dragonflow.Utils.TextUtils.DAY_SECONDS * 1000));
        java.io.File file = new File(com.dragonflow.SiteView.Platform.getDirectoryPath("logs", s) + java.io.File.separator + "SiteView.log");
        com.dragonflow.SiteView.SiteViewLogReader siteviewlogreader = new SiteViewLogReader(file);
        int l = i * com.dragonflow.Utils.TextUtils.DAY_SECONDS;
        int i1 = 0;
        siteviewlogreader.process(array2, date1, date, i1, l);
        for(int j1 = 0; j1 < array2.size(); j1++)
        {
            com.dragonflow.SiteView.SampleCollector samplecollector = (com.dragonflow.SiteView.SampleCollector)array2.at(j1);
            float f = samplecollector.getAverage();
            float f1 = samplecollector.getStandardDeviation();
            com.dragonflow.SiteView.Monitor monitor2 = samplecollector.getMonitor();
            String s4 = monitor2.getProperty(com.dragonflow.SiteView.Monitor.pGroupID);
            String s5 = monitor2.getProperty(com.dragonflow.SiteView.Monitor.pID);
            jgl.Array array3 = getGroupFrames(s4);
            jgl.HashMap hashmap = com.dragonflow.Page.managePage.findMonitor(array3, s5);
            com.dragonflow.SiteView.Monitor _tmp = monitor2;
            String s6 = com.dragonflow.SiteView.Monitor.pBaselineMean.getName();
            com.dragonflow.SiteView.Monitor _tmp1 = monitor2;
            String s7 = com.dragonflow.SiteView.Monitor.pBaselineStdDev.getName();
            com.dragonflow.SiteView.Monitor _tmp2 = monitor2;
            String s8 = com.dragonflow.SiteView.Monitor.pBaselineDate.getName();
            Long long1 = new Long(com.dragonflow.SiteView.Platform.timeMillis());
            String s9 = long1.toString();
            hashmap.put(s6, com.dragonflow.Utils.TextUtils.floatToString(f, 4));
            hashmap.put(s7, com.dragonflow.Utils.TextUtils.floatToString(f1, 4));
            hashmap.put(s8, s9);
        }

        if(array2.size() > 0)
        {
            saveGroups();
        }
    }

    private void addCollector(jgl.Array array, com.dragonflow.SiteView.Monitor monitor, com.dragonflow.Properties.StringProperty stringproperty)
    {
        com.dragonflow.SiteView.SampleCollector samplecollector = new SampleCollector(monitor, stringproperty);
        array.add(samplecollector);
    }

    public static jgl.HashMap copyHashMap(jgl.HashMap hashmap)
    {
        Object obj;
        if(hashmap instanceof com.dragonflow.Properties.HashMapOrdered)
        {
            obj = new HashMapOrdered(true);
        } else
        {
            obj = new HashMap();
        }
        for(java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements();)
        {
            Object obj1 = enumeration.nextElement();
            if(hashmap.get(obj1) instanceof jgl.Array)
            {
                jgl.Array array = (jgl.Array)hashmap.get(obj1);
                jgl.Array array1 = new Array();
                for(int i = 0; i < array.size(); i++)
                {
                    array1.add(new String((String)array.at(i)));
                }

                ((jgl.HashMap) (obj)).put(obj1, array1);
            } else
            {
                ((jgl.HashMap) (obj)).put(obj1, hashmap.get(obj1));
            }
        }

        return ((jgl.HashMap) (obj));
    }

    public void performGroupConfigChange(String s, String s1, String as[], String s2, String s3, String s4)
        throws Exception
    {
        if(s.equals("_master"))
        {
            com.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
            getGroupNameList(hashmapordered, null, null, true);
            String s6;
            for(java.util.Enumeration enumeration = hashmapordered.elements(); enumeration.hasMoreElements(); performGroupConfigChange(s6, s1, as, s2, s3, s4))
            {
                com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)enumeration.nextElement();
                s6 = monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pGroupID);
            }

            return;
        }
        jgl.Array array = getGroupFrames(s);
        String s5 = com.dragonflow.Page.managePage.getGroupName(array, s);
        if(debug)
        {
            com.dragonflow.Utils.TextUtils.debugPrint(s1 + " GROUP=" + s);
            com.dragonflow.Utils.TextUtils.debugPrint("Timed:" + s2 + " Alert:" + s3);
        }
        if(s2.equals("0"))
        {
            printProgressMessage("Undo schedule for " + s5 + " Group<BR>");
        } else
        {
            printProgressMessage(s1 + (s3.length() <= 0 ? " " : " alert ") + s5 + " Group<BR>");
        }
        for(int i = 1; i < array.size(); i++)
        {
            jgl.HashMap hashmap = (jgl.HashMap)array.at(i);
            String s7 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_class");
            if(s7.equals("SubGroup"))
            {
                String s8 = com.dragonflow.Utils.I18N.toDefaultEncoding(com.dragonflow.Utils.TextUtils.getValue(hashmap, "_group"));
                if(s8.length() != 0)
                {
                    performGroupConfigChange(s8, s1, as, s2, s3, s4);
                }
            } else
            {
                performMonitorConfigChange(hashmap, s, s1, s2, s3, s4, as);
            }
        }

    }

    void refreshMonitor(String s, String s1, String s2)
    {
        com.dragonflow.Utils.I18N.test(s, 0);
        String s3 = s + com.dragonflow.SiteView.SiteViewGroup.ID_SEPARATOR + s1;
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(s3);
        String s4 = "0";
        if(s2.equals("Refresh"))
        {
            s4 = "-1";
        }
        if(monitor != null)
        {
            monitor.setProperty(com.dragonflow.SiteView.Monitor.pLastUpdate, s4);
            monitor.setProperty(com.dragonflow.SiteView.Monitor.pForceRefresh, request.getValue("forceRefresh"));
        }
    }

    public void performMonitorConfigChange(String s, String s1, String as[], String s2, String s3, String s4)
        throws Exception
    {
        int i = s.indexOf(' ');
        if(i >= 0)
        {
            com.dragonflow.Utils.I18N.test(s, 0);
            if(debug)
            {
                com.dragonflow.Utils.TextUtils.debugPrint(s1 + " MONITOR=" + s);
                com.dragonflow.Utils.TextUtils.debugPrint("Timed:" + s2 + " Alert:" + s3);
            }
            String s5 = s.substring(0, i);
            String s6 = s.substring(i + 1);
            jgl.Array array = getGroupFrames(s5);
            jgl.HashMap hashmap = com.dragonflow.Page.managePage.findMonitor(array, s6);
            String s7 = (String)hashmap.get("_class");
            if(s7 != null && s7.equals("SubGroup"))
            {
                String s8 = (String)hashmap.get("_group");
                performGroupConfigChange(s8, s1, as, s2, s3, s4);
            } else
            {
                performMonitorConfigChange(hashmap, s5, s1, s2, s3, s4, as);
            }
        }
    }

    private void performMonitorConfigChange(jgl.HashMap hashmap, String s, String s1, String s2, String s3, String s4, String as[])
    {
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        String s5 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_class");
        String s6 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_id");
        boolean flag = false;
        com.dragonflow.SiteView.AtomicMonitor atomicmonitor = null;
        if(!s5.equals("SubGroup"))
        {
            try
            {
                atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)siteviewgroup.getElement("SiteView/" + s + "/" + s6);
                flag = true;
            }
            catch(Exception exception)
            {
                com.dragonflow.Log.LogManager.log("Error", "Could NOT create monitor to sync with the dispatcher, details: " + com.dragonflow.Utils.FileUtils.stackTraceText(exception));
                flag = false;
                atomicmonitor = null;
            }
        }
        if(s2.equals("0"))
        {
            printProgressMessage("Undo schedule for " + com.dragonflow.Utils.TextUtils.getValue(hashmap, "_name") + "<BR>");
        } else
        {
            printProgressMessage(s1 + " " + com.dragonflow.Utils.TextUtils.getValue(hashmap, "_name") + "<BR>");
        }
        if(s1.equals("Disable"))
        {
            if(flag && atomicmonitor != null)
            {
                siteviewgroup.notifyMonitorDeletion(atomicmonitor);
            }
            if(s3.length() > 0)
            {
                if(s3.equals("undo_temp_alert_disable"))
                {
                    hashmap.put("_alertDisabled", "");
                } else
                {
                    hashmap.put("_alertDisabled", s3);
                }
            } else
            {
                if(s2.length() == 0)
                {
                    hashmap.put("_disabled", "checked");
                } else
                if(s2.equals("0"))
                {
                    hashmap.put("_timedDisable", "");
                } else
                {
                    hashmap.put("_timedDisable", s2);
                }
                hashmap.put("_disabledDescription", s4);
            }
        } else
        if(s1.equals("Enable"))
        {
            if(s3.equals("true"))
            {
                hashmap.put("_alertDisabled", "");
            } else
            {
                hashmap.put("_timedDisable", "");
                hashmap.put("_disabledDescription", "");
                if(s2.length() == 0)
                {
                    hashmap.put("_disabled", "");
                }
                if(flag && atomicmonitor != null && atomicmonitor.isDispatcher())
                {
                    siteviewgroup.checkDispatcherForStart(atomicmonitor);
                }
            }
        } else
        if(s1.equals("Replace") && as.length > 0 && com.dragonflow.SiteView.Monitor.isMonitorFrame(hashmap))
        {
            printProgressMessage(com.dragonflow.Utils.TextUtils.replaceInHashMap(hashmap, as, EXCLUDE_MAP));
        }
        refreshMonitor(s, s6, s1);
    }

    public static void acknowledgeLog(String s, String s1, String s2, String s3, String s4, String s5, String s6)
    {
        com.dragonflow.Log.LogManager.log("Operator", s + "\t" + s1 + "\t" + s2 + "\t" + s3 + "\t" + s4 + "\t" + s5 + "\t" + s6);
    }

    private void getMonitorInfo(String s)
        throws Exception
    {
        if(s == null)
        {
            return;
        }
        int i = s.indexOf(' ');
        if(i >= 0)
        {
            String s1 = com.dragonflow.Utils.I18N.toDefaultEncoding(s.substring(0, i));
            String s2 = s.substring(i + 1);
            jgl.Array array = getGroupFrames(s1);
            infoState = com.dragonflow.Page.managePage.findMonitor(array, s2);
            String s3 = s1 + com.dragonflow.SiteView.SiteViewGroup.ID_SEPARATOR + s2;
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            infoMonitor = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(s3);
            infoGroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s1);
        }
    }

    private void acknowledgeProperties(com.dragonflow.SiteView.Monitor monitor, String s, String s1, String s2, String s3, boolean flag)
    {
        if(flag)
        {
            String s4 = monitor.getProperty(com.dragonflow.SiteView.Monitor.pCategory);
            long l = monitor.getPropertyAsLong(com.dragonflow.SiteView.Monitor.pLastUpdate);
            Long long1 = new Long(com.dragonflow.SiteView.Platform.timeMillis() - l);
            monitor.setProperty(com.dragonflow.SiteView.Monitor.pAcknowledgedDelay, long1);
            monitor.setProperty(com.dragonflow.SiteView.Monitor.pAcknowledgedState, s4);
            monitor.setProperty(com.dragonflow.SiteView.Monitor.pAcknowledgeComment, s2);
            monitor.setProperty(com.dragonflow.SiteView.Monitor.pAcknowledged, com.dragonflow.Utils.TextUtils.dateToString(com.dragonflow.SiteView.Platform.timeMillis()));
            monitor.setProperty(com.dragonflow.SiteView.Monitor.pAcknowledgeUser, s);
            monitor.setProperty(com.dragonflow.SiteView.Monitor.pAcknowledgeUserIP, s1);
            monitor.setProperty(com.dragonflow.SiteView.Monitor.pAcknowledgeAlertDisabled, s3);
            if(infoGroup != null)
            {
                infoGroup.saveDynamic();
            }
            com.dragonflow.Page.managePage.acknowledgeLog("Acknowledge", s, s1, monitor.getFullID(), s4, long1.toString(), s2);
        } else
        {
            monitor.unsetProperty(com.dragonflow.SiteView.Monitor.pAcknowledged);
            monitor.unsetProperty(com.dragonflow.SiteView.Monitor.pAcknowledgedDelay);
            monitor.unsetProperty(com.dragonflow.SiteView.Monitor.pAcknowledgedState);
            monitor.unsetProperty(com.dragonflow.SiteView.Monitor.pAcknowledgeComment);
            monitor.unsetProperty(com.dragonflow.SiteView.Monitor.pAcknowledgeUser);
            monitor.unsetProperty(com.dragonflow.SiteView.Monitor.pAcknowledgeUserIP);
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)monitor.getOwner();
            if(monitor.isAlertTemporarilyDisabled() && monitor.getProperty(com.dragonflow.SiteView.Monitor.pAcknowledgeAlertDisabled).length() > 0)
            {
                monitor.unsetProperty(com.dragonflow.SiteView.Monitor.pAlertDisabled);
                monitor.unsetProperty(com.dragonflow.SiteView.Monitor.pTimedDisable);
                monitor.unsetProperty(com.dragonflow.SiteView.Monitor.pDisabled);
            }
            monitor.unsetProperty(com.dragonflow.SiteView.Monitor.pAcknowledgeAlertDisabled);
            if(monitorgroup != null)
            {
                monitorgroup.saveDynamic();
            }
            com.dragonflow.Page.managePage.acknowledgeLog("AcknowledgeClear", monitor.getFullID(), "", "", "", "", "");
        }
    }

    public void acknowledgeMonitor(String s, String s1, String s2, String s3, String s4, boolean flag)
        throws Exception
    {
        if(s1.length() <= 0)
        {
            s1 = "administrator";
        }
        getMonitorInfo(com.dragonflow.Utils.I18N.toNullEncoding(s));
        if(infoMonitor != null)
        {
            String s5 = com.dragonflow.Utils.TextUtils.getValue(infoState, "_class");
            if(s5.equals("SubGroup"))
            {
                String s6 = com.dragonflow.Utils.I18N.toDefaultEncoding(com.dragonflow.Utils.TextUtils.getValue(infoState, "_group"));
                acknowledgeProperties(infoMonitor, s1, s2, s3, s4, flag);
                acknowledgeGroup(s6, s1, s2, s3, s4, flag);
            }
            acknowledgeProperties(infoMonitor, s1, s2, s3, s4, flag);
        }
    }

    public void acknowledgeGroup(String s, String s1, String s2, String s3, String s4, boolean flag)
        throws Exception
    {
        jgl.Array array = null;
        try
        {
            array = getGroupFrames(s);
        }
        catch(Exception exception)
        {
            com.dragonflow.Log.LogManager.log("Error", "Problem with Acknowledge: " + exception);
            throw exception;
        }
        String s5 = com.dragonflow.Page.managePage.getGroupName(array, s);
        printProgressMessage("Acknowledge" + s5 + " Group<BR>");
        for(int i = 1; i < array.size(); i++)
        {
            jgl.HashMap hashmap = (jgl.HashMap)array.at(i);
            String s6 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_class");
            if(s6.equals("SubGroup"))
            {
                String s7 = com.dragonflow.Utils.I18N.toDefaultEncoding(com.dragonflow.Utils.TextUtils.getValue(hashmap, "_group"));
                if(s7.length() != 0)
                {
                    acknowledgeGroup(s7, s1, s2, s3, s4, flag);
                }
            }
            String s8 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_id");
            acknowledgeMonitor(s + " " + s8, s1, s2, s3, s4, flag);
        }

    }

    private String acknowledgeFromPortal(String s)
    {
        com.dragonflow.SiteView.SiteViewObject siteviewobject = com.dragonflow.SiteView.Portal.getSiteViewForID(request.getValue("group"));
        String s1 = "http://" + siteviewobject.getProperty("_server") + "/SiteView/cgi/go.exe/SiteView";
        String s2 = "";
        String s3 = "";
        String s4 = request.getValue("account");
        if(s4.equals("administrator"))
        {
            s2 = siteviewobject.getProperty("_username");
            s3 = siteviewobject.getProperty("_password");
        } else
        {
            s2 = request.user.getProperty("_login");
            s3 = request.user.getProperty("_password");
            jgl.Array array = new Array();
            array.add(new String("page=login"));
            array.add(new String("operation=Login"));
            array.add(new String("_login=" + s2));
            array.add(new String("_password=" + s3));
            int i = 60000;
            StringBuffer stringbuffer = new StringBuffer();
            long l = 50000L;
            String s5 = new String("");
            long al[] = com.dragonflow.StandardMonitor.URLMonitor.checkURL(com.dragonflow.Utils.SocketSession.getSession(null), s1, "", "", "", "", "", array, s2, s3, "", stringbuffer, l, "", 0, i, null);
            if(al[0] == 200L)
            {
                s5 = stringbuffer.toString();
            }
            if(!s5.equals(""))
            {
                int k = s5.indexOf("/acc") + (new String("/accounts/")).length();
                s4 = s5.substring(k);
                int i1 = s4.indexOf("/htdocs/");
                s4 = s4.substring(0, i1);
            }
        }
        jgl.Array array1 = new Array();
        array1.add(new String("page=manage"));
        array1.add(new String("operation=" + s));
        array1.add(new String("account=" + s4));
        array1.add(new String("monitor1=" + request.getValue("monitor1")));
        array1.add(new String("acknowledgeComment=" + request.getValue("acknowledgeComment")));
        if(request.getValue("disable_alert_time").length() > 0)
        {
            array1.add(new String("disable_alert_time=" + request.getValue("disable_alert_time")));
            array1.add(new String("disable_alert_units=" + request.getValue("disable_alert_units")));
        } else
        if(request.getValue("disableAlertStart").length() > 0)
        {
            array1.add(new String("disableAlertStart=" + request.getValue("disableAlertStart")));
            array1.add(new String("disableAlertEnd=" + request.getValue("disableAlertEnd")));
        }
        int j = 60000;
        StringBuffer stringbuffer1 = new StringBuffer();
        long l1 = 50000L;
        String s6 = null;
        long al1[] = com.dragonflow.StandardMonitor.URLMonitor.checkURL(com.dragonflow.Utils.SocketSession.getSession(null), s1, "", "", "", "", "", array1, s2, s3, "", stringbuffer1, l1, "", 0, j, null);
        if(al1[0] == 200L)
        {
            s6 = com.dragonflow.StandardMonitor.URLMonitor.getHTTPContent(stringbuffer1.toString());
        }
        if(s6 != null)
        {
            s6 = s6.substring(s6.indexOf("</FONT>") + 10);
            s6 = s6.substring(0, s6.indexOf("Done") - 6);
        }
        return s6;
    }

    private void syncWithSiteView()
    {
        String s = request.getValue("portalserver");
        s = s.substring(0, s.indexOf(':'));
        try
        {
            jgl.Array array = com.dragonflow.Properties.FrameFile.readFromFile(com.dragonflow.SiteView.Portal.PORTAL_SERVERS_CONFIG_PATH);
            jgl.HashMap hashmap = com.dragonflow.Page.portalPreferencePage.findFrameByID(array, s);
            com.dragonflow.Page.portalServerPage.syncRemoteSiteView(hashmap, outputStream);
        }
        catch(Exception exception)
        {
            printError("There was a problem reading the server.", exception.toString(), "/SiteView/?account=" + request.getAccount());
        }
    }

    public void printBody()
        throws Exception
    {
        String s = request.getValue("operation");
        if(s.equals("Refresh"))
        {
            if(!request.actionAllowed("_groupRefresh"))
            {
                throw new HTTPRequestException(557);
            }
        } else
        if(s.equals("Disable") || s.equals("Enable"))
        {
            if(!request.actionAllowed("_groupDisable") && !request.actionAllowed("_monitorDisable"))
            {
                throw new HTTPRequestException(557);
            }
        } else
        if(!s.equals("") && !request.actionAllowed("_groupEdit") && !s.startsWith("Acknowledge"))
        {
            throw new HTTPRequestException(557);
        }
        if(s.length() != 0 && !s.equals("List") && !s.startsWith("Apply") && !s.startsWith("Select"))
        {
            printManageForm(s);
        } else
        {
            printListForm();
        }
    }

    public static String getStartTimeHTML(long l)
    {
        java.util.Date date = com.dragonflow.SiteView.Platform.makeDate();
        l *= 1000L;
        return com.dragonflow.Page.managePage.getTimeHTML(new Date(date.getTime() + l), "start");
    }

    public static String getEndTimeHTML(long l)
    {
        java.util.Date date = com.dragonflow.SiteView.Platform.makeDate();
        l *= 1000L;
        return com.dragonflow.Page.managePage.getTimeHTML(new Date(date.getTime() + (long)(com.dragonflow.Utils.TextUtils.HOUR_SECONDS * 1000) + l), "end");
    }

    private java.util.Enumeration getExistingSchedule(com.dragonflow.SiteView.SiteViewGroup siteviewgroup)
    {
        jgl.HashMap hashmap = new HashMap();
        for(java.util.Enumeration enumeration = request.getValues("group"); enumeration.hasMoreElements();)
        {
            jgl.HashMap hashmap1 = new HashMap();
            String s = (String)enumeration.nextElement();
            try
            {
                hashmap1 = getExistingGroupSchedule(s, siteviewgroup);
            }
            catch(Exception exception) { }
            java.util.Enumeration enumeration2 = hashmap1.keys();
            while(enumeration2.hasMoreElements()) 
            {
                String s2 = enumeration2.nextElement().toString();
                String s5 = hashmap1.get(s2).toString();
                if(!s5.equals("") && s5 != null)
                {
                    hashmap.add(s2, s5);
                }
            }
        }

        java.util.Enumeration enumeration1 = request.getValues("monitor");
        Object obj = null;
        while(enumeration1.hasMoreElements()) 
        {
            String s1 = (String)enumeration1.nextElement();
            if(com.dragonflow.Page.treeControl.useTree())
            {
                s1 = com.dragonflow.HTTP.HTTPRequest.decodeString(s1);
            }
            int i = s1.indexOf(' ');
            String s3 = "";
            String s6 = "";
            if(i >= 0)
            {
                String s4 = s1.substring(0, i);
                String s7 = s1.substring(i + 1);
                String s8 = getExistingMonitorSchedule(s4, s7, siteviewgroup);
                jgl.HashMap hashmap2 = new HashMap();
                if(!s8.equals("SubGroup"))
                {
                    if(s8.length() > 0)
                    {
                        hashmap.add(s4 + "/" + s7, s8);
                    }
                } else
                {
                    try
                    {
                        com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(s4 + '/' + s7);
                        String s9 = com.dragonflow.Utils.I18N.toDefaultEncoding(monitor.getProperty("_group"));
                        hashmap2 = getExistingGroupSchedule(s9, siteviewgroup);
                    }
                    catch(Exception exception1) { }
                    java.util.Enumeration enumeration3 = hashmap2.keys();
                    while(enumeration3.hasMoreElements()) 
                    {
                        String s10 = enumeration3.nextElement().toString();
                        String s11 = hashmap2.get(s10).toString();
                        if(!s11.equals("") && s11 != null)
                        {
                            hashmap.add(s10, s11);
                        }
                    }
                }
            }
        }
        return hashmap.elements();
    }

    private String getExistingMonitorSchedule(String s, String s1, com.dragonflow.SiteView.SiteViewGroup siteviewgroup)
    {
        String s2 = "";
        String s3 = "";
        String s5 = "";
        String s6 = "";
        com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(com.dragonflow.Utils.I18N.toDefaultEncoding(s) + '/' + s1);
        if(monitor != null)
        {
            s2 = monitor.getProperty("_timedDisable");
            s6 = monitor.getProperty("_class");
        }
        if(!s6.equals("SubGroup"))
        {
            if(s2.length() > 0 && s2.indexOf(";") >= 0)
            {
                String s4 = monitor.getProperty("_name");
                int i = s2.indexOf(";");
                String s7 = s2.substring(0, i);
                String s8 = s2.substring(i + 1);
                java.util.Date date = com.dragonflow.Utils.TextUtils.stringToDate(s7);
                java.util.Date date1 = com.dragonflow.Utils.TextUtils.stringToDate(s8);
                boolean flag = date != null && date.getTime() > com.dragonflow.SiteView.Platform.timeMillis() || date != null && date.getTime() < com.dragonflow.SiteView.Platform.timeMillis() && date1 != null && date1.getTime() > com.dragonflow.SiteView.Platform.timeMillis();
                if(flag)
                {
                    s5 = "Monitor " + s + ": " + "<B>" + s4 + " </B> is disabled from " + s7 + " to " + s8;
                }
            }
        } else
        {
            s5 = "SubGroup";
        }
        return s5;
    }

    private jgl.HashMap getExistingGroupSchedule(String s, com.dragonflow.SiteView.SiteViewGroup siteviewgroup)
        throws Exception
    {
        jgl.Array array = null;
        jgl.HashMap hashmap = new HashMap();
        try
        {
            array = getGroupFrames(s);
        }
        catch(Exception exception)
        {
            com.dragonflow.Log.LogManager.log("Error", "Problem with getting group frames for existing disable schedule: " + exception);
            hashmap.add(s, "SiteView was unable to retrieve " + s + " group");
            throw exception;
        }
label0:
        for(int i = 1; i < array.size(); i++)
        {
            jgl.HashMap hashmap1 = (jgl.HashMap)array.at(i);
            String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_class");
            if(s1.equals("SubGroup"))
            {
                String s2 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_group");
                if(s2.length() == 0)
                {
                    continue;
                }
                jgl.HashMap hashmap2 = getExistingGroupSchedule(s2, siteviewgroup);
                java.util.Enumeration enumeration = hashmap2.keys();
                do
                {
                    String s5;
                    String s6;
                    do
                    {
                        if(!enumeration.hasMoreElements())
                        {
                            continue label0;
                        }
                        s5 = enumeration.nextElement().toString();
                        s6 = hashmap2.get(s5).toString();
                    } while(s6.equals("") || s6 == null);
                    hashmap.add(s5, s6);
                } while(true);
            }
            String s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_id");
            if(s3.equals(""))
            {
                continue;
            }
            String s4 = getExistingMonitorSchedule(s, s3, siteviewgroup);
            if(!s4.equals("") && s4 != null)
            {
                hashmap.add(s + "/" + s3, s4);
            }
        }

        return hashmap;
    }

    public static void main(String args[])
        throws java.io.IOException
    {
        com.dragonflow.Page.managePage managepage = new managePage();
        managepage.outputStream = new PrintWriter(System.out);
        if(args.length > 0)
        {
            managepage.args = args;
        }
        managepage.handleRequest();
    }

    static 
    {
        EXCLUDE_MAP = null;
        EXCLUDE_MAP = new HashMap();
        EXCLUDE_MAP.put("_parent", "exclude");
        EXCLUDE_MAP.put("_group", "exclude");
        EXCLUDE_MAP.put("_class", "exclude");
        EXCLUDE_MAP.put("_id", "exclude");
        EXCLUDE_MAP.put("_nextID", "exclude");
        EXCLUDE_MAP.put("_nextConditionID", "exclude");
        EXCLUDE_MAP.put("_timedDisable", "exclude");
    }
}
