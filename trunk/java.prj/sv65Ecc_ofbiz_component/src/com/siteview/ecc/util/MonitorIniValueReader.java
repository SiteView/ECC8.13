package com.siteview.ecc.util;

import java.util.List;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityOperator;

public class MonitorIniValueReader {
	public static final String DESCRIPTION = "description";
	public static final String LABEL = "label";
	public static final String UNIT = "unit";
	public static final String TITLE = "title";
	public static String getCommonValue(String attrName,String valueName)
	{
		String val = getCommonValueWithNull(attrName,valueName);
		if (val == null) return "";
		return val;
	}
	public static String getCommonValueWithNull(String attrName,String valueName)
	{
		if (attrName==null) return null;
		if (valueName==null) return null;
        List<GenericValue> values = null;
		try {
			values = getMonitorCommonAttrs(attrName);
		} catch (Exception e) {
			return null;
		}
        for (GenericValue val : values )
        {
        	if (LABEL.equals(valueName)){
        		return val.getString(LABEL);
        	}else if (DESCRIPTION.equals(valueName)){
        		return val.getString(DESCRIPTION);
        	}else if (UNIT.equals(valueName)){
        		return val.getString(UNIT);
        	}
        }
		return null;
	}	
	public static String getValue(String absClassName,String attrName,String valueName)
	{
		String val = getValueWithNull(absClassName,attrName,valueName);
		if (val == null) return "";
		return val;
	}
	public static String getValueWithNull(String absClassName,String attrName,String valueName)
	{
		if (absClassName==null) return null;
		if (attrName==null) return null;
		if (valueName==null) return null;
        List<GenericValue> values = null;
		try {
			values = getMonitorAttrs(absClassName,attrName);
		} catch (Exception e) {
			return null;
		}
        for (GenericValue val : values )
        {
        	if (LABEL.equals(valueName)){
        		return val.getString(LABEL);
        	}else if (DESCRIPTION.equals(valueName)){
        		return val.getString(DESCRIPTION);
        	}else if (UNIT.equals(valueName)){
        		return val.getString(UNIT);
        	}
        }
		return null;
	}

	
	private static List<GenericValue> getMonitorCommonAttrs(String attrName) throws Exception
	{
        EntityCondition condition = EntityCondition.makeCondition("attrName", EntityOperator.EQUALS, attrName);		
        	
        return getDelegator().findList("SvMonitorCommonAttr", condition, null,null,null,false);
	}

	private static List<GenericValue> getMonitorAttrs(String absClassName,String attrName) throws Exception
	{
        EntityCondition condition = EntityCondition.makeCondition(
        		UtilMisc.toList(
        				EntityCondition.makeCondition("className", EntityOperator.EQUALS, absClassName),		
        				EntityCondition.makeCondition("attrName", EntityOperator.EQUALS, attrName)		
        		),
        		EntityOperator.AND
        		);
        	
        return getDelegator().findList("SvMonitorAttr", condition, null,null,null,false);
	}
	
	private static GenericDelegator localdelegator = null;
	private static GenericDelegator getDelegator()
	{
		if (localdelegator == null) localdelegator = GenericDelegator.getGenericDelegator("default");
		return localdelegator;
	}
	
}
