package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

import com.dragonflow.Api.APIPreference;
import com.dragonflow.Api.SSInstanceProperty;

public class ScheduleOperate {

	public static Map<String, Object> saveRangScheduleV(DispatchContext ctx,
			Map<?, ?> context) {

		try {
			saveRangScheduleV(context);
			return ServiceUtil.returnSuccess();
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static void saveRangScheduleV(Map<?, ?> context) throws Exception {
		Map value = (Map) context.get("value");
		List<SSInstanceProperty> assinstanceproperty = new ArrayList<SSInstanceProperty>();
		Set<String> keys = (Set<String>) value.keySet();
		for (String key : keys) {
			Object val = value.get(key);
			assinstanceproperty.add(new SSInstanceProperty(key, val));
		}
		SSInstanceProperty returnValue = new APIPreference().create(
				"ScheduleInstancePreferences", assinstanceproperty
						.toArray(new SSInstanceProperty[0]));
		refrashData();

	}

	public static Map<String, Object> saveAbsoluteScheduleV(
			DispatchContext ctx, Map<?, ?> context) {
		try {
			saveAbsoluteScheduleV(context);
			return ServiceUtil.returnSuccess();
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static void saveAbsoluteScheduleV(Map<?, ?> context)
			throws Exception {
		String timeStr = (String) context.get("value");

		Map value = (Map) BaseClass.stringToMap(timeStr);
		List<SSInstanceProperty> assinstanceproperty = new ArrayList<SSInstanceProperty>();
		Set<String> keys = (Set<String>) value.keySet();
		for (String key : keys) {
			Object val = value.get(key);
			assinstanceproperty.add(new SSInstanceProperty(key, val));
		}
		SSInstanceProperty returnValue = new APIPreference().create(
				"ScheduleInstancePreferences", assinstanceproperty
						.toArray(new SSInstanceProperty[0]));
		refrashData();
	}

	public static Map<String, Object> getScheduleList(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			Map<String, Object> retMap = ServiceUtil.returnSuccess();
			retMap.put("value", getScheduleList());

			return retMap;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static List<Map<?, ?>> getScheduleList() throws Exception {

		Map value = (Map) Config.getConfigByName("_additionalSchedule");
		List<Map<?, ?>> list = new ArrayList<Map<?, ?>>();
		if (value.size() <= 0) {
			Map<String, Object> map = new HashMap<String, Object>();
			map.put("_id", "no");
			map.put("_name", "");
			map.put("_type", "no additional schedules");
			list.add(map);
		} else {
			Iterator it = value.values().iterator();
			while (it.hasNext()) {
				String ls = (String) it.next();
				Map map = BaseClass.stringToMap(ls);				
				String tem = (String) map.get("_schedule");
				if (tem.charAt(0) == '*') {
					map.put("_type", "absolute");
				} else {
					map.put("_type", "rang");
				}
				System.out.println("~~~~~~~~~~1111~~~~~~~~~~~~~~~~~~~~~~~"+list);
				list.add(map);
			}
		}
		System.out.println("~~~~~~~~~222~~~~~~~~~~~~~~~~~~~~~"+list);
		return list;
	}
	
	public static Map<String, Object> delScheduleV(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			delScheduleV(context);
			return ServiceUtil.returnSuccess();
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static void delScheduleV(Map<?,?> context) throws Exception {
		String id=(String) context.get("id");
		try {
			com.dragonflow.Api.APIPreference apipreference = new APIPreference();
			apipreference.delete("ScheduleInstancePreferences", "_id", id);
		} finally {
			refrashData();
		}
	}
	
	public static Map<String, Object> editAbsoluteScheduleV(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			Map retMap=ServiceUtil.returnSuccess();
			retMap.put("value", editAbsoluteScheduleV(context));
			return retMap;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<Object, Object> editAbsoluteScheduleV(Map<?,?> context) throws Exception {
		String id=(String) context.get("id");
		Map<Object, Object> map = new HashMap<Object, Object>();

		Map value = (Map) Config.getConfigByName("_additionalSchedule");
		Iterator it = value.values().iterator();
		String mapString = "";
		boolean flag = true;
		while (it.hasNext()) {
			String ls = (String) it.next();
			String[] temple = ls.split("_");
			for (int i = 1; i < temple.length; i++) {
				String tem = "id=" + id;
				String tem1 = "id=" + id + " ";
				if (tem.equals(temple[i]) || (tem1.equals(temple[i]))) {
					flag = false;
					break;
				}
			}
			mapString = ls;
			if (flag == false) {
				break;
			}
		}
		map = BaseClass.stringToMap(mapString);
		if(map.get("_name")==null){
			map.put("_name","");
		}
		return map;
	}	
	public static Map<String, Object> updateAbsoluteScheduleV(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			updateAbsoluteScheduleV(context);
			return ServiceUtil.returnSuccess();
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static void updateAbsoluteScheduleV(Map<?, ?> context)
			throws Exception {
		String id = (String) context.get("id");
		String timeV = (String) context.get("value");

		Map value = (Map) Config.getConfigByName("_additionalSchedule");
		Iterator it = value.values().iterator();
		long idx = 0;
		boolean flag = true;
		while (it.hasNext()) {
			String ls = (String) it.next();
			String[] temple = ls.split("_");
			for (int i = 1; i < temple.length; i++) {
				String tem = "id=" + id;
				String tem1 = "id=" + id + " ";
				
				if (tem.equals(temple[i]) || (tem1.equals(temple[i]))) {
					flag = false;
					break;
				}
			}
			idx++;
			if (flag == false) {
				break;
			}
		}

		Config.updConfig("_additionalSchedule", idx, timeV);
		refrashData();

	}	
	public static Map<String, Object> editRangeScheduleV(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			Map retMap=ServiceUtil.returnSuccess();
			retMap.put("value", editRangeScheduleV(context));
			return retMap;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<Object, Object> editRangeScheduleV(Map<?,?> context) throws Exception {
		String id=(String) context.get("id");
		Map<Object, Object> map = new HashMap<Object, Object>();

		Map value = (Map) Config.getConfigByName("_additionalSchedule");
		Iterator it = value.values().iterator();
		String mapString = "";
		boolean flag = true;
		while (it.hasNext()) {
			String ls = (String) it.next();
			String[] temple = ls.split("_");
			for (int i = 1; i < temple.length; i++) {
				String tem = "id=" + id;
				String tem1 = "id=" + id + " ";
				if (tem.equals(temple[i]) || (tem1.equals(temple[i]))) {
					flag = false;
					break;
				}
			}
			mapString = ls;
			if (flag == false) {
				break;
			}
		}
		map = BaseClass.stringToMap(mapString);
		if(map.get("_name")==null){
			map.put("_name","");
		}
		return map;
	}		
	
	
	
	private static void refrashData() throws Exception {
		Config.clearCache();
	}
}
