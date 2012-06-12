package com.siteview.ecc.service;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

import com.siteview.svecc.service.Assistant;

public class ScheduleUI {

	public static Map<String,Object> saveRangSchedule(DispatchContext ctx,Map<?,?> context){
		try{
			String name=(String)context.get("name");
		Map map=Assistant.ScheduleOperate(context);
		if((Boolean)map.get("sodier")==false){
			throw new Exception("时间格式错误");//message.getMessage(??);
		}else{
			Map<String,Object> mapV=new HashMap<String,Object>();
			mapV.put("_name",name);
			mapV.put("_schedule", (String)map.get("timeString"));

			ctx.getDispatcher().runSync("saveRangScheduleV",UtilMisc.toMap("value", mapV));
		}
		}catch(Exception e){
			return ServiceUtil.returnFailure(e.getMessage());			
		}
		return ServiceUtil.returnSuccess();
	}
	
	public static Map<String,Object> saveAbsoluteSchedule(DispatchContext ctx,Map<?,?> context){
		try{
		String name=(String)context.get("name");
		String scheduleAt0=(String)context.get("scheduleAt0");
		String scheduleAt1=(String)context.get("scheduleAt1");
		String scheduleAt2=(String)context.get("scheduleAt2");
		String scheduleAt3=(String)context.get("scheduleAt3");
		String scheduleAt4=(String)context.get("scheduleAt4");
		String scheduleAt5=(String)context.get("scheduleAt5");
		String scheduleAt6=(String)context.get("scheduleAt6");
		String timeV=" _name="+name+" _schedule="+"*"+scheduleAt0+","+scheduleAt1+","+scheduleAt2+","+scheduleAt3+","+scheduleAt4+","+scheduleAt5+","+scheduleAt6;
		ctx.getDispatcher().runSync("saveAbsoluteScheduleV", UtilMisc.toMap("value", timeV));	
		}catch(Exception e){
			return ServiceUtil.returnFailure(e.getMessage());
		}
		return ServiceUtil.returnSuccess();
	}
	
	public static Map<String,Object> getScheduleSettingsList(DispatchContext ctx,Map<?,?> context){
		try{
			List list=(List)ctx.getDispatcher().runSync("getScheduleList",new HashMap()).get("value");
			Map retMap=ServiceUtil.returnSuccess();

			retMap.put("result", list);
			return retMap;
		}catch(Exception e){
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}
	public static Map<String,Object> delSchedule(DispatchContext ctx,Map<?,?> context){
	try{
		String id=(String) context.get("id");
		ctx.getDispatcher().runSync("delScheduleV", UtilMisc.toMap("id", id));
		return ServiceUtil.returnSuccess();
	}catch(Exception e){
		return ServiceUtil.returnFailure(e.getMessage());
	}
	}
	public static Map<String ,Object> editAbsoluteSchedule(DispatchContext ctx,Map<?,?> context){
		try{
			String id=(String) context.get("id");
			Map map=(Map) (ctx.getDispatcher().runSync("editAbsoluteScheduleV", UtilMisc.toMap("id", id)).get("value"));
			Map<String, Object> retMap= ServiceUtil.returnSuccess();
			retMap.put("result", map);
			return retMap;
		}catch(Exception e){
			return ServiceUtil.returnFailure(e.getMessage());
		}
		}
	public static Map<String ,Object> updateAbsoluteSchedule(DispatchContext ctx,Map<?,?> context){
		try{
			String id=(String) context.get("id");
			String name=(String)context.get("name");
			String scheduleAt0=(String)context.get("scheduleAt0");
			String scheduleAt1=(String)context.get("scheduleAt1");
			String scheduleAt2=(String)context.get("scheduleAt2");
			String scheduleAt3=(String)context.get("scheduleAt3");
			String scheduleAt4=(String)context.get("scheduleAt4");
			String scheduleAt5=(String)context.get("scheduleAt5");
			String scheduleAt6=(String)context.get("scheduleAt6");
			String timeV="_id="+id+" _name="+name+" _schedule="+"*"+scheduleAt0+","+scheduleAt1+","+scheduleAt2+","+scheduleAt3+","+scheduleAt4+","+scheduleAt5+","+scheduleAt6;
			ctx.getDispatcher().runSync("updateAbsoluteScheduleV", UtilMisc.toMap("value", timeV,"id",id));
			return ServiceUtil.returnSuccess();
		}catch(Exception e){
			return ServiceUtil.returnFailure(e.getMessage());
		}
		}

	public static Map<String ,Object> editRangeSchedule(DispatchContext ctx,Map<?,?> context){
		try{
			String id=(String) context.get("id");
			Map map=(Map) (ctx.getDispatcher().runSync("editRangeScheduleV", UtilMisc.toMap("id", id)).get("value"));
			Map<String, Object> retMap= ServiceUtil.returnSuccess();
			retMap.put("result", map);
			return retMap;
		}catch(Exception e){
			return ServiceUtil.returnFailure(e.getMessage());
		}
		}
	public static Map<String ,Object> updateRangSchedule(DispatchContext ctx,Map<?,?> context){
		try{
			String id=(String) context.get("id");
			String name=(String)context.get("name");
			Map map=Assistant.ScheduleOperate(context);
			String timeV="_id="+id+" _name="+name+" _schedule="+(String)map.get("timeString");
			ctx.getDispatcher().runSync("updateAbsoluteScheduleV", UtilMisc.toMap("value", timeV,"id",id));
			return ServiceUtil.returnSuccess();
		}catch(Exception e){
			return ServiceUtil.returnFailure(e.getMessage());
		}
		}	
}
