package com.siteview.ecc.service.db;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityConditionList;
import org.ofbiz.entity.condition.EntityExpr;
import org.ofbiz.entity.condition.EntityOperator;

public class MonitorDBReader{
	private Map<String, List<String>> data = new HashMap<String, List<String>>();
	public MonitorDBReader(String id) throws Exception
	{
		this(id,GenericDelegator.getGenericDelegator("default"));
	}
	public MonitorDBReader(String id,GenericDelegator delegator) throws Exception
	{
    	ArrayList<EntityExpr> exprs = new ArrayList<EntityExpr>();
    	exprs.add(new EntityExpr("instanceId", EntityOperator.EQUALS, id));
        EntityCondition condition = new EntityConditionList<EntityExpr>(exprs, EntityOperator.AND);
        List<GenericValue> list = delegator.findList("SvMonitorInstanceValue", condition, null,UtilMisc.toList("attrName","idx"),null,false);
        String oldKey = null;
        List<String> values = null;
        for(GenericValue val : list){
        	String key = val.getString("attrName");
        	if (!key.equals(oldKey)){
        		if (values != null){
        			data.put(oldKey, values);
        		}
    			values = new ArrayList<String>();
    			values.add(val.getString("attrValue"));
        		
        	} else {
            	values.add(val.getString("attrValue"));
        	}
        	
        	oldKey = val.getString("attrName");
        }
	}
	
	public List<String> get(String key)
	{
		return data.get(key);
	}
	
}
