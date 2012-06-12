package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.Collection;
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

import com.dragonflow.Api.APIMonitor;
import com.dragonflow.Api.SSInstanceProperty;
import com.dragonflow.Api.SSStringReturnValue;
import com.dragonflow.SiteView.AtomicMonitor;
import com.siteview.ecc.api.GroupEntity;
import com.siteview.ecc.api.MonitorEntity;
import com.siteview.ecc.drive.MonitorDevice;

public class Monitor extends BaseClass{
	public static final String module = Monitor.class.getName();
	
	public static Map<?, ?> addMonitor(DispatchContext ctx, Map<?, ?> context) {
		try {
			String className = (String) getNotOptionalValue(context,"className");
			String groupId = (String) getNotOptionalValue(context,"groupId");
			Object data = getNotOptionalValue(context,"data");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("message", addMonitor(className,groupId,convert(data)));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error addMonitor: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}
	public static String addMonitor(String className,String groupId,Map<String,Object> data)throws Exception {
		List<SSInstanceProperty> assinstanceproperty = new ArrayList<SSInstanceProperty>();
		for (String key : data.keySet()){
			Object value = data.get(key);
			assinstanceproperty.add(new SSInstanceProperty(key,value));
		}
		Map<String, Object> map = Group.getGroupById(groupId);
		assinstanceproperty.add(new SSInstanceProperty("_id",map.get("_nextID")));
		SSStringReturnValue returnValue = new APIMonitor().create(className, groupId, assinstanceproperty.toArray(new SSInstanceProperty[0]));
		return returnValue.getValue();
	}
	
	
	
	public static Map<?, ?> getMonitorType(DispatchContext ctx, Map<?, ?> context) {
		try {
			String keyword = (String) getOptionalValue(context,"keyword");
			Boolean bContains = (Boolean) getOptionalValue(context,"bContains");
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getMonitorType(keyword,bContains,ctx.getDelegator()));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getMonitorType: " + e.toString());
			retresult.put("result", new ArrayList<Map<String, Object>>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}		
	public static List<Map<String, Object>> getMonitorType(String keyword,Boolean bContains)throws Exception {
		return getMonitorType(keyword,bContains,getGenericDelegator());
	}
	public static List<Map<String, Object>> getMonitorType(String keyword,Boolean bContains,GenericDelegator delegator)throws Exception {
		EntityCondition entityCondition = null;
		if (keyword!=null){
			StringBuffer searchWord = new StringBuffer();
			searchWord.append("%");
			searchWord.append(keyword);
			searchWord.append("%");
			if (bContains){
				entityCondition = EntityCondition.makeCondition(UtilMisc.toList(
	                    EntityCondition.makeCondition("className", EntityOperator.LIKE, searchWord.toString()),
	                    EntityCondition.makeCondition("description", EntityOperator.LIKE, searchWord.toString()),
	                    EntityCondition.makeCondition("title", EntityOperator.LIKE, searchWord.toString())), EntityOperator.OR);
			}else{
				entityCondition = EntityCondition.makeCondition(UtilMisc.toList(
	                    EntityCondition.makeCondition("className", EntityOperator.NOT_LIKE, searchWord.toString()),
	                    EntityCondition.makeCondition("description", EntityOperator.NOT_LIKE, searchWord.toString()),
	                    EntityCondition.makeCondition("title", EntityOperator.NOT_LIKE, searchWord.toString())), EntityOperator.AND);
			}
		}
		List<GenericValue> list = delegator.findList("SvMonitorType", entityCondition,null,null,null,false);
        List<Map<String, Object>> retlist = new ArrayList<Map<String, Object>>();
        for (GenericValue val : list)
        {
        	Map<String, Object> map = new HashMap<String, Object>();
        	if (checkData(val.get("className"))) map.put("className", val.get("className"));
        	if (checkData(val.get("description"))) map.put("description", val.get("description"));
        	if (checkData(val.get("title"))) map.put("title", val.get("title"));
//        	if (checkData(val.get("class"))) map.put("class", val.getString("className").replace("com.dragonflow.StandardMonitor.", ""));
        	if (checkData(val.get("target"))) map.put("target", val.get("target"));
        	if (checkData(val.get("toolName"))) map.put("toolName", val.get("toolName"));
        	if (checkData(val.get("toolDescription"))) map.put("toolDescription", val.get("toolDescription"));
        	if (checkData(val.get("topazName"))) map.put("topazName", val.get("topazName"));
        	if (checkData(val.get("topazType"))) map.put("topazType", val.get("topazType"));
        	if (checkData(val.get("classType"))) map.put("classType", val.get("classType"));
        	if (checkData(val.get("applicationType"))) map.put("applicationType", val.get("applicationType"));
        	retlist.add(map);
        }
		return retlist;
	}	
	public static Map<?, ?> getMonitorInstanceByClassName(DispatchContext ctx, Map<?, ?> context) {
		try {
			String className = (String) getNotOptionalValue(context,"className");
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getMonitorInstanceByClassName(className));
			//retresult.put("objectMap", getMonitorInstanceObjectsByClassName(className));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getMonitorTypeByClassName: " + e.toString());
			retresult.put("result", new HashMap<String, Object>());
			//retresult.put("objectMap", new HashMap<String, StringProperty>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}		
	public static Map<String, Object> getMonitorInstanceByClassName(String className)throws Exception {
		if (className == null) return new HashMap<String, Object>();
 		AtomicMonitor atomicMonitor = APIMonitor.instantiateMonitor(className);
		return getProperties(atomicMonitor);
	}

	public static Map<?, ?> delMonitor(DispatchContext ctx, Map<?, ?> context) {
		try {
			String id = (String) getNotOptionalValue(context,"id");
			String groupId = (String) getNotOptionalValue(context,"groupId");
			delMonitor(groupId,id,ctx.getDelegator());
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error delMonitor: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static void delMonitor(String groupId,String id)throws Exception {
		delMonitor(groupId,id,getGenericDelegator());
	}
		
	public static void delMonitor(String groupId,String id,GenericDelegator genericdelegator)throws Exception {
    	MonitorDevice.deleteMonitor(id,groupId, genericdelegator);
		new APIMonitor().delete(id, groupId);
	}	
	public static Map<?, ?> getMonitorById(DispatchContext ctx, Map<?, ?> context) {
		try {
			String groupId = (String) getNotOptionalValue(context,"groupId");
			String id = (String) getNotOptionalValue(context,"id");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getMonitorById(groupId,id));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getMonitorById: " + e.toString());
			retresult.put("result", new HashMap<String, Object>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static Map<String, Object> getMonitorById(String groupId,String id)throws Exception {
		if (id == null )return new HashMap<String, Object>();
		Collection<?> collection = new APIMonitor().getChildMonitors(groupId);
		for (Object object : collection)
		{
			if (object == null) continue;
			if (object instanceof AtomicMonitor)
			{
				AtomicMonitor atomicMonitor = (AtomicMonitor) object;
				if (id.equals(atomicMonitor.getProperty(AtomicMonitor.pID))){
					return getProperties(atomicMonitor);
				}
			}
		}
		return new HashMap<String, Object>();
	}
	public static Map<?, ?> getMonitorByGroupId(DispatchContext ctx, Map<?, ?> context) {
		try {
			String groupId = (String) getNotOptionalValue(context,"groupId");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getMonitorByGroupId(groupId));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getMonitorByGroupId: " + e.toString());
			retresult.put("result", new ArrayList<Map<String, Object>>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static List<Map<String, Object>> getMonitorByGroupId(String groupId)throws Exception {
		Collection<?> collection = new APIMonitor().getChildMonitors(groupId);
		List<Map<String, Object>> retlist = new ArrayList<Map<String, Object>>();
		for (Object object : collection)
		{
			if (object == null) continue;
			AtomicMonitor atomicMonitor = (AtomicMonitor) object;
			try{
				String id = atomicMonitor.getProperty(AtomicMonitor.pID);
				if (MonitorEntity.exist(groupId, GroupEntity.FILENAME_EXT_MG, id))
					retlist.add(getProperties(atomicMonitor));
			}catch(Exception e){}
		}
		return retlist;
	}
	public static Map<?, ?> getMonitorDYNInfoById(DispatchContext ctx, Map<?, ?> context) {
		try {
			String groupId = (String) getNotOptionalValue(context,"groupId");
			String id = (String) getNotOptionalValue(context,"id");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getMonitorDYNInfoById(groupId,id));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getMonitorDYNInfoById: " + e.toString());
			retresult.put("result", new HashMap<String, Object>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	@SuppressWarnings("unchecked")
	public static Map<String, Object> getMonitorDYNInfoById(String groupId,String id)throws Exception {
		jgl.HashMap map = MonitorEntity.getHashMap(groupId, GroupEntity.FILENAME_EXT_DYN, id);
		return (Map<String, Object>) convert(map);
	}	
	public static Map<?, ?> getMonitorDYNInfoByGroupId(DispatchContext ctx, Map<?, ?> context) {
		try {
			String groupId = (String) getNotOptionalValue(context,"groupId");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getMonitorDYNInfoByGroupId(groupId));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getMonitorDYNInfoByGroupId: " + e.toString());
			retresult.put("result", new ArrayList<Map<String, Object>>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static List<Map<String, Object>> getMonitorDYNInfoByGroupId(String groupId)throws Exception {
		
		List<GenericValue> list = MonitorEntity.getMonitorsInstanceByGroupId(groupId, GroupEntity.FILENAME_EXT_DYN);
		List<Map<String, Object>> retlist = new ArrayList<Map<String, Object>>();
		for  (GenericValue val : list){
			if (val == null) continue;
			String id = val.getString("id");
			if (id == null) continue;
			Map<String, Object> map = getMonitorDYNInfoById(groupId,id);
			retlist.add(map);
		}
		return retlist;
	}
	
	public static Map<?, ?> updMonitor(DispatchContext ctx, Map<?, ?> context) {
		try {
			String groupId = (String) getNotOptionalValue(context,"groupId");
			String id = (String) getNotOptionalValue(context,"id");
			Object data = getNotOptionalValue(context,"data");
			updMonitor(groupId,id,convert(data));
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error updMonitor: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static void updMonitor(String groupId,String id,Map<String,Object> data)throws Exception {
		new APIMonitor().update(id, groupId, convert(data));
	}

	
	public static Map<?, ?> getMonitorEditProperties(DispatchContext ctx, Map<?, ?> context) {
		try {
			String className = (String) getOptionalValue(context,"className");
			String groupId = (String) getOptionalValue(context,"groupId");
			String id = (String) getOptionalValue(context,"id");
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			
			Map<String, Object> retmap = new HashMap<String, Object>();
			if (id == null){
				AtomicMonitor atomicMonitor = APIMonitor.instantiateMonitor(className);
				retmap = MonitorEditProperties.getDefaultValue(atomicMonitor);
			} else {
				retmap = Monitor.getMonitorById(groupId, id);
			}
			retmap = BooleanToString(retmap);
			retresult.put("result", retmap);
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getMonitorEditProperties: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}
	
	
	
}
