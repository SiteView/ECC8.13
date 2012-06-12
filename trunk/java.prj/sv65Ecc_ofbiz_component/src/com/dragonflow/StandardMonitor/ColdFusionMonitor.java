/*
 * 
 * Created on 2005-3-7 0:53:01
 *
 * ColdFusionMonitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>ColdFusionMonitor</code>
 * 
 * @author 
 * @version 0.0
 *
 *
 */
import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.*;
import com.siteview.ecc.util.MonitorIniValueReader;
import com.siteview.ecc.util.MonitorTypeValueReader;

import java.net.URLEncoder;
import jgl.HashMap;

public class ColdFusionMonitor extends NTCounterBase
{

 static String returnURL;
 static String counterObjects;
 private static StringProperty pCounters;

 public ColdFusionMonitor()
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
     String s1 = getSetting("_counterObjectsColdFusionMonitor");
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
     String s1 = getSetting("_counterInstanceColdFusionMonitor");
     String s;
     if(s1 == "")
     {
         s = "cfserver";
     } else
     {
         s = s1;
     }
     return s;
 }

 public String getDefaultCounters()
 {
     return "ColdFusion Server -- Page Hits / Sec -- cfserver,ColdFusion Server -- Bytes Out / Sec -- cfserver,ColdFusion Server -- Queued Requests -- cfserver,ColdFusion Server -- Running Requests -- cfserver,ColdFusion Server -- Avg Queue Time (msec) -- cfserver,ColdFusion Server -- Avg Req Time (msec) -- cfserver";
 }

 protected String getTestMachine()
 {
     return "\\\\TESTWIN2K1.qa.Dragonflow.com";
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
     returnURL = "/SiteView/cgi/go.exe/SiteView/?page=monitor&class=ColdFusionMonitor";
     counterObjects = "ColdFusion Server";
     
     pCounters = new StringProperty("_counters", "", "ColdFusion Selected Counters");
     String tempcounters=MonitorIniValueReader.getValue(ColdFusionMonitor.class.getName(), "_counters", MonitorIniValueReader.DESCRIPTION);
     tempcounters=tempcounters.replaceAll("1%", URLEncoder.encode(returnURL));
     tempcounters=tempcounters.replaceAll("2%", ""+nMaxCounters);
     tempcounters=tempcounters.replaceAll("3%", counterObjects);
     pCounters.setDisplayText(MonitorIniValueReader.getValue(ColdFusionMonitor.class.getName(), "_counters", MonitorIniValueReader.LABEL),tempcounters);
     //pCounters.setDisplayText("Counters", "the current selection of counters</TD></TR><TR><TD></TD><TD><A HREF=\"/SiteView/cgi/go.exe/SiteView/?page=counter&returnURL=" + URLEncoder.encode(returnURL) + "&maxcounters=" + nMaxCounters + "&counterobjects=" + counterObjects + "&type=NTCounter\">choose counters</A>");
     pCounters.setParameterOptions(false, true, 1, false);
     pCounters.isMultiLine = true;
     StringProperty astringproperty[] = {
         pCounters
     };
     addProperties("com.dragonflow.StandardMonitor.ColdFusionMonitor", astringproperty);
     addClassElement("com.dragonflow.StandardMonitor.ColdFusionMonitor", Rule.stringToClassifier("value0 == n/a\terror", true));
     addClassElement("com.dragonflow.StandardMonitor.ColdFusionMonitor", Rule.stringToClassifier("always\tgood"));
     setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "description", MonitorTypeValueReader.getValue(ColdFusionMonitor.class.getName(), MonitorTypeValueReader.DESCRIPTION));
     //setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "description", "Monitors ColdFusion server performance metrics.");
     
     setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "help", "ColdFusionMon.htm");
     
     setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "title", MonitorTypeValueReader.getValue(ColdFusionMonitor.class.getName(), MonitorTypeValueReader.TITLE));
     //setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "title", "ColdFusion Server");
     
     setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "class", "ColdFusionMonitor");
     
     setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "target", MonitorTypeValueReader.getValue(ColdFusionMonitor.class.getName(), MonitorTypeValueReader.TARGET));
     //setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "target", "_serverName");
     
     setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "topazName", MonitorTypeValueReader.getValue(ColdFusionMonitor.class.getName(), MonitorTypeValueReader.TOPAZNAME));
     //setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "topazName", "MS ColdFusion Server");
     
     setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "topazType", MonitorTypeValueReader.getValue(ColdFusionMonitor.class.getName(), MonitorTypeValueReader.TOPAZTYPE));
     //setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "topazType", "Web Server");
     
     setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "classType", MonitorTypeValueReader.getValue(ColdFusionMonitor.class.getName(), MonitorTypeValueReader.CLASSTYPE));
     //setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "classType", "application");
     
     setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "applicationType", MonitorTypeValueReader.getValue(ColdFusionMonitor.class.getName(), MonitorTypeValueReader.APPLICATIONTYPE));
     //setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "applicationType", "NTCounter");
     if(!Platform.isWindows())
     {
         setClassProperty("com.dragonflow.StandardMonitor.ColdFusionMonitor", "loadable", "false");
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