package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

import com.siteview.svecc.service.BaseClass;
public class PermissionOperate extends BaseClass{
	
	public static final String module = User.class.getName();
	
	public static List<Map<String,Object>> getAllPermissionTypeAndAttrValue() throws Exception{
		return getAllPermissionTypeAndAttrValue(getGenericDelegator());
		}
	
	public static List<Map<String,Object>> getAllPermissionTypeAndAttrValue(GenericDelegator delegator) throws Exception{
		List<GenericValue> list =delegator.findList("SvUserPermissionType", null, null, null, null, false);
		List<Map<String,Object>> retList=new ArrayList<Map<String,Object>>();
		for(GenericValue val:list){
			Map<String,Object> map=new HashMap<String,Object>();
			if(checkData(val.get("attrName")))  map.put("attrName", val.get("attrName"));
			if(checkData(val.get("label")))  map.put("label", val.get("label"));
			if(checkData(val.get("description")))  map.put("description", val.get("description"));
			retList.add(map);
			
		}
		return retList;
	}
	
	public static Map<?,?> getAllPermissionTypeAndAttrValue(DispatchContext ctx,Map<?,?> context){

    		String id=(String)context.get("userId");   	
    		
		try{
			Map<String,Object> retresult=ServiceUtil.returnSuccess();
			retresult.put("result",getResultList(id,ctx,getAllPermissionTypeAndAttrValue(ctx.getDelegator())));
			return retresult;
		}catch(Exception e){
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getAllUser: " + e.toString());
			retresult.put("result", new ArrayList<Map<String, Object>>());
			retresult.put("message", e.toString());
			return retresult;			
		}
	}
	
	public static List<Map> getResultList(String id,DispatchContext ctx,List allPermissionList) throws Exception{
		
		Map<String, Object> map = ctx.getDispatcher().runSync("getUserPermissionById", 
				UtilMisc.toMap(
						"id",id
				)
				);		
		Map<String, Object> newmap = (Map<String, Object>)map.get("result");
				
		List<Map> list=allPermissionList;
			for(Map permissionMap:list){
				String attrName=(String) permissionMap.get("attrName");
				for(String key : newmap.keySet()){
					if(attrName.equals(key)){
						permissionMap.put("attrValue",(Boolean)newmap.get(key));
					
					}
				}
	     	}
		return  list;
		}
	
}
