package com.siteview.ecc.api;

import java.util.Enumeration;
import java.util.List;
import java.util.Map;

import jgl.Array;
import jgl.HashMap;
import jgl.Sorting;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityOperator;

import com.dragonflow.Properties.HashMapOrdered;
import com.dragonflow.Properties.LessEqualPropertyName;
import com.dragonflow.Properties.StringProperty;

public class MonitorEntity extends EntityBase{
	private static boolean allowNestedFrames = false;
	
	public static void save(String groupId,String stype,String id, HashMap hashmap) throws Exception {
		save(groupId,stype,id, hashmap, false);
	}

	public static void save(String groupId,String stype,String id, HashMap hashmap, boolean flag)
			throws Exception {
		save(groupId,stype,id, hashmap, null, false, flag,null);
	}

	public static void save(String groupId,String stype,String id,HashMap hashmap,String s,
			boolean flag, boolean flag1,String parentAttrName) throws Exception
	{
       	delete(groupId,stype,id);
        create(groupId,stype,id, hashmap, null, false, flag,null);
	}
	
	private static String getABSClassName(HashMap hashmap)
	{
		String className = (String) hashmap.get("_class");
		if (className==null)return null;
		return "com.dragonflow.StandardMonitor." + className;
	}
	
	private static void create(String groupId,String stype,String id,HashMap hashmap,String s,
			boolean flag, boolean flag1,String parentAttrName) throws Exception
	{
		
		GenericValue group = getDelegator().makeValue("SvMonitorInstance");
    	group.set("groupId", groupId);
    	group.set("stype", stype);
    	group.set("id", id);
    	
     	group.set("className", getABSClassName(hashmap));
    	group.create();
		
        long maxIdx = 0;

		boolean flag2 = s != null;
		if (hashmap.get("noSlotFilter") != null) {
			flag2 = false;
		}
 		
        Enumeration<?> enumeration = hashmap.keys();

		if (flag1) {
			Array array = new Array();
			for (; enumeration.hasMoreElements(); array.add(enumeration
					.nextElement())) {
			}
			Sorting.sort(array, new LessEqualPropertyName());
			enumeration = array.elements();
		}
        
        while (enumeration.hasMoreElements()) {
        	Object obj = enumeration.nextElement();
			String key = null;
			if (obj instanceof StringProperty) {
				key = ((StringProperty) obj).getName();
			} if (obj instanceof String) {
				key = (String) obj;
			}
            if (key == null) continue;
            
            Enumeration<?> enumeration1 = hashmap.values(obj);
            while (enumeration1.hasMoreElements()) {
				Object obj1 = enumeration1.nextElement();
				boolean flag3 = true;
				if (flag2) {
					flag3 = s.startsWith(s);
					if (!flag) {
						flag3 = !flag3;
					}
				}
				if (flag3) {
					if (allowNestedFrames && (obj1 instanceof HashMap)) {
						create(groupId,stype,id,(HashMap) obj1,s,
								flag, flag1,key);
					} else if (obj1 instanceof Array) {
						Enumeration<?> enumeration2 = ((Array) obj1).elements();
						while (enumeration2.hasMoreElements()) {
			            	GenericValue val = getDelegator().makeValue("SvMonitorInstanceValue");
			            	val.set("groupId", groupId);
			            	val.set("stype", stype);
			            	val.set("id", id);
			            	maxIdx++;
			            	val.set("idx", maxIdx);
			            	val.set("attrName", key);
			            	val.set("parentAttrName", parentAttrName);
			            	val.set("attrValue", enumeration2.nextElement());
			            	val.create();
						}
					} else {
						if (("" + obj1).length() != 0 || flag1) {
			            	GenericValue val = getDelegator().makeValue("SvMonitorInstanceValue");
			            	val.set("groupId", groupId);
			            	val.set("stype", stype);
			            	val.set("id", id);
			            	maxIdx++;
			            	val.set("idx", maxIdx);
			            	val.set("attrName", key);
			            	val.set("parentAttrName", parentAttrName);
			            	val.set("attrValue", obj1);
			            	val.create();
						}
					}
				}
            }
        }        
	}

	public static HashMapOrdered getHashMap(String groupId,String stype,String id) throws Exception
	{
		EntityCondition condition = EntityCondition.makeCondition(
				UtilMisc.toList(
						EntityCondition.makeCondition("groupId", EntityOperator.EQUALS, groupId),
						EntityCondition.makeCondition("stype", EntityOperator.EQUALS, stype),
						EntityCondition.makeCondition("id", EntityOperator.EQUALS, id)
				),EntityOperator.AND
				);
        List<GenericValue> values = getDelegator().findList("SvMonitorInstanceValue", condition, null,UtilMisc.toList("idx"),null,false);
        HashMapOrdered hashMap = new HashMapOrdered(true);
        if (values.size()<=0) return hashMap;
        
		for (GenericValue val : values)
		{
			hashMap.add(val.getString("attrName"), val.getString("attrValue"));
		}
		return hashMap;
	}	
	
	public static boolean exist(String groupId,String stype,String id) throws Exception
	{
		if (groupId == null) return false;
		if (id == null) return false;
		if (stype == null) return false;
		EntityCondition condition = EntityCondition.makeCondition(
				UtilMisc.toList(
						EntityCondition.makeCondition("groupId", EntityOperator.EQUALS, groupId),
						EntityCondition.makeCondition("stype", EntityOperator.EQUALS, stype),
						EntityCondition.makeCondition("id", EntityOperator.EQUALS, id)
				),EntityOperator.AND
				);
				
        List<GenericValue> values = getDelegator().findList("SvMonitorInstance",condition,null, UtilMisc.toList("idx"),null,false);
		if (values.size()>0) return true;
		return false;
	}
	public static List<GenericValue> getMonitorsValueByGroupId(String groupId,String stype) throws Exception
	{
        EntityCondition whereCondition = EntityCondition.makeCondition(
        		UtilMisc.toList(
        		        EntityCondition.makeCondition("groupId", EntityOperator.EQUALS, groupId),
        		        EntityCondition.makeCondition("stype", EntityOperator.EQUALS, stype)
        		),
        		EntityOperator.AND
        );
        return getDelegator().findList("SvMonitorInstanceValue", whereCondition, null,UtilMisc.toList("id","idx"),null,false);
	}
	
	public static List<GenericValue> getMonitorsInstanceByGroupId(String groupId,String stype) throws Exception
	{
        EntityCondition whereCondition = EntityCondition.makeCondition(
        		UtilMisc.toList(
        		        EntityCondition.makeCondition("groupId", EntityOperator.EQUALS, groupId),
        		        EntityCondition.makeCondition("stype", EntityOperator.EQUALS, stype)
        		),
        		EntityOperator.AND
        );
        return getDelegator().findList("SvMonitorInstance", whereCondition, null,null,null,false);
	}
	

	public static void delete(String groupid,String stype,String id) throws Exception
	{
		if (groupid == null) return;
		if (stype == null) return;
		if (id == null) return;
		Map<String,String> condition = UtilMisc.toMap("groupId", groupid,"stype", stype,"id", id);
		getDelegator().removeByAnd("SvMonitorInstanceValue",condition);
		getDelegator().removeByAnd("SvMonitorInstance",condition);
	}	
	public static void deleteByGroupId(String groupId,String stype) throws Exception
	{
		List<GenericValue> monitors = getMonitorsInstanceByGroupId(groupId, stype);
		for (GenericValue monitor : monitors){
			if (monitor==null)continue;
			String id = monitor.getString("id");
			delete(groupId,stype,id);
		}
	}	
	
}
