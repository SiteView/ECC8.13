/*
 * 
 * Created on 2005-3-7 0:58:57
 *
 * DB2Monitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>DB2Monitor</code>
 * 
 * @author 
 * @version 0.0
 *
 *
 */
import com.dragonflow.Properties.BrowsableProperty;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.*;
import com.siteview.ecc.util.MonitorIniValueReader;
import com.siteview.ecc.util.MonitorTypeValueReader;

import jgl.Array;

public class DB2Monitor extends BrowsableExeBase
{

 static BrowsableProperty pBrowseCounters;
 static StringProperty pUsername;
 static StringProperty pPassword;
 static StringProperty pInstance;
 static StringProperty pDb2Server;
 static String monDll = "db2mon_adapter.dll";

 public DB2Monitor()
 {
 }

 public Array getConnectionProperties()
 {
     Array array = new Array();
     array.add(pDb2Server);
     array.add(pUsername);
     array.add(pPassword);
     array.add(pInstance);
     return array;
 }

 public String getHostname()
 {
     return getProperty(pDb2Server);
 }

 protected String getMonDll()
 {
     return monDll;
 }

 public static void main(String args[])
 {
 }

 static 
 {
     Array array = new Array();
     pDb2Server = new StringProperty("_server", "");
     pDb2Server.setDisplayText(MonitorIniValueReader.getValue(DB2Monitor.class.getName(), "_server", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(DB2Monitor.class.getName(), "_server", MonitorIniValueReader.DESCRIPTION));
     //pDb2Server.setDisplayText("Server", "DB2 server name.");
     pDb2Server.setParameterOptions(false, true, BrowsableBase.COUNTER_PROPERTY_INDEX + 1, false);
     array.add(pDb2Server);
     
     pUsername = new StringProperty("_usr");
     pUsername.setDisplayText(MonitorIniValueReader.getValue(DB2Monitor.class.getName(), "_usr", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(DB2Monitor.class.getName(), "_usr", MonitorIniValueReader.DESCRIPTION));
     //pUsername.setDisplayText("Username", "Enter the Username for Db2");
     pUsername.setParameterOptions(false, true, 2, false);
     array.add(pUsername);     
     
     pPassword = new StringProperty("_pwd");
     pPassword.setDisplayText(MonitorIniValueReader.getValue(DB2Monitor.class.getName(), "_pwd", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(DB2Monitor.class.getName(), "_pwd", MonitorIniValueReader.DESCRIPTION));
     //pPassword.setDisplayText("Password", "Enter the Password for Db2");
     pPassword.setParameterOptions(false, true, 3, false);
     pPassword.isPassword = true;
     array.add(pPassword);
     
     pInstance = new StringProperty("_instance");
     pInstance.setDisplayText(MonitorIniValueReader.getValue(DB2Monitor.class.getName(), "_instance", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(DB2Monitor.class.getName(), "_instance", MonitorIniValueReader.DESCRIPTION));
     //pInstance.setDisplayText("Node Name", "Enter the Node Name for Db2");
     pInstance.setParameterOptions(false, true, 4, false);
     array.add(pInstance);
     StringProperty astringproperty[] = new StringProperty[array.size()];
     for(int i = 0; i < array.size(); i++)
     {
         astringproperty[i] = (StringProperty)array.at(i);
     }

     String s = (com.dragonflow.StandardMonitor.DB2Monitor.class).getName();
     addProperties(s, astringproperty);
     addClassElement(s, Rule.stringToClassifier("countersInError > 0\terror"));
     addClassElement(s, Rule.stringToClassifier("always\tgood"));
     
     setClassProperty(s, "description", MonitorTypeValueReader.getValue(DB2Monitor.class.getName(), MonitorTypeValueReader.DESCRIPTION));
     //setClassProperty(s, "description", "Monitors DB2 Database server performance metrics.");
     
     setClassProperty(s, "help", "db2Mon.htm");
     
     setClassProperty(s, "title", MonitorTypeValueReader.getValue(DB2Monitor.class.getName(), MonitorTypeValueReader.TITLE));
     //setClassProperty(s, "title", "DB2");
     
     setClassProperty(s, "class", "DB2Monitor");
     
     setClassProperty(s, "target", MonitorTypeValueReader.getValue(DB2Monitor.class.getName(), MonitorTypeValueReader.TARGET));
     //setClassProperty(s, "target", "_server");
     
     setClassProperty(s, "topazName", MonitorTypeValueReader.getValue(DB2Monitor.class.getName(), MonitorTypeValueReader.TOPAZNAME));
     //setClassProperty(s, "topazName", "cm_db2_mon");
     
     setClassProperty(s, "classType", MonitorTypeValueReader.getValue(DB2Monitor.class.getName(), MonitorTypeValueReader.CLASSTYPE));
     //setClassProperty(s, "classType", "application");
     
     setClassProperty(s, "topazType", MonitorTypeValueReader.getValue(DB2Monitor.class.getName(), MonitorTypeValueReader.TOPAZTYPE));
     //setClassProperty(s, "topazType", "Database Server");
     if(Platform.isWindows())
     {
         setClassProperty(s, "loadable", "true");
     } else
     {
         setClassProperty(s, "loadable", "false");
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