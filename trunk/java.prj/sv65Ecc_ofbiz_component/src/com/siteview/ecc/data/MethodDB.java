package com.siteview.ecc.data;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityConditionList;
import org.ofbiz.entity.condition.EntityExpr;
import org.ofbiz.entity.condition.EntityOperator;

public class MethodDB {
	
	private static String ERROR = "error";
	private static String GOOD = "good";
	private static String WARNING = "warning";

	public static void addMethodAndCi(MethodBean bean,GenericDelegator delegator) throws Exception{
		GenericValue ci = setCiByMethod(bean, delegator);
		bean.setCiId(ci.getString("ci_id"));
		addMethod(bean,delegator);
	}
	
	public static void addMethod(MethodBean bean,GenericDelegator delegator) throws Exception{
		GenericValue method = setMethods(bean, delegator);
		String methodId = method.getString("method_id");
		setArrributeByMethod(bean, methodId, delegator);
		setConditionByMethod(bean, methodId, delegator);
	}
	
	public static List<Map<String, String>> getAllMethod(GenericDelegator delegator) throws Exception{
		List<Map<String, String>> result = new ArrayList<Map<String, String>>();
		
		List<GenericValue> allMonitor = getMethods(delegator);
		for(GenericValue monitor: allMonitor)
		{
			List<Map<String, String>> vallist = getMethod(monitor,delegator);
			result.addAll(vallist);
		}		
		return result;
	}
	public static List<Map<String, String>> getMethod(String methodId) throws Exception
	{
		return getMethod(methodId, GenericDelegator.getGenericDelegator("default"));
	}
	public static List<Map<String, String>> getMethod(String methodId,GenericDelegator delegator) throws Exception{
		GenericValue monitor = getMethods(methodId,delegator);
		return getMethod(monitor,delegator);
	}
	
	public static List<Map<String, String>> getMethod(GenericValue monitor,GenericDelegator delegator) throws Exception{
		List<Map<String, String>> result = new ArrayList<Map<String, String>>();
		if (monitor==null) return result;
		List<GenericValue> allAttribute = getArrributeByMethod(monitor,delegator);
		List<GenericValue> allCondition = getConditionByMethod(monitor,delegator);
		List<GenericValue> allCiAttr = getCiAttrByMethod(monitor,delegator);
		Map<String, String> map = new HashMap<String, String>();
		map = MethodDB.addMap(map, monitor);
		
		for(GenericValue ci: allCiAttr){
			map.put(ci.getString("attrName"), ci.getString("attrValue"));
		}
		for(GenericValue attribute: allAttribute){
			map.put(attribute.getString("attrName"), attribute.getString("attrValue"));
		}
		for(GenericValue condition: allCondition){
			String status = condition.getString("sv_status");
			if (status==null)continue;
			map.put(status + "_idx",condition.getString("idx"));
			map.put(status + "_sv_relation",condition.getString("sv_relation"));
			map.put(status + "_sv_paramname",condition.getString("sv_paramname"));
			map.put(status + "_sv_operate",condition.getString("sv_operate"));
			map.put(status + "_sv_paramvalue",condition.getString("sv_paramvalue"));
		}
		
		result.add(map);
		return result;
	}		

	/*
	 * 取所有监测器的ID
	 */
	public static List<GenericValue> getMethods(GenericDelegator delegator) throws Exception{
		return delegator.findList("SvCiMethod", null, null, null, null, false);
	}
	
	/*
	 * 
	 */
	private static GenericValue getMethods(String id,GenericDelegator delegator) throws Exception{
		return delegator.findByPrimaryKey("SvCiMethod", UtilMisc.toMap("method_id", id));
	}
	private static GenericValue setMethods(MethodBean bean,GenericDelegator delegator) throws Exception{
		GenericValue val = delegator.makeValue("SvCiMethod");
		String newid = delegator.getNextSeqId("SvCiMethod");
		val.set("method_id", newid);
		val.set("ci_id", bean.getCiId());
		val.set("method_name",bean.getMethodName());
		val.create();
		return val;
	}
	
	private static List<GenericValue> getCiAttrByMethod(GenericValue method,GenericDelegator delegator) throws Exception
	{
		String ciId = method.getString("ci_id");
		if (ciId==null) return new ArrayList<GenericValue>();
    	ArrayList<EntityExpr> exprs = new ArrayList<EntityExpr>();
    	exprs.add(new EntityExpr("ci_id", EntityOperator.EQUALS, ciId));
        EntityCondition condition = new EntityConditionList<EntityExpr>(exprs, EntityOperator.AND);
        return delegator.findList("SvCiAttr", condition, null,null,null,false);
	}
	private static GenericValue setCiByMethod(MethodBean bean,GenericDelegator delegator) throws Exception{
		GenericValue val = delegator.makeValue("SvCi");
		String newid = delegator.getNextSeqId("SvCi");
		val.set("ci_id", newid);
		val.set("ci_name", bean.getName());
		val.create();
		return val;
	}
	
	private static List<GenericValue> getArrributeByMethod(GenericValue method,GenericDelegator delegator) throws Exception
	{
		String methodId = method.getString("method_id");
		if (methodId==null) return new ArrayList<GenericValue>();
    	ArrayList<EntityExpr> exprs = new ArrayList<EntityExpr>();
    	exprs.add(new EntityExpr("method_id", EntityOperator.EQUALS, methodId));
        EntityCondition condition = new EntityConditionList<EntityExpr>(exprs, EntityOperator.AND);
        return delegator.findList("SvCiMethodAttr", condition, null,null,null,false);
	}

	private static List<GenericValue> setArrributeByMethod(MethodBean bean,String methodId, GenericDelegator delegator) throws Exception{
		
		List<GenericValue> list = new ArrayList<GenericValue>();
		
		GenericValue val = delegator.makeValue("SvCiMethodAttr");
		val.set("method_id", methodId);
		val.set("attrName", "_frequency");
		val.set("attrValue", bean.getFrequency());
		val.create();
		list.add(val);
		val = delegator.makeValue("SvCiMethodAttr");
		val.set("method_id", methodId);
		val.set("attrName", "_frequencyUnit");
		val.set("attrValue", bean.getFrequencyUnit());
		val.create();
		list.add(val);
		return list;
	}
	
	private static List<GenericValue> getConditionByMethod(GenericValue method,GenericDelegator delegator) throws Exception
	{
		String methodId = method.getString("method_id");
		if (methodId==null) return new ArrayList<GenericValue>();
    	ArrayList<EntityExpr> exprs = new ArrayList<EntityExpr>();
    	exprs.add(new EntityExpr("method_id", EntityOperator.EQUALS,methodId));
        EntityCondition condition = new EntityConditionList<EntityExpr>(exprs, EntityOperator.AND);
        return delegator.findList("SvCiMethodCondition", condition, null,null,null,false);
	}
	private static List<GenericValue> setConditionByMethod(MethodBean bean,String methodId, GenericDelegator delegator) throws Exception{
		
		List<GenericValue> list = new ArrayList<GenericValue>();
		
		GenericValue val = delegator.makeValue("SvCiMethodCondition");
		val.set("method_id", methodId);
		val.set("idx", "0");
		val.set("sv_status", ERROR);
		val.set("sv_paramname",  bean.getErrorParamName());
		val.set("sv_operate", bean.getErrorOperate());
		val.set("sv_paramvalue", bean.getErrorParamValue());
		val.create();
		list.add(val);

		val = delegator.makeValue("SvCiMethodCondition");
		val.set("method_id", methodId);
		val.set("idx", "1");
		val.set("sv_status", GOOD);
		val.set("sv_paramname",  bean.getGoodParamName());
		val.set("sv_operate", bean.getGoodOperate());
		val.set("sv_paramvalue", bean.getGoodParamValue());
		val.create();
		list.add(val);

		val = delegator.makeValue("SvCiMethodCondition");
		val.set("method_id", methodId);
		val.set("idx", "2");
		val.set("sv_status", WARNING);
		val.set("sv_paramname",  bean.getWarnParamName());
		val.set("sv_operate", bean.getWarnOperate());
		val.set("sv_paramvalue", bean.getWarnParamValue());
		val.create();
		list.add(val);
		return list;
	}
	
	private static Map<String, String> addMap(Map<String, String> map,GenericValue val)
	{
		Map<String, String> retMap = map;
		Iterator<String> keys = val.getAllKeys().iterator();
		while(keys.hasNext()){
			String key = keys.next();
			retMap.put(key, val.getString(key));
		}
		
		return retMap;
	}
}
