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
import com.dragonflow.Api.APIMonitor;
import com.dragonflow.Api.SSInstanceProperty;

// Referenced classes of package com.dragonflow.XmlApi:
// XmlApiResponse

public class XmlApiMonitor {

    private com.dragonflow.Api.APIMonitor api;

    private com.dragonflow.Api.APIAlert apiAlert;

    public XmlApiMonitor() {
        api = null;
        apiAlert = null;
        api = new APIMonitor();
    }

    public java.lang.Object add(jgl.Array array, jgl.Array array1, jgl.Array array2, java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            int i = 0;
            java.util.Vector vector = new Vector();
            java.lang.String s1 = "";
            java.lang.String s3 = "";
            java.lang.String s5 = "";
            java.lang.String s6 = "";
            for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements();) {
                java.lang.String s2 = (java.lang.String) enumeration.nextElement();
                java.lang.String s4 = (java.lang.String) array1.at(i);
                jgl.HashMap hashmap = (jgl.HashMap) array2.at(i);
                java.lang.Boolean boolean1 = new Boolean(false);
                java.lang.String s7 = "10000";
                if ((java.lang.String) hashmap.get("wsdlfile") != null) {
                    s5 = (java.lang.String) hashmap.get("wsdlfile");
                }
                if ((java.lang.String) hashmap.get("webserviceurl") != null) {
                    s6 = (java.lang.String) hashmap.get("webserviceurl");
                }
                if ((java.lang.String) hashmap.get("runMonitor") != null) {
                    boolean1 = new Boolean((java.lang.String) hashmap.get("runMonitor"));
                    hashmap.remove("runMonitor");
                }
                if ((java.lang.String) hashmap.get("runTimeout") != null) {
                    s7 = (java.lang.String) hashmap.get("runTimeout");
                    hashmap.remove("runTimeout");
                }
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
                java.util.Enumeration enumeration1 = hashmap.keys();
                for (int j = 0; enumeration1.hasMoreElements(); j ++) {
                    java.lang.String s8 = (java.lang.String) enumeration1.nextElement();
                    assinstanceproperty[j] = new SSInstanceProperty(s8, hashmap.get(s8));
                }

                com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = api.create(s2, s4, assinstanceproperty);
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = null;
                if (!boolean1.booleanValue()) {
                    assinstanceproperty1 = api.getInstanceProperties(ssstringreturnvalue.getValue(), s4, com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL);
                } else {
                    com.dragonflow.Api.SSMonitorInstance ssmonitorinstance = api.runExisting(ssstringreturnvalue.getValue(), s4, (new Long(s7)).longValue());
                    assinstanceproperty1 = ssmonitorinstance.getInstanceProperties();
                }
                jgl.HashMap hashmap1 = new HashMap();
                for (int k = 0; k < assinstanceproperty1.length; k ++) {
                    hashmap1.put(assinstanceproperty1[k].getName(), assinstanceproperty1[k].getValue());
                }

                if (s2.equals("WebServiceMonitor")) {
                    hashmap1.put("wsdlfile", s5);
                    hashmap1.put("webserviceurl", s6);
                }
                vector.add(hashmap1);
                i ++;
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object delete(jgl.Array array, jgl.Array array1, jgl.Array array2, jgl.Array array3) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            int i = 0;
            java.lang.String s = "";
            java.lang.String s2 = "";
            for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements();) {
                java.lang.String s1 = (java.lang.String) enumeration.nextElement();
                java.lang.String s3 = (java.lang.String) array1.at(i);
                api.delete(s1, s3);
                java.lang.String as[] = new java.lang.String[2];
                as[0] = s1;
                as[1] = s3;
                vector.add(as);
                i ++;
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object move(jgl.Array array, jgl.Array array1, jgl.Array array2) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            int i = 0;
            java.lang.String s = "";
            java.lang.String s2 = "";
            java.lang.String s4 = "";
            java.lang.String s1;
            java.lang.String s3;
            java.lang.String s5;
            for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); vector.add(api.move(s3, s1, s5))) {
                s3 = (java.lang.String) enumeration.nextElement();
                s1 = (java.lang.String) array1.at(i);
                s5 = (java.lang.String) array2.at(i);
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object copy(java.lang.String s, java.lang.String s1, java.lang.String s2) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = api.copy(s, s1, s2);
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = api.getInstanceProperties(ssstringreturnvalue.getValue(), s2, com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL, true);
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

    public java.lang.Object runExisting(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.Boolean boolean1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            jgl.HashMap hashmap = new HashMap();
            com.dragonflow.Api.SSMonitorInstance ssmonitorinstance = null;
            if (boolean1 != null) {
                ssmonitorinstance = api.runExisting(s, s1, (new Long(s2)).longValue(), boolean1.booleanValue());
            } else {
                ssmonitorinstance = api.runExisting(s, s1, (new Long(s2)).longValue(), false);
            }
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = ssmonitorinstance.getInstanceProperties();
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

    /**
     * @deprecated Method runTemporary is deprecated
     */

    public java.lang.Object runTemporary(jgl.Array array, jgl.Array array1, jgl.Array array2, jgl.Array array3, jgl.Array array4) {
        return runTemporary(array, array2, array3, array4);
    }

    public java.lang.Object runTemporary(jgl.Array array, jgl.Array array1, jgl.Array array2, jgl.Array array3) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            int i = 0;
            java.util.Vector vector = new Vector();
            java.lang.String s = "";
            java.lang.String s2 = "";
            java.lang.String s4 = "";
            for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements();) {
                java.lang.String s1 = (java.lang.String) enumeration.nextElement();
                java.lang.String s3 = (java.lang.String) array2.at(i);
                java.lang.String s5 = (java.lang.String) array3.at(i);
                jgl.HashMap hashmap = (jgl.HashMap) array1.at(i);
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
                java.util.Enumeration enumeration1 = hashmap.keys();
                for (int j = 0; enumeration1.hasMoreElements(); j ++) {
                    java.lang.String s6 = (java.lang.String) enumeration1.nextElement();
                    assinstanceproperty[j] = new SSInstanceProperty(s6, hashmap.get(s6));
                }

                com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = null;
                if (s5 != null) {
                    assinstanceproperty1 = api.runTemporary(s1, assinstanceproperty, (new Long(s3)).longValue(), (new Boolean(s5)).booleanValue());
                } else {
                    assinstanceproperty1 = api.runTemporary(s1, assinstanceproperty, (new Long(s3)).longValue(), false);
                }
                jgl.HashMap hashmap1 = new HashMap();
                for (int k = 0; k < assinstanceproperty1.length; k ++) {
                    hashmap1.put(assinstanceproperty1[k].getName(), assinstanceproperty1[k].getValue());
                }

                vector.add(hashmap1);
                i ++;
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object addBrowsableCounters(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            java.util.HashMap hashmap1 = com.dragonflow.Utils.jglUtils.fromJgl(hashmap);
            api.addBrowsableCounters(s, s1, hashmap1);
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = api.getInstanceProperties(s, s1, com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL_NOT_EMPTY);
            jgl.HashMap hashmap2 = new HashMap();
            for (int i = 0; i < assinstanceproperty.length; i ++) {
                hashmap2.put(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
            }

            vector.add(hashmap2);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object removeBrowsableCounters(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            java.util.HashMap hashmap1 = com.dragonflow.Utils.jglUtils.fromJgl(hashmap);
            api.removeBrowsableCounters(s, s1, hashmap1);
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = api.getInstanceProperties(s, s1, com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL_NOT_EMPTY);
            jgl.HashMap hashmap2 = new HashMap();
            for (int i = 0; i < assinstanceproperty.length; i ++) {
                hashmap2.put(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
            }

            vector.add(hashmap2);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getClassPropertiesDetails(java.lang.String s, jgl.HashMap hashmap, java.lang.Integer integer) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
            java.util.Enumeration enumeration = hashmap.keys();
            for (int i = 0; enumeration.hasMoreElements(); i ++) {
                java.lang.String s1 = (java.lang.String) enumeration.nextElement();
                java.lang.String s2 = (java.lang.String) hashmap.get(s1);
                assinstanceproperty[i] = new SSInstanceProperty(s1, s2);
            }

            com.dragonflow.Api.SSPropertyDetails asspropertydetails[] = api.getClassPropertiesDetails(s, integer.intValue(), assinstanceproperty);
            for (int j = 0; j < asspropertydetails.length; j ++) {
                jgl.HashMap hashmap1 = new HashMap();
                com.dragonflow.Api.SSPropertyDetails.extractDetailsIntoHashMap(asspropertydetails[j], hashmap1);
                vector.add(hashmap1);
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getClassPropertyDetails(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
            java.util.Enumeration enumeration = hashmap.keys();
            for (int i = 0; enumeration.hasMoreElements(); i ++) {
                java.lang.String s2 = (java.lang.String) enumeration.nextElement();
                java.lang.String s3 = (java.lang.String) hashmap.get(s2);
                assinstanceproperty[i] = new SSInstanceProperty(s2, s3);
            }

            java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s, ",");
            for (int j = 0; j < as.length; j ++) {
                com.dragonflow.Api.SSPropertyDetails sspropertydetails = api.getClassPropertyDetails(as[j], s1, assinstanceproperty);
                jgl.HashMap hashmap1 = new HashMap();
                com.dragonflow.Api.SSPropertyDetails.extractDetailsIntoHashMap(sspropertydetails, hashmap1);
                vector.add(hashmap1);
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getClassPropertyScalars(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
            java.util.Enumeration enumeration = hashmap.keys();
            for (int i = 0; enumeration.hasMoreElements(); i ++) {
                java.lang.String s2 = (java.lang.String) enumeration.nextElement();
                java.lang.String s3 = (java.lang.String) hashmap.get(s2);
                assinstanceproperty[i] = new SSInstanceProperty(s2, s3);
            }

            com.dragonflow.Api.SSPropertyDetails sspropertydetails = api.getClassPropertyDetails(s, s1, assinstanceproperty);
            vector.add(sspropertydetails.getName());
            vector.add(sspropertydetails.getSelectionIDs());
            vector.add(sspropertydetails.getSelectionDisplayNames());
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getInstancePropertyScalars(java.lang.String s, java.lang.String s1, java.lang.String s2, jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
            java.util.Enumeration enumeration = hashmap.keys();
            for (int i = 0; enumeration.hasMoreElements(); i ++) {
                java.lang.String s3 = (java.lang.String) enumeration.nextElement();
                java.lang.String s4 = (java.lang.String) hashmap.get(s3);
                assinstanceproperty[i] = new SSInstanceProperty(s3, s4);
            }

            com.dragonflow.Api.SSPropertyDetails sspropertydetails = api.getInstancePropertyDetails(s, s1, s2);
            vector.add(sspropertydetails.getName());
            vector.add(sspropertydetails.getSelectionIDs());
            vector.add(sspropertydetails.getSelectionDisplayNames());
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getInstancePropertyDetails(java.lang.String s, java.lang.String s1, java.lang.String s2, jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
            java.util.Enumeration enumeration = hashmap.keys();
            for (int i = 0; enumeration.hasMoreElements(); i ++) {
                java.lang.String s3 = (java.lang.String) enumeration.nextElement();
                java.lang.String s4 = (java.lang.String) hashmap.get(s3);
                assinstanceproperty[i] = new SSInstanceProperty(s3, s4);
            }

            java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s, " ,");
            for (int j = 0; j < as.length; j ++) {
                com.dragonflow.Api.SSPropertyDetails sspropertydetails = api.getInstancePropertyDetails(as[j], s1, s2);
                jgl.HashMap hashmap1 = new HashMap();
                com.dragonflow.Api.SSPropertyDetails.extractDetailsIntoHashMap(sspropertydetails, hashmap1);
                vector.add(hashmap1);
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getInstances(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.Integer integer) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSMonitorInstance assmonitorinstance[] = api.getInstances(s, integer.intValue());
            if (apiAlert == null) {
                apiAlert = new APIAlert();
            }
            for (int i = 0; i < assmonitorinstance.length; i ++) {
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = assmonitorinstance[i].getInstanceProperties();
                jgl.HashMap hashmap = new HashMap();
                for (int j = 0; j < assinstanceproperty.length; j ++) {
                    hashmap.put(assinstanceproperty[j].getName(), assinstanceproperty[j].getValue());
                }

                java.lang.String s4 = (java.lang.String) hashmap.get("_id");
                java.lang.String s5 = s;
                if (com.dragonflow.Api.Alert.getInstance().getAlertsResidingInGroupOrMonitor(s5, s4).size() > 0) {
                    hashmap.put("hasDependencies", "true");
                }
                vector.add(hashmap);
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getInstanceProperties(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.Integer integer) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = api.getInstanceProperties(s, s1, integer.intValue());
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

    public java.lang.Object getInstanceProperty(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.Integer integer) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            jgl.HashMap hashmap = new HashMap();
            java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s, " ,");
            for (int i = 0; i < as.length; i ++) {
                com.dragonflow.Api.SSInstanceProperty ssinstanceproperty = api.getInstanceProperty(as[i], s1, s2);
                hashmap.put(as[i], ssinstanceproperty.getValue());
            }

            vector.add(hashmap);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object update(jgl.Array array, jgl.Array array1, jgl.Array array2, jgl.Array array3, jgl.Array array4) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            int i = 0;
            java.lang.String s = "";
            java.lang.String s2 = "";
            java.lang.String s4 = "";
            java.lang.String s5 = "";
            Object obj = null;
            for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements();) {
                java.lang.String s1 = (java.lang.String) enumeration.nextElement();
                java.lang.String s3 = (java.lang.String) array1.at(i);
                jgl.HashMap hashmap = (jgl.HashMap) array2.at(i);
                if ((java.lang.String) hashmap.get("wsdlfile") != null) {
                    s4 = (java.lang.String) hashmap.get("wsdlfile");
                }
                if ((java.lang.String) hashmap.get("webserviceurl") != null) {
                    s5 = (java.lang.String) hashmap.get("webserviceurl");
                }
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
                java.util.Enumeration enumeration1 = hashmap.keys();
                for (int j = 0; enumeration1.hasMoreElements(); j ++) {
                    java.lang.String s6 = (java.lang.String) enumeration1.nextElement();
                    assinstanceproperty[j] = new SSInstanceProperty(s6, hashmap.get(s6));
                }

                api.update(s1, s3, assinstanceproperty);
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = api.getInstanceProperties(s1, s3, com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL);
                jgl.HashMap hashmap1 = new HashMap();
                for (int k = 0; k < assinstanceproperty1.length; k ++) {
                    hashmap1.put(assinstanceproperty1[k].getName(), assinstanceproperty1[k].getValue());
                }

                com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                s3 = com.dragonflow.Utils.I18N.toDefaultEncoding(s3);
                com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup) siteviewgroup.getElementByID(s3);
                com.dragonflow.SiteView.AtomicMonitor atomicmonitor = null;
                java.util.Enumeration enumeration2 = monitorgroup.getMonitors();
                while (enumeration2.hasMoreElements()) {
                    com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor) enumeration2.nextElement();
                    if ((s1 != null) & s1.equals(s1)) {
                    atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor) monitor;
                    break;
                    }
                } 
                if (atomicmonitor != null) {
                    java.lang.String s7 = atomicmonitor.getClass().toString();
                    int l = s7.lastIndexOf(".");
                    if (l != -1) {
                        s7 = s7.substring(l + 1);
                    }
                    if (s7.equals("WebServiceMonitor")) {
                        hashmap1.put("wsdlfile", s4);
                        hashmap1.put("webserviceurl", s5);
                    }
                }
                vector.add(hashmap1);
                i ++;
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getURLStepProperties(jgl.Array array, jgl.Array array1, jgl.Array array2, jgl.Array array3) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            int i = 0;
            java.util.Vector vector = new Vector();
            java.lang.String s = "";
            java.lang.String s2 = "";
            java.lang.String s4 = "";
            for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements();) {
                java.lang.String s1 = (java.lang.String) enumeration.nextElement();
                java.lang.String s3 = (java.lang.String) array1.at(i);
                java.lang.String s5 = (java.lang.String) array3.at(i);
                java.util.HashMap hashmap = (java.util.HashMap) array2.at(i);
                com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = new com.dragonflow.Api.SSInstanceProperty[hashmap.size()];
                java.util.Set set = hashmap.keySet();
                java.util.Iterator iterator = set.iterator();
                for (int j = 0; iterator.hasNext(); j ++) {
                    java.lang.String s6 = (java.lang.String) iterator.next();
                    assinstanceproperty[j] = new SSInstanceProperty(s6, hashmap.get(s6));
                }

                com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = api.getURLStepProperties(s1, s3, assinstanceproperty, s5);
                jgl.HashMap hashmap1 = new HashMap();
                for (int k = 0; k < assinstanceproperty1.length; k ++) {
                    hashmap1.put(assinstanceproperty1[k].getName(), assinstanceproperty1[k].getValue());
                }

                vector.add(hashmap1);
                i ++;
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getObjects(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSStringReturnValue assstringreturnvalue[] = api.getMonitorTypes();
            for (int i = 0; i < assstringreturnvalue.length; i ++) {
                vector.add(assstringreturnvalue[i].getValue());
            }

            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getTopazId(java.lang.String s, java.lang.String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = api.getTopazID(s, s1);
            vector.add(ssstringreturnvalue.getValue());
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getCount() {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            java.util.Collection collection = api.getAllMonitors();
            java.lang.Long long1 = new Long(collection.size());
            vector.add(long1);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object resetCounters(java.lang.String s, java.lang.String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            jgl.HashMap hashmap = new HashMap();
            com.dragonflow.Api.SSMonitorInstance ssmonitorinstance = api.resetCounters(s, s1);
            com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = ssmonitorinstance.getInstanceProperties();
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
}
