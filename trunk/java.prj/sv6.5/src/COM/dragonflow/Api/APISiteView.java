/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.Api;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Timer;
import java.util.Vector;

import jgl.Array;
import jgl.HashMap;
import COM.dragonflow.HTTP.HTTPRequest;
import COM.dragonflow.Log.LogManager;
import COM.dragonflow.Properties.StringProperty;
import COM.dragonflow.SiteView.CompareSlot;
import COM.dragonflow.SiteView.FindRunningMonitors;
import COM.dragonflow.SiteView.Platform;
import COM.dragonflow.SiteViewException.SiteViewOperationalException;
import COM.dragonflow.SiteViewException.SiteViewParameterException;
import COM.dragonflow.StandardMonitor.ADReplicationMonitor;
import COM.dragonflow.StandardMonitor.Exchange2k3MailboxMonitor;
//import COM.dragonflow.StandardMonitor.SiebelCmdLineMonitor;
//import COM.dragonflow.TopazIntegration.TopazServerSettings;
import COM.dragonflow.Utils.URLInfo;
import COM.dragonflow.Utils.WSDLParser;

// Referenced classes of package COM.dragonflow.Api:
// SSHealthStats, SSInstanceProperty, APIPreference, APIMonitor,
// APIGroup, APIAlert, APIReport, SSPropertyDetails

public class APISiteView
{
    class HeartbeatTask extends java.util.TimerTask
        implements java.lang.Runnable
    {

        private java.lang.String host;
        private int port;

        public void run()
        {
            try
            {
                byte abyte0[] = new byte[11];
                abyte0[0] = 126;
                abyte0[1] = 126;
                java.util.Date date = new Date();
                java.lang.String s = (new Long(date.getTime())).toString();
                s = s + "@" + host + "@" + (new Integer(port)).toString();
                int i = s.length();
                java.lang.String s1 = (new Integer(i)).toString();
                byte abyte1[] = s.getBytes();
                int j = 6 - s1.length();
                for(int k = 0; j < 6; k++)
                {
                    abyte0[j + 2] = java.lang.Byte.decode(s1.substring(k, k + 1)).byteValue();
                    j++;
                }

                abyte0[8] = 1;
                char ac[] = new char[abyte1.length + 9];
                for(int l = 0; l < 9; l++)
                {
                    ac[l] = (char)abyte0[l];
                }

                for(int i1 = 0; i1 < abyte1.length; i1++)
                {
                    ac[i1 + 9] = (char)abyte1[i1];
                }

                COM.dragonflow.Log.LogManager.log("SSEELog", new String(ac));
            }
            catch(java.lang.Exception exception)
            {
                exception.printStackTrace();
            }
        }

        public HeartbeatTask(java.lang.String s, int i)
        {
            super();
            host = s;
            port = i;
        }
    }


    protected COM.dragonflow.SiteView.User user;
    protected java.lang.String account;
    protected boolean debug;
    protected jgl.HashMap groups;
    private static final double CURRENT_API_VERSION = 2D;
    private static final java.lang.String SITEVIEW_DATE_FORMAT = "EEE MM-dd-yyyy HH:mm:ss ('GMT'Z)";
    protected static java.util.Vector siteViewObjects = null;
    protected static java.util.Vector ssChildObjects = null;
    protected static java.util.HashMap ssRequiredProperties = null;
    public static int FILTER_ALL = 0;
    public static int FILTER_CONFIGURATION_ADD_ALL = 1;
    public static int FILTER_CONFIGURATION_ADD_BASIC = 2;
    public static int FILTER_CONFIGURATION_ADD_ADVANCED = 3;
    public static int FILTER_CONFIGURATION_EDIT_ALL = 4;
    public static int FILTER_CONFIGURATION_EDIT_BASIC = 5;
    public static int FILTER_CONFIGURATION_EDIT_ADVANCED = 6;
    public static int FILTER_CONFIGURATION_ALL = 7;
    public static int FILTER_CONFIGURATION_ADD_ALL_NOT_EMPTY = 8;
    public static int FILTER_CONFIGURATION_ADD_BASIC_NOT_EMPTY = 9;
    public static int FILTER_CONFIGURATION_ADD_ADVANCED_NOT_EMPTY = 10;
    public static int FILTER_CONFIGURATION_EDIT_ALL_NOT_EMPTY = 11;
    public static int FILTER_CONFIGURATION_EDIT_BASIC_NOT_EMPTY = 12;
    public static int FILTER_CONFIGURATION_EDIT_ADVANCED_NOT_EMPTY = 13;
    public static int FILTER_CONFIGURATION_ALL_NOT_EMPTY = 14;
    public static int FILTER_CONFIGURATION_ADD_REQUIRED = 15;
    public static int FILTER_RUNTIME_ALL = 16;
    public static int FILTER_RUNTIME_MEASUREMENTS = 17;
    public static int PREREQ_OP = 18;
    public static int FILTER_ALERT_ASSOCIATED = 19;
    public static final java.lang.String TOPAZ_LOG_ONLY_MONITOR_DATA = "_logOnlyMonitorData";
    public static final java.lang.String TOPAZ_LOG_ONLY_THRESHOLD_MEAS = "_logOnlyThresholdMeas";
    public static final java.lang.String TOPAZ_ONLY_STATUS_CHANGES = "_onlyStatusChanges";
    public static final java.lang.String OS_WINDOWS = "WIN";
    public static final java.lang.String OS_UNIX = "UNIX";
    protected static java.util.HashMap apiLookup = new java.util.HashMap();
    protected static java.util.Timer timer = null;
    private static java.lang.String savedRespondHostname = null;
    public static final java.lang.String SSM_SOL_ACTIVE_DIR = "Active Directory";
    private static final java.lang.String SSM_SOL_EXCHANGE_SERVER_55 = "Exchange 5.5";
    private static final java.lang.String SSM_SOL_EXCHANGE_SERVER_2000 = "Exchange 2000";
    private static final java.lang.String SSM_SOL_EXCHANGE_SERVER_2003 = "Exchange 2003";
    private static java.text.DateFormat mSiteViewDisableFormat = new SimpleDateFormat("HH:mm:ss MM/dd/yyyy");
    private static java.text.DateFormat mAPIDisableDateFormat = new SimpleDateFormat("MM/dd/yy HH:mm");
    static final boolean $assertionsDisabled; /* synthetic field */

    public APISiteView()
    {
        user = null;
        account = "";
        debug = false;
        groups = null;
        account = "administrator";
        user = COM.dragonflow.SiteView.User.getUserForAccount(account);
        groups = new HashMap();
    }

    public static double getCurrentApiVersion()
    {
        return 2D;
    }

    public void enableRealTimeStatusInformation(java.lang.String s, int i, java.lang.String s1, int j, long l, java.lang.String s2)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            if(savedRespondHostname == null || savedRespondHostname.equals(s))
            {
                COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                siteviewgroup.registerSSEELogger(s, i, s1, j, s2);
                enableHeartbeats(s1, j, l);
                savedRespondHostname = s;
                COM.dragonflow.Log.LogManager.log("RunMonitor", "SiteView is now reporting status and owned by: " + s + ":" + (new Integer(i)).toString());
            } else
            {
                COM.dragonflow.Log.LogManager.log("RunMonitor", "Ignoring enableRealTimeStatus from a alternate configuration console: " + s + ":" + (new Integer(i)).toString());
            }
        }
        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "enableRealTimeStatusInformation"
            }, 0L, exception.getMessage());
        }
    }

    public void disableRealTimeStatusInformation(java.lang.String s, int i)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            if(savedRespondHostname.equals(s))
            {
                COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                siteviewgroup.unregisterSSEELogger();
                disableHeartbeats();
                savedRespondHostname = null;
                COM.dragonflow.Log.LogManager.log("RunMonitor", "SiteView is no longer owned or reporting status from: " + s + ":" + (new Integer(i)).toString());
            } else
            {
                COM.dragonflow.Log.LogManager.log("RunMonitor", "Ignoring disableRealTimeStatus from: " + s);
            }
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "disableRealTimeStatusInformation"
            }, 0L, exception.getMessage());
        }
    }

    public java.util.Vector getSiteViewInfo(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.util.Vector vector = new Vector();
        try
        {
            java.lang.String s1 = "unknown";
            java.lang.String s2 = "unknown";
            java.lang.String s3 = "unknown";
            try
            {
                java.lang.String s4 = java.lang.System.getProperty("os.name").toUpperCase();
                s3 = java.lang.System.getProperty("os.version");
                s2 = s4;
                if(s4.startsWith("WINDOWS"))
                {
                    s1 = "WIN";
                } else
                if(s4.equals("IRIX"))
                {
                    s1 = "UNIX";
                } else
                if(s4.equals("SOLARIS") || s4.equals("SUNOS"))
                {
                    s1 = "UNIX";
                } else
                if(s4.equals("HP-UX"))
                {
                    s1 = "UNIX";
                } else
                if(s4.equals("LINUX"))
                {
                    s1 = "UNIX";
                }
            }
            catch(java.lang.Exception exception1)
            {
                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                    "APISiteView", "getSiteViewInfo init"
                }, 0L, exception1.getMessage());
            }
            jgl.HashMap hashmap = new HashMap();
            if(s1 != null)
            {
                hashmap.put("platform", s1);
            } else
            {
                hashmap.put("platform", "unavailble");
            }
            hashmap.put("osType", s2);
            hashmap.put("osVersion", s3);
            java.lang.String s5 = COM.dragonflow.SiteView.Platform.getVersion();
            java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s5, " ");
            java.lang.String s6 = as[0];
            java.lang.String s7 = as[1] + " " + as[2];
            java.lang.String s8 = as[3];
            java.lang.String s9 = as[5];
            hashmap.put("ssVersion", s6);
            hashmap.put("ssBuildTime", s7);
            hashmap.put("ssBuildDate", s8);
            hashmap.put("ssBuildNumber", s9);
            vector.add(hashmap);
        }
        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "getSiteViewInfo"
            }, 0L, exception.getMessage());
        }
        return vector;
    }

    public void releaseSiteView()
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
//            COM.dragonflow.TopazIntegration.MAManager.releaseSiteView();
            COM.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = COM.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "releaseSiteView"
            }, 0L, exception.getMessage());
        }
    }

    public void controlSiteView(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            createSSEEDefaultUser();
//            if(COM.dragonflow.TopazIntegration.MAManager.isAttached())
//            {
//                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALREADY_ATTACHED, null);
//            }
//            COM.dragonflow.TopazIntegration.MAManager.attachToHost(s);
            COM.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = COM.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        }
        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "controlSiteView"
            }, 0L, exception.getMessage());
        }
    }

    public static void forceConfigurationRefresh()
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            COM.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = COM.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
            COM.dragonflow.SiteView.SiteViewGroup.updateStaticPages();
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "forceConfigurationRefresh"
            }, 0L, exception.getMessage());
        }
    }

    public COM.dragonflow.Api.SSHealthStats getCurrentMonitorsPerMinute()
    {
        java.lang.Float float1 = new Float(COM.dragonflow.SiteView.AtomicMonitor.monitorStats.getCountPerTimePeriod());
        return new SSHealthStats("Current Monitors Per Minute", null, "CURRENT_MONITORS_PER_MINUTE", float1, null);
    }

    public COM.dragonflow.Api.SSHealthStats getCurrentMonitorsRunning()
    {
        java.lang.Integer integer = new Integer(COM.dragonflow.SiteView.MonitorQueue.getRunningCount());
        return new SSHealthStats("Current Monitors Running", null, "CURRENT_MONITORS_RUNNING", integer, null);
    }

    public COM.dragonflow.Api.SSHealthStats getCurrentMonitorsWaiting()
    {
        java.lang.Integer integer = new Integer(COM.dragonflow.SiteView.MonitorQueue.readyMonitors.size());
        return new SSHealthStats("Current Monitors Waiting", null, "CURRENT_MONITORS_WAITING", integer, null);
    }

    public COM.dragonflow.Api.SSHealthStats getMaximumMonitorsPerMinute()
    {
        java.lang.Float float1 = new Float(COM.dragonflow.SiteView.AtomicMonitor.monitorStats.getMaximumCountPerTimePeriod());
        java.lang.Float float2 = new Float(COM.dragonflow.SiteView.AtomicMonitor.monitorStats.getMaximumCountPerTimePeriodTime());
        return new SSHealthStats("Maximum Monitors Per Minute", null, "MAXIMUM_MONITORS_PER_MINUTE", float1, float2);
    }

    public COM.dragonflow.Api.SSHealthStats getMaximumMonitorsRunning()
    {
        java.lang.Float float1 = new Float(COM.dragonflow.SiteView.AtomicMonitor.monitorStats.getMaximum());
        java.lang.Float float2 = new Float(COM.dragonflow.SiteView.AtomicMonitor.monitorStats.getMaximumTime());
        return new SSHealthStats("Maximum Monitors Running", null, "MAXIMUM_MONITORS_RUNNING", float1, float2);
    }

    public COM.dragonflow.Api.SSHealthStats getMaximumMonitorsWaiting()
    {
        java.lang.Float float1 = new Float(COM.dragonflow.SiteView.MonitorQueue.maxReadyMonitors);
        java.lang.Float float2 = new Float(COM.dragonflow.SiteView.MonitorQueue.maxReadyMonitorsTime);
        return new SSHealthStats("Maximum Monitors Waiting", null, "MAXIMUM_MONITORS_WAITING", float1, float2);
    }

    public COM.dragonflow.Api.SSHealthStats[] getRunningMonitorStats()
    {
        COM.dragonflow.SiteView.FindRunningMonitors findrunningmonitors = new FindRunningMonitors();
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        siteviewgroup.acceptVisitor(findrunningmonitors);
        java.util.Enumeration enumeration = findrunningmonitors.getResultsElements();
        java.util.Vector vector = new Vector();
        if(enumeration.hasMoreElements())
        {
            COM.dragonflow.Api.SSHealthStats sshealthstats;
            for(; enumeration.hasMoreElements(); vector.add(sshealthstats))
            {
                COM.dragonflow.SiteView.Monitor monitor = (COM.dragonflow.SiteView.Monitor)enumeration.nextElement();
                java.lang.String s = monitor.getProperty(COM.dragonflow.SiteView.Monitor.pName);
                java.lang.String s1 = monitor.currentStatus;
                java.lang.String s2 = "N/A";
                long l = monitor.getPropertyAsLong(COM.dragonflow.SiteView.Monitor.pLastUpdate);
                if(l > 0L)
                {
                    s2 = " (previous update at " + COM.dragonflow.Utils.TextUtils.prettyDate(new Date(l)) + ")";
                }
                java.lang.String s3 = monitor.getProperty(COM.dragonflow.SiteView.SiteViewObject.pOwnerID);
                COM.dragonflow.SiteView.Monitor monitor1 = (COM.dragonflow.SiteView.Monitor)siteviewgroup.getElement(s3);
                if(monitor1 != null)
                {
                    s3 = monitor1.getProperty(COM.dragonflow.SiteView.Monitor.pName);
                }
                sshealthstats = new SSHealthStats(s, s1, "RUNNING_MONITOR_STATS", "Last Update: " + s2, "Group: " + s3);
            }

        }
        COM.dragonflow.Api.SSHealthStats asshealthstats[] = new COM.dragonflow.Api.SSHealthStats[vector.size()];
        for(int i = 0; i < vector.size(); i++)
        {
            asshealthstats[i] = (COM.dragonflow.Api.SSHealthStats)vector.get(i);
        }

        return asshealthstats;
    }

    public java.util.Vector getWebServers(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.util.Vector vector = new Vector();
        try
        {
            vector = COM.dragonflow.SiteView.Platform.getWebServers(s);
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "getWebServers"
            }, 0L, exception.getMessage());
        }
        return vector;
    }

    public java.util.Vector getOSs()
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.util.Vector vector = new Vector();
        try
        {
            jgl.Array array = new Array();
            array = COM.dragonflow.SiteView.OSAdapter.getOSs(array);
            for(int i = 0; i < array.size(); i++)
            {
                vector.add(array.at(i));
            }

        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "getOSs", exception.getMessage()
            });
        }
        return vector;
    }

    public java.util.Vector getWebServiceFiles()
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.util.Vector vector = new Vector();
        java.io.File file = new File(COM.dragonflow.SiteView.Platform.getUsedDirectoryPath("templates.wsdl", account));
        if(!file.exists())
        {
            return vector;
        }
        try
        {
            java.lang.String as[] = file.list();
            for(int i = 0; i < as.length; i++)
            {
                java.lang.String s = as[i];
                if(s.endsWith(".wsdl"))
                {
                    vector.add(s);
                }
            }

        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "getWebServciceFiles", exception.getMessage()
            });
        }
        return vector;
    }

    public java.util.Vector getWebServiceMethodsAndURL(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.util.Vector vector = new Vector();
        try
        {
            java.lang.StringBuffer stringbuffer = new StringBuffer();
            COM.dragonflow.Utils.WSDLParser wsdlparser = null;
            java.lang.String s1 = "";
            if(s.indexOf("http") < 0)
            {
                java.lang.String s2 = COM.dragonflow.SiteView.Platform.getUsedDirectoryPath("templates.wsdl", account);
                s1 = s2 + "/" + s;
            } else
            {
                s1 = s;
            }
            wsdlparser = new WSDLParser();
            wsdlparser.readWSDL(s1, stringbuffer);
            if(stringbuffer.length() > 0)
            {
                throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_UNABLE_TO_READ_WSDLURL, new java.lang.String[] {
                    stringbuffer.toString()
                });
            }
            java.util.List list = wsdlparser.getOperationNames(stringbuffer);
            if(stringbuffer.length() > 0)
            {
                throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_UNABLE_TO_GENERATE_METHODNAME, new java.lang.String[] {
                    stringbuffer.toString()
                });
            }
            java.lang.String s3 = wsdlparser.getServiceEndpointURL(stringbuffer);
            if(stringbuffer.length() > 0)
            {
                throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_UNABLE_TO_READ_WSDLURL, new java.lang.String[] {
                    stringbuffer.toString()
                });
            }
            java.lang.String as[] = new java.lang.String[list.size()];
            for(int i = 0; i < list.size(); i++)
            {
                as[i] = (java.lang.String)list.get(i);
            }

            vector.add(as);
            vector.add(s3);
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "getWebServciceMethods", exception.getMessage()
            });
        }
        return vector;
    }

    public java.util.Vector getWebServiceArgs(java.lang.String s, java.lang.String s1)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.util.Vector vector = new Vector();
        try
        {
            java.lang.StringBuffer stringbuffer = new StringBuffer();
            COM.dragonflow.Utils.WSDLParser wsdlparser = null;
            java.lang.String s2 = "";
            if(s.indexOf("http") < 0)
            {
                java.lang.String s3 = COM.dragonflow.SiteView.Platform.getUsedDirectoryPath("templates.wsdl", account);
                s2 = s3 + "/" + s;
            } else
            {
                s2 = s;
            }
            wsdlparser = new WSDLParser();
            wsdlparser.readWSDL(s2, stringbuffer);
            if(stringbuffer.length() > 0)
            {
                throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_UNABLE_TO_READ_WSDLURL, new java.lang.String[] {
                    stringbuffer.toString()
                });
            }
            java.util.List list = wsdlparser.generateArgXMLforUI(s1, stringbuffer);
            if(stringbuffer.length() > 0)
            {
                throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_UNABLE_TO_GENERATE_ARGNAMES, new java.lang.String[] {
                    s1, stringbuffer.toString()
                });
            }
            java.lang.StringBuffer stringbuffer1 = new StringBuffer();
            java.lang.String s4 = wsdlparser.getOperationNamespace(s1, stringbuffer1, stringbuffer);
            if(stringbuffer.length() > 0)
            {
                throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_UNABLE_TO_GENERATE_NAMESPACE, new java.lang.String[] {
                    s1, stringbuffer.toString()
                });
            }
            java.lang.String s5 = stringbuffer1.toString();
            java.lang.String as[] = new java.lang.String[list.size()];
            for(int i = 0; i < list.size(); i++)
            {
                as[i] = (java.lang.String)list.get(i);
            }

            vector.add(as);
            vector.add(s4);
            vector.add(s5);
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "getWebServciceMethodsAndURL", exception.getMessage()
            });
        }
        return vector;
    }

    public void createSession(long l)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            COM.dragonflow.Utils.LUtils.createSession(l);
        }
        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_LICENCE_EXCEPTION);
        }
    }

    public void sendHeartbeat()
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            COM.dragonflow.Utils.LUtils.sendHeartbeat();
        }
        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_LICENCE_EXCEPTION);
        }
    }

    public void updateGeneralLicense(java.lang.String s, boolean flag)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            COM.dragonflow.Utils.LUtils.updateGeneralLicense(s, flag);
            COM.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = COM.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        }
        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_LICENCE_EXCEPTION);
        }
    }

    public void updateSpecialLicense(java.lang.String s, boolean flag)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            COM.dragonflow.Utils.LUtils.updateSpecialLicense(s, flag);
            COM.dragonflow.Api.APISiteView.refreshSSChildObjects();
            COM.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = COM.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        }
        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_LICENCE_EXCEPTION);
        }
    }

    public void shutdownSiteView()
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
			LogManager.log("Error", Platform.productName
                    + " shutting down..by APISiteView");
            //SiteViewMain.SiteViewSupport.ShutdownProcess(); dingbing.xu
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_LICENCE_EXCEPTION);
        }
    }

    public boolean isTopazConnected()
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        return false;
    }

    public boolean isAMIntegrationActivated(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        boolean flag = false;
//        try
//        {
//            flag = COM.dragonflow.TopazIntegration.TopazManager.getInstance().isAMServerIntegrationActived();
//            if(!flag)
//            {
//                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_CAN_NOT_RETRIEVE_TOPAZ_SETTINGS);
//            }
//            if(s == null)
//            {
//                flag = COM.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazPrimaryServerSettings() != null;
//            } else
//            {
//                flag = COM.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazServerSettings(s) != null;
//            }
//        }
//        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
//        {
//            siteviewexception.fillInStackTrace();
//            throw siteviewexception;
//        }
//        catch(java.lang.Exception exception)
//        {
//            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
//                "APISiteView", "isAMIntegrationActivated"
//            }, 0L, exception.getMessage());
//        }
        return flag;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @return
     * @throws COM.dragonflow.SiteViewException.SiteViewException
     */
    public boolean isUIControled()
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try {
		return false;
//        return COM.dragonflow.TopazIntegration.MAManager.isAttached();
        }
        catch (java.lang.Exception exception) {
        throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
            "APISiteView", "isUIControled"
        }, 0L, exception.getMessage());
        }
    }

    public boolean isServerRegistered(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        boolean flag = false;
        try
        {
//          flag = COM.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazServerSettings(s) != null;			
//            flag = COM.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazServerSettings(s) != null;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "isServerRegistered"
            }, 0L, exception.getMessage());
        }
        return flag;
    }

    public java.util.HashMap getFreeProfiles(java.util.HashMap hashmap)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.util.HashMap hashmap1 = new java.util.HashMap();
//        try
//        {
//            COM.dragonflow.TopazIntegration.TopazServerSettings topazserversettings = new TopazServerSettings(hashmap, true);
//            java.lang.StringBuffer stringbuffer = new StringBuffer();
//            int i = COM.dragonflow.TopazIntegration.TopazManager.getInstance().getFreeProfilesList(topazserversettings, stringbuffer, hashmap1);
//            if(i < 0)
//            {
//                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_CAN_NOT_FREE_PROFILES, new java.lang.String[] {
//                    stringbuffer.toString()
//                });
//            }
//        }
//        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
//        {
//            siteviewexception.fillInStackTrace();
//            throw siteviewexception;
//        }
//        catch(java.lang.Exception exception)
//        {
//            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
//                "APISiteView", "getFreeProfiles"
//            }, 0L, exception.getMessage());
//        }
        return hashmap1;
    }

    public boolean isTopazDisabled(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        boolean flag = true;
//        try
//        {
//            COM.dragonflow.TopazIntegration.TopazServerSettings topazserversettings = COM.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazServerSettings(s);
//            if(topazserversettings == null)
//            {
//                topazserversettings = COM.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazPrimaryServerSettings();
//            }
//            if(topazserversettings == null)
//            {
//                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MUST_BE_CONNECTED_TO_TOPAZ, new java.lang.String[] {
//                    "isTopazDisabled"
//                });
//            }
//            flag = topazserversettings.isDisabled();
//        }
//        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
//        {
//            siteviewexception.fillInStackTrace();
//            throw siteviewexception;
//        }
//        catch(java.lang.Exception exception)
//        {
//            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
//                "APISiteView", "isTopazDisabled"
//            }, 0L, exception.getMessage());
//        }
        return flag;
    }

    public void setTopazDisabled(java.lang.String s, boolean flag)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
//        try
//        {
//            if(isAMIntegrationActivated(s))
//            {
//                if(s == null)
//                {
//                    s = COM.dragonflow.TopazIntegration.AMSettingsManager.getPrimaryServerAddress();
//                }
//                COM.dragonflow.TopazIntegration.AMReturnValue amreturnvalue = flag ? COM.dragonflow.TopazIntegration.TopazManager.getInstance().disable(s) : COM.dragonflow.TopazIntegration.TopazManager.getInstance().enable(s, null);
//                if(!amreturnvalue.isOK())
//                {
//                    throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_CAN_NOT_DISABLE_TOPAZ, new java.lang.String[] {
//                        amreturnvalue.getErrorString()
//                    });
//                }
//                COM.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = COM.dragonflow.SiteView.DetectConfigurationChange.getInstance();
//                detectconfigurationchange.setConfigChangeFlag();
//            } else
//            {
//                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MUST_BE_CONNECTED_TO_TOPAZ, new java.lang.String[] {
//                    "setTopazDisabled"
//                });
//            }
//        }
//        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
//        {
//            siteviewexception.fillInStackTrace();
//            throw siteviewexception;
//        }
//        catch(java.lang.Exception exception)
//        {
//            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
//                "APISiteView", "setTopazDisabled"
//            }, 0L, exception.getMessage());
//        }
    }

    public void flushTopazData()
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
//        try
//        {
//            if(isAMIntegrationActivated(null))
//            {
//                COM.dragonflow.TopazIntegration.TopazManager.getInstance().flushDataReportingASync();
//            } else
//            {
//                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MUST_BE_CONNECTED_TO_TOPAZ, new java.lang.String[] {
//                    "flushTopazData"
//                });
//            }
//        }
//        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
//        {
//            siteviewexception.fillInStackTrace();
//            throw siteviewexception;
//        }
//        catch(java.lang.Exception exception)
//        {
//            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
//                "APISiteView", "flushTopazData"
//            }, 0L, exception.getMessage());
//        }
    }

    public void resyncTopazData(boolean flag)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            if(!isAMIntegrationActivated(null))
            {
                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MUST_BE_CONNECTED_TO_TOPAZ, new java.lang.String[] {
                    "resyncTopazData"
                });
            }
//            COM.dragonflow.TopazIntegration.TopazManager.getInstance().reSync(COM.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazPrimaryServerSettings(), flag);
        }
        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "resyncTopazData"
            }, 0L, exception.getMessage());
        }
    }

//    public void resetTopazProfile(java.lang.String s)
//        throws COM.dragonflow.SiteViewException.SiteViewException
//    {
//        try
//        {
//            if(s == null)
//            {
//                s = COM.dragonflow.TopazIntegration.AMSettingsManager.getPrimaryServerAddress();
//            }
//            if(s == null)
//            {
//                throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_TOPAZ_SERVER_ADDRESS_MISSING);
//            }
//            COM.dragonflow.TopazWatchdog.WatchdogConfig.clearWatchdogConfig(null, null);
//            COM.dragonflow.TopazIntegration.AMReturnValue amreturnvalue = COM.dragonflow.TopazIntegration.TopazManager.getInstance().reset(s);
//            if(!amreturnvalue.isOK())
//            {
//                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_CAN_NOT_RESET_TOPAX_PROFILES, new java.lang.String[] {
//                    amreturnvalue.getErrorString()
//                });
//            }
//            COM.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = COM.dragonflow.SiteView.DetectConfigurationChange.getInstance();
//            detectconfigurationchange.setConfigChangeFlag();
//        }
//        catch(java.lang.Exception exception)
//        {
//            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
//                "APISiteView", "resetTopazProfile"
//            }, 0L, exception.getMessage());
//        }
//    }

    public void deleteSiteView(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
//            COM.dragonflow.TopazIntegration.MAManager.releaseSiteView();
            COM.dragonflow.Api.APIReport.deleteQuickReports();
//            resetTopazProfile(s);
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "deleteTopazProfile"
            }, 0L, exception.getMessage());
        }
    }

//    public java.util.HashMap getServerSettingsByEntity(java.lang.String s)
//        throws COM.dragonflow.SiteViewException.SiteViewException
//    {
//        java.lang.String s1 = COM.dragonflow.TopazIntegration.TopazManager.getInstance().getServerAddressByEntity(s);
//        if(s1 == null)
//        {
//            return new java.util.HashMap();
//        } else
//        {
//            return getTopazServerSettings(s1);
//        }
//    }

//    public java.util.HashMap getTopazServerSettings(java.lang.String s)
//        throws COM.dragonflow.SiteViewException.SiteViewException
//    {
//        java.util.HashMap hashmap = new java.util.HashMap();
//        try
//        {
//            if(isAMIntegrationActivated(s))
//            {
//                if(s == null)
//                {
//                    s = COM.dragonflow.TopazIntegration.AMSettingsManager.getPrimaryServerAddress();
//                }
//                COM.dragonflow.TopazIntegration.TopazServerSettings topazserversettings = COM.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazServerSettings(s);
//                hashmap.put("profileId", topazserversettings.getProfileId());
//                hashmap.put("profileName", topazserversettings.getProfileName());
//                hashmap.put("location", topazserversettings.getLocation());
//                java.lang.String s1 = topazserversettings.getAdminServerUrl();
//                COM.dragonflow.Utils.URLInfo urlinfo = new URLInfo(s1);
//                hashmap.put("_topazAdminServer", urlinfo.getRawHost());
//                hashmap.put("_topazAdminUserName", topazserversettings.getTopazUserName());
//                hashmap.put("_topazAdminPassword", topazserversettings.getTopazUserPassword());
//                hashmap.put("_topazWebServerUserName", topazserversettings.getAdminServerAuthUserName());
//                hashmap.put("_topazWebServerPassword", topazserversettings.getAdminServerAuthPassword());
//                java.lang.String s2 = topazserversettings.getAgentServerUrl(false);
//                urlinfo = new URLInfo(s2);
//                hashmap.put("_topazAgentServer", urlinfo.getRawHost());
//                hashmap.put("_topazAgentWebServerUserName", topazserversettings.getAgentServerAuthPassword());
//                hashmap.put("_topazAgentWebServerPassword", topazserversettings.getAgentServerAuthPassword());
//                hashmap.put("_topazProxy", topazserversettings.getProxy());
//                hashmap.put("_topazProxyUser", topazserversettings.getProxyPassword());
//                hashmap.put("_topazProxyPassword", topazserversettings.getProxyUserName());
//                java.lang.String s3 = s1.startsWith("https") ? "on" : "";
//                java.lang.String s4 = s2.startsWith("https") ? "on" : "";
//                hashmap.put("_sslProtocol", s3);
//                hashmap.put("_agentSslProtocol", s4);
//            } else
//            {
//                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MUST_BE_CONNECTED_TO_TOPAZ, new java.lang.String[] {
//                    "getTopazServerSettings"
//                });
//            }
//        }
//        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
//        {
//            siteviewexception.fillInStackTrace();
//            throw siteviewexception;
//        }
//        catch(java.lang.Exception exception)
//        {
//            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
//                "APISiteView", "getTopazServerSettings"
//            }, 0L, exception.getMessage());
//        }
//        return hashmap;
//    }

//    public void registerTopazProfile(java.lang.String s, java.lang.String s1, java.util.HashMap hashmap)
//        throws COM.dragonflow.SiteViewException.SiteViewOperationalException
//    {
//        try
//        {
//            if(s == null || s.length() == 0)
//            {
//                if(s1 == null || s1.length() == 0)
//                {
//                    throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_PROFILE_NAME_IS_MISSING);
//                }
//                java.util.HashMap hashmap1 = getFreeProfiles(hashmap);
//                java.util.Iterator iterator = hashmap1.keySet().iterator();
//                while (iterator.hasNext()) {
//                    java.lang.String s2 = (java.lang.String)iterator.next();
//                    java.lang.String s3 = (java.lang.String)hashmap1.get(s2);
//                    if(s1.equalsIgnoreCase(s3))
//                    {
//                    s = s2;
//                    break;
//                    }
//                } 
//                if(s == null || s.length() == 0)
//                {
//                    throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_CANT_RETRIEVE_FREE_PROFILE_ID);
//                }
//            }
//            COM.dragonflow.TopazIntegration.TopazManager.getInstance().registerNew(s, s1, hashmap);
//            COM.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = COM.dragonflow.SiteView.DetectConfigurationChange.getInstance();
//            detectconfigurationchange.setConfigChangeFlag();
//        }
//        catch(java.lang.Exception exception)
//        {
//            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
//                "APISiteView", "registerTopazProfile"
//            }, 0L, exception.getMessage());
//        }
//    }
//
//    public void reRegisterTopazProfile(java.util.HashMap hashmap)
//        throws COM.dragonflow.SiteViewException.SiteViewException
//    {
//        try
//        {
//            java.lang.String s = (java.lang.String)hashmap.get("_topazAdminServer");
//            if(s == null)
//            {
//                throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_TOPAZ_SERVER_ADDRESS_MISSING);
//            }
//            if(isAMIntegrationActivated(s))
//            {
//                COM.dragonflow.TopazIntegration.TopazManager.getInstance().reRegister(hashmap);
//                COM.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = COM.dragonflow.SiteView.DetectConfigurationChange.getInstance();
//                detectconfigurationchange.setConfigChangeFlag();
//            } else
//            {
//                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MUST_BE_CONNECTED_TO_TOPAZ, new java.lang.String[] {
//                    "reRegisterTopazProfile"
//                });
//            }
//        }
//        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
//        {
//            siteviewexception.fillInStackTrace();
//            throw siteviewexception;
//        }
//        catch(java.lang.Exception exception)
//        {
//            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
//                "APISiteView", "reRegisterTopazProfile"
//            }, 0L, exception.getMessage());
//        }
//    }

//    public java.lang.String getTopazFullId(int i)
//        throws COM.dragonflow.SiteViewException.SiteViewException
//    {
//        java.lang.String s = "";
//        try
//        {
//            s = COM.dragonflow.TopazIntegration.TopazConfigManager.getInstance().getMonitorFullId(i);
//            if(s == null || s.length() == 0)
//            {
//                throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_UNASSOCIATED_TOPAZ_ID, new java.lang.String[] {
//                    (new Integer(i)).toString()
//                });
//            }
//        }
//        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
//        {
//            siteviewexception.fillInStackTrace();
//            throw siteviewexception;
//        }
//        catch(java.lang.Exception exception)
//        {
//            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
//                "APISiteView", "getTopazFullID"
//            }, 0L, exception.getMessage());
//        }
//        return s;
//    }

//    public java.util.Vector issueSiebelCmd(java.lang.String s)
//        throws COM.dragonflow.SiteViewException.SiteViewException
//    {
//        java.util.Vector vector = new Vector();
//        try
//        {
//            java.lang.StringBuffer stringbuffer = new StringBuffer();
//            java.lang.StringBuffer stringbuffer1 = new StringBuffer();
//            if(s.indexOf(" /u ") < 0 || s.indexOf(" /p ") < 0)
//            {
//                throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_API_SIEBEL_COMMAND_MALFORMED);
//            }
//            COM.dragonflow.StandardMonitor.SiebelCmdLineMonitor siebelcmdlinemonitor = new SiebelCmdLineMonitor();
//            java.lang.String as[][] = siebelcmdlinemonitor.runCommand(s, stringbuffer, stringbuffer1, null, true);
//            if(stringbuffer.length() > 0)
//            {
//                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_RUN_COMMAND, 0L, stringbuffer.toString());
//            }
//            java.lang.String as1[] = COM.dragonflow.Utils.TextUtils.split(stringbuffer1.toString(), " ");
//            if(as1.length > 0)
//            {
//                vector.add(as1);
//            }
//            if(as != null)
//            {
//                for(int i = 0; i < as.length; i++)
//                {
//                    vector.add(as[i]);
//                }
//
//            } else
//            {
//                vector.add(new java.lang.String[] {
//                    "No", "Response"
//                });
//            }
//        }
//        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
//        {
//            siteviewexception.fillInStackTrace();
//            throw siteviewexception;
//        }
//        catch(java.lang.Exception exception)
//        {
//            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
//                "APISiteView", "issueSiebelCmd"
//            }, 0L, exception.getMessage());
//        }
//        return vector;
//    }

    public java.util.Vector getSystemTime(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.util.Vector vector = new Vector();
        try
        {
            java.lang.StringBuffer stringbuffer = new StringBuffer();
            java.util.Calendar calendar = COM.dragonflow.SiteView.Platform.getSystemTime(s, stringbuffer);
            java.text.SimpleDateFormat simpledateformat = new SimpleDateFormat("EEE MM-dd-yyyy HH:mm:ss ('GMT'Z)");
            simpledateformat.setTimeZone(calendar.getTimeZone());
            java.util.Date date = calendar.getTime();
            vector.add(simpledateformat.format(date));
        }
        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "getSystemTime"
            }, 0L, exception.getMessage());
        }
        return vector;
    }

    public java.util.Vector getFileList(java.lang.String s, java.lang.String s1, java.lang.StringBuffer stringbuffer)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.util.Vector vector = new Vector();
        try
        {
            java.lang.String as[][];
            if((as = COM.dragonflow.SiteView.Platform.getFileList(s, s1, stringbuffer)) == null)
            {
                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_RUN_COMMAND, 0L, stringbuffer.toString());
            }
            for(int i = 0; i < as.length; i++)
            {
                vector.add(as[i]);
            }

        }
        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "getFileList"
            }, 0L, exception.getMessage());
        }
        return vector;
    }

    protected void createSSEEDefaultUser()
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.util.HashMap hashmap = new java.util.HashMap();
        hashmap.put("_preference", "true");
        hashmap.put("_monitorDisable", "true");
        hashmap.put("_groupRefresh", "true");
        hashmap.put("_progress", "true");
        hashmap.put("_alertAdhocReport", "true");
        hashmap.put("_reportToolbar", "true");
        hashmap.put("_preferenceTest", "true");
        hashmap.put("_reportDisable", "true");
        hashmap.put("_reportAdhoc", "true");
        hashmap.put("_reportGenerate", "true");
        hashmap.put("_login", "Flipper");
        hashmap.put("_alertRecentReport", "true");
        hashmap.put("_groupDisable", "true");
        hashmap.put("_monitorRecent", "true");
        hashmap.put("_monitorTools", "true");
        hashmap.put("_browse", "true");
        hashmap.put("_logs", "true");
        hashmap.put("_support", "true");
        hashmap.put("_reportEdit", "true");
        hashmap.put("_tools", "true");
        hashmap.put("_alertTest", "true");
        hashmap.put("_alertDisable", "true");
        hashmap.put("_monitorAcknowledge", "true");
        hashmap.put("_password", "Flipper");
        hashmap.put("_realName", "Flipper");
        boolean flag = false;
        int i = 0;
        COM.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new COM.dragonflow.Api.SSInstanceProperty[hashmap.size()];
        java.util.Set set = hashmap.keySet();
        for(java.util.Iterator iterator = set.iterator(); iterator.hasNext();)
        {
            java.lang.String s = (java.lang.String)iterator.next();
            assinstanceproperty[i++] = new SSInstanceProperty(s, hashmap.get(s));
        }

        COM.dragonflow.Api.APIPreference apipreference = new APIPreference();
        jgl.Array array = getUserFrames();
        java.util.Enumeration enumeration = array.elements();
        if(enumeration.hasMoreElements())
        {
            enumeration.nextElement();
        }
        while (enumeration.hasMoreElements()) {
            jgl.HashMap hashmap1 = (jgl.HashMap)enumeration.nextElement();
            java.lang.String s1 = (java.lang.String)hashmap1.get("_login");
            if(s1 != null && s1.equals("Flipper"))
            {
                flag = true;
            }
        } 
        if(!flag)
        {
            apipreference.create("UserInstancePreferences", assinstanceproperty);
        }
        COM.dragonflow.SiteView.SiteViewGroup.updateStaticPages();
        COM.dragonflow.SiteView.User.unloadUsers();
        COM.dragonflow.SiteView.User.loadUsers();
    }

    protected static void initSSChildObjects()
    {
        if(ssChildObjects == null && siteViewObjects == null)
        {
            ssChildObjects = new Vector();
            siteViewObjects = new Vector();
            try
            {
                java.io.File file = new File(COM.dragonflow.SiteView.Platform.getRoot() + "/classes/COM/dragonflow/Api");
                java.lang.String as[] = file.list();
                for(int i = 0; i < as.length; i++)
                {
                    if(as[i] != null && !as[i].startsWith("APISiteView") && as[i].endsWith(".class") && as[i].startsWith("API"))
                    {
                        try
                        {
                            int j = as[i].lastIndexOf(".class");
                            java.lang.String s = as[i].substring(3, j);
                            java.lang.String as1[] = new java.lang.String[3];
                            as1[0] = s;
                            as1[1] = "true";
                            as1[2] = "";
                            siteViewObjects.add(as1);
                            ssChildObjects.add(COM.dragonflow.Api.APISiteView.getObjects(s));
                        }
                        catch(java.lang.Throwable throwable1)
                        {
                            COM.dragonflow.Log.LogManager.log("Error", "APISiteView.initSSChildObjects failed with exception '" + throwable1.toString() + "' while processing file '" + as[i] + "'");
                        }
                    }
                }

            }
            catch(java.lang.Throwable throwable)
            {
                COM.dragonflow.Log.LogManager.log("Error", "Critical failure to initialize in APISiteView.initSSChildObjects with exception '" + throwable.toString() + "'");
            }
        }
    }

    public static void refreshSSChildObjects()
    {
        ssChildObjects = null;
        siteViewObjects = null;
        COM.dragonflow.Api.APISiteView.initSSChildObjects();
    }

    protected boolean isRequiredProperty(java.lang.String s)
    {
        boolean flag = false;
        if(ssRequiredProperties != null && ssRequiredProperties.get(s) != null)
        {
            flag = true;
        }
        return flag;
    }

    protected static void initRequiredPropertyArray()
    {
        if(ssRequiredProperties == null)
        {
            ssRequiredProperties = new java.util.HashMap();
            ssRequiredProperties.put("_server", "true");
            ssRequiredProperties.put("_hostname", "true");
            ssRequiredProperties.put("_machine", "true");
            ssRequiredProperties.put("_duration", "true");
            ssRequiredProperties.put("_counters", "true");
            ssRequiredProperties.put("_browse", "true");
            ssRequiredProperties.put("_fileName", "true");
            ssRequiredProperties.put("_index", "true");
            ssRequiredProperties.put("_community", "true");
            ssRequiredProperties.put("_content", "true");
            ssRequiredProperties.put("_username", "true");
            ssRequiredProperties.put("_password", "true");
            ssRequiredProperties.put("_duration", "true");
            ssRequiredProperties.put("_url", "true");
            ssRequiredProperties.put("_SMNPServer", "true");
            ssRequiredProperties.put("_popServer", "true");
            ssRequiredProperties.put("_popAccount", "true");
            ssRequiredProperties.put("_popUser", "true");
            ssRequiredProperties.put("_noFileCheckExists", "true");
            ssRequiredProperties.put("_securityPrincipal", "true");
            ssRequiredProperties.put("_securityCredential", "true");
            ssRequiredProperties.put("_urlProvider", "true");
            ssRequiredProperties.put("_timeout", "true");
            ssRequiredProperties.put("_requestAddress", "true");
            ssRequiredProperties.put("_database", "true");
            ssRequiredProperties.put("_BVHost", "true");
            ssRequiredProperties.put("_BVPort", "true");
        }
    }

    protected jgl.Array getPropertiesForClass(COM.dragonflow.SiteView.SiteViewObject siteviewobject, java.lang.String s, java.lang.String s1, int i)
        throws java.lang.Exception
    {
        jgl.Array array = new Array();
        jgl.Array array1 = siteviewobject.getProperties();
        array1 = COM.dragonflow.Properties.StringProperty.sortByOrder(array1);
        java.util.Enumeration enumeration = array1.elements();
        while (enumeration.hasMoreElements()) {
            boolean flag = false;
            COM.dragonflow.Properties.StringProperty stringproperty3 = (COM.dragonflow.Properties.StringProperty)enumeration.nextElement();
            int j = s.lastIndexOf(".");
            flag = returnProperty(stringproperty3, i, siteviewobject, s.substring(j + 1));
            if(flag)
            {
                array.add(stringproperty3);
            }
        }
        
        if(siteviewobject instanceof COM.dragonflow.SiteView.BrowsableMonitor)
        {
            COM.dragonflow.Properties.StringProperty stringproperty = new StringProperty("availableCounters", "", "Available Counters");
            array.add(stringproperty);
            COM.dragonflow.Properties.StringProperty stringproperty4 = new StringProperty("availableCountersHierarchical", "", "Available Counters Hierarchical");
            array.add(stringproperty4);
        } else
        if(siteviewobject instanceof COM.dragonflow.SiteView.ApplicationBase)
        {
            COM.dragonflow.Properties.StringProperty stringproperty1 = new StringProperty("availableObjects", "", "Available Objects");
            array.add(stringproperty1);
            COM.dragonflow.Properties.StringProperty stringproperty5 = new StringProperty("availableCounters", "", "Available Counters");
            array.add(stringproperty5);
            COM.dragonflow.Properties.StringProperty stringproperty7 = new StringProperty("availableInstances", "", "Available Instances");
            array.add(stringproperty7);
            COM.dragonflow.Properties.StringProperty stringproperty9 = new StringProperty("defaultCounters", "", "Default Counters");
            array.add(stringproperty9);
        } else
        if((siteviewobject instanceof COM.dragonflow.SiteView.NTCounterBase) || (siteviewobject instanceof COM.dragonflow.SiteView.PerfmonMonitorBase))
        {
            COM.dragonflow.Properties.StringProperty stringproperty2 = new StringProperty("counterObject", "", "Selected Counter Object");
            array.add(stringproperty2);
            COM.dragonflow.Properties.StringProperty stringproperty6 = new StringProperty("availableObjects", "", "Available Objects");
            array.add(stringproperty6);
            COM.dragonflow.Properties.StringProperty stringproperty8 = new StringProperty("availableCounters", "", "Available Counters");
            array.add(stringproperty8);
            COM.dragonflow.Properties.StringProperty stringproperty10 = new StringProperty("availableInstances", "", "Available Instances");
            array.add(stringproperty10);
            COM.dragonflow.Properties.StringProperty stringproperty11 = new StringProperty("defaultCounters", "", "Default Counters");
            array.add(stringproperty11);
        }
        return array;
    }

    protected static jgl.Array getObjects(java.lang.String s)
    {
        jgl.Array array = new Array();
        if(s.equals("Alert"))
        {
            s = "Action";
        }
        java.io.File file = new File(COM.dragonflow.SiteView.Platform.getRoot() + "/classes/COM/dragonflow/Standard" + s);
        java.lang.String as[] = file.list();
        if(as != null)
        {
            for(int i = 0; i < as.length; i++)
            {
                if(!as[i].endsWith(".class"))
                {
                    continue;
                }
                try
                {
                    int k = as[i].lastIndexOf(".class");
                    java.lang.String s1 = "COM.dragonflow.Standard" + s + "." + as[i].substring(0, k);
                    boolean flag = true;
                    if(s.equals("Monitor") && (flag = COM.dragonflow.Api.APIMonitor.isValidObject(s1, s)))
                    {
                        flag = COM.dragonflow.Api.APIMonitor.isAddableMonitor(s1);
                    }
                    if(flag)
                    {
                        java.lang.String as1[] = new java.lang.String[3];
                        as1[0] = s1;
                        as1[1] = "";
                        as1[2] = "true";
                        array.add(as1);
                    }
                }
                catch(java.lang.Throwable throwable)
                {
                    COM.dragonflow.Log.LogManager.log("Error", "APISiteView.getObjects(" + s + ") Standard directory handler failed with exception '" + throwable.toString() + "' while processing file '" + as[i] + "'");
                }
            }

        }
        file = new File(COM.dragonflow.SiteView.Platform.getRoot() + "/classes/Custom" + s);
        as = file.list();
        if(as != null)
        {
            for(int j = 0; j < as.length; j++)
            {
                if(!as[j].endsWith(".class"))
                {
                    continue;
                }
                try
                {
                    int l = as[j].lastIndexOf(".class");
                    java.lang.String s2 = "Custom" + s + "." + as[j].substring(0, l);
                    boolean flag1 = true;
                    if(s.equals("Monitor"))
                    {
                        flag1 = COM.dragonflow.Api.APIMonitor.isValidObject(s2, s);
                    }
                    if(flag1)
                    {
                        java.lang.String as2[] = new java.lang.String[3];
                        as2[0] = s2;
                        as2[1] = "";
                        as2[2] = "true";
                        array.add(as2);
                    }
                }
                catch(java.lang.Throwable throwable1)
                {
                    COM.dragonflow.Log.LogManager.log("Error", "APISiteView.getObjects(" + s + ") Custom directory handler failed with exception '" + throwable1.toString() + "' while processing file '" + as[j] + "'");
                }
            }

        }
        return array;
    }

    protected jgl.Array getGroupFrames(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        jgl.Array array = new Array();
        try
        {
            array = (jgl.Array)groups.get(s);
            array = ReadGroupFrames(s);
            groups.put(s, array);
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APIGroup", "getGroupFrames", exception.getMessage()
            });
        }
        return array;
    }

    protected jgl.Array ReadGroupFrames(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        jgl.Array array = new Array();
        try
        {
            if(!isGroupAllowedForAccount(s))
            {
                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_ACCESS_EXCEPTION, new java.lang.String[] {
                    user.toString(), s
                });
            }
            java.lang.String s1 = getGroupFilePath(s, ".mg");
            array = COM.dragonflow.Properties.FrameFile.readFromFile(s1);
            if(array.size() == 0)
            {
                array.add(new HashMap());
            }
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "copySubGroups", exception.getMessage()
            });
        }
        return array;
    }

    protected boolean isGroupAllowedForAccount(java.lang.String s, jgl.Array array)
    {
        if(array != null && array.size() != 0)
        {
            return allowedByGroupFilter(s, array);
        } else
        {
            return true;
        }
    }

    protected boolean isGroupAllowedForAccount(java.lang.String s)
    {
        java.lang.String s1 = "";
        return isGroupAllowedForAccount(s, getGroupFilterForAccount(s1));
    }

    protected jgl.Array getGroupFilterForAccount(java.lang.String s)
    {
        jgl.Array array = new Array();
        if(COM.dragonflow.SiteView.Platform.isStandardAccount(account))
        {
            java.util.Enumeration enumeration = user.getMultipleValues("_group");
            if(enumeration.hasMoreElements())
            {
                while (enumeration.hasMoreElements()) {
                    java.lang.String s1 = (java.lang.String)enumeration.nextElement();
                    if(s.length() == 0 || isRelated(s1, s))
                    {
                        array.add(s1);
                    }
                } 
            } else
            if(s.length() > 0)
            {
                array.add(s);
            }
        }
        return array;
    }

    protected boolean allowedByGroupFilter(java.lang.String s, jgl.Array array)
    {
        for(java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements();)
        {
            java.lang.String s1 = (java.lang.String)enumeration.nextElement();
            if(isRelated(s, s1))
            {
                return true;
            }
        }

        return false;
    }

    protected void WriteGroupFrames(java.lang.String s, jgl.Array array)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            java.lang.String s1 = getGroupFilePath(s, ".mg");
            COM.dragonflow.Properties.FrameFile.writeToFile(s1, array, "_", true);
//            if(COM.dragonflow.SiteView.TopazConfigurator.configInTopazAndRegistered())
//            {
//                jgl.Array array1 = new Array();
//                COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
//                COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s);
//                array1.add(monitorgroup);
//                siteviewgroup.removeElement(monitorgroup);
//                java.lang.StringBuffer stringbuffer = new StringBuffer();
//                COM.dragonflow.SiteView.TopazConfigurator.updateTopazGroups(array1, 0, stringbuffer);
//            }
        }
//        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
//        {
//            siteviewexception.fillInStackTrace();
//            throw siteviewexception;
//        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "WriteGroupFrames"
            }, 0L, exception.getMessage());
        }
    }

    protected boolean isRelated(java.lang.String s, java.lang.String s1)
    {
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        do
        {
            if(s.length() == 0)
            {
                break;
            }
            if(s.equals(s1))
            {
                return true;
            }
            COM.dragonflow.SiteView.Monitor monitor = (COM.dragonflow.SiteView.Monitor)siteviewgroup.getElement(s);
            if(monitor == null)
            {
                break;
            }
            s = monitor.getProperty("_parent");
        } while(true);
        return false;
    }

    protected java.lang.String getGroupFilePath(java.lang.String s, java.lang.String s1)
    {
        java.lang.String s2;
        if(s.equals("_master"))
        {
            s2 = "/groups/master.config";
        } else
        if(s.equals("_users"))
        {
            s2 = "/groups/users.config";
        } else
        {
            s2 = "/groups/" + s + s1;
        }
        return COM.dragonflow.SiteView.Platform.getRoot() + s2;
    }

    protected int findMonitorIndex(jgl.Array array, java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        if(s.equals("_config"))
        {
            return 0;
        }
        java.util.Enumeration enumeration = array.elements();
        int i = 0;
        enumeration.nextElement();
        i++;
        int j = -1;
        while (enumeration.hasMoreElements()) {
            jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
            if(COM.dragonflow.SiteView.Monitor.isMonitorFrame(hashmap) && hashmap.get("_id").equals(s))
            {
                j = i;
                break;
            }
            i++;
        } 
        if(j == -1)
        {
            throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_UNASSOCIATED_ID, new java.lang.String[] {
                s
            });
        } else
        {
            return j;
        }
    }

    protected void saveGroups()
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            java.util.Enumeration enumeration = groups.keys();
            while (enumeration.hasMoreElements()) {
                java.lang.String s = (java.lang.String)enumeration.nextElement();
                jgl.Array array = (jgl.Array)groups.get(s);
                if(array != null)
                {
//                    WriteGroupFrames(s, array);
                    if(debug)
                    {
                        COM.dragonflow.Utils.TextUtils.debugPrint("SAVED GROUP=" + s);
                    }
                } else
                {
                    java.lang.System.out.println("TRIED TO SAVE OUT EMPTY GROUP=" + s);
                }
            } 
        }
//        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
//        {
//            siteviewexception.fillInStackTrace();
//            throw siteviewexception;
//        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "saveGroups"
            }, 0L, exception.getMessage());
        }
        groups.clear();
    }

    protected java.lang.String getRawValue(COM.dragonflow.Properties.ScalarProperty scalarproperty, jgl.HashMap hashmap)
    {
        java.lang.String s = "";
        java.lang.String s1 = "";
        java.util.Enumeration enumeration = hashmap.values(scalarproperty.getName());
        if(enumeration.hasMoreElements())
        {
            s = (java.lang.String)enumeration.nextElement();
        }
        if(enumeration.hasMoreElements())
        {
            s1 = (java.lang.String)enumeration.nextElement();
        }
        if(s.equals(COM.dragonflow.Properties.ScalarProperty.OTHER_STRING) || s1.length() > 0)
        {
            return s1;
        } else
        {
            return s;
        }
    }

    protected int getThresholdNum(COM.dragonflow.SiteView.Monitor monitor)
    {
        int i = ((COM.dragonflow.SiteView.AtomicMonitor)monitor).getMaxCounters();
        if(i == 0)
        {
            if(((COM.dragonflow.SiteView.AtomicMonitor)monitor).isMultiThreshold() || monitor.getClassProperty("class").equals("URLSequenceMonitor"))
            {
                i = 10;
            } else
            {
                i = 1;
            }
        }
        return i;
    }

    protected java.lang.String GetPropertyLabel(COM.dragonflow.Properties.StringProperty stringproperty, boolean flag)
    {
        if(stringproperty == null)
        {
            return "";
        }
        java.lang.String s = stringproperty.printString();
        if(flag && (stringproperty instanceof COM.dragonflow.Properties.NumericProperty))
        {
            COM.dragonflow.Properties.NumericProperty numericproperty = (COM.dragonflow.Properties.NumericProperty)stringproperty;
            java.lang.String s1 = numericproperty.getUnits();
            if(s1 != null && s1.length() > 0)
            {
                s = s + "(" + s1 + ")";
            }
        }
        return s;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param stringproperty
     * @param i
     * @param siteviewobject
     * @param s
     * @return
     * @throws COM.dragonflow.SiteViewException.SiteViewException
     */
    protected boolean returnProperty(COM.dragonflow.Properties.StringProperty stringproperty, int i, COM.dragonflow.SiteView.SiteViewObject siteviewobject, java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        boolean flag;
            flag = false;
            if(i == FILTER_CONFIGURATION_ADD_ALL)
            {
                if(stringproperty.isParameter && stringproperty.getOrder() > 0)
                {
                    flag = true;
                }
            }
            else if(i == FILTER_CONFIGURATION_ADD_ALL_NOT_EMPTY)
            {
                if(stringproperty.isParameter && stringproperty.getOrder() > 0 && !siteviewobject.getProperty(stringproperty).equals(""))
                {
                    flag = true;
                }
            }
            else if(i == FILTER_CONFIGURATION_ALL)
            {
                if(stringproperty.isParameter && (stringproperty.getOrder() > 0 || stringproperty.getName().equals("_class") || stringproperty.getName().equals("_id")))
                {
                    flag = true;
                }
            }
            else if(i == PREREQ_OP)
            {
                COM.dragonflow.Api.SSPropertyDetails sspropertydetails = null;
                if(siteviewobject instanceof COM.dragonflow.SiteView.AtomicMonitor)
                {
                    sspropertydetails = ((COM.dragonflow.Api.APIMonitor)this).getClassPropertyDetails(stringproperty.getName(), s, new COM.dragonflow.Api.SSInstanceProperty[0]);
                } else
                if(siteviewobject instanceof COM.dragonflow.SiteView.Preferences)
                {
                    sspropertydetails = ((COM.dragonflow.Api.APIPreference)this).getClassPropertyDetails(stringproperty.getName(), s, FILTER_CONFIGURATION_ALL);
                } else
                if(siteviewobject instanceof COM.dragonflow.SiteView.Group)
                {
                    sspropertydetails = ((COM.dragonflow.Api.APIGroup)this).getClassPropertyDetails(stringproperty.getName());
                } else
                if(siteviewobject instanceof COM.dragonflow.SiteView.Action)
                {
                    sspropertydetails = ((COM.dragonflow.Api.APIAlert)this).getClassPropertyDetails(stringproperty.getName(), s, new HashMap());
                }
                if(sspropertydetails.isPrerequisite())
                {
                    flag = true;
                }
            }
            else if(i == FILTER_CONFIGURATION_ALL_NOT_EMPTY)
            {
                if(stringproperty.isParameter && !siteviewobject.getProperty(stringproperty).equals("") && (stringproperty.getOrder() > 0 || stringproperty.getName().equals("_class") || stringproperty.getName().equals("_id")))
                {
                    flag = true;
                }
            }
            else if(i == FILTER_CONFIGURATION_EDIT_ALL_NOT_EMPTY)
            {
                if(stringproperty.isParameter && stringproperty.getOrder() > 0 && (stringproperty.isEditable || stringproperty.isConfigurable) && !siteviewobject.getProperty(stringproperty).equals(""))
                {
                    flag = true;
                }
            }
            else if(i == FILTER_CONFIGURATION_EDIT_ALL)
            {
                if(siteviewobject instanceof COM.dragonflow.SiteView.BrowsableMonitor)
                {
                    if(stringproperty.getName().startsWith(((COM.dragonflow.SiteView.BrowsableMonitor)siteviewobject).getBrowseName()) || stringproperty.getName().startsWith(((COM.dragonflow.SiteView.BrowsableMonitor)siteviewobject).getBrowseID()))
                    {
                        flag = true;
                    }
                } else
                if(((siteviewobject instanceof COM.dragonflow.SiteView.ApplicationBase) || (siteviewobject instanceof COM.dragonflow.SiteView.NTCounterBase)) && stringproperty.getName().equals("_counters"))
                {
                    flag = true;
                }
                if(stringproperty.isParameter && stringproperty.getOrder() > 0 && (stringproperty.isEditable || stringproperty.isConfigurable) || stringproperty.getName().equals("_logOnlyMonitorData") || stringproperty.getName().equals("_logOnlyThresholdMeas") || stringproperty.getName().equals("_onlyStatusChanges"))
                {
                    flag = true;
                }
            }
            else if(i == FILTER_CONFIGURATION_ADD_REQUIRED)
            {
                if(isRequiredProperty(stringproperty.getName()))
                {
                    flag = true;
                }
            }
            else if(i == FILTER_RUNTIME_ALL)
            {
                if(!stringproperty.isParameter)
                {
                    flag = true;
                }
            }
            else if(i == FILTER_RUNTIME_MEASUREMENTS)
            {
                java.util.Enumeration enumeration = siteviewobject.getStatePropertyObjects(true);
                COM.dragonflow.Properties.StringProperty stringproperty1;
                while (enumeration.hasMoreElements())
                    {
                    stringproperty1 = (COM.dragonflow.Properties.StringProperty)enumeration.nextElement();
                if (stringproperty1.getName().equals(stringproperty.getName())) {
                flag = true;
                }
                    }
            } else
            if(i == FILTER_ALL)
            {
                flag = true;
            } else
            if(i == FILTER_CONFIGURATION_ADD_BASIC)
            {
                if(!stringproperty.isAdvanced && stringproperty.isParameter && stringproperty.getOrder() > 0)
                {
                    flag = true;
                }
            } else
            if(i == FILTER_CONFIGURATION_ADD_ADVANCED && stringproperty.isAdvanced && stringproperty.isParameter && stringproperty.getOrder() > 0)
            {
                flag = true;
            }

        return flag;
    }

    protected java.util.Vector getLocalServers()
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.util.Vector vector = new Vector();
        try
        {
            COM.dragonflow.HTTP.HTTPRequest httprequest = new HTTPRequest();
            java.lang.Class class1 = java.lang.Class.forName("COM.dragonflow.Page.serverPage");
            COM.dragonflow.Page.CGI cgi = (COM.dragonflow.Page.CGI)class1.newInstance();
            cgi.initialize(httprequest, null);
            vector = COM.dragonflow.SiteView.Platform.getServers();
            try
            {
                java.net.InetAddress inetaddress = java.net.InetAddress.getLocalHost();
                java.lang.String s = inetaddress.getHostName();
                java.util.Vector vector1 = getSiteViewInfo(s);
                jgl.HashMap hashmap = (jgl.HashMap)vector1.get(0);
                if(hashmap.get("platform") != null && hashmap.get("platform").equals("WIN"))
                {
                    s = "\\\\" + s.toUpperCase();
                }
                vector.setElementAt(s, 0);
                vector.setElementAt(s, 1);
            }
            catch(java.net.UnknownHostException unknownhostexception)
            {
                throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_NO_IP, new java.lang.String[] {
                    "localhost"
                });
            }
        }
        catch(COM.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "getLocalServers"
            }, 0L, exception.getMessage());
        }
        return vector;
    }

    protected java.util.Vector addServers(java.util.Vector vector, java.lang.String s, boolean flag)
        throws java.io.IOException
    {
        COM.dragonflow.HTTP.HTTPRequest httprequest = new HTTPRequest();
        jgl.Array array = readMachines(s);
        jgl.Sorting.sort(array, new CompareSlot("_name", COM.dragonflow.SiteView.CompareSlot.DIRECTION_LESS));
        boolean flag1 = s.indexOf("NT") == -1;
        for(int i = 0; i < array.size(); i++)
        {
            jgl.HashMap hashmap = (jgl.HashMap)array.at(i);
            java.lang.String s1 = "";
            if(flag1)
            {
                s1 = COM.dragonflow.SiteView.Machine.getFullMachineID(COM.dragonflow.SiteView.Machine.REMOTE_PREFIX + COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_id"), httprequest);
            } else
            {
                s1 = COM.dragonflow.SiteView.Machine.getFullMachineID(COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_host"), httprequest);
            }
            java.lang.String s2 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_name");
            if(s2.length() == 0)
            {
                s2 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_host");
            }
            if(flag)
            {
                if(hashmap.get("_method") != null && hashmap.get("_method").equals("ssh"))
                {
                    vector.addElement(s1);
                    vector.addElement(s2);
                }
            } else
            {
                vector.addElement(s1);
                vector.addElement(s2);
            }
        }

        return vector;
    }

    protected jgl.Array readMachines(java.lang.String s)
        throws java.io.IOException
    {
        jgl.Array array = new Array();
        jgl.HashMap hashmap = COM.dragonflow.SiteView.MasterConfig.getMasterConfig();
        java.lang.String s1;
        for(java.util.Enumeration enumeration = hashmap.values(s); enumeration.hasMoreElements(); array.add(COM.dragonflow.Utils.TextUtils.stringToHashMap(s1)))
        {
            s1 = (java.lang.String)enumeration.nextElement();
            if(s1.indexOf("_id") >= 0)
            {
                continue;
            }
            java.lang.String s2 = "_nextRemoteID";
            if(s.equals("_remoteNTMachine"))
            {
                s2 = "_nextRemoteNTID";
            }
            java.lang.String s3 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, s2);
            if(s3.length() == 0)
            {
                s3 = "10";
            }
            s1 = s1 + " _id=" + s3;
            hashmap.put(s2, COM.dragonflow.Utils.TextUtils.increment(s3));
        }

        return array;
    }

    protected boolean isPortalServerRequest()
    {
        COM.dragonflow.HTTP.HTTPRequest httprequest = new HTTPRequest();
        if(httprequest != null)
        {
            return COM.dragonflow.Api.APISiteView.isPortalServerRequest(httprequest);
        } else
        {
            return false;
        }
    }

    protected static boolean isPortalServerRequest(COM.dragonflow.HTTP.HTTPRequest httprequest)
    {
        if(httprequest != null)
        {
            return httprequest.getPortalServer().length() > 0;
        } else
        {
            return false;
        }
    }

    private jgl.Array getUserFrames()
    {
        jgl.Array array = null;
        if(isPortalServerRequest())
        {
            try
            {
                array = ReadGroupFrames("_users");
            }
            catch(java.lang.Exception exception)
            {
                array = new Array();
            }
            jgl.HashMap hashmap = COM.dragonflow.SiteView.MasterConfig.getMasterConfig();
            COM.dragonflow.SiteView.User.initializeUsersList(array, hashmap);
        } else
        {
            array = COM.dragonflow.SiteView.User.readUsers();
        }
        return array;
    }

    public static java.lang.Object invokeTestMethod(java.lang.String s, java.lang.String s1, java.lang.Object aobj[])
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.Object obj = null;
        try
        {
            java.lang.Object obj1 = null;
            java.lang.Class class1 = null;
            java.lang.reflect.Method amethod[] = null;
            class1 = java.lang.Class.forName(s);
            obj1 = class1.newInstance();
            amethod = class1.getMethods();
            for(int i = 0; i < amethod.length; i++)
            {
                if(amethod[i].getName().equals(s1))
                {
                    obj = amethod[i].invoke(obj1, aobj);
                }
            }

        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APISiteView", "invokeTestMethod"
            }, 0L, exception.getMessage());
        }
        return obj;
    }

    private void disableHeartbeats()
    {
        timer.cancel();
        timer = null;
    }

    private void enableHeartbeats(java.lang.String s, int i, long l)
    {
        if(timer != null)
        {
            timer.cancel();
        }
        HeartbeatTask heartbeattask = new HeartbeatTask(s, i);
        timer = new Timer();
        if(COM.dragonflow.Log.LogManager.loggerRegistered("SSEELog"))
        {
            jgl.HashMap hashmap = COM.dragonflow.SiteView.MasterConfig.getMasterConfig();
            java.lang.String s1 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_sseeHeartbeatTimer");
            if(s1 != null && s1.length() > 0)
            {
                l = java.lang.Integer.parseInt(s1);
            }
            timer.scheduleAtFixedRate(heartbeattask, new Date(), l);
        }
    }

    protected int findType(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        int i = -1;
        COM.dragonflow.Api.APISiteView.initSSChildObjects();
        int j = 0;
        do
        {
            if(j >= siteViewObjects.size())
            {
                break;
            }
            if(((java.lang.String[])siteViewObjects.get(j))[0].equals(s))
            {
                i = j;
                break;
            }
            j++;
        } while(true);
        return i;
    }

    public boolean hasSolutionLicense(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        if(!$assertionsDisabled && s == null)
        {
            throw new AssertionError();
        }
        boolean flag = false;
        if(s.startsWith("Active Directory") && COM.dragonflow.Utils.LUtils.isValidSSforXLicense(new ADReplicationMonitor()))
        {
            flag = true;
        } else
        if((s.equals("Exchange 5.5") || s.equals("Exchange 2000") || s.equals("Exchange 2003")) && COM.dragonflow.Utils.LUtils.isValidSSforXLicense(new Exchange2k3MailboxMonitor()))
        {
            flag = true;
        }
        return flag;
    }

    public static java.lang.String getContext(jgl.Array array, java.lang.String s)
    {
        if(!$assertionsDisabled && array == null)
        {
            throw new AssertionError();
        }
        if(!$assertionsDisabled && array.size() <= 0)
        {
            throw new AssertionError();
        }
        java.lang.String s1 = (java.lang.String)array.at(0);
        for(int i = 1; i < array.size(); i++)
        {
            for(; !COM.dragonflow.Api.APISiteView.childOf(s1, (java.lang.String)array.at(i)); s1 = COM.dragonflow.Api.APISiteView.getParent(s1)) { }
        }

        if(s != null && s.length() > 0)
        {
            s1 = COM.dragonflow.Api.APISiteView.childOf(s, s1) ? s : s1;
        }
        return s1;
    }

    public static java.lang.String getContext(java.lang.String as[], java.lang.String s)
    {
        jgl.Array array = new Array();
        for(int i = 0; i < as.length; i++)
        {
            array.add(as[i]);
        }

        return COM.dragonflow.Api.APISiteView.getContext(array, s);
    }

    private static boolean childOf(java.lang.String s, java.lang.String s1)
    {
        if(!$assertionsDisabled && s == null)
        {
            throw new AssertionError();
        }
        if(s.length() == 0 || s.equals("_SiteViewRoot_"))
        {
            return true;
        }
        java.lang.String s2 = COM.dragonflow.Api.APISiteView.getGroup(s1);
        if(s.equals(s2))
        {
            return true;
        }
        if(s2.length() == 0)
        {
            return false;
        } else
        {
            return COM.dragonflow.Api.APISiteView.childOf(s, COM.dragonflow.Api.APISiteView.getParent(s2));
        }
    }

    private static java.lang.String getParent(java.lang.String s)
    {
        if(!s.equals(COM.dragonflow.Api.APISiteView.getGroup(s)))
        {
            return COM.dragonflow.Api.APISiteView.getGroup(s);
        } else
        {
            COM.dragonflow.SiteView.MonitorGroup monitorgroup = COM.dragonflow.SiteView.MonitorGroup.getMonitorGroup(s);
            return monitorgroup != null ? monitorgroup.getProperty("_parent") : "";
        }
    }

    private static java.lang.String getGroup(java.lang.String s)
    {
        java.lang.String s1 = new String(s == null ? "" : s);
        java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s1, " ");
        if(as.length == 2)
        {
            try
            {
                java.lang.Integer.parseInt(as[0]);
                s1 = as[1];
            }
            catch(java.lang.Exception exception)
            {
                s1 = as[0];
            }
        }
        return s1;
    }

    private jgl.Array getAllAllowedGroupIDs()
    {
        jgl.Array array = COM.dragonflow.Utils.I18N.toDefaultArray(COM.dragonflow.SiteView.SiteViewGroup.currentSiteView().getGroupIDs());
        COM.dragonflow.HTTP.HTTPRequest httprequest = new HTTPRequest();
        httprequest.setValue("account", account);
        httprequest.setUser(user);
        jgl.Array array1 = COM.dragonflow.Page.CGI.filterGroupsForAccount(array, httprequest);
        return array1;
    }

    protected java.util.Collection getAllAllowedGroups()
    {
        jgl.Array array = getAllAllowedGroupIDs();
        java.util.ArrayList arraylist = new ArrayList(array.size());
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        for(int i = 0; i < array.size(); i++)
        {
            java.lang.String s = (java.lang.String)array.at(i);
            if(!s.equals("__Health__"))
            {
                arraylist.add(siteviewgroup.getGroup(s));
            }
        }

        return arraylist;
    }

    protected java.util.Collection getMonitorsForGroup(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewParameterException
    {
        if(isGroupAllowedForAccount(s))
        {
            java.util.Vector vector = new Vector();
            COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s);
            java.util.ArrayList arraylist = new ArrayList();
            if(monitorgroup != null)
            {
                arraylist.add(monitorgroup);
                COM.dragonflow.SiteView.ConfigurationChanger.getGroupsMonitors(arraylist, vector, null, false);
                return vector;
            } else
            {
                throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION);
            }
        } else
        {
            throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_ACCESS_EXCEPTION);
        }
    }

    protected java.util.Collection getSubGroups(java.lang.String s)
        throws COM.dragonflow.SiteViewException.SiteViewParameterException
    {
        if(isGroupAllowedForAccount(s))
        {
            java.util.Vector vector = new Vector();
            COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s);
            java.util.ArrayList arraylist = new ArrayList();
            if(monitorgroup != null)
            {
                arraylist.add(monitorgroup);
                COM.dragonflow.SiteView.ConfigurationChanger.getGroupsMonitors(arraylist, null, vector, false);
            }
            return vector;
        } else
        {
            throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_ACCESS_EXCEPTION);
        }
    }

    protected void fixDisableAlertingParams(jgl.HashMap hashmap)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s = (java.lang.String)hashmap.get("groupAlertsDisable");
        if(s == null)
        {
            return;
        }
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        if(!s.equals("undo"))
        {
            if(s.equals("timed"))
            {
                java.util.Date date = null;
                int i = 0;
                try
                {
                    i = java.lang.Integer.parseInt((java.lang.String)hashmap.get("disableGroupAlertsTime"));
                }
                catch(java.lang.NumberFormatException numberformatexception)
                {
                    throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_ALERT_INVALID_DISABLE_DATE_RANGE);
                }
                java.util.GregorianCalendar gregoriancalendar = new GregorianCalendar();
                gregoriancalendar.setTime(new Date());
                gregoriancalendar.add(13, i);
                date = gregoriancalendar.getTime();
                synchronized(mSiteViewDisableFormat)
                {
                    stringbuffer.append(mSiteViewDisableFormat.format(date));
                }
            } else
            if(s.equals("schedule"))
            {
                java.util.Date date1 = null;
                java.util.Date date2 = null;
                java.lang.String s2 = hashmap.get("disableGroupAlertsStartTimeDate") + " " + hashmap.get("disableGroupAlertsStartTimeTime");
                java.lang.String s3 = hashmap.get("disableGroupAlertsEndTimeDate") + " " + hashmap.get("disableGroupAlertsEndTimeTime");
                synchronized(mAPIDisableDateFormat)
                {
                    try
                    {
                        date1 = mAPIDisableDateFormat.parse(s2);
                        date2 = mAPIDisableDateFormat.parse(s3);
                    }
                    catch(java.text.ParseException parseexception)
                    {
                        throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_ALERT_INVALID_DISABLE_DATE_RANGE);
                    }
                }
                synchronized(mSiteViewDisableFormat)
                {
                    stringbuffer.append(mSiteViewDisableFormat.format(date1));
                    stringbuffer.append(";");
                    stringbuffer.append(mSiteViewDisableFormat.format(date2));
                }
            }
        }
        java.lang.String s1 = (java.lang.String)hashmap.get("alertDisableDescription");
        if(s1 != null && s1.length() > 0 && stringbuffer.length() > 0)
        {
            stringbuffer.append("*").append(s1);
        }
        hashmap.put("_alertDisabled", stringbuffer.toString());
    }

    protected void fixDisableAlertingParamsOut(COM.dragonflow.SiteView.Monitor monitor, java.util.Vector vector)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s = monitor.getProperty("_alertDisabled");
        if(s == null || s.equals(""))
        {
            vector.add(new SSInstanceProperty("groupAlertsDisable", "undo"));
            vector.add(new SSInstanceProperty("disableGroupAlertsTime", ""));
            vector.add(new SSInstanceProperty("alertDisableDescription", ""));
            vector.add(new SSInstanceProperty("disableGroupAlertsStartTimeDate", ""));
            vector.add(new SSInstanceProperty("disableGroupAlertsStartTimeTime", ""));
            vector.add(new SSInstanceProperty("disableGroupAlertsEndTimeDate", ""));
            vector.add(new SSInstanceProperty("disableGroupAlertsEndTimeTime", ""));
            return;
        }
        java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s, "*");
        java.lang.String s1 = "";
        if(as.length > 1)
        {
            s1 = as[1];
        }
        java.lang.String as1[] = COM.dragonflow.Utils.TextUtils.split(as[0], ";");
        java.util.Date date = null;
        java.util.Date date1 = null;
        try
        {
            synchronized(mSiteViewDisableFormat)
            {
                if(as1.length >= 1)
                {
                    date = mSiteViewDisableFormat.parse(as1[0]);
                }
                if(as1.length >= 2)
                {
                    date1 = mSiteViewDisableFormat.parse(as1[1]);
                }
            }
        }
        catch(java.text.ParseException parseexception) { }
        if(date == null && date1 == null)
        {
            return;
        }
        if(date1 == null)
        {
            date1 = date;
            date = new Date();
        }
        synchronized(mAPIDisableDateFormat)
        {
            java.lang.String s2 = mAPIDisableDateFormat.format(date);
            java.lang.String s3 = mAPIDisableDateFormat.format(date1);
            java.lang.String as2[] = COM.dragonflow.Utils.TextUtils.split(s2, " ");
            java.lang.String as3[] = COM.dragonflow.Utils.TextUtils.split(s3, " ");
            vector.add(new SSInstanceProperty("disableGroupAlertsStartTimeDate", as2[0]));
            vector.add(new SSInstanceProperty("disableGroupAlertsStartTimeTime", as2[1]));
            vector.add(new SSInstanceProperty("disableGroupAlertsEndTimeDate", as3[0]));
            vector.add(new SSInstanceProperty("disableGroupAlertsEndTimeTime", as3[1]));
        }
        vector.add(new SSInstanceProperty("disableGroupAlertsTime", ""));
        vector.add(new SSInstanceProperty("alertDisableDescription", s1));
        vector.add(new SSInstanceProperty("groupAlertsDisable", "schedule"));
    }

    protected void fixDisableGroupOrMonitorParams(jgl.HashMap hashmap)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s = (java.lang.String)hashmap.get("monitorsDisable");
        java.lang.String s1 = (java.lang.String)hashmap.get("monitorDisableDescription");
        if(s == null)
        {
            return;
        }
        if(s.equals("undo"))
        {
            hashmap.put(COM.dragonflow.SiteView.Monitor.pDisabled.getName(), "");
            hashmap.put(COM.dragonflow.SiteView.Monitor.pTimedDisable.getName(), "");
            hashmap.put(COM.dragonflow.SiteView.Monitor.pDisabledDescription.getName(), "");
        } else
        if(s.equals("permanent"))
        {
            hashmap.put(COM.dragonflow.SiteView.Monitor.pDisabled.getName(), "checked");
            hashmap.put(COM.dragonflow.SiteView.Monitor.pDisabledDescription.getName(), s1);
            hashmap.put(COM.dragonflow.SiteView.Monitor.pTimedDisable.getName(), "");
        } else
        if(s.equals("timed") || s.equals("schedule"))
        {
            java.util.Date date = null;
            java.util.Date date1 = null;
            if(s.equals("timed"))
            {
                int i = 0;
                try
                {
                    i = java.lang.Integer.parseInt((java.lang.String)hashmap.get("disableMonitorsTime"));
                }
                catch(java.lang.NumberFormatException numberformatexception)
                {
                    throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_ALERT_INVALID_DISABLE_DATE_RANGE);
                }
                java.util.GregorianCalendar gregoriancalendar = new GregorianCalendar();
                date = new Date();
                gregoriancalendar.setTime(date);
                gregoriancalendar.add(13, i);
                date1 = gregoriancalendar.getTime();
            } else
            {
                java.lang.String s2 = hashmap.get("disableMonitorsStartTimeDate") + " " + hashmap.get("disableMonitorsStartTimeTime");
                java.lang.String s3 = hashmap.get("disableMonitorsEndTimeDate") + " " + hashmap.get("disableMonitorsEndTimeTime");
                synchronized(mAPIDisableDateFormat)
                {
                    try
                    {
                        date = mAPIDisableDateFormat.parse(s2);
                        date1 = mAPIDisableDateFormat.parse(s3);
                    }
                    catch(java.text.ParseException parseexception)
                    {
                        throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_ALERT_INVALID_DISABLE_DATE_RANGE);
                    }
                }
            }
            java.lang.StringBuffer stringbuffer = new StringBuffer();
            synchronized(mSiteViewDisableFormat)
            {
                stringbuffer.append(mSiteViewDisableFormat.format(date));
                stringbuffer.append(";");
                stringbuffer.append(mSiteViewDisableFormat.format(date1));
            }
            hashmap.put(COM.dragonflow.SiteView.Monitor.pTimedDisable.getName(), stringbuffer.toString());
            hashmap.put(COM.dragonflow.SiteView.Monitor.pDisabled.getName(), "");
            hashmap.put(COM.dragonflow.SiteView.Monitor.pDisabledDescription.getName(), s1);
        }
    }

    protected void fixDisableGroupOrMonitorParamsOut(COM.dragonflow.SiteView.Monitor monitor, java.util.Vector vector)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s = monitor.getProperty(COM.dragonflow.SiteView.Monitor.pDisabled);
        java.lang.String s1 = monitor.getProperty(COM.dragonflow.SiteView.Monitor.pTimedDisable);
        java.lang.String s2 = monitor.getProperty(COM.dragonflow.SiteView.Monitor.pDisabledDescription);
        if((s == null || s.equals("")) && (s1 == null || s1.equals("")))
        {
            vector.add(new SSInstanceProperty("monitorsDisable", "undo"));
            vector.add(new SSInstanceProperty("disableMonitorsTime", ""));
            vector.add(new SSInstanceProperty("monitorDisableDescription", ""));
            vector.add(new SSInstanceProperty("disableMonitorsStartTimeDate", ""));
            vector.add(new SSInstanceProperty("disableMonitorsStartTimeTime", ""));
            vector.add(new SSInstanceProperty("disableMonitorsEndTimeDate", ""));
            vector.add(new SSInstanceProperty("disableMonitorsEndTimeTime", ""));
            return;
        }
        if(s != null && (s.equals("checked") || s.equals("on")))
        {
            vector.add(new SSInstanceProperty("monitorsDisable", "permanent"));
            vector.add(new SSInstanceProperty("disableMonitorsTime", ""));
            vector.add(new SSInstanceProperty("monitorDisableDescription", s2));
            vector.add(new SSInstanceProperty("disableMonitorsStartTimeDate", ""));
            vector.add(new SSInstanceProperty("disableMonitorsStartTimeTime", ""));
            vector.add(new SSInstanceProperty("disableMonitorsEndTimeDate", ""));
            vector.add(new SSInstanceProperty("disableMonitorsEndTimeTime", ""));
            return;
        }
        if(s1 != null && !s1.equals(""))
        {
            java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s1, ";");
            java.util.Date date = null;
            java.util.Date date1 = null;
            try
            {
                synchronized(mSiteViewDisableFormat)
                {
                    if(as.length >= 1)
                    {
                        date = mSiteViewDisableFormat.parse(as[0]);
                    }
                    if(as.length >= 2)
                    {
                        date1 = mSiteViewDisableFormat.parse(as[1]);
                    }
                }
            }
            catch(java.text.ParseException parseexception) { }
            if(date == null && date1 == null)
            {
                return;
            }
            if(date1 == null)
            {
                date1 = date;
                date = new Date();
            }
            synchronized(mAPIDisableDateFormat)
            {
                java.lang.String s3 = mAPIDisableDateFormat.format(date);
                java.lang.String s4 = mAPIDisableDateFormat.format(date1);
                java.lang.String as1[] = COM.dragonflow.Utils.TextUtils.split(s3, " ");
                java.lang.String as2[] = COM.dragonflow.Utils.TextUtils.split(s4, " ");
                vector.add(new SSInstanceProperty("disableMonitorsStartTimeDate", as1[0]));
                vector.add(new SSInstanceProperty("disableMonitorsStartTimeTime", as1[1]));
                vector.add(new SSInstanceProperty("disableMonitorsEndTimeDate", as2[0]));
                vector.add(new SSInstanceProperty("disableMonitorsEndTimeTime", as2[1]));
            }
            vector.add(new SSInstanceProperty("disableMonitorsTime", ""));
            vector.add(new SSInstanceProperty("monitorDisableDescription", s2));
            vector.add(new SSInstanceProperty("monitorsDisable", "schedule"));
        }
    }

    protected void processWSDLParameters(jgl.HashMap hashmap)
        throws COM.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s = "";
        if(hashmap.get("webserviceurl") == null || hashmap.get("webserviceurl").equals("http://") || hashmap.get("webserviceurl").equals(""))
        {
            java.lang.String s1 = (java.lang.String)hashmap.get("wsdlfile");
            java.lang.String s2 = COM.dragonflow.SiteView.Platform.getUsedDirectoryPath("templates.wsdl", account);
            s = s2 + "/" + s1;
        } else
        {
            s = (java.lang.String)hashmap.get("webserviceurl");
        }
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        COM.dragonflow.Utils.WSDLParser wsdlparser = null;
        wsdlparser = new WSDLParser();
        wsdlparser.readWSDL(s, stringbuffer);
        if(stringbuffer.length() > 0)
        {
            throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_UNABLE_TO_READ_WSDLURL, new java.lang.String[] {
                stringbuffer.toString()
            });
        }
        java.lang.String s3 = wsdlparser.getServiceEndpointURL(stringbuffer);
        if(stringbuffer.length() > 0)
        {
            throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_UNABLE_TO_READ_WSDLURL, new java.lang.String[] {
                stringbuffer.toString()
            });
        } else
        {
            hashmap.put("_wsdlurl", s);
            hashmap.put("_serverurl", s3);
            hashmap.remove("wsdlfile");
            hashmap.remove("webserviceurl");
            return;
        }
    }

    protected void removeAPIDisableProperties(jgl.HashMap hashmap)
    {
        hashmap.remove("monitorsDisable");
        hashmap.remove("disableMonitorsTime");
        hashmap.remove("monitorDisableDescription");
        hashmap.remove("disableMonitorsStartTimeDate");
        hashmap.remove("disableMonitorsStartTimeTime");
        hashmap.remove("disableMonitorsEndTimeDate");
        hashmap.remove("disableMonitorsEndTimeTime");
        hashmap.remove("groupAlertsDisable");
        hashmap.remove("disableGroupAlertsTime");
        hashmap.remove("alertDisableDescription");
        hashmap.remove("disableGroupAlertsStartTimeDate");
        hashmap.remove("disableGroupAlertsStartTimeTime");
        hashmap.remove("disableGroupAlertsEndTimeDate");
        hashmap.remove("disableGroupAlertsEndTimeTime");
    }

    static 
    {
        $assertionsDisabled = !(COM.dragonflow.Api.APISiteView.class).desiredAssertionStatus();
        COM.dragonflow.Api.APISiteView.initRequiredPropertyArray();
    }
}
