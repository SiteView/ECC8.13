package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericEntity;
import org.ofbiz.entity.GenericEntityException;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.GenericServiceException;
import org.ofbiz.service.LocalDispatcher;
import org.ofbiz.service.ServiceUtil;

import com.dragonflow.Api.APIPreference;
import com.dragonflow.Api.SSInstanceProperty;
import com.siteview.svecc.service.BaseClass;

public class EmailOperate extends BaseClass {

	public static Map<?, ?> getEmailPreferences(DispatchContext dctx,
			Map context) {
		try {
			Map<String, Object> retmap = ServiceUtil.returnSuccess();
			retmap.put("result", getEmailPreferences());
			return retmap;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<?, ?> getEmailPreferences() throws Exception {
		long tem = 1;
		Map<String, Object> map = new HashMap<String, Object>();
		map.put("mailServer", (Config.configGet("_mailServer")==null)?"":Config.configGet("_mailServer"));
		map.put("autoEmail", (Config.configGet("_autoEmail")==null)?"":Config.configGet("_autoEmail"));
		map.put("autoDaily", (Config.configGet("_autoDaily")==null)?"":Config.configGet("_autoDaily"));
		map.put("autoStartup", (Config.configGet("_autoStartup")==null)?"":Config.configGet("_autoStartup"));
		map.put("fromAddress", (Config.configGet("_fromAddress")==null)?"":Config.configGet("_fromAddress"));
		map.put("mailServerBackup", (Config.configGet("_mailServerBackup")==null)?"":Config.configGet("_mailServerBackup"));
		return map;
	}

	public static Map<?, ?> setEmailPreferences(DispatchContext ctx,
			Map<?, ?> context) {
		// 设置数据库中EmailPreferences信息
		try {
			setEmailPreferences(context);
		} catch (Exception e) {
			return ServiceUtil.returnFailure();
		}
		return ServiceUtil.returnSuccess();

	}

	public static void setEmailPreferences(Map<?, ?> context) throws Exception {
		Map map = (Map) context.get("Value");
		Config.configPut("_mailServer", (String) map.get("mailServer"));
		Config.configPut("_autoEmail", (String) map.get("autoEmail"));
		Config
				.configPut("_autoDaily",
						(context.get("autoDaily") == null) ? "unchecked" : ""
								.equals(map.get("autoDaily")) ? "unchecked"
								: "checked");
		Config.configPut("_autoStartup",
				(context.get("autoStartup") == null) ? "unchecked" : ""
						.equals(map.get("autoStartup")) ? "unchecked"
						: "checked");
		Config.configPut("_fromAddress", (String) map.get("fromAddress"));
		Config.configPut("_mailServerBackup", (String) map
				.get("mailServerBackup"));
		refrashData();

	}

	public static Map<?, ?> AddEmailSetting(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			AddEmailSetting(context);
		} catch (Exception e) {
			return ServiceUtil.returnFailure();
		}
		return ServiceUtil.returnSuccess();

	}

	public static void AddEmailSetting(Map<?, ?> context) throws Exception {

		Map value = (Map) context.get("Value");
		List<SSInstanceProperty> assinstanceproperty = new ArrayList<SSInstanceProperty>();
		Set<String> keys = (Set<String>) value.keySet();
		for (String key : keys) {
			Object val = value.get(key);
			assinstanceproperty.add(new SSInstanceProperty(key, val));
		}
		SSInstanceProperty returnValue = new APIPreference().create(
				"MailInstancePreferences", assinstanceproperty
						.toArray(new SSInstanceProperty[0]));
		System.out.println("~~~~~~~~~~~~~~~~~~~~~~~000");
		// shedule 操作没有做，可以按下面代码修改

		// List<SSInstanceProperty> assinstanceproperty = new
		// ArrayList<SSInstanceProperty>();
		// Set<String> keys = (Set<String>) value.keySet();
		// for (String key : keys){
		// Object val = value.get(key);
		// assinstanceproperty.add(new SSInstanceProperty(key,val));
		// }
		// SSInstanceProperty returnValue = new
		// APIPreference().create("MailInstancePreferences",
		// assinstanceproperty.toArray(new SSInstanceProperty[0]));

	}

	public static Map<?, ?> delAdditionalEmail(DispatchContext ctx,
			Map<?, ?> context) throws Exception {
		try {
			delAdditionalEmail(context);
			return ServiceUtil.returnSuccess();
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static void delAdditionalEmail(Map<?, ?> context) throws Exception {
		String id = (String) context.get("id");
		try {
			com.dragonflow.Api.APIPreference apipreference = new APIPreference();
			apipreference.delete("MailInstancePreferences", "_id", id);
		} finally {
			refrashData();
		}
	}

	private static void refrashData() throws Exception {
		Config.clearCache();
	}
}