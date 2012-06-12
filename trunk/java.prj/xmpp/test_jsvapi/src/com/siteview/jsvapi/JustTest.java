package com.siteview.jsvapi;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Vector;

import com.focus.db.DBCon;
import com.focus.db.QueryResult;

public class JustTest {

	Jsvapi svapi = new Jsvapi();
	
	public static void main(String[] args) throws Exception{
	
		new JustTest().importMonitor("default");

	}
	private void importMonitor(String parentid) throws Exception {
		Vector<HashMap<String, String>> fmap = new Vector<HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();

		ndata.put("dowhat", "GetTreeData");
		ndata.put("parentid", parentid);
		ndata.put("onlySon", "true");

		boolean ret = svapi.GetForestData(fmap, ndata, estr);
		for (int i = 0; i < fmap.size(); i++) {
			HashMap<String, String> map = fmap.get(i);

			if (map.get("type").toString().equals("monitor"))
				importMonitorInstance( parentid, map);
			else if (map.get("has_son") != null
					&& map.get("has_son").toString().equals("true"))
				importMonitor( map.get("sv_id"));

		}
	}
	private void importMonitorInstance(String parentid, HashMap inMap)
			throws Exception {

		if (inMap.get("sv_monitortype").equals("")) {
			System.out.println("data error:monitor " + parentid + "."
					+ inMap.get("sv_name") + " no sv_monitortype\n");
			return;
		}
		HashMap<String, HashMap<String, String>> map = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();

		ndata.put("dowhat", "GetMonitor");
		ndata.put("id", inMap.get("sv_id").toString());
		boolean ret = svapi.GetUnivData(map, ndata, estr);
		
		Iterator iterator = map.keySet().iterator();
		  System.out.println("===================="); while
		  (iterator.hasNext()) { String key = iterator.next().toString();
		  System.out.println(key + "=" + map.get(key)); }
		 

		

	}
}
