package com.siteview.ecc.drive;

import java.util.HashMap;
import java.util.Map;

public class MonitorDict {
	private static Map<String, String> dataMonitor = new HashMap<String, String>(); 

	private static Map<String, Object> dataAttribute = new HashMap<String, Object>(); 
	
	static {
		registerMonitor("Ping","PingMonitor");
		registerMonitor("URL","URLSequenceMonitor");
		
		registerAttribute("addErrorComparison",null);
		registerAttribute("addErrorCondition",null);
		registerAttribute("addWaringCondition",null);
		registerAttribute("busyServers",null);
		registerAttribute("busyWorkers",null);
		registerAttribute("bytesPerReq",null);
		registerAttribute("bytesPerSec",null);
		registerAttribute("Cisco_chassisPs1Status",null);
		registerAttribute("cpuLoad",null);
		registerAttribute("dbFreeResources",null);
		registerAttribute("dbIndex",null);
		registerAttribute("dbTotalResources",null);
		registerAttribute("downloadsize",null);
		registerAttribute("drpAvgReqTime",null);
		registerAttribute("FreePhysicalMemory",null);
		registerAttribute("freeSpace",null);
		registerAttribute("hrProcessorLoad",null);
		registerAttribute("idleServers",null);
		registerAttribute("idleWorkers",null);
		registerAttribute("ifInDiscardsRate",null);
		registerAttribute("ifInOctetsRate",null);
		registerAttribute("ifOutDiscardsRate",null);
		registerAttribute("ifOutOctetsRate",null);
		registerAttribute("Mbfree",null);
		registerAttribute("opentable",null);
		registerAttribute("PercentProcessorTime",null);
		registerAttribute("ProcessCount",null);
		registerAttribute("packetsGoodPercent",null);
		registerAttribute("pagesPerSec",null);
		registerAttribute("percentFull",null);
		registerAttribute("percentUsed",null);
		registerAttribute("percentUsedPhysicalMemory",null);
		registerAttribute("querycount",null);
		registerAttribute("reqPerSec",null);
		registerAttribute("roundTripTime",null);
		registerAttribute("SV_BufHitRate",null);
		registerAttribute("SV_Cursor",null);
		registerAttribute("SV_DeadLock",null);
		registerAttribute("SV_LibHitRate",null);
		registerAttribute("SV_Lock",null);
		registerAttribute("SV_Session",null);
		registerAttribute("SV_Transaction",null);
		registerAttribute("SV_time",null);
		registerAttribute("slowquery",null);
		registerAttribute("status",null);
		registerAttribute("stCreatedSessionCnt",null);
		registerAttribute("svrows",null);
		registerAttribute("sysFreeMem",null);
		registerAttribute("sysTotalMem",null);
		registerAttribute("ThreadCount",null);
		registerAttribute("TotalMemory",null);
		registerAttribute("TotalPhysicalMemory",null);
		registerAttribute("TotalSize",null);
		registerAttribute("TotalTime",null);
		registerAttribute("thread",null);
		registerAttribute("totalAccesses",null);
		registerAttribute("totalKBytes",null);
		registerAttribute("totalmatch",null);
		registerAttribute("totaltime",null);
		registerAttribute("utilization",null);
		registerAttribute("WorkingSet",null);
		registerAttribute("_Community",null);
		registerAttribute("_connPort",null);
		registerAttribute("_Disk",null);
		registerAttribute("_DomName",null);
		registerAttribute("_errorParameter",null);
		registerAttribute("_Facelity",null);
		registerAttribute("_frequency","_frequency");
		registerAttribute("_frequencyUnit",null);
		registerAttribute("_goodParameter",null);
		registerAttribute("_Index",null);
		registerAttribute("_InterfaceIndex",null);
		registerAttribute("_IPName",null);
		registerAttribute("_Level",null);
		registerAttribute("_MachineName","_hostname");
		registerAttribute("_MachStr",null);
		registerAttribute("_MatchIP",null);
		registerAttribute("_MatchStr",null);
		registerAttribute("_Matchstring",null);
		registerAttribute("_match",null);
		registerAttribute("_monitorcondition",null);
		registerAttribute("_monitorProcessList",null);
		registerAttribute("_other",null);
		registerAttribute("_PassWord",null);
		registerAttribute("_PostData",null);
		registerAttribute("_ProxyPass","_proxypassword");
		registerAttribute("_ProxyServerPort", null);
		registerAttribute("_ProxyUser","_proxyusername");
		registerAttribute("_private",null);
		registerAttribute("_RemoteMachineName",null);
		registerAttribute("_RetryDelay",null);
		registerAttribute("_RetryTimes",null);
		registerAttribute("_SelValue",null);
		registerAttribute("_SendBytes","_packetSize");
		registerAttribute("_SendNums",null);
		registerAttribute("_SendStr",null);
		registerAttribute("_ServerManUrl",null);
		registerAttribute("_SqlStr",null);
		registerAttribute("_TimeOut","_timeout");
		registerAttribute("_Timeout","_timeout");
		registerAttribute("_URL","url");
		registerAttribute("_UserAccount",null);
		registerAttribute("_warningParameter",null);
		
		
		/*
		registerAttribute("","_errorFrequency");
		registerAttribute("","_class");
		registerAttribute("","_notLogToTopaz");
		_onlyStatusChanges
		_logOnlyThresholdMeas
		_logOnlyMonitorData
		_internalId
		_maxrun
		customData
		sample
		monitorDoneTime
		gethostname
		nodata
		maxErrorCount
		monitorsInError
		_packetSize
		
		*/
	}
	
	private static void registerMonitor(String key,String value)
	{
		dataMonitor.put(key, value);
	}
	public static String getMonitorClass(String key)
	{
		return dataMonitor.get(key);
	}

	private static void registerAttribute(String key,Object value)
	{
		dataAttribute.put(key, value);
	}
	
	public static Object getAttribute(String key)
	{
		return dataAttribute.get(key);
	}
	
	public static Map<String,String> convert(Map<String,String> svdbParams)
	{
		Map<String,String> retResult = new HashMap<String,String>();
		for (String key : svdbParams.keySet()) {
			Object monitorAttribute = getAttribute(key);
			if (monitorAttribute == null) continue;
			String monitorAttributeValue = svdbParams.get(key);
			if (monitorAttributeValue == null) continue;
			if (monitorAttribute.getClass().equals(String.class))
			{
				retResult.put((String)monitorAttribute, monitorAttributeValue);
			}
		}
		getSpecialParam(svdbParams, retResult);
		return retResult;
	}
	
	
	private static void getSpecialParam(Map<String,String> svdbParams,Map<String,String> retResult)
	{
		
		if (	svdbParams.get("_ProxyServer") !=null 
			&&  svdbParams.get("_ProxyServerPort") !=null){
			String pProxy = svdbParams.get("_ProxyServer") + ":" + svdbParams.get("_ProxyServerPort");
			retResult.put("_proxy", pProxy);
		}
		retResult.put("_proxy", "www.sina.com.cn:80");

		//sitescope的参数中,_frequency要求是15以上的数
		int frequency = 15;
		try{
			frequency = Integer.parseInt(retResult.get("_frequency"));
		}catch(Exception e){}
		
		retResult.put("_frequency", (frequency > 15 ? "" + frequency : "15"));
		
	}
}
