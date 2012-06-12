package com.siteview.ecc.service;

import java.util.HashMap;
import java.util.Map;

import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.LocalDispatcher;
import org.ofbiz.service.ServiceUtil;
import com.siteview.svecc.service.BaseClass;
import com.siteview.svecc.service.Message;

//本类执行与用户有关的操作
public class UserUI {
	public static final String module = UserUI.class.getName();

	public static Map<String, Object> getEveryUserInfo(DispatchContext dctx,
			Map context) {
		//得到指定id的用户信息
		try {
			Map<String, Object> result = new HashMap<String, Object>();
			//String monitorId = (String)context.get("monitorId");              
			String id = (String) context.get("userId");
			Map<String, Object> map = dctx.getDispatcher().runSync("getUserById", UtilMisc.toMap("id", id));
			Map<String, Object> newmap = (Map<String, Object>) map.get("result");
			if ((Boolean) newmap.get("disabled")) {
				newmap.put("disabled", "Y");
			} else {
				newmap.put("disabled", "N");
			}

			result.put("result", newmap);
			return result;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<String, Object> UserInfoOperator(Map context) {
		//实现对用户信息操作
		try {
			Map<String, Object> map = new HashMap<String, Object>();
			map.put("id", context.get("userId"));
			map.put("disabled", Boolean.valueOf("Y".equals(context.get("disabled"))));
			map.put("group", context.get("group"));
			map.put("ldapserver", context.get("ldapserver"));
			map.put("login", context.get("login"));
			map.put("password", context.get("password"));
			map.put("realName", context.get("realName"));
			map.put("securityprincipal", context.get("securityprincipal"));
			return map;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<?, ?> delUIUser(DispatchContext dctx, Map context) {
		//删除用户
		try {
			LocalDispatcher dispatcher = dctx.getDispatcher();
			dispatcher.runSync("updUserPermission", UtilMisc.toMap("id",context.get("id"), "data", new HashMap()));
			dispatcher.runSync("delUser", UtilMisc.toMap("id", context.get("id")));
			Map<String, Object> retmap = ServiceUtil.returnSuccess();
			return retmap;
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<String, Object> modifyUserInfo(DispatchContext dctx,
			Map context) {
		//更改用户信息
		try {
			Map<String, Object> result = new HashMap<String, Object>();
			LocalDispatcher dispatcher = dctx.getDispatcher();
			dispatcher.runSync("updUser", UtilMisc.toMap("id", context.get("id"), "data", UserInfoOperator(context)));

			return dispatcher.runSync("getUserById", UtilMisc.toMap("id",context.get("id")));
		} catch (Exception ex) {
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<String, Object> savePwd(DispatchContext dctx, Map context) {
		//存储密码
		String id = (String) context.get("userId");
		String newPwd = (String) context.get("newPwd");
		String oldPwd = (String) context.get("oldPwd");
		String confirmPwd = (String) context.get("confirmPwd");
		Map map = null;
		try {
			if (oldPwd == null || oldPwd.equals(""))
				throw new Exception(Message.getMessage(3005L));
			if (newPwd == null || newPwd.equals(""))
				throw new Exception(Message.getMessage(3006L));
			if (confirmPwd == null || confirmPwd == "")
				throw new Exception(Message.getMessage(3007L));
			if (newPwd.equals(confirmPwd) == false)
				throw new Exception(Message.getMessage(3002L));
			//调用服务
			LocalDispatcher Dispatcher = dctx.getDispatcher();
			map = Dispatcher.runSync("chgUserPassword", UtilMisc.toMap("id",
					(String) context.get("userId"), "oldPassword",
					(String) context.get("oldPwd"), "newPassword",
					(String) context.get("newPwd")));

			String message = (String) map.get("message");
			if (message != null)
				throw new Exception(message);
			return ServiceUtil.returnSuccess();
		} catch (Exception ex) {
			String message = map == null ? null : (String) map.get("message");
			Map retmap = ServiceUtil.returnFailure(message == null ? ex.getMessage() : message);
			retmap.put("id", id);
			return retmap;
		}
	}

	public static Map<String, Object> saveUser(DispatchContext dctx, Map context) {
		//存储用户信息
		Map map = null;
		try {
			String id = (String) context.get("userId");
			String login = (String) context.get("login");
			String pwd = (String) context.get("password");
			String realName = (String) context.get("realName");
			//if(id==null||id.equals(""))
			//throw new Exception(Message.getMessage(3000L));
			if (pwd == null || pwd.equals(""))
				throw new Exception(Message.getMessage(3001L));
			if (login == null || login.equals(""))
				throw new Exception(Message.getMessage(3003L));
			if (realName == null || realName == "")
				throw new Exception(Message.getMessage(3004L));

			LocalDispatcher dispatcher = dctx.getDispatcher();
			Map<String, Object> params = new HashMap<String, Object>();
			params.put("data", UserInfoOperator(context));
			map = dispatcher.runSync("addUser", params);

			//			String message = (String)map.get("message");
			//	    	if (message!=null) throw new Exception(message);

			return ServiceUtil.returnSuccess();
		} catch (Exception ex) {
			String message = map == null ? null : (String) map.get("message");
			Map retmap = ServiceUtil.returnFailure(message == null ? ex.getMessage() : message);
			return retmap;
		}
	}

	private static String getBooleanValue(Object val)
	//将布尔类型的disabled转换为字符串类型
	{
		if (val == null)
			return "N";
		return "Y".equals(val) ? "Y" : "N";
	}

	public static Map<String, Object> getUserPermissionByIdForDisp(
			DispatchContext ctx, Map context)
	// 将permission对象中的disabled改成字符串类型
	{
		try {
			String id = (String) BaseClass.getNotOptionalValue(context,
					"userId");

			Map<String, Object> retresult = ServiceUtil.returnSuccess();

			Map<String, Object> map = ctx.getDispatcher().runSync("getUserPermissionById", UtilMisc.toMap("id", id));

			Map<String, Object> newmap = (Map<String, Object>) map.get("result");

			Map<String, Object> retmap = new HashMap<String, Object>();
			for (String key : newmap.keySet()) {
				Object obj = newmap.get(key);
				if (obj == null)
					continue;
				if ((Boolean) obj) {
					retmap.put(key, "Y");
				} else {
					retmap.put(key, "N");
				}
			}

			retresult.put("result", retmap);
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getUserPermissionById: " + e.toString());
			retresult.put("result", new HashMap<String, Object>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}

}
