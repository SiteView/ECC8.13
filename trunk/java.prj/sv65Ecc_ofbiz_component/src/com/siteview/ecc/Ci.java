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

public class Ci {
	public static final String resource = "EccUiLabels.xml";
	
	public static Map deleteCi(DispatchContext ctx, Map context) {
		Map result = new HashMap();
        GenericDelegator delegator = ctx.getDelegator();
        //LocalDispatcher dispatcher = ctx.getDispatcher();
        
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
	
	public static Map deleteCiChildren(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		return result;
	}
	
	public static Map deleteCiMany(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		return result;
	}
	
	public static Map copyCi(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		return result;
	}	

	public static Map getCi(DispatchContext ctx, Map context) {
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
	
	public static Map getCiMany(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		GenericDelegator delegator = ctx.getDelegator();
		
        Object idList=context.get("idList");
        List<GenericValue> list;
        try
        {
          if(idList==null)
          {
        	  list=delegator.findAll("SvCi");
        	  result.put("idList", "");
        	  result.put("ciList", list);
          }
          else
        	{
        	  
        	  List orExprs =new ArrayList();
        	  String[] idArray=idList.toString().split(",");
        	  for(String id:idArray)
        		  orExprs.add(new EntityExpr("ci_id",EntityOperator.EQUALS, id));
        	  EntityConditionList entityConditionList=new EntityConditionList(orExprs, EntityOperator.OR);
        	  
        	  
        	  list=delegator.findByAndCache("SvCi",entityConditionList, UtilMisc.toList("ci_id"));
        	  result.put("idList", idList);
        	  result.put("ciList", list);
        	}
          
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}
	public static Map getCiType(DispatchContext ctx, Map context) {
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
	public static Map getCiTypeMany(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		GenericDelegator delegator = ctx.getDelegator();
		
        Object idList=context.get("idList");
        List<GenericValue> list;
        try
        {
          if(idList==null)
          {
        	  list=delegator.findAll("SvCiType");
        	  result.put("idList", "");
        	  result.put("ciTypeList", list);
          }
          else
        	{
        	  
        	  List orExprs =new ArrayList();
        	  String[] idArray=idList.toString().split(",");
        	  for(String id:idArray)
        		  orExprs.add(new EntityExpr("ciTypeId",EntityOperator.EQUALS, id));
        	  EntityConditionList entityConditionList=new EntityConditionList(orExprs, EntityOperator.OR);
        	  
        	  
        	  list=delegator.findByAndCache("SvCiType",entityConditionList, UtilMisc.toList("ciTypeId"));
        	  result.put("idList", idList);
        	  result.put("ciTypeList", list);
        	}
          
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}
	
	public static Map getCiTypeCategory(DispatchContext ctx, Map context) {
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
	
	public static Map getCiTypeCategoryMany(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		GenericDelegator delegator = ctx.getDelegator();
		
        Object idList=context.get("idList");
        List<GenericValue> list;
        try
        {
          if(idList==null)
          {
        	  list=delegator.findAll("SvCiTypeCategory");
        	  result.put("idList", "");
        	  result.put("ciTypeCategoryList", list);
          }
          else
        	{
        	  
        	  List orExprs =new ArrayList();
        	  String[] idArray=idList.toString().split(",");
        	  for(String id:idArray)
        		  orExprs.add(new EntityExpr("sv_id",EntityOperator.EQUALS, id));
        	  EntityConditionList entityConditionList=new EntityConditionList(orExprs, EntityOperator.OR);
        	  
        	  
        	  list=delegator.findByAndCache("SvCiTypeCategory",entityConditionList, UtilMisc.toList("sv_id"));
        	  result.put("idList", idList);
        	  result.put("ciTypeCategoryList", list);
        	}
          
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}
	public static Map getCiTypeByCategory(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		return result;
	}
	
	public static Map submitCi(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		GenericDelegator delegator = ctx.getDelegator();
        GenericValue addrMap = delegator.makeValue("SvCi");


		Locale locale = (Locale) context.get("locale");
		String errMsg = null;

        addrMap.put("ci_depend",(String) context.get("ci_depend"));
        addrMap.put("ci_depend_status",(String) context.get("ci_depend_status"));
        addrMap.put("ci_desciption",(String) context.get("ci_desciption"));
        addrMap.put("ci_id",(String) context.get("ci_id"));
        addrMap.put("ci_name",(String) context.get("ci_name"));
        addrMap.put("has_son",(String) context.get("has_son"));
        addrMap.put("parent_group_id",(String) context.get("parent_group_id"));
        addrMap.put("sv_disable",(String) context.get("sv_disable"));
        addrMap.put("sv_network",(String) context.get("sv_network"));
        addrMap.put("sv_status",(String) context.get("sv_status"));
        
		try {
			
			delegator.create("SvCi",addrMap);
			result.putAll(addrMap);

		} catch (Exception e) {

			Debug.logWarning(e, Group.class.toString());
			Map messageMap = UtilMisc.toMap("errMessage", e.getMessage());
			errMsg = UtilProperties.getMessage(resource,
					"ciservices.error_adding_ci",
					messageMap, locale);

			return ServiceUtil.returnError(errMsg);
		}


		return result;
	}
	
	public static Map testCi(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		return result;
	}
}
