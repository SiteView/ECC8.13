package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.Date;
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

import com.dragonflow.Log.EntityLogger;

public class Log extends BaseClass{
	public static final String module = Log.class.getName();
	
	
	public static Map<?, ?> addLog(DispatchContext ctx, Map<?, ?> context) {
		try {
			Object data = getNotOptionalValue(context,"data");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("message", addLog(convert(data),ctx.getDelegator()));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error addLog: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}
	public static String addLog(Map<String,Object> data)throws Exception {
		return addLog(data,getGenericDelegator());
	}
	public static String addLog(Map<String,Object> data,GenericDelegator delegator)throws Exception {
		GenericValue newValue = delegator.makeValue("SvLog");
		newValue.set("id", delegator.getNextSeqId("SvLog"));
		String datex = convert(new Date());
		newValue.set("datex",datex );
		newValue.set("serverName", EntityLogger.getServerName());
		newValue.set("className", data.get("className"));
		newValue.set("sample", data.get("sample"));
		newValue.set("category", data.get("category"));
		newValue.set("groupName", data.get("groupName"));
		newValue.set("monitorName", data.get("monitorName"));
		newValue.set("status", data.get("status"));
		newValue.set("monitorId", data.get("monitorId"));
		newValue.set("value1", data.get("value1"));
		newValue.set("value2", data.get("value2"));
		newValue.set("value3", data.get("value3"));
		newValue.set("value4", data.get("value4"));
		newValue.set("value5", data.get("value5"));
		newValue.set("value6", data.get("value6"));
		newValue.set("value7", data.get("value7"));
		newValue.set("value8", data.get("value8"));
		newValue.set("value9", data.get("value9"));
		newValue.set("value10", data.get("value10"));
		newValue.create();
		return datex;
	}
	
	public static Map<?, ?> delLog(DispatchContext ctx, Map<?, ?> context) {
		try {
			Date datex = (Date) getNotOptionalValue(context,"datex");
			String serverName = (String) getNotOptionalValue(context,"serverName");
			delLog(datex,serverName,ctx.getDelegator());
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error delLog: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static void delLog(String datex,String serverName,GenericDelegator delegator)throws Exception {
        EntityCondition whereCondition = EntityCondition.makeCondition(
        		UtilMisc.toList(
        		        EntityCondition.makeCondition("datex", EntityOperator.EQUALS, datex),
        		        EntityCondition.makeCondition("serverName", EntityOperator.EQUALS, serverName)
        		),
        		EntityOperator.AND
        );
        
        delegator.removeByCondition("SvLog", whereCondition);
	}	
	public static void delLog(Date datex,String serverName,GenericDelegator delegator)throws Exception {
		delLog(convert(datex),serverName,delegator);
	}	
	public static void delLog(Date datex,String serverName)throws Exception {
		delLog(datex,serverName,getGenericDelegator());
	}	
	public static void delLog(String datex,String serverName)throws Exception {
		delLog(datex,serverName,getGenericDelegator());
	}	
	public static Map<?, ?> getLog(DispatchContext ctx, Map<?, ?> context) {
		try {
			Date datex = (Date) getNotOptionalValue(context,"datex");
			String serverName = (String) getNotOptionalValue(context,"serverName");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getLog(datex,serverName,ctx.getDelegator()));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getLog: " + e.toString());
			retresult.put("result", new HashMap<String, Object>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static Map<String, Object> getLog(String datex,String serverName,GenericDelegator delegator)throws Exception {
        EntityCondition whereCondition = EntityCondition.makeCondition(
        		UtilMisc.toList(
        		        EntityCondition.makeCondition("datex", EntityOperator.EQUALS, datex),
        		        EntityCondition.makeCondition("serverName", EntityOperator.EQUALS, serverName)
        		),
        		EntityOperator.AND
        );
        
        List<GenericValue> list = delegator.findList("SvLog", whereCondition,null,null,null,false);
        Map<String, Object> map = new HashMap<String, Object>();
        for (GenericValue val : list){
    		map.put("datex", val.get("datex"));
    		map.put("serverName", val.get("serverName"));
    		map.put("className", val.get("className"));
    		map.put("sample", val.get("sample"));
    		map.put("category", val.get("category"));
    		map.put("groupName", val.get("groupName"));
    		map.put("monitorName", val.get("monitorName"));
    		map.put("status", val.get("status"));
    		map.put("monitorId", val.get("monitorId"));
    		map.put("value1", val.get("value1"));
    		map.put("value2", val.get("value2"));
    		map.put("value3", val.get("value3"));
    		map.put("value4", val.get("value4"));
    		map.put("value5", val.get("value5"));
    		map.put("value6", val.get("value6"));
    		map.put("value7", val.get("value7"));
    		map.put("value8", val.get("value8"));
    		map.put("value9", val.get("value9"));
    		map.put("value10", val.get("value10"));
    		return map;
        }
		return map;
        
	}	
	public static Map<String, Object> getLog(Date datex,String serverName)throws Exception {
		return getLog(convert(datex),serverName,getGenericDelegator());
	}	
	public static Map<String, Object> getLog(String datex,String serverName)throws Exception {
		return getLog(datex,serverName,getGenericDelegator());
	}	
	public static Map<String, Object> getLog(Date datex,String serverName,GenericDelegator delegator)throws Exception {
		return getLog(convert(datex),serverName,delegator);
	}	
	public static Map<?, ?> getLogByDate(DispatchContext ctx, Map<?, ?> context) {
		try {
			Date begin = (Date) getOptionalValue(context,"begin");
			Date end = (Date) getOptionalValue(context,"end");
			String serverName = (String) getOptionalValue(context,"serverName");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getLogByDate(begin,end,serverName,ctx.getDelegator()));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getLogByDate: " + e.toString());
			retresult.put("result", new ArrayList<Map<String, Object>>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static List<Map<String, Object>> getLogByDate(String begin,String end,String serverName,GenericDelegator delegator)throws Exception {
        EntityCondition whereCondition = EntityCondition.makeCondition(
        		UtilMisc.toList(
        		        EntityCondition.makeCondition("datex", EntityOperator.BETWEEN, UtilMisc.toList(begin,end)),
        		        EntityCondition.makeCondition("serverName", EntityOperator.EQUALS, serverName)
        		),
        		EntityOperator.AND
        );
        
        List<GenericValue> list = delegator.findList("SvLog", whereCondition,null,null,null,false);
        List<Map<String, Object>> retlist = new ArrayList<Map<String, Object>>();
        for (GenericValue val : list){
        	Map<String, Object> map = new HashMap<String, Object>();
    		map.put("datex", val.get("datex"));
    		map.put("serverName", val.get("serverName"));
    		map.put("className", val.get("className"));
    		map.put("sample", val.get("sample"));
    		map.put("category", val.get("category"));
    		map.put("groupName", val.get("groupName"));
    		map.put("monitorName", val.get("monitorName"));
    		map.put("status", val.get("status"));
    		map.put("monitorId", val.get("monitorId"));
    		map.put("value1", val.get("value1"));
    		map.put("value2", val.get("value2"));
    		map.put("value3", val.get("value3"));
    		map.put("value4", val.get("value4"));
    		map.put("value5", val.get("value5"));
    		map.put("value6", val.get("value6"));
    		map.put("value7", val.get("value7"));
    		map.put("value8", val.get("value8"));
    		map.put("value9", val.get("value9"));
    		map.put("value10", val.get("value10"));
    		retlist.add(map);
        }
		return retlist;
		
	}	
	public static List<Map<String, Object>> getLogByDate(Date begin,Date end,String serverName,GenericDelegator delegator)throws Exception {
		return getLogByDate(convert(begin),convert(end),serverName,delegator);
	}	
	public static List<Map<String, Object>> getLogByDate(Date begin,Date end,String serverName)throws Exception {
		return getLogByDate(convert(begin),convert(end),serverName,getGenericDelegator());
	}	
	public static List<Map<String, Object>> getLogByDate(String begin,String end,String serverName)throws Exception {
		return getLogByDate(begin,end,serverName,getGenericDelegator());
	}	
	
}
