package com.siteview.svecc.service;


import java.util.HashMap;
import java.util.Map;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

public class LogOperate {

	public static Map<String, Object> getLogPreference(
			DispatchContext ctx, Map<?, ?> context) {
		try {
			Map<String, Object> map2 = ServiceUtil.returnSuccess();
			map2.put("LogInfo", getLogPreference());
			return map2;
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static Map<?, ?> getLogPreference() throws Exception {
		Map<String ,Object> retMap=new HashMap<String,Object>();
		retMap.put("_dailyLogKeepDays",( Config.configGet("_dailyLogKeepDays")==null)?" ":Config.configGet("_dailyLogKeepDays"));
		retMap.put("_dailyLogTotalLimit", (Config.configGet("_dailyLogTotalLimit")==null)?" ":Config.configGet("_dailyLogTotalLimit"));
		retMap.put("_logJdbcURLSiteViewLog", (Config.configGet("_logJdbcURLSiteViewLog")==null)?" ":Config.configGet("_logJdbcURLSiteViewLog"));
		retMap.put("_logJdbcDriverSiteViewLog", (Config.configGet("_logJdbcDriverSiteViewLog")==null)?" ":Config.configGet("_logJdbcDriverSiteViewLog"));
		retMap.put("_logJdbcUserSiteViewLog", (Config.configGet("_logJdbcUserSiteViewLog")==null)?" ":Config.configGet("_logJdbcUserSiteViewLog"));
		retMap.put("_logJdbcPasswordSiteViewLog", (Config.configGet("_logJdbcPasswordSiteViewLog")==null)?" ":Config.configGet("_logJdbcPasswordSiteViewLog"));
		retMap.put("_logJdbcURLBackupSiteViewLog",(Config.configGet("_logJdbcURLBackupSiteViewLog")==null)?" ":Config.configGet("_logJdbcURLBackupSiteViewLog"));
		return retMap;
	}
	
	public static Map<String, Object> saveLogChange(
			DispatchContext ctx, Map<?, ?> context) {
		try {
			saveLogChange(context);
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
		return ServiceUtil.returnSuccess();
	}

	public static void saveLogChange(Map<?,?> context) throws Exception {
		Map value=(Map)context.get("value");
		System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~"+(Map)context.get("value"));
		Config.configPut("_dailyLogKeepDays",(String)value.get("dailyLogKeepDays") );
		Config.configPut("_dailyLogTotalLimit",(String)value.get("dailyLogTotalLimit") );
		Config.configPut("_logJdbcURLSiteViewLog",(String)value.get("logJdbcURLSiteViewLog") );
		Config.configPut("_logJdbcDriverSiteViewLog",(String)value.get("logJdbcDriverSiteViewLog") );
		Config.configPut("_logJdbcUserSiteViewLog",(String)value.get("logJdbcUserSiteViewLog") );
		Config.configPut("_logJdbcPasswordSiteViewLog",(String)value.get("logJdbcPasswordSiteViewLog") );
		Config.configPut("_logJdbcURLBackupSiteViewLog",(String)value.get("logJdbcURLBackupSiteViewLog") );
	}
}
