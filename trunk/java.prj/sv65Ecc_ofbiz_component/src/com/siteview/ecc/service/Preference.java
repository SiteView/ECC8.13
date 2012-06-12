package com.siteview.ecc.service;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;

import jgl.Array;

import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericEntityException;
import org.ofbiz.entity.GenericValue;

import com.dragonflow.Properties.NumericProperty;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.Preferences;

public class Preference {
	public static void update() throws Exception
	{
		GenericDelegator delegator = GenericDelegator.getGenericDelegator("default");
		List<GenericValue> vals = delegator.findList("SvPreferenceType", null, null,
				null, null, false);
		for (GenericValue val : vals) {
			try {
				String className = val.getString("className");
				if (className == null) continue;
				if (!className.startsWith("com.dragonflow.StandardPreference.")) continue;
				Preferences instance = getInstance(className);
				if (instance == null) continue;
				update(instance,val,className);
			} catch (Exception e) {
			}
		}
	}
	public static void update(Preferences instance,GenericValue val,String className)
	{
		/*
		try {
			val.set("description", getProperty(instance,"description"));
			val.set("title", getProperty(instance,"title"));
			val.set("target", getProperty(instance,"target"));
			val.set("toolName", getProperty(instance,"toolName"));
			val.set("toolDescription", getProperty(instance,"toolDescription"));
			val.set("topazName", getProperty(instance,"topazName"));
			val.set("topazType", getProperty(instance,"topazType"));
			val.set("classType", getProperty(instance,"classType"));
			val.set("applicationType", getProperty(instance,"applicationType"));
			val.store();
		} catch (GenericEntityException e) {
			e.printStackTrace();
		}
		*/
		//if (true)return ;
		Array properties = instance.getProperties();
		Enumeration enumeration = properties.elements();
		while(enumeration.hasMoreElements())
		{
			Object object = enumeration.nextElement();
			if (object instanceof StringProperty)
			{
				StringProperty stringProperty = (StringProperty) object;
				setPropertyValue(stringProperty,className);
			}
			
		}
	}

	private static void setPropertyValue(StringProperty stringProperty,String className)
	{
		try {
			GenericDelegator genericdelegator = GenericDelegator.getGenericDelegator("default");
			GenericValue val = genericdelegator.makeValue("SvPreferenceAttr");
			val.set("className", className);
			val.set("attrName", "" + stringProperty);
			val.set("label", stringProperty.getLabel());
			val.set("description", stringProperty.getDescription());

			
			if (stringProperty instanceof  NumericProperty){
				NumericProperty numericProperty = (NumericProperty)stringProperty;
				val.set("unit", numericProperty.getUnits());
			}

			val.create();
		} catch (GenericEntityException e) {
			e.printStackTrace();
		}
	}	
	public static String getProperty(Preferences preferences,String key)
	{
		Object object = preferences.getClassPropertyByObject(preferences.getClass().getName(),key);
		System.out.println(key + "=" + object);
		if (object instanceof String ) return object == null ? "" : ("" + object);
		return "";
	}
	
	private static Preferences getInstance(String className) throws Exception
	{
		if (className==null) return null;
		for (String instance : getClassNames())
		{
			if (className.equals(instance)) {
				try {
					Class classz = Class.forName(instance);
					return (Preferences)classz.newInstance();
				} catch (Exception e) {
					return null;
				}
			}
		}
		return null;
	}
    public static List<String> getClassNames() throws Exception
	{
		return getMonitorClassNames(GenericDelegator.getGenericDelegator("default"));
	}

	private static List<String> classeNames = null;
	public static List<String> getMonitorClassNames(GenericDelegator delegator)
			throws Exception {
		if (classeNames==null){
			List<GenericValue> vals = delegator.findList("SvPreferenceType", null, null,
					null, null, false);
			List<String> monitors = new ArrayList<String>();
			for (GenericValue val : vals) {
				String className = val.getString("className");
				if (className == null)continue;
				monitors.add(className);
			}
			classeNames = monitors;
		}
		return classeNames;
	}
	

}
