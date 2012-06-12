package com.siteview.ecc.api;

import java.util.Enumeration;
import java.util.List;

import jgl.Array;
import jgl.HashMap;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityOperator;

import com.dragonflow.Properties.HashMapOrdered;

public class UserEntity extends EntityBase{
	public static Array get()throws Exception
	{
		List<GenericValue> list = getAllUser();
		
		Array retlist = new Array();
		HashMapOrdered hashMapControl = new HashMapOrdered(false);
		hashMapControl.put("_nextID",  getDelegator().getNextSeqId("SvUser"));
		hashMapControl.put("_fileEncoding",  "UTF-8");
		retlist.add(hashMapControl);
		for (GenericValue val : list)
		{
			HashMapOrdered hashMap = new HashMapOrdered(false);
			hashMap.put("_id", val.get("id"));
			if (val.get("disabled") !=null && val.getBoolean("disabled") == true)hashMap.put("_disabled",  "true");
			if (val.getString("group")!=null)hashMap.put("_group",  val.getString("group"));
			if (val.getString("ldapserver")!=null)hashMap.put("_ldapserver",  val.getString("ldapserver"));
			if (val.getString("login")!=null)hashMap.put("_login",  val.getString("login"));
			if (val.getString("password")!=null)hashMap.put("_password",  val.getString("password"));
			if (val.getString("realName")!=null)hashMap.put("_realName",  val.getString("realName"));
			if (val.getString("securityprincipal")!=null)hashMap.put("_securityprincipal",  val.getString("securityprincipal"));
			
			setUserPermission(val.getString("id"),hashMap);
			
			retlist.add(hashMap);
		}
		return retlist;
	}
	public static void put(Array data)throws Exception
	{
		deleteAll();
		Enumeration<?> enumeration = data.elements();
		if (enumeration.hasMoreElements()){
			Object objectFirst = enumeration.nextElement();
			if (objectFirst instanceof HashMap){
				//put("0",(HashMap) objectFirst);
			}
			
			while(enumeration.hasMoreElements())
			{
				Object object = enumeration.nextElement();
				if (object instanceof HashMap){
					put((String)((HashMap)object).get("_id"),(HashMap) object);
				}
			}
		}
	}
	
	private static List<String> cols = getDelegator().getModelEntity("SvUser").getAllFieldNames();
	
	public static void put(String id,HashMap hashmap)throws Exception
	{
		if (id==null)return;
		GenericValue val = getDelegator().makeValue("SvUser");
		val.set("id", id);
		val.set("disabled", "true".equals(hashmap.get("_disabled")) ? Boolean.TRUE : Boolean.FALSE);
		val.set("group", hashmap.get("_group"));
		val.set("ldapserver", hashmap.get("_ldapserver"));
		val.set("login", hashmap.get("_login"));
		val.set("password", hashmap.get("_password"));
		val.set("realName", hashmap.get("_realName"));
		val.set("securityprincipal", hashmap.get("_securityprincipal"));
		val.create();
		
		Enumeration<?> keys = hashmap.keys();
		while(keys.hasMoreElements())
		{
			String key = (String)keys.nextElement();
			if (isExist(key,cols)) continue;
			String value = (String)hashmap.get(key);
			putPermission(id,key,value);
		}

	}
	
	public static boolean isExist(String skey,List<String> keys)
	{
		if (skey == null) return false;
		if (keys == null) return false;
		for (String key : keys){
			if (skey.equals("_" + key)) return true;
		}
		return false;
	}
	
	public static void putPermission(String userId,String key,String value) throws Exception
	{
		if (userId==null)return;
		GenericValue val = getDelegator().makeValue("SvUserPermission");
		val.set("userId", userId);
		val.set("attrName",key);
		val.set("attrValue", "true".equals(value) ? Boolean.TRUE : Boolean.FALSE);
		val.create();
	}
	
	public static List<GenericValue> getPermission(String id)throws Exception
	{
		EntityCondition condition = EntityCondition.makeCondition("userId", EntityOperator.EQUALS, id);
        return getDelegator().findList("SvUserPermission", condition, null,null,null,false);
	}
	
	public static void setUserPermission(String id,HashMap hashMap)throws Exception
	{
		List<GenericValue> list = getPermission(id);
		for (GenericValue val : list)
		{
			String key = (String)val.getString("attrName");
			if (key == null) continue;
			String value = "" + val.getBoolean("attrValue");
			if (!"true".equals(value)) continue;
			hashMap.add(key, value);
		}
	}
	
	public static List<GenericValue> getAllUser()throws Exception
	{
        return getDelegator().findList("SvUser", null, null,null,null,false);
	}
	
	public static void deleteAll()throws Exception
	{
		getDelegator().removeByAnd("SvUserPermission",UtilMisc.toMap("1","1"));
		getDelegator().removeByAnd("SvUser",UtilMisc.toMap("1","1"));
	}
	
}
