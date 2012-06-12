package com.siteview.ecc.service;

import java.util.HashMap;
import java.util.Map;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.GenericServiceException;
import org.ofbiz.service.ServiceUtil;

public class LogUI {

	public static Map<String,Object> getLogSetInfo(DispatchContext ctx,Map<?,?> context){
		Map map;
		try {
			map = (Map) ctx.getDispatcher().runSync("getLogPreference",new HashMap()).get("LogInfo");
		} catch (GenericServiceException e) {
			return ServiceUtil.returnError(e.getMessage());
		}
		Map<String, Object> retMap=ServiceUtil.returnSuccess();
		System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~"+map);
		retMap.put("setInfo", map);
		return retMap;
	}
	
	public static Map<String,Object> saveLogSetting(DispatchContext ctx,Map<?,?> context){
		try{
		Map<String,Object> map=new HashMap<String,Object>();
		String dailyLogKeepDays=((String)context.get("dailyLogKeepDays")==null)?" ":(String)context.get("dailyLogKeepDays");
		String dailyLogTotalLimit=((String)context.get("dailyLogTotalLimit")==null)?" ":(String)context.get("dailyLogTotalLimit");
		String logJdbcURLSiteViewLog=((String)context.get("logJdbcURLSiteViewLog")==null)?" ":(String)context.get("logJdbcURLSiteViewLog");
		String logJdbcDriverSiteViewLog=((String)context.get("logJdbcDriverSiteViewLog")==null)?" ":(String)context.get("logJdbcDriverSiteViewLog");
		String logJdbcUserSiteViewLog=((String)context.get("logJdbcUserSiteViewLog")==null)?" ":(String)context.get("logJdbcUserSiteViewLog");
		String logJdbcPasswordSiteViewLog=((String)context.get("logJdbcPasswordSiteViewLog")==null)?" ":(String)context.get("logJdbcPasswordSiteViewLog");
		String logJdbcURLBackupSiteViewLog=((String)context.get("logJdbcURLBackupSiteViewLog")==null)?" ":(String)context.get("logJdbcURLBackupSiteViewLog");
		map.put("dailyLogKeepDays",dailyLogKeepDays);
		map.put("dailyLogTotalLimit",dailyLogTotalLimit);
		map.put("logJdbcURLSiteViewLog",logJdbcURLSiteViewLog);
		map.put("logJdbcDriverSiteViewLog",logJdbcDriverSiteViewLog);
		map.put("logJdbcUserSiteViewLog",logJdbcUserSiteViewLog);
		map.put("logJdbcPasswordSiteViewLog",logJdbcPasswordSiteViewLog);
		map.put("logJdbcURLBackupSiteViewLog",logJdbcURLBackupSiteViewLog);
		ctx.getDispatcher().runSync("saveLogChange", UtilMisc.toMap("value", map));
		}catch(Exception e){
			return ServiceUtil.returnFailure(e.getMessage());
		}
		return ServiceUtil.returnSuccess();
	}
}
