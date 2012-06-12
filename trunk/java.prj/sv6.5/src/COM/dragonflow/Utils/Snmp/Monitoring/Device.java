/*
 * 
 * Created on 2005-3-9 18:55:36
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.Utils.Snmp.Monitoring;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.Vector;

import COM.dragonflow.SiteView.RealTimeReportingData;

// Referenced classes of package COM.dragonflow.Utils.Snmp.Monitoring:
// Metric

public class Device
{

    java.util.Vector metrics;
    private java.lang.String identifier;
    private java.lang.String displayName;
    private COM.dragonflow.Utils.Snmp.SNMPSession session;
    private java.util.Hashtable propertyNametoMetricLabel;
    private java.util.Hashtable RTPropertyNametoMetricLabel;
    private java.util.Hashtable RTPropertyNametoGraphLabel;
    private java.lang.String initialRTPropertyValue;
    private long realTimeDataWindow;
    private int numRequests;
    static final boolean $assertionsDisabled; /* synthetic field */

    public Device(java.lang.String s, java.lang.String s1, java.util.Vector vector)
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

    public void setSession(COM.dragonflow.Utils.Snmp.SNMPSession snmpsession)
    {
        session = snmpsession;
        int i = metrics.size();
        for(int j = 0; j < i; j++)
        {
            COM.dragonflow.Utils.Snmp.Monitoring.Metric metric = (COM.dragonflow.Utils.Snmp.Monitoring.Metric)metrics.get(j);
            metric.setSession(snmpsession);
        }

    }

    public java.lang.String getDisplayName()
    {
        return displayName;
    }

    public java.lang.String getIdentifier()
    {
        return identifier;
    }

    public boolean refreshMetrics(java.lang.StringBuffer stringbuffer)
    {
        stringbuffer.setLength(0);
        for(int i = 0; i < metrics.size(); i++)
        {
            COM.dragonflow.Utils.Snmp.Monitoring.Metric metric = (COM.dragonflow.Utils.Snmp.Monitoring.Metric)metrics.get(i);
            metric.refresh(stringbuffer);
            if(stringbuffer.length() > 0)
            {
                return false;
            }
        }

        return true;
    }

    public int populateRegularProperties(COM.dragonflow.Properties.StringProperty astringproperty[], COM.dragonflow.SiteView.Monitor monitor)
    {
        int i = 0;
        int j = metrics.size();
        for(int k = 0; k < j && i < astringproperty.length; k++)
        {
            COM.dragonflow.Utils.Snmp.Monitoring.Metric metric = (COM.dragonflow.Utils.Snmp.Monitoring.Metric)metrics.get(k);
            java.lang.String as[] = metric.getValues();
            for(int l = 0; l < as.length && i < astringproperty.length; l++)
            {
                monitor.setProperty(astringproperty[i], as[l]);
                propertyNametoMetricLabel.put(astringproperty[i].getName(), metric.getLabel(l));
                i++;
            }

        }

        return i;
    }

    public java.util.Vector getRTDataFromProperty(java.lang.String s)
    {
        return (java.util.Vector)COM.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(s);
    }

    public int populateRTProperties(COM.dragonflow.Properties.StringProperty astringproperty[], COM.dragonflow.SiteView.Monitor monitor, COM.dragonflow.Properties.StringProperty stringproperty)
    {
        int i = 0;
        int j = metrics.size();
        java.util.HashMap hashmap = (java.util.HashMap)COM.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(monitor.getProperty(stringproperty));
        if(hashmap == null)
        {
            hashmap = new HashMap();
        }
        java.util.ArrayList arraylist = new ArrayList();
        for(int k = 0; k < j && i < astringproperty.length; k++)
        {
            COM.dragonflow.Utils.Snmp.Monitoring.Metric metric = (COM.dragonflow.Utils.Snmp.Monitoring.Metric)metrics.get(k);
            if(!metric.isRealTime())
            {
                continue;
            }
            java.lang.String as[] = metric.getValues();
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
                    vector = (java.util.Vector)COM.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(monitor.getProperty(astringproperty[i]));
                    truncateDataOutsideWindow(vector);
                }
                COM.dragonflow.SiteView.RealTimeReportingData realtimereportingdata = new RealTimeReportingData(metric.getTime(), as[l]);
                vector.add(realtimereportingdata);
                monitor.setProperty(astringproperty[i], COM.dragonflow.Utils.SerializerUtils.encodeObjectBase64(vector, false));
                java.lang.String s = astringproperty[i].getName();
                RTPropertyNametoMetricLabel.put(s, metric.getLabel(l));
                RTPropertyNametoGraphLabel.put(s, metric.getName());
                i++;
            }

            java.lang.String as1[] = new java.lang.String[arraylist.size()];
            arraylist.toArray(as1);
            for(int i1 = 0; i1 < as1.length; i1++)
            {
                hashmap.put(as1[i1], as1);
            }

        }

        monitor.setProperty(stringproperty, COM.dragonflow.Utils.SerializerUtils.encodeObjectBase64(hashmap, false));
        return i;
    }

    public COM.dragonflow.Properties.StringProperty[] getPropertiesOnSameGraph(COM.dragonflow.SiteView.Monitor monitor, COM.dragonflow.Properties.StringProperty stringproperty, COM.dragonflow.Properties.StringProperty stringproperty1)
    {
        java.lang.String s = monitor.getProperty(stringproperty1);
        java.util.HashMap hashmap;
        java.lang.String as[];
        if((hashmap = (java.util.HashMap)COM.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(s)) != null && (as = (java.lang.String[])hashmap.get(stringproperty.getName())) != null)
        {
            COM.dragonflow.Properties.StringProperty astringproperty[] = new COM.dragonflow.Properties.StringProperty[as.length];
            for(int i = 0; i < as.length; i++)
            {
                COM.dragonflow.Properties.StringProperty stringproperty2 = monitor.getPropertyObject(as[i]);
                if(stringproperty2 == null)
                {
                    COM.dragonflow.Log.LogManager.log("Error", "Device.getPropertiesOnSameGraph could not find property: " + as[i]);
                    return (new COM.dragonflow.Properties.StringProperty[] {
                        stringproperty
                    });
                }
                astringproperty[i] = stringproperty2;
            }

            return astringproperty;
        } else
        {
            return (new COM.dragonflow.Properties.StringProperty[] {
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
            COM.dragonflow.SiteView.RealTimeReportingData realtimereportingdata = (COM.dragonflow.SiteView.RealTimeReportingData)listiterator.next();
            if(l - realtimereportingdata.getTime() <= realTimeDataWindow)
            {
                break;
            }
            listiterator.remove();
        } while(true);
    }

    private boolean isNewRTProperty(java.lang.String s)
    {
        return s.equals(initialRTPropertyValue);
    }

    public void setInitialRTPropertyValue(java.lang.String s)
    {
        initialRTPropertyValue = "-1";
    }

    public void updateRegularPropertyNameToLabelMap(COM.dragonflow.Properties.StringProperty stringproperty, COM.dragonflow.SiteView.Monitor monitor)
    {
        monitor.setProperty(stringproperty, COM.dragonflow.Utils.SerializerUtils.encodeObjectBase64(propertyNametoMetricLabel, false));
    }

    public void updateRTPropertyNameToLabelMap(COM.dragonflow.Properties.StringProperty stringproperty, COM.dragonflow.SiteView.Monitor monitor)
    {
        monitor.setProperty(stringproperty, COM.dragonflow.Utils.SerializerUtils.encodeObjectBase64(RTPropertyNametoMetricLabel, false));
    }

    public void updateRTPropertyNameToGraphLabelMap(COM.dragonflow.Properties.StringProperty stringproperty, COM.dragonflow.SiteView.Monitor monitor)
    {
        monitor.setProperty(stringproperty, COM.dragonflow.Utils.SerializerUtils.encodeObjectBase64(RTPropertyNametoGraphLabel, false));
    }

    public void setRegularyPropertyNameToLabelMap(COM.dragonflow.Properties.StringProperty stringproperty, COM.dragonflow.SiteView.Monitor monitor)
    {
        if(monitor.getProperty(stringproperty).length() > 0)
        {
            propertyNametoMetricLabel = (java.util.Hashtable)COM.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(monitor.getProperty(stringproperty));
        }
    }

    public void setRTPropertyNameToLabelMap(COM.dragonflow.Properties.StringProperty stringproperty, COM.dragonflow.SiteView.Monitor monitor)
    {
        if(monitor.getProperty(stringproperty).length() > 0)
        {
            RTPropertyNametoMetricLabel = (java.util.Hashtable)COM.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(monitor.getProperty(stringproperty));
        }
    }

    public void setRTPropertyNameToGraphLabelMap(COM.dragonflow.Properties.StringProperty stringproperty, COM.dragonflow.SiteView.Monitor monitor)
    {
        if(monitor.getProperty(stringproperty).length() > 0)
        {
            RTPropertyNametoGraphLabel = (java.util.Hashtable)COM.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromStringBase64(monitor.getProperty(stringproperty));
        }
    }

    public java.lang.String getLabelFromPropertyName(java.lang.String s)
    {
        java.lang.String s1 = (java.lang.String)propertyNametoMetricLabel.get(s);
        if(s1 == null)
        {
            s1 = (java.lang.String)RTPropertyNametoMetricLabel.get(s);
        }
        if(s1 == null)
        {
            s1 = "";
        }
        return s1;
    }

    public java.lang.String getRTGraphLabel(java.lang.String s)
    {
        java.lang.String s1 = (java.lang.String)RTPropertyNametoGraphLabel.get(s);
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
            COM.dragonflow.Utils.Snmp.Monitoring.Metric metric = (COM.dragonflow.Utils.Snmp.Monitoring.Metric)metrics.get(i);
            numRequests += metric.getNumRequests();
        }

        return numRequests;
    }

    public int populateNamesAndIDs(COM.dragonflow.Properties.StringProperty astringproperty[], COM.dragonflow.Properties.StringProperty astringproperty1[], COM.dragonflow.SiteView.Monitor monitor, java.lang.StringBuffer stringbuffer)
    {
        if(!$assertionsDisabled && astringproperty.length != astringproperty1.length)
        {
            throw new AssertionError();
        }
        stringbuffer.setLength(0);
        int i = 0;
        for(int j = 0; j < metrics.size() && i < astringproperty1.length; j++)
        {
            COM.dragonflow.Utils.Snmp.Monitoring.Metric metric = (COM.dragonflow.Utils.Snmp.Monitoring.Metric)metrics.get(j);
            java.lang.String as[] = metric.getInstanceOIDs(stringbuffer);
            java.lang.String as1[] = metric.getInstanceNames(stringbuffer);
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
        $assertionsDisabled = !(COM.dragonflow.Utils.Snmp.Monitoring.Device.class).desiredAssertionStatus();
    }
}
