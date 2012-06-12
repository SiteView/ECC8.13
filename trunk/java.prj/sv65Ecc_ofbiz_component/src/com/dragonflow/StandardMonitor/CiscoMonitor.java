/*
 * 
 * Created on 2005-3-7 0:52:16
 *
 * CiscoMonitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>CiscoMonitor</code>
 * 
 * @author 
 * @version 0.0
 *
 *
 */
import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Log.LogManager;
import com.dragonflow.Page.CGI;
import com.dragonflow.Properties.ScalarProperty;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.BrowsableSNMPBase;
import com.dragonflow.SiteView.Rule;
import com.dragonflow.SiteViewException.SiteViewException;
import com.dragonflow.Utils.Snmp.BrowsableMIB;
import com.siteview.ecc.util.MonitorTypeValueReader;

import java.util.Vector;
import jgl.Array;

public class CiscoMonitor extends BrowsableSNMPBase
{

 private String ciscoWorksMIB;

 public CiscoMonitor()
 {
     ciscoWorksMIB = "CISCOWORKS-MIB.my";
 }

 public Array getConnectionProperties()
 {
     Array array = super.getConnectionProperties();
     return array;
 }

 protected String getMonitorType()
 {
     return "Cisco";
 }

 public Vector getScalarValues(ScalarProperty scalarproperty, HTTPRequest httprequest, CGI cgi)
     throws SiteViewException
 {
     if(scalarproperty == pMIB)
     {
         Vector vector = new Vector();
         try
         {
             BrowsableMIB browsablemib = BrowsableMIB.getInstance();
             if(browsablemib.containsMIB(ciscoWorksMIB))
             {
                 vector.add(ciscoWorksMIB);
                 vector.add(ciscoWorksMIB);
             }
         }
         catch(Exception exception)
         {
             LogManager.log("Error", "CiscoWorks Monitor could not get BrowsableMIB instance: " + exception.getMessage());
         }
         if(vector.size() == 0)
         {
             vector.add("No MIBs Available");
             vector.add("No MIBs Available");
         }
         return vector;
     } else
     {
         return super.getScalarValues(scalarproperty, httprequest, cgi);
     }
 }

 static 
 {
     StringProperty astringproperty[] = new StringProperty[0];
     addProperties("com.dragonflow.StandardMonitor.CiscoMonitor", astringproperty);
     addClassElement("com.dragonflow.StandardMonitor.CiscoMonitor", Rule.stringToClassifier("countersInError > 0\terror"));
     addClassElement("com.dragonflow.StandardMonitor.CiscoMonitor", Rule.stringToClassifier("always\tgood"));
     
     setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "description", MonitorTypeValueReader.getValue(CiscoMonitor.class.getName(), MonitorTypeValueReader.DESCRIPTION));
     //setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "description", "Monitors Cisco Works server metrics.");
     
     setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "help", "CiscoWorksMon.htm");
     
     setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "title", MonitorTypeValueReader.getValue(CiscoMonitor.class.getName(), MonitorTypeValueReader.TITLE));
     //setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "title", "Cisco Works");
     
     setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "class", "CiscoMonitor");
     
     setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor","target",MonitorTypeValueReader.getValue(CiscoMonitor.class.getName(), MonitorTypeValueReader.TARGET));
     //setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "target", "_server");
     
     setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "topazName", MonitorTypeValueReader.getValue(CiscoMonitor.class.getName(), MonitorTypeValueReader.TOPAZNAME));
     //setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "topazName", "Cisco Works");
     
     setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "classType", MonitorTypeValueReader.getValue(CiscoMonitor.class.getName(), MonitorTypeValueReader.CLASSTYPE));
     //setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "classType", "application");
     
     setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "topazType", MonitorTypeValueReader.getValue(CiscoMonitor.class.getName(), MonitorTypeValueReader.TOPAZTYPE));
     //setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "topazType", "System Resources");
     
     setClassProperty("com.dragonflow.StandardMonitor.CiscoMonitor", "loadable", "true");
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
