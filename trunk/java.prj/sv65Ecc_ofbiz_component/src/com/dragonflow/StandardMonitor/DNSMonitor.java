/*
 * 
 * Created on 2005-3-7 1:00:50
 *
 * DNSMonitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>DNSMonitor</code>
 * 
 * @author 
 * @version 0.0
 *
 *
 */
import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Properties.NumericProperty;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.*;
import com.dragonflow.Utils.I18N;
import com.dragonflow.Utils.TextUtils;
import com.siteview.ecc.util.MonitorIniValueReader;
import com.siteview.ecc.util.MonitorTypeValueReader;

import java.util.Enumeration;
import java.util.Vector;
import jgl.Array;
import jgl.HashMap;

public class DNSMonitor extends AtomicMonitor
{

 static StringProperty pServer;
 static StringProperty pHostName;
 static StringProperty pHostIP;
 static StringProperty pRoundTripTime;
 static StringProperty pStatus;
 static StringProperty pStatusText;
 private static final String DEFAULT_SERVER_TAGS[] = {
     "Server:", "Servidor:", "Serveur:", "Serveur\377:"
 };
 private static final String DNS_SERVER_TAGS_SETTING = "_dnsServerTags";
 private static String serverTags[];
 private static final String DEFAULT_NAME_TAGS[] = {
     "Name:", "Nombre:", "Navn:", "Nome:", "Nom :", "Nom\377:"
 };
 private static final String DNS_NAME_TAGS_SETTING = "_dnsNameTags";
 private static String nameTags[];

 public DNSMonitor()
 {
 }

 public String getHostname()
 {
     return getProperty(pServer);
 }

 public String getTestURL()
 {
     return "/SiteView/cgi/go.exe/SiteView?page=DNS&host=" + getProperty(pServer) + "&misc=" + getProperty(pHostName) + "&group=" + HTTPRequest.encodeString(I18N.toDefaultEncoding(getProperty(pGroupID)));
 }

 protected boolean update()
 {
     String s = getProperty(pServer);
     String s1 = getProperty(pHostName);
     String s2 = getProperty(pHostIP);
     boolean flag = true;
     String as[] = Platform.dnsLookup(s, s1, s2);
     int i = TextUtils.toInt(as[0]);
     long l = TextUtils.toInt(as[1]);
     String s3 = lookupStatus(i);
     synchronized(this)
     {
         setProperty(pStatus, i);
         setProperty(pStatusText, s3);
         if(i == kURLok)
         {
             if(l < 10L)
             {
                 l = 10L;
             }
             setProperty(pStateString, TextUtils.floatToString((float)l / 1000F, 2) + " sec");
             setProperty(pRoundTripTime, String.valueOf(l));
             setProperty(pMeasurement, getMeasurement(pRoundTripTime, 4000L));
         } else
         {
             setProperty(pStateString, s3);
             setProperty(pMeasurement, String.valueOf(0));
             setProperty(pRoundTripTime, "n/a");
             setProperty(pNoData, "n/a");
         }
     }
     return flag;
 }

 public Array getLogProperties()
 {
     Array array = super.getLogProperties();
     array.add(pStatus);
     array.add(pRoundTripTime);
     array.add(pStatusText);
     return array;
 }

 public String verify(StringProperty stringproperty, String s, HTTPRequest httprequest, HashMap hashmap)
 {
     if(stringproperty == pServer)
     {
         if(s.length() == 0)
         {
             hashmap.put(stringproperty, stringproperty.getLabel() + " missing");
         } else
         if(TextUtils.hasLetters(s))
         {
             hashmap.put(stringproperty, "no letters are allowed");
         } else
         if(TextUtils.hasSpaces(s))
         {
             hashmap.put(stringproperty, "no spaces are allowed");
         }
         return s;
     }
     if(stringproperty == pHostName)
     {
         if(s.length() == 0)
         {
             hashmap.put(stringproperty, stringproperty.getLabel() + " missing");
         } else
         if(TextUtils.hasSpaces(s))
         {
             hashmap.put(stringproperty, "no spaces are allowed");
         }
         return s;
     }
     if(stringproperty == pHostIP)
     {
         if(TextUtils.hasLetters(s))
         {
             hashmap.put(stringproperty, "no letters are allowed");
         } else
         if(TextUtils.hasSpaces(s))
         {
             hashmap.put(stringproperty, "no spaces are allowed");
         }
         return s;
     } else
     {
         return super.verify(stringproperty, s, httprequest, hashmap);
     }
 }

 public String getProperty(StringProperty stringproperty)
     throws NullPointerException
 {
     if(stringproperty == pDiagnosticText)
     {
         if(getProperty(pCategory).equals("good"))
         {
             return "";
         } else
         {
             return diagnostic(getProperty(pServer), getPropertyAsInteger(pStatus));
         }
     } else
     {
         return super.getProperty(stringproperty);
     }
 }

 public Enumeration getRuntimeProperties(Vector vector, boolean flag)
 {
     vector.add("diagnosticText");
     return super.getRuntimeProperties(vector, flag);
 }

 public static String[] getNameTagsOptions()
 {
     return nameTags;
 }

 public static String[] getServerTagsOptions()
 {
     return serverTags;
 }

 static 
 {
     serverTags = null;
     nameTags = null;
     serverTags = TextUtils.getSettingAsStringArray("_dnsServerTags");
     if(serverTags == null)
     {
         serverTags = DEFAULT_SERVER_TAGS;
     }
     nameTags = TextUtils.getSettingAsStringArray("_dnsNameTags");
     if(nameTags == null)
     {
         nameTags = DEFAULT_NAME_TAGS;
     }
     pServer = new StringProperty("_server");
     pServer.setDisplayText(MonitorIniValueReader.getValue(DNSMonitor.class.getName(), "_server", MonitorIniValueReader.LABEL), MonitorIniValueReader.getValue(DNSMonitor.class.getName(), "_server", MonitorIniValueReader.DESCRIPTION));
     //pServer.setDisplayText("DNS Server Address", "IP address of the DNS server (example: 206.168.191.1)");
     pServer.setParameterOptions(true, 1, false);
     
     pHostName = new StringProperty("_hostname");
     String hostname_description = MonitorIniValueReader.getValue(DNSMonitor.class.getName(), "_hostname", MonitorIniValueReader.DESCRIPTION);
     hostname_description=hostname_description.replaceAll("1%", Platform.exampleDomain);
     pHostName.setDisplayText(MonitorIniValueReader.getValue(DNSMonitor.class.getName(), "_hostname", MonitorIniValueReader.LABEL), hostname_description);
     //pHostName.setDisplayText("Host Name", "the hostname to lookup (example: demo." + Platform.exampleDomain + ")");
     pHostName.setParameterOptions(true, 2, false);
     
     pHostIP = new StringProperty("_content");
     pHostIP.setDisplayText(MonitorIniValueReader.getValue(DNSMonitor.class.getName(), "_content", MonitorIniValueReader.LABEL), MonitorIniValueReader.getValue(DNSMonitor.class.getName(), "_content", MonitorIniValueReader.DESCRIPTION));
     //pHostIP.setDisplayText("Host Address", "optional IP address or list of addresses to verify against for the hostname (examples 206.168.191.21 or 206.168.191.21,206.168.191.46)");
     pHostIP.setParameterOptions(true, 3, true);
     
     pRoundTripTime = new NumericProperty("roundTripTime", "0", MonitorIniValueReader.getValue(DNSMonitor.class.getName(), "roundTripTime", MonitorIniValueReader.UNIT));
     //pRoundTripTime = new NumericProperty("roundTripTime", "0", "milliseconds");
     pRoundTripTime.setLabel(MonitorIniValueReader.getValue(DNSMonitor.class.getName(), "roundTripTime", MonitorIniValueReader.LABEL));
     //pRoundTripTime.setLabel("round trip time");
     pRoundTripTime.setStateOptions(1);
     
     pStatus = new StringProperty("status");
     pStatusText = new StringProperty("statusText");
     StringProperty astringproperty[] = {
         pServer, pHostName, pHostIP, pRoundTripTime, pStatus, pStatusText
     };
     addProperties("com.dragonflow.StandardMonitor.DNSMonitor", astringproperty);
     addClassElement("com.dragonflow.StandardMonitor.DNSMonitor", Rule.stringToClassifier("status = 200\tgood"));
     addClassElement("com.dragonflow.StandardMonitor.DNSMonitor", Rule.stringToClassifier("status <> 200\terror"));
     
     setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "description", MonitorTypeValueReader.getValue(DNSMonitor.class.getName(), MonitorTypeValueReader.DESCRIPTION));
     //setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "description", "Verifies that a DNS server is working.");
     
     setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "help", "DnsMon.htm");
     
     setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "title", MonitorTypeValueReader.getValue(DNSMonitor.class.getName(), MonitorTypeValueReader.TITLE));
     //setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "title", "DNS");
     
     setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "class", "DNSMonitor");
     
     setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "target", MonitorTypeValueReader.getValue(DNSMonitor.class.getName(), MonitorTypeValueReader.TARGET));
     //setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "target", "_server");
     
     setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "toolName", MonitorTypeValueReader.getValue(DNSMonitor.class.getName(), MonitorTypeValueReader.TOOLNAME));
     //setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "toolName", "DNS Lookup");
     
     setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "topazName", MonitorTypeValueReader.getValue(DNSMonitor.class.getName(), MonitorTypeValueReader.TOPAZNAME));
     //setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "topazName", "DNS");
     
     setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "topazType", MonitorTypeValueReader.getValue(DNSMonitor.class.getName(), MonitorTypeValueReader.TOPAZTYPE));
     //setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "topazType", "System Resources");
     
     setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "toolDescription", MonitorTypeValueReader.getValue(DNSMonitor.class.getName(), MonitorTypeValueReader.TOOLDESCRIPTION));
     //setClassProperty("com.dragonflow.StandardMonitor.DNSMonitor", "toolDescription", "Test a DNS to see if it can resolve a domain name.");
     StringProperty astringproperty1[] = {
         pRoundTripTime, pStatusText
     };
     setClassPropertyByObject("com.dragonflow.StandardMonitor.DNSMonitor", "history", astringproperty1);
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
