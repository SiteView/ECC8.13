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

import jgl.HashMap;
import com.dragonflow.Api.APIAlert;
import com.dragonflow.Api.SSInstanceProperty;

// Referenced classes of package com.dragonflow.XmlApi:
// XmlApiResponse

public class XmlApiAlert {

    private com.dragonflow.Api.APIAlert api;

    public XmlApiAlert() {
        api = null;
        api = new APIAlert();
    }

    public Object add(jgl.Array array, jgl.Array array1, jgl.Array array2, String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            int i = 0;
            Object obj = null;
            java.util.Enumeration enumeration = array.elements();
            java.util.Vector vector = new Vector();
            jgl.HashMap hashmap1;
            for (; enumeration.hasMoreElements(); vector.add(hashmap1)) {
                String s1 = (String) enumeration.nextElement();
                String s2 = (String) array1.at(i);
                jgl.HashMap hashmap = (jgl.HashMap) array2.at(i);
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
                java.util.Enumeration enumeration1 = hashmap.keys();
                for (int j = 0; enumeration1.hasMoreElements(); j ++) {
                    String s3 = (String) enumeration1.nextElement();
                    assinstanceproperty[j] = new SSInstanceProperty(s3, hashmap.get(s3));
                }

                com.dragonflow.Api.Alert alert = api.create(s1, s2, assinstanceproperty);
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = api.getInstanceProperties(alert.getIDStr(), alert.getMonitorID(), alert.getGroup(), com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL);
                hashmap1 = new HashMap();
                assinstanceproperty = new com.dragonflow.Api.SSInstanceProperty[assinstanceproperty1.length];
                for (int k = 0; k < assinstanceproperty1.length; k ++) {
                    hashmap1.put(assinstanceproperty1[k].getName(), assinstanceproperty1[k].getValue());
                }

                hashmap1.put("_id", alert.getIDStr());
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object update(jgl.Array array, jgl.Array array1, jgl.Array array2, jgl.Array array3, jgl.Array array4) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            int i = 0;
            Object obj = null;
            java.util.Enumeration enumeration = array.elements();
            java.util.Vector vector = new Vector();
            jgl.HashMap hashmap1;
            for (; enumeration.hasMoreElements(); vector.add(hashmap1)) {
                String s = (String) enumeration.nextElement();
                String s1 = (String) array1.at(i);
                jgl.HashMap hashmap = (jgl.HashMap) array2.at(i);
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
                java.util.Enumeration enumeration1 = hashmap.keys();
                for (int j = 0; enumeration1.hasMoreElements(); j ++) {
                    String s2 = (String) enumeration1.nextElement();
                    assinstanceproperty[j] = new SSInstanceProperty(s2, hashmap.get(s2));
                }

                com.dragonflow.Api.Alert alert = api.update(s, s1, assinstanceproperty);
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = api.getInstanceProperties(alert.getIDStr(), alert.getMonitorID(), alert.getGroup(), com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL);
                hashmap1 = new HashMap();
                assinstanceproperty = new com.dragonflow.Api.SSInstanceProperty[assinstanceproperty1.length];
                for (int k = 0; k < assinstanceproperty1.length; k ++) {
                    hashmap1.put(assinstanceproperty1[k].getName(), assinstanceproperty1[k].getValue());
                }

                hashmap1.put("_id", alert.getIDStr());
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object delete(jgl.Array array, jgl.Array array1, jgl.Array array2, jgl.Array array3) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            int i = 0;
            java.util.Enumeration enumeration = array.elements();
            java.util.Vector vector = new Vector();
            String as[];
            for (; enumeration.hasMoreElements(); vector.add(as)) {
                String s = (String) enumeration.nextElement();
                String s1 = (String) array1.at(i);
                api.delete(s);
                as = new String[2];
                as[0] = s;
                as[1] = s1;
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object copy(String s, String s1, String s2) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        jgl.HashMap hashmap = new HashMap();
        try {
            java.util.Vector vector = new Vector();
            String s3 = "";
            String s4 = "";
            if (s1 != null && s1.length() > 0) {
                s3 = s1;
                String as[] = com.dragonflow.Utils.TextUtils.split(s1);
                if (as.length > 1) {
                    s3 = as[0];
                    s4 = as[1];
                }
            }
            String s5 = "";
            String s6 = "";
            if (s2 != null && s2.length() > 0) {
                s5 = s2;
                String as1[] = com.dragonflow.Utils.TextUtils.split(s2);
                if (as1.length > 1) {
                    s5 = as1[0];
                    s6 = as1[1];
                }
            }
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = api.getInstanceProperties(s, s4, s3, com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL);
            if (assinstanceproperty != null) {
                String s7 = "NoAlertType";
                for (int i = 0; i < assinstanceproperty.length; i ++) {
                    if (assinstanceproperty[i].getName() != null && assinstanceproperty[i].getName().equals("_class")) {
                        s7 = (String) assinstanceproperty[i].getValue();
                    }
                }

                com.dragonflow.Api.Alert alert = api.create(s7, s2, assinstanceproperty);
                assinstanceproperty = api.getInstanceProperties(alert.getIDStr(), s6, s5, com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL);
                jgl.HashMap hashmap1 = new HashMap();
                for (int j = 0; j < assinstanceproperty.length; j ++) {
                    hashmap1.put(assinstanceproperty[j].getName(), assinstanceproperty[j].getValue());
                }

                hashmap1.put("_id", alert.getIDStr());
                vector.add(hashmap1);
            } else {
                hashmap.put(String.valueOf(0), "Can not find alert for copy");
            }
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object test(String s, String s1, String s2, String s3, String s4) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            vector.add(api.test(s, s2, s3));
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getClassPropertyDetails(String s, String s1, jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSPropertyDetails asspropertydetails[] = api.getClassPropertiesDetails(s1, com.dragonflow.Api.APISiteView.FILTER_ALL, hashmap);
            for (int i = 0; i < asspropertydetails.length; i ++) {
                jgl.HashMap hashmap1 = new HashMap();
                com.dragonflow.Api.SSPropertyDetails.extractDetailsIntoHashMap(asspropertydetails[i], hashmap1);
                if (s.indexOf(asspropertydetails[i].getName()) != -1) {
                    vector.add(hashmap1);
                }
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getClassPropertyScalars(String s, String s1, jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSPropertyDetails sspropertydetails = api.getClassPropertyDetails(s, s1, hashmap);
            vector.add(sspropertydetails.getName());
            vector.add(sspropertydetails.getSelectionIDs());
            vector.add(sspropertydetails.getSelectionDisplayNames());
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getInstancePropertyScalars(String s, String s1, String s2) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            String s3 = "";
            String s4 = "";
            if (s2 != null && s2.length() > 0) {
                s3 = s2;
                String as[] = com.dragonflow.Utils.TextUtils.split(s2);
                if (as.length > 1) {
                    s3 = as[0];
                    s4 = as[1];
                }
            }
            com.dragonflow.Api.SSPropertyDetails sspropertydetails = api.getInstancePropertyDetails(s, s3, s4, s1);
            vector.add(sspropertydetails.getName());
            vector.add(sspropertydetails.getSelectionIDs());
            vector.add(sspropertydetails.getSelectionDisplayNames());
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getInstances(String s, String s1, String s2, String s3, Integer integer) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SVAlertInstance assalertinstance[] = api.getInstances(s1, s, integer.intValue());
            Object obj = null;
            for (int i = 0; i < assalertinstance.length; i ++) {
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = assalertinstance[i].getInstanceProperties();
                jgl.HashMap hashmap = new HashMap(false);
                for (int j = 0; j < assinstanceproperty.length; j ++) {
                    hashmap.put(assinstanceproperty[j].getName(), assinstanceproperty[j].getValue());
                }

                vector.add(hashmap);
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getInstanceProperties(String s, String s1, String s2, String s3, Integer integer) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = api.getInstanceProperties(s, s1, s2, integer.intValue());
            jgl.HashMap hashmap = new HashMap();
            for (int i = 0; i < assinstanceproperty.length; i ++) {
                hashmap.put(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
            }

            vector.add(hashmap);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object listObjects(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        java.util.Vector vector = new Vector();
        String as[] = null;
        as = new String[3];
        as[0] = "Alert";
        as[1] = "yes";
        as[2] = "yes";
        vector.add(as);
        xmlapiresponse.setReturnVector(vector);
        return xmlapiresponse;
    }
}
