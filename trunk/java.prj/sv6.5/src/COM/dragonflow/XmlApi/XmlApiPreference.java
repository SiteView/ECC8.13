/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.XmlApi;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.util.Vector;

import jgl.HashMap;
import COM.dragonflow.Api.APIPreference;
import COM.dragonflow.Api.SSInstanceProperty;

// Referenced classes of package COM.dragonflow.XmlApi:
// XmlApiResponse

public class XmlApiPreference {

    COM.dragonflow.Api.APIPreference api;

    public XmlApiPreference() {
        api = null;
        api = new APIPreference();
    }

    public java.lang.Object add(jgl.Array array, jgl.Array array1, jgl.Array array2, java.lang.String s) {
        COM.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            java.util.Enumeration enumeration = array.elements();
            int i = 0;
            java.lang.String s1 = "";
            Object obj = null;
            while (enumeration.hasMoreElements()) {
                java.lang.String s2 = (java.lang.String) enumeration.nextElement();
                jgl.HashMap hashmap = (jgl.HashMap) array2.at(i);
                java.lang.Boolean boolean1 = new Boolean(false);
                if ((java.lang.String) hashmap.get("testPreference") != null) {
                    boolean1 = new Boolean((java.lang.String) hashmap.get("testPreference"));
                    hashmap.remove("testPreference");
                }
                COM.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new COM.dragonflow.Api.SSInstanceProperty[hashmap.size()];
                java.util.Enumeration enumeration1 = hashmap.keys();
                int j = 0;
                Object obj1 = null;
                while (enumeration1.hasMoreElements()) {
                    java.lang.String s3 = (java.lang.String) enumeration1.nextElement();
                    java.lang.String s4 = (java.lang.String) hashmap.get(s3);
                    assinstanceproperty[j] = new SSInstanceProperty(s3, s4);
                    j ++;
                }
                COM.dragonflow.Api.SSInstanceProperty ssinstanceproperty = api.create(s2, assinstanceproperty);
                if (!boolean1.booleanValue()) {
                    COM.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = api.getInstanceProperties(s2, "", ssinstanceproperty.getName(), (java.lang.String) ssinstanceproperty.getValue(),
                            COM.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ADD_ALL);
                    jgl.HashMap hashmap1 = new HashMap();
                    for (int k = 0; k < assinstanceproperty1.length; k ++) {
                        hashmap1.put(assinstanceproperty1[k].getName(), assinstanceproperty1[k].getValue());
                    }

                    vector.add(hashmap1);
                } else {
                    java.util.Vector vector1 = api.test(s2, "_id", (java.lang.String) ssinstanceproperty.getValue(), "", false);
                    jgl.HashMap hashmap2 = new HashMap();
                    for (int l = 0; l < vector1.size(); l ++) {
                        hashmap2.put(vector1.elementAt(l), vector1.elementAt(l));
                    }

                    vector.add(hashmap2);
                }
            }
            xmlapiresponse.setReturnVector(vector);
        } catch (COM.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object update(jgl.Array array, jgl.Array array1, jgl.Array array2, jgl.Array array3, jgl.Array array4) throws COM.dragonflow.SiteViewException.SiteViewException {
        COM.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            int i = 0;
            java.lang.String s = "";
            java.lang.String s2 = "";
            java.lang.String s4 = "";
            Object obj = null;
            jgl.HashMap hashmap1;
            for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); vector.add(hashmap1)) {
                java.lang.String s1 = (java.lang.String) enumeration.nextElement();
                java.lang.String s3 = (java.lang.String) array3.at(i);
                java.lang.String s5 = (java.lang.String) array4.at(i);
                jgl.HashMap hashmap = (jgl.HashMap) array2.at(i);
                COM.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new COM.dragonflow.Api.SSInstanceProperty[hashmap.size()];
                java.util.Enumeration enumeration1 = hashmap.keys();
                for (int j = 0; enumeration1.hasMoreElements(); j ++) {
                    java.lang.String s6 = (java.lang.String) enumeration1.nextElement();
                    assinstanceproperty[j] = new SSInstanceProperty(s6, hashmap.get(s6));
                }

                COM.dragonflow.Api.SSInstanceProperty ssinstanceproperty = api.update(s1, s3, s5, assinstanceproperty);
                COM.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = api.getInstanceProperties(s1, "", ssinstanceproperty.getName(), (java.lang.String) ssinstanceproperty.getValue(), COM.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL);
                hashmap1 = new HashMap();
                for (int k = 0; k < assinstanceproperty1.length; k ++) {
                    hashmap1.put(assinstanceproperty1[k].getName(), assinstanceproperty1[k].getValue());
                }

            }

            xmlapiresponse.setReturnVector(vector);
        } catch (COM.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object delete(jgl.Array array, jgl.Array array1, jgl.Array array2, jgl.Array array3) {
        COM.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            int i = 0;
            java.lang.String s = "";
            java.lang.String s2 = "";
            java.lang.String s4 = "";
            java.lang.String as[];
            for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); vector.add(as)) {
                java.lang.String s1 = (java.lang.String) enumeration.nextElement();
                java.lang.String s3 = (java.lang.String) array2.at(i);
                java.lang.String s5 = (java.lang.String) array3.at(i);
                api.delete(s1, s3, s5);
                as = new java.lang.String[2];
                as[0] = s3;
                as[1] = s5;
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (COM.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object test(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4) {
        COM.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            vector.add(api.test(s, s1, s2, s3, (new Boolean(s4)).booleanValue()));
            xmlapiresponse.setReturnVector(vector);
        } catch (COM.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getClassPropertiesDetails(java.lang.String s, jgl.HashMap hashmap, java.lang.Integer integer) {
        COM.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            COM.dragonflow.Api.SSPropertyDetails asspropertydetails[] = api.getClassPropertiesDetails(s, integer.intValue());
            for (int i = 0; i < asspropertydetails.length; i ++) {
                jgl.HashMap hashmap1 = new HashMap();
                COM.dragonflow.Api.SSPropertyDetails.extractDetailsIntoHashMap(asspropertydetails[i], hashmap1);
                vector.add(hashmap1);
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (COM.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getClassPropertyDetails(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap) {
        COM.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            COM.dragonflow.Api.SSPropertyDetails asspropertydetails[] = api.getClassPropertiesDetails(s1, COM.dragonflow.Api.APISiteView.FILTER_ALL);
            for (int i = 0; i < asspropertydetails.length; i ++) {
                if (asspropertydetails[i].getName().equals(s)) {
                    jgl.HashMap hashmap1 = new HashMap();
                    COM.dragonflow.Api.SSPropertyDetails.extractDetailsIntoHashMap(asspropertydetails[i], hashmap1);
                    vector.add(hashmap1);
                }
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (COM.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getInstances(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.Integer integer) {
        COM.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            COM.dragonflow.Api.SSPreferenceInstance asspreferenceinstance[] = api.getInstances(s, s1, "", "", integer.intValue());
            for (int i = 0; i < asspreferenceinstance.length; i ++) {
                COM.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = asspreferenceinstance[i].getInstanceProperties();
                jgl.HashMap hashmap = new HashMap();
                for (int j = 0; j < assinstanceproperty.length; j ++) {
                    hashmap.add(assinstanceproperty[j].getName(), assinstanceproperty[j].getValue());
                }

                vector.add(hashmap);
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (COM.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getInstanceProperties(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.Integer integer) {
        COM.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            COM.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = api.getInstanceProperties(s, s1, s2, s3, integer.intValue());
            jgl.HashMap hashmap = new HashMap();
            for (int i = 0; i < assinstanceproperty.length; i ++) {
                hashmap.add(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
            }

            vector.add(hashmap);
            xmlapiresponse.setReturnVector(vector);
        } catch (COM.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }
}
