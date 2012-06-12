package com.dragonflow.Api;

import java.util.ArrayList;
import java.util.HashMap;

import org.ofbiz.base.util.Debug;


public class ApiForOfbiz
{
	public static final String module = ApiForOfbiz.class.getName();
	static public ArrayList<HashMap<String, String>> getMonitorsData()
	{		
		ArrayList<HashMap<String, String>> list = new ArrayList<HashMap<String, String>>();
		try
		{
			com.dragonflow.Api.APIMonitor apim = new APIMonitor();
			java.util.Collection collection = apim.getAllMonitors();
			java.util.Vector vector = (java.util.Vector) collection;

			com.dragonflow.SiteView.Monitor monitor;
			int index = 0;
			for (java.util.Iterator iterator = collection.iterator(); iterator.hasNext();)
			{
				monitor = (com.dragonflow.SiteView.Monitor) iterator.next();
				// add by hailong.yi 2008/6/10
				if (!monitor.isScheduleEnabled()) continue;
				
				HashMap<String, String> ndata = new HashMap<String, String>();
				ndata.put(new String("Name"), monitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pName));
				ndata.put(new String("GroupID"), monitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pOwnerID));
				ndata.put(new String("MonitorID"), monitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pID));
				ndata.put(new String("Type"), monitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pClass));
				ndata.put(new String("methodID"), monitor.getProperty(com.dragonflow.SiteView.AtomicMonitor.pMethodId));
				list.add(ndata);
			}
		} catch (java.lang.Exception e)
		{
			Debug.logError(e, module);
		}
		return list;
	}
	
	static public String getStr()
	{
		return new String("value test");
	}
	
	static public String getMonitorStr(int index)
	{
		String rstr= new String("");
		ArrayList<HashMap<String, String>> list= getMonitorsData();
		if(index>=list.size())
			return rstr;
		
		HashMap<String, String> ndata= list.get(index);
		rstr= "&nbsp;-- " + (index+1) + "th monitor --<BR>";
		for (String key : ndata.keySet())
			rstr+="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + key + "= \"" + ndata.get(key) + "\"<BR>";
		return rstr;
	}
	
	static public void DisplayAllMonitor()
	{
		ArrayList<HashMap<String, String>> list= getMonitorsData();
		System.out.println("\n\n ------------- Display All Monitor: " + list.size() + "------------------");
		int index=0;

		for(HashMap<String, String> ndata: list)
		{
			System.out.println(" -- " + ++index + "th monitor --");
			for (String key : ndata.keySet())
				System.out.println("        " + key + "= \"" + ndata.get(key) + "\"");
		}
		System.out.println(" ------------- Display All Monitor ------------------\n\n");
	}
}
