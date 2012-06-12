package com.siteview.ecc.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import jgl.Array;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.LocalDispatcher;
import org.ofbiz.service.ServiceUtil;
import com.dragonflow.Page.snmpPrefsPage;
import com.siteview.svecc.service.BaseClass;

public class SNMPUI {

	public static Map<String, Object> SNMPDefaultSettingsInfo(
	// 得到缺省值
			DispatchContext ctx, Map<?, ?> context) {

		try {
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult
					.put("result", (ctx.getDispatcher().runSync(
							"getSNMPPreferenceInfoValue", new HashMap()))
							.get("result"));
			return retresult;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<?, ?> saveSNMPChange(DispatchContext ctx,
			Map<?, ?> context) {
		try {

			Map<String, Object> map = new HashMap<String, Object>();

			map.put("_snmpHost", (String) context.get("_snmpHost"));
			map.put("_snmpObjectID", (String) context.get("_snmpObjectID"));
			map.put("_otherSNMPId", (String) context.get("_otherSNMPId"));
			map.put("_snmpCommunity", (String) context.get("_snmpCommunity"));
			map.put("_snmpGeneric", (String) context.get("_snmpGeneric"));
			map.put("_snmpSpecific", (String) context.get("_snmpSpecific"));
			map.put("_snmpTrapVersion", (String) context
					.get("_snmpTrapVersion"));

			ctx.getDispatcher().runSync("saveSNMPChangeValue",
					UtilMisc.toMap("result", map));
			Map<String, Object> retmap = ServiceUtil.returnSuccess();
			return retmap;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<String, Object> getSNMPPrefefencesList(
			DispatchContext ctx, Map<?, ?> context) {
		try {
			Map<String, Object> map2 = ServiceUtil.returnSuccess();
			List<Map<Object, Object>> list = new ArrayList<Map<Object, Object>>();
			Map<String, Object> retDataMap = (Map<String, Object>) (ctx
					.getDispatcher().runSync("getConfigByName", UtilMisc.toMap(
					"attrName", "_additionalSNMP"))).get("result");
			if (retDataMap == null || retDataMap.size() == 0
					|| retDataMap.isEmpty()) {
				Map<Object, Object> map1 = new HashMap<Object, Object>();
				map1.put("_id", "no");
				map1.put("_name", "");
				map1.put("_snmpObjectID", "no additional SNMP settings");
				map1.put("_snmpGeneric", "");
				map1.put("_snmpHost", "");

				list.add(map1);
				map2.put("result", list);
			} else {
				map2.put("result", (ctx.getDispatcher().runSync(
						"getSNMPPrefefencesListValue", new HashMap()))
						.get("result"));
			}
			System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" + map2);
			System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
					+ map2.get("result"));
			return map2;

		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static Map<String, Object> saveSetting(DispatchContext ctx,
			Map<?, ?> context) {

		try {
			String id = (String) context.get("id");
			if (id != null && ("".equals(id) == false)) {
				String _name = ((String) context.get("settingName") == null) ? ""
						: (String) context.get("settingName");
				String _disabled = ((String) context.get("flag") == null) ? ""
						: "CHECKED";
				String _snmpHost = ((String) context.get("Host") == null) ? ""
						: (String) context.get("Host");
				String _snmpObjectID = ((String) context.get("snmpObjectID") == null) ? ""
						: (String) context.get("snmpObjectID");
				String _snmpCommunity = ((String) context.get("snmpCommunity") == null) ? ""
						: (String) context.get("snmpCommunity");
				String _snmpGeneric = ((String) context.get("snmpGeneric") == null) ? ""
						: (String) context.get("snmpGeneric");
				String _snmpSpecific = ((String) context.get("specific") == null) ? ""
						: (String) context.get("specific");
				String _snmpTrapVersion = (String) context
						.get("snmpTrapVersion");

				String SNMPValue = " _id=" + id + " _name=" + _name
						+ " _disabled=" + _disabled + " _snmpHost=" + _snmpHost
						+ " _snmpObjectID=" + _snmpObjectID
						+ " _snmpCommunity=" + _snmpCommunity
						+ " _snmpGeneric=" + _snmpGeneric + " _snmpSpecific="
						+ _snmpSpecific + " _snmpTrapVersion="
						+ _snmpTrapVersion;
				System.out.println(id + "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
						+ SNMPValue);

				Map value = (Map) (ctx.getDispatcher().runSync(
						"getConfigByName", UtilMisc.toMap("attrName",
								"_additionalSNMP"))).get("result");
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
				ctx.getDispatcher().runSync("UpdateAddSNMPSetting",
						UtilMisc.toMap("idx", idx, "pagerValue", SNMPValue));

				return ServiceUtil.returnSuccess();
			} else {
				Map<String, Object> value = new HashMap<String, Object>();
				value.put("_name",
						((String) context.get("settingName") == null) ? ""
								: (String) context.get("settingName"));
				value
						.put("_disabled",
								((String) context.get("flag") == null) ? ""
										: "CHECKED");
				value.put("_snmpHost",
						((String) context.get("Host") == null) ? ""
								: (String) context.get("Host"));
				value.put("_snmpObjectID", ((String) context
						.get("snmpObjectID") == null) ? "" : (String) context
						.get("snmpObjectID"));
				value.put("_snmpCommunity", ((String) context
						.get("snmpCommunity") == null) ? "" : (String) context
						.get("snmpCommunity"));
				value.put("_snmpGeneric",
						((String) context.get("snmpGeneric") == null) ? ""
								: (String) context.get("snmpGeneric"));
				value.put("_snmpSpecific",
						((String) context.get("specific") == null) ? ""
								: (String) context.get("specific"));
				value.put("_snmpTrapVersion", (String) context
						.get("snmpTrapVersion"));

				ctx.getDispatcher().runSync("saveAddSNMPSettingValue",
						UtilMisc.toMap("value", value));
				return ServiceUtil.returnSuccess();
			}
		} catch (Exception e) {
			ServiceUtil.returnFailure(e.getMessage());
		}

		Map<String, Object> retresult = ServiceUtil.returnSuccess();
		retresult.put("result", "success");
		return retresult;
	}

	public static Map<String, Object> getNeedSNMPSetting(DispatchContext ctx,
			Map<?, ?> context) {
		String id = (String) context.get("id");
		if (id == null || "".equals(id)) {
			HashMap<Object, Object> map1 = new HashMap<Object, Object>();
			try {
				Map<String, Object> retDataMap = (Map) (ctx.getDispatcher()
						.runSync("getConfigByName", UtilMisc.toMap("attrName",
								"_additionalSNMP"))).get("result");
				Iterator it = retDataMap.keySet().iterator();
				String key = "";
				while (it.hasNext()) {
					key = (String) it.next();
				}
				String value = (String) (retDataMap.get(key));
				map1 = (HashMap<Object, Object>) BaseClass.stringToMap(value);

			} catch (Exception e) {
				return ServiceUtil.returnFailure(e.getMessage());
			}
			Map<String, Object> map2 = ServiceUtil.returnSuccess();
			map2.put("result", map1);
			return map2;
		} else {
			return SNMPSettingInfo(ctx, context);
		}
	}

	public static Map<String, Object> SNMPSettingInfo(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", SNMPSettingInfo(ctx.getDispatcher(),
					context));
			return retresult;
		} catch (Exception e1) {
			return ServiceUtil.returnError(e1.getMessage());
		}
	}

	public static Map<Object, Object> SNMPSettingInfo(LocalDispatcher dispatch,
			Map<?, ?> context) throws Exception {
		String id = (String) context.get("id");
		Map<Object, Object> map = new HashMap<Object, Object>();
		if (id == null) {
			Map<Object, Object> value = new HashMap<Object, Object>();
			value.put("_id", "");
			value.put("_name", "");
			value.put("_disabled", "");
			value.put("_snmpHost", "");
			value.put("_snmpObjectID", "");
			value.put("_snmpCommunity", "");
			value.put("_snmpGeneric", "");
			value.put("_snmpSpecific", "");
			value.put("_snmpTrapVersion", "");
			return value;
		} else {
			Map value = (Map) (dispatch.runSync("getConfigByName", UtilMisc
					.toMap("attrName", "_additionalSNMP"))).get("result");
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
			return map;
		}

	}

	public static Map<?, ?> delSNMPseting(DispatchContext ctx, Map<?, ?> context) {
		try {
			String id = (String) context.get("id");
			ctx.getDispatcher().runSync("delSNMPsetingValue",
					UtilMisc.toMap("id", id));
			return ServiceUtil.returnSuccess();
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());

		}
	}

	public static Map<?, ?> SNMPSend(DispatchContext ctx, Map<?, ?> context) {
		String s1 = (String) context.get("message");
		String id = (String) context.get("id");
		try {
			if (id == null || "".equals(id)) {

				jgl.HashMap hashmap = new snmpPrefsPage()
						.getAdditionalSettings("SNMP", "");
				com.dragonflow.StandardAction.SNMPTrap snmptrap = new snmpPrefsPage()
						.getSNMPTrapObject(hashmap);

				snmptrap.setProperty("_snmpHost", (String) context
						.get("snmpHost"));
				snmptrap.setProperty("_snmpCommunity", (String) context
						.get("snmpCommunity"));
				snmptrap.setProperty("_snmpGeneric", (String) context
						.get("snmpGeneric"));
				snmptrap.setProperty("_snmpSpecific", (String) context
						.get("snmpSpecific"));
				snmptrap.setProperty("_snmpObjectID", (String) context
						.get("snmpObjectID"));

				jgl.Array array = new Array();
				array.add(s1);
				snmptrap.setArgs(array);
				String s3 = snmptrap.sendTrap(s1);
				if (s3.length() == 0) {
					return ServiceUtil.returnSuccess();
				} else {
					throw new Exception("The SNMP Trap could not be sent.");
				}
			} else {
				ctx.getDispatcher().runSync("SNMPSendValue",
						UtilMisc.toMap("id", id, "message", s1));
				return ServiceUtil.returnSuccess();
			}
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

}
