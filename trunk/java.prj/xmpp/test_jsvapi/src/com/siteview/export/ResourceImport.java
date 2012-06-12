package com.siteview.export;

import java.util.HashMap;
import java.util.Iterator;

import com.focus.util.Util;
import com.siteview.jsvapi.Jsvapi;

public class ResourceImport {

	Jsvapi svapi = new Jsvapi();
	public static StringBuffer errorMsg = new StringBuffer();
	
	HashMap<String, String> enMap = new HashMap<String, String>();
	HashMap<String, String> zhMap = new HashMap<String, String>();
	HashMap<String, String> japMap = new HashMap<String, String>();

	public static void main(String[] args) throws Exception{
		ResourceImport resource = new ResourceImport();
		resource.run();
		System.out.println(resource.errorMsg);
	}

	public void run() throws Exception
	{
		//"EccUiLabels.xml"
			readToMap("english",enMap);
			readToMap("english-ForTpl",enMap);
			readToMap("chinese",zhMap);
			readToMap("chinese-ForTpl",zhMap);
			readToMap("japanese",japMap);
			readToMap("japanese-ForTpl",japMap);
			
			StringBuffer sb=new StringBuffer();
			sb.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
			sb.append("<resource xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n");
			
			genXml(sb);
			genXml(sb);
			genXml(sb);
			
			Util.writeFile("c:/EccUiLabels.xml", sb.toString());
			System.out.println("ok,see c:/EccUiLabels.xml");
			Runtime.getRuntime().exec("write c:\\EccUiLabels.xml");
	}
    private void genXml(StringBuffer sb)
    {
		for (Iterator iterator = zhMap.keySet().iterator(); iterator.hasNext();) 
		{
			String key=iterator.next().toString();
			String value=zhMap.get(key).toString();
		    sb.append("<property key=\"").append(key).append("\">\n");
            sb.append("<value xml:lang=\"").append("zh").append("\">").append(value).append("</value>\n");
            if(enMap.get(key)!=null)
            	sb.append("<value xml:lang=\"").append("en").append("\">").append(enMap.get(key)).append("</value>\n");
            if(japMap.get(key)!=null)
            	sb.append("<value xml:lang=\"").append("ja").append("\">").append(japMap.get(key)).append("</value>\n");
            
            sb.append("</property>\n");
		}
		sb.append("</resource>");
    	
    }
	private void readToMap(String languageKey, HashMap outmap) 
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		ndata.put("dowhat", "LoadResource"); //ByKeys
		ndata.put("language",languageKey);
		svapi.GetUnivData(fmap, ndata, estr);

		HashMap map = fmap.get("property");
		
		if(map==null)
		{
			errorMsg.append(" Ù–‘¥ÌŒÛ:"+languageKey+"√ª”–property");
			svapi.DisplayUtilMapInMap(fmap);
			return;
		}
		
		for (Iterator iterator = map.keySet().iterator(); iterator.hasNext();) {
			String key = iterator.next().toString();
			String value = map.get(key).toString();
			outmap.put(key, value);
		}
		
	}
}
