package com.siteview.web.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericEntity;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityOperator;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.LocalDispatcher;
import org.ofbiz.service.ServiceUtil;

import com.siteview.web.util.Tools;

public class WebSiteService {
	private static final String module = WebSiteService.class.getName();
	
	public static Map<?,?> getNoteInfos(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			result = ServiceUtil.returnSuccess();
			
			Locale locale = (Locale) context.get("locale");
			
			result.put("result", getNoteInfos(locale,ctx.getDelegator(),(String)context.get("category")));
			
			result.put("categoryInfo", getCategory(locale,ctx.getDelegator(),(String)context.get("category")));
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error getNoteInfos: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static List<GenericValue> getNoteInfos(Locale locale,String category)throws Exception{
		return getNoteInfos(locale,GenericDelegator.getGenericDelegator("default"),category);
	}
	
	public static List<GenericValue> getCategory(Locale locale,GenericDelegator genericDelegator,String category)throws Exception{
		EntityCondition entityCondition = EntityCondition.makeCondition(UtilMisc.toMap("id", category));
		List<GenericValue> list = genericDelegator.findList(getEntityName(locale,"SvNoteInfoCategory"), getEntityCondition(locale,entityCondition),  null, null,null, false);
		List<GenericValue> retlist = new LinkedList<GenericValue>();
		for (GenericValue val : list){
			String parentid = val.getString("parentid");
			if (parentid == null) continue; 
			retlist.addAll(getCategory(locale,genericDelegator,parentid));
		}
		retlist.addAll(list);
		return retlist;
	}
	
	public static List<GenericValue> getAllCategory(Locale locale,GenericDelegator genericDelegator,String category)throws Exception{
		EntityCondition entityCondition = EntityCondition.makeCondition(UtilMisc.toMap("id", category));
		List<GenericValue> listSelf = genericDelegator.findList(getEntityName(locale,"SvNoteInfoCategory"), getEntityCondition(locale,entityCondition),  null, null,null, false);
		listSelf.addAll(getChildrenCategory(locale,genericDelegator,category));
		return listSelf;
	}

	private static List<GenericValue> getChildrenCategory(Locale locale,GenericDelegator genericDelegator,String category)throws Exception{
		EntityCondition entityCondition = EntityCondition.makeCondition(UtilMisc.toMap("parentid", category));
		List<GenericValue> listChildren = genericDelegator.findList(getEntityName(locale,"SvNoteInfoCategory"), getEntityCondition(locale,entityCondition),  null, null,null, false);
		for (GenericValue val : listChildren){
			String id = val.getString("id");
			if (id == null) continue; 
			listChildren.addAll(getChildrenCategory(locale,genericDelegator,id));
		}
		return listChildren;
	}
	
	public static List<GenericValue> getNoteInfosOld(Locale locale,GenericDelegator genericDelegator,String category)throws Exception{
		if (category == null) return new LinkedList<GenericValue>(); 
		List<GenericValue> categoryList = getAllCategory(locale,genericDelegator,category);
		List<GenericValue> retlist = new LinkedList<GenericValue>();
		for (GenericValue val : categoryList){
			String id = val.getString("id");
			if (id == null) continue; 
			EntityCondition entityCondition = EntityCondition.makeCondition(UtilMisc.toMap("category", id));
			retlist.addAll(genericDelegator.findList(getEntityName(locale,"SvViewNoteInfo"), getEntityCondition(locale,entityCondition),  null, UtilMisc.toList("idx"),null, false));
		}
		return retlist;
	}
	
	public static List<GenericValue> getNoteInfos(Locale locale,GenericDelegator genericDelegator,String category)throws Exception{
		if (category == null) return new LinkedList<GenericValue>(); 
		List<GenericValue> categoryList = getAllCategory(locale,genericDelegator,category);
		List<GenericValue> retlist = new LinkedList<GenericValue>();
		List<EntityCondition> conditionList= new ArrayList<EntityCondition>();
		for (GenericValue val : categoryList){
			String id = val.getString("id");
			if (id == null) continue;
			conditionList.add(EntityCondition.makeCondition("category", EntityOperator.EQUALS, id));
		}
		EntityCondition entityCondition = EntityCondition.makeCondition(conditionList,EntityOperator.OR);
		retlist.addAll(genericDelegator.findList(getEntityName(locale,"SvViewNoteInfo"), getEntityCondition(locale,entityCondition),  null, UtilMisc.toList("idx"),null, false));
		return retlist;
	}
		
	public static Map<?,?> getNoteInfo(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			result = ServiceUtil.returnSuccess();
			Locale locale = (Locale) context.get("locale");
			Map<?,?> map = getNoteInfo(locale,ctx.getDelegator(),(String)context.get("id"));
			result.put("result", map);
			result.put("categoryInfo", getCategory(locale,ctx.getDelegator(),(String)map.get("category")));
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error getNoteInfos: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static Map<?,?> getNoteInfo(Locale locale,String id)throws Exception{
		return getNoteInfo(locale,GenericDelegator.getGenericDelegator("default"),id);
	}
	
	public static Map<?,?> getNoteInfo(Locale locale,GenericDelegator genericDelegator,String id)throws Exception{
		EntityCondition entityCondition = EntityCondition.makeCondition(UtilMisc.toMap("id", id));
		List<GenericValue> retlist = genericDelegator.findList(getEntityName(locale,"SvViewNoteInfo"), getEntityCondition(locale,entityCondition),  null, UtilMisc.toList("idx"),null, false);
		return retlist.size() == 1 ? retlist.get(0) : null;
	}

	
	public static Map<?,?> getCategorys(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			result = ServiceUtil.returnSuccess();
			
			Locale locale = (Locale) context.get("locale");
			
			result.put("categoryInfo", getCategoryInfo(locale,ctx.getDelegator(),(String)context.get("category")));
			result.put("children", getCategory1LevelChildren(locale,ctx.getDelegator(),(String)context.get("category")));
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error getCategorys: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static GenericValue getCategoryInfo(Locale locale,GenericDelegator genericDelegator,String category)throws Exception{
		EntityCondition entityCondition = EntityCondition.makeCondition(UtilMisc.toMap("id", category));
		List<GenericValue> listSelf = genericDelegator.findList(getEntityName(locale,"SvNoteInfoCategory"), getEntityCondition(locale,entityCondition),  null, null,null, false);
		return listSelf.size() == 1 ? listSelf.get(0) : null;
	}
	public static List<GenericValue> getCategory1LevelChildren(Locale locale,GenericDelegator genericDelegator,String category)throws Exception{
		if ("".equals(category))category=null;
		EntityCondition entityCondition = EntityCondition.makeCondition(UtilMisc.toMap("parentid", category));
		List<GenericValue> listSelf = genericDelegator.findList(getEntityName(locale,"SvNoteInfoCategory"), getEntityCondition(locale,entityCondition),  null, null,null, false);

		return listSelf;
	}
	public static Map<?,?> get1LevelNoteInfos(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			result = ServiceUtil.returnSuccess();
			
			Locale locale = (Locale) context.get("locale");
			
			result.put("result", get1LevelNoteInfos(locale,ctx.getDelegator(),(String)context.get("category")));
			
			result.put("categoryInfo", getCategory(locale,ctx.getDelegator(),(String)context.get("category")));
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error get1LevelNoteInfos: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}
	public static List<GenericValue> get1LevelNoteInfos(Locale locale,GenericDelegator genericDelegator,String category)throws Exception{
		if (category == null) return new LinkedList<GenericValue>(); 
		EntityCondition entityCondition = EntityCondition.makeCondition(UtilMisc.toMap("category", category));
		return genericDelegator.findList(getEntityName(locale,"SvViewNoteInfo"), getEntityCondition(locale,entityCondition),  null, UtilMisc.toList("idx"),null, false);
	}
	
	private static String getEntityName(Locale locale,String prefix)
	{
		StringBuffer bf = new StringBuffer();
		bf.append(prefix);
		bf.append(Tools.getLocale(locale));
		return bf.toString();
	}
	
	private static EntityCondition getEntityCondition(Locale locale,EntityCondition entityCondition)
	{
		
		EntityCondition countryEntityCondition = EntityCondition.makeCondition(
				UtilMisc.toList(
						EntityCondition.makeCondition("country",EntityOperator.LIKE, getLikeString(Tools.getCountry(locale))),
						EntityCondition.makeCondition("country",EntityOperator.EQUALS, ""),
						EntityCondition.makeCondition("country",EntityOperator.EQUALS, null)
				),
				EntityOperator.OR
		);
		if (entityCondition == null) return countryEntityCondition;
		return EntityCondition.makeCondition(UtilMisc.toList(entityCondition,countryEntityCondition),EntityOperator.AND);
		
	}
	
	private static String getLikeString(String str)
	{
		StringBuffer bf = new StringBuffer();
		bf.append("%");
		bf.append(str);
		bf.append("%");
		return bf.toString();
	}
	
	
// addid by lijian
	public static Map<?,?> getDisplayInformation(DispatchContext ctx, Map<?,?> context){
		Map<String, Object> result = null;
		try {
			result = ServiceUtil.returnSuccess();			
			Locale locale = (Locale) context.get("locale");		
			result.put("categoryInfo", getDisplayInformation(locale,ctx.getDelegator(),(String)context.get("category")));
			
		} catch (Exception e) {
			Debug.logWarning(e, module);
			result=ServiceUtil.returnError("Error getNoteInfos: " + e.toString());
			result.put("message", e.toString());
		}
		return result;
	}	
	public static List<GenericValue> getDisplayInformation(Locale locale,GenericDelegator genericDelegator,String category)throws Exception{
		if (category == null){
			return new LinkedList<GenericValue>(); 
		}
		EntityCondition whereCondition = EntityCondition.makeCondition("category", EntityOperator.EQUALS, category);		
        List<GenericValue> retlist = null;
		try {
			retlist = genericDelegator.findList("SvNoteInfo", whereCondition, null,null,null,false);	
			for(GenericValue val:retlist){
				if(val.get("coname")==null){
					val.put("coname","此记录还没有输入全");
				}
				if(val.get("textData")==null){
					val.put("textData","此记录还没有输入全");
				}
				if(val.get("name")==null){

					val.put("name","此记录还没有输入全");
				}
			}
        	return retlist;

		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
		return retlist;		
	}	
	
	public static Map<?,?> showContentInfo(DispatchContext ctx,Map<?,?> context){
		String id=(String)context.get("Id");
		Map<String,Object> result=null;
		try{
		result=ServiceUtil.returnSuccess();
		result.put("contentInfo", showContentInfo(ctx.getDelegator(),id));
		}catch(Exception e){
			return ServiceUtil.returnFailure(e.getMessage());
		}
		return result;
	}
	
	public static Map<?,?> showContentInfo(GenericDelegator genericDelegator,String id) throws Exception{
		EntityCondition whereCondition = EntityCondition.makeCondition("id", EntityOperator.EQUALS, id);
		Map<String, Object> retmap=null;
        List<GenericValue> list = null;

			list = genericDelegator.findList("SvNoteInfo", whereCondition, null,null,null,false);		
			 retmap=(Map)list.get(0);
				if(retmap.get("coname")==null){
					retmap.put("coname","此记录还没有录入完全");
				}
				if(retmap.get("textData")==null){
					retmap.put("textData","此记录还没有录入完全");
				}
				if(retmap.get("title")==null){
					retmap.put("title","此记录还没有录入完全");
				}
				if(retmap.get("name")==null){
					retmap.put("name","此记录还没有录入完全");
				}	
				if(retmap.get("enName")==null){
					retmap.put("enName","此记录还没有录入完全");
				}
				if(retmap.get("enConame")==null){
					retmap.put("enConame","此记录还没有录入完全");
				}
				if(retmap.get("enTitle")==null){
					retmap.put("enTitle","此记录还没有录入完全");
				}
				if(retmap.get("enTextData")==null){
					retmap.put("enTextData","此记录还没有录入完全");
				}				
        	return retmap;			
	}	
	
	public static Map<?,?> delCategaryInfo(DispatchContext ctx,Map<?,?> context){
		String id=(String)context.get("Id");
		try{
			delCategaryInfo(ctx.getDelegator(),id);
		}catch(Exception e){
			return ServiceUtil.returnFailure(e.getMessage());
		}
		return ServiceUtil.returnSuccess();
	}
	
	public static void delCategaryInfo(GenericDelegator genericDelegator,String id) throws Exception{
        EntityCondition whereCondition = EntityCondition.makeCondition("id", EntityOperator.EQUALS, id);
        genericDelegator.removeByCondition("SvNoteInfo", whereCondition);
	}
	
	public static Map<?,?> savechangedInfo(DispatchContext ctx,Map<?,?> context){
		try{			
		savechangedInfo(ctx.getDelegator(),context);
		}catch(Exception e){
		return 	ServiceUtil.returnFailure(e.getMessage());
		}
		return ServiceUtil.returnSuccess();
	}
	
	public  static void savechangedInfo(GenericDelegator genericDelegator,Map context) throws Exception{
		String id=(String)context.get("id");	

		EntityCondition whereCondition = EntityCondition.makeCondition("id", EntityOperator.EQUALS, id);
        List<GenericValue> list = null;
			list = genericDelegator.findList("SvNoteInfo", whereCondition, null,null,null,false);		
	        for (GenericValue val : list){
	        	val.set("title", (String)(context.get("title")));	
	        	val.set("name", (String)(context.get("name")));		
	        	val.set("coname", (String)(context.get("coname")));
	        	val.set("textData", (String)(context.get("text_date")));
	        	val.set("enName", (String)(context.get("en_name")));
	        	val.set("enConame", (String)(context.get("en_coname")));		
	        	val.set("enTextData", (String)(context.get("en_text_date")));
	    		val.store();
	    		return;
	        }
	}
	public static Map<?,?>  saveAddedRecord(DispatchContext ctx,Map<?,?> context){
		try{			
			saveAddedRecord(ctx.getDelegator(),context);
			}catch(Exception e){
			return 	ServiceUtil.returnFailure(e.getMessage());
			}
			return ServiceUtil.returnSuccess();
		
	}
	
	public static void saveAddedRecord(GenericDelegator genericDelegator,Map context) throws Exception{
			GenericValue gValue = genericDelegator.makeValue("SvNoteInfo");
			String id = genericDelegator.getNextSeqId("SvNoteInfo");
			gValue.set("id", id);				
			gValue.set("idx", id);
			gValue.set("country", (String)(context.get("country")));
			gValue.set("title", (String)(context.get("title")));
			gValue.set("category", (String)(context.get("category")));
			gValue.set("name", (String)(context.get("name")));
			gValue.set("coname", (String)(context.get("coname")));
			gValue.set("textData", (String)(context.get("text_date")));
			gValue.set("enName", (String)(context.get("en_name")));
			gValue.set("enConame", (String)(context.get("en_coname")));
			gValue.set("enTextData", (String)(context.get("en_text_date")));
			gValue.create();
	}
	public static Map<?,?>  saveAddedMonu(DispatchContext ctx,Map<?,?> context){
		try{			
			saveAddedMonu(ctx.getDelegator(),context);
			}catch(Exception e){
			return 	ServiceUtil.returnFailure(e.getMessage());
			}
			return ServiceUtil.returnSuccess();
		
	}
	
	public static void saveAddedMonu(GenericDelegator genericDelegator,Map context) throws Exception{
			GenericValue gValue = genericDelegator.makeValue("SvNoteInfoCategory");
			String id = genericDelegator.getNextSeqId("SvNoteInfoCategory");
			gValue.set("id", id);						
			gValue.set("parentid", (String)(context.get("parentId")));
			gValue.set("country", (String)(context.get("country")));
			gValue.set("name", (String)(context.get("name")));
			gValue.set("images", (String)(context.get("imagines")));
			gValue.set("link", (String)(context.get("link")));
			gValue.set("enName", (String)(context.get("enName")));
			gValue.set("enImages", (String)(context.get("enImagines")));
			gValue.create();
	}	
	
	public static Map<?,?> getEditMenuInfo(DispatchContext ctx,Map<?,?> context){
		String id=(String)context.get("id");
		Map<String,Object> result=null;
		try{
		result=ServiceUtil.returnSuccess();
		result.put("monuInfo", getEditMenuInfo(ctx.getDelegator(),id));
		}catch(Exception e){
			return ServiceUtil.returnFailure(e.getMessage());
		}
		return result;
	}
	
	public static Map<?,?> getEditMenuInfo(GenericDelegator genericDelegator,String id) throws Exception{
		EntityCondition whereCondition = EntityCondition.makeCondition("id", EntityOperator.EQUALS, id);
		Map<String, Object> retmap=null;
        List<GenericValue> list = null;
			list = genericDelegator.findList("SvNoteInfoCategory", whereCondition, null,null,null,false);		
			 retmap=(Map)list.get(0);
				if(retmap.get("country")==null){
					retmap.put("country","");
				}
				if(retmap.get("name")==null){
					retmap.put("name","");
				}
				if(retmap.get("images")==null){
					retmap.put("images","");
				}
				if(retmap.get("link")==null){
					retmap.put("link","");
				}	
				if(retmap.get("enName")==null){
					retmap.put("enName","");
				}
				if(retmap.get("enImages")==null){
					retmap.put("enImages","");
				}
        	return retmap;			
	}	
	
	public static Map<?,?> saveEditmonu(DispatchContext ctx,Map<?,?> context){
		try{			
			saveEditmonu(ctx.getDelegator(),context);
		}catch(Exception e){
		return 	ServiceUtil.returnFailure(e.getMessage());
		}
		return ServiceUtil.returnSuccess();
	}
	
	public  static void saveEditmonu(GenericDelegator genericDelegator,Map context) throws Exception{
		String id=(String)context.get("id");	
		try{
		EntityCondition whereCondition = EntityCondition.makeCondition("id", EntityOperator.EQUALS, id);
        List<GenericValue> list = null;
			list = genericDelegator.findList("SvNoteInfoCategory", whereCondition, null,null,null,false);	
	        for (GenericValue val : list){
	        	val.set("parentid", (String)(context.get("parentId")));	
	        	val.set("country", (String)(context.get("country")));		
	        	val.set("name", (String)(context.get("name")));
	        	val.set("link", (String)(context.get("link")));
	        	val.set("images", (String)(context.get("images")));
	        	val.set("enName", (String)(context.get("enName")));		
	        	val.set("enImages", (String)(context.get("enImages")));
	    		val.store();
	    		return;
	        }
		}catch(Exception e){
			System.out.println("!!!!!!!!!!!!!!!!!!!!!!!exception!!!!!!!"+e.getMessage() );
		}
	}	
}

