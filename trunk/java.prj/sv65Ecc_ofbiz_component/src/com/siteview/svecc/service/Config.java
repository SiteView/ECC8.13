package com.siteview.svecc.service;

import java.util.Enumeration;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityOperator;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

import com.dragonflow.SiteView.MasterConfig;

public class Config extends BaseClass{
	public static final String module = Config.class.getName();
	public static Map<?, ?> getConfig(DispatchContext ctx, Map<?, ?> context) {
		try {
			String attrName = (String) getNotOptionalValue(context,"attrName");
			Long idx = (Long) getNotOptionalValue(context,"idx");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getConfig(attrName,idx,ctx.getDelegator()));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getConfig: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static String getConfig(String attrName,String idx)throws Exception {
		return getConfig(attrName,convertIndex(idx));
	}
	public static String getConfig(String attrName,Long idx)throws Exception {
		return getConfig(attrName,idx,getGenericDelegator());
	}
	
	private static List<GenericValue> userlist = null;
	
	public static String getConfig(String attrName,Long idx,GenericDelegator delegator)throws Exception 
	{
		if (attrName == null) throwException(THROW_TYPE_OPTIONAL_PARAM,"attrName"); 
		if (idx == null) throwException(THROW_TYPE_OPTIONAL_PARAM,"idx");
		if (userlist == null){
			userlist = delegator.findList("SvMasterConfig", null, null, null, null, false);
		}
		for (GenericValue val : userlist)
		{
			if (attrName.equals(val.getString("attrName")) && idx.equals(val.getLong("idx"))){
				String retval = val.getString("attrValue");
				if (retval!=null)return retval;
			}
		}
		return "";
	}

	public static Map<?, ?> getConfigByName(DispatchContext ctx, Map<?, ?> context) {
		try {
			String attrName = (String) getNotOptionalValue(context,"attrName");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getConfigByName(attrName,ctx.getDelegator()));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getConfig: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static Map<String,Object> getConfigByName(String attrName)throws Exception {
		return getConfigByName(attrName,getGenericDelegator());
	}
	public static Map<String,Object> getConfigByName(String attrName,GenericDelegator delegator)throws Exception 
	{
		if (attrName == null) throwException(THROW_TYPE_OPTIONAL_PARAM,"attrName"); 

		if (userlist == null){
			userlist = delegator.findList("SvMasterConfig", null, null, UtilMisc.toList("attrName","idx"), null, false);
		}
		
		Map<String,Object> map = new LinkedHashMap<String,Object>();
		for (GenericValue val : userlist)
		{
			if (attrName.equals(val.getString("attrName"))){
				String retidx = val.getString("idx");
				String retval = val.getString("attrValue");
				if (retval == null) continue;
				map.put(retidx, retval);
			}
		}
		return map;
	}
	public static Map<?, ?> updConfig(DispatchContext ctx, Map<?, ?> context) {
		try {
			String attrName = (String) getNotOptionalValue(context,"attrName");
			Long idx = (Long) getNotOptionalValue(context,"idx");
			String value = (String) getOptionalValue(context,"value");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			updConfig(attrName,idx,value,ctx.getDelegator());
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error updConfig: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static void updConfig(String attrName,String idx,String value)throws Exception {
		updConfig(attrName,convertIndex(idx),value);
	}
	public static void updConfig(String attrName,Long idx,String value)throws Exception {
		updConfig(attrName,idx,value,getGenericDelegator());
	}
	public static void updConfig(String attrName,Long idx,String value,GenericDelegator delegator)throws Exception {
		try{
			if (attrName == null) throwException(THROW_TYPE_OPTIONAL_PARAM,"attrName"); 
			if (idx == null) throwException(THROW_TYPE_OPTIONAL_PARAM,"idx"); 
			EntityCondition entityCondition = EntityCondition.makeCondition(
					UtilMisc.toList(
							EntityCondition.makeCondition("attrName",EntityOperator.EQUALS,attrName),
							EntityCondition.makeCondition("idx",EntityOperator.EQUALS,idx)
					),
					EntityOperator.AND
			);
			List<GenericValue> retlist = delegator.findList("SvMasterConfig", entityCondition, null, null, null, false);
			for (GenericValue val : retlist)
			{
				if (value == null) {
					val.remove();
					return;
				}
				val.set("attrValue", value);
				val.store();
				return;
			}
			GenericValue val = delegator.makeValue("SvMasterConfig");
			val.set("attrName", attrName);
			val.set("idx", idx);
			val.set("attrValue", value);
			val.create();
		}finally{
			refrashData();
		}
	}
	private static void refrashData()throws Exception
	{
		clearCache();
		MasterConfig.clearConfigCache();
	}
	
	public static void clearCache()
	{
		userlist = null;
	}

	
    public static String configGet(String attrName)
    {
    	try {
    		Map<String, Object> map = Config.getConfigByName(attrName);
    		for (String idx : map.keySet()){
    			return (String) map.get(idx);
    		}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
    }
    public static Map<String, Object> configGetAll(String attrName)
    {
    	try {
    		return Config.getConfigByName(attrName);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return new HashMap<String, Object>();
    }
    public static void configPut(String attrName ,String value)
    {
    	try {
    		Map<String, Object> map = Config.getConfigByName(attrName);
    		if (map.size()>0){
        		for (String idx : map.keySet()){
        			Config.updConfig(attrName, idx, value);
        		}
    		}else{
    			Config.updConfig(attrName, "1", value);
    		}
		} catch (Exception e) {
			e.printStackTrace();
		}
    }
    public static void configAdd(String attrName ,String value)
    {
    	try {
        	Map<String, Object> map = Config.getConfigByName(attrName);
 			Config.updConfig(attrName, getNewDistinctKey(map.keySet()), value);
		} catch (Exception e) {
			e.printStackTrace();
		}
    }
    public static void configAdd(jgl.HashMap map)
    {
    	try {
    		Enumeration<?> enumeration = map.keys();
    		while(enumeration.hasMoreElements()){
    			Object key = enumeration.nextElement();
    			Object val = map.get(key);
    			if (val instanceof String){
    				configAdd((String)key,(String)val);
    			}else if (val instanceof jgl.Array){
    				Enumeration<?> values = ((jgl.Array)val).elements();
    				while(values.hasMoreElements()){
    					Object value = values.nextElement();
    					if (value instanceof String){
    						configAdd((String)key,(String)value);
    					}
    				}
    			}
    		}
		} catch (Exception e) {
			e.printStackTrace();
		}
    }
    public static void configPut(jgl.HashMap map)
    {
    	try {
    		Enumeration<?> enumeration = map.keys();
    		while(enumeration.hasMoreElements()){
    			Object key = enumeration.nextElement();
				configDel((String)key);
    			Object val = map.get(key);
    			if (val instanceof String){
    				configAdd((String)key,(String)val);
    			}else if (val instanceof jgl.Array){
    				Enumeration<?> values = ((jgl.Array)val).elements();
    				while(values.hasMoreElements()){
    					Object value = values.nextElement();
    					if (value instanceof String){
    						configAdd((String)key,(String)value);
    					}
    				}
    			}
    		}
		} catch (Exception e) {
			e.printStackTrace();
		}
    }
    public static void configDel(String attrName)
    {
    	try {
        	Map<String, Object> map = Config.getConfigByName(attrName);
    		for (String idx : map.keySet()){
    			Config.updConfig(attrName, idx, null);
    		}
		} catch (Exception e) {
			e.printStackTrace();
		}
    }
    
    public static String getNewDistinctKey(Set<String> keys){
    	return getNewDistinctKey(keys,"1");
    }
    
    private static String getNewDistinctKey(Set<String> keys,String initKey){
    	String newkey = initKey;
   		if (isExistKey(keys,newkey)){
   			newkey = "" + (Long.parseLong(newkey) + 1);
   			return getNewDistinctKey(keys,newkey);
   		}
   		return newkey;
    }
    private static boolean isExistKey(Set<String> keys,String newkey){
   		for (String key : keys){
			if (newkey.equals(key)){
				return true;
			}
		}
   		return false;
    }	
}
