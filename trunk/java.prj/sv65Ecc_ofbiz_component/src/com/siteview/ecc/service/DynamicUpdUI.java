package com.siteview.ecc.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.GenericServiceException;
import org.ofbiz.service.ServiceUtil;

import com.dragonflow.SiteView.DispatcherConnection;

public class DynamicUpdUI {

	public static Map<String, Object> getDynamicUpdPrefefencesList(
			DispatchContext ctx, Map<?, ?> context) {
		try {
			Map<String, Object> map2 = ServiceUtil.returnSuccess();
			List<Map<?,?>> list=(List<Map<?, ?>>) (ctx.getDispatcher().runSync(
					"getDynamicUpdPrefefencesListValue", new HashMap()))
					.get("result");

			if(list.size()>0){
			map2.put("result",list );
			
			}else{
				Map<String,Object> mapV=new HashMap<String,Object>();
				mapV.put("_name", "");
				mapV.put("_Server", "no Dynamic Update Sets defined");
				mapV.put("_id", "no");
				list.add(mapV);
				map2.put("result",list );

			}
			return map2;	
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}
	public static Map<String,Object> pagerSettingInfo(DispatchContext ctx, Map<?,?> context){
		String id=(String)context.get("id");
		Map<String,Object> map=new HashMap<String,Object>();
		if(id==null||"".equals(id)){
	//		map.put("_set", "");
			map.put("_otheroid", "");
			map.put("_dbUserName", "");
			map.put("_id", "");
			map.put("_groupSet", "$NODE-IP$");
			map.put("_dbQueryTimeout", "60");
			map.put("_dbConnectTimeout", "60");
			map.put("_frequency", "21600");
			map.put("_poolIncluded", "");
	//		map.put("_oid", "");
			map.put("_host", "");
			map.put("_fileEncoding", "");
			map.put("_group", "");
			map.put("_dbDriver", "com.inet.tds.TdsDriver");
			map.put("_dbConnectionURL", "");
			map.put("_community", "public");
			map.put("_name", "");
			map.put("_dbSqlQuery", "");
			map.put("_excludeIP", "");
			map.put("_dbPassword", "");
		}else{
			try {
				map = (Map) ctx.getDispatcher().runSync("getValueById", UtilMisc.toMap("id", id)).get("result");
				if(map.get("_set")==null) { map.put("_set", "");}
				if(map.get("_otheroid")==null) { map.put("_otheroid", "");}
				if(map.get("_dbUserName")==null) { map.put("_dbUserName", "");}
				if(map.get("_groupSet")==null) { map.put("_groupSet", "");}
				if(map.get("_dbQueryTimeout")==null) { map.put("_dbQueryTimeout", "");}
				if(map.get("_dbConnectTimeout")==null) { map.put("_dbConnectTimeout", "");}
				if(map.get("_frequency")==null) { map.put("_frequency", "");}
				if(map.get("_poolIncluded")==null) { map.put("_poolIncluded", "");}
				if(map.get("_oid")==null) { map.put("_oid", "");}
				if(map.get("_host")==null) { map.put("_host", "");}
				if(map.get("_fileEncoding")==null) { map.put("_fileEncoding", "");}
				if(map.get("_group")==null) { map.put("_group", "");}
				if(map.get("_dbDriver")==null) { map.put("_dbDriver", "");}
				if(map.get("_dbConnectionURL")==null) { map.put("_dbConnectionURL", "");}
				if(map.get("_community")==null) { map.put("_community", "");}
				if(map.get("_name")==null) { map.put("_name", "");}
				if(map.get("_dbSqlQuery")==null) { map.put("_dbSqlQuery", "");}
				if(map.get("_excludeIP")==null) { map.put("_excludeIP", "");}
				if(map.get("_dbPassword")==null) { map.put("_dbPassword", "");}
			} catch (GenericServiceException e) {
			return ServiceUtil.returnFailure(e.getMessage());
			}
		}
		Map retmap=ServiceUtil.returnSuccess();
		retmap.put("result",map);
		return retmap;
	}
	public static Map<String,Object> saveSet(DispatchContext ctx,Map<?,?> context){
		try{
		Map<String,Object> map=new HashMap<String,Object>();
		map.put("_set", ((String)context.get("set")==null)?" ":((String)context.get("set")));
		map.put("_otheroid", ((String)context.get("otheroid")==null)?" ":((String)context.get("otheroid")));
		map.put("_dbUserName",((String)context.get("dbUserName")==null)?" ":((String)context.get("dbUserName")));
//		map.put("_id", "");
		map.put("_groupSet",((String)context.get("groupSet")==null)?" ":((String)context.get("groupSet")));
		map.put("_dbQueryTimeout", ((String)context.get("dbQueryTimeout")==null)?" ":((String)context.get("dbQueryTimeout")));
		map.put("_dbConnectTimeout", ((String)context.get("dbConnectTimeout")==null)?" ":((String)context.get("dbConnectTimeout")));
		map.put("_frequency", ((String)context.get("frequency")==null)?" ":((String)context.get("frequency")));
		map.put("_poolIncluded", ((String)context.get("poolIncluded")==null)?" ":((String)context.get("poolIncluded")));
		map.put("_oid", ((String)context.get("oid")==null)?" ":((String)context.get("oid")));
		map.put("_host",((String)context.get("host")==null)?" ":((String)context.get("host")));
		map.put("_fileEncoding",((String)context.get("fileEncoding")==null)?" ":((String)context.get("fileEncoding")));
		map.put("_group", ((String)context.get("group")==null)?" ":((String)context.get("group")));
		map.put("_dbDriver", ((String)context.get("dbDriver")==null)?" ":((String)context.get("dbDriver")));
		map.put("_dbConnectionURL", ((String)context.get("dbConnectionURL")==null)?" ":((String)context.get("dbConnectionURL")));
		map.put("_community",((String)context.get("community")==null)?" ":((String)context.get("community")));
		map.put("_name", ((String)context.get("name")==null)?" ":((String)context.get("name")));
		map.put("_dbSqlQuery", ((String)context.get("dbSqlQuery")==null)?" ":((String)context.get("dbSqlQuery")));
		map.put("_excludeIP", ((String)context.get("excludeIP")==null)?" ":((String)context.get("excludeIP")));
		map.put("_dbPassword", ((String)context.get("dbPassword")==null)?" ":((String)context.get("dbPassword")));
		
		String id=(String)context.get("id");
		if(id==null||"".equals(id)){
			ctx.getDispatcher().runSync("addDynamicSet", UtilMisc.toMap("result",map));			
		}else{
			map.put("_id", (String)context.get("id"));
			ctx.getDispatcher().runSync("editDynamicSet", UtilMisc.toMap("id",id,"result",map));
			
		}
		}catch(Exception e){
			return ServiceUtil.returnFailure(e.getMessage());
		}
		return ServiceUtil.returnSuccess();
	}

	public static Map<?,?> delDynamicseting(DispatchContext ctx, Map<?,?> context){
		String id=(String)context.get("id");
		try {
			ctx.getDispatcher().runSync("deleteDynamicSet", UtilMisc.toMap("id",id));
		} catch (GenericServiceException e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
		return ServiceUtil.returnSuccess();
	}
}
