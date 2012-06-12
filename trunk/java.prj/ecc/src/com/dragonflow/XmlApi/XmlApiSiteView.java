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

import java.util.HashMap;
import java.util.Vector;

import com.dragonflow.Api.APISiteView;

// Referenced classes of package com.dragonflow.XmlApi:
// XmlApiResponse

public class XmlApiSiteView {

    private com.dragonflow.Api.APISiteView api;

    public XmlApiSiteView() {
        api = null;
        api = new APISiteView();
    }

    public java.lang.Object enableRealTimeStatusInformation(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4, java.lang.String s5) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.enableRealTimeStatusInformation(s, java.lang.Integer.parseInt(s1), s2, java.lang.Integer.parseInt(s3), java.lang.Long.parseLong(s4), s5);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object disableRealTimeStatusInformation(java.lang.String s, java.lang.String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.disableRealTimeStatusInformation(s, java.lang.Integer.parseInt(s1));
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object controlSiteView(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.controlSiteView(s);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object releaseSiteView(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.releaseSiteView();
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getSiteViewInfo(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getSiteViewInfo(s);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getWebServers(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getWebServers(s);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getOSs(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getOSs();
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getWebServiceFiles(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getWebServiceFiles();
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getWebServiceMethodsAndURL(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getWebServiceMethodsAndURL(s);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getWebServiceArgs(java.lang.String s, java.lang.String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getWebServiceArgs(s, s1);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object shutdownSiteView(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.shutdownSiteView();
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object createSession(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.createSession((new Long(s)).longValue());
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object sendHeartbeat(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.sendHeartbeat();
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object updateGeneralLicense(java.lang.String s, java.lang.String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.updateGeneralLicense(s, (new Boolean(s1)).booleanValue());
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object updateSpecialLicense(java.lang.String s, java.lang.String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.updateSpecialLicense(s, (new Boolean(s1)).booleanValue());
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object isTopazDisabled(java.lang.String s, java.lang.String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            java.util.Vector vector = new Vector();
////            boolean flag = api.isTopazDisabled(s);
//            vector.add(new Boolean(flag));
//            xmlapiresponse.setReturnVector(vector);
//        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
//            xmlapiresponse.setErrorResponse(siteviewexception);
//        }
//        return xmlapiresponse;
		return null;
    }

    public java.lang.Object setTopazDisabled(java.lang.String s, java.lang.String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.setTopazDisabled(s, (new Boolean(s1)).booleanValue());
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object isTopazConnected(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            boolean flag = api.isTopazConnected();
            vector.add(new Boolean(flag));
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object isUIControled(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            boolean flag = api.isUIControled();
            vector.add(new Boolean(flag));
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object isServerRegistered(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            boolean flag = api.isServerRegistered(s);
            vector.add(new Boolean(flag));
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getFreeProfiles(jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.HashMap hashmap1 = new HashMap();
            java.lang.String s;
            java.lang.String s1;
            for (java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements(); hashmap1.put(s, s1)) {
                s = (java.lang.String) enumeration.nextElement();
                s1 = (java.lang.String) hashmap.get(s);
            }

            api.getFreeProfiles(hashmap1);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object flushTopazData(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.flushTopazData();
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object resyncTopazData(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.resyncTopazData((new Boolean(s)).booleanValue());
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object resetTopazProfile(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            api.resetTopazProfile(s);
//        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
//            xmlapiresponse.setErrorResponse(siteviewexception);
//        }
//        return xmlapiresponse;
		return null;
    }

    public java.lang.Object deleteSiteView(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.deleteSiteView(s);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getServerSettingsByEntity(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            java.util.Vector vector = new Vector();
//            java.util.HashMap hashmap = api.getServerSettingsByEntity(s);
//            if (hashmap != null) {
//                jgl.HashMap hashmap1 = new jgl.HashMap();
//                java.util.Set set = hashmap.keySet();
//                java.lang.String s1;
//                for (java.util.Iterator iterator = set.iterator(); iterator.hasNext(); hashmap1.put(s1, hashmap.get(s1))) {
//                    s1 = (java.lang.String) iterator.next();
//                }
//
//                vector.add(hashmap1);
//            }
//            xmlapiresponse.setReturnVector(vector);
//        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
//            xmlapiresponse.setErrorResponse(siteviewexception);
//        }
//        return xmlapiresponse;
		return null;
    }

    public java.lang.Object getTopazServerSettings(java.lang.String s, java.lang.String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            java.util.Vector vector = new Vector();
//            java.util.HashMap hashmap = api.getTopazServerSettings(s);
//            if (hashmap != null) {
//                jgl.HashMap hashmap1 = new jgl.HashMap();
//                java.util.Set set = hashmap.keySet();
//                java.lang.String s2;
//                for (java.util.Iterator iterator = set.iterator(); iterator.hasNext(); hashmap1.put(s2, hashmap.get(s2))) {
//                    s2 = (java.lang.String) iterator.next();
//                }
//
//                vector.add(hashmap1);
//            }
//            xmlapiresponse.setReturnVector(vector);
//        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
//            xmlapiresponse.setErrorResponse(siteviewexception);
//        }
//        return xmlapiresponse;
      return null;
    }

    public java.lang.Object registerTopazProfile(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            java.util.HashMap hashmap1 = new HashMap();
//            java.lang.String s2;
//            java.lang.String s3;
//            for (java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements(); hashmap1.put(s2, s3)) {
//                s2 = (java.lang.String) enumeration.nextElement();
//                s3 = (java.lang.String) hashmap.get(s2);
//            }
//
////            api.registerTopazProfile(s, s1, hashmap1);
//        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
//            xmlapiresponse.setErrorResponse(siteviewexception);
//        }
//        return xmlapiresponse;
		return null;
    }

    public java.lang.Object reRegisterTopazProfile(jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            java.util.HashMap hashmap1 = new HashMap();
//            java.lang.String s;
//            java.lang.String s1;
//            for (java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements(); hashmap1.put(s, s1)) {
//                s = (java.lang.String) enumeration.nextElement();
//                s1 = (java.lang.String) hashmap.get(s);
//            }
//
//            api.reRegisterTopazProfile(hashmap1);
//        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
//            xmlapiresponse.setErrorResponse(siteviewexception);
//        }
//        return xmlapiresponse;
		return null;
    }
	

    public java.lang.Object getTopazFullId(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            java.util.Vector vector = new Vector();
//            java.lang.Integer integer = new Integer(s);
//            java.lang.String s1 = api.getTopazFullId(integer.intValue());
//            if (s1 != null && s1.length() > 0) {
//                vector.add(s1);
//            }
//            xmlapiresponse.setReturnVector(vector);
//        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
//            xmlapiresponse.setErrorResponse(siteviewexception);
//        }
//        return xmlapiresponse;
		return null;
    }

    public java.lang.Object refreshCache(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            com.dragonflow.Api.APISiteView.forceConfigurationRefresh();
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

//    public java.lang.Object issueSiebelCmd(java.lang.String s) {
//        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
////            java.util.Vector vector = api.issueSiebelCmd(s);
//            xmlapiresponse.setReturnVector(vector);
//        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
//            xmlapiresponse.setErrorResponse(siteviewexception);
//        }
//        return xmlapiresponse;
//    }

    public java.lang.Object getCurrentApiVersion(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        com.dragonflow.Api.APISiteView _tmp = api;
        double d = com.dragonflow.Api.APISiteView.getCurrentApiVersion();
        java.lang.String s1 = (new Double(d)).toString();
        java.util.Vector vector = new Vector();
        vector.add(s1);
        xmlapiresponse.setReturnVector(vector);
        return xmlapiresponse;
    }

    public java.lang.Object getSystemTime(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getSystemTime(s);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param s1
     * @return
     */
    public java.lang.Object getFileList(java.lang.String s, java.lang.String s1) {

        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector;
            java.lang.StringBuffer stringbuffer = new StringBuffer();
            vector = api.getFileList(s, s1, stringbuffer);
            if (stringbuffer.length() != 0) {
                xmlapiresponse.setError(stringbuffer.toString());
                return xmlapiresponse;
            }
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object hasSolutionLicense(java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = new Vector();
            boolean flag = api.hasSolutionLicense(s);
            vector.add(new Boolean(flag));
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }
}
