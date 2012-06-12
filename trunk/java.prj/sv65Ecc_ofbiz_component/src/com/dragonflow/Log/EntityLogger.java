package com.dragonflow.Log;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Enumeration;

import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericEntityException;
import org.ofbiz.entity.GenericValue;

import jgl.Array;
import jgl.HashMap;

import com.dragonflow.Properties.PropertiedObject;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.MasterConfig;
import com.dragonflow.SiteView.SiteViewGroup;
import com.dragonflow.Utils.jglUtils;
import com.siteview.svecc.service.Log;

public class EntityLogger extends Logger {
	private static final SimpleDateFormat dateformat=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss S");
    public static EntityLogger logger = null;
    
    private static HashMap hashmapMasterConfig = null;

    public static String getServerName(){
    	return SiteViewGroup.getServerID(getMasterConfig());
    }
    public static HashMap getMasterConfig(){
    	if (hashmapMasterConfig == null) hashmapMasterConfig = MasterConfig.getMasterConfig();
    	return hashmapMasterConfig;
    }
    
	public void log(String title, Date date,
			PropertiedObject object) {
		writeLog(getLogValue(title, object, date));
	}

	public void log(String title, Date date, String str) {
		writeLog(getLogValue(title, str, date));
	}


	public void logCustom(PropertiedObject propertiedobject,
			Array array, String s, String s1, String s2, String s3) {
		logCustom(propertiedobject, array, s, s1, null, s2, s3);
	}

	public void logCustom(PropertiedObject propertiedobject,
			Array array, String s, String s1, String s2, String s3, String s4) {
		logCustom(propertiedobject, array, s, s1, s2, null, s3, s4);
	}

	public void logCustom(PropertiedObject object,
			Array array, String s, String s1, String s2, String s3, String s4,
			String s5) {
		writeLog(getLogValue("", object, new Date()));
		System.out.println("logCustom : propertiedobject=" + object + ",array=" + array 
				+ ",s1=" + s1
				+ ",s2=" + s2
				+ ",s3=" + s3
				+ ",s4=" + s4
				+ ",s5=" + s5
				);
	}
    public static String dateFormat(Date date)
    {
        return dateformat.format(date);
    }
    public void logLink(Date date, PropertiedObject object, String as[])
    {
    	writeLogLinks(getLogLinksValue(as, object, date));
    }
    private HashMap getLogValue(String title,String str,Date date)
    {
    	HashMap hashmap = getLogValue(title,(PropertiedObject) null, date);
    	hashmap.put("value1", str);
    	return hashmap;
    }

    private HashMap getLogValue(String title,PropertiedObject object,Date date)
    {
    	HashMap hashmap = new HashMap();
    	try{
        	hashmap.put("datex", dateFormat(date));
        	hashmap.put("serverName", getServerName());
        	
        	if (object!=null){
            	hashmap.put("className", getValue(object.getProperty(com.dragonflow.SiteView.AtomicMonitor.pClass),object));
            	hashmap.put("sample", getValue(object.getProperty(com.dragonflow.SiteView.AtomicMonitor.pSample),object));
            	
            	Array array = object.getLogProperties();
            	Enumeration<?> properties = array.elements();
            	
            	int index = 0;
            	while(properties.hasMoreElements())
            	{
            		StringProperty property = (StringProperty)properties.nextElement();
            		if (property != null) 
            		if (index == 0){
                    	hashmap.put("category", getValue(property,object));
            		}else if (index == 1){
                    	hashmap.put("groupName", getValue(property,object));
            		}else if (index == 2){
                    	hashmap.put("monitorName", getMonitorName(object));
            		}else if (index == 3){
                    	hashmap.put("status", getValue(property,object));
            		}else if (index == 4){
                    	hashmap.put("monitorId", getValue(property,object));
            		}else if (index == 5){
                    	hashmap.put("value1", getValue(property,object));
            		}else if (index == 6){
                    	hashmap.put("value2", getValue(property,object));
            		}else if (index == 7){
                    	hashmap.put("value3", getValue(property,object));
            		}else if (index == 8){
                    	hashmap.put("value4", getValue(property,object));
            		}else if (index == 9){
                    	hashmap.put("value5", getValue(property,object));
            		}else if (index == 10){
                    	hashmap.put("value6", getValue(property,object));
            		}else if (index == 11){
                    	hashmap.put("value7", getValue(property,object));
            		}else if (index == 12){
                    	hashmap.put("value8", getValue(property,object));
            		}else if (index == 13){
                    	hashmap.put("value9", getValue(property,object));
            		}else if (index == 14){
                    	hashmap.put("value10", getValue(property,object));
            		}
            		index ++;
            	}
        	}
    	}catch (Exception e){
    		e.printStackTrace();
    	}
    	return hashmap;
    }
    
	private static final int maxStringLength = 255;
    private HashMap getLogLinksValue(String params[],PropertiedObject object,Date date)
    {
    	HashMap hashmap = new HashMap();
    	try{
        	hashmap.put("datex", dateFormat(date));
        	hashmap.put("serverName", getServerName());
        	
        	if (object!=null){
            	hashmap.put("className", getValue(object.getProperty(com.dragonflow.SiteView.AtomicMonitor.pClass),object));
               	hashmap.put("sample", getValue(object.getProperty(com.dragonflow.SiteView.AtomicMonitor.pSample),object));
            	hashmap.put("groupName", getValue(object.getProperty(com.dragonflow.SiteView.AtomicMonitor.pOwnerID),object));
            	hashmap.put("monitorName", getMonitorName(object));
            	hashmap.put("monitorId", getValue(object.getProperty(com.dragonflow.SiteView.AtomicMonitor.pID),object));

            	for(int index = 0; index < params.length; index++)
            	{
                    String param = params[index];
                    if(param.length() > maxStringLength)
                    {
                    	param = param.substring(0, maxStringLength);
                    }
            		if (index == 0){
                    	hashmap.put("url", param);
            		}else if (index == 1){
                    	hashmap.put("status", param);
            		}else if (index == 2){
                    	hashmap.put("contentType", param);
            		}else if (index == 3){
                    	hashmap.put("referenceCount", param);
            		}else if (index == 4){
                    	hashmap.put("isExternal", param);
            		}else if (index == 5){
                    	hashmap.put("duration", param);
            		}else if (index == 6){
                    	hashmap.put("contentSize", param);
            		}else if (index == 7){
                    	hashmap.put("source", param);
            		}            		
            	}
        	}
    	}catch (Exception e){
    		e.printStackTrace();
    	}
    	return hashmap;
    }    
    private String getValue(Object val,PropertiedObject object)
    {
    	if (val instanceof StringProperty) {
    		return object.getProperty((StringProperty)val);
    	}
    	if (val instanceof String) return (String)val;
    	return "";
    }

    private void writeLog(HashMap data)
    {
    	try {
    		Log.addLog(jglUtils.fromJgl(data));
    	} catch (Exception e) {
    		e.printStackTrace();
    	}
//     	try {
//     	   	if (data == null) return;
//        	GenericValue val = getDelegator().makeValue("SvLog");
//        	Enumeration<?> enumeration = data.keys();
//        	while(enumeration.hasMoreElements())
//        	{
//        		String key = (String)enumeration.nextElement();
//        		val.set(key, data.get(key));
//        	}
//			val.create();
//		} catch (Exception e) {
//			e.printStackTrace();
//		}
    }
    
    private static void writeLogLinks(HashMap data)
    {
     	try {
     	   	if (data == null) return;
        	GenericValue val = getDelegator().makeValue("SvLogLinks");
        	Enumeration<?> enumeration = data.keys();
        	while(enumeration.hasMoreElements())
        	{
        		String key = (String)enumeration.nextElement();
        		val.set(key, data.get(key));
        	}
			val.create();
		} catch (GenericEntityException e) {
		}
    }    
	private static GenericDelegator localdelegator = null;
	private static GenericDelegator getDelegator()
	{
		if (localdelegator == null) localdelegator = GenericDelegator.getGenericDelegator("default");
		return localdelegator;
	}
	
}
