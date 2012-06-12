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

public class Alert {
	public static final String resource = "EccUiLabels.xml";
	public static Map deleteAlert(DispatchContext ctx, Map context) {
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

	public static Map getAlert(DispatchContext ctx, Map context) {
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
	
	public static Map getAlertMany(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		GenericDelegator delegator = ctx.getDelegator();
		
        Object idList=context.get("idList");
        List<GenericValue> list;
        try
        {
          if(idList==null)
          {
        	  list=delegator.findAll("SvAlert");
        	  result.put("idList", "");
        	  result.put("alertList", list);
          }
          else
        	{
        	  
        	  List orExprs =new ArrayList();
        	  String[] idArray=idList.toString().split(",");
        	  for(String id:idArray)
        		  orExprs.add(new EntityExpr("alertId",EntityOperator.EQUALS, id));
        	  EntityConditionList entityConditionList=new EntityConditionList(orExprs, EntityOperator.OR);
        	  
        	  
        	  list=delegator.findByAndCache("SvAlert",entityConditionList, UtilMisc.toList("alertId"));
        	  result.put("idList", idList);
        	  result.put("alertList", list);
        	}
          
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}

	public static Map submitAlert(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		GenericDelegator delegator = ctx.getDelegator();
        GenericValue addrMap = delegator.makeValue("SvAlert");


		Locale locale = (Locale) context.get("locale");
		String errMsg = null;

        addrMap.put("alertName",(String) context.get("alertName"));
        addrMap.put("alertState",(String) context.get("alertState"));
        addrMap.put("alertType",(String) context.get("alertType"));
        addrMap.put("alwaysTimes",(String) context.get("alwaysTimes"));
        addrMap.put("attr",(String) context.get("attr"));
        addrMap.put("onlyTimes",(String) context.get("onlyTimes"));
        addrMap.put("selTimes1",(String) context.get("selTimes1"));
        addrMap.put("selTimes2",(String) context.get("selTimes2"));
        
		
		try {
			
			delegator.create("SvAlert",addrMap);
			result.putAll(addrMap);

		} catch (Exception e) {

			Debug.logWarning(e, Group.class.toString());
			Map messageMap = UtilMisc.toMap("errMessage", e.getMessage());
			errMsg = UtilProperties.getMessage(resource,
					"groupservices.error_adding_alert",
					messageMap, locale);

			return ServiceUtil.returnError(errMsg);
		}


		return result;
	}
	
	public static Map getAlertType(DispatchContext ctx, Map context) {
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
	public static Map getAlertTypeMany(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		GenericDelegator delegator = ctx.getDelegator();
		
        Object idList=context.get("idList");
        List<GenericValue> list;
        try
        {
          if(idList==null)
          {
        	  list=delegator.findAll("SvAlertType");
        	  result.put("idList", "");
        	  result.put("alertTypeList", list);
          }
          else
        	{
        	  
        	  List orExprs =new ArrayList();
        	  String[] idArray=idList.toString().split(",");
        	  for(String id:idArray)
        		  orExprs.add(new EntityExpr("alertType",EntityOperator.EQUALS, id));
        	  EntityConditionList entityConditionList=new EntityConditionList(orExprs, EntityOperator.OR);
        	  
        	  
        	  list=delegator.findByAndCache("SvAlertType",entityConditionList, UtilMisc.toList("alertType"));
        	  result.put("idList", idList);
        	  result.put("alertTypeList", list);
        	}
          
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}
	public static Map smsTest(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		return result;
	}
	
	public static Map emailTest(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		return result;
	}
	public static Map queryAlertLog(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		return result;
	}
	
	
	
}
