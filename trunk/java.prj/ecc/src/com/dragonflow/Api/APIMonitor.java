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

import java.io.StringReader;
import java.io.StringWriter;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashSet;
import java.util.Vector;

import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import jgl.Array;
import jgl.HashMap;

import org.xml.sax.InputSource;

import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.ConfigurationChanger;
import com.dragonflow.SiteView.DetectConfigurationChange;
import com.dragonflow.SiteViewException.SiteViewAvailabilityException;
import com.dragonflow.SiteViewException.SiteViewException;
import com.dragonflow.SiteViewException.SiteViewOperationalException;
import com.dragonflow.SiteViewException.SiteViewParameterException;
import com.dragonflow.Utils.HTMLTagParser;

// Referenced classes of package com.dragonflow.Api:
// APISiteView, SSInstanceProperty, SSStringReturnValue, SSMonitorInstance,
// SSPropertyDetails, Alert

public class APIMonitor extends com.dragonflow.Api.APISiteView
{
    private class OrderComparitor
        implements java.util.Comparator
    {

        public int compare(java.lang.Object obj, java.lang.Object obj1)
        {
            return ((com.dragonflow.Properties.StringProperty)obj).getOrder() - ((com.dragonflow.Properties.StringProperty)obj1).getOrder();
        }

        public boolean equals(java.lang.Object obj)
        {
            return obj instanceof OrderComparitor;
        }

        private OrderComparitor()
        {
            super();
        }

    }

    class Worker
        implements java.lang.Runnable
    {

        com.dragonflow.SiteView.AtomicMonitor mon;
        boolean timedOut;
        java.lang.Object mutex;

        public void run()
        {
            mon.run();
            timedOut = false;
            synchronized(mutex)
            {
                mutex.notify();
            }
        }

        public Worker(com.dragonflow.SiteView.AtomicMonitor atomicmonitor, java.lang.Object obj)
        {
            super();
            timedOut = true;
            mon = atomicmonitor;
            mutex = obj;
        }
    }


    public static final java.lang.String[] TARGET_TAGS = {
        "/A", "INPUT", "/FORM", "/OPTION", "/SELECT", "/TEXTAREA", "FRAME", "BASE", "AREA", "META", 
        "IFRAME"
    };
    public static final java.lang.String[] FORM_INPUT_TAGS = {
        "INPUT", "SELECT"
    };
    public static final int displayMax = 80;
    public static final int formNameMax = 30;
    public static final java.lang.String openBrace = "{";
    public static final java.lang.String closeBrace = "}";
    public static final java.lang.String formType = "form";
    public static final java.lang.String frameType = "frame";
    public static final java.lang.String thisPostData = "_postData";
    private static java.lang.String OP_ADD = "add";
    private static java.lang.String OP_TEMP = "temp";
    private static java.lang.String OP_EDIT = "edit";
    public static final java.lang.String PORT_OTHER = "portOther";
    public static final java.lang.String MAX_SEARCH_DEPTH_OTHER = "_maxSearchDepthOther";
    public static final java.lang.String OID_OTHER = "oidOther";
    public static final java.lang.String PERCENTAGEBASE_OTHER = "percentageBaseOther";
    public static final java.lang.String SCALE_OTHER = "scaleOther";
    public static final java.lang.String SERVICE_OTHER = "serviceOther";
    public static final java.lang.String TOPAZ_LOGGING = "topazLogging";
    public static final java.lang.String TOPAZ_NOT_LOG_TO_TOPAZ = "_notLogToTopaz";
    public static final java.lang.String TOPAZ_LOG_EVERYTHING = "logEverything";
    public static final java.lang.String SSPARAM_PORT = "_port";
    public static final java.lang.String SSPARAM_MAXSEARCHDEPTH = "_maxSearchDepth";
    public static final java.lang.String SSPARAM_OID = "_oid";
    public static final java.lang.String SSPARAM_PERCENTAGEBASE = "_percentageBase";
    public static final java.lang.String SSPARAM_SCALE = "_scale";
    public static final java.lang.String SSPARAM_SERVICE = "_service";
    public static final java.lang.String SSPARAM_COUNTERS = "_counters";
    public static final java.lang.String SSPARAM_BROWSE = "_browse";
    public static final java.lang.String SSPARAM_DESCRIPTION = "_description";
    public static final java.lang.String SSPARAM_MONITOR_DESCRIPTION = "_monitorDescription";
    public static final java.lang.String SSPARAM_MACHINE = "_machine";
    public static final java.lang.String SSPARAM_POSTDATA_PREFIX = "_postData";
    public static final java.lang.String SSPARAM_REFERENCE_PREFIX = "_reference";
    private static com.dragonflow.Properties.StringProperty pMonDisable = new StringProperty("monitorsDisable");
    private static com.dragonflow.Properties.StringProperty pMonDisableTime = new StringProperty("disableMonitorsTime");
    private static com.dragonflow.Properties.StringProperty pMonDisableDesc = new StringProperty("monitorDisableDescription");
    private static com.dragonflow.Properties.StringProperty pMonDisableStartDate = new StringProperty("disableMonitorsStartTimeDate");
    private static com.dragonflow.Properties.StringProperty pMonDisableStartTime = new StringProperty("disableMonitorsStartTimeTime");
    private static com.dragonflow.Properties.StringProperty pMonDisableEndDate = new StringProperty("disableMonitorsEndTimeDate");
    private static com.dragonflow.Properties.StringProperty pMonDisableEndTime = new StringProperty("disableMonitorsEndTimeTime");
    private static com.dragonflow.Properties.StringProperty pAlertDisable = new StringProperty("groupAlertsDisable");
    private static com.dragonflow.Properties.StringProperty pAlertDisableTime = new StringProperty("disableGroupAlertsTime");
    private static com.dragonflow.Properties.StringProperty pAlertDisableDesc = new StringProperty("alertDisableDescription");
    private static com.dragonflow.Properties.StringProperty pAlertDisableStartDate = new StringProperty("disableGroupAlertsStartTimeDate");
    private static com.dragonflow.Properties.StringProperty pAlertDisableStartTime = new StringProperty("disableGroupAlertsStartTimeTime");
    private static com.dragonflow.Properties.StringProperty pAlertDisableEndDate = new StringProperty("disableGroupAlertsEndTimeDate");
    private static com.dragonflow.Properties.StringProperty pAlertDisableEndTime = new StringProperty("disableGroupAlertsEndTimeTime");
    static final boolean $assertionsDisabled; /* synthetic field */

    public APIMonitor()
    {
    }

    public com.dragonflow.Api.SSStringReturnValue create(java.lang.String s, java.lang.String s1, com.dragonflow.Api.SSInstanceProperty assinstanceproperty[])
    throws com.dragonflow.SiteViewException.SiteViewException
    {
    	return this.create(s, s1, assinstanceproperty,null);
    }
    
    
    public com.dragonflow.Api.SSStringReturnValue create(java.lang.String s, java.lang.String s1, com.dragonflow.Api.SSInstanceProperty assinstanceproperty[],String methodId)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s2 = "";
        try
        {
            jgl.HashMap hashmap = new HashMap(true);
            java.lang.String s3 = "";
            boolean flag = false;
            boolean flag1 = false;
            java.lang.String s5 = null;
            for(int i = 0; i < assinstanceproperty.length; i++)
            {
                boolean flag2 = false;
                if(assinstanceproperty[i].getName().equals("portOther"))
                {
                    flag = true;
                    s5 = "_port";
                } else
                if(assinstanceproperty[i].getName().equals("oidOther"))
                {
                    flag = true;
                    s5 = "_oid";
                } else
                if(assinstanceproperty[i].getName().equals("_maxSearchDepthOther"))
                {
                    flag = true;
                    s5 = "_maxSearchDepth";
                } else
                if(assinstanceproperty[i].getName().equals("percentageBaseOther"))
                {
                    flag = true;
                    s5 = "_percentageBase";
                } else
                if(assinstanceproperty[i].getName().equals("scaleOther"))
                {
                    flag = true;
                    s5 = "_scale";
                } else
                if(assinstanceproperty[i].getName().equals("serviceOther"))
                {
                    flag = true;
                    s5 = "_service";
                } else
                if(assinstanceproperty[i].getName().equals("topazLogging"))
                {
                    flag1 = true;
                } else
                if(assinstanceproperty[i].getName().equals("_perfmonMsmtsProp"))
                {
                    hashmap.put(assinstanceproperty[i].getName(), com.dragonflow.SiteView.monitorUtils.transformPerfmonMeasurementsToMgFormat((java.lang.String)assinstanceproperty[i].getValue()));
                }
                if(flag)
                {
                    java.lang.String s4 = (java.lang.String)assinstanceproperty[i].getValue();
                    if(s4.length() > 0)
                    {
                        hashmap.put(s5, s4);
                    }
                    flag = false;
                    continue;
                }
                if(flag1)
                {
                    java.lang.String s6 = "";
                    if(assinstanceproperty[i].getValue() != null && ((java.lang.String)assinstanceproperty[i].getValue()).length() > 0)
                    {
                        s6 = (java.lang.String)assinstanceproperty[i].getValue();
                        if(!s6.equals("logEverything"))
                        {
                            hashmap.put(s6, "true");
                        }
                    }
                    if(!s6.equals("_notLogToTopaz"))
                    {
                        hashmap.put("_notLogToTopaz", "");
                    }
                    if(!s6.equals("_logOnlyMonitorData"))
                    {
                        hashmap.put("_logOnlyMonitorData", "");
                    }
                    if(!s6.equals("_logOnlyThresholdMeas"))
                    {
                        hashmap.put("_logOnlyThresholdMeas", "");
                    }
                    if(!s6.equals("_onlyStatusChanges"))
                    {
                        hashmap.put("_onlyStatusChanges", "");
                    }
                    flag1 = false;
                    continue;
                }
                if(assinstanceproperty[i].getName().equals("_port"))
                {
                    if((java.lang.String)hashmap.get("_port") != null)
                    {
                        flag2 = true;
                    }
                } else
                if(assinstanceproperty[i].getName().equals("_oid"))
                {
                    if((java.lang.String)hashmap.get("_oid") != null)
                    {
                        flag2 = true;
                    }
                } else
                if(assinstanceproperty[i].getName().equals("_maxSearchDepth"))
                {
                    if((java.lang.String)hashmap.get("_maxSearchDepth") != null)
                    {
                        flag2 = true;
                    }
                } else
                if(assinstanceproperty[i].getName().equals("_percentageBase"))
                {
                    if((java.lang.String)hashmap.get("_percentageBase") != null)
                    {
                        flag2 = true;
                    }
                } else
                if(assinstanceproperty[i].getName().equals("_scale"))
                {
                    if((java.lang.String)hashmap.get("_scale") != null)
                    {
                        flag2 = true;
                    }
                } else
                if(assinstanceproperty[i].getName().equals("_service") && (java.lang.String)hashmap.get("_service") != null)
                {
                    flag2 = true;
                }
                if(assinstanceproperty[i].getName().equals("_description") || assinstanceproperty[i].getName().equals("_monitorDescription") && assinstanceproperty[i].getValue() != null)
                {
                    assinstanceproperty[i] = new SSInstanceProperty(assinstanceproperty[i].getName(), com.dragonflow.Utils.TextUtils.replaceString((java.lang.String)assinstanceproperty[i].getValue(), "\r\n", " "));
                }
                if(!flag2)
                {
                    hashmap.add(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
                }
            }

            jgl.HashMap hashmap1 = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
            int j = com.dragonflow.Utils.TextUtils.toInt(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_URLSequenceMonitorSteps"));
            for(int k = 0; k < j; k++)
            {
                java.lang.String s8 = (java.lang.String)hashmap.get("_postData" + (new Integer(k + 1)).toString());
                int l = -1;
                do
                {
                    if(s8 != null && s8.length() > 0)
                    {
                        l = s8.indexOf("{[");
                        int i1 = s8.indexOf("}");
                        if(l >= 0 && i1 >= 0)
                        {
                            s8 = s8.substring(0, l) + s8.substring(i1 + 1);
                        }
                        hashmap.put("_postData" + (new Integer(k + 1)).toString(), s8);
                    }
                } while(l != -1);
                java.lang.String s9 = (java.lang.String)hashmap.get("_reference" + (new Integer(k + 1)).toString());
                if(s9 == null || s9.length() <= 0)
                {
                    continue;
                }
                int j1 = s9.indexOf("{[");
                int k1 = s9.indexOf("}");
                if(j1 >= 0 && k1 >= 0)
                {
                    s9 = s9.substring(k1 + 1);
                }
                hashmap.put("_reference" + (new Integer(k + 1)).toString(), s9);
            }

            fixDisableAlertingParams(hashmap);
            fixDisableGroupOrMonitorParams(hashmap);
            removeAPIDisableProperties(hashmap);
            if(s.equals("WebServiceMonitor"))
            {
                processWSDLParameters(hashmap);
            }
            java.lang.String s7 = (java.lang.String)hashmap.get("_machine");
            processMachineName(s7, hashmap);
            com.dragonflow.SiteView.AtomicMonitor atomicmonitor = instantiateMonitor(s);
            atomicmonitor.setMethodId(methodId);
            setMonitorProperties(OP_ADD, atomicmonitor, "", s1, hashmap);
            atomicmonitor.initialize(hashmap);
            validateProperties(hashmap, atomicmonitor, s, com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ALL);
            writeMonitor(OP_ADD, atomicmonitor, "", s1);
            com.dragonflow.SiteView.ScheduleManager schedulemanager = com.dragonflow.SiteView.ScheduleManager.getInstance();
            schedulemanager.addMonitorToScheduleObject(atomicmonitor);
            s2 = atomicmonitor.getProperty("_id");
            com.dragonflow.Api.APIMonitor.forceConfigurationRefresh();
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "create"
            }, 0L, exception.getMessage());
        }
        return new SSStringReturnValue(s2);
    }

    public void update(java.lang.String s, java.lang.String s1, com.dragonflow.Api.SSInstanceProperty assinstanceproperty[])
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            jgl.HashMap hashmap = new HashMap(true);
            java.lang.String s2 = "";
            boolean flag = false;
            boolean flag1 = false;
            java.lang.String s4 = null;
            for(int i = 0; i < assinstanceproperty.length; i++)
            {
                boolean flag2 = false;
                if(assinstanceproperty[i].getName().equals("portOther"))
                {
                    flag = true;
                    s4 = "_port";
                } else
                if(assinstanceproperty[i].getName().equals("oidOther"))
                {
                    flag = true;
                    s4 = "_oid";
                } else
                if(assinstanceproperty[i].getName().equals("_maxSearchDepthOther"))
                {
                    flag = true;
                    s4 = "_maxSearchDepth";
                } else
                if(assinstanceproperty[i].getName().equals("percentageBaseOther"))
                {
                    flag = true;
                    s4 = "_percentageBase";
                } else
                if(assinstanceproperty[i].getName().equals("scaleOther"))
                {
                    flag = true;
                    s4 = "_scale";
                } else
                if(assinstanceproperty[i].getName().equals("serviceOther"))
                {
                    flag = true;
                    s4 = "_service";
                } else
                if(assinstanceproperty[i].getName().equals("topazLogging"))
                {
                    flag1 = true;
                } else
                if(assinstanceproperty[i].getName().equals("_perfmonMsmtsProp"))
                {
                    hashmap.put(assinstanceproperty[i].getName(), com.dragonflow.SiteView.monitorUtils.transformPerfmonMeasurementsToMgFormat((java.lang.String)assinstanceproperty[i].getValue()));
                }
                if(flag)
                {
                    java.lang.String s3 = (java.lang.String)assinstanceproperty[i].getValue();
                    if(s3.length() > 0)
                    {
                        hashmap.put(s4, s3);
                    }
                    flag = false;
                    continue;
                }
                if(flag1)
                {
                    java.lang.String s5 = "";
                    if(assinstanceproperty[i].getValue() != null && ((java.lang.String)assinstanceproperty[i].getValue()).length() > 0)
                    {
                        s5 = (java.lang.String)assinstanceproperty[i].getValue();
                        if(!s5.equals("logEverything"))
                        {
                            hashmap.put(s5, "true");
                        }
                    }
                    if(!s5.equals("_notLogToTopaz"))
                    {
                        hashmap.put("_notLogToTopaz", "");
                    }
                    if(!s5.equals("_logOnlyMonitorData"))
                    {
                        hashmap.put("_logOnlyMonitorData", "");
                    }
                    if(!s5.equals("_logOnlyThresholdMeas"))
                    {
                        hashmap.put("_logOnlyThresholdMeas", "");
                    }
                    if(!s5.equals("_onlyStatusChanges"))
                    {
                        hashmap.put("_onlyStatusChanges", "");
                    }
                    flag1 = false;
                    continue;
                }
                if(assinstanceproperty[i].getName().equals("_port"))
                {
                    if((java.lang.String)hashmap.get("_port") != null)
                    {
                        flag2 = true;
                    }
                } else
                if(assinstanceproperty[i].getName().equals("_oid"))
                {
                    if((java.lang.String)hashmap.get("_oid") != null)
                    {
                        flag2 = true;
                    }
                } else
                if(assinstanceproperty[i].getName().equals("_maxSearchDepth"))
                {
                    if((java.lang.String)hashmap.get("_maxSearchDepth") != null)
                    {
                        flag2 = true;
                    }
                } else
                if(assinstanceproperty[i].getName().equals("_percentageBase"))
                {
                    if((java.lang.String)hashmap.get("_percentageBase") != null)
                    {
                        flag2 = true;
                    }
                } else
                if(assinstanceproperty[i].getName().equals("_scale"))
                {
                    if((java.lang.String)hashmap.get("_scale") != null)
                    {
                        flag2 = true;
                    }
                } else
                if(assinstanceproperty[i].getName().equals("_service") && (java.lang.String)hashmap.get("_service") != null)
                {
                    flag2 = true;
                }
                if(assinstanceproperty[i].getName().equals("_description") || assinstanceproperty[i].getName().equals("_monitorDescription") && assinstanceproperty[i].getValue() != null)
                {
                    assinstanceproperty[i] = new SSInstanceProperty(assinstanceproperty[i].getName(), com.dragonflow.Utils.TextUtils.replaceString((java.lang.String)assinstanceproperty[i].getValue(), "\r\n", " "));
                }
                if(!flag2)
                {
                    hashmap.add(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
                }
            }

            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            s1 = com.dragonflow.Utils.I18N.toDefaultEncoding(s1);
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElementByID(s1);
            com.dragonflow.SiteView.AtomicMonitor atomicmonitor = null;
            java.util.Enumeration enumeration = monitorgroup.getMonitors();
            while (enumeration.hasMoreElements()) {
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
                java.lang.String s7 = monitor.getProperty("_id");
                if((s7 != null) & s7.equals(s))
                {
                    atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)monitor;
                    break;
                }
            } 
            java.lang.String s6 = "_postData1";
            if(atomicmonitor.getPropertyObject(s6) != null)
            {
                fixPostDataParams(hashmap);
            }
            fixDisableAlertingParams(hashmap);
            fixDisableGroupOrMonitorParams(hashmap);
            removeAPIDisableProperties(hashmap);
            java.lang.String s8 = (java.lang.String)hashmap.get("_machine");
            processMachineName(s8, hashmap);
            if(atomicmonitor != null)
            {
                java.lang.String s9 = atomicmonitor.getClass().toString();
                int j = s9.lastIndexOf(".");
                if(j != -1)
                {
                    s9 = s9.substring(j + 1);
                }
                if(s9.equals("WebServiceMonitor"))
                {
                    processWSDLParameters(hashmap);
                }
                com.dragonflow.SiteView.ScheduleManager schedulemanager = com.dragonflow.SiteView.ScheduleManager.getInstance();
                java.lang.String s10 = schedulemanager.getScheduleIdFromMonitor(atomicmonitor);
                setMonitorProperties(OP_EDIT, atomicmonitor, s, s1, hashmap);
                validateProperties(hashmap, atomicmonitor, s9, FILTER_CONFIGURATION_EDIT_ALL);
                writeMonitor(OP_EDIT, atomicmonitor, s, s1);
                schedulemanager.updateMonitorInScheduleObject(s10, atomicmonitor);
            } else
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_UNASSOCIATED_ID, new java.lang.String[] {
                    s1 + "/" + s
                });
            }
            com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "update"
            }, 0L, exception.getMessage());
        }
    }

    private void fixPostDataParams(jgl.HashMap hashmap)
    {
        jgl.HashMap hashmap1 = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        int i = com.dragonflow.Utils.TextUtils.toInt(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_URLSequenceMonitorSteps"));
        for(int j = 0; j < i; j++)
        {
            java.lang.String s = (java.lang.String)hashmap.get("_postData" + (new Integer(j + 1)).toString());
            int k = -1;
            do
            {
                if(s != null && s.length() > 0)
                {
                    k = s.indexOf("{[");
                    int l = s.indexOf("}");
                    if(k >= 0 && l >= 0)
                    {
                        s = s.substring(0, k) + s.substring(l + 1);
                    }
                    hashmap.put("_postData" + (new Integer(j + 1)).toString(), s);
                }
            } while(k != -1);
            java.lang.String s1 = (java.lang.String)hashmap.get("_reference" + (new Integer(j + 1)).toString());
            if(s1 == null || s1.length() <= 0)
            {
                continue;
            }
            int i1 = s1.indexOf("{[");
            int j1 = s1.indexOf("}");
            if(i1 >= 0 && j1 >= 0)
            {
                s1 = s1.substring(j1 + 1);
            }
            hashmap.put("_reference" + (new Integer(j + 1)).toString(), s1);
        }

    }

    private void processMachineName(java.lang.String s, jgl.HashMap hashmap)
        throws com.dragonflow.SiteViewException.SiteViewParameterException
    {
        if(s != null)
        {
            if(s.length() > 0)
            {
                try
                {
                    if(s.startsWith("\\\\"))
                    {
                        s = s.substring(2);
                    } else
                    if(s.startsWith("remote:"))
                    {
                        s = com.dragonflow.SiteView.Machine.getMachineHost(s);
                    }
                    java.net.InetAddress inetaddress = java.net.InetAddress.getByName(s);
                    java.lang.String s1 = inetaddress.getHostAddress();
                    java.net.InetAddress inetaddress1 = java.net.InetAddress.getLocalHost();
                    java.lang.String s2 = inetaddress1.getHostAddress();
                    if(s1.equals(s2))
                    {
                        hashmap.remove("_machine");
                    }
                }
                catch(java.net.UnknownHostException unknownhostexception)
                {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_NO_IP, new java.lang.String[] {
                        "localhost"
                    });
                }
                catch(java.lang.Exception exception)
                {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_NO_IP, new java.lang.String[] {
                        s
                    });
                }
            } else
            {
                hashmap.remove("_machine");
            }
        }
    }

    public void delete(java.lang.String s, java.lang.String s1)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            com.dragonflow.SiteView.ScheduleManager schedulemanager = com.dragonflow.SiteView.ScheduleManager.getInstance();
            com.dragonflow.SiteView.AtomicMonitor atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)com.dragonflow.SiteView.SiteViewGroup.currentSiteView().getElement(s1 + "/" + s);
            schedulemanager.deleteMonitorFromScheduleObject(schedulemanager.getScheduleIdFromMonitor(atomicmonitor), atomicmonitor.getFullID());
            deleteMonitorInternal(s1 + " " + s);
            saveGroups();
            com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "delete"
            }, 0L, exception.getMessage());
        }
    }

    public com.dragonflow.Api.SSStringReturnValue move(java.lang.String s, java.lang.String s1, java.lang.String s2)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s3 = "";
        try
        {
            jgl.Array array = new Array();
            jgl.Array array1 = new Array();
            array1.add("");
            array.add(s1 + " " + s);
            com.dragonflow.SiteView.ConfigurationChanger configurationchanger = new ConfigurationChanger();
            java.lang.String as[] = new java.lang.String[0];
            configurationchanger.manageMonitors(array, array1, s2, true, as);
            jgl.Array array2 = ReadGroupFrames(s2);
            s3 = (java.lang.String)((jgl.HashMap)array2.at(0)).get("_nextID");
            long l = java.lang.Long.parseLong(s3);
            s3 = java.lang.String.valueOf(l - 1L);
            com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "move"
            }, 0L, exception.getMessage());
        }
        return new SSStringReturnValue(s3);
    }

    public com.dragonflow.Api.SSStringReturnValue copy(java.lang.String s, java.lang.String s1, java.lang.String s2)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s3 = "";
        try
        {
            jgl.Array array = new Array();
            jgl.Array array1 = new Array();
            array.add(s1 + " " + s);
            com.dragonflow.SiteView.ConfigurationChanger configurationchanger = new ConfigurationChanger();
            java.lang.String as[] = new java.lang.String[0];
            jgl.Array array2 = getGroupFrames(s1);
            int i = com.dragonflow.Page.CGI.findMonitorIndex(array2, s);
            if(i >= 1)
            {
                jgl.HashMap hashmap = (jgl.HashMap)array2.at(i);
                array1.add(hashmap.get("_name"));
            }
            jgl.Array array3 = configurationchanger.manageMonitors(array, array1, s2, false, as);
            s3 = (java.lang.String)((jgl.HashMap)array3.at(0)).get("_nextID");
            long l = java.lang.Long.parseLong(s3);
            s3 = java.lang.String.valueOf(l - 1L);
            com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "copy"
            }, 0L, exception.getMessage());
        }
        return new SSStringReturnValue(s3);
    }

    public com.dragonflow.Api.SSMonitorInstance runExisting(java.lang.String s, java.lang.String s1, long l)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        return runExisting(s, s1, l, false);
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @deprecated Method runExisting is deprecated
     */
    public com.dragonflow.Api.SSMonitorInstance runExisting(java.lang.String s, java.lang.String s1, long l, boolean flag)
    throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSMonitorInstance ssmonitorinstance;
        
        ssmonitorinstance = null;
        try
        {
            com.dragonflow.SiteView.AtomicMonitor atomicmonitor;
            boolean flag1;
            
            
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            s1 = com.dragonflow.Utils.I18N.toDefaultEncoding(s1);
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElementByID(s1);
            atomicmonitor = null;
            if(monitorgroup != null)
            {
                java.util.Enumeration enumeration = monitorgroup.getMonitors();
                com.dragonflow.SiteView.Monitor monitor;
                java.lang.String s2;
                while (enumeration.hasMoreElements())
                {
                    monitor = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
                    s2 = monitor.getProperty("_id");
                    if (s2 != null && s2.equals(s)) {
                        atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)monitor;
                    }
                }
                
                flag1 = false;
                if(atomicmonitor != null)
                {
                    
                    long l1 = (new Date()).getTime();
                    
                    while (atomicmonitor.isRunning())
                    {
                        com.dragonflow.SiteView.Platform.sleep(1000L);
                        if(atomicmonitor.isRunning() && l >= 0L && (new Date()).getTime() > l1 + l)
                        {
                            flag1 = true;
                            break;
                        }
                    } 
                    
                    if(flag1)
                    {
                        throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_API_MONITOR_TIMED_OUT_WAITING);
                    }
                    atomicmonitor.runUpdate(true);
                    if(atomicmonitor.isRunning())
                    {
                        l1 = (new Date()).getTime();
                        while (atomicmonitor.isRunning())
                        {
                            com.dragonflow.SiteView.Platform.sleep(1000L);
                            if (atomicmonitor.isRunning() && l >= 0L && (new Date()).getTime() > l1 + l) {
                                flag1 = true;
                            }
                        }
                    }
                    if(flag1)
                    {
                        throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_API_MONITOR_TIMED_OUT);
                    }
                    com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = getPropertiesForMonitorInstance(atomicmonitor, null, FILTER_RUNTIME_ALL);
                    if(!atomicmonitor.collectionErrorOccurred() || flag)
                    {
                        ssmonitorinstance = new SSMonitorInstance(s1, s, assinstanceproperty);
                    } else
                    {
                        com.dragonflow.SiteViewException.SiteViewError siteviewerror = atomicmonitor.getCollectionError();
                        if(siteviewerror.getType() == 1)
                        {
                            throw new SiteViewAvailabilityException(siteviewerror);
                        } else
                        {
                            throw new SiteViewOperationalException(siteviewerror);
                        }
                    }
                } else {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_UNASSOCIATED_ID, new java.lang.String[] {
                            s1 + "/" + s
                    });
                }
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                    "APIMonitor", "runExisting"
            }, 0L, exception.getMessage());
        }
        return ssmonitorinstance;
    }

    public com.dragonflow.Api.SSInstanceProperty[] runTemporary(java.lang.String s, com.dragonflow.Api.SSInstanceProperty assinstanceproperty[], long l)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        return runTemporary(s, assinstanceproperty, l, false);
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @deprecated Method runTemporary is deprecated
     */
    public com.dragonflow.Api.SSInstanceProperty[] runTemporary(java.lang.String s, com.dragonflow.Api.SSInstanceProperty assinstanceproperty[], long l, boolean flag)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = null;
        com.dragonflow.SiteView.AtomicMonitor atomicmonitor;
        com.dragonflow.Utils.ThreadPool.SingleThread singlethread;
        
        try {
        jgl.HashMap hashmap = new HashMap(true);
        for(int i = 0; i < assinstanceproperty.length; i++)
        {
            hashmap.add(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
        }

        atomicmonitor = instantiateMonitor(s);
        setMonitorProperties(OP_TEMP, atomicmonitor, "", "", hashmap);
        validateProperties(hashmap, atomicmonitor, s, com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ALL);
        singlethread = com.dragonflow.SiteView.AtomicMonitor.monitorThreadsPool.getThread();
        singlethread.setName("Temporary monitor run thread");
        java.lang.Object obj1 = new Object();
        synchronized (obj1) {
        Worker worker = null;
        try
        {
            worker = new Worker(atomicmonitor, obj1);
            singlethread.activate(worker);
            if(l < 0L)
            {
                obj1.wait();
            } else
            {
                obj1.wait(l);
            }
        }
        catch(java.lang.InterruptedException interruptedexception) { }
        if(flag)
        {
            return getPropertiesForMonitorInstance(atomicmonitor, null, com.dragonflow.Api.APISiteView.FILTER_RUNTIME_ALL);
        }
        if(!worker.timedOut)
        {
            if(!atomicmonitor.collectionErrorOccurred())
            {
                assinstanceproperty1 = getPropertiesForMonitorInstance(atomicmonitor, null, com.dragonflow.Api.APISiteView.FILTER_RUNTIME_ALL);
            } else
            {
                com.dragonflow.SiteViewException.SiteViewError siteviewerror = atomicmonitor.getCollectionError();
                if(siteviewerror.getType() == 1)
                {
                    throw new SiteViewAvailabilityException(siteviewerror);
                } else
                {
                    throw new SiteViewOperationalException(siteviewerror);
                }
            }
        } else
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_API_MONITOR_TIMED_OUT);
        }
        }
        }
        catch (SiteViewException e) {
        e.fillInStackTrace();
        throw e;
        }
        catch (Exception e) {
        throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
            "APIMonitor", "runTemporary"
        }, 0L, e.getMessage());
        }

        return assinstanceproperty1;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @return
     * @throws com.dragonflow.SiteViewException.SiteViewException
     */
    public com.dragonflow.Api.SSInstanceProperty[] getClassAttributes(java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try {
        com.dragonflow.Api.SSInstanceProperty assinstanceproperty[];
        jgl.HashMap hashmap = getClassAttribs(s);
        assinstanceproperty = null;
        int i = 0;
        assinstanceproperty = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
        for(java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements();)
        {
            java.lang.String s1 = (java.lang.String)enumeration.nextElement();
            java.lang.String s2 = "";
            if(!s1.equals("elements"))
            {
                s2 = (java.lang.String)hashmap.get(s1);
            }
            assinstanceproperty[i] = new SSInstanceProperty(s1, s2);
            i++;
        }

        return assinstanceproperty;
        }
        catch (SiteViewException e) {
        e.fillInStackTrace();
        throw e;
        }
        catch (Exception e) {
        throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
            "APIMonitor", "getClassAttributes"
        }, 0L, e.getMessage());
    }
    }

    public com.dragonflow.Api.SSPropertyDetails[] getClassPropertiesDetails(java.lang.String s, int i, com.dragonflow.Api.SSInstanceProperty assinstanceproperty[])
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSPropertyDetails asspropertydetails[] = null;
        try
        {
            jgl.Array array = new Array();
            com.dragonflow.SiteView.AtomicMonitor atomicmonitor = instantiateMonitor(s);
            for(int j = 0; j < assinstanceproperty.length; j++)
            {
                atomicmonitor.setProperty(assinstanceproperty[j].getName(), (java.lang.String)assinstanceproperty[j].getValue());
            }

            for(java.util.Enumeration enumeration = getFilteredMonitorProperties(atomicmonitor, new Vector(), i); enumeration.hasMoreElements(); array.add(enumeration.nextElement())) { }
            java.util.HashMap hashmap = new java.util.HashMap();
            for(int k = 0; k < assinstanceproperty.length; k++)
            {
                if(assinstanceproperty[k] != null)
                {
                    hashmap.put(assinstanceproperty[k].getName(), assinstanceproperty[k].getValue());
                }
            }

            java.util.Vector vector = createThresholdProperties(i, array, atomicmonitor, hashmap);
            asspropertydetails = new com.dragonflow.Api.SSPropertyDetails[array.size() + vector.size()];
            for(int l = 0; l < array.size(); l++)
            {
                asspropertydetails[l] = getClassProperty((com.dragonflow.Properties.StringProperty)array.at(l), atomicmonitor, hashmap, false);
            }

            for(int i1 = 0; i1 < vector.size(); i1++)
            {
                asspropertydetails[i1 + array.size()] = (com.dragonflow.Api.SSPropertyDetails)vector.elementAt(i1);
            }

        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "getClassPropertiesDetails"
            }, 0L, exception.getMessage());
        }
        return asspropertydetails;
    }

    public com.dragonflow.Api.SSPropertyDetails getClassPropertyDetails(java.lang.String s, java.lang.String s1, com.dragonflow.Api.SSInstanceProperty assinstanceproperty[])
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSPropertyDetails sspropertydetails = null;
        try
        {
            Object obj = null;
            com.dragonflow.SiteView.AtomicMonitor atomicmonitor = instantiateMonitor(s1);
            if(com.dragonflow.Api.APIMonitor.isValidObject(atomicmonitor.getClass().getName(), "Monitor"))
            {
                java.util.HashMap hashmap = new java.util.HashMap();
                for(int i = 0; i < assinstanceproperty.length; i++)
                {
                    if(assinstanceproperty[i] != null)
                    {
                        hashmap.put(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
                    }
                }

                for(int j = 0; j < assinstanceproperty.length; j++)
                {
                    if(assinstanceproperty[j] != null)
                    {
                        atomicmonitor.setProperty(assinstanceproperty[j].getName(), (java.lang.String)assinstanceproperty[j].getValue());
                    }
                }

                com.dragonflow.Properties.StringProperty stringproperty = atomicmonitor.getPropertyObject(s);
                if(s.indexOf("error-") >= 0 || s.indexOf("warning-") >= 0 || s.indexOf("good-") >= 0)
                {
                    java.util.Enumeration enumeration = atomicmonitor.getStatePropertyObjects(false);
                    if(!atomicmonitor.isMultiThreshold())
                    {
                        jgl.Array array = atomicmonitor.getProperties();
                        enumeration = array.elements();
                    }
                    jgl.Array array1 = new Array();
                    while (enumeration.hasMoreElements()) {
                        com.dragonflow.Properties.StringProperty stringproperty1 = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
                        if(stringproperty1.isThreshold())
                        {
                            array1.add(stringproperty1);
                        }
                    } 

                    sspropertydetails = getThreshold(s, array1, atomicmonitor);
                    if(sspropertydetails == null)
                    {
                        throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_NONEXISTANT_PROPERTY, new java.lang.String[] {
                            s1, s
                        });
                    }
                } else
                if(s.indexOf("availableObjects") != -1)
                {
                    stringproperty = new StringProperty("availableObjects", "", "Available Objects");
                    stringproperty.isMultiLine = true;
                    sspropertydetails = getClassProperty(stringproperty, atomicmonitor, hashmap, true);
                } else
                if(s.indexOf("availableCountersHierarchical") != -1)
                {
                    stringproperty = new StringProperty("availableCountersHierarchical", "", "Available Counters Hierarchical");
                    stringproperty.isMultiLine = true;
                    sspropertydetails = getClassProperty(stringproperty, atomicmonitor, hashmap, true);
                } else
                if(s.indexOf("availableCounters") != -1)
                {
                    stringproperty = new StringProperty("availableCounters", "", "Available Counters");
                    stringproperty.isMultiLine = true;
                    sspropertydetails = getClassProperty(stringproperty, atomicmonitor, hashmap, true);
                } else
                if(s.indexOf("defaultCounters") != -1)
                {
                    stringproperty = new StringProperty("defaultCounters", "", "Default Counters");
                    stringproperty.isMultiLine = true;
                    sspropertydetails = getClassProperty(stringproperty, atomicmonitor, hashmap, true);
                } else
                if(s.indexOf("availableInstances") != -1)
                {
                    stringproperty = new StringProperty("availableInstances", "", "Available Instances");
                    stringproperty.isMultiLine = true;
                    sspropertydetails = getClassProperty(stringproperty, atomicmonitor, hashmap, true);
                } else
                {
                    if(s != null && stringproperty == null)
                    {
                        throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_PROPERTY_NOT_FOUND, new java.lang.String[] {
                            s
                        });
                    }
                    sspropertydetails = getClassProperty(stringproperty, atomicmonitor, hashmap, true);
                }
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "getClassPropertyDetails"
            }, 0L, exception.getMessage());
        }
        return sspropertydetails;
    }

    public com.dragonflow.Api.SSPropertyDetails getInstancePropertyDetails(java.lang.String s, java.lang.String s1, java.lang.String s2)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSPropertyDetails sspropertydetails = null;
        try
        {
            jgl.Array array = null;
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            s2 = com.dragonflow.Utils.I18N.toDefaultEncoding(s2);
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElementByID(s2);
            com.dragonflow.SiteView.AtomicMonitor atomicmonitor = null;
            java.util.Enumeration enumeration = monitorgroup.getMonitors();
            while (enumeration.hasMoreElements()) {
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
                java.lang.String s3 = monitor.getProperty("_id");
                if((s3 != null) & s3.equals(s1))
                {
                    atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)monitor;
                    break;
                }
            }
            
            if(atomicmonitor != null)
            {
                com.dragonflow.Properties.StringProperty stringproperty = atomicmonitor.getPropertyObject(s);
                if(s.indexOf("error-") >= 0 || s.indexOf("warning-") >= 0 || s.indexOf("good-") >= 0)
                {
                    java.util.Enumeration enumeration1 = array.elements();
                    jgl.Array array1 = new Array();
                    while (enumeration1.hasMoreElements()) {
                        com.dragonflow.Properties.StringProperty stringproperty1 = (com.dragonflow.Properties.StringProperty)enumeration1.nextElement();
                        if(stringproperty1.isThreshold())
                        {
                            array1.add(stringproperty1);
                        }
                    } 
                    
                    sspropertydetails = getThreshold(s, array1, atomicmonitor);
                    if(sspropertydetails == null)
                    {
                        throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_NONEXISTANT_PROPERTY, new java.lang.String[] {
                            s2 + "/" + s1, s
                        });
                    }
                } else
                {
                    sspropertydetails = getClassProperty(stringproperty, atomicmonitor, new java.util.HashMap(), true);
                }
            } else
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_UNASSOCIATED_ID, new java.lang.String[] {
                    s2 + "/" + s1
                });
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "getInstancePropertyDetails"
            }, 0L, exception.getMessage());
        }
        return sspropertydetails;
    }

    public com.dragonflow.Api.SSMonitorInstance[] getInstances(java.lang.String s, int i)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSMonitorInstance assmonitorinstance[] = null;
        try
        {
            if(s == null || s.length() == 0)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_GROUP_ID_MISSING);
            }
            java.util.Vector vector = new Vector();
            java.util.Collection collection = getMonitorsForGroup(s);
            java.lang.String s1;
            java.lang.String s2;
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[];
            for(java.util.Iterator iterator = collection.iterator(); iterator.hasNext(); vector.addElement(new SSMonitorInstance(s1, s2, assinstanceproperty1)))
            {
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)iterator.next();
                s1 = monitor.getProperty(com.dragonflow.SiteView.Monitor.pOwnerID);
                if(!$assertionsDisabled && !s1.equals(s))
                {
                    throw new AssertionError();
                }
                s2 = monitor.getProperty(com.dragonflow.SiteView.Monitor.pID);
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = getInstanceProperties(s2, s1, i);
                int k = 0;
                boolean flag = false;
                if(com.dragonflow.Api.Alert.getInstance().getAlertsResidingInGroupOrMonitor(s1, s2).size() > 0)
                {
                    flag = true;
                    k++;
                }
                assinstanceproperty1 = new com.dragonflow.Api.SSInstanceProperty[assinstanceproperty.length + k];
                if(flag)
                {
                    assinstanceproperty1[0] = new SSInstanceProperty("hasDependencies", "true");
                }
                for(int l = 0; l < assinstanceproperty.length; l++)
                {
                    assinstanceproperty1[l + k] = assinstanceproperty[l];
                }

            }

            assmonitorinstance = new com.dragonflow.Api.SSMonitorInstance[vector.size()];
            for(int j = 0; j < vector.size(); j++)
            {
                assmonitorinstance[j] = (com.dragonflow.Api.SSMonitorInstance)vector.elementAt(j);
            }

        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "getInstances"
            }, 0L, exception.getMessage());
        }
        return assmonitorinstance;
    }

    public com.dragonflow.Api.SSInstanceProperty[] getInstanceProperties(java.lang.String s, java.lang.String s1, int i, boolean flag)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = null;
        try
        {
            com.dragonflow.SiteView.AtomicMonitor atomicmonitor = null;
            java.util.Collection collection = getMonitorsForGroup(s1);
            java.util.Iterator iterator = collection.iterator();
            while (iterator.hasNext()) {
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)iterator.next();
                java.lang.String s2 = monitor.getProperty("_id");
                if(s2 != null && s2.equals(s))
                {
                atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)monitor;
                break;
                }
            } 
            if(atomicmonitor != null)
            {
                assinstanceproperty = getPropertiesForMonitorInstance(atomicmonitor, "", i);
                if(flag && com.dragonflow.Api.Alert.getInstance().getAlertsResidingInGroupOrMonitor(s1, s).size() > 0)
                {
                    com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = new com.dragonflow.Api.SSInstanceProperty[assinstanceproperty.length + 1];
                    java.lang.System.arraycopy(assinstanceproperty, 0, assinstanceproperty1, 0, assinstanceproperty.length);
                    assinstanceproperty1[assinstanceproperty1.length - 1] = new SSInstanceProperty("hasDependencies", "true");
                    assinstanceproperty = assinstanceproperty1;
                }
            } else
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_UNASSOCIATED_ID, new java.lang.String[] {
                    s1 + "/" + s
                });
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "getInstanceProperties"
            }, 0L, exception.getMessage());
        }
        return assinstanceproperty;
    }

    public com.dragonflow.Api.SSInstanceProperty[] getInstanceProperties(java.lang.String s, java.lang.String s1, int i)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        return getInstanceProperties(s, s1, i, false);
    }

    public com.dragonflow.Api.SSInstanceProperty getInstanceProperty(java.lang.String s, java.lang.String s1, java.lang.String s2)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSInstanceProperty ssinstanceproperty = null;
        try
        {
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            s2 = com.dragonflow.Utils.I18N.toDefaultEncoding(s2);
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElementByID(s2);
            com.dragonflow.SiteView.AtomicMonitor atomicmonitor = null;
            java.util.Enumeration enumeration = monitorgroup.getMonitors();
            while (enumeration.hasMoreElements()) {
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
                java.lang.String s3 = monitor.getProperty("_id");
                if((s3 != null) & s3.equals(s1))
                {
                atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)monitor;
                break;
                }
            }
            Object obj = null;
            if(atomicmonitor != null)
            {
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = getPropertiesForMonitorInstance(atomicmonitor, s, com.dragonflow.Api.APISiteView.FILTER_ALL);
                for(int i = 0; i < assinstanceproperty.length; i++)
                {
                    if(assinstanceproperty[i].getName().equals(s))
                    {
                        ssinstanceproperty = assinstanceproperty[i];
                    }
                }

            } else
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_UNASSOCIATED_ID, new java.lang.String[] {
                    s2 + "/" + s1
                });
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, 0L, exception.getMessage());
        }
        return ssinstanceproperty;
    }

    public com.dragonflow.Api.SSInstanceProperty[] getURLStepProperties(java.lang.String s, java.lang.String s1, com.dragonflow.Api.SSInstanceProperty assinstanceproperty[], java.lang.String s2)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = null;
        try
        {
            jgl.HashMap hashmap = new HashMap(true);
            for(int i = 0; i < assinstanceproperty.length; i++)
            {
                hashmap.add(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
            }

            com.dragonflow.SiteView.AtomicMonitor atomicmonitor = instantiateMonitor(s);
            setMonitorProperties(OP_TEMP, atomicmonitor, "", s1, hashmap);
            hashmap = validateProperties(hashmap, atomicmonitor, s, com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ALL);
            java.lang.StringBuffer stringbuffer = new StringBuffer();
            java.lang.StringBuffer stringbuffer1 = new StringBuffer();
            java.lang.StringBuffer stringbuffer2 = new StringBuffer();
            java.lang.StringBuffer stringbuffer3 = new StringBuffer();
            long al[] = com.dragonflow.StandardMonitor.URLSequenceMonitor.checkURLSequence(hashmap, stringbuffer, null, stringbuffer3, stringbuffer1, stringbuffer2, (com.dragonflow.StandardMonitor.URLSequenceMonitor)atomicmonitor);
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty2[] = getPropertiesForMonitorInstance(atomicmonitor, "", com.dragonflow.Api.APISiteView.FILTER_ALL);
            assinstanceproperty1 = new com.dragonflow.Api.SSInstanceProperty[assinstanceproperty2.length + 7];
            java.lang.String s3 = com.dragonflow.StandardMonitor.URLMonitor.getHTTPContent(stringbuffer1.toString());
            assinstanceproperty1[0] = new SSInstanceProperty("content", s3);
            if(s3.length() > 0)
            {
                com.dragonflow.Utils.HTMLTagParser htmltagparser = new HTMLTagParser(s3, TARGET_TAGS);
                jgl.HashMap hashmap1 = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
                htmltagparser.ignoreScripts = false;
                htmltagparser.ignoreNoscripts = false;
                if(hashmap1.get("_urlHTMLInJavaScript") != null && ((java.lang.String)hashmap1.get("_urlHTMLInJavaScript")).length() == 0)
                {
                    htmltagparser.ignoreScripts = true;
                    htmltagparser.ignoreNoscripts = true;
                }
                htmltagparser.process();
                java.util.Enumeration enumeration = getLinks(htmltagparser);
                java.lang.String s4 = "";
                for(; enumeration.hasMoreElements(); enumeration.nextElement())
                {
                    s4 = s4 + (java.lang.String)enumeration.nextElement() + "\r\n";
                }

                assinstanceproperty1[1] = new SSInstanceProperty("links", s4);
                s4 = "";
                for(java.util.Enumeration enumeration1 = getForms(htmltagparser, atomicmonitor, s2); enumeration1.hasMoreElements(); enumeration1.nextElement())
                {
                    s4 = s4 + (java.lang.String)enumeration1.nextElement() + "\r\n";
                }

                assinstanceproperty1[2] = new SSInstanceProperty("forms", s4);
                for(int k = 0; k < assinstanceproperty2.length; k++)
                {
                    if(assinstanceproperty2[k].getName().equals("_postData" + s2))
                    {
                        assinstanceproperty2[k] = new SSInstanceProperty("_postData" + s2, atomicmonitor.getProperty("_postData" + s2));
                    }
                }

                s4 = "";
                for(java.util.Enumeration enumeration2 = getFrames(htmltagparser); enumeration2.hasMoreElements(); enumeration2.nextElement())
                {
                    s4 = s4 + (java.lang.String)enumeration2.nextElement() + "\r\n";
                }

                assinstanceproperty1[3] = new SSInstanceProperty("frames", s4);
                s4 = "";
                for(java.util.Enumeration enumeration3 = getRefresh(htmltagparser); enumeration3.hasMoreElements(); enumeration3.nextElement())
                {
                    s4 = s4 + (java.lang.String)enumeration3.nextElement() + "\r\n";
                }

                assinstanceproperty1[4] = new SSInstanceProperty("metas", s4);
                java.lang.String s5 = "";
                int l = stringbuffer3.toString().toLowerCase().lastIndexOf("<hr><b><a name=step");
                if(l >= 0 && l < stringbuffer3.length())
                {
                    int i1 = -1;
                    for(i1 = stringbuffer2.toString().toLowerCase().indexOf("content-type:"); i1 >= 0 && stringbuffer2.toString().substring(i1 + 13).toLowerCase().indexOf("content-type:") >= 0; i1 += stringbuffer2.toString().substring(i1 + 13).toLowerCase().indexOf("content-type:") + 13) { }
                    if(i1 >= 0)
                    {
                        int j1 = stringbuffer2.toString().substring(i1).toLowerCase().indexOf("<!doctype");
                        if(j1 < 0)
                        {
                            j1 = stringbuffer2.toString().substring(i1).toLowerCase().indexOf("<html");
                        }
                        if(j1 > 0)
                        {
                            i1 += j1;
                        }
                    }
                    s5 = stringbuffer2.toString().substring(0, i1);
                }
                assinstanceproperty1[5] = new SSInstanceProperty("header", s5);
                assinstanceproperty1[6] = new SSInstanceProperty("httpstatus", (new Long(al[0])).toString());
            }
            for(int j = 0; j < assinstanceproperty2.length; j++)
            {
                assinstanceproperty1[j + 7] = assinstanceproperty2[j];
            }

        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "getURLStepProperties"
            }, 0L, exception.getMessage());
        }
        return assinstanceproperty1;
    }

    public java.util.Collection getAllMonitors()
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.util.Vector vector = new Vector();
        com.dragonflow.SiteView.ConfigurationChanger.getGroupsMonitors(getAllAllowedGroups(), vector, null, false);
        return vector;
    }

    public java.util.Collection getChildMonitors(java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        return getMonitorsForGroup(s);
    }

    public com.dragonflow.Api.SSStringReturnValue[] getMonitorTypes()
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSStringReturnValue assstringreturnvalue[] = null;
        try
        {
            int i = findType("Monitor");
            jgl.Array array = (jgl.Array)ssChildObjects.elementAt(i);
            assstringreturnvalue = new com.dragonflow.Api.SSStringReturnValue[array.size()];
            for(int j = 0; j < array.size(); j++)
            {
                com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = new SSStringReturnValue(((java.lang.String[])array.at(j))[0]);
                int k = ssstringreturnvalue.getValue().lastIndexOf(".");
                if(k != -1)
                {
                    ssstringreturnvalue = new SSStringReturnValue(ssstringreturnvalue.getValue().substring(k + 1));
                }
                assstringreturnvalue[j] = ssstringreturnvalue;
            }

        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "getMonitorTypes"
            }, 0L, exception.getMessage());
        }
        return assstringreturnvalue;
    }

    public com.dragonflow.Api.SSStringReturnValue getTopazID(java.lang.String s, java.lang.String s1)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = null;
        try
        {
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            s1 = com.dragonflow.Utils.I18N.toDefaultEncoding(s1);
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElementByID(s1);
            com.dragonflow.SiteView.AtomicMonitor atomicmonitor = null;
            java.util.Enumeration enumeration = monitorgroup.getMonitors();
            while (enumeration.hasMoreElements()) {
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
                java.lang.String s2 = monitor.getProperty("_id");
                if((s2 != null) & s2.equals(s))
                {
                atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)monitor;
                break;
                }
            } 
            if(atomicmonitor != null)
            {
//                ssstringreturnvalue = getTopazID(atomicmonitor);
            } else
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_UNASSOCIATED_TOPAZ_ID, new java.lang.String[] {
                    s1, s
                });
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "getTopazID"
            }, 0L, exception.getMessage());
        }
        return ssstringreturnvalue;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param s1
     * @param hashmap
     * @throws com.dragonflow.SiteViewException.SiteViewException
     */
    public void addBrowsableCounters(java.lang.String s, java.lang.String s1, java.util.HashMap hashmap)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try {       
        com.dragonflow.SiteView.AtomicMonitor atomicmonitor;
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        s1 = com.dragonflow.Utils.I18N.toDefaultEncoding(s1);
        com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElementByID(s1);
        atomicmonitor = null;
        java.util.Enumeration enumeration = monitorgroup.getMonitors();
        while (enumeration.hasMoreElements())
            {
            com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
            java.lang.String s2 = monitor.getProperty("_id");
            if((s2 != null) & s2.equals(s))
            {
            atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)monitor;
            break;
            }
        } 
        
        String s9;
        java.lang.String s3;
        int i;
        jgl.HashMap hashmap1;
        java.util.Iterator iterator;
        if(atomicmonitor instanceof com.dragonflow.SiteView.BrowsableMonitor) {
        if(atomicmonitor != null) {
        s9 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getBrowseName();
        s3 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getBrowseID();
        i = s3.length();
        hashmap1 = new HashMap();
        java.util.Set set = hashmap.keySet();
        iterator = set.iterator();
        }
        else {
        throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_UNASSOCIATED_ID, new java.lang.String[] {
            s1 + "/" + s
        });
        }
        }
        else {
        throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_BROWSABLE_TYPE_REQUIRED, new java.lang.String[] {
            s1 + "/" + s
        });
        }

        while (iterator.hasNext())
        {
            java.lang.String s4 = (java.lang.String)iterator.next();
            java.lang.String s6 = (java.lang.String)hashmap.get(s4);
            jgl.HashMap hashmap2 = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
            int k = com.dragonflow.Utils.TextUtils.toInt(com.dragonflow.Utils.TextUtils.getValue(hashmap2, "_browsableContentMaxCounters"));
            if(k == 0)
            {
                k = 10;
            }
            for(int l = 0; l < k; l++)
            {
                if(atomicmonitor.getProperty(s3 + l) != null && atomicmonitor.getProperty(s3 + l).equals(s6))
                {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_COUNTER_ALREADY_EXISTS, new java.lang.String[] {
                        s6
                    });
                }
            }

            int i1 = 1;
            while (true)
            {
                if(s4.startsWith(s3))
                {
                    if(hashmap1.get(s3 + i1) == null && (atomicmonitor.getProperty(s3 + i1) == null || atomicmonitor.getProperty(s3 + i1).length() == 0) && hashmap1.get(s9 + i1) == null && (atomicmonitor.getProperty(s9 + i1) == null || atomicmonitor.getProperty(s9 + i1).length() == 0))
                    {
                        hashmap1.put(s3 + i1, hashmap.get(s4));
                        java.lang.String s7 = s9 + s4.substring(i);
                        if(hashmap.get(s7) != null && ((java.lang.String)hashmap.get(s7)).length() > 0)
                        {
                            hashmap1.put(s9 + i1, hashmap.get(s7));
                        } else
                        {
                            throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_UNASSOCIATED_COUNTER_ID);
                        }
                        break; 
                    }
                } else
                {
                    if(!s4.startsWith(s9))
                    {
                        throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_COUNTER_PROPERTY_NOT_VALID);
                    }
                    break; 
                }
                i1++;
            } 
        }
        
        java.lang.String s5 = atomicmonitor.getClass().toString();
        int j = s5.lastIndexOf(".");
        if(j != -1)
        {
            s5 = s5.substring(j + 1);
        }
        jgl.Array array = ReadGroupFrames(s1);
        com.dragonflow.SiteView.AtomicMonitor atomicmonitor1 = com.dragonflow.SiteView.AtomicMonitor.MonitorCreate(array, s, "");
        setMonitorProperties(OP_EDIT, atomicmonitor1, s, s1, hashmap1);
        validateProperties(hashmap1, atomicmonitor1, s5, com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_EDIT_ALL);
        writeMonitor(OP_EDIT, atomicmonitor1, s, s1);
        DetectConfigurationChange dcc;
        dcc = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
        dcc.setConfigChangeFlag();
        }
        catch (SiteViewException e) {
        e.fillInStackTrace();
        throw e;
        }
        catch (Exception e) {
        throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
            "APIMonitor", "addBrowsableCounters"
        }, 0L, e.getMessage());
        }

        return;
    }

    public void removeBrowsableCounters(java.lang.String s, java.lang.String s1, java.util.HashMap hashmap)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            s1 = com.dragonflow.Utils.I18N.toDefaultEncoding(s1);
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElementByID(s1);
            com.dragonflow.SiteView.AtomicMonitor atomicmonitor = null;
            java.util.Enumeration enumeration = monitorgroup.getMonitors();
            while (enumeration.hasMoreElements()) {
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
                java.lang.String s3 = monitor.getProperty("_id");
                if((s3 != null) & s3.equals(s))
                {
                atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)monitor;
                break;
                }
            } 
            if(atomicmonitor instanceof com.dragonflow.SiteView.BrowsableMonitor)
            {
                if(atomicmonitor != null)
                {
                    java.lang.String s2 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getBrowseName();
                    java.lang.String s4 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getBrowseID();
                    jgl.HashMap hashmap1 = new HashMap();
                    java.util.Set set = hashmap.keySet();
                    for(java.util.Iterator iterator = set.iterator(); iterator.hasNext();)
                    {
                        java.lang.String s5 = (java.lang.String)iterator.next();
                        java.lang.String s7 = (java.lang.String)hashmap.get(s5);
                        jgl.HashMap hashmap2 = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
                        int j = com.dragonflow.Utils.TextUtils.toInt(com.dragonflow.Utils.TextUtils.getValue(hashmap2, "_browsableContentMaxCounters"));
                        if(j == 0)
                        {
                            j = 10;
                        }
                        boolean flag = false;
                        int k = 0;
                        do
                        {
                            if(k >= j)
                            {
                                break;
                            }
                            if(atomicmonitor.getProperty(s4 + k) != null && atomicmonitor.getProperty(s4 + k).endsWith(s7))
                            {
                                flag = true;
                                hashmap1.put(s4 + k, "");
                                hashmap1.put(s2 + k, "");
                                break;
                            }
                            k++;
                        } while(true);
                        if(!flag)
                        {
                            throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_COUNTER_DOES_NOT_EXIST, new java.lang.String[] {
                                s7
                            });
                        }
                    }

                    java.lang.String s6 = atomicmonitor.getClass().toString();
                    int i = s6.lastIndexOf(".");
                    if(i != -1)
                    {
                        s6 = s6.substring(i + 1);
                    }
                    jgl.Array array = ReadGroupFrames(s1);
                    com.dragonflow.SiteView.AtomicMonitor atomicmonitor1 = com.dragonflow.SiteView.AtomicMonitor.MonitorCreate(array, s, "");
                    setMonitorProperties(OP_EDIT, atomicmonitor1, s, s1, hashmap1);
                    validateProperties(hashmap1, atomicmonitor1, s6, com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_EDIT_ALL);
                    writeMonitor(OP_EDIT, atomicmonitor1, s, s1);
                } else
                {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_UNASSOCIATED_ID, new java.lang.String[] {
                        s1 + "/" + s
                    });
                }
            } else
            {
                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_BROWSABLE_TYPE_REQUIRED, new java.lang.String[] {
                    s1 + "/" + s
                });
            }
            com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "removeBrowsableCounters"
            }, 0L, exception.getMessage());
        }
    }

    public com.dragonflow.Api.SSStringReturnValue getClassAttribute(java.lang.String s, java.lang.String s1)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = null;
        try
        {
            jgl.HashMap hashmap = getClassAttribs(s);
            ssstringreturnvalue = new SSStringReturnValue((java.lang.String)hashmap.get(s1));
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                exception.getMessage()
            });
        }
        return ssstringreturnvalue;
    }

    private java.util.Enumeration getFilteredMonitorProperties(com.dragonflow.SiteView.AtomicMonitor atomicmonitor, java.util.Vector vector, int i)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.util.ArrayList arraylist = new ArrayList();
        java.util.Enumeration enumeration = null;
        try
        {
            java.lang.String s = atomicmonitor.getClass().getName();
            if(s.indexOf(".") != -1)
            {
                s = s.substring(s.lastIndexOf(".") + 1);
            }
            if(i == FILTER_ALL)
            {
                jgl.Array array = atomicmonitor.getProperties();
                enumeration = array.elements();
            } else
            if(i == FILTER_CONFIGURATION_ADD_ALL)
            {
                enumeration = atomicmonitor.getConfigurationAddProperties(vector, false, 0);
            } else
            if(i == FILTER_CONFIGURATION_ADD_BASIC)
            {
                enumeration = atomicmonitor.getConfigurationAddProperties(vector, false, 1);
            } else
            if(i == FILTER_CONFIGURATION_ADD_ADVANCED)
            {
                enumeration = atomicmonitor.getConfigurationAddProperties(vector, false, 2);
            } else
            if(i == FILTER_CONFIGURATION_EDIT_ALL)
            {
                enumeration = atomicmonitor.getConfigurationEditProperties(vector, false, 0);
            } else
            if(i == FILTER_CONFIGURATION_EDIT_BASIC)
            {
                enumeration = atomicmonitor.getConfigurationEditProperties(vector, false, 1);
            } else
            if(i == FILTER_CONFIGURATION_EDIT_ADVANCED)
            {
                enumeration = atomicmonitor.getConfigurationEditProperties(vector, false, 2);
            } else
            if(i == FILTER_CONFIGURATION_ALL)
            {
                enumeration = atomicmonitor.getConfigurationAllProperties(vector, false);
            } else
            if(i == FILTER_CONFIGURATION_ADD_REQUIRED)
            {
                enumeration = atomicmonitor.getConfigurationRequiredProperties(s);
            } else
            if(i == FILTER_RUNTIME_ALL)
            {
                enumeration = atomicmonitor.getRuntimeProperties(vector, false);
            } else
            if(i == FILTER_RUNTIME_MEASUREMENTS)
            {
                enumeration = atomicmonitor.getMeasurementProperties(vector, false);
            } else
            if(i == FILTER_CONFIGURATION_ADD_ALL_NOT_EMPTY)
            {
                enumeration = atomicmonitor.getConfigurationAddProperties(vector, true, 0);
            } else
            if(i == FILTER_CONFIGURATION_ADD_BASIC_NOT_EMPTY)
            {
                enumeration = atomicmonitor.getConfigurationAddProperties(vector, true, 1);
            } else
            if(i == FILTER_CONFIGURATION_ADD_ADVANCED_NOT_EMPTY)
            {
                enumeration = atomicmonitor.getConfigurationAddProperties(vector, true, 2);
            } else
            if(i == FILTER_CONFIGURATION_EDIT_ALL_NOT_EMPTY)
            {
                enumeration = atomicmonitor.getConfigurationEditProperties(vector, true, 0);
            } else
            if(i == FILTER_CONFIGURATION_EDIT_BASIC_NOT_EMPTY)
            {
                enumeration = atomicmonitor.getConfigurationEditProperties(vector, true, 1);
            } else
            if(i == FILTER_CONFIGURATION_EDIT_ADVANCED_NOT_EMPTY)
            {
                enumeration = atomicmonitor.getConfigurationEditProperties(vector, true, 2);
            } else
            if(i == FILTER_CONFIGURATION_ALL_NOT_EMPTY)
            {
                enumeration = atomicmonitor.getConfigurationAllProperties(vector, true);
            } else
            if(i == PREREQ_OP)
            {
                Object obj = null;
                jgl.Array array1 = new Array();
                jgl.Array array2 = atomicmonitor.getProperties();
                for(int j = 0; j < array2.size(); j++)
                {
                    com.dragonflow.Api.SSPropertyDetails sspropertydetails = getClassPropertyDetails(((com.dragonflow.Properties.StringProperty)array2.at(j)).getName(), s, new com.dragonflow.Api.SSInstanceProperty[0]);
                    if(sspropertydetails.isPrerequisite())
                    {
                        array1.add(array2.at(j));
                    }
                }

                enumeration = array1.elements();
            } else
            if(!$assertionsDisabled)
            {
                throw new AssertionError();
            }
            com.dragonflow.Properties.StringProperty stringproperty;
            for(; enumeration.hasMoreElements(); arraylist.add(stringproperty))
            {
                stringproperty = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
            }

        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "getFilteredMonitorProperties", exception.getMessage()
            });
        }
        java.util.Collections.sort(arraylist, new OrderComparitor());
        return java.util.Collections.enumeration(arraylist);
    }

//    private com.dragonflow.Api.SSStringReturnValue getTopazID(com.dragonflow.SiteView.AtomicMonitor atomicmonitor)
//        throws com.dragonflow.SiteViewException.SiteViewException
//    {
//        com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = null;
//        try
//        {
//            com.dragonflow.TopazIntegration.TopazServerSettings topazserversettings = com.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazServerSettings();
//            if(topazserversettings.isConnected())
//            {
//                ssstringreturnvalue = new SSStringReturnValue((new Integer(com.dragonflow.TopazIntegration.TopazConfigManager.getInstance().getMonitor(atomicmonitor.getUniqueInternalId()).getTopazId())).toString());
//            } else
//            {
//                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_TOPAZ_NOT_CONFIGURED);
//            }
//        }
//        catch(java.lang.Exception exception)
//        {
//            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
//                "APIMonitor", "getTopazID", exception.getMessage()
//            });
//        }
//        return ssstringreturnvalue;
//    }

    private com.dragonflow.Api.SSInstanceProperty[] getPropertiesForMonitorInstance(com.dragonflow.SiteView.AtomicMonitor atomicmonitor, java.lang.String s, int i)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = null;
        try
        {
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = null;
            jgl.Array array = new Array();
            java.util.Vector vector = new Vector();
            java.lang.String s1 = null;
            java.util.Vector vector1 = new Vector();
            boolean flag = true;
            Object obj = null;
            java.util.Enumeration enumeration = null;
            if(s != null && s.length() > 0)
            {
                jgl.Array array1 = new Array();
                com.dragonflow.Properties.StringProperty stringproperty = atomicmonitor.getPropertyObject(s);
                if(stringproperty != null)
                {
                    array1.add(stringproperty);
                    enumeration = array1.elements();
                }
            } else
            {
                enumeration = getFilteredMonitorProperties(atomicmonitor, new Vector(), i);
                enumeration = adjustVirtualProperties(enumeration);
            }
            while (enumeration.hasMoreElements()) {
                boolean flag1 = false;
                boolean flag2 = false;
                boolean flag3 = false;
                com.dragonflow.Properties.StringProperty stringproperty2 = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
                java.lang.String s2 = stringproperty2.getName();
                if(s2 != null)
                {
                    java.lang.String s3 = "";
                    if(s2.equals("_port"))
                    {
                        flag2 = true;
                        s1 = "portOther";
                    } else
                    if(s2.equals("_oid"))
                    {
                        flag2 = true;
                        s1 = "oidOther";
                    } else
                    if(s2.equals("_percentageBase"))
                    {
                        flag2 = true;
                        s1 = "percentageBaseOther";
                    } else
                    if(s2.equals("_scale"))
                    {
                        flag2 = true;
                        s1 = "scaleOther";
                    } else
                    if(s2.equals("_service"))
                    {
                        flag2 = true;
                        s1 = "serviceOther";
                    } else
                    if(s2.equals("_notLogToTopaz") || s2.equals("_logOnlyMonitorData") || s2.equals("_logOnlyThresholdMeas") || s2.equals("_onlyStatusChanges"))
                    {
                        s3 = atomicmonitor.getProperty(stringproperty2);
                        if(s3 != null && s3.length() > 0)
                        {
                            flag3 = true;
                            flag = false;
                        }
                    }
                    if(flag2)
                    {
                        com.dragonflow.HTTP.HTTPRequest httprequest = new HTTPRequest();
                        java.lang.Class class1 = null;
                        class1 = java.lang.Class.forName("com.dragonflow.Page.monitorPage");
                        com.dragonflow.Page.CGI cgi = (com.dragonflow.Page.CGI)class1.newInstance();
                        cgi.initialize(httprequest, null);
                        if(stringproperty2 instanceof com.dragonflow.Properties.ScalarProperty)
                        {
                            java.util.Vector vector3 = atomicmonitor.getScalarValues((com.dragonflow.Properties.ScalarProperty)stringproperty2, httprequest, cgi);
                            java.lang.String as1[] = new java.lang.String[vector3.size() / 2];
                            java.lang.String as2[] = new java.lang.String[vector3.size() / 2];
                            int i2 = 0;
                            int k2 = 0;
                            while (i2 < vector3.size() / 2)
                                {
                                as2[i2] = (java.lang.String)vector3.elementAt(k2);
                                as1[i2] = (java.lang.String)vector3.elementAt(k2 + 1);
                                if(as2[i2].equals(s3))
                                {
                                    flag1 = true;
                                    break;
                                }
                                i2++;
                                k2 += 2;
                            } 
                            if(!flag1)
                            {
                                vector.add(new SSInstanceProperty(s1, s3));
                            } else
                            {
                                vector.add(new SSInstanceProperty(s1, ""));
                            }
                        }
                        array.add(stringproperty2);
                    } else
                    if(flag3)
                    {
                        if(s3 != null && s3.length() > 0)
                        {
                            com.dragonflow.Properties.StringProperty stringproperty4 = new StringProperty("topazLogging", s2);
                            array.add(stringproperty4);
                        }
                    } else
                    {
                        array.add(stringproperty2);
                    }
                }
            } 
            if(flag)
            {
                com.dragonflow.Properties.StringProperty stringproperty1 = new StringProperty("topazLogging", "logEverything");
                array.add(stringproperty1);
            }
            assinstanceproperty1 = processInstanceThresholdProperties(i, atomicmonitor);
            java.util.Vector vector2 = new Vector();
            fixDisableAlertingParamsOut(atomicmonitor, vector2);
            fixDisableGroupOrMonitorParamsOut(atomicmonitor, vector2);
            int j = 0;
            com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = null;
            try
            {
                if(i == com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL || i == com.dragonflow.Api.APISiteView.FILTER_ALL)
                {
                    j = 1;
//                    ssstringreturnvalue = getTopazID(atomicmonitor);
                }
            }
            catch(java.lang.Exception exception1)
            {
                j = 0;
            }
            assinstanceproperty = new com.dragonflow.Api.SSInstanceProperty[j + array.size() + assinstanceproperty1.length + vector.size() + vector1.size() + vector2.size()];
            int k = 0;
            for(java.util.Enumeration enumeration1 = array.elements(); enumeration1.hasMoreElements();)
            {
                com.dragonflow.Properties.StringProperty stringproperty3 = (com.dragonflow.Properties.StringProperty)enumeration1.nextElement();
                java.lang.String s4 = GetPropertyLabel(stringproperty3, true);
                java.lang.Object obj1;
                if(stringproperty3.isMultiLine)
                {
                    java.util.Enumeration enumeration2 = atomicmonitor.getMultipleValues(stringproperty3);
                    java.lang.String s7 = "";
                    if(enumeration2.hasMoreElements())
                    {
                        while(enumeration2.hasMoreElements()) 
                        {
                            s7 = s7 + (java.lang.String)enumeration2.nextElement() + "\r\n";
                        }
                    } else
                    {
                        java.lang.String s8 = atomicmonitor.getProperty(stringproperty3);
                        java.lang.String as3[] = com.dragonflow.Utils.TextUtils.split(s8, ",");
                        for(int j2 = 0; j2 < as3.length; j2++)
                        {
                            s7 = s7 + as3[j2] + "\r\n";
                        }

                    }
                    obj1 = s7;
                } else
                if((stringproperty3 instanceof com.dragonflow.Properties.ScalarProperty) && ((com.dragonflow.Properties.ScalarProperty)stringproperty3).multiple)
                {
                    java.lang.String s5 = atomicmonitor.getProperty(stringproperty3);
                    java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s5, ",");
                    for(int l1 = 0; l1 < as.length; l1++)
                    {
                        as[l1] = as[l1].trim();
                    }

                    obj1 = as;
                } else
                {
                    java.lang.String s6 = atomicmonitor.getProperty(stringproperty3);
                    if(stringproperty3.isPassword)
                    {
                        s6 = com.dragonflow.Utils.TextUtils.obscure(s6);
                    }
                    obj1 = s6;
                }
                if(stringproperty3.getName().equals("_perfmonMsmtsProp"))
                {
                    obj1 = com.dragonflow.SiteView.monitorUtils.transformMgFormatToPerfmonMeasurements((java.lang.String)obj1);
                }
                assinstanceproperty[k] = new SSInstanceProperty(stringproperty3.getName(), s4, obj1);
                k++;
            }

            for(int l = 0; l < vector.size(); l++)
            {
                com.dragonflow.Api.SSInstanceProperty ssinstanceproperty = (com.dragonflow.Api.SSInstanceProperty)vector.elementAt(l);
                assinstanceproperty[k + l] = ssinstanceproperty;
                if(ssinstanceproperty.getValue() != "")
                {
                    setTheCorrespondingSiteViewVarToZero(ssinstanceproperty, assinstanceproperty);
                }
            }

            k += vector.size();
            for(int i1 = 0; i1 < vector2.size(); i1++)
            {
                assinstanceproperty[k++] = (com.dragonflow.Api.SSInstanceProperty)vector2.elementAt(i1);
            }

            for(int j1 = 0; j1 < vector1.size(); j1++)
            {
                assinstanceproperty[k + j1] = (com.dragonflow.Api.SSInstanceProperty)vector1.elementAt(j1);
            }

            k += vector1.size();
            for(int k1 = 0; k1 < assinstanceproperty1.length; k1++)
            {
                assinstanceproperty[k + k1] = assinstanceproperty1[k1];
            }

            k += assinstanceproperty1.length;
            if(j > 0)
            {
//                assinstanceproperty[k] = new SSInstanceProperty("topazMonitorID", com.dragonflow.SiteView.TopazInfo.getTopazName() + " Monitor ID", ssstringreturnvalue.getValue());
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "getPropertiesForMonitorInstance", exception.getMessage()
            });
        }
        return assinstanceproperty;
    }

    private void setTheCorrespondingSiteViewVarToZero(com.dragonflow.Api.SSInstanceProperty ssinstanceproperty, com.dragonflow.Api.SSInstanceProperty assinstanceproperty[])
    {
        java.lang.String s = ssinstanceproperty.getName();
        int i = s.indexOf("Other");
        if(i != -1)
        {
            java.lang.String s1 = "_" + s.substring(0, i);
            int j = 0;
            do
            {
                if(j >= assinstanceproperty.length)
                {
                    break;
                }
                com.dragonflow.Api.SSInstanceProperty ssinstanceproperty1 = assinstanceproperty[j];
                if(ssinstanceproperty1.getName().equals(s1))
                {
                    assinstanceproperty[j] = new SSInstanceProperty(assinstanceproperty[j].getName(), assinstanceproperty[j].getLabel(), "0");
                    break;
                }
                j++;
            } while(true);
        } else
        {
            com.dragonflow.Log.LogManager.log("Error", "Error finding the word 'Other' in the otherProperty: " + s + " -- unable to indicate to Flipper that an 'Other' property is in use.");
        }
    }

    private com.dragonflow.Api.SSInstanceProperty[] processInstanceThresholdProperties(int i, com.dragonflow.SiteView.AtomicMonitor atomicmonitor)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[0];
        try
        {
            if(i == FILTER_CONFIGURATION_ADD_ALL || i == FILTER_CONFIGURATION_ADD_BASIC || i == FILTER_CONFIGURATION_ADD_ADVANCED || i == FILTER_CONFIGURATION_EDIT_ALL || i == FILTER_CONFIGURATION_EDIT_BASIC || i == FILTER_CONFIGURATION_EDIT_ADVANCED || i == FILTER_ALL || i == FILTER_CONFIGURATION_ALL || i == FILTER_CONFIGURATION_ALL && i == FILTER_CONFIGURATION_ALL_NOT_EMPTY)
            {
                java.util.Vector vector = getInstanceThresholds(atomicmonitor, i);
                assinstanceproperty = new com.dragonflow.Api.SSInstanceProperty[vector.size()];
                for(int j = 0; j < vector.size(); j++)
                {
                    assinstanceproperty[j] = (com.dragonflow.Api.SSInstanceProperty)vector.elementAt(j);
                }

            }
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "processInstanceThresholdProperties", exception.getMessage()
            });
        }
        return assinstanceproperty;
    }

    private java.util.Vector createThresholdProperties(int i, jgl.Array array, com.dragonflow.SiteView.SiteViewObject siteviewobject, java.util.HashMap hashmap)
    {
        java.util.Vector vector = new Vector();
        if(i == com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ALL || i == com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_BASIC || i == com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ADVANCED || i == com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_EDIT_ALL || i == com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_EDIT_BASIC || i == com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_EDIT_ADVANCED || i == com.dragonflow.Api.APISiteView.FILTER_ALL || i == com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL)
        {
            java.util.Enumeration enumeration = array.elements();
            jgl.Array array1 = new Array();
            while (enumeration.hasMoreElements()) {
                com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
                if(stringproperty.isThreshold())
                {
                    array1.add(stringproperty);
                }
            } 
            if(i != com.dragonflow.Api.APISiteView.FILTER_ALL)
            {
                for(int j = 0; j < array1.size(); j++)
                {
                    array.remove(array1.at(j));
                }

            }
            vector = getThresholds(array1, siteviewobject, hashmap);
        }
        return vector;
    }

    protected java.util.Vector getThresholds(jgl.Array array, com.dragonflow.SiteView.SiteViewObject siteviewobject, java.util.HashMap hashmap)
    {
        int i = getThresholdNum((com.dragonflow.SiteView.Monitor)siteviewobject);
        java.util.Vector vector = new Vector();
        if(siteviewobject instanceof com.dragonflow.SiteView.Monitor)
        {
            jgl.Array array1 = new Array();
            jgl.Array array2 = new Array();
            for(int j = 0; j < array.size(); j++)
            {
                com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)array.at(j);
                if(stringproperty != com.dragonflow.SiteView.Monitor.pNumStdDev && stringproperty != com.dragonflow.SiteView.Monitor.pNumPercent || siteviewobject.hasValue(com.dragonflow.SiteView.Monitor.pBaselineDate))
                {
                    array1.add(stringproperty.getName());
                    array2.add(stringproperty.getLabel());
                }
            }

            getThresholdCounters(hashmap, array1, i);
            int k = getThresholdNum((com.dragonflow.SiteView.Monitor)siteviewobject);
            java.lang.String as[] = {
                "error", "warning", "good"
            };
            java.lang.String as1[] = {
                "condition", "comparison", "parameter"
            };
            for(int l = 0; l < as.length; l++)
            {
                for(int i1 = 0; i1 < k; i1++)
                {
                    java.lang.String s = "";
                    java.lang.String s2 = "";
                    java.lang.String s3 = "";
                    for(int j1 = 0; j1 < as1.length; j1++)
                    {
                        java.lang.String s4 = as1[j1];
                        java.lang.String s10 = "THRESHOLD";
                        java.lang.String s5 = as[l] + "-" + s4 + i1;
                        java.lang.String s6 = as[l] + " " + s4;
                        java.lang.String s7 = as[l] + " threshold " + s4;
                        java.lang.String s8 = "SCALAR";
                        java.lang.String s11 = "";
                        java.lang.String as2[];
                        java.lang.String as3[];
                        java.lang.String s9;
                        if(s4.equals("condition"))
                        {
                            java.lang.String as4[] = processClassifiers((com.dragonflow.SiteView.Monitor)siteviewobject, as[l]);
                            if(as4[i1] == null)
                            {
                                as4[i1] = "";
                            }
                            as2 = new java.lang.String[array1.size()];
                            as3 = new java.lang.String[array2.size()];
                            java.lang.String s12 = as4[i1];
                            if(s12.indexOf(" ") > 0)
                            {
                                int k1 = s12.indexOf(" ");
                                int i2 = s12.indexOf(" ", k1 + 1);
                                java.lang.String s1 = s12.substring(0, k1);
                                s2 = s12.substring(k1 + 1, i2);
                                s3 = s12.substring(i2 + 1);
                                s9 = s1;
                            } else
                            {
                                s9 = s12;
                            }
                            for(int l1 = 0; l1 < array1.size(); l1++)
                            {
                                if(array1.at(l1) != null)
                                {
                                    as2[l1] = (java.lang.String)array1.at(l1);
                                    as3[l1] = (java.lang.String)array2.at(l1);
                                }
                            }

                            s6 = as[l] + " if:";
                        } else
                        if(s4.equals("comparison"))
                        {
                            as2 = createComparisonList();
                            as3 = createComparisonList();
                            s9 = s2;
                        } else
                        {
                            as2 = null;
                            as3 = null;
                            s8 = "TEXT";
                            s9 = s3;
                        }
                        vector.add(new SSPropertyDetails(s5, s8, s7, s6, true, false, s9, as2, as3, s10, false, false, 0, s11, true, false, siteviewobject.getProperty(s5)));
                    }

                }

            }

        }
        return vector;
    }

    private java.lang.String[] createComparisonList()
    {
        java.lang.String as[] = new java.lang.String[8];
        as[0] = ">=";
        as[1] = ">";
        as[2] = "==";
        as[3] = "!=";
        as[4] = "<";
        as[5] = "<=";
        as[6] = "contains";
        as[7] = "!contains";
        return as;
    }

    private void getThresholdCounters(java.util.HashMap hashmap, jgl.Array array, int i)
    {
        if(hashmap.containsKey("_counters") || hashmap.containsKey("_counter"))
        {
            int j = 0;
            int l;
            if(array.contains("value0"))
            {
                l = j;
            } else
            {
                l = j + 1;
            }
            java.lang.String s = (java.lang.String)hashmap.get("_counters");
            if(s == null)
            {
                s = (java.lang.String)hashmap.get("_counter");
            }
            if(s != null)
            {
                int j1 = 0;
                int k1 = s.indexOf(",");
                do
                {
                    if(j >= i)
                    {
                        break;
                    }
                    if(k1 >= 0)
                    {
                        array.replace("value" + l, s.substring(j1, k1));
                    } else
                    {
                        array.replace("value" + l, s.substring(j1));
                        break;
                    }
                    j1 = k1 + 1;
                    k1 = s.indexOf(",", j1);
                    l++;
                    j++;
                } while(true);
            }
        } else
        if(hashmap.containsKey("_browseName1"))
        {
            for(int k = 0; k < i; k++)
            {
                int i1 = k + 1;
                java.lang.String s1 = (java.lang.String)hashmap.get("_browseName" + i1);
                if(s1 != null)
                {
                    array.replace("value" + i1, s1);
                }
            }

        }
    }

    private com.dragonflow.Api.SSPropertyDetails getThreshold(java.lang.String s, jgl.Array array, com.dragonflow.SiteView.Monitor monitor)
    {
        int i = getThresholdNum(monitor);
        java.lang.String s2 = s.substring(0, s.indexOf("-"));
        java.lang.String as[] = new java.lang.String[0];
        java.lang.String as1[] = new java.lang.String[0];
        java.lang.String s6 = "";
        java.lang.String s7 = "THRESHOLD";
        java.lang.String s8 = "";
        java.lang.String as2[] = processClassifiers(monitor, s2);
        for(int j = 0; j < as2.length; j++)
        {
            if(as2[j] == null)
            {
                as2[j] = "";
            }
        }

        java.lang.String s9 = as2[0];
        java.lang.String s10 = "";
        java.lang.String s12 = "";
        if(s9.indexOf(" ") > 0)
        {
            int k = s9.indexOf(" ");
            int i1 = s9.indexOf(" ", k + 1);
            java.lang.String s11 = s9.substring(0, k);
            s12 = s9.substring(k + 1, i1);
            s6 = s11;
        } else
        {
            s6 = s9;
        }
        java.lang.String s5 = "SCALAR";
        java.lang.String s1;
        if(s.indexOf("condition") >= 0)
        {
            s1 = "condition";
            java.util.Vector vector = new Vector();
            java.util.Vector vector1 = new Vector();
            vector.add(s9 + " (default)");
            vector1.add("default");
            for(int k1 = 0; k1 < array.size(); k1++)
            {
                com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)array.at(k1);
                java.lang.String s13 = monitor.GetPropertyLabel(stringproperty, true);
                java.lang.String s14 = stringproperty.getName();
                if(s13 != null && s13.length() > 0)
                {
                    vector.add(s13);
                    vector1.add(s14);
                }
            }

            as = new java.lang.String[vector.size()];
            for(int l1 = 0; l1 < vector.size(); l1++)
            {
                as[l1] = (java.lang.String)vector.elementAt(l1);
            }

            as1 = new java.lang.String[vector.size()];
            for(int i2 = 0; i2 < vector1.size(); i2++)
            {
                as1[i2] = (java.lang.String)vector1.elementAt(i2);
            }

            s5 = "TEXT";
        } else
        if(s.indexOf("comparison") >= 0)
        {
            s1 = "comparison";
            as = createComparisonList();
            s6 = s12;
        } else
        {
            s1 = "parameter";
            as = null;
            as1 = null;
        }
        java.lang.String s3 = s2 + " " + s1;
        java.lang.String s4 = s2 + " threshold " + s1;
        int l = s.indexOf(s1) + s1.length();
        int j1 = (new Integer(s.substring(l))).intValue();
        com.dragonflow.Api.SSPropertyDetails sspropertydetails;
        if(j1 < i)
        {
            sspropertydetails = new SSPropertyDetails(s, s5, s4, s3, true, false, s6, as, as1, s7, false, false, 0, s8, true, false, monitor.getProperty(s));
        } else
        {
            sspropertydetails = null;
        }
        return sspropertydetails;
    }

    private java.lang.String[] processClassifiers(com.dragonflow.SiteView.Monitor monitor, java.lang.String s)
    {
        java.util.Enumeration enumeration = monitor.getClassifiers();
        int i = getThresholdNum(monitor);
        java.lang.String as[] = new java.lang.String[i];
        for(int j = 0; j < i; j++)
        {
            as[j] = null;
        }

        java.lang.String s1 = "SetProperty category " + s;
        int k = 0;
        while (enumeration.hasMoreElements()) {
            com.dragonflow.SiteView.Rule rule = (com.dragonflow.SiteView.Rule)enumeration.nextElement();
            if(k < i && s1.equals(rule.getProperty(com.dragonflow.SiteView.Rule.pAction)))
            {
                if(rule.getOwner() == monitor)
                {
                    as[k] = rule.getProperty(com.dragonflow.SiteView.Rule.pExpression);
                }
                k++;
            }
        }
        java.lang.String as1[] = new java.lang.String[i];
        as1[0] = "default";
        return as[0] != null ? as : as1;
    }

    protected java.util.Vector getInstanceThresholds(com.dragonflow.SiteView.Monitor monitor, int i)
    {
        java.util.Vector vector = new Vector();
        int j = getThresholdNum(monitor);
        java.util.HashMap hashmap = new java.util.HashMap();
        java.util.Enumeration enumeration = monitor.getProperties().elements();
        while (enumeration.hasMoreElements()) {
            com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
            if(stringproperty.isThreshold())
            {
                java.lang.String s = monitor.GetPropertyLabel(stringproperty, true);
                if(s.length() != 0)
                {
                    hashmap.put(stringproperty.getName(), monitor.getProperty(stringproperty));
                }
            }
        } 
        java.lang.String as[] = {
            "error", "warning", "good"
        };
        for(int k = 0; k < as.length; k++)
        {
            java.lang.String as1[] = processClassifiers(monitor, as[k]);
            for(int l = 0; l < j; l++)
            {
                java.lang.String as2[] = new java.lang.String[0];
                if(as1[l] != null)
                {
                    as2 = com.dragonflow.Utils.TextUtils.tokenize(as1[l]);
                }
                java.lang.String s1 = as[k] + "-condition" + l;
                java.lang.String s2 = "";
                if(as2.length > 0)
                {
                    java.lang.String s3 = as2[0];
                    s2 = s3;
                } else
                if(i == com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL_NOT_EMPTY)
                {
                    continue;
                }
                java.lang.String s4 = as[k] + "-comparison" + l;
                java.lang.String s5 = "";
                if(as2.length > 1)
                {
                    s5 = as2[1];
                }
                java.lang.String s6 = as[k] + "-parameter" + l;
                java.lang.String s7 = "";
                if(as2.length > 2)
                {
                    s7 = as2[2];
                }
                vector.add(new SSInstanceProperty(s1, s2));
                vector.add(new SSInstanceProperty(s4, s5));
                vector.add(new SSInstanceProperty(s6, s7));
            }

        }

        return vector;
    }

    private void validateCustomProperties(jgl.HashMap hashmap, com.dragonflow.SiteView.AtomicMonitor atomicmonitor, jgl.HashMap hashmap1)
    {
        jgl.HashMap hashmap2 = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        java.util.Enumeration enumeration = hashmap2.values("_monitorEditCustom");
        while (enumeration.hasMoreElements()) {
            java.lang.String s = "";
            java.lang.String s1 = (java.lang.String)enumeration.nextElement();
            java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s1, "|");
            java.lang.String s2 = as[0];
            if(s2.length() > 0)
            {
                if(!s2.startsWith("_"))
                {
                    s2 = "_" + s2;
                }
                if(!shouldPrintProperty(atomicmonitor, s2) || hashmap.get(s2) == null)
                {
                    continue;
                }
                java.lang.String s3 = "";
                if(as.length > 1 && as.length > 3)
                {
                    s3 = as[3];
                }
                if(s3.equals("") || !atomicmonitor.getProperty(s2).equals(""))
                {
                    s = (java.lang.String)hashmap.get(s2);
                } else
                {
                    s = s3;
                }
            }
            hashmap.remove(s2);
            hashmap1.add(s2, s);
        } 
    }

    private jgl.HashMap validateProperties(jgl.HashMap hashmap, com.dragonflow.SiteView.AtomicMonitor atomicmonitor, java.lang.String s, int i)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        jgl.HashMap hashmap1 = new HashMap(true);
        try
        {
            java.util.Enumeration enumeration = getFilteredMonitorProperties(atomicmonitor, new Vector(), i);
            jgl.HashMap hashmap2 = new HashMap();
            com.dragonflow.HTTP.HTTPRequest httprequest = new HTTPRequest();
            if(enumeration != null)
            {
                hashmap1.put("_class", s);
                if(hashmap.get("_class") != null)
                {
                    hashmap.remove("_class");
                }
                hashmap.remove("_logOnlyMonitorData");
                hashmap.remove("_logOnlyThresholdMeas");
                hashmap.remove("_onlyStatusChanges");
                hashmap.remove(com.dragonflow.SiteView.Monitor.pDisabledDescription.getName());
                hashmap.remove(com.dragonflow.SiteView.Monitor.pDisabled.getName());
                hashmap.remove(com.dragonflow.SiteView.Monitor.pTimedDisable.getName());
                hashmap.remove(com.dragonflow.SiteView.Monitor.pAlertDisabled.getName());
                while (enumeration.hasMoreElements()) {
                    com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
                    java.lang.String s1 = stringproperty.getName();
                    java.util.Enumeration enumeration2 = hashmap.values(s1);
                    hashmap.remove(s1);
                    if(!stringproperty.isThreshold())
                    {
                        while(enumeration2.hasMoreElements()) 
                        {
                            java.lang.Object obj = enumeration2.nextElement();
                            if(obj == null || obj.equals(""))
                            {
                                obj = stringproperty.getDefault();
                            }
                            if(obj != null && (stringproperty instanceof com.dragonflow.Properties.BooleanProperty) && obj.equals("0"))
                            {
                                obj = "";
                            }
                            if(obj instanceof java.lang.String)
                            {
                                obj = atomicmonitor.verify(stringproperty, (java.lang.String)obj, httprequest, hashmap2);
                            }
                            hashmap1.add(s1, obj);
                        }
                    }
                }
                validateCustomProperties(hashmap, atomicmonitor, hashmap1);
                if(hashmap2.size() == 0)
                {
                    atomicmonitor.verifyAll(hashmap2);
                }
            }
            if(hashmap2.size() > 0)
            {
                java.util.HashMap hashmap3 = new java.util.HashMap();
                com.dragonflow.Properties.StringProperty stringproperty1;
                for(java.util.Enumeration enumeration1 = hashmap2.keys(); enumeration1.hasMoreElements(); hashmap3.put(stringproperty1.getName(), hashmap2.get(stringproperty1)))
                {
                    stringproperty1 = (com.dragonflow.Properties.StringProperty)enumeration1.nextElement();
                }

                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_VERIFICATION_ERRORS, hashmap3);
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                exception.getMessage()
            });
        }
        return hashmap1;
    }

    private jgl.HashMap getClassAttribs(java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.SiteView.AtomicMonitor atomicmonitor = instantiateMonitor(s);
        if(com.dragonflow.Api.APIMonitor.isValidObject(atomicmonitor.getClass().getName(), "Monitor"))
        {
            return atomicmonitor.getClassProperties();
        } else
        {
            return null;
        }
    }

    private com.dragonflow.Api.SSPropertyDetails getClassProperty(com.dragonflow.Properties.StringProperty stringproperty, com.dragonflow.SiteView.AtomicMonitor atomicmonitor, java.util.HashMap hashmap, boolean flag)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        boolean flag1 = false;
        java.lang.String s = "";
        boolean flag2 = false;
        java.lang.String s3 = "";
        java.lang.String s4 = "TEXT";
        java.lang.String as[] = null;
        java.lang.String as1[] = null;
        java.lang.String s5 = "";
        try
        {
            if(atomicmonitor instanceof com.dragonflow.SiteView.BrowsableMonitor)
            {
                jgl.Array array = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getConnectionProperties();
                for(int i = 0; i < array.size(); i++)
                {
                    java.lang.String s1 = ((com.dragonflow.Properties.StringProperty)array.at(i)).getName();
                    atomicmonitor.unsetProperty(s1);
                    if(hashmap.get(s1) == null)
                    {
                        continue;
                    }
                    java.lang.String s8 = (java.lang.String)hashmap.get(s1);
                    com.dragonflow.Properties.StringProperty stringproperty1 = atomicmonitor.getPropertyObject(s1);
                    if((stringproperty1 instanceof com.dragonflow.Properties.BooleanProperty) && s8.equals("0"))
                    {
                        s8 = "";
                    }
                    atomicmonitor.setProperty(s1, s8);
                }

                if(hashmap.get("reloadCounters") != null)
                {
                    flag2 = (new Boolean((java.lang.String)hashmap.get("reloadCounters"))).booleanValue();
                }
            }
            if((atomicmonitor instanceof com.dragonflow.SiteView.IServerPropMonitor) && stringproperty.getName() != null)
            {
                if((atomicmonitor instanceof com.dragonflow.SiteView.NTCounterBase) && stringproperty.getName() != null && stringproperty.getName().equals("counterObject") && hashmap.get("counterObject") == null)
                {
                    flag1 = true;
                }
                if(stringproperty.getName().equals("_machine") && hashmap.get("_machine") == null)
                {
                    flag1 = true;
                }
                if(stringproperty.getName().equals("_pdhMachine") && hashmap.get("_pdhMachine") == null)
                {
                    flag1 = true;
                }
                if(stringproperty.getName().equals("_server") && hashmap.get("_server") == null)
                {
                    flag1 = true;
                }
            } else
            if(((atomicmonitor instanceof com.dragonflow.SiteView.BrowsableMonitor) || (atomicmonitor instanceof com.dragonflow.SiteView.BrowsableSNMPBase)) && stringproperty.getName() != null)
            {
                jgl.Array array1 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getConnectionProperties();
                int j = 0;
                do
                {
                    if(j >= array1.size())
                    {
                        break;
                    }
                    java.lang.String s2 = ((com.dragonflow.Properties.StringProperty)array1.at(j)).getName();
                    if(stringproperty.getName().equals(s2) && hashmap.get(s2) == null)
                    {
                        flag1 = true;
                        break;
                    }
                    j++;
                } while(true);
            }
            com.dragonflow.HTTP.HTTPRequest httprequest = new HTTPRequest();
            httprequest.setUser(account);
            if(stringproperty.isPassword)
            {
                s4 = "PASSWORD";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.ServerProperty)
            {
                s4 = "SERVER";
                java.util.Vector vector = returnMachineScalarValues(atomicmonitor);
                as = new java.lang.String[vector.size() / 2];
                as1 = new java.lang.String[vector.size() / 2];
                int k = 0;
                for(int l = 0; k < vector.size(); l++)
                {
                    as1[l] = (java.lang.String)vector.elementAt(k);
                    as[l] = (java.lang.String)vector.elementAt(k + 1);
                    k += 2;
                }

                s5 = "LIST";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.ScheduleProperty)
            {
                s4 = "SCHEDULE";
                com.dragonflow.Properties.ScheduleProperty scheduleproperty = (com.dragonflow.Properties.ScheduleProperty)stringproperty;
                java.lang.Class class1 = java.lang.Class.forName("com.dragonflow.Page.monitorPage");
                com.dragonflow.Page.CGI cgi = (com.dragonflow.Page.CGI)class1.newInstance();
                cgi.initialize(httprequest, null);
                java.util.Vector vector1 = atomicmonitor.getScalarValues(scheduleproperty, httprequest, cgi);
                as = new java.lang.String[vector1.size() / 2];
                as1 = new java.lang.String[vector1.size() / 2];
                int i2 = 0;
                for(int k2 = 0; i2 < vector1.size() / 2; k2 += 2)
                {
                    as1[i2] = (java.lang.String)vector1.elementAt(k2);
                    as[i2] = (java.lang.String)vector1.elementAt(k2 + 1);
                    i2++;
                }

                s5 = "LIST";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.ScalarProperty)
            {
                s4 = "SCALAR";
                com.dragonflow.Properties.ScalarProperty scalarproperty = (com.dragonflow.Properties.ScalarProperty)stringproperty;
                java.lang.Class class2 = java.lang.Class.forName("com.dragonflow.Page.monitorPage");
                com.dragonflow.Page.CGI cgi1 = (com.dragonflow.Page.CGI)class2.newInstance();
                cgi1.initialize(httprequest, null);
                if(hashmap.get("_machine") != null)
                {
                    jgl.HashMap hashmap3 = com.dragonflow.Utils.jglUtils.toJgl(hashmap);
                    processMachineName((java.lang.String)hashmap.get("_machine"), hashmap3);
                    hashmap = com.dragonflow.Utils.jglUtils.fromJgl(hashmap3);
                }
                if(hashmap.get("_machine") != null)
                {
                    httprequest.setValue("_machine", (java.lang.String)hashmap.get("_machine"));
                    atomicmonitor.setProperty("_machine", (java.lang.String)hashmap.get("_machine"));
                } else
                {
                    httprequest.setValue("_machine", "");
                    atomicmonitor.unsetProperty("_machine");
                }
                java.util.Vector vector2 = null;
                if(stringproperty.getName().equals("_machine"))
                {
                    vector2 = returnMachineScalarValues(atomicmonitor);
                } else
                {
                    vector2 = atomicmonitor.getScalarValues(scalarproperty, httprequest, cgi1);
                }
                as = new java.lang.String[vector2.size() / 2];
                as1 = new java.lang.String[vector2.size() / 2];
                int j2 = 0;
                for(int l2 = 0; j2 < vector2.size() / 2; l2 += 2)
                {
                    as1[j2] = (java.lang.String)vector2.elementAt(l2);
                    as[j2] = (java.lang.String)vector2.elementAt(l2 + 1);
                    j2++;
                }

                s5 = "LIST";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.RateProperty)
            {
                s4 = "RATE";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.PercentProperty)
            {
                s4 = "PERCENT";
                s3 = ((com.dragonflow.Properties.PercentProperty)stringproperty).getUnits();
            } else
            if(stringproperty instanceof com.dragonflow.Properties.FrequencyProperty)
            {
                s4 = "FREQUENCY";
                s3 = "seconds";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.FileProperty)
            {
                s4 = "FILE";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.BrowsableProperty)
            {
                s4 = "BROWSABLE";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.BooleanProperty)
            {
                s4 = "BOOLEAN";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.NumericProperty)
            {
                s4 = "NUMERIC";
                s3 = ((com.dragonflow.Properties.NumericProperty)stringproperty).getUnits();
            } else
            if(stringproperty instanceof com.dragonflow.Properties.StringProperty)
            {
                s4 = "TEXT";
                if((atomicmonitor instanceof com.dragonflow.SiteView.NTCounterBase) && stringproperty.getName() != null && stringproperty.getName().equals("availableObjects"))
                {
                    java.lang.String s6 = (java.lang.String)hashmap.get("_machine");
                    if(s6 != null)
                    {
                        atomicmonitor.setProperty("_machine", s6);
                        jgl.Array array7 = ((com.dragonflow.SiteView.NTCounterBase)atomicmonitor).getAvailableCounters();
                        jgl.HashMap hashmap2 = new HashMap();
                        for(int j1 = 0; j1 < array7.size(); j1++)
                        {
                            if(((com.dragonflow.Utils.PerfCounter)array7.at(j1)).object != null)
                            {
                                hashmap2.put(((com.dragonflow.Utils.PerfCounter)array7.at(j1)).object, "");
                            }
                        }

                        int k1 = 0;
                        java.util.Enumeration enumeration = hashmap2.keys();
                        as = new java.lang.String[hashmap2.size()];
                        while(enumeration.hasMoreElements()) 
                        {
                            as[k1++] = (java.lang.String)enumeration.nextElement();
                        }
                    }
                } else
                if((atomicmonitor instanceof com.dragonflow.SiteView.NTCounterBase) && stringproperty.getName() != null && stringproperty.getName().equals("availableCounters"))
                {
                    jgl.Array array2 = new Array(0);
                    java.lang.StringBuffer stringbuffer2 = new StringBuffer();
                    jgl.Array array8 = new Array();
                    java.lang.String s13 = (java.lang.String)hashmap.get("_machine");
                    if(s13 != null)
                    {
                        atomicmonitor.setProperty("_machine", s13);
                        java.lang.String s16 = (java.lang.String)hashmap.get("counterObject");
                        if(s16 != null)
                        {
                            array8.add(s16);
                            jgl.Array array3 = com.dragonflow.SiteView.NTCounterBase.getPerfCounters(s13, array8, stringbuffer2, "");
                            jgl.HashMap hashmap4 = new HashMap();
                            for(int j3 = 0; j3 < array3.size(); j3++)
                            {
                                if(((com.dragonflow.Utils.PerfCounter)array3.at(j3)).counterName != null)
                                {
                                    hashmap4.put(((com.dragonflow.Utils.PerfCounter)array3.at(j3)).counterName, "");
                                }
                            }

                            int k3 = 0;
                            java.util.Enumeration enumeration1 = hashmap4.keys();
                            as = new java.lang.String[hashmap4.size()];
                            while(enumeration1.hasMoreElements()) 
                            {
                                as[k3++] = (java.lang.String)enumeration1.nextElement();
                            }
                            hashmap4 = new HashMap();
                            for(int j5 = 0; j5 < array3.size(); j5++)
                            {
                                if(((com.dragonflow.Utils.PerfCounter)array3.at(j5)).counterID != null)
                                {
                                    hashmap4.put(((com.dragonflow.Utils.PerfCounter)array3.at(j5)).counterID, "");
                                }
                            }

                            k3 = 0;
                            enumeration1 = hashmap4.keys();
                            as1 = new java.lang.String[hashmap4.size()];
                            while(enumeration1.hasMoreElements()) 
                            {
                                as1[k3++] = (java.lang.String)enumeration1.nextElement();
                            }
                        }
                    }
                } else
                if((atomicmonitor instanceof com.dragonflow.SiteView.NTCounterBase) && stringproperty.getName() != null && stringproperty.getName().equals("availableInstances"))
                {
                    jgl.Array array4 = new Array(0);
                    java.lang.StringBuffer stringbuffer3 = new StringBuffer();
                    jgl.Array array9 = new Array();
                    java.lang.String s14 = (java.lang.String)hashmap.get("_machine");
                    if(s14 != null)
                    {
                        atomicmonitor.setProperty("_machine", s14);
                        java.lang.String s17 = (java.lang.String)hashmap.get("counterObject");
                        if(s17 != null)
                        {
                            array9.add(s17);
                            jgl.Array array5 = com.dragonflow.SiteView.NTCounterBase.getPerfCounters(s14, array9, stringbuffer3, "");
                            jgl.HashMap hashmap5 = new HashMap();
                            for(int l3 = 0; l3 < array5.size(); l3++)
                            {
                                if(((com.dragonflow.Utils.PerfCounter)array5.at(l3)).instance != null)
                                {
                                    hashmap5.put(((com.dragonflow.Utils.PerfCounter)array5.at(l3)).instance, "");
                                }
                            }

                            int i4 = 0;
                            java.util.Enumeration enumeration2 = hashmap5.keys();
                            as = new java.lang.String[hashmap5.size()];
                            while(enumeration2.hasMoreElements()) 
                            {
                                as[i4++] = (java.lang.String)enumeration2.nextElement();
                            }
                        }
                    }
                } else
                if((atomicmonitor instanceof com.dragonflow.SiteView.ISelectableCounter) && stringproperty.getName() != null && stringproperty.getName().equals("defaultCounters"))
                {
                    java.lang.String s7 = ((com.dragonflow.SiteView.ISelectableCounter)atomicmonitor).getDefaultCounters();
                    as = com.dragonflow.Utils.TextUtils.split(s7, ",");
                } else
                if((atomicmonitor instanceof com.dragonflow.SiteView.BrowsableMonitor) && stringproperty.getName() != null && stringproperty.getName().equals("availableCounters"))
                {
                    java.lang.StringBuffer stringbuffer = new StringBuffer("");
                    java.lang.String s9 = "";
                    boolean flag3 = false;
                    if(((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).isUsingCountersCache())
                    {
                        if(!flag2)
                        {
                            s9 = com.dragonflow.SiteView.BrowsableCache.getXmlFile(com.dragonflow.SiteView.BrowsableCache.getXmlFileName(atomicmonitor));
                            if(s9 == null || s9.length() == 0)
                            {
                                flag3 = true;
                            }
//							else
//                            if(atomicmonitor instanceof com.dragonflow.StandardMonitor.SiebelCmdLineMonitor)
//                            {
//                                s9 = ((com.dragonflow.StandardMonitor.SiebelCmdLineMonitor)atomicmonitor).postProcessBrowseTree(s9);
//                            }
                        } else
                        {
                            flag3 = true;
                        }
                        if(flag3)
                        {
                            com.dragonflow.SiteView.BrowsableCache.deleteXmlFile(com.dragonflow.SiteView.BrowsableCache.getXmlFileName(atomicmonitor));
                            s9 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getBrowseData(stringbuffer).trim();
                            com.dragonflow.SiteView.BrowsableCache.saveXmlFile(com.dragonflow.SiteView.BrowsableCache.getXmlFileName(atomicmonitor), s9);
                        }
                    } else
                    {
                        s9 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getBrowseData(stringbuffer).trim();
                    }
                    if(stringbuffer.length() == 0)
                    {
                        org.w3c.dom.Document document = createDocumentFromString(s9);
                        java.util.Vector vector3 = new Vector();
                        java.util.Vector vector4 = new Vector();
                        org.w3c.dom.NodeList nodelist = document.getDocumentElement().getChildNodes();
                        int l4 = nodelist.getLength();
                        for(int k5 = 0; k5 < l4; k5++)
                        {
                            findCounters(atomicmonitor, vector4, vector3, nodelist.item(k5), 1);
                        }

                        as = new java.lang.String[vector4.size()];
                        for(int l5 = 0; l5 < vector4.size(); l5++)
                        {
                            as[l5] = (java.lang.String)vector4.elementAt(l5);
                        }

                        as1 = new java.lang.String[vector3.size()];
                        for(int i6 = 0; i6 < vector3.size(); i6++)
                        {
                            as1[i6] = (java.lang.String)vector3.elementAt(i6);
                        }

                    } else
                    {
                        if(flag)
                        {
                            throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_COUNTER_EXCEPTION, new java.lang.String[] {
                                stringbuffer.toString()
                            });
                        }
                        as = new java.lang.String[1];
                        as[0] = "unable to retrieve counters";
                        as1 = new java.lang.String[1];
                        as1[0] = stringbuffer.toString();
                    }
                } else
                if((atomicmonitor instanceof com.dragonflow.SiteView.BrowsableMonitor) && stringproperty.getName() != null && stringproperty.getName().equals("availableCountersHierarchical"))
                {
                    if(atomicmonitor.isDispatcher())
                    {
                        com.dragonflow.SiteView.SiteViewGroup.currentSiteView().checkDispatcherForStart(atomicmonitor);
                    }
                    java.lang.StringBuffer stringbuffer1 = new StringBuffer("");
                    java.lang.String s10 = "";
                    boolean flag4 = false;
                    if(((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).isUsingCountersCache())
                    {
                        if(!flag2)
                        {
                            s10 = com.dragonflow.SiteView.BrowsableCache.getXmlFile(com.dragonflow.SiteView.BrowsableCache.getXmlFileName(atomicmonitor));
                            if(s10 == null || s10.length() == 0)
                            {
                                flag4 = true;
                            }
//							else
//                            if(atomicmonitor instanceof com.dragonflow.StandardMonitor.SiebelCmdLineMonitor)
//                            {
//                                s10 = ((com.dragonflow.StandardMonitor.SiebelCmdLineMonitor)atomicmonitor).postProcessBrowseTree(s10);
//                            }
                        } else
                        {
                            flag4 = true;
                        }
                        if(flag4)
                        {
                            com.dragonflow.SiteView.BrowsableCache.deleteXmlFile(com.dragonflow.SiteView.BrowsableCache.getXmlFileName(atomicmonitor));
                            s10 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getBrowseData(stringbuffer1).trim();
                            com.dragonflow.SiteView.BrowsableCache.saveXmlFile(com.dragonflow.SiteView.BrowsableCache.getXmlFileName(atomicmonitor), s10);
                        }
                    } else
                    {
                        s10 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getBrowseData(stringbuffer1).trim();
                    }
                    if(stringbuffer1.length() == 0)
                    {
                        org.w3c.dom.Document document1 = createDocumentFromString(s10);
                        s10 = getIDs(document1, (com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor);
                        as = new java.lang.String[1];
                        as[0] = s10;
                        as1 = new java.lang.String[1];
                        as1[0] = "not applicable";
                    } else
                    {
                        if(flag)
                        {
                            throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_COUNTER_EXCEPTION, new java.lang.String[] {
                                stringbuffer1.toString()
                            });
                        }
                        as = new java.lang.String[1];
                        as[0] = "unable to retrieve counters";
                        as1 = new java.lang.String[1];
                        as1[0] = stringbuffer1.toString();
                    }
                } else
                if((atomicmonitor instanceof com.dragonflow.SiteView.ApplicationBase) && stringproperty.getName() != null && stringproperty.getName().equals("availableCounters"))
                {
                    jgl.Array array6 = ((com.dragonflow.SiteView.ApplicationBase)atomicmonitor).getAvailableCounters();
                    if(array6 != null)
                    {
                        as = new java.lang.String[array6.size()];
                        as1 = new java.lang.String[array6.size()];
                        java.util.HashMap hashmap1 = new java.util.HashMap();
                        int i1 = 0;
                        int l1 = 0;
                        for(; i1 < array6.size(); i1++)
                        {
                            java.lang.String s18 = (java.lang.String)array6.at(i1);
                            if(s18 != null)
                            {
                                as[l1] = s18;
                                as1[l1] = s18;
                                l1++;
                                hashmap1.put(s18, "");
                            }
                        }

                    }
                } else
                if((atomicmonitor instanceof com.dragonflow.StandardMonitor.PDHMonitor) && stringproperty.getName() != null)
                {
                    java.lang.Object aobj[] = new java.lang.Object[1];
                    java.lang.StringBuffer stringbuffer4 = new StringBuffer();
                    if(stringproperty.getName().equals("availableObjects") || stringproperty.getName().equals("availableCounters") || stringproperty.getName().equals("availableInstances"))
                    {
                        java.lang.String s11 = (java.lang.String)hashmap.get("_pdhMachine");
                        if(s11 != null)
                        {
                            atomicmonitor.setProperty("_pdhMachine", s11);
                            boolean flag5 = false;
                            if(stringproperty.getName().equals("availableObjects"))
                            {
                                boolean flag6 = ((com.dragonflow.StandardMonitor.PDHMonitor)atomicmonitor).getAvailableObjects(aobj, stringbuffer4);
                                if(flag6)
                                {
                                    com.dragonflow.Properties.StringProperty astringproperty[] = (com.dragonflow.Properties.StringProperty[])aobj[0];
                                    as = new java.lang.String[astringproperty.length];
                                    as1 = new java.lang.String[astringproperty.length];
                                    for(int i3 = 0; i3 < astringproperty.length; i3++)
                                    {
                                        as[i3] = astringproperty[i3].getName();
                                        as1[i3] = astringproperty[i3].getName();
                                    }

                                } else
                                {
                                    throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_PERFMON_EXCEPTION, new java.lang.String[] {
                                        stringbuffer4.toString()
                                    });
                                }
                            } else
                            if(stringproperty.getName().equals("availableCounters"))
                            {
                                java.lang.String s19 = (java.lang.String)hashmap.get("counterObject");
                                if(s19 != null)
                                {
                                    boolean flag7 = ((com.dragonflow.StandardMonitor.PDHMonitor)atomicmonitor).getAvailableCounters(s19, aobj, stringbuffer4);
                                    if(flag7)
                                    {
                                        com.dragonflow.Properties.StringProperty astringproperty1[] = (com.dragonflow.Properties.StringProperty[])aobj[0];
                                        as = new java.lang.String[astringproperty1.length];
                                        as1 = new java.lang.String[astringproperty1.length];
                                        for(int j4 = 0; j4 < astringproperty1.length; j4++)
                                        {
                                            as[j4] = astringproperty1[j4].getName();
                                            as1[j4] = astringproperty1[j4].getName();
                                        }

                                    } else
                                    {
                                        throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_PERFMON_EXCEPTION, new java.lang.String[] {
                                            stringbuffer4.toString()
                                        });
                                    }
                                }
                            } else
                            if(stringproperty.getName().equals("availableInstances"))
                            {
                                java.lang.String s20 = (java.lang.String)hashmap.get("counterObject");
                                if(s20 != null)
                                {
                                    boolean flag8 = ((com.dragonflow.StandardMonitor.PDHMonitor)atomicmonitor).getAvailableInstances(s20, aobj, stringbuffer4);
                                    if(flag8)
                                    {
                                        com.dragonflow.Properties.StringProperty astringproperty2[] = (com.dragonflow.Properties.StringProperty[])aobj[0];
                                        as = new java.lang.String[astringproperty2.length];
                                        as1 = new java.lang.String[astringproperty2.length];
                                        for(int k4 = 0; k4 < astringproperty2.length; k4++)
                                        {
                                            as[k4] = astringproperty2[k4].getName();
                                            as1[k4] = astringproperty2[k4].getName();
                                        }

                                    } else
                                    {
                                        throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_PERFMON_EXCEPTION, new java.lang.String[] {
                                            stringbuffer4.toString()
                                        });
                                    }
                                }
                            }
                        }
                    }
                } 
//				else if((atomicmonitor instanceof com.dragonflow.StandardMonitor.MQStatusMonitor) && stringproperty.getName() != null)
//                {
//                    java.lang.Object aobj1[] = new java.lang.Object[1];
//                    java.lang.StringBuffer stringbuffer5 = new StringBuffer();
//                    if(stringproperty.getName().equals("availableObjects") || stringproperty.getName().equals("availableCounters") || stringproperty.getName().equals("availableInstances"))
//                    {
//                        java.lang.String s12 = (java.lang.String)hashmap.get("_serverHostName");
//                        java.lang.String s15 = (java.lang.String)hashmap.get("_serverPortNumber");
//                        java.lang.String s21 = (java.lang.String)hashmap.get("_channel");
//                        if(s12 != null && s15 != null && s21 != null)
//                        {
//                            atomicmonitor.setProperty("_serverHostName", s12);
//                            atomicmonitor.setProperty("_serverPortNumber", s15);
//                            atomicmonitor.setProperty("_channel", s21);
//                            boolean flag9 = false;
//                            if(stringproperty.getName().equals("availableObjects"))
//                            {
//                                boolean flag10 = false;//((com.dragonflow.StandardMonitor.MQStatusMonitor)atomicmonitor).getAvailableObjects(aobj1, stringbuffer5);
//                                if(flag10)
//                                {
//                                    com.dragonflow.Properties.StringProperty astringproperty3[] = (com.dragonflow.Properties.StringProperty[])aobj1[0];
//                                    as = new java.lang.String[astringproperty3.length];
//                                    as1 = new java.lang.String[astringproperty3.length];
//                                    for(int i5 = 0; i5 < astringproperty3.length; i5++)
//                                    {
//                                        as[i5] = astringproperty3[i5].getName();
//                                        as1[i5] = astringproperty3[i5].getName();
//                                    }
//
//                                } else
//                                {
//                                    throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_PERFMON_EXCEPTION, new java.lang.String[] {
//                                        stringbuffer5.toString()
//                                    });
//                                }
//                            } else
//                            if(stringproperty.getName().equals("availableCounters"))
//                            {
//                                java.lang.String s22 = (java.lang.String)hashmap.get("counterObject");
//                                if(s22 != null)
//                                {
//                                    boolean flag11 = false;//((com.dragonflow.StandardMonitor.MQStatusMonitor)atomicmonitor).getAvailableCounters(s22, aobj1, stringbuffer5);
//                                    if(flag11)
//                                    {
//                                        com.dragonflow.Properties.StringProperty astringproperty4[] = (com.dragonflow.Properties.StringProperty[])aobj1[0];
//                                        as = new java.lang.String[astringproperty4.length];
//                                        as1 = new java.lang.String[astringproperty4.length];
//                                        for(int j6 = 0; j6 < astringproperty4.length; j6++)
//                                        {
//                                            as[j6] = astringproperty4[j6].getName();
//                                            as1[j6] = astringproperty4[j6].getName();
//                                        }
//
//                                    } else
//                                    {
//                                        throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_PERFMON_EXCEPTION, new java.lang.String[] {
//                                            stringbuffer5.toString()
//                                        });
//                                    }
//                                }
//                            } else
//                            if(stringproperty.getName().equals("availableInstances"))
//                            {
//                                java.lang.String s23 = (java.lang.String)hashmap.get("counterObject");
//                                if(s23 != null)
//                                {
//                                    boolean flag12 = false;//((com.dragonflow.StandardMonitor.MQStatusMonitor)atomicmonitor).getAvailableInstances(s23, aobj1, stringbuffer5);
//                                    if(flag12)
//                                    {
//                                        com.dragonflow.Properties.StringProperty astringproperty5[] = (com.dragonflow.Properties.StringProperty[])aobj1[0];
//                                        as = new java.lang.String[astringproperty5.length];
//                                        as1 = new java.lang.String[astringproperty5.length];
//                                        for(int k6 = 0; k6 < astringproperty5.length; k6++)
//                                        {
//                                            as[k6] = astringproperty5[k6].getName();
//                                            as1[k6] = astringproperty5[k6].getName();
//                                        }
//
//                                    } else
//                                    {
//                                        throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_PERFMON_EXCEPTION, new java.lang.String[] {
//                                            stringbuffer5.toString()
//                                        });
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "getClassProperty", exception.getMessage()
            });
        }
        return new SSPropertyDetails(stringproperty.getName(), s4, stringproperty.getDescription(), stringproperty.getLabel(), stringproperty.isEditable, stringproperty.isMultivalued, stringproperty.getDefault(), as, as1, s5, isRequiredProperty(stringproperty.getName()), flag1, stringproperty.getOrder(), s3, stringproperty.isAdvanced, stringproperty.isPassword, atomicmonitor.getProperty(stringproperty.getName()));
    }

    private java.util.Vector removeDupMachines(java.util.Vector vector)
    {
        java.util.Vector vector1 = new Vector();
        java.util.HashSet hashset = new HashSet();
        if(vector.size() > 1)
        {
            vector1.add(vector.elementAt(0));
            vector1.add(vector.elementAt(1));
            hashset.add(((java.lang.String)vector.elementAt(0)).toLowerCase());
        }
        for(int i = vector.size() - 2; i > 0; i -= 2)
        {
            java.lang.String s = ((java.lang.String)vector.elementAt(i)).toLowerCase();
            if(!hashset.contains(s))
            {
                hashset.add(s);
                vector1.add(vector.elementAt(i));
                vector1.add(vector.elementAt(i + 1));
            }
        }

        return vector1;
    }

    private java.util.Vector returnMachineScalarValues(com.dragonflow.SiteView.AtomicMonitor atomicmonitor)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.util.Vector vector = null;
        try
        {
            boolean flag = true;
            boolean flag1 = false;
            boolean flag2 = true;
            if(atomicmonitor instanceof com.dragonflow.StandardMonitor.LogMonitor)
            {
                flag = false;
            }
            if(atomicmonitor instanceof com.dragonflow.StandardMonitor.ScriptMonitor)
            {
                flag = false;
                flag1 = true;
            }
            if((atomicmonitor instanceof com.dragonflow.StandardMonitor.NTCounterMonitor) || (atomicmonitor instanceof com.dragonflow.StandardMonitor.NTEventLogMonitor) || (atomicmonitor instanceof com.dragonflow.SiteView.NTCounterBase))
            {
                flag2 = false;
            }
            if(flag)
            {
                vector = getLocalServers();
                vector = addServers(vector, "_remoteNTMachine", false);
            } else
            {
                vector = new Vector();
                try
                {
                    java.net.InetAddress inetaddress = java.net.InetAddress.getLocalHost();
                    java.lang.String s = inetaddress.getHostName();
                    if(com.dragonflow.SiteView.Platform.isWindows())
                    {
                        s = "\\\\" + s;
                    }
                    vector.addElement(s);
                    vector.addElement(s);
                }
                catch(java.net.UnknownHostException unknownhostexception)
                {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_NO_IP, new java.lang.String[] {
                        "localhost"
                    });
                }
                if(flag1)
                {
                    vector = addServers(vector, "_remoteNTMachine", true);
                }
            }
            if(flag2)
            {
                vector = addServers(vector, "_remoteMachine", false);
            }
            vector = removeDupMachines(vector);
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "getClassProperty", exception.getMessage()
            });
        }
        return vector;
    }

    private org.w3c.dom.Document createDocumentFromString(java.lang.String s)
        throws javax.xml.parsers.ParserConfigurationException, org.xml.sax.SAXException, java.io.IOException
    {
        javax.xml.parsers.DocumentBuilderFactory documentbuilderfactory = javax.xml.parsers.DocumentBuilderFactory.newInstance();
        documentbuilderfactory.setValidating(false);
        javax.xml.parsers.DocumentBuilder documentbuilder = documentbuilderfactory.newDocumentBuilder();
        org.w3c.dom.Document document = documentbuilder.parse(new InputSource(new StringReader(s)));
        return document;
    }

    protected static boolean isValidObject(java.lang.String s, java.lang.String s1)
    {
        boolean flag = false;
        if(s.endsWith(s1))
        {
            try
            {
                java.lang.Class class1 = java.lang.Class.forName(s);
                if(com.dragonflow.SiteView.SiteViewObject.loadableClass(class1))
                {
                    flag = true;
                }
            }
            catch(java.lang.Exception exception)
            {
                com.dragonflow.Log.LogManager.log("error", "APIMonitor: failed to load class: " + s + ", Exception: " + exception.getMessage());
            }
            catch(java.lang.NoClassDefFoundError noclassdeffounderror)
            {
                com.dragonflow.Log.LogManager.log("error", "APIMonitor: NoClassDefFoundError, failed to load class: " + s + ", Exception: " + noclassdeffounderror.getMessage());
            }
        }
        return flag;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @return
     */
    protected static boolean isAddableMonitor(java.lang.String s)
    {
        try {
        Object obj = null;
        java.lang.Object obj1;
        java.lang.Class class1 = java.lang.Class.forName(s);
        obj1 = com.dragonflow.SiteView.SiteViewObject.getClassPropertyByObject(class1.getName(), "addable");
        if(obj1 != null)
        {
            return obj1.equals("true");
        }
        return true;
        }
        catch (java.lang.ClassNotFoundException classnotfoundexception) {
        return false;
        }
    }

    private java.lang.String getIDs(org.w3c.dom.Document document, com.dragonflow.SiteView.BrowsableMonitor browsablemonitor)
    {
        if(document.getDocumentElement() != null)
        {
            org.w3c.dom.NodeList nodelist = document.getElementsByTagName("counter");
            int i = nodelist.getLength();
            for(int j = 0; j < i; j++)
            {
                org.w3c.dom.Node node = nodelist.item(j);
                java.lang.String s = node.getNodeName();
                if(s.toLowerCase().equals("counter"))
                {
                    java.lang.String s1 = browsablemonitor.setBrowseID(getNodeIdNames(node));
                    ((org.w3c.dom.Element)node).setAttribute("id", s1);
                }
            }

        } else
        {
            com.dragonflow.Log.LogManager.log("error", "Document Element is null");
        }
        java.io.StringWriter stringwriter = new StringWriter();
        try
        {
            javax.xml.transform.Transformer transformer = javax.xml.transform.TransformerFactory.newInstance().newTransformer();
            transformer.setOutputProperty("omit-xml-declaration", "yes");
            transformer.transform(new DOMSource(document.getDocumentElement()), new StreamResult(stringwriter));
        }
        catch(javax.xml.transform.TransformerException transformerexception)
        {
            com.dragonflow.Log.LogManager.log("Error", "TransformationException while serializing XML Document in APIMonitor.getIDs: " + transformerexception.getMessage());
        }
        return stringwriter.toString();
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param atomicmonitor
     * @param s1
     * @param s2
     * @param hashmap
     * @throws com.dragonflow.SiteViewException.SiteViewException
     */
    private void setMonitorProperties(java.lang.String s, com.dragonflow.SiteView.AtomicMonitor atomicmonitor, java.lang.String s1, java.lang.String s2, jgl.HashMap hashmap)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try {
        com.dragonflow.SiteView.User user;
        com.dragonflow.HTTP.HTTPRequest httprequest;
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup;
        int j;
        java.lang.String s5;
        jgl.HashMap hashmap1;
        java.util.Enumeration enumeration;
        user = com.dragonflow.SiteView.User.getUserForAccount("administrator");
        httprequest = new HTTPRequest();
        httprequest.setUser("administrator");
        java.lang.String s3 = user.getPermission("_monitorType", (java.lang.String)atomicmonitor.getClassProperty("class"));
        if(s3.equals("optional"))
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_LICENSE_TYPE, new java.lang.String[] {
                (java.lang.String)atomicmonitor.getClassProperty("class")
            });
        }
        siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        if(s.equals(OP_ADD))
        {
            s2 = com.dragonflow.Utils.I18N.toDefaultEncoding(s2);
            com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)com.dragonflow.SiteView.SiteViewGroup.currentSiteView().getElementByID(s2);
            atomicmonitor.setOwner(monitor);
            if(com.dragonflow.Utils.TextUtils.toInt(s3) > 0)
            {
                int k = monitor.countMonitorsOfClass(hashmap.get("class") == null ? "" : (java.lang.String)hashmap.get("class"), user.getValue("_account"));
                if(k >= com.dragonflow.Utils.TextUtils.toInt(s3))
                {
                    throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_LICENSE_LIMIT, new java.lang.String[] {
                        (new Integer(k)).toString()
                    });
                }
            }
            int l = com.dragonflow.Utils.TextUtils.toInt(user.getPermission("_maximumMonitors"));
            if(l > 0)
            {
                int i1 = monitor.countMonitors(user.getValue("_account"));
                if(i1 >= l)
                {
                    throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_LICENSE_LIMIT, new java.lang.String[] {
                        (new Integer(i1)).toString()
                    });
                }
            }
        }
        if(s.equals(OP_ADD) || s.equals(OP_TEMP))
        {
            if(com.dragonflow.Utils.LUtils.wouldExceedLimit(atomicmonitor))
            {
                int i = com.dragonflow.Utils.LUtils.getLicensedPoints();
                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_LICENSE_LIMIT, new java.lang.String[] {
                    (new Integer(i)).toString()
                });
            }
            if(!com.dragonflow.Utils.LUtils.isMonitorTypeAllowed(atomicmonitor))
            {
                java.lang.String s4 = (java.lang.String)atomicmonitor.getClassProperty("title");
                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_LICENSE_TYPE, new java.lang.String[] {
                    s4
                });
            }
        }
        j = com.dragonflow.Utils.TextUtils.toInt(user.getPermission("_minimumFrequency"));
        s5 = atomicmonitor.defaultTitle();
        hashmap1 = new HashMap();
        java.lang.String s6 = com.dragonflow.SiteView.ServerMonitor.pMachineName.getName();
        if(hashmap.get(s6) != null)
        {
            java.lang.String s7 = (java.lang.String)hashmap.get(s6);
            if(!s7.startsWith("\\\\") && !s7.startsWith("remote:") && !s7.equals(""))
            {
                s7 = "remote:" + s7;
                hashmap.put(s6, s7);
            }
        }
        if(hashmap.get("_counters") != null)
        {
            java.lang.String s8 = (java.lang.String)hashmap.get("_counters");
            java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s8, ",");
            int l1 = atomicmonitor.getMaxCounters();
            if(as.length > l1)
            {
                jgl.HashMap hashmap3 = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
                hashmap3.put("_ApplicationMonitorMaxCounters", (new Integer(as.length)).toString());
                com.dragonflow.SiteView.MasterConfig.saveMasterConfig(hashmap3);
                ((com.dragonflow.SiteView.ISelectableCounter)atomicmonitor).increaseCounters(as.length);
            }
            ((com.dragonflow.SiteView.ISelectableCounter)atomicmonitor).setCountersPropertyValue(atomicmonitor, s8);
        }
        if(atomicmonitor instanceof com.dragonflow.StandardMonitor.URLSequenceMonitor)
        {
            jgl.HashMap hashmap2 = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
            int j1 = com.dragonflow.Utils.TextUtils.toInt(com.dragonflow.Utils.TextUtils.getValue(hashmap2, "_URLSequenceMonitorSteps"));
            if(j1 == 0)
            {
                j1 = 20;
            }
            int i2 = j1;
            int j2 = j1 + 1;
            while (true)
            {
                java.lang.String s15 = (java.lang.String)hashmap.get("_referenceType" + j2);
                if(s15 == null)
                {
                    break;
                }
                i2++;
                j2++;
            } 
            if(i2 > j1)
            {
                hashmap2.put("_URLSequenceMonitorSteps", (new Integer(i2)).toString());
                com.dragonflow.SiteView.MasterConfig.saveMasterConfig(hashmap2);
                com.dragonflow.StandardMonitor.URLSequenceMonitor.allocateStepProperties(i2);
            }
        }
        if(atomicmonitor instanceof com.dragonflow.SiteView.BrowsableMonitor)
        {
            jgl.Array array = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getConnectionProperties();
            for(int k1 = 0; k1 < array.size(); k1++)
            {
                java.lang.String s10 = ((com.dragonflow.Properties.StringProperty)array.at(k1)).getName();
                java.lang.String s12 = (java.lang.String)hashmap.get(s10);
                if(s12 != null)
                {
                    atomicmonitor.setProperty(s10, s12);
                }
            }

            java.lang.String s9 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getBrowseName();
            java.lang.String s11 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getBrowseID();
            boolean flag = hashmap.get(s9 + 1) != null;
            if(flag)
            {
                int k2 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getMaxCounters();
                int i3;
                for(i3 = 1; hashmap.get(s9 + i3) != null; i3++) { }
                if(--i3 > k2)
                {
                    java.util.List list = com.dragonflow.SiteView.BrowsableBase.createNewBrowsableCounters(k2, i3);
                    for(java.util.Iterator iterator = list.iterator(); iterator.hasNext(); com.dragonflow.Properties.PropertiedObject.addPropertyToPropertyMap(atomicmonitor.getClass().getName(), (com.dragonflow.Properties.StringProperty)iterator.next())) { }
                    ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).setMaxCounters(i3);
                    k2 = i3;
                }
                for(int j4 = 1; j4 <= k2; j4++)
                {
                    java.lang.String s24 = (java.lang.String)hashmap.get(s9 + j4);
                    java.lang.String s28 = (java.lang.String)hashmap.get(s11 + j4);
                    atomicmonitor.unsetProperty(s9 + j4);
                    atomicmonitor.unsetProperty(s11 + j4);
                    atomicmonitor.unsetProperty(com.dragonflow.SiteView.BrowsableBase.PROPERTY_NAME_COUNTER_VALUE + j4);
                    if(s24 != null)
                    {
                        if(!$assertionsDisabled && !atomicmonitor.hasProperty(s9 + j4))
                        {
                            throw new AssertionError();
                        }
                        atomicmonitor.setProperty(s9 + j4, s24);
                        jgl.Array array3 = new Array();
                        java.lang.String as3[] = s24.split("/");
                        for(int i5 = as3.length - 1; i5 >= 0; i5--)
                        {
                            array3.add(as3[i5]);
                        }

                        hashmap.put(s9 + j4, ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).setBrowseName(array3));
                    }
                    if(s28 == null)
                    {
                        continue;
                    }
                    if(!$assertionsDisabled && !atomicmonitor.hasProperty(s11 + j4))
                    {
                        throw new AssertionError();
                    }
                    atomicmonitor.setProperty(s11 + j4, s28);
                    int k4 = s28.indexOf(" ");
                    if(k4 < 0)
                    {
                        continue;
                    }
                    java.lang.String s34 = s28.substring(0, k4);
                    if(!com.dragonflow.Utils.TextUtils.isNumber(s34))
                    {
                        jgl.Array array4 = new Array();
                        array4.add(s28);
                        hashmap.put(s11 + j4, ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).setBrowseID(array4));
                    }
                }

            }
            int l2 = 1;
            java.lang.String s19 = (java.lang.String)hashmap.get("uniqueID");
            if(s19 != null && s19.length() > 0)
            {
                jgl.HashMap hashmap4 = com.dragonflow.SiteView.BrowsableCache.getCache(s19, true, false);
                jgl.HashMap hashmap5 = (jgl.HashMap)hashmap4.get("selectNames");
                jgl.HashMap hashmap6 = (jgl.HashMap)hashmap4.get("selectIDs");
                for(java.util.Enumeration enumeration4 = hashmap5.keys(); enumeration4.hasMoreElements();)
                {
                    java.lang.String s35 = (java.lang.String)enumeration4.nextElement();
                    java.lang.String s36 = (java.lang.String)hashmap6.get(s35);
                    atomicmonitor.setProperty(s9 + l2, s35);
                    if(s36 != null)
                    {
                        atomicmonitor.setProperty(s11 + l2, s36);
                    }
                    l2++;
                }

            }
        }
        if(s.equals(OP_ADD) || s.equals(OP_TEMP))
        {
            siteviewgroup.checkDispatcherForStart(atomicmonitor);
        }
        
        jgl.Array array1 = atomicmonitor.getProperties();
        array1 = com.dragonflow.Properties.StringProperty.sortByOrder(array1);
        enumeration = array1.elements();
        com.dragonflow.Properties.StringProperty stringproperty;
        java.lang.String s14;
        while (enumeration.hasMoreElements())
            {
            stringproperty = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
        if (s.equals(OP_ADD) || s.equals(OP_TEMP) || hashmap.get(stringproperty.getName()) != null && atomicmonitor.propertyInTemplate(stringproperty) && stringproperty.isConfigurable) {
        if(stringproperty.isMultiLine)
        {
            java.lang.String s13 = "";
            if(stringproperty.getName().equals("_counters"))
            {
                s13 = atomicmonitor.getProperty(stringproperty);
            } else
            {
                s13 = (java.lang.String)hashmap.get(stringproperty.getName());
                if(s13 == null)
                {
                    s13 = atomicmonitor.getProperty(stringproperty);
                }
            }
            java.lang.String as1[] = com.dragonflow.Utils.TextUtils.split(s13, "\r\n");
            atomicmonitor.unsetProperty(stringproperty);
            int j3 = 0;
            while(j3 < as1.length) 
            {
                java.lang.String s21 = as1[j3];
                atomicmonitor.addProperty(stringproperty, s21);
                j3++;
            }
            continue; 
        }
        if((stringproperty instanceof com.dragonflow.Properties.ScalarProperty) && ((com.dragonflow.Properties.ScalarProperty)stringproperty).multiple && stringproperty.getName().indexOf("Remote") == -1)
        {
            java.lang.Object obj1 = hashmap.get(stringproperty.getName());
            if(obj1 instanceof java.lang.String[])
            {
                java.lang.String as2[] = (java.lang.String[])hashmap.get(stringproperty.getName());
                atomicmonitor.unsetProperty(stringproperty);
                int k3 = 0;
                while(k3 < as2.length) 
                {
                    java.lang.String s22 = as2[k3];
                    atomicmonitor.addProperty(stringproperty, s22);
                    k3++;
                }
            } else
            if(obj1 instanceof java.lang.String)
            {
                java.lang.String s16 = (java.lang.String)hashmap.get(stringproperty.getName());
                atomicmonitor.unsetProperty(stringproperty);
                atomicmonitor.addProperty(stringproperty, s16);
            }
            continue; /* Loop/switch isn't completed */
        }
        s14 = (java.lang.String)hashmap.get(stringproperty.getName());
        if(s14 == null)
        {
            s14 = atomicmonitor.getProperty(stringproperty);
        }
        if(!s.equals(OP_TEMP))
        {
            java.lang.String s17 = stringproperty.getName();
            if((s17.equals("_getImages") || s17.equals("_getFrames")) && s14.equals("on") && httprequest.isSiteSeerAccount())
            {
                int l3 = com.dragonflow.Utils.TextUtils.toInt(user.getPermission("_maximumFAndIMonitors"));
                java.lang.String s23 = httprequest.getValue("operation");
                java.lang.String s25 = s1;
                java.lang.String s29 = httprequest.getValue("class");
                if(s29.equals("") && !s25.equals(""))
                {
                    java.lang.String s32 = s2 + com.dragonflow.SiteView.SiteViewObject.ID_SEPARATOR + s25;
                    s32 = com.dragonflow.Utils.I18N.toDefaultEncoding(s32);
                    com.dragonflow.SiteView.Monitor monitor1 = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(s32);
                    s29 = monitor1.getProperty("_class");
                }
                if(s29.startsWith("URLRemote"))
                {
                    java.lang.String s33 = com.dragonflow.Utils.I18N.toDefaultEncoding(user.getValue("_account"));
                    com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s33);
                    java.lang.String s37 = monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pGroupID);
                    jgl.Array array5 = monitorgroup.getMonitorsOfClass("", s37);
                    java.util.Enumeration enumeration5 = array5.elements();
                    int j5 = 0;
                    while (enumeration5.hasMoreElements())
                        {
                        com.dragonflow.SiteView.Monitor monitor2 = (com.dragonflow.SiteView.Monitor)enumeration5.nextElement();
                        if(!s23.equals("Edit"))
                        {
//                            if(((monitor2 instanceof com.dragonflow.StandardMonitor.URLRemoteMonitor) || (monitor2 instanceof com.dragonflow.StandardMonitor.URLRemoteSequenceMonitor)) && (monitor2.getProperty("_getImages").equals("on") || monitor2.getProperty("_getFrames").equals("on")))
//                            {
//                                j5++;
//                            }
//                            continue;
                        }
                        if(monitor2.getProperty("id").equals(s1) && (monitor2.getProperty("_getImages").equals("on") || monitor2.getProperty("_getFrames").equals("on")))
                        {
                            break;
                        }
//                        if(((monitor2 instanceof com.dragonflow.StandardMonitor.URLRemoteMonitor) || (monitor2 instanceof com.dragonflow.StandardMonitor.URLRemoteSequenceMonitor)) && (monitor2.getProperty("_getImages").equals("on") || monitor2.getProperty("_getFrames").equals("on")))
//                        {
//                            j5++;
//                        }
                    }
                    
                    if(j5 >= l3)
                    {
                        return;
                    }
                }
            }
        }
        
        java.lang.String s18 = s14;
        if(j > 0 && (stringproperty instanceof com.dragonflow.Properties.FrequencyProperty))
        {
            int i4 = com.dragonflow.Utils.TextUtils.toInt(s18);
            if(i4 != 0 && i4 < j)
            {
                hashmap1.put(stringproperty, "For this account, monitors must run at intervals of " + com.dragonflow.Utils.TextUtils.secondsToString(j) + " or more.");
            }
        }
        if(stringproperty == com.dragonflow.SiteView.Monitor.pName)
        {
            if(s18.equals(s5))
            {
                atomicmonitor.setProperty(stringproperty, "");
            } else
            {
                atomicmonitor.setProperty(stringproperty, s18);
            }
        } else
        if((stringproperty instanceof com.dragonflow.Properties.ScalarProperty) && ((com.dragonflow.Properties.ScalarProperty)stringproperty).multiple)
        {
            jgl.Array array2 = new Array();
            if(!com.dragonflow.SiteView.Platform.isStandardAccount(user.getValue("_account")) && stringproperty.getName().equals("_location"))
            {
                java.util.Enumeration enumeration1 = atomicmonitor.getMultipleValues(stringproperty);
                java.lang.String s26 = "";
                java.lang.String s30 = "";
                while (enumeration1.hasMoreElements())
                    {
                    java.lang.String s27 = (java.lang.String)enumeration1.nextElement();
                    java.lang.String s31 = (java.lang.String)com.dragonflow.Utils.HTTPUtils.locationMap.get(s27);
                    if(s31 != null && !s31.equals(""))
                    {
                        int l4 = com.dragonflow.Utils.HTTPUtils.getDisplayOrder(s31);
                        if(l4 < 0)
                        {
                            array2.add(s27);
                        }
                    }
                } 
            }
            java.util.Enumeration enumeration2 = httprequest.getValues(stringproperty.getName());
            atomicmonitor.unsetProperty(stringproperty);
            while (enumeration2.hasMoreElements()) {
                atomicmonitor.addProperty(stringproperty, (java.lang.String)enumeration2.nextElement());
            }
            if(array2 != null && array2.size() > 0)
            {
                java.util.Enumeration enumeration3 = array2.elements();
                while(enumeration3.hasMoreElements()) 
                {
                    atomicmonitor.addProperty(stringproperty, (java.lang.String)enumeration3.nextElement());
                }
            }
        } else
        {
            java.lang.String s20 = atomicmonitor.getProperty(stringproperty);
            atomicmonitor.setProperty(stringproperty, s18);
            if(stringproperty.getName().equals("_disabled"))
            {
                if(s20.length() <= 0 && s18.length() > 0)
                {
                    siteviewgroup.notifyMonitorDeletion(atomicmonitor);
                } else
                if(s20.length() > 0 && s18.length() <= 0)
                {
                    siteviewgroup.checkDispatcherForStart(atomicmonitor);
                }
            }
        }
        }
            }

        saveThresholds(atomicmonitor, hashmap);
        saveCustomProperties(atomicmonitor, hashmap);
        if(atomicmonitor.getProperty(com.dragonflow.SiteView.Monitor.pName).length() == 0)
        {
            atomicmonitor.setProperty(com.dragonflow.SiteView.Monitor.pName, atomicmonitor.defaultTitle());
        }
    }
    catch (SiteViewException e) {
        e.fillInStackTrace();
        throw e;
    }
    catch (Exception e) {
        throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
            "APIMonitor", "setMonitorProperties", e.getMessage()
        });
    }
    }

    private void writeMonitor(java.lang.String s, com.dragonflow.SiteView.AtomicMonitor atomicmonitor, java.lang.String s1, java.lang.String s2)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s3 = s1;
        try
        {
            com.dragonflow.HTTP.HTTPRequest httprequest = new HTTPRequest();
            int i = saveOrdering(httprequest);
            jgl.HashMap hashmap = atomicmonitor.getValuesTable();
            jgl.Array array = null;
            if(!$assertionsDisabled && s.equals(OP_TEMP))
            {
                throw new AssertionError();
            }
            array = ReadGroupFrames(s2);
            if(s.equals(OP_ADD))
            {
                jgl.HashMap hashmap1 = (jgl.HashMap)array.at(0);
                s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_nextID");
                if(s3.length() == 0)
                {
                    s3 = "1";
                }
                hashmap.remove(com.dragonflow.SiteView.Monitor.pID);
                hashmap.remove("_id");
                hashmap.put("_id", s3);
                hashmap.put("_class", atomicmonitor.getClassProperty("class"));
                array.insert(i, hashmap);
                java.lang.String s4 = com.dragonflow.Utils.TextUtils.increment(s3);
                hashmap1.put("_nextID", s4);
            } else
            {
                int j = com.dragonflow.SiteView.monitorUtils.findMonitorIndex(array, s1);
                java.lang.Object obj = array.at(j);
                array.remove(obj);
                array.insert(j, hashmap);
            }
//            if(com.dragonflow.SiteView.TopazConfigurator.configInTopazAndRegistered())
//            {
//                jgl.Array array1 = new Array();
//                array1.add(atomicmonitor);
//                if(s.equals(OP_EDIT) && atomicmonitor.isDispatcher())
//                {
//                    com.dragonflow.SiteView.DispatcherMonitor.notifyDispatcherMonitor(com.dragonflow.SiteView.DispatcherMonitor.EDIT_MON, atomicmonitor);
//                }
//            }
            if(!s.equals(OP_TEMP))
            {
                WriteGroupFrames(s2, array);
            }
            if(s.equals(OP_ADD) || s.equals(OP_TEMP))
            {
                atomicmonitor.setProperty(com.dragonflow.SiteView.Monitor.pID, s3);
            }
            if(!s.equals(OP_EDIT) && !s.equals(OP_ADD) || atomicmonitor.getProperty(com.dragonflow.SiteView.Monitor.pDisabled).length() != 0 || atomicmonitor.getPropertyAsLong(com.dragonflow.SiteView.AtomicMonitor.pFrequency) == 0L || !com.dragonflow.SiteView.SiteViewGroup.currentSiteView().internalServerActive())
            {
                com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
                detectconfigurationchange.setConfigChangeFlag();
            }
            if(atomicmonitor instanceof com.dragonflow.SiteView.BrowsableMonitor)
            {
                com.dragonflow.SiteView.BrowsableCache.getCache(s1, false, true);
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                "APIMonitor", "writeMonitor", exception.getMessage()
            });
        }
    }

    private void saveThresholds(com.dragonflow.SiteView.Monitor monitor, jgl.HashMap hashmap)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        int i = getThresholdNum(monitor);
        java.lang.String as[] = {
            "error", "warning", "good"
        };
        java.lang.String s = "-condition";
        java.lang.String s1 = "-comparison";
        java.lang.String s2 = "-parameter";
        monitor.unsetProperty("_classifier");
        com.dragonflow.SiteView.Rule rule;
        for(java.util.Enumeration enumeration = monitor.getClassifiers(); enumeration.hasMoreElements(); monitor.removeElement(rule))
        {
            rule = (com.dragonflow.SiteView.Rule)enumeration.nextElement();
        }

        for(int j = 0; j < as.length; j++)
        {
            for(int k = 0; k < i; k++)
            {
                java.lang.String s3 = as[j] + s + k;
                java.lang.String s4 = as[j] + s1 + k;
                java.lang.String s5 = as[j] + s2 + k;
                java.lang.String s6 = (java.lang.String)hashmap.get(s3);
                java.lang.String s7 = (java.lang.String)hashmap.get(s4);
                java.lang.String s8 = (java.lang.String)hashmap.get(s5);
                hashmap.remove(s3);
                hashmap.remove(s4);
                hashmap.remove(s5);
                if(s6 == null || s6.equals("default"))
                {
                    continue;
                }
                if(s7 == null)
                {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_INVALID_THRESHOLD_COND_MISSING);
                }
                if(s8 == null)
                {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_INVALID_THRESHOLD_VAL_MISSING);
                }
                java.lang.String s9 = s6 + " " + s7 + " " + s8 + "\t" + as[j];
                saveThreshold(monitor, k, as[j], s9);
            }

        }

    }

    private void saveThreshold(com.dragonflow.SiteView.Monitor monitor, int i, java.lang.String s, java.lang.String s1)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        int j = getThresholdNum(monitor);
        java.lang.String s2 = "SetProperty category " + s;
        if(i > j)
        {
            throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_INVALID_THRESHOLD, new java.lang.String[] {
                s1, (new Integer(i)).toString()
            });
        }
        com.dragonflow.SiteView.Rule rule = com.dragonflow.SiteView.Rule.stringToClassifier(s1);
        if(s2.equals(rule.getProperty(com.dragonflow.SiteView.Rule.pAction)))
        {
            if(rule != null)
            {
                monitor.addProperty("_classifier", s1);
                monitor.addElement(rule);
            } else
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_INVALID_THRESHOLD, new java.lang.String[] {
                    s1, (new Integer(i)).toString()
                });
            }
        }
    }

    private void saveCustomProperties(com.dragonflow.SiteView.Monitor monitor, jgl.HashMap hashmap)
    {
        jgl.HashMap hashmap1 = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        java.util.Enumeration enumeration = hashmap1.values("_monitorEditCustom");
        while (enumeration.hasMoreElements()) {
            java.lang.String s = (java.lang.String)enumeration.nextElement();
            java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s, "|");
            java.lang.String s1 = as[0];
            if(s1.length() > 0)
            {
                if(!s1.startsWith("_"))
                {
                    s1 = "_" + s1;
                }
                if(shouldPrintProperty(monitor, s1))
                {
                    java.lang.String s2 = (java.lang.String)hashmap.get(s1);
                    if(s2 != null)
                    {
                        s2 = s2.replace('\r', ' ');
                        s2 = s2.replace('\n', ' ');
                        monitor.setProperty(s1, (java.lang.String)hashmap.get(s1));
                    }
                }
            }
        } 
    }

    private boolean shouldPrintProperty(com.dragonflow.SiteView.SiteViewObject siteviewobject, java.lang.String s)
    {
        return !siteviewobject.propertyInTemplate(s);
    }

    private int saveOrdering(com.dragonflow.HTTP.HTTPRequest httprequest)
    {
        int i = com.dragonflow.Utils.TextUtils.toInt(httprequest.getValue("ordering"));
        if(i <= 0)
        {
            i = 1;
        }
        return i;
    }

    private void deleteMonitorInternal(java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            int i = s.indexOf(' ');
            if(i >= 0)
            {
                java.lang.String s1 = s.substring(0, i);
                java.lang.String s2 = s.substring(i + 1);
                jgl.Array array = null;
                array = getGroupFrames(s1);
                int j = findMonitorIndex(array, s2);
                if(j >= 1)
                {
                    com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                    java.lang.StringBuffer stringbuffer = new StringBuffer();
                    java.lang.String s3 = com.dragonflow.Utils.I18N.toDefaultEncoding(s1 + com.dragonflow.SiteView.SiteViewGroup.ID_SEPARATOR + s2);
                    com.dragonflow.SiteView.AtomicMonitor atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)siteviewgroup.getElement(s3);
                    if(atomicmonitor != null)
                    {
                        jgl.Array array1 = new Array();
                        siteviewgroup.notifyMonitorDeletion(atomicmonitor);
//                        if(com.dragonflow.SiteView.TopazConfigurator.configInTopazAndRegistered())
//                        {
//                            array1.add(atomicmonitor);
//                            com.dragonflow.SiteView.TopazConfigurator.updateTopaz(array1, 1, stringbuffer, false, null);
//                            if(stringbuffer.length() > 0)
//                            {
//                                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_TOPAZ_DELETE_EXCEPTION, new java.lang.String[] {
//                                    s2, stringbuffer.toString()
//                                });
//                            }
//                        }
                    }
                    array.remove(j);
                } else
                {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_UNASSOCIATED_ID, new java.lang.String[] {
                        s1 + "/" + s2
                    });
                }
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                exception.getMessage()
            });
        }
    }

    private java.util.Enumeration getRefresh(com.dragonflow.Utils.HTMLTagParser htmltagparser)
    {
        java.util.Vector vector = new Vector();
        java.util.Enumeration enumeration = htmltagparser.findTags("meta");
        while (enumeration.hasMoreElements()) {
            jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
            java.lang.String s = new String("");
            if(com.dragonflow.Utils.TextUtils.getValue(hashmap, "http-equiv").equalsIgnoreCase("refresh"))
            {
                java.lang.String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "content").trim();
                vector.addElement(s1);
                vector.addElement(s1.length() <= 80 ? ((java.lang.Object) (s1)) : ((java.lang.Object) (s1.substring(0, 79))));
            }
        }
        return vector.elements();
    }

    private java.util.Enumeration getFrames(com.dragonflow.Utils.HTMLTagParser htmltagparser)
    {
        java.util.Vector vector = new Vector();
        java.util.Enumeration enumeration = htmltagparser.findTags("frame");
        java.util.Enumeration enumeration1 = htmltagparser.findTags("iframe");
        java.lang.String s;
        for(; enumeration.hasMoreElements(); vector.addElement(s.length() <= 80 ? ((java.lang.Object) (s)) : ((java.lang.Object) (s.substring(0, 79)))))
        {
            jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
            s = com.dragonflow.Utils.TextUtils.getValue(hashmap, "name").trim();
            if(s.length() == 0)
            {
                s = com.dragonflow.Utils.TextUtils.getValue(hashmap, "src").trim();
            }
            vector.addElement(s);
        }

        java.lang.String s1;
        for(; enumeration1.hasMoreElements(); vector.addElement(s1.length() <= 80 ? ((java.lang.Object) (s1)) : ((java.lang.Object) (s1.substring(0, 79)))))
        {
            jgl.HashMap hashmap1 = (jgl.HashMap)enumeration1.nextElement();
            s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "name").trim();
            if(s1.length() == 0)
            {
                s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "src").trim();
            }
            vector.addElement(s1);
        }

        return vector.elements();
    }

    private java.util.Enumeration getForms(com.dragonflow.Utils.HTMLTagParser htmltagparser, com.dragonflow.SiteView.AtomicMonitor atomicmonitor, java.lang.String s)
    {
        java.util.Vector vector = new Vector();
        java.util.Enumeration enumeration = htmltagparser.findTags("form");
        int i = 0;
        while (enumeration.hasMoreElements()) {
            i++;
            jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
            java.lang.String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "name").trim();
            if(s1.length() == 0)
            {
                s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "action").trim();
            }
            s1 = "[" + i + "]" + s1;
            if(s1.length() > 30)
            {
                s1 = s1.substring(0, 29);
            }
            java.util.Enumeration enumeration1 = htmltagparser.findTags(hashmap, FORM_INPUT_TAGS);
            int j = 0;
            java.lang.String s2 = "";
            java.lang.String s5 = "";
            java.lang.String s7 = "";
            while (enumeration1.hasMoreElements()) {
                java.lang.String s3 = "";
                java.lang.String s6 = "";
                java.lang.String s8 = "";
                jgl.HashMap hashmap1 = (jgl.HashMap)enumeration1.nextElement();
                java.lang.String s9 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "tag");
                if(s9.equals("select"))
                {
                    java.lang.String s10 = null;
                    java.lang.String s12 = null;
                    java.util.Enumeration enumeration2 = htmltagparser.findTags(hashmap1, "option");
                    while (enumeration2.hasMoreElements()) {
                        jgl.HashMap hashmap2 = (jgl.HashMap)enumeration2.nextElement();
                        if(s12 == null)
                        {
                            s12 = com.dragonflow.Utils.TextUtils.getValue(hashmap2, "value");
                        } else
                        if(s10 == null && hashmap2.get("selected") != null)
                        {
                            s10 = com.dragonflow.Utils.TextUtils.getValue(hashmap2, "value");
                        }
                    }
                    if(s10 == null)
                    {
                        s10 = s12;
                    }
                    s6 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "name");
                    s8 = s10;
                } else
                {
                    java.lang.String s11 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "type").toLowerCase();
                    if(s11.equals("submit"))
                    {
                        j++;
                        s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "value");
                        if(s3.length() == 0)
                        {
                            s3 = "Submit";
                        }
                    } else
                    if(s11.equals("image"))
                    {
                        j++;
                        s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "name");
                        if(s3.length() == 0)
                        {
                            s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "alt");
                            if(s3.length() == 0)
                            {
                                s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "value");
                                if(s3.length() == 0)
                                {
                                    s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "src");
                                    if(s3.length() == 0)
                                    {
                                        s3 = "[" + j + "]";
                                    }
                                }
                            }
                        }
                    } else
                    if(s11.equals("text") || s11.equals("password") || s11.equals("hidden") || s11.equals("checkbox") || s11.equals(""))
                    {
                        s6 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "name");
                        s8 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "value");
                    } else
                    if(s11.equals("radio") && hashmap1.get("checked") != null)
                    {
                        s6 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "name");
                        s8 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "value");
                    }
                    if(s3.length() > 0)
                    {
                        java.lang.String s13 = "";
                        if(i > 1)
                        {
                            java.util.Enumeration enumeration3 = vector.elements();
                            if(enumeration3.hasMoreElements())
                            {
                                java.lang.String s14 = (java.lang.String)enumeration3.nextElement();
                                if(s3.equals(s14))
                                {
                                    s13 = "[" + i + "]";
                                    break;
                                }
                                s14 = (java.lang.String)enumeration3.nextElement();
                            }
                        }
                        if(s3.length() > 40)
                        {
                            s3 = s3.substring(0, 39);
                        }
                        vector.addElement("{" + s1 + "}" + s3 + s13);
                        vector.addElement("{" + s1 + "}" + s3);
                    }
                }
                if(s6.length() > 0)
                {
                    atomicmonitor.setProperty("_postData" + s, atomicmonitor.getProperty("_postData" + s) + (atomicmonitor.getProperty("_postData" + s).length() <= 0 ? "" : "\n") + "{" + s1 + "}" + s6 + "=" + s8);
                }
            } 
            if(j == 0)
            {
                java.lang.String s4 = "[" + i + "]";
                vector.addElement("{" + s1 + "}" + s4);
                vector.addElement("{" + s1 + "}" + s4);
            }
        } 
        return vector.elements();
    }

    private java.util.Enumeration getLinks(com.dragonflow.Utils.HTMLTagParser htmltagparser)
    {
        java.util.Vector vector = new Vector();
        java.lang.String s;
        for(java.util.Enumeration enumeration = htmltagparser.findTags("a"); enumeration.hasMoreElements(); vector.addElement(s.length() <= 80 ? ((java.lang.Object) (s)) : ((java.lang.Object) (s.substring(0, 79)))))
        {
            jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
            s = com.dragonflow.Utils.TextUtils.getValue(hashmap, "contents").trim();
            vector.addElement(s);
        }

        java.lang.String s1;
        for(java.util.Enumeration enumeration1 = htmltagparser.findTags("area"); enumeration1.hasMoreElements(); vector.addElement(s1.length() <= 80 ? ((java.lang.Object) (s1)) : ((java.lang.Object) (s1.substring(0, 79)))))
        {
            jgl.HashMap hashmap1 = (jgl.HashMap)enumeration1.nextElement();
            s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "contents").trim();
            if(s1.length() == 0 || s1.toLowerCase().lastIndexOf("<img") >= 0)
            {
                s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "href").trim();
            }
            vector.addElement(s1);
        }

        return vector.elements();
    }

    private void findCounters(com.dragonflow.SiteView.Monitor monitor, java.util.Vector vector, java.util.Vector vector1, org.w3c.dom.Node node, int i)
    {
        if(node.getNodeType() == 1)
        {
            org.w3c.dom.NodeList nodelist = node.getChildNodes();
            int j = nodelist.getLength();
            java.lang.String s = ((org.w3c.dom.Element)node).getAttribute("name");
            if(s != null)
            {
                java.lang.String s1 = com.dragonflow.Utils.TextUtils.arrayToString(getNodeNames(node));
                java.lang.String s2 = node.getNodeName();
                if(s2.toLowerCase().equals("counter"))
                {
                    java.lang.String s3 = ((com.dragonflow.SiteView.BrowsableMonitor)monitor).setBrowseID(getNodeIdNames(node));
                    vector1.addElement(s3);
                    vector.addElement(s1);
                }
            }
            for(int k = 0; k < j; k++)
            {
                findCounters(monitor, vector, vector1, nodelist.item(k), i + 2);
            }

        }
    }

    private jgl.Array getNodeNames(org.w3c.dom.Node node)
    {
        jgl.Array array = new Array();
        java.lang.String s = ((org.w3c.dom.Element)node).getAttribute("name");
        if(s == null)
        {
            return array;
        }
        array.add(s);
        org.w3c.dom.Node node1 = node.getParentNode();
        do
        {
            if(node1 == null)
            {
                break;
            }
            java.lang.String s1 = ((org.w3c.dom.Element)node1).getAttribute("name");
            if(s1 == null || s1.length() <= 0)
            {
                break;
            }
            array.add(s1);
            node1 = node1.getParentNode();
        } while(true);
        return array;
    }

    jgl.Array getNodeIdNames(org.w3c.dom.Node node)
    {
        jgl.Array array = new Array();
        java.lang.String s = "id";
        java.lang.String s1 = ((org.w3c.dom.Element)node).getAttribute(s);
        if(s1 == null || s1.length() == 0)
        {
            s = "name";
            s1 = ((org.w3c.dom.Element)node).getAttribute(s);
        }
        if(s1 == null)
        {
            return array;
        }
        array.add(s1);
        org.w3c.dom.Node node1 = node.getParentNode();
        do
        {
            if(node1 == null)
            {
                break;
            }
            java.lang.String s2 = ((org.w3c.dom.Element)node1).getAttribute(s);
            if(s2 == null || s2.length() <= 0)
            {
                break;
            }
            array.add(s2);
            node1 = node1.getParentNode();
        } while(true);
        return array;
    }

    private com.dragonflow.SiteView.AtomicMonitor instantiateMonitor(java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewParameterException
    {
        java.lang.Class class1 = null;
        java.lang.String s1 = "com.dragonflow.StandardMonitor." + s;
        try
        {
            class1 = java.lang.Class.forName(s1);
        }
        catch(java.lang.ClassNotFoundException classnotfoundexception)
        {
            java.lang.String s2 = "com.dragonflow.CustomMonitor." + s;
            try
            {
                class1 = java.lang.Class.forName(s2);
            }
            catch(java.lang.ClassNotFoundException classnotfoundexception1)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_TYPE_NOT_VALID, new java.lang.String[] {
                    s
                });
            }
        }
        com.dragonflow.SiteView.AtomicMonitor atomicmonitor = null;
        try
        {
            atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)class1.newInstance();
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_TYPE_NOT_VALID, new java.lang.String[] {
                s
            });
        }
        if(!com.dragonflow.SiteView.SiteViewObject.loadableClass(class1))
        {
            throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_NOT_LOADABLE, new java.lang.String[] {
                s
            });
        } else
        {
            return atomicmonitor;
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * @param s
     * @param s1
     * @return
     * @throws com.dragonflow.SiteViewException.SiteViewException
     */
    public com.dragonflow.Api.SSMonitorInstance resetCounters(java.lang.String s, java.lang.String s1)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSMonitorInstance ssmonitorinstance;
            ssmonitorinstance = null;
            try
            {
                com.dragonflow.SiteView.AtomicMonitor atomicmonitor;
                    com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                    s1 = com.dragonflow.Utils.I18N.toDefaultEncoding(s1);
                    com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElementByID(s1);
                    atomicmonitor = null;
                    if(monitorgroup != null)
                    {
                    java.util.Enumeration enumeration = monitorgroup.getMonitors();
                    com.dragonflow.SiteView.Monitor monitor;
                    java.lang.String s2;
                    while (enumeration.hasMoreElements())
                        {
                        monitor = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
                        s2 = monitor.getProperty("_id");
                    if (s2 != null && s2.equals(s)) {
                    atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)monitor;
                    }
                }
                if(atomicmonitor != null)
                {
                    atomicmonitor.resetCounters();
                } else
                {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_MONITOR_UNASSOCIATED_ID, new java.lang.String[] {
                        s1 + "/" + s
                    });
                }
            }
            }
            catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
            {
                siteviewexception.fillInStackTrace();
                throw siteviewexception;
            }
            catch(java.lang.Exception exception)
            {
                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_MONITOR_EXCEPTION, new java.lang.String[] {
                    "APIMonitor", "resetCounters"
                }, 0L, exception.getMessage());
            }
        return ssmonitorinstance;
    }

    private java.util.Enumeration adjustVirtualProperties(java.util.Enumeration enumeration)
    {
        java.util.Vector vector = new Vector();
        while (enumeration.hasMoreElements())
            {
            com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
            if(stringproperty == com.dragonflow.SiteView.Monitor.pAlertDisabled)
            {
                vector.add(pAlertDisable);
                vector.add(pAlertDisableTime);
                vector.add(pAlertDisableDesc);
                vector.add(pAlertDisableStartTime);
                vector.add(pAlertDisableEndTime);
                vector.add(pAlertDisableStartDate);
                vector.add(pAlertDisableEndDate);
            } else
            if(stringproperty == com.dragonflow.SiteView.Monitor.pDisabled)
            {
                vector.add(pMonDisable);
                vector.add(pMonDisableTime);
                vector.add(pMonDisableDesc);
                vector.add(pMonDisableStartTime);
                vector.add(pMonDisableEndTime);
                vector.add(pMonDisableStartDate);
                vector.add(pMonDisableEndDate);
            } else
            if(stringproperty != com.dragonflow.SiteView.Monitor.pDisabledDescription && stringproperty != com.dragonflow.SiteView.Monitor.pTimedDisable)
            {
                vector.add(stringproperty);
            }
        }
        return vector.elements();
    }

    static 
    {
        $assertionsDisabled = !(com.dragonflow.Api.APIMonitor.class).desiredAssertionStatus();
    }
}
