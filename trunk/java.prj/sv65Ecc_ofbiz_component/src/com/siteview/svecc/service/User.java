package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityOperator;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

public class User extends BaseClass{
	public static final String module = User.class.getName();
	
	
	public static Map<?, ?> addUser(DispatchContext ctx, Map<?, ?> context) {
		try {
			Object data = getNotOptionalValue(context,"data");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("message", addUser(convert(data),ctx.getDelegator()));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error addUser: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}
	public static String addUser(Map<String,Object> data)throws Exception {
		return addUser(data,getGenericDelegator());
	}

	public static String addUser(Map<String,Object> data,GenericDelegator delegator)throws Exception {
		try{
			checkLogin((String)data.get("login"),delegator);
			
			GenericValue newValue = delegator.makeValue("SvUser");
			String id = delegator.getNextSeqId("SvUser");
			newValue.set("id", id);
			if (checkData(data.get("disabled"))) newValue.set("disabled", data.get("disabled"));
			if (checkData(data.get("group"))) newValue.set("group", data.get("group"));
			if (checkData(data.get("ldapserver"))) newValue.set("ldapserver", data.get("ldapserver"));
			if (checkData(data.get("login"))) newValue.set("login", data.get("login"));
			if (checkData(data.get("password"))) newValue.set("password", data.get("password"));
			if (checkData(data.get("realName"))) newValue.set("realName", data.get("realName"));
			if (checkData(data.get("securityprincipal"))) newValue.set("securityprincipal", data.get("securityprincipal"));
			newValue.create();
			return id;
		}finally{
			refrashData();
		}
	}
	public static Map<?, ?> delUser(DispatchContext ctx, Map<?, ?> context) {
		try {
			String id = (String) getNotOptionalValue(context,"id");
			delUser(id,ctx.getDelegator());
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error delUser: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static void delUser(String id)throws Exception {
		delUser(id,getGenericDelegator());
	}

	public static void delUser(String id,GenericDelegator delegator)throws Exception {
		try{
	        EntityCondition whereCondition = EntityCondition.makeCondition("id", EntityOperator.EQUALS, id);
	        delegator.removeByCondition("SvUser", whereCondition);
		}finally{
			refrashData();
		}
	}
	public static Map<?, ?> getAllUser(DispatchContext ctx, Map<?, ?> context) {
		try {
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getAllUser(ctx.getDelegator()));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getAllUser: " + e.toString());
			retresult.put("result", new ArrayList<Map<String, Object>>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static List<Map<String, Object>> getAllUser()throws Exception {
		return getAllUser(getGenericDelegator());
	}
	public static List<Map<String, Object>> getAllUser(GenericDelegator delegator)throws Exception {
		List<GenericValue> list = delegator.findList("SvUser", null, null, null, null, false);
        List<Map<String, Object>> retlist = new ArrayList<Map<String, Object>>();
        
        for (GenericValue val : list){
        	Map<String, Object> map = new HashMap<String, Object>();
        	if (checkData(val.get("id"))) map.put("id", val.get("id"));
        	if (checkData(val.get("disabled"))) map.put("disabled",val.getBoolean("disabled"));
        	if (checkData(val.get("group"))) map.put("group", val.get("group"));
        	if (checkData(val.get("ldapserver"))) map.put("ldapserver", val.get("ldapserver"));
        	if (checkData(val.get("login"))) map.put("login", val.get("login"));
        	if (checkData(val.get("realName"))) map.put("realName", val.get("realName"));
        	if (checkData(val.get("securityprincipal"))) map.put("securityprincipal", val.get("securityprincipal"));
    		retlist.add(map);
        }
		return retlist;
	}
	public static Map<?, ?> getUserById(DispatchContext ctx, Map<?, ?> context) {
		try {
			String id = (String) getNotOptionalValue(context,"id");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getUserById(id));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getGroupById: " + e.toString());
			retresult.put("result", new HashMap<String, Object>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static Map<String, Object> getUserById(String id)throws Exception {
		return getUserById(id,getGenericDelegator());
	}
	public static Map<String, Object> getUserById(String id,GenericDelegator delegator)throws Exception {
        EntityCondition whereCondition = EntityCondition.makeCondition("id", EntityOperator.EQUALS, id);

        List<GenericValue> list = delegator.findList("SvUser", whereCondition,null,null,null,false);
        Map<String, Object> map = new HashMap<String, Object>();
        for (GenericValue val : list){
        	map.put("id", id);
        	if (checkData(val.get("disabled"))) map.put("disabled", val.getBoolean("disabled"));
        	if (checkData(val.get("group"))) map.put("group", val.get("group"));
        	if (checkData(val.get("ldapserver"))) map.put("ldapserver", val.get("ldapserver"));
        	if (checkData(val.get("login"))) map.put("login", val.get("login"));
        	if (checkData(val.get("realName"))) map.put("realName", val.get("realName"));
        	if (checkData(val.get("securityprincipal"))) map.put("securityprincipal", val.get("securityprincipal"));
    		return map;
        }
		return map;
	}
	public static Map<?, ?> checkUser(DispatchContext ctx, Map<?, ?> context) {
		try {
			String username = (String) getNotOptionalValue(context,"username");
			String password = (String) getNotOptionalValue(context,"password");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			String id = checkUser(username,password,ctx.getDelegator());
			retresult.put("result", id!=null);
			retresult.put("id", id);
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error checkUser: " + e.toString());
			retresult.put("result", Boolean.FALSE);
			retresult.put("message", e.toString());
			return retresult;
		}
	}	

	public static String checkUser(String username,String password)throws Exception {
		return checkUser(username,password,getGenericDelegator());
	}

	public static String checkUser(String username,String password,GenericDelegator delegator)throws Exception {
		checkLogin(username,delegator);
		
        EntityCondition whereCondition = EntityCondition.makeCondition(
        		UtilMisc.toList(
        		        EntityCondition.makeCondition("login", EntityOperator.EQUALS, username),
        		        EntityCondition.makeCondition("password", EntityOperator.EQUALS, password)
        		),
        		EntityOperator.AND
        );
        
        List<GenericValue> retlist = delegator.findList("SvUser", whereCondition, null,null,null,false);
        if (retlist.size()>0) {
        	return retlist.get(0).getString("id");
        }
		return null;
	}
	
	public static Map<?, ?> updUser(DispatchContext ctx, Map<?, ?> context) {
		try {
			String id = (String) getNotOptionalValue(context,"id");
			Object data = getNotOptionalValue(context,"data");

			updUser(id,convert(data),ctx.getDelegator());
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error updUser: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static void updUser(String id,Map<String,Object> data)throws Exception {
		updUser(id,data,getGenericDelegator());
	}
	public static void updUser(String id,Map<String,Object> data,GenericDelegator delegator)throws Exception {
		try{
			//String login = (String)data.get("login");
			//checkLogin(login,delegator);
	        EntityCondition whereCondition = EntityCondition.makeCondition("id", EntityOperator.EQUALS, id);
	        
	        List<GenericValue> list = delegator.findList("SvUser", whereCondition,null,null,null,false);
	        for (GenericValue val : list){
	        	if (checkData(data.get("disabled"))) val.set("disabled", data.get("disabled"));
	        	if (checkData(data.get("group"))) val.set("group", data.get("group"));
	        	if (checkData(data.get("ldapserver"))) val.set("ldapserver", data.get("ldapserver"));
	        	//if (checkData(data.get("login"))) val.set("login", data.get("login"));
	        	if (checkData(data.get("realName"))) val.set("realName", data.get("realName"));
	        	if (checkData(data.get("securityprincipal"))) val.set("securityprincipal", data.get("securityprincipal"));
	    		val.store();
	    		return;
	        }
		}finally{
			refrashData();
		}
	}
	
	public static Map<?, ?> chgUserPassword(DispatchContext ctx, Map<?, ?> context) {
		try {
			String id = (String) getNotOptionalValue(context,"id");
			String oldPassword = (String) getNotOptionalValue(context,"oldPassword");
			String newPassword = (String) getNotOptionalValue(context,"newPassword");

			chgUserPassword(id,oldPassword,newPassword,ctx.getDelegator());
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error chgUserPassword: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	
	public static void chgUserPassword(String id,String oldPassword,String newPassword)throws Exception {
		chgUserPassword(id,oldPassword,newPassword,getGenericDelegator());
	}
	
	public static void chgUserPassword(String id,String oldPassword,String newPassword,GenericDelegator delegator)throws Exception {
		if (id==null) throwException(THROW_TYPE_OPTIONAL_PARAM,"id");
		if (oldPassword==null) throwException(THROW_TYPE_OPTIONAL_PARAM,"oldPassword");
		if (newPassword==null) throwException(THROW_TYPE_OPTIONAL_PARAM,"newPassword");
		if (newPassword.equals(oldPassword)) throwException(THROW_TYPE_PASSWORD_EQUALS);
		try{
	        EntityCondition whereCondition = EntityCondition.makeCondition("id", EntityOperator.EQUALS, id);
	        
	        List<GenericValue> list = delegator.findList("SvUser", whereCondition,null,null,null,false);
	        for (GenericValue val : list){
	        	if (! oldPassword.equals(val.getString("password")))
	        		throwException(THROW_TYPE_PASSWORD_NOT_VALID,"oldPassword");
	        	val.set("password", newPassword);
	    		val.store();
	    		return;
	        }
	        throwException(THROW_TYPE_PARAM_NOT_FOUND,"id(" + id + ")");
		}finally{
			refrashData();
		}
		
	}
	
	public static void checkLogin(String login) throws Exception
	{
		checkLogin(login,getGenericDelegator());
	}
	private static void checkLogin(String login,GenericDelegator delegator) throws Exception
	{
		if (login == null) throwException(THROW_TYPE_OPTIONAL_PARAM,"login(" + login + ")");
        EntityCondition whereCondition = EntityCondition.makeCondition("login", EntityOperator.EQUALS, login);
        
        long count = delegator.findCountByCondition("SvUser", whereCondition, null,null);
        if (count>1) throwException(THROW_TYPE_PARAM_DUPLICATE,"login name(" + login + ")");
		
	}
	
	private static void refrashData()
	{
		com.dragonflow.SiteView.User.unloadUsers();
		com.dragonflow.SiteView.User.loadUsers();
		
	}
	
}
