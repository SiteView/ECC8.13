package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

import com.dragonflow.Api.APIPreference;
import com.dragonflow.Api.SSInstanceProperty;
import com.dragonflow.StandardAction.Page;
import com.dragonflow.StandardPreference.PagerInstancePreferences;
import com.dragonflow.StandardPreference.RemoteUnixInstancePreferences;

public class PagerOperate extends BaseClass {

	public static Map<String, Object> getPagerDefaultPrefefences(
			DispatchContext ctx, Map<?, ?> context) {

		try {
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getPagerDefaultPrefefences());
			return retresult;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<String, Object> getPagerDefaultPrefefences()
			throws Exception {

		Map<String, Object> map = new HashMap<String, Object>();

		map.put("_pagerPort", (Config.configGet("_pagerPort") == null) ? ""
				: Config.configGet("_pagerPort"));
		map.put("_pagerSpeed", (Config.configGet("_pagerSpeed") == null) ? ""
				: Config.configGet("_pagerSpeed"));
		map.put("_pagerAlphaPhone",
				(Config.configGet("_pagerAlphaPhone") == null) ? "" : Config
						.configGet("_pagerAlphaPhone"));
		map.put("_pagerAlphaPIN",
				(Config.configGet("_pagerAlphaPIN") == null) ? "" : Config
						.configGet("_pagerAlphaPIN"));
		map.put("_pagerDirectPhone",
				(Config.configGet("_pagerDirectPhone") == null) ? "" : Config
						.configGet("_pagerDirectPhone"));
		map.put("_pagerOptionPhone",
				(Config.configGet("_pagerOptionPhone") == null) ? "" : Config
						.configGet("_pagerOptionPhone"));
		map.put("_pagerCustom", (Config.configGet("_pagerCustom") == null) ? ""
				: Config.configGet("_pagerCustom"));
		map.put("_pagerOption", (Config.configGet("_pagerOption") == null) ? ""
				: Config.configGet("_pagerOption"));

		return map;
	}

	public static Map<String, Object> getPagerPrefefencesList(
			DispatchContext ctx, Map<?, ?> context) {
		try {
			Map<String, Object> map2 = ServiceUtil.returnSuccess();
			map2.put("result", getPagerPrefefencesList());
			return map2;
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static List<Map<Object, Object>> getPagerPrefefencesList()
			throws Exception {
		List<Map<Object, Object>> list = new ArrayList<Map<Object, Object>>();

		Map<String, Object> retDataMap = Config
				.getConfigByName("_additionalPager");

		// 接下来去map中的值放到list中
		Iterator it = retDataMap.keySet().iterator();
		while (it.hasNext()) {
			String key = (String) it.next();
			String value = (String) (retDataMap.get(key));
			Map<Object, Object> map2 = BaseClass.stringToMap(value);

			if ("CHECKED".equals((String) map2.get("_disabled"))) {
				map2.put("_disabled", "disabled");
			}
			if ("".equals((String) map2.get("_disabled"))
					|| (String) map2.get("_disabled") == null) {
				map2.put("_disabled", "scheduled");
			}
			list.add(map2);
		}
		return list;
	}

	public static Map<?, ?> savePagerChange(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			savePagerChange(context);
			Map<String, Object> retmap = ServiceUtil.returnSuccess();
			return retmap;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static void savePagerChange(Map<?, ?> context) throws Exception {
		Map map = (Map) context.get("Value");
		Config.configPut("_pagerPort", (String) map.get("pagerPort"));
		Config.configPut("_pagerSpeed", (String) map.get("pagerSpeed"));
		Config.configPut("_pagerAlphaPhone", (String) map
				.get("pagerAlphaPhone"));
		Config.configPut("_pagerAlphaPIN", (String) map.get("pagerAlphaPIN"));
		Config.configPut("_pagerDirectPhone", (String) map
				.get("pagerDirectPhone"));
		Config.configPut("_pagerOptionPhone", (String) map
				.get("pagerOptionPhone"));
		Config.configPut("_pagerCustom", (String) map.get("pagerCustom"));
		Config.configPut("_pagerOption", (String) map.get("pagerOption"));
		Config.configPut("_pagerType", (String) map.get("pagerType"));
		refrashData();
	}

	public static Map<String, Object> pagerSettingInfo(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", pagerSettingInfo(context));
			return retresult;
		} catch (Exception e1) {
			return ServiceUtil.returnError(e1.getMessage());
		}
	}

	public static Map<Object, Object> pagerSettingInfo(Map<?, ?> context)
			throws Exception {
		String id = (String) context.get("id");
		Map<Object, Object> map = new HashMap<Object, Object>();

		Map value = (Map) Config.getConfigByName("_additionalPager");
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

	public static Map<String, Object> saveSetting(DispatchContext ctx,
			Map<?, ?> context) throws Exception {

		Map value = (Map) context.get("value");
		List<SSInstanceProperty> assinstanceproperty = new ArrayList<SSInstanceProperty>();
		Set<String> keys = (Set<String>) value.keySet();
		for (String key : keys) {
			Object val = value.get(key);
			assinstanceproperty.add(new SSInstanceProperty(key, val));
		}
		SSInstanceProperty returnValue = new APIPreference().create(
				"PagerInstancePreferences", assinstanceproperty
						.toArray(new SSInstanceProperty[0]));
		refrashData();
		return ServiceUtil.returnSuccess();
	}

	public static Map<String, Object> updatePagersetting(DispatchContext ctx,
			Map<?, ?> context) {
		try {

			updatePagersetting(context);
			return ServiceUtil.returnSuccess();
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static void updatePagersetting(Map<?, ?> context) throws Exception {
		long idx = (Long) context.get("idx");
		String pagerValue = (String) context.get("pagerValue");
		Config.updConfig("_additionalPager", idx, pagerValue);
		refrashData();
	}

	public static Map<?, ?> delPagerseting(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			delPagerseting(context);
			return ServiceUtil.returnSuccess();
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());

		}
	}

	public static void delPagerseting(Map<?, ?> context) throws Exception {
		String id = (String) context.get("id");
		try {
			com.dragonflow.Api.APIPreference apipreference = new APIPreference();
			apipreference.delete("PagerInstancePreferences", "_id", id);
		} finally {
			refrashData();
		}
	}

	public static Map<?, ?> sendTest(DispatchContext ctx, Map<?, ?> context) {
		try {
			sendTest(context);
			return ServiceUtil.returnSuccess();
		} catch (Exception e) {
			Map map = ServiceUtil.returnFailure(e.getMessage());
			return map;
		}
	}

	public static void sendTest(Map<?, ?> context) throws Exception {
		String id = (String) context.get("id");
		String message = (String) context.get("message");
		if (id == null || "".equals(id)) {
			Page page = new Page();
			page.pagerSend(message);
		} else {
			PagerInstancePreferences preferences = (PagerInstancePreferences) new APIPreference()
					.getPreferencesById(id, "PagerInstancePreferences");
			preferences.test(message);
		}

	}

	private static void refrashData() throws Exception {
		Config.clearCache();
	}
}
