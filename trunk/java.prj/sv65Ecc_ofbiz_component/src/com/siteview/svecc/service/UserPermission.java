package com.siteview.svecc.service;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityOperator;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

public class UserPermission extends BaseClass{
	public static final String module = UserPermission.class.getName();

	public static Map<?, ?> getUserPermissionById(DispatchContext ctx, Map<?, ?> context) {
		try {
			String id = (String)getNotOptionalValue(context,"id");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getUserPermissionById(id,ctx.getDelegator()));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getUserPermissionById: " + e.toString());
			retresult.put("result", new HashMap<String, Object>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static Map<String, Object> getUserPermissionById(String userId)throws Exception {
		return getUserPermissionById(userId,getGenericDelegator());
	}
	public static Map<String, Object> getUserPermissionById(String userId,GenericDelegator delegator)throws Exception {
        EntityCondition whereCondition = EntityCondition.makeCondition("userId", EntityOperator.EQUALS, userId);
        
        List<GenericValue> list = delegator.findList("SvUserPermission", whereCondition,null,null,null,false);
        Map<String, Object> map = new HashMap<String, Object>();
        for (GenericValue val : list){
    		map.put(val.getString("attrName"), val.getBoolean("attrValue"));
        }
		return map;
	}
	public static Map<?, ?> getUserPermission(DispatchContext ctx, Map<?, ?> context) {
		try {
			String id = (String) getNotOptionalValue(context,"id");
			String name = (String) getNotOptionalValue(context,"name");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getUserPermission(id,name,ctx.getDelegator()));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getUserPermission: " + e.toString());
			retresult.put("result", Boolean.FALSE);
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static Boolean getUserPermission(String userId,String name)throws Exception {
		return getUserPermission(userId,name,getGenericDelegator());
	}
	public static Boolean getUserPermission(String userId,String attrName,GenericDelegator delegator)throws Exception {
        EntityCondition whereCondition = EntityCondition.makeCondition(
        		UtilMisc.toList(
        		        EntityCondition.makeCondition("userId", EntityOperator.EQUALS, userId),
        		        EntityCondition.makeCondition("attrName", EntityOperator.EQUALS, attrName)
        		),
        		EntityOperator.AND
        );
        
        List<GenericValue> list = delegator.findList("SvUserPermission", whereCondition,null,null,null,false);
        for (GenericValue val : list){
        	return val.getBoolean("attrValue"); 
        }
		return Boolean.FALSE;
	}
	
	public static Map<?, ?> updUserPermission(DispatchContext ctx, Map<?, ?> context) {
		try {
			String id = (String) getNotOptionalValue(context,"id");
			Object data = getNotOptionalValue(context,"data");
			updUserPermission(id,convert(data),ctx.getDelegator());
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error updUserPermission: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static void updUserPermission(String userId,Map<String,Object> data)throws Exception {
		updUserPermission(userId,data,getGenericDelegator());
	}
	public static void updUserPermission(String userId,Map<String,Object> data,GenericDelegator delegator)throws Exception {
        EntityCondition whereCondition = EntityCondition.makeCondition("userId", EntityOperator.EQUALS, userId);
        
        List<GenericValue> list = delegator.findList("SvUserPermission", whereCondition,null,null,null,false);
        Set<String> keys = data.keySet();

        for (GenericValue val : list)
        {
    		boolean bFound = false;
    		for (String key : keys)
        	{
    			if (key == null) continue;
        		if (key.equals(val.getString("attrName")))
        		{
        			bFound = true;
        			break;
        		}
        	}
        	if(!bFound){
        		val.remove();
        	}
        }

        for (String key : keys)
        {
    		if (key == null) continue;
    		boolean bFound = false;
        	for (GenericValue val : list)
        	{
        		if (key.equals(val.getString("attrName")))
        		{
        			val.set("attrValue", data.get(key));
        			val.store();
        			bFound = true;
        			break;
        		}
        	}
        	if(!bFound){
        		GenericValue val = delegator.makeValue("SvUserPermission");
        		val.set("userId", userId);
        		val.set("attrName", key);
        		val.set("attrValue", data.get(key));
        		val.create();
        	}
        }
		
	}
	
}
