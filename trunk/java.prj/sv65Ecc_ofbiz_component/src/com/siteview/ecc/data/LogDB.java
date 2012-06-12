package com.siteview.ecc.data;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericEntityException;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityConditionList;
import org.ofbiz.entity.condition.EntityExpr;
import org.ofbiz.entity.condition.EntityOperator;

import com.dragonflow.SiteView.AtomicMonitor;
import com.siteview.ecc.drive.MonitorDevice;
import com.siteview.ecc.drive.MonitorDict;

public class LogDB {
	private static final SimpleDateFormat dateformat=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

	public static void add(AtomicMonitor monitor) throws Exception
	{
		String state = getStatusString(monitor);
		String value = monitor.getSvdbkeyValueStr();
		//add("" + monitor.getMethodId(), state, value);
		//MonitorDevice.updateMonitor(monitor);
	}
	
	public static void add(String id , String state , String value) throws Exception
	{
		LogDB.add(id, state, value, GenericDelegator.getGenericDelegator("default"));
	}
	public static void add(String id , String state , String value,GenericDelegator delegator) throws Exception{
		GenericValue newValue = delegator.makeValue("SvLog");
		newValue.set("monitorID", id);
		newValue.set("CreateTime", dateformat.format(new Date()));
		newValue.set("RecordState", state);
		newValue.set("keyValueStr", value);
		newValue.create();
	}
	
	private static String getStatusString(AtomicMonitor monitor) throws Exception
	{
		GenericDelegator delegator = GenericDelegator.getGenericDelegator("default");
		//String methodId = (String) monitor.getMethodId();

		ArrayList<EntityExpr> exprs = new ArrayList<EntityExpr>();
    	//exprs.add(new EntityExpr("method_id", EntityOperator.EQUALS, methodId));
        EntityCondition condition = new EntityConditionList<EntityExpr>(exprs, EntityOperator.AND);
        List<GenericValue> conditions = delegator.findList("SvCiMethodCondition", condition, null,UtilMisc.toList("idx"),null,true);
		for (GenericValue val : conditions){
			String paramName = val.getString("sv_paramname");
			if (paramName == null) continue;
			String operate = val.getString("sv_operate");
			if (operate == null) continue;
			String paramValue = val.getString("sv_paramvalue");
			if (paramValue == null) continue;
			String state = val.getString("sv_status");
			if (state == null) continue;
			if (monitor.getSvdbRecordState(paramName, operate, paramValue)) return state;
		}
		
		return "Unknown";
	}

}
