package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

import com.dragonflow.Utils.TextUtils;

public class SiteSeer extends BaseClass {
	private static final String module = SiteSeer.class.getName();
	
	private static final Map<String,Object> ATTRI_NAME_MAP = UtilMisc.toMap(
		"_siteseerAccount",null,
		"_siteseerUsername",null,
		"_siteseerPassword",null,
		"_siteseerHost","siteseer5.dragonflow.com",
		"_siteseerDisabled",null,
		"_siteseerTitle","Siteseer",
		"_siteseerProxy",null,
		"_siteseerProxyUsername",null,
		"_siteseerProxyPassword",null,
		"_siteseerHidden",null,
		"_siteseerLoginInURL",null,
		"_siteseerReadOnlyUsername",null,
		"_siteseerReadOnlyPassword",null
	);
	
	public static Map<?,?> getSiteSeerAttr(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			result = ServiceUtil.returnSuccess();
			result.put("data", getSiteSeerAttr());
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error getSiteSeer: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static List<String> getSiteSeerAttr(){
		List<String> retList = new ArrayList<String>();
		retList.addAll(ATTRI_NAME_MAP.keySet());
		return retList;
	}
	
	public static Map<?,?> getSiteSeer(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			result = ServiceUtil.returnSuccess();
			result.put("data", getSiteSeer());
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error getSiteSeer: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static Map<?,?> getSiteSeer() throws Exception{
		Map<Object,Object> retmap = new HashMap<Object,Object>();
		for (Object attrName : ATTRI_NAME_MAP.keySet()){
			retmap.put(attrName, getSiteSeer(attrName));
		}
		return retmap;
	}
	public static Object getSiteSeer(Object key) throws Exception{
		if (!isInAttriNameMap(key))return null;
		Object value = getValue(key);
		if (value == null || "".equals(value)){
			return getDefault(key);
		}
		return value;
	}
	
	private static Object getValue(Object key) throws Exception
	{
		if (key == null) return null;
		if (!(key instanceof String)) return null;
		Map<String,Object> map = Config.getConfigByName((String)key);
		for (String mapkey : map.keySet())
		{
			if (("" + key).endsWith("Password")){
				return TextUtils.enlighten((String) map.get(mapkey));
			}
			return map.get(mapkey);
		}
		return "";
	}

	public static Map<?,?> putSiteSeer(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			Map<?,?> value = (Map<?, ?>) getNotOptionalValue(context,"data");
			putSiteSeer(value);
			result = ServiceUtil.returnSuccess();
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error putSiteSeer: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static void putSiteSeer(Map<?,?> data) throws Exception{
		for (Object key : getSiteSeerAttr()){
			Object value = data.get(key);
			putSiteSeer(key,value);
		}
	}
	public static void putSiteSeer(Object key , Object value)
	{
		if (!isInAttriNameMap(key))return;
		putValue(key,value);
		
	}
	private static void putValue(Object key , Object value){
		if (key == null) return;
		if (!(key instanceof String)) return;
		if (("" + key).endsWith("Password")){
			if (NO_CHANGED_PASSWORD.equals(value)) return ;
			Config.configPut((String)key, TextUtils.obscure((String)value));
			return;
		}
		Config.configPut((String)key, (String)value);
	}
	private static boolean isInAttriNameMap(Object name)
	{
		if (name == null) return false;
		if ("".equals(name)) return false;
		return ATTRI_NAME_MAP.containsKey(name);
	}
	public static String getDefault(Object name)
	{
		return (String) ATTRI_NAME_MAP.get(name);
	}
}
