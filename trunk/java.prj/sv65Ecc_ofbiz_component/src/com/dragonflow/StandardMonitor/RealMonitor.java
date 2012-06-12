/*
 * 
 * Created on 2005-3-7 1:20:16
 *
 * RealMonitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>RealMonitor</code>
 * 
 * @author 
 * @version 0.0
 *
 *
 */

import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.*;
import com.dragonflow.Utils.PerfCounter;
import com.siteview.ecc.util.MonitorIniValueReader;
import com.siteview.ecc.util.MonitorTypeValueReader;

import java.net.URLEncoder;
import jgl.Array;
import jgl.HashMap;

public class RealMonitor extends NTCounterBase
{

    public static String returnURL;
    public static String counterObjects;
    private static StringProperty pCounters;

    public RealMonitor()
    {
    }

    public String getCountersContent()
    {
        return getProperty(pCounters);
    }

    public void setCountersContent(String s)
    {
        setProperty(pCounters, s);
    }

    public StringProperty getCountersProperty()
    {
        return pCounters;
    }

    public String getCounterObjects()
    {
        String s1 = getSetting("_counterObjectsRealMonitor");
        String s;
        if(s1 == "")
        {
            s = counterObjects;
        } else
        {
            s = s1;
        }
        return s;
    }

    public String getReturnURL()
    {
        return HTTPRequest.encodeString(returnURL);
    }

    public String getDefaultInstance()
    {
        String s1 = getSetting("_counterInstanceRealMonitor");
        String s;
        if(s1 == "")
        {
            s = "RMServer";
        } else
        {
            s = s1;
        }
        return s;
    }

    public String getDefaultCounters()
    {
        boolean flag = true;
        String s = "";
        String s1 = getDefaultInstance();
        Array array = getAvailableCounters();
        int i = 0;
        for(int j = 0; j < array.size(); j++)
        {
            if(!((PerfCounter)array.at(j)).instance.equals(s1))
            {
                continue;
            }
            if(i >= nMaxCounters)
            {
                break;
            }
            if(!flag)
            {
                s = s + ",";
            } else
            {
                flag = false;
            }
            s = s + ((PerfCounter)array.at(j)).object + " -- ";
            s = s + ((PerfCounter)array.at(j)).counterName;
            if(((PerfCounter)array.at(j)).instance.length() > 0)
            {
                s = s + " -- " + ((PerfCounter)array.at(j)).instance;
            }
            i++;
        }

        return s;
    }

    protected String getTestMachine()
    {
        return "\\\\TESTWIN2K4.qa.dragonflow.com";
    }

    public String verify(StringProperty stringproperty, String s, HTTPRequest httprequest, HashMap hashmap)
    {
        if(stringproperty == pCounters)
        {
            if(s.equals("No Counters available for this machine"))
            {
                hashmap.put(stringproperty, stringproperty.getLabel() + " missing");
            }
            return s;
        } else
        {
            return super.verify(stringproperty, s, httprequest, hashmap);
        }
    }

    static 
    {
        returnURL = "/SiteView/cgi/go.exe/SiteView/?page=monitor&class=RealMonitor";
        counterObjects = "RMServer";
        pCounters = new StringProperty("_counters", "", "Selected Counters");
        String counters_description = MonitorIniValueReader.getValue(RealMonitor.class.getName(), "_counters", MonitorIniValueReader.DESCRIPTION);
        counters_description = counters_description.replaceAll("1%", URLEncoder.encode(returnURL));
        counters_description = counters_description.replaceAll("2%", ""+nMaxCounters);
        counters_description = counters_description.replaceAll("3%", counterObjects);
        pCounters.setDisplayText(MonitorIniValueReader.getValue(RealMonitor.class.getName(), "_counters", MonitorIniValueReader.LABEL), counters_description);
        //pCounters.setDisplayText("Counters", "the current selection of counters</TD></TR><TR><TD></TD><TD><A HREF=\"/SiteView/cgi/go.exe/SiteView/?page=counter&returnURL=" + URLEncoder.encode(returnURL) + "&maxcounters=" + nMaxCounters + "&counterobjects=" + counterObjects + "&type=NTCounter\">choose counters</A>");
        pCounters.setParameterOptions(false, true, 1, false);
        pCounters.isMultiLine = true;
        StringProperty astringproperty[] = {
            pCounters
        };
        addProperties("com.dragonflow.StandardMonitor.RealMonitor", astringproperty);
        addClassElement("com.dragonflow.StandardMonitor.RealMonitor", Rule.stringToClassifier("value0 == n/a\terror", true));
        addClassElement("com.dragonflow.StandardMonitor.RealMonitor", Rule.stringToClassifier("always\tgood"));
        setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "description", MonitorTypeValueReader.getValue(RealMonitor.class.getName(), MonitorTypeValueReader.DESCRIPTION));
        //setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "description", "Monitors RealNetworks RealSystem Media Server performance metrics.");
        
        setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "help", "RealMediaMon.htm");
        
        setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "title", MonitorTypeValueReader.getValue(RealMonitor.class.getName(), MonitorTypeValueReader.TITLE));
        //setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "title", "Real Media Server");
        
        setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "class", "RealMonitor");
        
        setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "target", MonitorTypeValueReader.getValue(RealMonitor.class.getName(), MonitorTypeValueReader.TARGET));
        //setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "target", "_serverName");
        
        setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "topazName", MonitorTypeValueReader.getValue(RealMonitor.class.getName(), MonitorTypeValueReader.TOPAZNAME));
        //setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "topazName", "Real Media Server");
        
        setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "classType", MonitorTypeValueReader.getValue(RealMonitor.class.getName(), MonitorTypeValueReader.CLASSTYPE));
        //setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "classType", "application");
        
        setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "topazType", MonitorTypeValueReader.getValue(RealMonitor.class.getName(), MonitorTypeValueReader.TOPAZTYPE));
        //setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "topazType", "Streaming Media");
        
        setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "applicationType", MonitorTypeValueReader.getValue(RealMonitor.class.getName(), MonitorTypeValueReader.APPLICATIONTYPE));
        //setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "applicationType", "NTCounter");
        if(!Platform.isWindows())
        {
            setClassProperty("com.dragonflow.StandardMonitor.RealMonitor", "loadable", "false");
        }
    }

	@Override
	public boolean getSvdbRecordState(String paramName, String operate,
			String paramValue) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public String getSvdbkeyValueStr() {
		// TODO Auto-generated method stub
		return null;
	}
}
