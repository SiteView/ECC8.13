package com.siteview.ecc.api;

import org.ofbiz.entity.GenericDelegator;

public abstract class EntityBase {
	private static GenericDelegator localdelegator = null;
	public static GenericDelegator getDelegator()
	{
		if (localdelegator == null) localdelegator = GenericDelegator.getGenericDelegator("default");
		return localdelegator;
	}

}
