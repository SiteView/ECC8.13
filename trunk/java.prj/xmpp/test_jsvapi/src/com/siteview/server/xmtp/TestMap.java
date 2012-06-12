package com.siteview.server.xmtp;

import java.util.HashMap;

public class TestMap {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		//HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		/*ndata.put("dowhat", "LoadResourceByKeys");
		ndata.put("needkeys", "IDS_Close,IDS_Saturday");
		ndata.put("language", "default");*/
		
		
		System.out.println("\ntry QueryRecordsByCount ...");
		HashMap<String, String> ndata = new HashMap<String, String>();
		ndata.put("dowhat", "QueryRecordsByCount");
		ndata.put("id", "alertlogs");
		ndata.put("count", "50010");
		
		
		//boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		/*HashMap map=new HashMap();
		HashMap map1=new HashMap();
		HashMap map2=new HashMap();
		map1.put("key1", "{v}alue1");
		map1.put("key2", "valu{e}2");
		map2.put("k1", "v1");
		map2.put("k2", "v2");
		map.put("0", "ֲ,key1={v}alue1}");
		map.put("1", map1);
		map.put("2", map2);
		System.out.print(map.toString());*/
		String str=Map2String.toString(ndata);
		System.out.println(str);
		
		System.out.println(Map2String.toMap(str));
		
		
	}

}
