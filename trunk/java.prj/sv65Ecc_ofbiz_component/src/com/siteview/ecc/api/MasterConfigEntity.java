package com.siteview.ecc.api;

import java.util.Enumeration;
import java.util.List;

import jgl.Array;
import jgl.HashMap;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityOperator;

import com.dragonflow.Properties.HashMapOrdered;

public class MasterConfigEntity extends EntityBase{
	public static Array get()throws Exception
	{
		List<GenericValue> list = getAll();
		
		Array retlist = new Array();
		
		HashMapOrdered hashMap = new HashMapOrdered(true);
		for (GenericValue val : list)
		{
			Object key = val.getString("attrName");
			if (key == null) continue;
			Object value = val.getString("attrValue");
			if (value == null) continue;
			hashMap.add(key, value);
		}
		retlist.add(hashMap);
		return retlist;
	}
	public static void put(Array data)throws Exception
	{
		deleteAll();
		Enumeration<?> enumeration = data.elements();
		while(enumeration.hasMoreElements())
		{
			Object object = enumeration.nextElement();
			if (object instanceof HashMap){
				put((HashMap) object);
			}else if (object instanceof Array){
				put((Array) object);
			}
		}
	}
	
	private static void putArray(String key , Array array)throws Exception
	{
		Enumeration<?> enumeration = array.elements();
		while(enumeration.hasMoreElements())
		{
			Object value = enumeration.nextElement();
			if (value instanceof String){
				put(key,(String)value);
			}if (value instanceof Array){
				putArray(key,(Array)value);
			}
		}
	}

	private static void put(HashMap hashmap)throws Exception
	{
		Enumeration<?> keys = hashmap.keys();
		while(keys.hasMoreElements())
		{
			String key = (String)keys.nextElement();
			
			Object value = hashmap.get(key);
			if (value instanceof Array){
				putArray(key,(Array)value);
			}else if (value instanceof String){
				put(key,(String)value);
			}
		}
	}
	
	public static void put(String key,String value) throws Exception
	{
		GenericValue val = getDelegator().makeValue("SvMasterConfig");
		val.set("idx", getIndex(key));
		val.set("attrName",key);
		val.set("attrValue", value);
		val.create();
	}

	public static long getIndex(String key) throws Exception
	{
		EntityCondition condition = EntityCondition.makeCondition("attrName", EntityOperator.EQUALS, key);
        return getDelegator().findCountByCondition("SvMasterConfig", condition, null,null) + 1;
		
	}
	
	public static List<GenericValue> getAll()throws Exception
	{
        return getDelegator().findList("SvMasterConfig", null, null,UtilMisc.toList("idx"),null,false);
	}
	
	public static void deleteAll()throws Exception
	{
		getDelegator().removeByAnd("SvMasterConfig",UtilMisc.toMap("1","1"));
	}
	
}
