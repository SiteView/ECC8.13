/*
 * 
 * Created on 2005-3-9 18:55:36
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Utils.Snmp.Monitoring;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.Vector;

import com.dragonflow.SiteView.RealTimeReportingData;

// Referenced classes of package com.dragonflow.Utils.Snmp.Monitoring:
// Metric

public class Device
{

    java.util.Vector metrics;
    private String identifier;
    private String displayName;
    private com.dragonflow.Utils.Snmp.SNMPSession session;
    private java.util.Hashtable propertyNametoMetricLabel;
    private java.util.Hashtable RTPropertyNametoMetricLabel;
    private java.util.Hashtable RTPropertyNametoGraphLabel;
    private String initialRTPropertyValue;
    private long realTimeDataWindow;
    private int numRequests;
    static final boolean $assertionsDisabled; /* synthetic field */

    public Device(String s, String s1, java.util.Vector vector)
    {
        initialRTPropertyValue = "-1";
        numRequests = -1;
        identifier = s;
        displayName = s1;
        metrics = vector;
        propertyNametoMetricLabel = new Hashtable();
        RTPropertyNametoMetricLabel = new Hashtable();
        RTPropertyNametoGraphLabel = new Hashtable();
    }

    public void setRealTimeDataWindow(long l)
    {
        realTimeDataWindow = l;
    }

    public void setSession(com.dragonflow.Utils.Snmp.SNMPSession snmpsession)
    {
        session = snmpsession;
        int i = metrics.size();
        for(int j = 0; j < i; j++)
        {
            com.dragonflow.Utils.Snmp.Monitoring.Metric metric = (com.dragonflow.Utils.Snmp.Monitoring.Metric)metrics.get(j);
            metric.setSession(snmpsession);
        }

    }

    public String getDisplayName()
    {
        return displayName;
    }

    public String getIdentifier()
    {
        return identifier;
    }

    public boolean refreshMetrics(StringBuffer stringbuffer)
    {
        stringbuffer.setLength(0);
        for(int i = 0; i < metrics.size(); i++)
        {
            com.dragonflow.Utils.Snmp.Monitoring.Metric metric = (com.dragonflow.Utils.Snmp.Monitoring.Metric)metrics.get(i);
            metric.refresh(stringbuffer);
            if(stringbuffer.length() > 0)
            {
                return false;
            }
        }

        return true;
    }

    public int populateRegularProperties(com.dragonflow.Properties.StringProperty astringproperty[], com.dragonflow.SiteView.Monitor monitor)
    {
        int i = 0;
        int j = metrics.size();
        for(int k = 0; k < j && i < astringproperty.length; k++)
        {
            com.dragonflow.Utils.Snmp.Monitoring.Metric metric = (com.dragonflow.Utils.Snmp.Monitoring.Metric)metrics.get(k);
            String as[] = metric.getValues();
            for(int l = 0; l < as.length && i < astringproperty.length; l++)
            {
                monitor.setProperty(astringproperty[i], as[l]);
                propertyNametoMetricLabel.put(astringproperty[i].getName(), metric.getLabel(l));
                i++;
            }

        }

        return i;
    }

    public java.util.Vector getRTDataFromProperty(String s)
    {
        return (java.util.Vector)com.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(s);
    }

    public int populateRTProperties(com.dragonflow.Properties.StringProperty astringproperty[], com.dragonflow.SiteView.Monitor monitor, com.dragonflow.Properties.StringProperty stringproperty)
    {
        int i = 0;
        int j = metrics.size();
        java.util.HashMap hashmap = (java.util.HashMap)com.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(monitor.getProperty(stringproperty));
        if(hashmap == null)
        {
            hashmap = new HashMap();
        }
        java.util.ArrayList arraylist = new ArrayList();
        for(int k = 0; k < j && i < astringproperty.length; k++)
        {
            com.dragonflow.Utils.Snmp.Monitoring.Metric metric = (com.dragonflow.Utils.Snmp.Monitoring.Metric)metrics.get(k);
            if(!metric.isRealTime())
            {
                continue;
            }
            String as[] = metric.getValues();
            arraylist.clear();
            for(int l = 0; l < as.length && i < astringproperty.length; l++)
            {
                if(metric.isOnSameGraph())
                {
                    arraylist.add(astringproperty[i].getName());
                }
                java.util.Vector vector;
                if(isNewRTProperty(monitor.getProperty(astringproperty[i])))
                {
                    vector = new Vector();
                } else
                {
                    vector = (java.util.Vector)com.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(monitor.getProperty(astringproperty[i]));
                    truncateDataOutsideWindow(vector);
                }
                com.dragonflow.SiteView.RealTimeReportingData realtimereportingdata = new RealTimeReportingData(metric.getTime(), as[l]);
                vector.add(realtimereportingdata);
                monitor.setProperty(astringproperty[i], com.dragonflow.Utils.SerializerUtils.encodeObjectBase64(vector, false));
                String s = astringproperty[i].getName();
                RTPropertyNametoMetricLabel.put(s, metric.getLabel(l));
                RTPropertyNametoGraphLabel.put(s, metric.getName());
                i++;
            }

            String as1[] = new String[arraylist.size()];
            arraylist.toArray(as1);
            for(int i1 = 0; i1 < as1.length; i1++)
            {
                hashmap.put(as1[i1], as1);
            }

        }

        monitor.setProperty(stringproperty, com.dragonflow.Utils.SerializerUtils.encodeObjectBase64(hashmap, false));
        return i;
    }

    public com.dragonflow.Properties.StringProperty[] getPropertiesOnSameGraph(com.dragonflow.SiteView.Monitor monitor, com.dragonflow.Properties.StringProperty stringproperty, com.dragonflow.Properties.StringProperty stringproperty1)
    {
        String s = monitor.getProperty(stringproperty1);
        java.util.HashMap hashmap;
        String as[];
        if((hashmap = (java.util.HashMap)com.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(s)) != null && (as = (String[])hashmap.get(stringproperty.getName())) != null)
        {
            com.dragonflow.Properties.StringProperty astringproperty[] = new com.dragonflow.Properties.StringProperty[as.length];
            for(int i = 0; i < as.length; i++)
            {
                com.dragonflow.Properties.StringProperty stringproperty2 = monitor.getPropertyObject(as[i]);
                if(stringproperty2 == null)
                {
                    com.dragonflow.Log.LogManager.log("Error", "Device.getPropertiesOnSameGraph could not find property: " + as[i]);
                    return (new com.dragonflow.Properties.StringProperty[] {
                        stringproperty
                    });
                }
                astringproperty[i] = stringproperty2;
            }

            return astringproperty;
        } else
        {
            return (new com.dragonflow.Properties.StringProperty[] {
                stringproperty
            });
        }
    }

    private void truncateDataOutsideWindow(java.util.Vector vector)
    {
        if(vector == null)
        {
            return;
        }
        long l = (new Date()).getTime() / 1000L;
        java.util.ListIterator listiterator = vector.listIterator();
        do
        {
            if(!listiterator.hasNext())
            {
                break;
            }
            com.dragonflow.SiteView.RealTimeReportingData realtimereportingdata = (com.dragonflow.SiteView.RealTimeReportingData)listiterator.next();
            if(l - realtimereportingdata.getTime() <= realTimeDataWindow)
            {
                break;
            }
            listiterator.remove();
        } while(true);
    }

    private boolean isNewRTProperty(String s)
    {
        return s.equals(initialRTPropertyValue);
    }

    public void setInitialRTPropertyValue(String s)
    {
        initialRTPropertyValue = "-1";
    }

    public void updateRegularPropertyNameToLabelMap(com.dragonflow.Properties.StringProperty stringproperty, com.dragonflow.SiteView.Monitor monitor)
    {
        monitor.setProperty(stringproperty, com.dragonflow.Utils.SerializerUtils.encodeObjectBase64(propertyNametoMetricLabel, false));
    }

    public void updateRTPropertyNameToLabelMap(com.dragonflow.Properties.StringProperty stringproperty, com.dragonflow.SiteView.Monitor monitor)
    {
        monitor.setProperty(stringproperty, com.dragonflow.Utils.SerializerUtils.encodeObjectBase64(RTPropertyNametoMetricLabel, false));
    }

    public void updateRTPropertyNameToGraphLabelMap(com.dragonflow.Properties.StringProperty stringproperty, com.dragonflow.SiteView.Monitor monitor)
    {
        monitor.setProperty(stringproperty, com.dragonflow.Utils.SerializerUtils.encodeObjectBase64(RTPropertyNametoGraphLabel, false));
    }

    public void setRegularyPropertyNameToLabelMap(com.dragonflow.Properties.StringProperty stringproperty, com.dragonflow.SiteView.Monitor monitor)
    {
        if(monitor.getProperty(stringproperty).length() > 0)
        {
            propertyNametoMetricLabel = (java.util.Hashtable)com.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(monitor.getProperty(stringproperty));
        }
    }

    public void setRTPropertyNameToLabelMap(com.dragonflow.Properties.StringProperty stringproperty, com.dragonflow.SiteView.Monitor monitor)
    {
        if(monitor.getProperty(stringproperty).length() > 0)
        {
            RTPropertyNametoMetricLabel = (java.util.Hashtable)com.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(monitor.getProperty(stringproperty));
        }
    }

    public void setRTPropertyNameToGraphLabelMap(com.dragonflow.Properties.StringProperty stringproperty, com.dragonflow.SiteView.Monitor monitor)
    {
        if(monitor.getProperty(stringproperty).length() > 0)
        {
            RTPropertyNametoGraphLabel = (java.util.Hashtable)com.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(monitor.getProperty(stringproperty));
        }
    }

    public String getLabelFromPropertyName(String s)
    {
        String s1 = (String)propertyNametoMetricLabel.get(s);
        if(s1 == null)
        {
            s1 = (String)RTPropertyNametoMetricLabel.get(s);
        }
        if(s1 == null)
        {
            s1 = "";
        }
        return s1;
    }

    public String getRTGraphLabel(String s)
    {
        String s1 = (String)RTPropertyNametoGraphLabel.get(s);
        if(s1 == null)
        {
            s1 = "";
        }
        return s1;
    }

    public int getNumRequests()
    {
        if(numRequests > 0)
        {
            return numRequests;
        }
        numRequests = 0;
        for(int i = 0; i < metrics.size(); i++)
        {
            com.dragonflow.Utils.Snmp.Monitoring.Metric metric = (com.dragonflow.Utils.Snmp.Monitoring.Metric)metrics.get(i);
            numRequests += metric.getNumRequests();
        }

        return numRequests;
    }

    public int populateNamesAndIDs(com.dragonflow.Properties.StringProperty astringproperty[], com.dragonflow.Properties.StringProperty astringproperty1[], com.dragonflow.SiteView.Monitor monitor, StringBuffer stringbuffer)
    {
        if(!$assertionsDisabled && astringproperty.length != astringproperty1.length)
        {
            throw new AssertionError();
        }
        stringbuffer.setLength(0);
        int i = 0;
        for(int j = 0; j < metrics.size() && i < astringproperty1.length; j++)
        {
            com.dragonflow.Utils.Snmp.Monitoring.Metric metric = (com.dragonflow.Utils.Snmp.Monitoring.Metric)metrics.get(j);
            String as[] = metric.getInstanceOIDs(stringbuffer);
            String as1[] = metric.getInstanceNames(stringbuffer);
            if(stringbuffer.length() > 0)
            {
                return i;
            }
            for(int k = 0; k < as.length && i < astringproperty1.length; k++)
            {
                monitor.setProperty(astringproperty1[i], as[k]);
                if(as1.length == as.length)
                {
                    monitor.setProperty(astringproperty[i], as1[k]);
                } else
                {
                    monitor.setProperty(astringproperty[i], as1[0]);
                }
                i++;
            }

        }

        return i;
    }

    static 
    {
        $assertionsDisabled = !(com.dragonflow.Utils.Snmp.Monitoring.Device.class).desiredAssertionStatus();
    }
}
