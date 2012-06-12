package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

import com.dragonflow.Api.APIPreference;
import com.dragonflow.Api.SSInstanceProperty;
import com.dragonflow.StandardPreference.GeneralDefaultPreferences;
import com.dragonflow.Utils.TextUtils;

public class General extends BaseClass {
	private static final String module = General.class.getName();
	private static final String CLASS_NAME = "GeneralDefaultPreferences";
	
	private static final Map<String,Object> ATTRI_NAME_MAP = UtilMisc.toMap(
		//GeneralDefaultPreferences.pHttpPort.getName(),null,
		//GeneralDefaultPreferences.pWebserverAddress.getName(),null,
		//GeneralDefaultPreferences.pAuthorizedIP.getName(),null,
		//GeneralDefaultPreferences.pCheckAddressAndLogin.getName(),null,
		//GeneralDefaultPreferences.pCreateStaticHTML.getName(),null,
		GeneralDefaultPreferences.pLocaleEnabled.getName(),null,
		GeneralDefaultPreferences.pAcknowledgeMonitors.getName(),null,
		GeneralDefaultPreferences.pAlertIconLink.getName(),null,
		GeneralDefaultPreferences.pReportIconLink.getName(),null,
		GeneralDefaultPreferences.pDisplayGauges.getName(),null,
		GeneralDefaultPreferences.pIsI18N.getName(),null,
		GeneralDefaultPreferences.pMainGaugesPerRow.getName(),GeneralDefaultPreferences.pMainGaugesPerRow.getDefault(),
		GeneralDefaultPreferences.pBackups2Keep.getName(),GeneralDefaultPreferences.pBackups2Keep.getDefault(),
		GeneralDefaultPreferences.pSuspendMonitors.getName(),null,
		GeneralDefaultPreferences.pDefaultAuthUsername.getName(),null,
		GeneralDefaultPreferences.pDefaultAuthPassword.getName(),null,
		"_defaultAuthWhenToAuthenticate",null,
		GeneralDefaultPreferences.pLicenseForX.getName(),null,
		GeneralDefaultPreferences.pLicense.getName(),null
	);
	
	public static Map<?,?> getGeneralAttr(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			result = ServiceUtil.returnSuccess();
			result.put("data", getGeneralAttr());
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error getGeneral: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static List<String> getGeneralAttr(){
		List<String> retList = new ArrayList<String>();
		retList.addAll(ATTRI_NAME_MAP.keySet());
		return retList;
	}
	
	public static Map<?,?> getGeneral(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			result = ServiceUtil.returnSuccess();
			result.put("data", getGeneral());
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error getGeneral: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static Map<?,?> getGeneral() throws Exception{
		Map<Object,Object> retmap = new HashMap<Object,Object>();
		for (Object attrName : ATTRI_NAME_MAP.keySet()){
			retmap.put(attrName, getGeneral(attrName));
		}
		return retmap;
	}
	public static Object getGeneral(Object key) throws Exception{
		if (!isInAttriNameMap(key))return null;
		Object value = getValue(key);
		if (value == null || "".equals(value)){
			return getDefault(key);
		}
		if (GeneralDefaultPreferences.pBackups2Keep.getName().equals(key)){
			int val = toInt((String)value);
			if ( val<1 || val >80 ) return getDefault(key);
		}
		if (GeneralDefaultPreferences.pMainGaugesPerRow.getName().equals(key)){
			int val = toInt((String)value);
			if ( val<1 || val >20 ) return getDefault(key);
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

	public static Map<?,?> putGeneral(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			Map<?,?> value = (Map<?, ?>) getNotOptionalValue(context,"data");
			putGeneral(value);
			result = ServiceUtil.returnSuccess();
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error putGeneral: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static void putGeneralOld(Map<?,?> data) throws Exception{
		try{
			List<SSInstanceProperty> assinstanceproperty = new ArrayList<SSInstanceProperty>();
			for (Object key : getGeneralAttr()){
				Object value = data.get(key);
				if (value == null) continue;
				assinstanceproperty.add(new SSInstanceProperty("" + key,value));
			}
			new APIPreference().update(CLASS_NAME,null, null, assinstanceproperty.toArray(new SSInstanceProperty[0]));
		}finally{
			refrashData();
		}
	}
	public static void putGeneral(Map<?,?> data) throws Exception{
		for (Object key : getGeneralAttr()){
			Object value = data.get(key);
			value = verify(key,value,data);
			putGeneral(key,value);
		}
	}
	
	private static String verify(Object key , Object value,Map<?,?> data) throws Exception
	{
		String valStr = "".equals(value) ? null : (String)value;
		if (GeneralDefaultPreferences.pHttpPort.getName().equals(key)){
			if (valStr != null)
			{
                try {
    				int val = (new Integer((valStr).trim())).intValue();
                    if (val == 0) {
                        throw new Exception("HTTP Port must be a number greater than 0");
                    }
                } catch (NumberFormatException numberformatexception) {
                    throw new Exception("The entry is not a valid number.");
                }
            }
		}else if(GeneralDefaultPreferences.pAuthorizedIP.getName().equals(key)){
            if (valStr != null && !com.dragonflow.Utils.TextUtils.onlyChars(valStr, "0123456789,.*")) {
            	throw new Exception("The IP Address allowed access contained illegal characters");
            }
        } else if (GeneralDefaultPreferences.pCheckAddressAndLogin.getName().equals(key)){
            if (valStr != null) {
            	Object authorizedIP = data.get(GeneralDefaultPreferences.pAuthorizedIP.getName());
            	if ("".equals(authorizedIP) || authorizedIP == null)
            		throw new Exception("To enable \"Require both IP address and Login\" you must fill in authorized IP address(es))");
            }
        } else if (GeneralDefaultPreferences.pMainGaugesPerRow.getName().equals(key)){
            if (valStr == null) {
                valStr = getDefault(key);
            }
            int j = com.dragonflow.Utils.TextUtils.toInt(valStr);
            if (j < 1 || j > 20) {
                valStr = getDefault(key);
            }
        } else if (GeneralDefaultPreferences.pBackups2Keep.getName().equals(key)){
            if (valStr == null) {
                valStr = getDefault(key);
            }
            int k = com.dragonflow.Utils.TextUtils.toInt(valStr);
            if (k < 1 || k > 80) {
                valStr = getDefault(key);
            }
        }
		return valStr;
	}
	
	public static void putGeneral(Object key , Object value)
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
	private static String getDefault(Object name)
	{
		return (String) ATTRI_NAME_MAP.get(name);
	}
	private static int toInt(String val){
		try{
			return Integer.parseInt(val);
		}catch(Exception e){}
		return 0;
	}
	private static void refrashData()throws Exception
	{
		Config.clearCache();
	}
}
