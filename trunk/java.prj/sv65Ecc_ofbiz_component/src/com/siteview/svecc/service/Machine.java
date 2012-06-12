package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.ofbiz.base.util.Debug;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

import com.dragonflow.Api.APIPreference;
import com.dragonflow.Api.SSInstanceProperty;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.StandardPreference.RemoteUnixInstancePreferences;



public class Machine extends BaseClass{
	private static final String module = Machine.class.getName();
	private static final String machine = new RemoteUnixInstancePreferences().getSettingName();
	
	private static final String CLASS_NAME = "RemoteUnixInstancePreferences";

	public static final String TEST_SHORT = "short";
	public static final String TEST_DETAIL = "detail";
	
	public static Map<?,?> getMachineList(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			result = ServiceUtil.returnSuccess();
			result.put("list", getMachineList());
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error getMachineList: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static List<Map<?,?>> getMachineList() throws Exception{
		return convertToList(Config.getConfigByName(machine));
	}
	
	
	public static Map<?,?> getMachineAttri(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			result = ServiceUtil.returnSuccess();
			result.put("data", getMachineAttri());
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error getMachineAttri: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static Map<String,StringProperty> getMachineAttri() throws Exception{
		return getStringProperties(new RemoteUnixInstancePreferences());
	}
	
	private static List<Map<?,?>> convertToList(Map<?,?> serviceResult){
		List<Map<?,?>> machineList = new ArrayList<Map<?,?>>();
		
		for (Object idx : serviceResult.keySet() )
		{
			Object value = serviceResult.get(idx);
			Map<Object, Object> map = stringToMap((String)value);
			map.put("idx", idx);
			machineList.add(map);
		}
		return machineList;
	}
	
	public static Map<?,?> getMachineById(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		
		try {
			String id = (String)getNotOptionalValue(context,"id");
			result = ServiceUtil.returnSuccess();
			result.put("data", getMachineById(id));
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error getMachineById: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static Map<?,?> getMachineById(String id) throws Exception{
		if (id == null) return null;
		List<Map<?,?>> list = getMachineList();
		for(Map<?,?> map : list)
		{
			if (map == null) continue;
			String mapid = (String) map.get("_id");
			if (mapid == null) continue;
			if (mapid.equals(id)) return map;
		}
		return null;
	}

	public static Map<?,?> deleteMachineById(DispatchContext ctx,Map<?,?> context){
		Map<String,Object> result=null;
		try {
			String id = (String)getNotOptionalValue(context,"id");
			deleteMachineById(id);
			result = ServiceUtil.returnSuccess();
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error deleteMachineById: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}

	public static void deleteMachineById(String id) throws Exception{
		try{
		    com.dragonflow.Api.APIPreference apipreference = new APIPreference();
		    apipreference.delete(CLASS_NAME, "_id", id);
		}finally{
			refrashData();
		}
	}


	public static Map<?,?> updateMachineById(DispatchContext ctx,Map<?,?> context){
		Map<String,Object> result=null;
		try {
			String id = (String) getNotOptionalValue(context,"id");
			Boolean bTest = (Boolean) getNotOptionalValue(context,"bTest");
			Map<?,?> value = (Map<?, ?>) getNotOptionalValue(context,"data");
			updateMachineById(id,value,bTest);			
			result = ServiceUtil.returnSuccess();
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error updateMachineById: " + e.toString());
			result.put("message", e.toString());
		}
		return result;

	}
	public static void updateMachineById(String id,Map<?,?> value,Boolean bTest) throws Exception{
		try{
			Map<String,Object> map = (Map<String, Object>) value;
			
			List<SSInstanceProperty> assinstanceproperty = new ArrayList<SSInstanceProperty>();
			Set<String> keys = (Set<String>) map.keySet();
			for (String key : keys){
				Object val = map.get(key);
				assinstanceproperty.add(new SSInstanceProperty(key,val));
			}
			new APIPreference().update(CLASS_NAME,"_id", id, assinstanceproperty.toArray(new SSInstanceProperty[0]));
			if (bTest)
			{
				testMachineById(id,TEST_SHORT);
			}
		}finally{
			refrashData();
		}
	}
	
	public static Map<?,?> addMachine(DispatchContext ctx,Map<?,?> context){
		Map<String,Object> result=null;
		try {
			Map<?,?> value = (Map<?, ?>) getNotOptionalValue(context,"data");
			Boolean bTest = (Boolean) getNotOptionalValue(context,"bTest");
			result = ServiceUtil.returnSuccess();
			result.put("message", addMachine(value,bTest));
		}catch(Exception e){
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error addMachine: " + e.toString());
			result.put("message", e.toString());			
		}
		return result;

	}

	public static String addMachine(Map<?,?> value,Boolean bTest)throws Exception{
		try {
			List<SSInstanceProperty> assinstanceproperty = new ArrayList<SSInstanceProperty>();
			Set<String> keys = (Set<String>) value.keySet();
			for (String key : keys){
				Object val = value.get(key);
				assinstanceproperty.add(new SSInstanceProperty(key,val));
			}
			SSInstanceProperty returnValue = new APIPreference().create(CLASS_NAME, assinstanceproperty.toArray(new SSInstanceProperty[0]));
			String id = (String) returnValue.getValue();
			if (bTest)
			{
				testMachineById(id,TEST_SHORT);
			}
			return id;
		}finally{
			refrashData();
		}
	}

	public static Map<?,?> testMachineById(DispatchContext ctx,Map<?,?> context){
		Map<String,Object> result=null;
		try {
			String id = (String)getNotOptionalValue(context,"id");
			String type = (String)getNotOptionalValue(context,"type");
			testMachineById(id,type);
			result = ServiceUtil.returnSuccess();
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error testMachineById: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static void testMachineById(String id,String type) throws Exception
	{
		try{
			RemoteUnixInstancePreferences preferences = (RemoteUnixInstancePreferences) new APIPreference().getPreferencesById(id, CLASS_NAME);
			preferences.test(type);
		}catch(Exception e){
		}finally{
			refrashData();
		}
		
	}

	private static void refrashData()throws Exception
	{
		Config.clearCache();
	}

}
