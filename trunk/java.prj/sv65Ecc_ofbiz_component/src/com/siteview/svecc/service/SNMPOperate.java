package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import jgl.Array;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.GenericServiceException;
import org.ofbiz.service.LocalDispatcher;
import org.ofbiz.service.ServiceUtil;

import com.dragonflow.Api.APIPreference;
import com.dragonflow.Api.SSInstanceProperty;
import com.dragonflow.Page.snmpPrefsPage;
import com.dragonflow.StandardPreference.PagerInstancePreferences;
import com.dragonflow.StandardPreference.SNMPInstancePreferences;

import sun.java2d.loops.FillRect.General;

public class SNMPOperate {

	public static Map<String, Object> SNMPDefaultSettingsInfo(
			DispatchContext ctx, Map<?, ?> context) {
		// 获得snmp中的缺省设置
		try {
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", SNMPDefaultSettingsInfo());
			return retresult;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<String, Object> SNMPDefaultSettingsInfo() throws Exception{
		Map<String, Object> map = new HashMap<String, Object>();
			map.put("_snmpHost", Config.configGet("_snmpHost"));
			map.put("_snmpObjectID", Config.configGet("_snmpObjectID"));
			map.put("_snmpCommunity", Config.configGet("_snmpCommunity"));
			map.put("_snmpGeneric", Config.configGet("_snmpGeneric"));
			map.put("_snmpSpecific", Config.configGet("_snmpSpecific"));
			map.put("_snmpTrapVersion", Config.configGet("_snmpTrapVersion"));
		return map;
	}

	public static Map<?, ?> saveSNMPChange(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			saveSNMPChange(context);
			Map<String, Object> retmap = ServiceUtil.returnSuccess();
			return retmap;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static void saveSNMPChange(Map<?, ?> context) throws Exception{
		Map map = (Map) context.get("result");
			Config.configPut("_snmpHost",(String) map
					.get("_snmpHost"));
			Config.configPut("_snmpObjectID",(String) map
					.get("_snmpObjectID"));
			Config.configPut("_snmpCommunity",(String) map
					.get("_snmpCommunity"));
			Config.configPut("_snmpGeneric",(String) map
					.get("_snmpGeneric"));
			Config.configPut("_snmpSpecific",(String) map
					.get("_snmpSpecific"));
			Config.configPut("_snmpTrapVersion",(String) map
					.get("_snmpTrapVersion"));
			refrashData();
	}

	public static Map<String, Object> getSNMPPrefefencesList(
			DispatchContext ctx, Map<?, ?> context) {
		// 获得snmp中的缺省设置
		try {
			Map<String, Object> map2 = ServiceUtil.returnSuccess();
			map2.put("result", getSNMPPrefefencesList());
			return map2;
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static List<Map<Object, Object>> getSNMPPrefefencesList() throws Exception{
		List<Map<Object, Object>> list = new ArrayList<Map<Object, Object>>();
			Map<String, Object> retDataMap = Config
					.getConfigByName("_additionalSNMP");

				// 接下来去map中的值放到list中
				Iterator it = retDataMap.keySet().iterator();
				while (it.hasNext()) {
					String key = (String) it.next();
					String value = (String) (retDataMap.get(key));
					Map<Object, Object> map2 = BaseClass.stringToMap(value);

					if (((String) map2.get("_disabled")).equals("CHECKED ")) {
						map2.put("_name", map2.get("name") + "(disabled)");
					}
					if ((".1.3.6.1.4.1.11.2.17.1").equals((String) map2
							.get("_snmpObjectID"))) {
						map2.put("_snmpObjectID", "HP Open View Event");
					}
					if (((String) map2.get("_snmpObjectID"))
							.equals(".1.3.6.1.2.1.1")) {
						map2.put("_snmpObjectID", "System - MIB-II");
					}
					if (((String) map2.get("_snmpObjectID"))
							.equals(".1.3.6.1.4.1.311.1.1.3.1.2")) {
						map2.put("_snmpObjectID", "Microsoft - Vendor MIB");
					}
					if (((String) map2.get("_snmpObjectID"))
							.equals(".1.3.6.1.2.1.25.1")) {
						map2
								.put("_snmpObjectID",
										"System - Host Resources MIB");
					}
					if (((String) map2.get("_snmpObjectID")).equals("0")) {
						map2.put("_snmpObjectID", "other...");
					}
					if (((String) map2.get("_snmpGeneric")).equals("0")) {
						map2.put("_snmpGeneric", "cold start");
					}
					if (((String) map2.get("_snmpGeneric")).equals("1")) {
						map2.put("_snmpGeneric", "warm start");
					}
					if (((String) map2.get("_snmpGeneric")).equals("2")) {
						map2.put("_snmpGeneric", "link down");
					}
					if (((String) map2.get("_snmpGeneric")).equals("3")) {
						map2.put("_snmpGeneric", "link up");
					}

					if (((String) map2.get("_snmpGeneric")).equals("6")) {
						map2.put("_snmpGeneric", "enterprise specific");
					}
					list.add(map2);
				}			
		return list;
	}

	public static Map<?, ?> saveSetting(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			saveSetting(context);
			Map<String, Object> retmap = ServiceUtil.returnSuccess();
			return retmap;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}
	
	public static void saveSetting(Map<?, ?> context) throws Exception{
		Map value = (Map) context.get("value");
			List<SSInstanceProperty> assinstanceproperty = new ArrayList<SSInstanceProperty>();
			Set<String> keys = (Set<String>) value.keySet();
			for (String key : keys) {
				Object val = value.get(key);
				assinstanceproperty.add(new SSInstanceProperty(key, val));
			}
			SSInstanceProperty returnValue = new APIPreference().create(
					"SNMPInstancePreferences", assinstanceproperty
							.toArray(new SSInstanceProperty[0]));
			refrashData();
	}

	public static Map<String, Object> updateSNMPsetting(DispatchContext ctx,
			Map<?, ?> context) {
		try {

			updateSNMPsetting(ctx.getDelegator(), context);
			return ServiceUtil.returnSuccess();
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static void updateSNMPsetting(GenericDelegator delegator,
			Map<?, ?> context) throws Exception{
		long idx = (Long) context.get("idx");
		String pagerValue = (String) context.get("pagerValue");
			Config.updConfig("_additionalSNMP", idx, pagerValue);
			refrashData();
	}

	public static Map<?, ?> delSNMPseting(DispatchContext ctx, Map<?, ?> context)
			 {
		try {
			delSNMPseting(context);
			return ServiceUtil.returnSuccess();
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());

		}
	}

	public static void delSNMPseting(Map<?, ?> context) throws Exception {
		String id = (String) context.get("id");
		try {
			com.dragonflow.Api.APIPreference apipreference = new APIPreference();
			apipreference.delete("SNMPInstancePreferences", "_id", id);
		} 
		finally {
			refrashData();
		}
	}

	public static Map<?, ?> SNMPSend(DispatchContext ctx, Map<?, ?> context)
			{
		String s1 = (String) context.get("message");
		String id=(String)context.get("id");
		try{
			SNMPInstancePreferences preferences = (SNMPInstancePreferences) new APIPreference().getPreferencesById(id, "SNMPInstancePreferences");
			preferences.test(s1);
			return ServiceUtil.returnSuccess();
		}catch(Exception e){
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	private static void refrashData() throws Exception {
		Config.clearCache();
	}
}
