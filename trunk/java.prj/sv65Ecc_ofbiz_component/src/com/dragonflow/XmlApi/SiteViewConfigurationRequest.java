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

import java.util.Vector;

import jgl.Array;
import jgl.HashMap;

// Referenced classes of package com.dragonflow.XmlApi:
// XmlApiObject, XmlApiResponse, XmlApiRequest

public class SiteViewConfigurationRequest {

    public static final int VERBOSE_SHOW_ALWAYS = 0;

    public static final int VERBOSE_SHOW_ON_MEDIUM_DETAIL = 1;

    public static final int VERBOSE_SHOW_ON_MAX_DETAIL = 2;

    public static final String CLASS_NAME_PROPERTY = "class";

    public static final String CLASS_TYPE_PROPERTY = "type";

    public static final String PACKAGE_BASE = "com.dragonflow.";

    public static final String XML_API_PACKAGE = "com.dragonflow.XmlApi.XmlApi";

    public static final String API_PACKAGE = "com.dragonflow.Api.";

    public static final String SITEVIEW_PACKAGE = "com.dragonflow.SiteView";

    public static final String STANDARD_PACKAGE = "com.dragonflow.Standard";

    public static boolean debug = true;

    public SiteViewConfigurationRequest() {
    }

    public void add(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        Object obj = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("runMonitor");
            String s1 = xmlapiobject.getProperty("runTimeout");
            String s2 = xmlapiobject.getProperty("testPreference");
            jgl.Array array = new Array();
            jgl.Array array1 = new Array();
            jgl.Array array2 = new Array();
            String s3 = xmlapiobject.getProperty("type");
            Object aobj[] = new Object[4];
            java.util.Enumeration enumeration = xmlapiobject.elements();
            while (enumeration.hasMoreElements()) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                String s4 = xmlapiobject1.getProperty("name");
                String s5 = xmlapiobject1.getProperty("subtype");
                String s6 = xmlapiobject1.getProperty("ownerid");
                jgl.HashMap hashmap1 = null;
                String s8 = xmlapiobject1.getProperty("id");
                if (s8 != null && s8.length() > 0) {
                    s6 = s6 + " " + s8;
                }
                if (s6 != null && s6.length() > 0) {
                    array2.add(s6);
                } else {
                    array2.add("");
                }
                if (s3.equals("Group")) {
                    array1.add(s4);
                } else {
                    array1.add(s5);
                }
                hashmap1 = new HashMap();
                for (java.util.Enumeration enumeration2 = xmlapiobject1.elements(); enumeration2.hasMoreElements();) {
                    com.dragonflow.XmlApi.XmlApiObject xmlapiobject3 = (com.dragonflow.XmlApi.XmlApiObject) enumeration2.nextElement();
                    jgl.HashMap hashmap3 = xmlapiobject3.getProperties();
                    if (s != null && s.length() > 0) {
                        hashmap3.put("runMonitor", s);
                    }
                    if (s1 != null && s1.length() > 0) {
                        hashmap3.put("runTimeout", s1);
                    }
                    if (s2 != null && s2.length() > 0) {
                        hashmap3.put("testPreference", s2);
                    }
                    java.util.Enumeration enumeration3 = hashmap3.keys();
                    while (enumeration3.hasMoreElements()) {
                        String s9 = (String) enumeration3.nextElement();
                        if (!s9.equals("_verify")) {
                            hashmap1.put(s9, hashmap3.get(s9));
                        }
                    }
                }

                array.add(hashmap1);
            } 
            
            aobj[0] = array1;
            aobj[1] = array2;
            aobj[2] = array;
            aobj[3] = s3;
            com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s3, "add", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            enumeration = xmlapiobject.elements();
            for (int i = 0; enumeration.hasMoreElements(); i ++) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                if (!xmlapiresponse.hasErrors() && vector != null) {
                    String s7 = (String) array1.at(i);
                    if (s7 != null && s7.length() > 0) {
                        xmlapiobject1.setProperty("name", s7, false);
                    }
                    jgl.HashMap hashmap2 = (jgl.HashMap) vector.get(i);
                    java.util.Enumeration enumeration1 = xmlapiobject1.elements();
                    com.dragonflow.XmlApi.XmlApiObject xmlapiobject2 = (com.dragonflow.XmlApi.XmlApiObject) enumeration1.nextElement();
                    xmlapiobject2.setProperties(hashmap2, false);
                    if (hashmap2.get("_id") != null) {
                        xmlapiobject1.setProperty("createid", (String) hashmap2.get("_id"), false);
                    }
                }
            }

        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
    }

    public void update(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        Object obj = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            jgl.Array array = new Array();
            jgl.Array array1 = new Array();
            jgl.Array array2 = new Array();
            jgl.Array array3 = new Array();
            jgl.Array array4 = new Array();
            Object obj1 = null;
            String s = xmlapiobject.getProperty("type");
            java.util.Enumeration enumeration = xmlapiobject.elements();
            while (enumeration.hasMoreElements()) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                String s1 = xmlapiobject1.getProperty("id");
                if (s1 != null && s1.length() > 0) {
                    array.add(s1);
                } else {
                    array1.add("");
                }
                String s2 = xmlapiobject1.getProperty("ownerid");
                if (s2 != null && s2.length() > 0) {
                    array1.add(s2);
                } else {
                    array1.add("");
                }
                String s3 = xmlapiobject1.getProperty("attributeId");
                if (s3 != null && s3.length() > 0) {
                    array3.add(s3);
                } else {
                    array3.add("");
                }
                String s4 = xmlapiobject1.getProperty("attributeValue");
                if (s4 != null && s4.length() > 0) {
                    array4.add(s4);
                } else {
                    array4.add("");
                }
                jgl.HashMap hashmap1 = new HashMap();
                for (java.util.Enumeration enumeration1 = xmlapiobject1.elements(); enumeration1.hasMoreElements();) {
                    com.dragonflow.XmlApi.XmlApiObject xmlapiobject2 = (com.dragonflow.XmlApi.XmlApiObject) enumeration1.nextElement();
                    jgl.HashMap hashmap3 = xmlapiobject2.getProperties();
                    xmlapiobject2.setProperties(hashmap3, false);
                    java.util.Enumeration enumeration3 = hashmap3.keys();
                    while (enumeration3.hasMoreElements()) {
                        String s5 = (String) enumeration3.nextElement();
                        if (!s5.equals("_verify")) {
                            hashmap1.put(s5, hashmap3.get(s5));
                        }
                    }
                }

                array2.add(hashmap1);
            } 
            
            Object aobj[] = new Object[5];
            aobj[0] = array;
            aobj[1] = array1;
            aobj[2] = array2;
            aobj[3] = array3;
            aobj[4] = array4;
            com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "update", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            enumeration = xmlapiobject.elements();
            for (int i = 0; enumeration.hasMoreElements(); i ++) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                if (!xmlapiresponse.hasErrors() && vector != null) {
                    jgl.HashMap hashmap2 = (jgl.HashMap) vector.get(i);
                    java.util.Enumeration enumeration2 = xmlapiobject1.elements();
                    com.dragonflow.XmlApi.XmlApiObject xmlapiobject3 = null;
                    if (enumeration2.hasMoreElements()) {
                        xmlapiobject3 = (com.dragonflow.XmlApi.XmlApiObject) enumeration2.nextElement();
                        xmlapiobject3.setProperties(hashmap2, false);
                    } else {
                        xmlapiobject3 = new XmlApiObject("object", new HashMap());
                    }
                }
            }

        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
    }

    public void delete(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        Object obj = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            jgl.Array array = new Array();
            jgl.Array array1 = new Array();
            jgl.Array array2 = new Array();
            jgl.Array array3 = new Array();
            String s = xmlapiobject.getProperty("type");
            for (java.util.Enumeration enumeration = xmlapiobject.elements(); enumeration.hasMoreElements(); array1.add(xmlapiobject1.getProperty("ownerid"))) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                array.add(xmlapiobject1.getProperty("id"));
            }

            String s1 = xmlapiobject1.getProperty("attributeId");
            if (s1 != null && s1.length() > 0) {
                array2.add(s1);
            } else {
                array2.add("");
            }
            String s2 = xmlapiobject1.getProperty("attributeValue");
            if (s2 != null && s2.length() > 0) {
                array3.add(s2);
            } else {
                array3.add("");
            }
            Object aobj[] = new Object[4];
            aobj[0] = array;
            aobj[1] = array1;
            aobj[2] = array2;
            aobj[3] = array3;
            com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "delete", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            java.util.Enumeration enumeration1 = xmlapiobject.elements();
            for (int i = 0; enumeration1.hasMoreElements(); i ++) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration1.nextElement();
                if (!xmlapiresponse.hasErrors() && vector != null) {
                    String as[] = (String[]) vector.get(i);
                    String s3 = as[0];
                    if (s3 != null && s3.length() > 0) {
                        xmlapiobject1.setProperty("id", s3, false);
                    }
                    String s4 = as[1];
                    if (s4 != null && s4.length() > 0) {
                        xmlapiobject1.setProperty("ownerid", s4, false);
                    }
                }
            }

        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
    }

    public void copy(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        Object obj = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("type");
            java.util.Enumeration enumeration = xmlapiobject.elements();
            xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
            String s1 = xmlapiobject1.getProperty("id");
            String s2 = xmlapiobject1.getProperty("ownerid");
            String s3 = xmlapiobject1.getProperty("destid");
            Object aobj[] = new Object[3];
            aobj[0] = s1;
            aobj[1] = s2;
            aobj[2] = s3;
            com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "copy", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            enumeration = xmlapiobject.elements();
            xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
            if (!xmlapiresponse.hasErrors() && vector != null) {
                jgl.HashMap hashmap1 = (jgl.HashMap) vector.get(0);
                xmlapiobject1.add("objectProperty", hashmap1, false);
                if (hashmap1.get("_id") != null) {
                    xmlapiobject1.setProperty("createid", (String) hashmap1.get("_id"), false);
                }
            }
        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
    }

    public Object getClassPropertiesDetails(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("type");
            java.util.Enumeration enumeration = xmlapiobject.elements();
            xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
            jgl.HashMap hashmap1 = xmlapiobject1.getProperties();
            String s1 = (String) hashmap1.get("subtype");
            if (s1.length() > 0) {
                hashmap1.remove("subtype");
            }
            xmlapiobject1.setProperties(hashmap1, false);
            Object aobj[] = new Object[3];
            aobj[0] = s1;
            aobj[1] = hashmap1;
            aobj[2] = getOperationObject(xmlapiobject1.getProperty("operation"));
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "getClassPropertiesDetails", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                for (int i = 0; i < vector.size(); i ++) {
                    jgl.HashMap hashmap2 = (jgl.HashMap) vector.elementAt(i);
                    xmlapiobject1.add("objectProperty", hashmap2, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getClassPropertyDetails(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("type");
            java.util.Enumeration enumeration = xmlapiobject.elements();
            xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
            jgl.HashMap hashmap1 = xmlapiobject1.getProperties();
            String s1 = (String) hashmap1.get("name");
            hashmap1.remove("name");
            String s2 = (String) hashmap1.get("subtype");
            if (s2.length() > 0) {
                hashmap1.remove("subtype");
            }
            xmlapiobject1.setProperties(hashmap1, false);
            Object aobj[] = new Object[3];
            aobj[0] = s1;
            aobj[1] = s2;
            aobj[2] = hashmap1;
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "getClassPropertyDetails", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                for (int i = 0; i < vector.size(); i ++) {
                    jgl.HashMap hashmap2 = (jgl.HashMap) vector.elementAt(i);
                    xmlapiobject1.add("objectProperty", hashmap2, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getClassPropertyScalars(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("type");
            java.util.Enumeration enumeration = xmlapiobject.elements();
            xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
            jgl.HashMap hashmap1 = xmlapiobject1.getProperties();
            String s1 = (String) hashmap1.get("name");
            hashmap1.remove("name");
            String s2 = (String) hashmap1.get("subtype");
            if (s2.length() > 0) {
                hashmap1.remove("subtype");
            }
            xmlapiobject1.setProperties(hashmap1, false);
            Object aobj[] = new Object[3];
            aobj[0] = s1;
            aobj[1] = s2;
            aobj[2] = hashmap1;
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "getClassPropertyScalars", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                jgl.HashMap hashmap2 = new HashMap();
                hashmap2.put("name", vector.get(0));
                xmlapiobject1.setProperties(hashmap2, false);
                String as[] = (String[]) vector.get(1);
                String as1[] = (String[]) vector.get(2);
                for (int i = 0; i < as.length; i ++) {
                    jgl.HashMap hashmap3 = new HashMap();
                    hashmap3.add("listItem", as[i]);
                    hashmap3.add("listItemName", as1[i]);
                    xmlapiobject1.add("objectProperty", hashmap3, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getInstancePropertyDetails(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("type");
            java.util.Enumeration enumeration = xmlapiobject.elements();
            xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
            jgl.HashMap hashmap1 = xmlapiobject1.getProperties();
            String s1 = (String) hashmap1.get("name");
            hashmap1.remove("name");
            String s2 = (String) hashmap1.get("id");
            if (s2.length() > 0) {
                hashmap1.remove("id");
            }
            String s3 = (String) hashmap1.get("ownerid");
            if (s3.length() > 0) {
                hashmap1.remove("ownerid");
            }
            xmlapiobject1.setProperties(hashmap1, false);
            Object aobj[] = new Object[4];
            aobj[0] = s1;
            aobj[1] = s2;
            aobj[2] = s3;
            aobj[3] = hashmap1;
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "getInstancePropertyDetails", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                for (int i = 0; i < vector.size(); i ++) {
                    jgl.HashMap hashmap2 = (jgl.HashMap) vector.elementAt(i);
                    xmlapiobject1.add("objectProperty", hashmap2, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getInstancePropertyScalars(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("type");
            java.util.Enumeration enumeration = xmlapiobject.elements();
            xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
            jgl.HashMap hashmap1 = xmlapiobject1.getProperties();
            String s1 = (String) hashmap1.get("name");
            hashmap1.remove("name");
            String s2 = (String) hashmap1.get("id");
            if (s2.length() > 0) {
                hashmap1.remove("id");
            }
            String s3 = (String) hashmap1.get("ownerid");
            if (s3.length() > 0) {
                hashmap1.remove("ownerid");
            }
            xmlapiobject1.setProperties(hashmap1, false);
            Object aobj[] = new Object[4];
            aobj[0] = s1;
            aobj[1] = s2;
            aobj[2] = s3;
            aobj[3] = hashmap1;
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "getInstancePropertyScalars", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                jgl.HashMap hashmap2 = new HashMap();
                hashmap2.put("name", vector.get(0));
                xmlapiobject1.setProperties(hashmap2, false);
                String as[] = (String[]) vector.get(1);
                String as1[] = (String[]) vector.get(2);
                for (int i = 0; i < as.length; i ++) {
                    jgl.HashMap hashmap3 = new HashMap();
                    hashmap3.add("listItem", as[i]);
                    hashmap3.add("listItemName", as1[i]);
                    xmlapiobject1.add("objectProperty", hashmap3, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getInstances(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        Object obj = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            boolean flag = false;
            java.util.Enumeration enumeration = xmlapiobject.elements();
            if (!enumeration.hasMoreElements()) {
                com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = xmlapiobject;
                flag = true;
            }
            while (enumeration.hasMoreElements()) {
                String s = xmlapiobject.getProperty("type");
                String s1 = xmlapiobject.getProperty("id");
                String s2 = xmlapiobject.getProperty("ownerid");
                if (s2 == null || s2.length() == 0) {
                    s2 = s1;
                    s1 = "";
                }
                Object aobj[] = new Object[5];
                aobj[0] = s2;
                aobj[1] = s1;
                aobj[2] = xmlapiobject.getProperty("attributeId");
                aobj[3] = xmlapiobject.getProperty("attributeValue");
                aobj[4] = getOperationObject(xmlapiobject.getProperty("operation"));
                xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "getInstances", aobj);
                java.util.Vector vector = xmlapiresponse.getReturnVector();
                handleResponse(xmlapiresponse, xmlapiobject, vector);
                if (!xmlapiresponse.hasErrors()) {
                    for (int i = 0; i < vector.size(); i ++) {
                        jgl.HashMap hashmap1 = new HashMap();
                        if (s1.length() > 0) {
                            hashmap1.put("id", s1);
                        }
                        com.dragonflow.XmlApi.XmlApiObject xmlapiobject2 = xmlapiobject.add("object", hashmap1, false);
                        xmlapiobject2.add("objectProperty", (jgl.HashMap) vector.get(i), false);
                    }

                }
            if (flag) {
                break;
            }
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getInstanceProperties(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("type");
            String s1 = xmlapiobject.getProperty("id");
            Object aobj[] = new Object[5];
            aobj[0] = s1;
            aobj[1] = xmlapiobject.getProperty("ownerid");
            aobj[2] = xmlapiobject.getProperty("attributeId");
            aobj[3] = xmlapiobject.getProperty("attributeValue");
            aobj[4] = getOperationObject(xmlapiobject.getProperty("operation"));
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "getInstanceProperties", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                for (int i = 0; i < vector.size(); i ++) {
                    jgl.HashMap hashmap1 = new HashMap();
                    if (s1.length() > 0) {
                        hashmap1.put("id", s1);
                    }
                    xmlapiobject1 = xmlapiobject.add("object", hashmap1, false);
                    xmlapiobject1.add("objectProperty", (jgl.HashMap) vector.get(i), false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getInstanceProperty(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("type");
            String s1 = xmlapiobject.getProperty("name");
            String s2 = xmlapiobject.getProperty("id");
            String s3 = xmlapiobject.getProperty("ownerid");
            String s4 = xmlapiobject.getProperty("ownerparentid");
            Object aobj[] = new Object[5];
            aobj[0] = s1;
            aobj[1] = s2;
            aobj[2] = s3;
            aobj[3] = s4;
            aobj[4] = getOperationObject(xmlapiobject.getProperty("operation"));
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "getInstanceProperty", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                for (int i = 0; i < vector.size(); i ++) {
                    jgl.HashMap hashmap1 = new HashMap();
                    hashmap1.put("id", s2);
                    if (s3.length() > 0) {
                        hashmap1.put("ownerid", s3);
                    }
                    if (s4.length() > 0) {
                        hashmap1.put("ownerparentid", s4);
                    }
                    xmlapiobject1 = xmlapiobject.add("object", hashmap1, false);
                    xmlapiobject1.add("objectProperty", (jgl.HashMap) vector.get(i), false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getCount(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            boolean flag = false;
            java.util.Enumeration enumeration = xmlapiobject.elements();
            if (!enumeration.hasMoreElements()) {
                xmlapiobject1 = xmlapiobject;
                flag = true;
            }
            while (enumeration.hasMoreElements()) {
                if (!flag) {
                    xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                }
                String s = xmlapiobject.getProperty("type");
                Object aobj[] = new Object[1];
                String s1 = "";
                s1 = xmlapiobject1.getProperty("name");
                if (s1 == null || s1.equals("")) {
                    aobj[0] = s;
                } else {
                    aobj[0] = s1;
                }
                xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "getCount", aobj);
                java.util.Vector vector = xmlapiresponse.getReturnVector();
                handleResponse(xmlapiresponse, xmlapiobject, vector);
                if (!xmlapiresponse.hasErrors()) {
                    Long long1 = (Long) vector.elementAt(0);
                    jgl.HashMap hashmap1 = new HashMap();
                    hashmap1.put("count", long1.toString());
                    xmlapiobject1.add("object", hashmap1, false);
                }
            if (flag) {
                break;
            }
            }
        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object enableRealTimeStatusInformation(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[6];
            aobj[0] = xmlapiobject.getProperty("respondHostname");
            aobj[1] = xmlapiobject.getProperty("respondPort");
            aobj[2] = xmlapiobject.getProperty("hostname");
            aobj[3] = xmlapiobject.getProperty("port");
            aobj[4] = xmlapiobject.getProperty("heartbeatInterval");
            aobj[5] = xmlapiobject.getProperty("dnRoot");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "enableRealTimeStatusInformation", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object disableRealTimeStatusInformation(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[2];
            aobj[0] = xmlapiobject.getProperty("respondHostname");
            aobj[1] = xmlapiobject.getProperty("respondPort");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "disableRealTimeStatusInformation", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
            if (xmlapiresponse.hasErrors()) {
                String s = xmlapiresponse.getError();
                xmlapiobject.setProperty("error", s, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object controlSiteView(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = xmlapiobject.getProperty("hostname");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "controlSiteView", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
            if (xmlapiresponse.hasErrors()) {
                String s = xmlapiresponse.getError();
                xmlapiobject.setProperty("error", s, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object releaseSiteView(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = "not used";
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "releaseSiteView", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getSiteViewInfo(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = xmlapiobject;
            Object aobj[] = new Object[1];
            aobj[0] = xmlapiobject.getProperty("hostname");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "getSiteViewInfo", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                for (int i = 0; i < vector.size(); i ++) {
                    jgl.HashMap hashmap1 = (jgl.HashMap) vector.get(i);
                    xmlapiobject1.add("objectProperty", hashmap1, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object runExisting(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            java.util.Enumeration enumeration = xmlapiobject.elements();
            while (enumeration.hasMoreElements()) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                String s = xmlapiobject.getProperty("type");
                Object aobj[] = new Object[4];
                aobj[0] = xmlapiobject1.getProperty("id");
                aobj[1] = xmlapiobject1.getProperty("ownerid");
                aobj[2] = xmlapiobject1.getProperty("timeout");
                String s1 = xmlapiobject1.getProperty("returnPropertiesOnError");
                if (s1 != null) {
                    aobj[3] = new Boolean(s1);
                } else {
                    aobj[3] = new Boolean("false");
                }
                xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "runExisting", aobj);
                java.util.Vector vector = xmlapiresponse.getReturnVector();
                handleResponse(xmlapiresponse, xmlapiobject, vector);
                if (!xmlapiresponse.hasErrors()) {
                    int i = 0;
                    while (i < vector.size()) {
                        jgl.HashMap hashmap1 = (jgl.HashMap) vector.get(i);
                        xmlapiobject1.add("objectProperty", hashmap1, false);
                        i ++;
                    }
                }
            } 
        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public void runTemporary(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        Object obj = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            jgl.Array array = new Array();
            jgl.Array array1 = new Array();
            jgl.Array array2 = new Array();
            jgl.Array array3 = new Array();
            jgl.Array array4 = new Array();
            String s = xmlapiobject.getProperty("type");
            Object aobj[] = new Object[5];
            java.util.Enumeration enumeration = xmlapiobject.elements();
            while (enumeration.hasMoreElements()) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                String s1 = xmlapiobject1.getProperty("subtype");
                String s2 = xmlapiobject1.getProperty("ownerid");
                String s3 = xmlapiobject1.getProperty("timeout");
                String s5 = xmlapiobject1.getProperty("returnPropertiesOnError");
                jgl.HashMap hashmap2 = null;
                String s6 = xmlapiobject1.getProperty("id");
                if (s6 != null && s6.length() > 0) {
                    s2 = s2 + " " + s6;
                }
                if (s2 != null && s2.length() > 0) {
                    array2.add(s2);
                } else {
                    array2.add("");
                }
                if (s3 != null && s3.length() > 0) {
                    array3.add(s3);
                } else {
                    array3.add("");
                }
                if (s5 != null && s5.length() > 0) {
                    array4.add(s5);
                } else {
                    array4.add("");
                }
                if (s1 != null && s1.length() > 0) {
                    array1.add(s1);
                } else {
                    array1.add("");
                }
                hashmap2 = new HashMap();
                for (java.util.Enumeration enumeration2 = xmlapiobject1.elements(); enumeration2.hasMoreElements();) {
                    com.dragonflow.XmlApi.XmlApiObject xmlapiobject3 = (com.dragonflow.XmlApi.XmlApiObject) enumeration2.nextElement();
                    jgl.HashMap hashmap3 = xmlapiobject3.getProperties();
                    java.util.Enumeration enumeration3 = hashmap3.keys();
                    while (enumeration3.hasMoreElements()) {
                        String s7 = (String) enumeration3.nextElement();
                        if (!s7.equals("_verify")) {
                            hashmap2.put(s7, hashmap3.get(s7));
                        }
                    }
                }

                array.add(hashmap2);
            } 
            aobj[0] = array1;
            aobj[1] = array2;
            aobj[2] = array;
            aobj[3] = array3;
            aobj[4] = array4;
            com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "runTemporary", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            enumeration = xmlapiobject.elements();
            for (int i = 0; enumeration.hasMoreElements(); i ++) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                if (!xmlapiresponse.hasErrors() && vector != null) {
                    String s4 = (String) array1.at(i);
                    if (s4 != null && s4.length() > 0) {
                        xmlapiobject1.setProperty("name", s4, false);
                    }
                    jgl.HashMap hashmap1 = (jgl.HashMap) vector.get(i);
                    java.util.Enumeration enumeration1 = xmlapiobject1.elements();
                    com.dragonflow.XmlApi.XmlApiObject xmlapiobject2 = (com.dragonflow.XmlApi.XmlApiObject) enumeration1.nextElement();
                    xmlapiobject2.setProperties(hashmap1, false);
                    if (hashmap1.get("_id") != null) {
                        xmlapiobject1.setProperty("createid", (String) hashmap1.get("_id"), false);
                    }
                }
            }

        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
    }

    public Object refreshGroup(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = xmlapiobject.getProperty("id");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiGroup", "refreshGroup", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public void getURLStepProperties(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        Object obj = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            jgl.Array array = new Array();
            jgl.Array array1 = new Array();
            jgl.Array array2 = new Array();
            jgl.Array array3 = new Array();
            String s = xmlapiobject.getProperty("type");
            Object aobj[] = new Object[4];
            java.util.Enumeration enumeration = xmlapiobject.elements();
            while (enumeration.hasMoreElements()) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                String s1 = xmlapiobject1.getProperty("name");
                String s2 = xmlapiobject1.getProperty("subtype");
                String s3 = xmlapiobject1.getProperty("ownerid");
                String s5 = xmlapiobject1.getProperty("step");
                String s6 = xmlapiobject1.getProperty("id");
                if (s6 != null && s6.length() > 0) {
                    s3 = s3 + " " + s6;
                }
                if (s3 != null && s3.length() > 0) {
                    array2.add(s3);
                } else {
                    array2.add("");
                }
                if (s5 != null && s5.length() > 0) {
                    array3.add(s5);
                } else {
                    array3.add("");
                }
                if (s.equals("Group")) {
                    array1.add(s1);
                } else {
                    array1.add(s2);
                }
                java.util.HashMap hashmap2 = new java.util.HashMap();
                for (java.util.Enumeration enumeration2 = xmlapiobject1.elements(); enumeration2.hasMoreElements();) {
                    com.dragonflow.XmlApi.XmlApiObject xmlapiobject3 = (com.dragonflow.XmlApi.XmlApiObject) enumeration2.nextElement();
                    jgl.HashMap hashmap3 = xmlapiobject3.getProperties();
                    java.util.Enumeration enumeration3 = hashmap3.keys();
                    while (enumeration3.hasMoreElements()) {
                        String s7 = (String) enumeration3.nextElement();
                        if (!s7.equals("_verify")) {
                            hashmap2.put(s7, hashmap3.get(s7));
                        }
                    }
                }

                array.add(hashmap2);
            } 
            
            aobj[0] = array1;
            aobj[1] = array2;
            aobj[2] = array;
            aobj[3] = array3;
            com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "getURLStepProperties", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            enumeration = xmlapiobject.elements();
            for (int i = 0; enumeration.hasMoreElements(); i ++) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                if (!xmlapiresponse.hasErrors() && vector != null) {
                    String s4 = (String) array1.at(i);
                    if (s4 != null && s4.length() > 0) {
                        xmlapiobject1.setProperty("name", s4, false);
                    }
                    jgl.HashMap hashmap1 = (jgl.HashMap) vector.get(i);
                    java.util.Enumeration enumeration1 = xmlapiobject1.elements();
                    com.dragonflow.XmlApi.XmlApiObject xmlapiobject2 = (com.dragonflow.XmlApi.XmlApiObject) enumeration1.nextElement();
                    xmlapiobject2.setProperties(hashmap1, false);
                    if (hashmap1.get("_id") != null) {
                        xmlapiobject1.setProperty("createid", (String) hashmap1.get("_id"), false);
                    }
                }
            }

        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
    }

    public void addBrowsableCounters(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        Object obj = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("type");
            java.util.Enumeration enumeration = xmlapiobject.elements();
            xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
            String s1 = xmlapiobject1.getProperty("id");
            String s2 = xmlapiobject1.getProperty("ownerid");
            java.util.Enumeration enumeration1 = xmlapiobject1.elements();
            com.dragonflow.XmlApi.XmlApiObject xmlapiobject2 = (com.dragonflow.XmlApi.XmlApiObject) enumeration1.nextElement();
            jgl.HashMap hashmap1 = xmlapiobject2.getProperties();
            Object aobj[] = new Object[3];
            aobj[0] = s1;
            aobj[1] = s2;
            aobj[2] = hashmap1;
            com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "addBrowsableCounters", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            enumeration = xmlapiobject.elements();
            for (int i = 0; enumeration.hasMoreElements(); i ++) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                if (!xmlapiresponse.hasErrors() && vector != null) {
                    jgl.HashMap hashmap2 = (jgl.HashMap) vector.get(i);
                    java.util.Enumeration enumeration2 = xmlapiobject1.elements();
                    com.dragonflow.XmlApi.XmlApiObject xmlapiobject3 = (com.dragonflow.XmlApi.XmlApiObject) enumeration2.nextElement();
                    xmlapiobject3.setProperties(hashmap2, false);
                }
            }

        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
    }

    public void removeBrowsableCounters(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        Object obj = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("type");
            java.util.Enumeration enumeration = xmlapiobject.elements();
            xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
            String s1 = xmlapiobject1.getProperty("id");
            String s2 = xmlapiobject1.getProperty("ownerid");
            java.util.Enumeration enumeration1 = xmlapiobject1.elements();
            com.dragonflow.XmlApi.XmlApiObject xmlapiobject2 = (com.dragonflow.XmlApi.XmlApiObject) enumeration1.nextElement();
            jgl.HashMap hashmap1 = xmlapiobject2.getProperties();
            Object aobj[] = new Object[3];
            aobj[0] = s1;
            aobj[1] = s2;
            aobj[2] = hashmap1;
            com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "removeBrowsableCounters", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            enumeration = xmlapiobject.elements();
            for (int i = 0; enumeration.hasMoreElements(); i ++) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                if (!xmlapiresponse.hasErrors() && vector != null) {
                    jgl.HashMap hashmap2 = (jgl.HashMap) vector.get(i);
                    java.util.Enumeration enumeration2 = xmlapiobject1.elements();
                    com.dragonflow.XmlApi.XmlApiObject xmlapiobject3 = (com.dragonflow.XmlApi.XmlApiObject) enumeration2.nextElement();
                    xmlapiobject3.setProperties(hashmap2, false);
                }
            }

        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
    }

    public Object test(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            java.util.Enumeration enumeration = xmlapiobject.elements();
            while (enumeration.hasMoreElements()) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                String s = xmlapiobject.getProperty("type");
                Object aobj[] = new Object[5];
                aobj[0] = xmlapiobject1.getProperty("id");
                aobj[1] = xmlapiobject1.getProperty("attributeId");
                aobj[2] = xmlapiobject1.getProperty("attributeValue");
                aobj[3] = xmlapiobject1.getProperty("additionalParameter");
                if (xmlapiobject.getProperty("statusOnly") != null) {
                    aobj[4] = xmlapiobject.getProperty("statusOnly");
                }
                xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "test", aobj);
                java.util.Vector vector = xmlapiresponse.getReturnVector();
                handleResponse(xmlapiresponse, xmlapiobject, vector);
                if (!xmlapiresponse.hasErrors()) {
                    java.util.Vector vector1 = (java.util.Vector) vector.elementAt(0);
                    String s1 = "";
                    int i = 0;
                    while (i < vector1.size()) {
                        String s2 = (String) vector1.elementAt(i);
                        jgl.HashMap hashmap1 = new HashMap(true);
                        hashmap1.put("testOutput", s2);
                        xmlapiobject1.add("objectproperty", hashmap1, false);
                        i ++;
                    }
                }
            } 
        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getObjects(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("type");
            Object aobj[] = new Object[1];
            aobj[0] = s;
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "getObjects", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                for (int i = 0; i < vector.size(); i ++) {
                    jgl.HashMap hashmap1 = new HashMap();
                    hashmap1.put("listItem", vector.get(i));
                    xmlapiobject.add("object", hashmap1, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getTopazID(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("type");
            String s1 = xmlapiobject.getProperty("id");
            String s2 = xmlapiobject.getProperty("ownerid");
            Object aobj[] = new Object[2];
            aobj[0] = s1;
            aobj[1] = s2;
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "getTopazID", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                jgl.HashMap hashmap1 = new HashMap();
                hashmap1.put("topazID", vector.get(0));
                xmlapiobject.add("object", hashmap1, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getWebServers(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            java.util.Enumeration enumeration = xmlapiobject.elements();
            com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
            Object aobj[] = new Object[1];
            aobj[0] = xmlapiobject1.getProperty("_machine");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "getWebServers", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                for (int i = 0; i < vector.size(); i += 2) {
                    jgl.HashMap hashmap1 = new HashMap();
                    hashmap1.put("listItem", vector.get(i));
                    hashmap1.put("listItemName", vector.get(i + 1));
                    xmlapiobject1.add("objectProperty", hashmap1, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getOSs(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = "";
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "getOSs", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                for (int i = 0; i < vector.size(); i += 2) {
                    jgl.HashMap hashmap1 = new HashMap();
                    hashmap1.put("listItem", vector.get(i));
                    xmlapiobject.add("object", hashmap1, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getWebServiceFiles(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = "";
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "getWebServiceFiles", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                for (int i = 0; i < vector.size(); i ++) {
                    jgl.HashMap hashmap1 = new HashMap();
                    hashmap1.put("listItem", vector.get(i));
                    xmlapiobject.add("object", hashmap1, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getWebServiceMethodsAndURL(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = xmlapiobject.getProperty("wsdlurl");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "getWebServiceMethodsAndURL", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                for (int i = 0; i < vector.size(); i ++) {
                    jgl.HashMap hashmap1 = new HashMap();
                    hashmap1.put("listItem", vector.get(i));
                    xmlapiobject.add("object", hashmap1, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getWebServiceArgs(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[2];
            aobj[0] = xmlapiobject.getProperty("wsdlurl");
            aobj[1] = xmlapiobject.getProperty("methodName");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "getWebServiceArgs", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                for (int i = 0; i < vector.size(); i ++) {
                    jgl.HashMap hashmap1 = new HashMap();
                    hashmap1.put("listItem", vector.get(i));
                    xmlapiobject.add("object", hashmap1, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object shutdownSiteView(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = "";
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "shutdownSiteView", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object createSession(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = xmlapiobject.getProperty("timeout");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "createSession", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object sendHeartbeat(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = "";
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "sendHeartbeat", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object updateGeneralLicense(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[2];
            aobj[0] = xmlapiobject.getProperty("newLicenseKey");
            aobj[1] = xmlapiobject.getProperty("sessionOnly");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "updateGeneralLicense", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object updateSpecialLicense(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[2];
            aobj[0] = xmlapiobject.getProperty("newLicenseKey");
            aobj[1] = xmlapiobject.getProperty("sessionOnly");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "updateSpecialLicense", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object isTopazConnected(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = "";
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "isTopazConnected", aobj);
            if (!xmlapiresponse.hasErrors()) {
                java.util.Vector vector = xmlapiresponse.getReturnVector();
                jgl.HashMap hashmap1 = new HashMap();
                String s = vector.elementAt(0).toString();
                hashmap1.put("isTopazConnected", s);
                xmlapiobject.add("object", hashmap1, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object isUIControled(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = "";
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "isUIControled", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, xmlapiresponse.getReturnVector());
            if (!xmlapiresponse.hasErrors()) {
                java.util.Vector vector = xmlapiresponse.getReturnVector();
                jgl.HashMap hashmap1 = new HashMap();
                String s = vector.elementAt(0).toString();
                hashmap1.put("isUIControled", s);
                xmlapiobject.add("object", hashmap1, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object isServerRegistered(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = xmlapiobject.getProperty("serverAddress");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "isServerRegistered", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, xmlapiresponse.getReturnVector());
            if (!xmlapiresponse.hasErrors()) {
                java.util.Vector vector = xmlapiresponse.getReturnVector();
                jgl.HashMap hashmap1 = new HashMap();
                String s = vector.elementAt(0).toString();
                hashmap1.put("isServerRegistered", s);
                xmlapiobject.add("object", hashmap1, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getFreeProfiles(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = xmlapiobject.getTreeProperties();
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "getFreeProfiles", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, xmlapiresponse.getReturnVector());
            if (!xmlapiresponse.hasErrors()) {
                java.util.Vector vector = xmlapiresponse.getReturnVector();
                jgl.HashMap hashmap1 = new HashMap();
                String s = vector.elementAt(0).toString();
                hashmap1.put("getFreeProfiles", s);
                xmlapiobject.add("object", hashmap1, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object isTopazDisabled(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[2];
            aobj[0] = xmlapiobject.getProperty("serverAddress");
            aobj[1] = "not used";
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "isTopazDisabled", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                jgl.HashMap hashmap1 = new HashMap();
                String s = vector.elementAt(0).toString();
                hashmap1.put("isTopazDisabled", s);
                xmlapiobject.add("object", hashmap1, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object setTopazDisabled(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[2];
            aobj[0] = xmlapiobject.getProperty("serverAddress");
            aobj[1] = xmlapiobject.getProperty("disable");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "setTopazDisabled", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object flushTopazData(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = "";
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "flushTopazData", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object resyncTopazData(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("withDelete");
            Object aobj[] = new Object[1];
            aobj[0] = s;
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "resyncTopazData", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object resetTopazProfile(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = xmlapiobject.getProperty("serverAddress");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "resetTopazProfile", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object deleteSiteView(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = xmlapiobject.getProperty("serverAddress");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "deleteSiteView", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getTopazServerSettings(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = xmlapiobject.getProperty("serverAddress");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "getTopazServerSettings", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                jgl.HashMap hashmap1 = new HashMap();
                jgl.HashMap hashmap2 = new HashMap();
                if (vector.size() > 0) {
                    hashmap2 = (jgl.HashMap) vector.elementAt(0);
                    hashmap1.put("profileId", hashmap2.get("profileId"));
                    hashmap2.remove("profileId");
                } else {
                    hashmap1.put("profileId", "not connected");
                }
                com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = xmlapiobject.add("object", hashmap1, false);
                xmlapiobject1.add("objectProperty", hashmap2, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getServerSettingsByEntity(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = xmlapiobject.getProperty("entity");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "getServerSettingsByEntity", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                jgl.HashMap hashmap1 = new HashMap();
                if (vector.size() > 0) {
                    hashmap1 = (jgl.HashMap) vector.elementAt(0);
                }
                xmlapiobject.add("objectProperty", hashmap1, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object registerTopazProfile(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        Object obj = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("profileId");
            String s1 = xmlapiobject.getProperty("profileName");
            java.util.Enumeration enumeration = xmlapiobject.elements();
            com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
            jgl.HashMap hashmap1 = xmlapiobject1.getTreeProperties();
            Object aobj[] = new Object[3];
            aobj[0] = s;
            aobj[1] = s1;
            aobj[2] = hashmap1;
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "registerTopazProfile", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            if (vector == null) {
                vector = new Vector();
            }
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                jgl.HashMap hashmap2 = new HashMap();
                jgl.HashMap hashmap3 = new HashMap();
                if (vector.size() > 0) {
                    hashmap3 = (jgl.HashMap) vector.elementAt(0);
                    hashmap2.put("profileId", hashmap3.get("profileId"));
                    hashmap3.remove("profileId");
                } else {
                    hashmap2.put("profileId", "not connected");
                }
                xmlapiobject1.setProperties(hashmap2, false);
                xmlapiobject1.add("objectProperty", hashmap3, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object reRegisterTopazProfile(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        Object obj = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            java.util.Enumeration enumeration = xmlapiobject.elements();
            com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
            jgl.HashMap hashmap1 = xmlapiobject1.getTreeProperties();
            Object aobj[] = new Object[1];
            aobj[0] = hashmap1;
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "reRegisterTopazProfile", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getTopazFullId(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("topazId");
            Object aobj[] = new Object[1];
            aobj[0] = s;
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "getTopazFullId", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                jgl.HashMap hashmap1 = new HashMap();
                if (vector.size() > 0) {
                    hashmap1.put("topazId", vector.elementAt(0));
                } else {
                    hashmap1.put("topazId", "not found");
                }
                xmlapiobject.add("object", hashmap1, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object issueSiebelCmd(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("siebelCmd");
            Object aobj[] = new Object[1];
            aobj[0] = s;
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "issueSiebelCmd", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors() && vector.size() > 0) {
                for (int i = 0; i < vector.size(); i ++) {
                    jgl.HashMap hashmap1 = new HashMap();
                    hashmap1.put("siebelResp", vector.get(i));
                    xmlapiobject.add("object", hashmap1, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getCurrentApiVersion(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = "";
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "getCurrentApiVersion", aobj);
            if (!xmlapiresponse.hasErrors()) {
                java.util.Vector vector = xmlapiresponse.getReturnVector();
                jgl.HashMap hashmap1 = new HashMap();
                String s = vector.elementAt(0).toString();
                hashmap1.put("version", s);
                xmlapiobject.add("object", hashmap1, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object refreshCache(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "refreshCache", aobj);
            handleResponse(xmlapiresponse, xmlapiobject, new Vector());
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    private Object getOperationObject(String s) {
        Integer integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ALL);
        if (s.length() > 0) {
            if (s.equals("add")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ALL);
            } else if (s.equals("import")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL);
            } else if (s.equals("prereq")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.PREREQ_OP);
            } else if (s.equals("all")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_ALL);
            } else if (s.equals("edit")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_EDIT_ALL);
            } else if (s.equals("runtime")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_RUNTIME_ALL);
            } else if (s.equals("required")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_REQUIRED);
            } else if (s.equals("basic")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_BASIC);
            } else if (s.equals("advanced")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ADVANCED);
            } else if (s.equals("add_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ALL_NOT_EMPTY);
            } else if (s.equals("edit_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_EDIT_ALL_NOT_EMPTY);
            } else if (s.equals("import_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL_NOT_EMPTY);
            } else if (s.equals("add_all_notemtpy")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ALL);
            } else if (s.equals("add_basic_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_BASIC_NOT_EMPTY);
            } else if (s.equals("add_advanced_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ADVANCED_NOT_EMPTY);
            } else if (s.equals("edit_all_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_EDIT_ALL_NOT_EMPTY);
            } else if (s.equals("edit_basic_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_EDIT_BASIC_NOT_EMPTY);
            } else if (s.equals("edit_advanced_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_EDIT_ADVANCED_NOT_EMPTY);
            } else if (s.equals("add_all_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ALL_NOT_EMPTY);
            } else if (s.equals("add_basic_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_BASIC_NOT_EMPTY);
            } else if (s.equals("add_advanced_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ADVANCED_NOT_EMPTY);
            } else if (s.equals("edit_all_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_EDIT_ALL_NOT_EMPTY);
            } else if (s.equals("edit_basic_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_EDIT_BASIC_NOT_EMPTY);
            } else if (s.equals("edit_advanced_notempty")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_EDIT_ADVANCED_NOT_EMPTY);
            } else if (s.equals("runtime_all")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_RUNTIME_ALL);
            } else if (s.equals("runtime_measurements")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_RUNTIME_MEASUREMENTS);
            } else if (s.equals("alert_associated")) {
                integer = new Integer(com.dragonflow.Api.APISiteView.FILTER_ALERT_ASSOCIATED);
            }
        }
        return integer;
    }

    private void handleResponse(com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse, com.dragonflow.XmlApi.XmlApiObject xmlapiobject, java.util.Vector vector) {
        if (xmlapiresponse.hasErrors() || vector == null) {
            String s = xmlapiresponse.getErrorCode();
            if (s != null) {
                xmlapiobject.setProperty("errorcode", s, false);
            }
            String s1 = xmlapiresponse.getErrorType();
            if (s1 != null) {
                xmlapiobject.setProperty("errortype", s1, false);
            }
            String as[] = xmlapiresponse.getErrorArguments();
            if (as != null && as.length > 0) {
                xmlapiobject.setProperty("errorargs", as, false);
            }
            String s2 = xmlapiresponse.getApplicationErrorCode();
            if (s2 != null) {
                xmlapiobject.setProperty("applicationerrorcode", s2, false);
            }
            String s3 = xmlapiresponse.getApplicationErrorMessage();
            if (s3 != null) {
                xmlapiobject.setProperty("applicationerrormessage", s3, false);
            }
            java.util.Map map = xmlapiresponse.getParameterErrors();
            if (map != null && map.size() > 0) {
                String as1[] = new String[map.size() * 2];
                java.util.Set set = map.keySet();
                java.util.Iterator iterator = set.iterator();
                for (int i = 0; iterator.hasNext(); i += 2) {
                    String s6 = (String) iterator.next();
                    as1[i] = s6;
                    as1[i + 1] = (String) map.get(s6);
                }

                xmlapiobject.setProperty("errorparameters", as1, false);
            }
            String s4 = "";
            if (as == null || as.length == 0) {
                s4 = com.dragonflow.Resource.SiteViewResource.getString(s);
            } else {
                s4 = com.dragonflow.Resource.SiteViewResource.getFormattedString(s, as);
            }
            if (map != null && map.size() > 0) {
                String s5 = "";
                java.util.Set set1 = map.keySet();
                for (java.util.Iterator iterator1 = set1.iterator(); iterator1.hasNext();) {
                    if (s5.length() > 0) {
                        s5 = s5 + ", ";
                    }
                    s5 = s5 + (String) iterator1.next();
                }

                s4 = com.dragonflow.Resource.SiteViewResource.getFormattedString(s, new String[] { s5 });
            }
            if (s4 != null) {
                xmlapiobject.setProperty("error", s4, false);
            } else {
                xmlapiobject.setProperty("error", "operation on object failed, no specific exeception message provided", false);
            }
        }
    }

    public Object hasSolutionLicense(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            Object aobj[] = new Object[1];
            aobj[0] = xmlapiobject.getProperty("solutionType");
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "hasSolutionLicense", aobj);
            if (!xmlapiresponse.hasErrors()) {
                java.util.Vector vector = xmlapiresponse.getReturnVector();
                jgl.HashMap hashmap1 = new HashMap();
                String s = vector.elementAt(0).toString();
                hashmap1.put("hasSolutionLicense", s);
                xmlapiobject.add("object", hashmap1, false);
            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object resetCounters(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            java.util.Enumeration enumeration = xmlapiobject.elements();
            while (enumeration.hasMoreElements()) {
                xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
                String s = xmlapiobject.getProperty("type");
                Object aobj[] = new Object[2];
                aobj[0] = xmlapiobject1.getProperty("id");
                aobj[1] = xmlapiobject1.getProperty("ownerid");
                xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApi" + s, "resetCounters", aobj);
                java.util.Vector vector = xmlapiresponse.getReturnVector();
                handleResponse(xmlapiresponse, xmlapiobject, vector);
                if (!xmlapiresponse.hasErrors()) {
                    int i = 0;
                    while (i < vector.size()) {
                        jgl.HashMap hashmap1 = (jgl.HashMap) vector.get(i);
                        xmlapiobject1.add("objectProperty", hashmap1, false);
                        i ++;
                    }
                }
            } 
        } catch (Exception exception) {
            xmlapiobject1.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getSystemTime(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("sysTimetargetMachine");
            Object aobj[] = new Object[1];
            aobj[0] = s;
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "getSystemTime", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors() && vector.size() > 0) {
                for (int i = 0; i < vector.size(); i ++) {
                    jgl.HashMap hashmap1 = new HashMap();
                    hashmap1.put("sysTimetargetMachineResp", vector.get(i));
                    xmlapiobject.add("object", hashmap1, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

    public Object getFileList(com.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = null;
        try {
            jgl.HashMap hashmap = xmlapiobject.getProperties();
            xmlapiobject.setProperties(hashmap, false);
            String s = xmlapiobject.getProperty("getFileListTargetMachine");
            String s1 = xmlapiobject.getProperty("getFileListTargetDirectory");
            Object aobj[] = new Object[2];
            aobj[0] = s;
            aobj[1] = s1;
            xmlapiresponse = (com.dragonflow.XmlApi.XmlApiResponse) com.dragonflow.XmlApi.XmlApiRequest.invokeMethod("com.dragonflow.XmlApi.XmlApiSiteView", "getFileList", aobj);
            java.util.Vector vector = xmlapiresponse.getReturnVector();
            handleResponse(xmlapiresponse, xmlapiobject, vector);
            if (!xmlapiresponse.hasErrors()) {
                if (vector.size() == 0) {
                    vector.add(new String[] { "", "" });
                }
                for (int i = 0; i < vector.size(); i ++) {
                    jgl.HashMap hashmap1 = new HashMap();
                    hashmap1.put("getFileListResponse", vector.get(i));
                    xmlapiobject.add("object", hashmap1, false);
                }

            }
        } catch (Exception exception) {
            xmlapiobject.setProperty("error", exception.getMessage(), false);
        }
        return xmlapiresponse;
    }

}
