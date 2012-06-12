package com.siteview.ecc.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javolution.util.FastMap;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.GenericServiceException;
import org.ofbiz.service.ServiceUtil;

import com.siteview.svecc.service.Assistant;
import com.siteview.svecc.service.BaseClass;
import com.siteview.svecc.service.Config;

public class PagerUI {

	public static Map<String, Object> getPagerDefaultPrefefences(
	// 得到缺省值
			DispatchContext ctx, Map<?, ?> context) {

		try {
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", (ctx.getDispatcher().runSync(
					"getPagerDefaultPrefefencesValue", new HashMap()))
					.get("result"));
			return retresult;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<String, Object> getPagerPrefefencesList(
			DispatchContext ctx, Map<?, ?> context) {
		try {
			Map<String, Object> map2 = ServiceUtil.returnSuccess();
			List<Map<Object, Object>> list = new ArrayList<Map<Object, Object>>();
			Map<String, Object> retDataMap = (Map<String, Object>) (ctx
					.getDispatcher().runSync("getConfigByName", UtilMisc.toMap(
					"attrName", "_additionalPager"))).get("result");
			if (retDataMap == null || retDataMap.size() == 0
					|| retDataMap.isEmpty()) {
				Map<Object, Object> map1 = new HashMap<Object, Object>();
				map1.put("_id", "no");
				map1.put("_name", "");
				map1.put("_pagerType", "no additional pager settings");
				map1.put("_pagerAlphaPhone", "");
				map1.put("_disabled", "");
				map1.put("_pagerAlphaPIN", "");

				list.add(map1);
				map2.put("result", list);
			} else {
				map2.put("result", (ctx.getDispatcher().runSync(
						"getPagerPrefefencesListValue", new HashMap()))
						.get("result"));
			}
			return map2;
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static Map<?, ?> savePagerChange(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			Map<String, Object> map = new HashMap<String, Object>();

			map.put("pagerPort", (String) context.get("pagerPort"));
			map.put("pagerSpeed", (String) context.get("pagerSpeed"));
			map.put("pagerAlphaPhone", (String) context.get("pagerAlphaPhone"));
			map.put("pagerAlphaPIN", (String) context.get("pagerAlphaPIN"));
			map.put("pagerDirectPhone", (String) context
					.get("pagerDirectPhone"));
			map.put("pagerOptionPhone", (String) context
					.get("pagerOptionPhone"));
			map.put("pagerCustom", (String) context.get("pagerCustom"));
			map.put("pagerOption", (String) context.get("pagerOption"));
			map.put("pagerType", (String) context.get("pagerType"));

			ctx.getDispatcher().runSync("savePagerChangeValue",
					UtilMisc.toMap("Value", map));
			Map<String, Object> retmap = ServiceUtil.returnSuccess();
			return retmap;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<String, Object> pagerSettingInfo(DispatchContext ctx,
			Map<?, ?> context) {
		String id = (String) context.get("id");
		Map<String, Object> map = new HashMap<String, Object>();
		if (id == null||"".equalsIgnoreCase(id)) {
			map.put("_id", "");
			map.put("_name", "");
			map.put("_disabled", "no");
			map.put("_pagerSpeed", "");
			map.put("_pagerAlphaPhone", "");
			map.put("_pagerAlphaPIN", "");
			map.put("_pagerDirectPhone", "");
			map.put("_pagerOptionPhone", "");
			map.put("_pagerCustom", "");
			map.put("_pagerOption", "");
			map.put("_pagerType", "custom");
			Map retMap = ServiceUtil.returnSuccess();
			retMap.put("result", map);
			return retMap;
		} else {
			try {
				Map map1 = (Map<String, Object>) (ctx.getDispatcher().runSync(
						"pagerSettingInfoValue", UtilMisc.toMap("id", id)))
						.get("result");

				Map retMap = ServiceUtil.returnSuccess();
				retMap.put("result", map1);
				return retMap;
			} catch (GenericServiceException e) {
				return ServiceUtil.returnFailure(e.getMessage());
			}
		}

	}

	public static Map<String, Object> saveAddPagerSetting(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			String id = (String) context.get("id");
			if (id != null && ("".equals(id) == false)) {
				String _name = ((String) context.get("additionalPagerName") == null) ? ""
						: (String) context.get("additionalPagerName");
				String _disabled = ((String) context.get("disabled") == null) ? ""
						: "CHECKED";
				String _pagerAlphaPIN = ((String) context.get("pagerAlphaPIN") == null) ? ""
						: (String) context.get("pagerAlphaPIN");
				String _pagerAlphaPhone = ((String) context
						.get("pagerAlphaPhone") == null) ? ""
						: (String) context.get("pagerAlphaPhone");
				String _pagerCustom = ((String) context.get("pagerCustom") == null) ? ""
						: (String) context.get("pagerCustom");
				String _pagerDirectPhone = ((String) context
						.get("pagerDirectPhone") == null) ? ""
						: (String) context.get("pagerDirectPhone");
				String _pagerOption = ((String) context.get("pagerOption") == null) ? ""
						: (String) context.get("pagerOption");
				String _pagerOptionPhone = ((String) context
						.get("pagerOptionPhone") == null) ? ""
						: (String) context.get("pagerOptionPhone");
				String _pagerSpeed = ((String) context.get("pagerSpeed") == null) ? ""
						: (String) context.get("pagerSpeed");
				String _pagerType = ((String) context.get("pagerType") == null) ? ""
						: (String) context.get("pagerType");
				Map time = Assistant.ScheduleOperate(context);
				String timeValue = (String) time.get("timeString");

				String pagerValue = " _id=" + id + " _name=" + _name
						+ " _disabled=" + _disabled + " _pagerAlphaPIN="
						+ _pagerAlphaPIN + " _pagerAlphaPhone="
						+ _pagerAlphaPhone + " _pagerCustom=" + _pagerCustom
						+ " _pagerDirectPhone=" + _pagerDirectPhone
						+ " _pagerOption=" + _pagerOption
						+ " _pagerOptionPhone=" + _pagerOptionPhone
						+ " _pagerSpeed=" + _pagerSpeed + " _pagerType="
						+ _pagerType + " _schedule=" + timeValue;
				Map value = (Map) Config.getConfigByName("_additionalPager");
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
				ctx.getDispatcher().runSync("UpdateAddPagerSetting",
						UtilMisc.toMap("idx", idx, "pagerValue", pagerValue));
				return ServiceUtil.returnSuccess();
			} else {
				Map<String, Object> value = new HashMap<String, Object>();

				value.put("_name", ((String) context
								.get("additionalPagerName") == null) ? ""
								: (String) context.get("additionalPagerName"));
				value.put("_disabled",
						((String) context.get("disabled") == null) ? ""
								: "CHECKED");
				value.put("_pagerAlphaPIN", ((String) context
						.get("pagerAlphaPIN") == null) ? "" : (String) context
						.get("pagerAlphaPIN"));
				value.put("_pagerAlphaPhone", ((String) context
						.get("pagerAlphaPhone") == null) ? ""
						: (String) context.get("pagerAlphaPhone"));
				value.put("_pagerCustom",
						((String) context.get("pagerCustom") == null) ? ""
								: (String) context.get("pagerCustom"));
				value.put("_pagerDirectPhone", ((String) context
						.get("pagerDirectPhone") == null) ? ""
						: (String) context.get("pagerDirectPhone"));
				value.put("_pagerOption",
						((String) context.get("pagerOption") == null) ? ""
								: (String) context.get("pagerOption"));
				value.put("_pagerOptionPhone", ((String) context
						.get("pagerOptionPhone") == null) ? ""
						: (String) context.get("pagerOptionPhone"));
				value.put("_pagerSpeed",
						((String) context.get("pagerSpeed") == null) ? ""
								: (String) context.get("pagerSpeed"));
				value.put("_pagerType",
						((String) context.get("pagerType") == null) ? ""
								: (String) context.get("pagerType"));
				Map time = Assistant.ScheduleOperate(context);

				value.put("_schedule",
						((String) time.get("timeString") == null) ? ""
								: (String) time.get("timeString"));

				ctx.getDispatcher().runSync("saveAddPagerSettingValue",
						UtilMisc.toMap("value", value));
				return ServiceUtil.returnSuccess();
			}
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static Map<String, Object> getPagerPreferenceInfo(
			DispatchContext ctx, Map<?, ?> context) {
		String id = (String) context.get("id");
		try {
			Map<String, Object> valueMap = new HashMap<String, Object>();
			Map<String, Object> retMap = ServiceUtil.returnSuccess();
			if (id == null) {
				valueMap.put("id", "");
				valueMap.put("value", Assistant.getPagerDial("message"));
				retMap.put("result", valueMap);
				return retMap;
			} else {
				// Map value = (Map) Config.getConfigByName("_additionalPager");

				Map<String, Object> value = (Map<String, Object>) (ctx
						.getDispatcher().runSync("getConfigByName", UtilMisc
						.toMap("attrName", "_additionalPager"))).get("result");

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
				Map map = BaseClass.stringToMap(mapString);
				valueMap.put("id", id);
				valueMap.put("value", Assistant.getPagerDial1(map));
				retMap.put("result", valueMap);
				return retMap;

			}
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

}
