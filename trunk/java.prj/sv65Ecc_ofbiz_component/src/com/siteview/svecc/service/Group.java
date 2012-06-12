package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import org.ofbiz.base.util.Debug;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

import com.dragonflow.Api.APIGroup;
import com.dragonflow.Api.SSStringReturnValue;
import com.dragonflow.Properties.PropertiedObject;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.MonitorGroup;
import com.dragonflow.SiteView.SiteViewGroup;
import com.siteview.ecc.api.APIEntity;

public class Group extends BaseClass{
	public static final String module = Group.class.getName();
	
	
	public static Map<?, ?> addGroup(DispatchContext ctx, Map<?, ?> context) {
		try {
			String name = (String) getNotOptionalValue(context,"name");
			String parentId = (String) getOptionalValue(context,"parentId");
			Object data = getNotOptionalValue(context,"data");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("message", addGroup(name,parentId,convert(data)));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error addGroup: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}
	public static String addGroup(String name,String parentId,Map<String,Object> data)throws Exception {
		SSStringReturnValue returnValue = new APIGroup().create(name, parentId, convert(data));
		return returnValue.getValue();
	}
	
	
	public static Map<?, ?> delGroup(DispatchContext ctx, Map<?, ?> context) {
		try {
			String id = (String) getNotOptionalValue(context,"id");
			delGroup(id);
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error delGroup: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static void delGroup(String id)throws Exception {
		new APIGroup().delete(id);
		
	}
	public static Map<?, ?> getGroupById(DispatchContext ctx, Map<?, ?> context) {
		try {
			String id = (String) getNotOptionalValue(context,"id");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getGroupById(id));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getGroupById: " + e.toString());
			retresult.put("result", new HashMap<String, Object>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static Map<String, Object> getGroupById(String id)throws Exception {
		List<Map<String, Object>> allGroups = getAllGroup();
		for (Map<String, Object> map : allGroups)
		{
			Object groupid = map.get("_id");
			if (groupid == null) continue;
			if (groupid.equals(id)) return map;
		}
		return new HashMap<String, Object>();
		
		/*
        List<GenericValue> values = GroupEntity.getGroupValues(id,GroupEntity.FILENAME_EXT_MG);
        Map<String, Object> map = new HashMap<String, Object>();
        map.put("groupId", id);
        if (values.size()<=0) return map;
		for (GenericValue val : values)
		{
			map.put(val.getString("attrName"), val.getString("attrValue"));
		}
		return map;
		*/
	}
	
	public static Map<?, ?> getGroupByParentId(DispatchContext ctx, Map<?, ?> context) {
		try {
			String parentId = (String) getOptionalValue(context,"parentId");
			
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getGroupByParentId(parentId));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getGroupByParentId: " + e.toString());
			retresult.put("result", new ArrayList<Map<String, Object>>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static List<Map<String, Object>> getGroupByParentId(String parentId)throws Exception {
		String viewid = parentId;
		Collection collection = null;
		if (viewid == null){
			SiteViewGroup siteViewGroup = SiteViewGroup.currentSiteView();
			collection = siteViewGroup.getTopLevelGroups();
			//viewid = siteViewGroup.getProperty(SiteViewGroup.pID);
		}else{
			collection = new APIGroup().getChildGroupInstances(viewid);
		}
		Vector retVector = new Vector();
		for (Object obj : collection){
			if (obj instanceof MonitorGroup ){
				MonitorGroup monitorgroup = (MonitorGroup)obj;
				boolean flag = monitorgroup.isHealthGroup();
				if (parentId == null){
					if (  monitorgroup.isTopLevelGroup() && !flag && monitorgroup.getFile().exists() && APIEntity.exist(monitorgroup.getFile().getName())){
						retVector.add(obj);
					}
				} else {
					if (  monitorgroup.getFile().exists() && APIEntity.exist(monitorgroup.getFile().getName())){
						retVector.add(obj);
					}
				}
			}
		}
		return convert((Collection)retVector);
/*		SiteViewGroup siteViewGroup = SiteViewGroup.currentSiteView();
		String viewid = siteViewGroup.getProperty(SiteViewGroup.pID);
		return convert(new APIGroup().getChildGroupInstances(viewid));
*/		/*
        List<GenericValue> values = GroupEntity.getChild(parentId,GroupEntity.FILENAME_EXT_MG);
        
        List<Map<String, Object>> retlist = new ArrayList<Map<String, Object>>();
        if (values.size()<=0) return retlist;
		for (GenericValue val : values)
		{
			String id = val.getString("id");
			retlist.add(getGroupById(id));
		}
		return retlist;
		*/
	}
	public static Map<?, ?> getAllGroup(DispatchContext ctx, Map<?, ?> context) {
		try {
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getAllGroup());
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getAllGroup: " + e.toString());
			retresult.put("result", new ArrayList<Map<String, Object>>());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static List<Map<String, Object>> getAllGroup()throws Exception {
		Collection<PropertiedObject> list = new APIGroup().getAllGroupInstances();
		return convert(list);
		/*
        List<GenericValue> values = GroupEntity.getGroupByType(GroupEntity.FILENAME_EXT_MG);
        
        List<Map<String, Object>> retlist = new ArrayList<Map<String, Object>>();
        if (values.size()<=0) return retlist;
		for (GenericValue val : values)
		{
			String id = val.getString("id");
			retlist.add(getGroupById(id));
		}
		return retlist;*/
	}
	
	public static Map<?, ?> updGroup(DispatchContext ctx, Map<?, ?> context) {
		try {
			String id = (String) getNotOptionalValue(context,"id");
			Object data = getNotOptionalValue(context,"data");
			updGroup(id,convert(data));
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error updGroup: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	public static void updGroup(String id,Map<String,Object> data)throws Exception {
		new APIGroup().update(id, convert(data));
	}
	public static Map<?,?> getGroupAttri(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			result = ServiceUtil.returnSuccess();
			result.put("data", getGroupAttri());
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error getGroupAttri: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static Map<String,StringProperty> getGroupAttri() throws Exception{
		return getStringProperties(new com.dragonflow.SiteView.Group());
	}
}
