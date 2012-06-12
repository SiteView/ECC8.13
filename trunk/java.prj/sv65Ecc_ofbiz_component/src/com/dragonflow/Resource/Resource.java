/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Resource;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.util.HashMap;

import org.ofbiz.base.util.UtilProperties;

public abstract class Resource
{

    private static java.util.HashMap resourceBundles = new HashMap();
    private static String myBase = "resource";

    public Resource()
    {
    }

    public static String getString(String s, String s1)
    {
        return com.dragonflow.Resource.Resource.getString(s, s1, java.util.Locale.ENGLISH);
    }

    private static String getString(String s, String s1, java.util.Locale locale)
    {
        java.util.ResourceBundle resourcebundle = (java.util.ResourceBundle)resourceBundles.get(com.dragonflow.Resource.Resource.createResourceBundleKey(s, locale));
        if(resourcebundle == null)
        {
            resourcebundle = com.dragonflow.Resource.Resource.loadResourceBundle(s, locale);
        }
        String s2 = null;
        try
        {
            s2 = resourcebundle.getString(s1);
        }
        catch(Exception exception)
        {
            com.dragonflow.Log.LogManager.log("Error", "Resource key " + s1 + "not found returning key");
            s2 = s1;
        }
        return s2;
    }

    protected static String getFormattedString(String s, String s1, Object aobj[])
    {
        String s2 = com.dragonflow.Resource.Resource.getString(s, s1);
        return java.text.MessageFormat.format(s2, aobj);
    }

    private static java.util.ResourceBundle loadResourceBundle(String s, java.util.Locale locale)
    {
    	return UtilProperties.getResourceBundle(getResourceFileName(s), locale);
    	
    	/*
        java.util.ResourceBundle resourcebundle = null;
        try
        {
            resourcebundle = java.util.ResourceBundle.getBundle(com.dragonflow.Resource.Resource.getBase(s), locale);
            resourceBundles.put(com.dragonflow.Resource.Resource.createResourceBundleKey(s, locale), resourcebundle);
        }
        catch(Throwable throwable)
        {
            com.dragonflow.Log.LogManager.log("Error", "ResourceBundle " + s + " not found.");
        }
        return resourcebundle;
        */
    }
    private static String getResourceFileName(String siteview)
    {
        return siteview + "_" + myBase + ".properties";
    }

    private static String getBase(String s)
    {
        return "com/dragonflow/Resource/" + s + "_" + myBase;
    }

    private static String createResourceBundleKey(String s, java.util.Locale locale)
    {
        String s1 = s;
        String s2 = locale.toString();
        if(s2.length() > 0)
        {
            s1 = s1 + "_" + s2;
        } else
        if(locale.getVariant().length() > 0)
        {
            s1 = s1 + "___" + locale.getVariant();
        }
        return s1;
    }

}
