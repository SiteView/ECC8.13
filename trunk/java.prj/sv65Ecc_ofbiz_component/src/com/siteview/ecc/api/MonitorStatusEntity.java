package com.siteview.ecc.api;

import java.util.List;

import jgl.HashMap;

import org.ofbiz.entity.GenericValue;


public class MonitorStatusEntity extends EntityBase{
	private static HashMap statusMapping = null;
	
	public static HashMap getMapping()
	{
		if (statusMapping == null){
			statusMapping = new HashMap();
			try {
				for (GenericValue val : getAllStatus())
				{
					try {
						statusMapping.put(val.getString("id"), val.getString("status"));
					} catch (Exception e) {
					}
				}
			} catch (Exception e) {
			}
		}
		return statusMapping;
	}
	private static List<GenericValue> getAllStatus() throws Exception
	{
        return getDelegator().findList("SvMonitorStatus", null, null,null,null,false);
		
	}
}
