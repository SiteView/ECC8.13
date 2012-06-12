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

public class Group 
{
    public static final String resource = "EccUiLabels.xml";
	public static Map deleteSVSE(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		Locale locale = (Locale) context.get("locale");
        GenericDelegator delegator = ctx.getDelegator();
        GenericPK pk= delegator.makePKSingle("SvGroup",context.get("group_id"));
        
        try{
	        GenericValue value=delegator.findByPrimaryKeyCache(pk);
	        value.remove();
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
        String successMessage = UtilProperties.getMessage(resource,"groupservices.sucess_delete_svse",locale);
		result.put("successMessage",successMessage);
		
		return result;
	}

	public static Map getSVSE(DispatchContext ctx, Map context) {
		Map result = new HashMap();
        GenericDelegator delegator = ctx.getDelegator();
        
        /*GenericValue val = (GenericValue)context.get("group_id");
        GenericPK pk = val.getPrimaryKey();*/
        
        GenericPK pk= delegator.makePKSingle("SvGroup",context.get("group_id"));
        
        try{
	        GenericValue value=delegator.findByPrimaryKeyCache(pk);
	        result.put("group_id",value.get("group_id"));
	        result.put("group_name",value.get("group_name"));
	        result.put("disabled",value.get("disabled"));
	        result.put("dependon",value.get("dependon"));
	        result.put("dependon_status",value.get("dependon_status"));
	        result.put("grp_type",value.get("grp_type"));
	        result.put("has_son",value.get("has_son"));
	        result.put("parent_group_id",value.get("parent_group_id"));
	        result.put("status_type_id",value.get("status_type_id"));
	        result.put("sub_entity_sum",value.get("sub_entity_sum"));
	        result.put("sub_monitor_disable_sum",value.get("sub_monitor_disable_sum"));
	        result.put("sub_monitor_error_sum",value.get("sub_monitor_error_sum"));
	        result.put("sub_monitor_null_sum",value.get("sub_monitor_null_sum"));
	        result.put("sub_monitor_ok_sum",value.get("sub_monitor_ok_sum"));
	        result.put("sub_monitor_sum",value.get("sub_monitor_sum"));
	        result.put("sub_monitor_warning_sum",value.get("sub_monitor_warning_sum"));
	        result.put("sub_network_sum",value.get("sub_network_sum"));
	        result.put("sub_point_reduce_sum",value.get("sub_point_reduce_sum"));
	        result.put("sv_description",value.get("sv_description"));
	        result.put("sv_index",value.get("sv_index"));
	        
	        
	        
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}
	public static Map getSVSEMany(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		GenericDelegator delegator = ctx.getDelegator();
		
        Object idList=context.get("idList");
        List<GenericValue> list;
        try
        {
          if(idList==null)
          {
        	  Debug.logError("重点检查======================", Group.class.toString());
        	  list=delegator.findByAndCache("SvGroup",UtilMisc.toMap("parent_group_id", null), UtilMisc.toList("group_id"));
        	  Debug.logError("查到结果个数:"+list.size(), Group.class.toString());
        	  result.put("idList", "");
        	  result.put("svseList", list);
          }
          else
        	{
        	  List defaultExpr=UtilMisc.toList(new EntityExpr("parent_group_id",EntityOperator.EQUALS, null));
        	  
        	  List orExprs =new ArrayList();
        	  String[] idArray=idList.toString().split(",");
        	  for(String id:idArray)
        		  orExprs.add(new EntityExpr("group_id",EntityOperator.EQUALS, id));
        	  EntityConditionList entityConditionList=new EntityConditionList(orExprs, EntityOperator.OR);
        	  
        	  
        	  List andExprs =new ArrayList();
        	  andExprs.add(defaultExpr);
        	  andExprs.add(entityConditionList);
        	  
        	  EntityConditionList queryExpr = new EntityConditionList(andExprs, EntityOperator.AND);
        	  
        	  list=delegator.findByAndCache("SvGroup",queryExpr, UtilMisc.toList("group_id"));
        	  result.put("idList", idList);
        	  result.put("svseList", list);
        	}
          
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}
	
	public static Map submitSVSE(DispatchContext ctx, Map context) 
	{
		Map result = new HashMap();
		GenericDelegator delegator = ctx.getDelegator();
        GenericValue addrMap = delegator.makeValue("SvGroup");

        Locale locale = (Locale) context.get("locale");
		String errMsg = null;
		
		String id=(String) context.get("group_id");
		if(id==null)
		  id=GenericDelegator.getGenericDelegator("default").getNextSeqId("SvGroup");
		
		String group_name=(String) context.get("group_name");
		
		addrMap.put("group_id",id);
        addrMap.put("group_name",group_name);
        addrMap.put("disabled",(String) context.get("disabled"));
        addrMap.put("dependon",(String) context.get("dependon"));
        addrMap.put("dependon_status",(String) context.get("dependon_status"));
        addrMap.put("parent_group_id",null);

		
		try {
			addrMap.create();
			result.put("group_id",id);
			String successMessage = UtilProperties.getMessage(resource,
					"groupservices.sucess_adding_svse",
					 locale);
			result.put("successMessage",successMessage);
			
		} catch (Exception e) {

			Debug.logWarning(e, Group.class.toString());
			Map messageMap = UtilMisc.toMap("errMessage", e.getMessage());
			errMsg = UtilProperties.getMessage(resource,
					"groupservices.error_adding_svse",
					messageMap, locale);

			return ServiceUtil.returnError(errMsg);
		}


		return result;
	}
	public static Map deleteGroup(DispatchContext ctx, Map context) {
		Map result = new HashMap();
        GenericDelegator delegator = ctx.getDelegator();
        
        GenericPK pk= delegator.makePKSingle("SvGroup",context.get("group_id"));
        
        try{
	        GenericValue value=delegator.findByPrimaryKeyCache(pk);
	        value.remove();
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}

	public static Map getGroup(DispatchContext ctx, Map context) {
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
	
	public static Map getGroupMany(DispatchContext ctx, Map context) {
		Map result = new HashMap();
		GenericDelegator delegator = ctx.getDelegator();
		
        Object idList=context.get("idList");
        List<GenericValue> list;
        try
        {
          if(idList==null)
          {
        	  list=delegator.findByAndCache("SvGroup",UtilMisc.toMap("parent_group_id", null), UtilMisc.toList("group_id"));
        	  result.put("idList", "");
        	  result.put("svseList", list);
          }
          else
        	{
        	  List defaultExpr=UtilMisc.toList(new EntityExpr("parent_group_id",EntityOperator.EQUALS, null));
        	  
        	  List orExprs =new ArrayList();
        	  String[] idArray=idList.toString().split(",");
        	  for(String id:idArray)
        		  orExprs.add(new EntityExpr("group_id",EntityOperator.EQUALS, id));
        	  EntityConditionList entityConditionList=new EntityConditionList(orExprs, EntityOperator.OR);
        	  
        	  
        	  List andExprs =new ArrayList();
        	  andExprs.add(defaultExpr);
        	  andExprs.add(entityConditionList);
        	  
        	  EntityConditionList queryExpr = new EntityConditionList(andExprs, EntityOperator.AND);
        	  
        	  list=delegator.findByAndCache("SvGroup",queryExpr, UtilMisc.toList("group_id"));
        	  result.put("idList", idList);
        	  result.put("svseList", list);
        	}
          
        }catch(Exception e)
        {
        	return ServiceUtil.returnError(e.toString());
        }
        
		return result;
	}
	public static Map submitGroup(DispatchContext ctx, Map context) {
		Map result = new HashMap();

		
		GenericDelegator delegator = ctx.getDelegator();
        GenericValue addrMap = delegator.makeValue("SvGroup");

		Locale locale = (Locale) context.get("locale");
		String errMsg = null;
		
		addrMap.put("group_id",delegator.getNextSeqId("SvGroup"));
		
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
	
}
