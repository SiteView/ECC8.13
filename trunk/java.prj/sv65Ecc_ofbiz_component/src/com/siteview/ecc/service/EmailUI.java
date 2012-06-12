package com.siteview.ecc.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.LocalDispatcher;
import org.ofbiz.service.ServiceUtil;

import com.siteview.svecc.service.Assistant;
import com.siteview.svecc.service.BaseClass;
import com.siteview.svecc.service.Config;

import com.siteview.svecc.service.Message;

public class EmailUI {

	public static Map<String, Object> getEmailPreferences(
	// 得到缺省值
			DispatchContext ctx, Map<?, ?> context) {

		try {
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", (ctx.getDispatcher().runSync(
					"getEmailDefaultPrefefencesValue", new HashMap()))
					.get("result"));
			return retresult;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<?, ?> setEmailPreferences(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			Map<String, Object> map = new HashMap<String, Object>();

			map.put("mailServer", (String) context.get("mailServer"));
			map.put("autoEmail", (String) context.get("autoEmail"));
			map.put("autoDaily", (String) context.get("autoDaily"));
			map.put("autoStartup", (String) context.get("autoStartup"));
			map.put("fromAddress", (String) context.get("fromAddress"));
			map.put("mailServerBackup", (String) context
					.get("mailServerBackup"));

			ctx.getDispatcher().runSync("saveEmailChangeValue",
					UtilMisc.toMap("Value", map));
			Map<String, Object> retmap = ServiceUtil.returnSuccess();
			return retmap;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<?, ?> EmailSettingsInfo(DispatchContext ctx,
			Map<?, ?> context) throws Exception {

		String id = (String) context.get("id");
		Map<Object, Object> map = new HashMap<Object, Object>();
		if (id == null) {
			map.put("_name", "");
			map.put("_email", "");
			map.put("_disabled", "");
			map.put("_template", "");

			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", map);
			return retresult;
		} else {

			Map value = (Map) ctx.getDispatcher().runSync("getConfigByName",
					UtilMisc.toMap("attrName", "_additionalMail"))
					.get("result");
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
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", map);
			return retresult;
		}
	}

	public static Map<?, ?> AddEmailSetting(DispatchContext ctx,
			Map<?, ?> context) {
		// 将设置的Email信息储存到DB中
		try {
			String id = (String) context.get("id");
			if (id != null && id != "") {
				System.out.println("111~~~~~~~~~~~~~~~~~~~~~~~~~~~~" + id);
				return updateAdditionalEmail(ctx, context);
			} else {
				if ((Boolean) Assistant.ScheduleOperate(context).get("sodier") == false) {
					return ServiceUtil.returnError(Message.getMessage(3009L));
				} else {
					System.out.println("222~~~~~~~~~~~~~~~~~~~~~~~~~~~" + id);
					AddEmailSetting(ctx.getDispatcher(), context);

				}
			}
		} catch (Exception e) {
			Map<String, Object> map = ServiceUtil.returnFailure(e.getMessage());
			map.put("result", e.getMessage());
			return map;
		}
		Map<String, Object> map = ServiceUtil.returnSuccess();
		map.put("result", "success");
		return map;
	}

	public static void AddEmailSetting(LocalDispatcher dispatcher,
			Map<?, ?> context) throws Exception {

		Map<String, Object> value = new HashMap<String, Object>();
		value.put("_name", (String) context.get("SettingName"));
		value.put("_email", (String) context.get("emailTo"));
		if ((String) context.get("additionalMailDisabled") == null) {
			value.put("_disabled", "");
		} else {
			value.put("_disabled", (String) context
					.get("additionalMailDisabled"));
		}

		value.put("_template", (String) context.get("additionalMailTemplate"));
		System.out.println("3333~~~~~~~~~~~~~~~~~~~~" + value);
		dispatcher.runSync("saveAddEmailSettingValue", UtilMisc.toMap("Value",
				value));

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

	public static Map<?, ?> updateAdditionalEmail(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			if ((Boolean) Assistant.ScheduleOperate(context).get("sodier") == false) {
				Map<String, Object> retresult = ServiceUtil
						.returnFailure(Message.getMessage(3009L));
				return retresult;
			} else {
				String id = (String) context.get("id");
				String SettingName = (String) context.get("SettingName");
				String emailTo = (String) context.get("emailTo");
				String additionalMailDisabled = "";
				if (((String) context.get("additionalMailDisabled")) == null) {
					additionalMailDisabled = "";
				} else {
					additionalMailDisabled = (String) context
							.get("additionalMailDisabled");
				}
				String additionalMailTemplate = (String) context
						.get("additionalMailTemplate");

				String scheduleString = (String) Assistant.ScheduleOperate(
						context).get("timeString");
				String mailValue = "";
				String sheduleValue = "";
				mailValue = " _id=" + id + " _name=" + SettingName + " _email="
						+ emailTo + " _disabled=" + additionalMailDisabled
						+ " _template=" + additionalMailTemplate;

				sheduleValue = " _id=" + id + " _name=" + SettingName
						+ scheduleString;
				// look for the idx:
				List<GenericValue> list = ctx.getDelegator().findList(
						"SvMasterConfig", null, null, null, null, false);
				boolean flag = true;
				long idx = 0;
				for (GenericValue val : list) {
					String value = (String) val.get("attrValue");

					String[] temple = value.split("_");
					for (int i = 1; i < temple.length; i++) {
						String tem = "id=" + id;
						String tem1 = "id=" + id + " ";
						if (tem.equals(temple[i]) || (tem1.equals(temple[i]))) {
							flag = false;
							break;
						}
					}
					idx = (Long) val.get("idx");
					if (flag == false) {
						break;
					}
				}
				ctx.getDispatcher().runSync(
						"updConfig",
						UtilMisc.toMap("attrName", "_additionalMail", "idx",
								idx, "value", mailValue));
				ctx.getDispatcher().runSync(
						"updConfig",
						UtilMisc.toMap("attrName", "_additionalSchedule",
								"idx", idx, "value", sheduleValue));

			}
		} catch (Exception e) {
			Map result = ServiceUtil.returnFailure(e.getMessage());
			return result;
		}
		Map<String, Object> map = ServiceUtil.returnSuccess();
		map.put("result", "scucess");
		return map;

	}

	public static Map<?, ?> delAdditionalEmail(DispatchContext ctx,
			Map<?, ?> context) {
		String id = (String) context.get("id");
		try {
			ctx.getDispatcher().runSync("delAdditionalEmail",
					UtilMisc.toMap("id", id));
			return ServiceUtil.returnSuccess();
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static Map<String, Object> getAdditionalEmailList(
			DispatchContext ctx, Map<?, ?> context) {
		try {
			Map<String, Object> map2 = ServiceUtil.returnSuccess();

			List<Map<?, ?>> list = new ArrayList<Map<?, ?>>();
			Map retDataMap = Config.getConfigByName("_additionalMail");
			if (retDataMap == null || retDataMap.size() == 0
					|| retDataMap.isEmpty()) {
				Map<String, Object> map1 = new HashMap<String, Object>();
				map1.put("_id", "no");
				map1.put("_name", "");
				map1.put("_email", "");
				map1.put("_disabled", "no additional e-mail settings");
				list.add(map1);
			} else {
				// 接下来去map中的值放到list中
				Iterator it = retDataMap.keySet().iterator();
				while (it.hasNext()) {
					String key = (String) it.next();
					String value = (String) (retDataMap.get(key));
					list.add(BaseClass.stringToMap(value));
				}
			}

			map2.put("result", list);
			return map2;
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static Map<String, Object> sendEmail(DispatchContext ctx,
			Map<?, ?> context) {
		String Mailerver = (String) context.get("Mailerver");
		String BackupMailServer = (String) context.get("BackupMailServer");
		String Subject = (String) context.get("subject")
				+ com.dragonflow.SiteView.Platform.productName;
		String content = (String) context.get("content")
				+ "This is a test.  This is only a test.\n\n - "
				+ com.dragonflow.SiteView.Platform.productName;

		String emailAddress = (String) context.get("emailAddress");
		String[] emailArray = emailAddress.split(",");
		for (int i = 0; i < emailArray.length; i++) {
			String message1 = Assistant.sendMail(Mailerver, emailArray[i],
					Subject, content);
			if (message1.equals("success") == false) {
				String message2 = Assistant.sendMail(BackupMailServer,
						emailArray[i], Subject, content);
				if (message2.equals("success") == false) {
					return ServiceUtil.returnError("fail");
				}
			}
		}

		return ServiceUtil.returnSuccess("success");
	}
}
