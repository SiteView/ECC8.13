package com.siteview.ecc.api;

import java.util.List;

import jgl.HashMap;

import org.ofbiz.entity.GenericValue;


public class MonitorStatusHelpEntity extends EntityBase{
	private static HashMap statusHelpMapping = null;
	
	public static HashMap getMapping()
	{
		if (statusHelpMapping == null){
			statusHelpMapping = new HashMap();
			try {
				for (GenericValue val : getAllStatusHelp())
				{
					try {
						statusHelpMapping.put(val.getString("id"), val.getString("message"));
					} catch (Exception e) {
					}
				}
			} catch (Exception e) {
			}
		}
		return statusHelpMapping;
	}
	private static List<GenericValue> getAllStatusHelp() throws Exception
	{
        return getDelegator().findList("SvMonitorStatusHelp", null, null,null,null,false);
		
	}
}
