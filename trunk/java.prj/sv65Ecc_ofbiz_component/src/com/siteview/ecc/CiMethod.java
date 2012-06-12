package com.siteview.ecc;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.base.util.UtilProperties;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericPK;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityConditionList;
import org.ofbiz.entity.condition.EntityExpr;
import org.ofbiz.entity.condition.EntityOperator;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

public class CiMethod {
	public static final String resource = "EccUiLabels.xml";
	public static Map deleteCiMethod(DispatchContext ctx, Map context) {
		Map result = new HashMap();
        GenericDelegator delegator = ctx.getDelegator();
        
        GenericValue val = (GenericValue)context.get("pk");
        GenericPK pk = val.getPrimaryKey();
        try{
	        GenericValue value=delegator.findByPrimaryKeyCache(pk);
	        value.remove();
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}
	public static Map deleteCiMethodChildren(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		return result;
	}

	public static Map deleteCiMethodMany(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		return result;
	}

	public static Map copyCiMethod(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		return result;
	}
	
	public static Map getCiMethod(DispatchContext ctx, Map context) {
		Map result = new HashMap();
        GenericDelegator delegator = ctx.getDelegator();
        GenericValue val = (GenericValue)context.get("pk");
        GenericPK pk = val.getPrimaryKey();
        try{
	        GenericValue value=delegator.findByPrimaryKeyCache(pk);
	        result.putAll(value);
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}
	public static Map getCiMethodMany(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		GenericDelegator delegator = ctx.getDelegator();
		
        Object idList=context.get("idList");
        List<GenericValue> list;
        try
        {
          if(idList==null)
          {
        	  list=delegator.findAll("SvCiMethod");
        	  result.put("idList", "");
        	  result.put("ciMethodList", list);
          }
          else
        	{
        	  
        	  List orExprs =new ArrayList();
        	  String[] idArray=idList.toString().split(",");
        	  for(String id:idArray)
        		  orExprs.add(new EntityExpr("method_id",EntityOperator.EQUALS, id));
        	  EntityConditionList entityConditionList=new EntityConditionList(orExprs, EntityOperator.OR);
        	  
        	  
        	  list=delegator.findByAndCache("SvCiMethod",entityConditionList, UtilMisc.toList("method_id"));
        	  result.put("idList", idList);
        	  result.put("ciMethodList", list);
        	}
          
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}
	public static Map submitCiMethod(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		GenericDelegator delegator = ctx.getDelegator();
        GenericValue addrMap = delegator.makeValue("SvGroup");


		Locale locale = (Locale) context.get("locale");
		String errMsg = null;

        addrMap.put("group_name",(String) context.get("group_name"));
        addrMap.put("disabled",(String) context.get("disabled"));
        addrMap.put("dependon",(String) context.get("dependon"));
        addrMap.put("dependon_status",(String) context.get("dependon_status"));
        addrMap.put("parent_group_id",(String) context.get("parent_group_id"));

		
		try {
			
			delegator.create("SvGroup",addrMap);
			result.putAll(addrMap);

		} catch (Exception e) {

			Debug.logWarning(e, Group.class.toString());
			Map messageMap = UtilMisc.toMap("errMessage", e.getMessage());
			errMsg = UtilProperties.getMessage(resource,
					"groupservices.error_adding_group",
					messageMap, locale);

			return ServiceUtil.returnError(errMsg);
		}


		return result;
	}
	public static Map getCiMethodType(DispatchContext ctx, Map context) {
		Map result = new HashMap();
        GenericDelegator delegator = ctx.getDelegator();
        GenericValue val = (GenericValue)context.get("pk");
        GenericPK pk = val.getPrimaryKey();
        try{
	        GenericValue value=delegator.findByPrimaryKeyCache(pk);
	        result.putAll(value);
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}
	public static Map getCiMethodTypeMany(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		GenericDelegator delegator = ctx.getDelegator();
		
        Object idList=context.get("idList");
        List<GenericValue> list;
        try
        {
          if(idList==null)
          {
        	  list=delegator.findAll("SvCiMethodType");
        	  result.put("idList", "");
        	  result.put("ciMethodTypeList", list);
          }
          else
        	{
        	  List orExprs =new ArrayList();
        	  String[] idArray=idList.toString().split(",");
        	  for(String id:idArray)
        		  orExprs.add(new EntityExpr("methodTypeId",EntityOperator.EQUALS, id));
        	  EntityConditionList entityConditionList=new EntityConditionList(orExprs, EntityOperator.OR);
        	  
        	  
        	  list=delegator.findByAndCache("SvCiMethodType",entityConditionList, UtilMisc.toList("methodTypeId"));
        	  result.put("idList", idList);
        	  result.put("ciMethodTypeList", list);
        	}
          
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}
	
	public static Map disableMethod(DispatchContext ctx, Map context) {
		Map result = new HashMap();

		return result;
	}

	public static Map disableMethodTemp(DispatchContext ctx, Map context) {
		Map result = new HashMap();

		return result;
	}
	public static Map enableMethod(DispatchContext ctx, Map context) {
		Map result = new HashMap();

		return result;
	}
	public static Map refreshCiMethods(DispatchContext ctx, Map context) {
		Map result = new HashMap();

		return result;
	}	
	public static Map getLatestRefresh(DispatchContext ctx, Map context) {
		Map result = new HashMap();

		return result;
	}		
	
	
}
