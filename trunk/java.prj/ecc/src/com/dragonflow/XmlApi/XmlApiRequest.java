/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.XmlApi;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.io.File;
import java.util.HashSet;

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.Api.APISiteView;
import com.dragonflow.SiteViewException.SiteViewOperationalException;

// Referenced classes of package com.dragonflow.XmlApi:
// XmlApiObject, XmlApiResponse

public class XmlApiRequest
{

    private com.dragonflow.Api.APISiteView api;
    public static final int VERBOSE_LEVEL_MINIMUM = 0;
    public static final int VERBOSE_LEVEL_MEDIUM = 1;
    public static final int VERBOSE_LEVEL_ALL = 2;
    public static final java.lang.String API_GET_CURRENT_VERSION_OPERATION = "getCurrentApiVersion";
    static java.lang.Object mutex = new Object();
    protected boolean debug;
    com.dragonflow.XmlApi.XmlApiObject request;
    private static jgl.HashMap apiLookup = new HashMap();
    private static java.util.HashSet detachAllowedOperations = null;
    private static java.lang.Object detachAllowedOperationsSync = new Object();
    private static jgl.Array packages = null;
    private static jgl.Array standardObjects = null;
    private static jgl.Array siteViewObjects = null;

    public XmlApiRequest()
    {
        api = null;
        debug = false;
        request = null;
        request = new XmlApiObject("", null);
        api = new APISiteView();
    }

    public void doRequests()
    {
        java.lang.String s = request.getName();
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject;
        for(java.util.Enumeration enumeration = request.elements(); enumeration.hasMoreElements(); processRequest(s, xmlapiobject))
        {
            xmlapiobject = (com.dragonflow.XmlApi.XmlApiObject)enumeration.nextElement();
        }

        try
        {
            com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            if(detectconfigurationchange.isConfigChanged())
            {
                com.dragonflow.Api.APISiteView _tmp = api;
                com.dragonflow.Api.APISiteView.forceConfigurationRefresh();
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            com.dragonflow.Log.LogManager.log("error", "Unable to refresh SiteView's configuration");
        }
    }

    public void processRequest(java.lang.String s, com.dragonflow.XmlApi.XmlApiObject xmlapiobject)
    {
        java.lang.String s1 = xmlapiobject.getName();
        if(debug && (s1 == null || s1.length() == 0))
        {
            java.lang.System.out.println("documentName=" + s + ", operation=" + s1);
            java.lang.System.out.println(xmlapiobject.toString());
        }
        java.lang.String s2 = "com.dragonflow.XmlApi." + s;
        java.lang.Object aobj[] = new java.lang.Object[1];
        aobj[0] = xmlapiobject;
        try
        {
            java.lang.String s3 = xmlapiobject.getDocumentProperty("controllingHost");
//            com.dragonflow.TopazIntegration.MAManager.validateControllingHost(s3, com.dragonflow.XmlApi.XmlApiRequest.isDetachAllowedOperation(s1));
            java.lang.String s4 = com.dragonflow.SiteView.Platform.getVersion();
            double d = com.dragonflow.Api.APISiteView.getCurrentApiVersion();
            java.lang.String s5 = xmlapiobject.getDocumentProperty("version");
            double d1 = 0.0D;
            try
            {
                d1 = (new Double(s5)).doubleValue();
            }
            catch(java.lang.Exception exception1)
            {
                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_UNSUPPORTED_VERSION, new java.lang.String[] {
                    s4, "Error - client API version \"" + s5 + "\" is not a valid double"
                });
            }
            if(!s1.equals("getCurrentApiVersion") && d != d1)
            {
                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_UNSUPPORTED_VERSION, new java.lang.String[] {
                    s4, s5
                });
            }
            if(com.dragonflow.SiteView.SiteViewGroup.currentSiteView().hasCircularGroups())
            {
                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_CIRCULAR_GROUPS);
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewOperationalException siteviewoperationalexception)
        {
            com.dragonflow.Log.LogManager.log("error", siteviewoperationalexception.getMessage());
            xmlapiobject.setProperty("error", siteviewoperationalexception.getMessage(), false);
            xmlapiobject.setProperty("errortype", "operational", false);
            xmlapiobject.setProperty("errorcode", java.lang.String.valueOf(siteviewoperationalexception.getErrorCode()), false);
            return;
        }
        java.lang.Object obj = com.dragonflow.XmlApi.XmlApiRequest.invokeMethod(s2, s1, aobj);
        if(obj instanceof java.lang.Exception)
        {
            java.lang.Exception exception = (java.lang.Exception)obj;
            java.lang.StringBuffer stringbuffer = new StringBuffer();
            stringbuffer.append("Exception in APIRequest.processRequest()  " + exception.toString());
            stringbuffer.append(",  " + s2 + "." + s1 + "(");
            for(int i = 0; i < aobj.length; i++)
            {
                stringbuffer.append((i <= 0 ? "" : ", ") + aobj[i].getClass().getName());
            }

            stringbuffer.append(")");
            java.lang.reflect.Method amethod[] = com.dragonflow.XmlApi.XmlApiRequest.listAvailableMethods(s2, aobj);
            for(int j = 0; j < amethod.length; j++)
            {
                stringbuffer.append(",  " + amethod[j].getName() + "(");
                java.lang.Class aclass[] = amethod[j].getParameterTypes();
                for(int k = 0; k < aclass.length; k++)
                {
                    stringbuffer.append((k <= 0 ? "" : ", ") + aclass[k].getName());
                }

                stringbuffer.append(")");
            }

            com.dragonflow.Log.LogManager.log("error", stringbuffer.toString());
            java.lang.System.out.println(stringbuffer.toString());
            xmlapiobject.setProperty("error", exception.toString(), false);
        }
    }

    private static boolean isDetachAllowedOperation(java.lang.String s)
    {
        if(detachAllowedOperations == null)
        {
            synchronized(detachAllowedOperationsSync)
            {
                if(detachAllowedOperations == null)
                {
                    detachAllowedOperations = new HashSet();
                    detachAllowedOperations.add("controlSiteView");
                    detachAllowedOperations.add("getSiteViewInfo");
                    detachAllowedOperations.add("isServerRegistered");
                    detachAllowedOperations.add("isUIControled");
                }
            }
        }
        return detachAllowedOperations.contains(s);
    }

    public java.lang.String toString()
    {
        return request.toString();
    }

    public java.lang.Object getRequest()
    {
        return request;
    }

    public java.lang.Object getResponse()
    {
        return request;
    }

    public java.lang.Object getAPIRequest()
    {
        return request;
    }

    public void setAPIRequest(com.dragonflow.XmlApi.XmlApiObject xmlapiobject)
    {
        request = xmlapiobject;
    }

    public static java.lang.Object invokeMethod(java.lang.String s, java.lang.String s1, java.lang.Object aobj[])
    {
        java.lang.Object obj = null;
        Object obj1 = null;
        Object obj3 = null;
        Object obj4 = null;
        try
        {
            java.lang.Object obj2 = apiLookup.get(s);
            if(obj2 == null)
            {
                synchronized(mutex)
                {
                    obj2 = apiLookup.get(s);
                    if(obj2 == null)
                    {
                        java.lang.Class class1 = java.lang.Class.forName(s);
                        obj2 = class1.newInstance();
                        apiLookup.put(s, obj2);
                    }
                }
            }
            java.lang.Class aclass[] = new java.lang.Class[aobj.length];
            for(int i = 0; i < aobj.length; i++)
            {
                aclass[i] = aobj[i].getClass();
            }

            java.lang.reflect.Method method = obj2.getClass().getMethod(s1, aclass);
            obj = method.invoke(obj2, aobj);
        }
        catch(java.lang.Exception exception)
        {
            com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
            com.dragonflow.SiteViewException.SiteViewOperationalException siteviewoperationalexception = new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                s, s1
            }, 0L, exception.getMessage());
            xmlapiresponse.setErrorResponse(siteviewoperationalexception);
            obj = xmlapiresponse;
        }
        return obj;
    }

    private static boolean parmsMatch(java.lang.Class aclass[], java.lang.Object aobj[])
    {
        if(aclass.length != aobj.length)
        {
            return false;
        }
        for(int i = 0; i < aclass.length; i++)
        {
            if(aclass[i] != aobj[i].getClass())
            {
                return false;
            }
        }

        return true;
    }

    public static java.lang.reflect.Method[] listAvailableMethods(java.lang.String s, java.lang.Object aobj[])
    {
        jgl.Array array = new Array();
        try
        {
            java.lang.Class class1 = java.lang.Class.forName(s);
            java.lang.reflect.Method amethod1[] = class1.getMethods();
            for(int j = 0; j < amethod1.length; j++)
            {
                java.lang.Class aclass[] = amethod1[j].getParameterTypes();
                if(aobj == null || com.dragonflow.XmlApi.XmlApiRequest.parmsMatch(aclass, aobj))
                {
                    array.add(amethod1[j]);
                }
            }

        }
        catch(java.lang.Exception exception) { }
        java.lang.reflect.Method amethod[] = new java.lang.reflect.Method[array.size()];
        for(int i = 0; i < array.size(); i++)
        {
            amethod[i] = (java.lang.reflect.Method)array.at(i);
        }

        return amethod;
    }

    public static jgl.Array getPackages()
    {
        if(packages == null)
        {
            packages = new Array();
            java.io.File file = new File(com.dragonflow.SiteView.Platform.getRoot() + "/classes/com/dragonflow");
            java.lang.String as[] = file.list();
            for(int i = 0; i < as.length; i++)
            {
                java.io.File file1 = new File(com.dragonflow.SiteView.Platform.getRoot() + "/classes/com/dragonflow/" + as[i]);
                if(file1.isDirectory())
                {
                    packages.add(as[i]);
                }
            }

        }
        return packages;
    }

    public static jgl.Array getStandardObjects()
    {
        if(standardObjects == null)
        {
            standardObjects = new Array();
            try
            {
                java.io.File file = new File(com.dragonflow.SiteView.Platform.getRoot() + "/classes/com/dragonflow");
                java.lang.String as[] = file.list();
                for(int i = 0; i < as.length; i++)
                {
                    if(as[i].startsWith("Standard"))
                    {
                        java.lang.String as1[] = new java.lang.String[3];
                        as1[0] = as[i].substring(8);
                        as1[1] = "true";
                        as1[2] = "";
                        standardObjects.add(as1);
                    }
                }

            }
            catch(java.lang.Exception exception) { }
        }
        return standardObjects;
    }

    public static jgl.Array getSiteViewObjects()
    {
        return com.dragonflow.XmlApi.XmlApiRequest.getStandardObjects();
    }

    public static jgl.Array getObjects(java.lang.String s)
    {
        jgl.Array array = new Array();
        try
        {
            java.lang.Class class1 = java.lang.Class.forName("com.dragonflow.SiteView." + s);
            java.io.File file = new File(com.dragonflow.SiteView.Platform.getRoot() + "/classes/com/dragonflow/Standard" + s);
            java.lang.String as[] = file.list();
            for(int i = 0; i < as.length; i++)
            {
                if(as[i].endsWith(".class"))
                {
                    int j = as[i].lastIndexOf(".class");
                    java.lang.String s1 = as[i].substring(0, j);
                    try
                    {
                        java.lang.Class class2 = java.lang.Class.forName("com.dragonflow.Standard" + s + "." + s1);
                        if(class2.getSuperclass() == class1)
                        {
                            try
                            {
                                class2.getField("is" + s + "Object");
                                array.add(s1);
                            }
                            catch(java.lang.Exception exception1)
                            {
                                com.dragonflow.Log.LogManager.log("Error", "XmlApiRequest.getObjects(" + s + ") failed with exception '" + exception1.toString() + "' while adding class '" + as[i] + "' to myObjects array");
                            }
                        }
                    }
                    catch(java.lang.Throwable throwable)
                    {
                        com.dragonflow.Log.LogManager.log("Error", "XmlApiRequest.getObjects(" + s + ") Standard directory handler failed with exception '" + throwable.toString() + "' while processing file '" + as[i] + "'");
                    }
                }
            }

        }
        catch(java.lang.Exception exception) { }
        return array;
    }

}
