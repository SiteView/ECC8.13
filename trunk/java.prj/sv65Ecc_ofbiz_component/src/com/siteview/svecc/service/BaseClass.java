package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import jgl.Array;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.service.GenericDispatcher;
import org.ofbiz.service.LocalDispatcher;
import org.ofbiz.service.ServiceUtil;

import com.dragonflow.Api.SSInstanceProperty;
import com.dragonflow.Page.monitorPage;
import com.dragonflow.Properties.BooleanProperty;
import com.dragonflow.Properties.FrequencyProperty;
import com.dragonflow.Properties.PropertiedObject;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.AtomicMonitor;
import com.dragonflow.SiteView.Monitor;
import com.dragonflow.Utils.TextUtils;
import com.dragonflow.Utils.jglUtils;

public abstract class BaseClass implements MessageDefine{

	public static Date convert(String source) throws Exception
	{
		return DATE_FORMAT.parse(source);
	}
	public static Long convertToLong(String data) throws Exception
	{
		try{
			return Long.parseLong(data);
		}catch(Exception e){
			return 0L;
		}
	}
	public static String convert(Date source)throws Exception
	{
		return DATE_FORMAT.format(source);
	}
	public static Long convertIndex(String index)throws Exception
	{
		return convertToLong(index);
	}
	
	@SuppressWarnings("unchecked")
	public static Map<String,Object> convert(Object data)
	{
		return (Map<String,Object>)data;
	}
	public static Map<Object,Object> stringToMap(String value){
		return (Map<Object, Object>)convert(TextUtils.stringToHashMap(value));
	}
	public static String mapToString(Map<?,?> value){
		return TextUtils.mapToString(value);
	}
	
	public static SSInstanceProperty[] convert(Map<String,Object> map){
		List<SSInstanceProperty> assinstanceproperty = new ArrayList<SSInstanceProperty>();
		for (String key : map.keySet()){
			Object value = map.get(key);
			assinstanceproperty.add(new SSInstanceProperty(key,value));
		}
		return assinstanceproperty.toArray(new SSInstanceProperty[0]);
	}

	public static Map<String,Object> getProperties(PropertiedObject propertiedObject)
	{
		Array array = propertiedObject.getProperties();
		Enumeration<?> enumeration = array.elements();
		Map<String, Object> map = new HashMap<String, Object>();
		while (enumeration.hasMoreElements()) {
			StringProperty stringproperty = (StringProperty)enumeration.nextElement();
			if (stringproperty instanceof BooleanProperty)
			{
				Boolean value = propertiedObject.getPropertyAsBoolean(stringproperty);
				if (checkData(value)) map.put(stringproperty.getName(), value);
			} else {
				if (MonitorEditProperties.hasUnit(stringproperty))
				{
					int value = propertiedObject.getPropertyAsInteger(stringproperty);
					map.put(MonitorEditProperties.getUnitName(stringproperty.getName()), ((FrequencyProperty)stringproperty).getCurUnit(value));
					int val = ((FrequencyProperty)stringproperty).getRealValueWithUnit(value);
					map.put(stringproperty.getName(), val == 0 ? "" : val );
				}else{
					String value = propertiedObject.getProperty(stringproperty);
					if (checkData(value)) map.put(stringproperty.getName(), value);
				}
			}
		}
		return map;
	}
	public static String getProperty(AtomicMonitor atomicMonitor,String key)
	{
		Object object = AtomicMonitor.getClassPropertyByObject(atomicMonitor.getClass().getName(),key);
		System.out.println(key + "=" + object);
		if (object instanceof String ) return object == null ? "" : ("" + object);
		return "";
	}
	
	public static Map<String,StringProperty> getStringProperties(PropertiedObject propertiedObject)
	{
		Array array = propertiedObject.getProperties();
		array = StringProperty.sortByOrder(array);
		Enumeration<?> enumeration = array.elements();
		Map<String, StringProperty> map = new LinkedHashMap<String, StringProperty>();
		while (enumeration.hasMoreElements()) {
			StringProperty stringproperty = (StringProperty)enumeration.nextElement();
			map.put(stringproperty.getName(), stringproperty);
		}
		return map;
	}	

	public static Map<String,StringProperty> getStringProperties(PropertiedObject propertiedObject , int i)
	{
		Array array = propertiedObject.getProperties();
		array = StringProperty.sortByOrder(array);
		i = new monitorPage().calculateVariablePropertyCount(array, (Monitor) propertiedObject);
		Enumeration<?> enumeration = array.elements();
		Map<String, StringProperty> map = new LinkedHashMap<String, StringProperty>();
		while (enumeration.hasMoreElements()) {
			StringProperty stringproperty = (StringProperty)enumeration.nextElement();
			map.put(stringproperty.getName(), stringproperty);
		}
		return map;
	}	
	public static List<?> convert(Array array)
	{
		return jglUtils.fromJgl(array);
	}
	public static Array convert(List<?> list)
	{
		return jglUtils.toJgl(list);
	}
	public static Map<?,?> convert(jgl.HashMap map)
	{
		return jglUtils.fromJgl(map);
	}
	public static jgl.HashMap convert(Map<?,?> map)
	{
		return jglUtils.toJgl(map);
	}
	
	public static List<Map<String, Object>> convert(Collection<PropertiedObject> collection)
	{
		List<Map<String, Object>> retlist = new ArrayList<Map<String, Object>>();
		Iterator<?> iterator = collection.iterator();
		while(iterator.hasNext()){
			PropertiedObject monitorGroup = (PropertiedObject)iterator.next();
			retlist.add(getProperties(monitorGroup));
		}
		return retlist;
		
	}
	
	
	public static String BooleanToString(Boolean data)
	{
		return data ? "Y" : "N";
	}
	public static Boolean StringToBoolean(String data)
	{
		return "Y".equals(data);
	}
	public static Boolean isBoolean(String data)
	{
		return "Y".equals(data) || "N".equals(data);
	}
	
	public static Map<String, Object> BooleanToString(Map<String, Object> data)
	{
		Map<String, Object> retmap = new HashMap<String, Object>();
		for (String key : data.keySet()){
			Object value = data.get(key);
			if (value instanceof Boolean)
			{
				retmap.put(key, BooleanToString((Boolean)value));
			} else {
				retmap.put(key, value);
			}
		}
		return retmap;
		
	}
	public static Map<String, Object> StringToBoolean(Map<String, Object> data)
	{
		Map<String, Object> retmap = new HashMap<String, Object>();
		for (String key : data.keySet()){
			Object value = data.get(key);
			if (value instanceof String)
			{
				if (isBoolean((String)value)){
					retmap.put(key, StringToBoolean((String)value));
				} else {
					retmap.put(key, value);
				}
			} else {
				retmap.put(key, value);
			}
		}
		return retmap;
		
	}

//	public static Map<Object, Object> getMapData(Map<Object, Object> context)
//	{
//		Map<Object, Object> retmap = new HashMap<Object, Object>();
//		for (Object key : context.keySet())
//		{
//			try{
//				if (!filterKey(key)) continue;
//				retmap.put(key, context.get(key));
//			}catch(Exception e){
//				
//			}
//		}
//		return retmap;
//	}
//	
//	private static boolean filterKey(Object key)
//	{
//		if (key==null)return false;
//		return true;
//	}
	
	public static String getThrowMessage(Long type,String...names) throws Exception
	{
		Map<String, ? extends Object> map = getDispatcher().runSync("getMessage", UtilMisc.toMap("messageCode",type));
		if (ServiceUtil.isError(map)) {
			throw new Exception(ServiceUtil.getErrorMessage(map));
		}
		String message = (String) map.get("result");
		for (int index = 0 ; index < names.length ; index ++)
		{
			message = message.replace(PARAMDATA_REPLACE.replace("n", "" + (index + 1)), names[index]);
		}
		return message;
	}
	
	public static void throwException(Long type,String...name) throws Exception
	{
		throw new Exception(getThrowMessage(type,name));
	}
	
	public static Object getNotOptionalValue(Map<?, ?> context,String key) throws Exception
	{
		if (key == null || "".equals(key)) 
			throwException(THROW_TYPE_OPTIONAL_PARAM,key);
		Object value = context.get(key);
		if (value == null || "".equals(value))
			throwException(THROW_TYPE_OPTIONAL_PARAM,key);
		if (value instanceof String){
			if ("".equals(((String)value).trim()))throwException(THROW_TYPE_OPTIONAL_PARAM,key);
		}
		return value;
	}
	public static Object getOptionalValue(Map<?, ?> context,String key) throws Exception
	{
		if ("".equals(key) || key == null) return null;
		Object value = context.get(key);
		if ("".equals(value) || value == null) return null;
		return value;
	}
	
	public static LocalDispatcher getDispatcher()
	{
		return GenericDispatcher.getLocalDispatcher(MONITOR_DISPATCHER_NAME, getGenericDelegator());
	}
	public static GenericDelegator getGenericDelegator()
	{
		return GenericDelegator.getGenericDelegator(MONITOR_DELEGATOR_NAME);
	}

	public static boolean checkData(Object data)
	{
		if (data == null) return false;
		if (data instanceof String){
			if ("".equals(((String)data).trim())) return false;
		}
		return true;
	}
	
	public static void main(String[] args) throws Exception {
		System.out.println(checkData(false));
	}
}
