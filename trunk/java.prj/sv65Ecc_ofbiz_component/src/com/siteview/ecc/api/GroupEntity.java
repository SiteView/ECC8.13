package com.siteview.ecc.api;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;

import jgl.Array;
import jgl.HashMap;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityOperator;

import com.dragonflow.Properties.HashMapOrdered;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.Utils.TextUtils;


public class GroupEntity extends EntityBase{
	public static final String FILENAME_EXT_MG = "MG";
	public static final String FILENAME_EXT_DYN = "DYN";
	
	

	public static List<GenericValue> getAllGroup()throws Exception
	{
       return getDelegator().findList("SvGroup", null, null,null,null,false);
	}
	public static List<GenericValue> getGroupByType(String stype)throws Exception
	{
       EntityCondition whereCondition = EntityCondition.makeCondition("stype", EntityOperator.EQUALS, stype);
       return getDelegator().findList("SvGroup", whereCondition, null,UtilMisc.toList("idx"),null,false);
	}
	
	public static Array get(String groupId,String stype) throws Exception
	{
        List<GenericValue> groups = getGroupValues(groupId,stype);
        Array retlist = new Array();
        if (groups.size()<=0) return retlist;
        
        HashMapOrdered hashMap = new HashMapOrdered(false);
		for (GenericValue val : groups)
		{
			hashMap.add(val.getString("attrName"), val.getString("attrValue"));
		}
		retlist.add(hashMap);
		
		List<GenericValue> monitors = MonitorEntity.getMonitorsValueByGroupId(groupId,stype);
		List<HashMapOrdered> children = travel(monitors,null);
		for (HashMapOrdered child : children){
			if (child==null)continue;
			retlist.add(child);
		}
		
		List<GenericValue> childreGroups = getChild(groupId,stype);
        
		for (GenericValue val : childreGroups)
		{
			HashMapOrdered childreGroup = new HashMapOrdered(false);
			String group = val.getString("id");
			String groupName = getGroupName(group);
			String[] splits = group.split("\\.");
			String id = "0";
			if (splits.length>1){
				id =  splits[splits.length - 1];
			}
			childreGroup.add("_class", "SubGroup");
			childreGroup.add("_id", id);
			childreGroup.add("_encoding", "GBK");
			childreGroup.add("_group", group);
			childreGroup.add("_name", groupName);
			retlist.add(childreGroup);
		}
		
		return retlist;
	}
	
	public static List<GenericValue> getGroupValues(String groupId,String stype)throws Exception
	{
        EntityCondition whereCondition = EntityCondition.makeCondition(
        		UtilMisc.toList(
        		        EntityCondition.makeCondition("groupId", EntityOperator.EQUALS, groupId),
        		        EntityCondition.makeCondition("stype", EntityOperator.EQUALS, stype)
        		),
        		EntityOperator.AND
        );
        
		
        return getDelegator().findList("SvGroupValue", whereCondition, null,UtilMisc.toList("idx"),null,false);
	}
	
	public static String getGroupName(String groupId)throws Exception
	{
        EntityCondition whereCondition = EntityCondition.makeCondition("groupId", EntityOperator.LIKE, groupId + "%");
		
        List<GenericValue> list = getDelegator().findList("SvGroupValue", whereCondition, null,null,null,false);
        
        for (GenericValue val : list)
        {
        	if ("_name".equals(val.getString("attrName")))
        	{
        		return val.getString("attrValue");
        	}
        	
        }
		return "";
	}
	public static String getId(String groupId)throws Exception
	{
        EntityCondition whereCondition = EntityCondition.makeCondition("groupId", EntityOperator.LIKE, groupId + "%");
		
        List<GenericValue> list = getDelegator().findList("SvGroupValue", whereCondition, null,null,null,false);
        
        for (GenericValue val : list)
        {
        	if ("_name".equals(val.getString("attrName")))
        	{
        		return val.getString("attrValue");
        	}
        	
        }
		return "";
	}	
	public static List<GenericValue> getChild(String groupId,String stype) throws Exception
	{
        EntityCondition whereCondition = 
        	EntityCondition.makeCondition(UtilMisc.toList(
        			EntityCondition.makeCondition("parent", EntityOperator.EQUALS, groupId),
        			EntityCondition.makeCondition("stype", EntityOperator.EQUALS, stype)
        			),
        			EntityOperator.AND);
 		
        return getDelegator().findList("SvGroup", whereCondition, null,UtilMisc.toList("idx"),null,false);
	}
	
	
	private static List<HashMapOrdered> travel(List<GenericValue> monitors,String parentAttr)
	{
		List<HashMapOrdered> retlist = new ArrayList<HashMapOrdered>();
		
		HashMapOrdered hashMap = null;
		String oldId = "";
		for (GenericValue val : monitors)
		{
			String id = val.getString("id");
			
			if (id != null) 
			if (((parentAttr ==null && val.getString("parentAttrName") == null)) ||
					(parentAttr.equals(val.getString("parentAttrName")))){
				
				if (!id.equals(oldId)){
					if (hashMap!=null){
						retlist.add(hashMap);
					}
					hashMap = new HashMapOrdered(false);
				}
				
				if (hasChildrenAttr(monitors,val.getString("attrName"),id)){
					List<HashMapOrdered> children = travel(monitors,val.getString("attrName"));
					for (HashMapOrdered child : children){
						if (child==null)continue;
						hashMap.add(child);
					}
					
				}else{
					hashMap.add(val.getString("attrName"), val.getString("attrValue"));
				}
				
			}
			oldId = val.getString("id");
		}		
		
		if (hashMap!=null)retlist.add(hashMap);
		return retlist;
	}
	
	private static boolean hasChildrenAttr(List<GenericValue> monitors,String parentAttr,String id)
	{
		if (id==null) return false;
		if (parentAttr==null) return true;
		for (GenericValue val : monitors)
		{
			if (!id.equals(val.getString("id"))) continue;
			if (parentAttr.equals(val.getString("parentAttrName"))) return true;
		}		
		return false;
	}
	
	
	public static void saveGroup(String groupId,String stype,HashMap hashMap) throws Exception
	{
		
        EntityCondition whereCondition = EntityCondition.makeCondition(
        		UtilMisc.toList(
        		        EntityCondition.makeCondition("id", EntityOperator.EQUALS, groupId),
        		        EntityCondition.makeCondition("stype", EntityOperator.EQUALS, stype)
        		),
        		EntityOperator.AND
        );

        List<GenericValue> groups = getDelegator().findList("SvGroup", whereCondition, null,UtilMisc.toList("idx"),null,false);
        if (!(groups.size()>0)){
        	GenericValue group = getDelegator().makeValue("SvGroup");
        	group.set("id", groupId);
        	String[] splits = groupId.split("\\.");
        	if (splits.length>1){
        		group.set("parent", splits[0]);
        	}
        	group.set("stype", stype);
        	group.create();
        }
        
        whereCondition = EntityCondition.makeCondition(
        		UtilMisc.toList(
        		        EntityCondition.makeCondition("groupId", EntityOperator.EQUALS, groupId),
        		        EntityCondition.makeCondition("stype", EntityOperator.EQUALS, stype)
        		),
        		EntityOperator.AND
        );
        List<GenericValue> groupValue = getDelegator().findList("SvGroupValue", whereCondition, null,UtilMisc.toList("idx"),null,false);
        long maxIdx = 0;
        try {
        	int index = groupValue.size() - 1;
        	GenericValue val = groupValue.get(index);
        	maxIdx = val.getInteger("idx");
        } catch (Exception e){}
        
        for (GenericValue val : groupValue){
        	String key = val.getString("attrName");
        	if (key == null) continue;
        	boolean bExist = false;
        	Enumeration<?> enumKeys = hashMap.keys();
        	while (enumKeys.hasMoreElements()) {
        		Object obj = enumKeys.nextElement();
    			String keyi = null;
    			if (obj instanceof StringProperty) {
    				keyi = ((StringProperty) obj).getName();
    			} else {
    				keyi = (String) obj;
    			}
        		if (key.equals(keyi))
        		{
        			bExist = true;
        		}
        	}
        	if (!bExist){
        		val.remove();
        	}
        }   
        
        Enumeration<?> enumeration = hashMap.keys();
        while (enumeration.hasMoreElements()) {
        	Object obj = enumeration.nextElement();
			String key = null;
			if (obj instanceof StringProperty) {
				key = ((StringProperty) obj).getName();
			} else {
				key = (String) obj;
			}
            if (key == null) continue;
            
            String value = null;
            if (obj instanceof StringProperty) {
            	value = ((StringProperty) obj).getValue();
			} else if (obj instanceof Array) {
				
			} else if (obj instanceof String) {
				value = "" + hashMap.get(key);
			}
            value = "".equals(value) ? null : value ;
            boolean bExist = false;

            for (GenericValue val : groupValue){
            	if (key.equals(val.getString("attrName")))
            	{
            		if (value == null){
            			val.remove();
            		}else{
                		val.set("attrValue", value);
                		val.store();
            		}
            		bExist = true;
            	}
            }
            if (!bExist && value!=null){
            	GenericValue val = getDelegator().makeValue("SvGroupValue");
            	val.set("groupId", groupId);
            	val.set("stype", stype);
            	maxIdx++;
            	val.set("idx", maxIdx);
            	val.set("attrName", key);
            	val.set("attrValue", value);
            	val.create();
            }
        }                
	}

	
	public static void saveDYN(String groupId,Array data,String s,
			boolean flag, boolean flag1) throws Exception
	{
		Enumeration<?> enumeration = data.elements();
		
		while(enumeration.hasMoreElements())
		{
			HashMap hashMap = (HashMap) enumeration.nextElement();
			
			String id = (String) hashMap.get("id");
			if (id == null) continue; 
			if (id.equals("-1")) {
				saveGroup(groupId,FILENAME_EXT_DYN,hashMap);
			} else {
				MonitorEntity.save(groupId,FILENAME_EXT_DYN,(String)id, hashMap);
			}
		}
	}
	public static void saveMG(String groupId,Array data,String s,
			boolean flag, boolean flag1) throws Exception
	{
		
		Enumeration<?> enumeration = data.elements();
		while(enumeration.hasMoreElements())
		{
			HashMap hashMap = (HashMap) enumeration.nextElement();
			
			//Object nextID =  hashMap.get("_nextID");
			//if (nextID == null) continue;
			saveGroup(groupId,FILENAME_EXT_MG,hashMap);
			break;
		}
		
		//enumeration = data.elements();
		List<String> subgroups = new ArrayList<String>();
		while(enumeration.hasMoreElements())
		{
			HashMap hashMap = (HashMap) enumeration.nextElement();
			
			String _class = (String) hashMap.get("_class");
			if (_class == null) continue;
			if ("SubGroup".equals(_class)) {
				subgroups.add(TextUtils.getValue(hashMap, "_group"));
				continue;
			}
			Object id = getId(hashMap);
			if (id == null) continue;
			MonitorEntity.save(groupId,FILENAME_EXT_MG,(String)id, hashMap);
		}
		updateSubGroup(groupId,subgroups,FILENAME_EXT_MG);
	}
	
	public static void updateSubGroup(String groupId,List<String> groups,String stype )throws Exception
	{
		List<EntityCondition> groupConditions = new ArrayList<EntityCondition>();
		
		for (String groupid : groups)
		{
			if (groupid == null) continue;
			groupConditions.add(EntityCondition.makeCondition("id", EntityOperator.NOT_EQUAL, groupid));
		}
		groupConditions.add(EntityCondition.makeCondition("stype", EntityOperator.EQUALS, stype));
		groupConditions.add(EntityCondition.makeCondition("id", EntityOperator.LIKE, groupId + "%"));
		groupConditions.add(EntityCondition.makeCondition("id", EntityOperator.NOT_EQUAL, groupId));
		
        EntityCondition whereCondition = 
        	EntityCondition.makeCondition(groupConditions,EntityOperator.AND);
        List<GenericValue> groupValue = getDelegator().findList("SvGroup", whereCondition, null,null,null,false);
        for (GenericValue val : groupValue){
        	String groupid = val.getString("id");
        	delete(groupid,stype);
        }
		
	}
	public static void delete(String groupId,String stype) throws Exception
	{
		if (groupId==null)return;
		MonitorEntity.deleteByGroupId(groupId,stype);
		getDelegator().removeByAnd("SvGroupValue",UtilMisc.toMap("groupId",groupId,"stype",stype));
		getDelegator().removeByAnd("SvGroup",UtilMisc.toMap("id",groupId,"stype",stype));
	}
	
	private static String getId(HashMap hashmap)
	{
		Object id = hashmap.get("_id");
		if (id!=null) return (String) id;
        Enumeration<?> enumeration = hashmap.keys();
        while (enumeration.hasMoreElements()) {
        	Object obj = enumeration.nextElement();
			if (obj instanceof StringProperty) {
				String key = ((StringProperty) obj).getName();
	            if (key.equals("_id"))
	            {
	                Enumeration<?> enumeration1 = hashmap.values(obj);
	                while (enumeration1.hasMoreElements()) {
	    				Object obj1 = enumeration1.nextElement();
	    				return (String) obj1;
	                }
	            }
			}
        }
        return null;
	}
}
