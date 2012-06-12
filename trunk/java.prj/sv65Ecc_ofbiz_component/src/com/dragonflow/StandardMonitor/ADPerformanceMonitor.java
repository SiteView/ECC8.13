/*
 * 
 * Created on 2005-3-5 14:16:07
 *
 * ADPerformanceMonitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>ADPerformanceMonitor</code>
 * 
 * @author 
 * @version 0.0
 *
 *
 */
import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.*;
import com.dragonflow.Utils.*;
import com.siteview.ecc.util.MonitorIniValueReader;
import com.siteview.ecc.util.MonitorTypeValueReader;

import java.io.File;
import java.io.IOException;
import java.net.URLEncoder;
import jgl.Array;
import jgl.HashMap;

//Referenced classes of package com.dragonflow.StandardMonitor:
//         URLMonitor

public class ADPerformanceMonitor extends NTCounterBase
{

 static String returnURL;
 static String counterObjects;
 private static StringProperty pCounters;
 static String default_counters_path;

 public ADPerformanceMonitor()
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
     String s1 = getSetting("_counterObjectsADPerformanceMonitor");
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
     String s1 = getSetting("_counterInstanceADPerformanceMonitor");
     String s;
     if(s1 == "")
     {
         s = "_Total";
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
     File file = new File(default_counters_path);
     if(file.exists())
     {
         try
         {
             StringBuffer stringbuffer = FileUtils.readFile(default_counters_path);
             s = TextUtils.replaceString(stringbuffer.toString(), URLMonitor.CRLF, ",");
         }
         catch(IOException ioexception)
         {
             ioexception.printStackTrace();
         }
     } else
     {
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

     }
     return s;
 }

 protected String getTestMachine()
 {
     return "\\\\BCROWE";
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
     returnURL = "/SiteView/cgi/go.exe/SiteView/?page=monitor&class=ADPerformanceMonitor";
     counterObjects = "FileReplicaConn,FileReplicaSet,NTDS,Database";
     default_counters_path = Platform.getRoot() + File.separator + "templates.applications" + File.separator + "counters.ad";
     HashMap hashmap = MasterConfig.getMasterConfig();
     pCounters = new StringProperty("_counters", "", "Selected Counters");
     String description = MonitorIniValueReader.getValue(ADPerformanceMonitor.class.getName(), "_Counters", MonitorIniValueReader.DESCRIPTION);
     //String description ="the current selection of counters</TD></TR><TR><TD></TD><TD><A HREF=\"/SiteView/cgi/go.exe/SiteView/?page=counter&returnURL=" + URLEncoder.encode(returnURL) + "&maxcounters=" + nMaxCounters + "&counterobjects=" + counterObjects + "&type=NTCounter\">choose counters</A>";
     description=description.replaceAll("1%", URLEncoder.encode(returnURL));
     description=description.replaceAll("2%",""+nMaxCounters);
     description=description.replaceAll("3%", counterObjects);
     pCounters.setDisplayText(MonitorIniValueReader.getValue(ADPerformanceMonitor.class.getName(),"_Counters",MonitorIniValueReader.LABEL), description);
     //pCounters.setDisplayText("Counters", "the current selection of counters</TD></TR><TR><TD></TD><TD><A HREF=\"/SiteView/cgi/go.exe/SiteView/?page=counter&returnURL=" + URLEncoder.encode(returnURL) + "&maxcounters=" + nMaxCounters + "&counterobjects=" + counterObjects + "&type=NTCounter\">choose counters</A>");
     pCounters.setParameterOptions(false, true, 1, false);
     pCounters.isMultiLine = true;
     StringProperty astringproperty[] = {
         pCounters
     };
     addProperties("com.dragonflow.StandardMonitor.ADPerformanceMonitor", astringproperty);
     addClassElement("com.dragonflow.StandardMonitor.ADPerformanceMonitor", Rule.stringToClassifier("value0 == n/a\terror", true));
     addClassElement("com.dragonflow.StandardMonitor.ADPerformanceMonitor", Rule.stringToClassifier("always\tgood"));
     
     setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor","description",MonitorTypeValueReader.getValue(ADPerformanceMonitor.class.getName(), MonitorTypeValueReader.DESCRIPTION));
     //setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "description", "Monitors Microsoft Active Directory performance metrics.");
     
     setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "help", "ADPerfMon.htm");
     
     setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "title",MonitorTypeValueReader.getValue(ADPerformanceMonitor.class.getName(), MonitorTypeValueReader.TITLE) );
     //setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "title", "Active Directory Performance");
     
     setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "class", "ADPerformanceMonitor");
     
     setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "target", MonitorTypeValueReader.getValue(ADPerformanceMonitor.class.getName(), MonitorTypeValueReader.TARGET));
     //setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "target", "_serverName");
     
     setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "topazName", MonitorTypeValueReader.getValue(ADPerformanceMonitor.class.getName(), MonitorTypeValueReader.TOPAZTYPE));
     //setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "topazName", "Active Directory Perf");
     
     setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "classType",MonitorTypeValueReader.getValue(ADPerformanceMonitor.class.getName(), MonitorTypeValueReader.CLASSTYPE));
     //setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "classType", "beta");
     
     setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "topazType",MonitorTypeValueReader.getValue(ADPerformanceMonitor.class.getName(), MonitorTypeValueReader.TOPAZTYPE));
     //setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "topazType", "Application Server");
     
     setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "applicationType", MonitorTypeValueReader.getValue(ADPerformanceMonitor.class.getName(), MonitorTypeValueReader.APPLICATIONTYPE));
     setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "applicationType", "NTCounter");
     if(TextUtils.getValue(hashmap, "_allowADPerfromanceMonitor").length() <= 0 || !Platform.isWindows())
     {
         setClassProperty("com.dragonflow.StandardMonitor.ADPerformanceMonitor", "loadable", "false");
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