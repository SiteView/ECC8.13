package com.siteview.ecc.test;

import java.util.Enumeration;

import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;

import com.dragonflow.Utils.EmsDummyMonitor;

public class MonitorTest {
	public static void save(){
		saveHelp();
		saveStatus();
	}
	
	public static void saveHelp()
	{
		EmsDummyMonitor emsdummymonitor = new EmsDummyMonitor();
		
		Enumeration enumeration = emsdummymonitor.statusHelpMapping.keys();
		
		while(enumeration.hasMoreElements())
		{
			Object key = enumeration.nextElement();
			try{
				long id = Long.parseLong("" + key);
				Object message = emsdummymonitor.statusHelpMapping.get(key);
				saveHelp(id,message);
			}catch(Exception e)	{
				
			}
		}
		
	}
	
	private static void saveHelp(long id,Object message) throws Exception
	{
		GenericValue val = getDelegator().makeValue("SvMonitorStatusHelp");
		val.set("id", id);
		val.set("message", message);
		val.create();
	}
	public static void saveStatus()
	{
		EmsDummyMonitor emsdummymonitor = new EmsDummyMonitor();
		
		Enumeration enumeration = emsdummymonitor.statusMapping.keys();
		
		while(enumeration.hasMoreElements())
		{
			Object key = enumeration.nextElement();
			try{
				long id = Long.parseLong("" + key);
				Object message = emsdummymonitor.statusMapping.get(key);
				saveStatus(id,message);
			}catch(Exception e)	{
				
			}
		}
		
	}
	
	private static void saveStatus(long id,Object status) throws Exception
	{
		GenericValue val = getDelegator().makeValue("SvMonitorStatus");
		val.set("id", id);
		val.set("status", status);
		val.create();
	}	
	private static GenericDelegator localdelegator = null;
	private static GenericDelegator getDelegator()
	{
		if (localdelegator == null) localdelegator = GenericDelegator.getGenericDelegator("default");
		return localdelegator;
	}
}
