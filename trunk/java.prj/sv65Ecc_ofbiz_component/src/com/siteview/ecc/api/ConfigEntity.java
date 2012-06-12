package com.siteview.ecc.api;

import java.util.Date;

import org.ofbiz.entity.GenericEntityException;
import org.ofbiz.entity.GenericValue;

public class ConfigEntity extends EntityBase{
	public static void test()
	{
		try {
			GenericValue val = getDelegator().makeValue("SvLogLinks");
			val.set("datex", "" + new Date().getTime());
			val.set("serverName","test");
			val.set("className", "aaaa\n");
			val.create();
		} catch (GenericEntityException e) {
		}
		
	}
	
}
