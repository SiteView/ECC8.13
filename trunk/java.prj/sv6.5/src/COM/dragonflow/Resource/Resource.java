/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.Resource;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.util.HashMap;

public abstract class Resource
{

    private static java.util.HashMap resourceBundles = new HashMap();
    private static java.lang.String myBase = "resource";

    public Resource()
    {
    }

    public static java.lang.String getString(java.lang.String s, java.lang.String s1)
    {
        return COM.dragonflow.Resource.Resource.getString(s, s1, java.util.Locale.ENGLISH);
    }

    private static java.lang.String getString(java.lang.String s, java.lang.String s1, java.util.Locale locale)
    {
        java.util.ResourceBundle resourcebundle = (java.util.ResourceBundle)resourceBundles.get(COM.dragonflow.Resource.Resource.createResourceBundleKey(s, locale));
        if(resourcebundle == null)
        {
            resourcebundle = COM.dragonflow.Resource.Resource.loadResourceBundle(s, locale);
        }
        java.lang.String s2 = null;
        try
        {
            s2 = resourcebundle.getString(s1);
        }
        catch(java.lang.Exception exception)
        {
            COM.dragonflow.Log.LogManager.log("Error", "Resource key " + s1 + "not found returning key");
            s2 = s1;
        }
        return s2;
    }

    protected static java.lang.String getFormattedString(java.lang.String s, java.lang.String s1, java.lang.Object aobj[])
    {
        java.lang.String s2 = COM.dragonflow.Resource.Resource.getString(s, s1);
        return java.text.MessageFormat.format(s2, aobj);
    }

    private static java.util.ResourceBundle loadResourceBundle(java.lang.String s, java.util.Locale locale)
    {
        java.util.ResourceBundle resourcebundle = null;
        try
        {
            resourcebundle = java.util.ResourceBundle.getBundle(COM.dragonflow.Resource.Resource.getBase(s), locale);
            resourceBundles.put(COM.dragonflow.Resource.Resource.createResourceBundleKey(s, locale), resourcebundle);
        }
        catch(java.lang.Throwable throwable)
        {
            COM.dragonflow.Log.LogManager.log("Error", "ResourceBundle " + s + " not found.");
        }
        return resourcebundle;
    }

    private static java.lang.String getBase(java.lang.String s)
    {
        return "COM/dragonflow/Resource/" + s + "_" + myBase;
    }

    private static java.lang.String createResourceBundleKey(java.lang.String s, java.util.Locale locale)
    {
        java.lang.String s1 = s;
        java.lang.String s2 = locale.toString();
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
