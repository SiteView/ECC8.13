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
import com.dragonflow.Api.APIGroup;
import com.dragonflow.Api.SSInstanceProperty;

// Referenced classes of package com.dragonflow.XmlApi:
// XmlApiResponse

public class XmlApiGroup {

    private com.dragonflow.Api.APIGroup api;

    private com.dragonflow.Api.APIAlert apiAlert;

    public XmlApiGroup() {
        api = null;
        apiAlert = null;
        api = new APIGroup();
    }

    public Object add(jgl.Array array, jgl.Array array1, jgl.Array array2, String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            int i = 0;
            String s1 = "";
            String s3 = "";
            Object obj = null;
            java.util.Enumeration enumeration = array.elements();
            java.util.Vector vector = new Vector();
            while (enumeration.hasMoreElements()) {
                String s2 = (String) enumeration.nextElement();
                String s4 = (String) array1.at(i);
                jgl.HashMap hashmap = (jgl.HashMap) array2.at(i);
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
                java.util.Enumeration enumeration1 = hashmap.keys();
                for (int j = 0; enumeration1.hasMoreElements(); j ++) {
                    String s5 = (String) enumeration1.nextElement();
                    assinstanceproperty[j] = new SSInstanceProperty(s5, hashmap.get(s5));
                }

                com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = api.create(s2, s4, assinstanceproperty);
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = api.getInstanceProperties(ssstringreturnvalue.getValue(), com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL);
                jgl.HashMap hashmap1 = new HashMap();
                for (int k = 0; k < assinstanceproperty1.length; k ++) {
                    hashmap1.put(assinstanceproperty1[k].getName(), assinstanceproperty1[k].getValue());
                }

                hashmap1.put("_id", ssstringreturnvalue.getValue());
                vector.add(hashmap1);
                i ++;
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
            String s = "";
            Object obj = null;
            java.util.Vector vector = new Vector();
            jgl.HashMap hashmap1;
            for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); vector.add(hashmap1)) {
                String s1 = (String) enumeration.nextElement();
                jgl.HashMap hashmap = (jgl.HashMap) array2.at(i);
                if (hashmap.get("_id") != null) {
                    hashmap.remove("_id");
                }
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
                java.util.Enumeration enumeration1 = hashmap.keys();
                for (int j = 0; enumeration1.hasMoreElements(); j ++) {
                    String s2 = (String) enumeration1.nextElement();
                    assinstanceproperty[j] = new SSInstanceProperty(s2, hashmap.get(s2));
                }

                api.update(s1, assinstanceproperty);
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = api.getInstanceProperties(s1, com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL);
                hashmap1 = new HashMap();
                for (int k = 0; k < assinstanceproperty1.length; k ++) {
                    hashmap1.put(assinstanceproperty1[k].getName(), assinstanceproperty1[k].getValue());
                }

                hashmap1.put("_id", s1);
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
            String s = "";
            java.util.Vector vector = new Vector();
            String as[];
            for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); vector.add(as)) {
                String s1 = (String) enumeration.nextElement();
                api.delete(s1);
                as = new String[2];
                as[0] = s1;
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object move(jgl.Array array, jgl.Array array1, jgl.Array array2) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Enumeration enumeration = array.elements();
            int i = 0;
            String s = "";
            String s2 = "";
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue;
            for (; enumeration.hasMoreElements(); vector.add(ssstringreturnvalue.getValue())) {
                String s1 = (String) enumeration.nextElement();
                String s3 = (String) array2.at(i);
                ssstringreturnvalue = api.move(s1, s3);
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object copy(String s, String s1, String s2) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = api.copy(s, s2);
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = api.getInstanceProperties(ssstringreturnvalue.getValue(), com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL);
            jgl.HashMap hashmap = new HashMap();
            for (int i = 0; i < assinstanceproperty.length; i ++) {
                hashmap.put(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
            }

            hashmap.put("_id", ssstringreturnvalue.getValue());
            vector.add(hashmap);
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
            com.dragonflow.Api.SSPropertyDetails asspropertydetails[] = api.getClassPropertiesDetails(com.dragonflow.Api.APISiteView.FILTER_ALL);
            for (int i = 0; i < asspropertydetails.length; i ++) {
                jgl.HashMap hashmap1 = new HashMap();
                com.dragonflow.Api.SSPropertyDetails.extractDetailsIntoHashMap(asspropertydetails[i], hashmap1);
                if (s.indexOf(asspropertydetails[i].getName()) != -1) {
                    vector.add(hashmap1);
                }
            }

            xmlapiresponse.setReturnVector(vector);
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
            com.dragonflow.Api.SSPropertyDetails sspropertydetails = api.getClassPropertyDetails(s);
            vector.add(sspropertydetails.getName());
            vector.add(sspropertydetails.getSelectionIDs());
            vector.add(sspropertydetails.getSelectionDisplayNames());
            xmlapiresponse.setReturnVector(vector);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getInstancePropertyScalars(String s, String s1, String s2, jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSPropertyDetails sspropertydetails = api.getInstancePropertyScalars(s, s1);
            vector.add(sspropertydetails.getName());
            vector.add(sspropertydetails.getSelectionIDs());
            vector.add(sspropertydetails.getSelectionDisplayNames());
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getInstances(String s, String s1, String s2, String s3, Integer integer) throws Exception {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSGroupInstance assgroupinstance[] = api.getInstances(s, integer.intValue());
            if (apiAlert == null) {
                apiAlert = new APIAlert();
            }
            for (int i = 0; i < assgroupinstance.length; i ++) {
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = assgroupinstance[i].getInstanceProperties();
                jgl.HashMap hashmap = new HashMap();
                for (int j = 0; j < assinstanceproperty.length; j ++) {
                    hashmap.put(assinstanceproperty[j].getName(), assinstanceproperty[j].getValue());
                }

                String s4 = assgroupinstance[i].getGroupId();
                hashmap.put("_id", s4);
                if (com.dragonflow.Api.Alert.getInstance().getAlertsResidingInGroupOrMonitor(s, "").size() > 0) {
                    hashmap.put("hasDependencies", "true");
                }
                if (s.length() == 0 || api.hasSubGroupDependencies(s4)) {
                    hashmap.put("hasSubGroupDependencies", "true");
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
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = api.getInstanceProperties(s, integer.intValue());
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

    public Object refreshGroup(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.refreshGroup(s, true);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getInstanceProperty(String s, String s1, String s2, String s3, Integer integer) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = api.getInstanceProperties(s1, integer.intValue());
            jgl.HashMap hashmap = new HashMap();
            for (int i = 0; i < assinstanceproperty.length; i ++) {
                if (s.indexOf(assinstanceproperty[i].getName()) != -1) {
                    hashmap.put(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
                }
            }

            vector.add(hashmap);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getCount(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            java.util.Collection collection = api.getAllGroupInstances();
            Long long1 = new Long(collection.size());
            vector.add(long1);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

//    public Object getTopazId(String s, String s1) {
//        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            java.util.Vector vector = new Vector();
//            com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = api.getTopazID(s);
//            vector.add(ssstringreturnvalue.getValue());
//            xmlapiresponse.setReturnVector(vector);
//        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
//            xmlapiresponse.setErrorResponse(siteviewexception);
//        }
//        return xmlapiresponse;
//    }

    public Object listObjects(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        java.util.Vector vector = new Vector();
        String as[] = null;
        as = new String[3];
        as[0] = "Group";
        as[1] = "yes";
        as[2] = "yes";
        vector.add(as);
        xmlapiresponse.setReturnVector(vector);
        return xmlapiresponse;
    }
}
