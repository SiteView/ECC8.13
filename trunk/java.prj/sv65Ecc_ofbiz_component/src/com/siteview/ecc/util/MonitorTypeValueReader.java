package com.siteview.ecc.util;

import java.util.ArrayList;
import java.util.List;

import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityConditionList;
import org.ofbiz.entity.condition.EntityExpr;
import org.ofbiz.entity.condition.EntityOperator;

public class MonitorTypeValueReader {
	public static final String DESCRIPTION = "description";
	public static final String TITLE = "title";	
	public static final String TARGET = "target";
	public static final String TOOLNAME = "toolName";
	public static final String TOOLDESCRIPTION = "toolDescription";
	public static final String TOPAZNAME = "topazName";
	public static final String TOPAZTYPE = "topazType";
	public static final String CLASSTYPE = "classType";
	public static final String APPLICATIONTYPE = "applicationType";
	public static final String TOOLPAGEDISABLE = "toolPageDisable";
	public static final String LOADABLE = "loadable";
	public static final String DEFAULTFREQUENCY = "defaultFrequency";
	public static String getValue(String absClassName,String valueName)
	{
		String val = getValueWithNull(absClassName,valueName);
		if (val == null) return "";
		return val;
	}
	public static String getValueWithNull(String absClassName,String valueName)
	{
		if (absClassName==null) return null;
		if (valueName==null) return null;
        List<GenericValue> values = null;
		try {
			values = getMonitorAttrs(absClassName);
		} catch (Exception e) {
			return null;
		}
        for (GenericValue val : values )
        {
        	if (DESCRIPTION.equals(valueName)){
        		return val.getString(DESCRIPTION);
        	}else if (TITLE.equals(valueName)){
        		return val.getString(TITLE);
        	}else if (TARGET.equals(valueName)){
        		return val.getString(TARGET);
        	}else if (TOOLNAME.equals(valueName)){
        		return val.getString(TOOLNAME);
        	}else if (TOOLDESCRIPTION.equals(valueName)){
        		return val.getString(TOOLDESCRIPTION);
        	}else if (TOPAZNAME.equals(valueName)){
        		return val.getString(TOPAZNAME);
        	}else if (TOPAZTYPE.equals(valueName)){
        		return val.getString(TOPAZTYPE);
        	}else if (CLASSTYPE.equals(valueName)){
        		return val.getString(CLASSTYPE);
        	}else if (APPLICATIONTYPE.equals(valueName)){
        		return val.getString(APPLICATIONTYPE);
        	}else if (TOOLPAGEDISABLE.equals(valueName)){
        		return val.getString(TOOLPAGEDISABLE);
        	}else if (LOADABLE.equals(valueName)){
        		return val.getString(LOADABLE);
        	}else if (DEFAULTFREQUENCY.equals(valueName)){
        		return val.getString(DEFAULTFREQUENCY);
        	}
        }
		return null;
	}

	
	@SuppressWarnings("deprecation")
	private static List<GenericValue> getMonitorAttrs(String absClassName) throws Exception
	{
    	ArrayList<EntityExpr> exprs = new ArrayList<EntityExpr>();
     	exprs.add(new EntityExpr("className", EntityOperator.EQUALS, absClassName));
     	//exprs.add(new EntityExpr("attrName", EntityOperator.EQUALS, attrName));
        EntityCondition condition = new EntityConditionList<EntityExpr>(exprs, EntityOperator.AND);
        return getDelegator().findList("SvMonitorType", condition, null,null,null,false);
	}
	
	private static GenericDelegator localdelegator = null;
	private static GenericDelegator getDelegator()
	{
		if (localdelegator == null) localdelegator = GenericDelegator.getGenericDelegator("default");
		return localdelegator;
	}
	
}
