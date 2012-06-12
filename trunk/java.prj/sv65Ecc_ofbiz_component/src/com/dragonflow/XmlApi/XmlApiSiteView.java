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

    public Object enableRealTimeStatusInformation(String s, String s1, String s2, String s3, String s4, String s5) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.enableRealTimeStatusInformation(s, Integer.parseInt(s1), s2, Integer.parseInt(s3), Long.parseLong(s4), s5);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object disableRealTimeStatusInformation(String s, String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.disableRealTimeStatusInformation(s, Integer.parseInt(s1));
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object controlSiteView(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.controlSiteView(s);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object releaseSiteView(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.releaseSiteView();
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getSiteViewInfo(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getSiteViewInfo(s);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getWebServers(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getWebServers(s);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getOSs(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getOSs();
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getWebServiceFiles(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getWebServiceFiles();
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getWebServiceMethodsAndURL(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getWebServiceMethodsAndURL(s);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getWebServiceArgs(String s, String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getWebServiceArgs(s, s1);
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object shutdownSiteView(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.shutdownSiteView();
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object createSession(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.createSession((new Long(s)).longValue());
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object sendHeartbeat(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.sendHeartbeat();
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object updateGeneralLicense(String s, String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.updateGeneralLicense(s, (new Boolean(s1)).booleanValue());
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object updateSpecialLicense(String s, String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.updateSpecialLicense(s, (new Boolean(s1)).booleanValue());
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object isTopazDisabled(String s, String s1) {
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

    public Object setTopazDisabled(String s, String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.setTopazDisabled(s, (new Boolean(s1)).booleanValue());
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object isTopazConnected(String s) {
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

    public Object isUIControled(String s) {
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

    public Object isServerRegistered(String s) {
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

    public Object getFreeProfiles(jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.HashMap hashmap1 = new HashMap();
            String s;
            String s1;
            for (java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements(); hashmap1.put(s, s1)) {
                s = (String) enumeration.nextElement();
                s1 = (String) hashmap.get(s);
            }

            api.getFreeProfiles(hashmap1);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object flushTopazData(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.flushTopazData();
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object resyncTopazData(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.resyncTopazData((new Boolean(s)).booleanValue());
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object resetTopazProfile(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            api.resetTopazProfile(s);
//        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
//            xmlapiresponse.setErrorResponse(siteviewexception);
//        }
//        return xmlapiresponse;
		return null;
    }

    public Object deleteSiteView(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            api.deleteSiteView(s);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public Object getServerSettingsByEntity(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            java.util.Vector vector = new Vector();
//            java.util.HashMap hashmap = api.getServerSettingsByEntity(s);
//            if (hashmap != null) {
//                jgl.HashMap hashmap1 = new jgl.HashMap();
//                java.util.Set set = hashmap.keySet();
//                String s1;
//                for (java.util.Iterator iterator = set.iterator(); iterator.hasNext(); hashmap1.put(s1, hashmap.get(s1))) {
//                    s1 = (String) iterator.next();
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

    public Object getTopazServerSettings(String s, String s1) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            java.util.Vector vector = new Vector();
//            java.util.HashMap hashmap = api.getTopazServerSettings(s);
//            if (hashmap != null) {
//                jgl.HashMap hashmap1 = new jgl.HashMap();
//                java.util.Set set = hashmap.keySet();
//                String s2;
//                for (java.util.Iterator iterator = set.iterator(); iterator.hasNext(); hashmap1.put(s2, hashmap.get(s2))) {
//                    s2 = (String) iterator.next();
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

    public Object registerTopazProfile(String s, String s1, jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            java.util.HashMap hashmap1 = new HashMap();
//            String s2;
//            String s3;
//            for (java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements(); hashmap1.put(s2, s3)) {
//                s2 = (String) enumeration.nextElement();
//                s3 = (String) hashmap.get(s2);
//            }
//
////            api.registerTopazProfile(s, s1, hashmap1);
//        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
//            xmlapiresponse.setErrorResponse(siteviewexception);
//        }
//        return xmlapiresponse;
		return null;
    }

    public Object reRegisterTopazProfile(jgl.HashMap hashmap) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            java.util.HashMap hashmap1 = new HashMap();
//            String s;
//            String s1;
//            for (java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements(); hashmap1.put(s, s1)) {
//                s = (String) enumeration.nextElement();
//                s1 = (String) hashmap.get(s);
//            }
//
//            api.reRegisterTopazProfile(hashmap1);
//        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
//            xmlapiresponse.setErrorResponse(siteviewexception);
//        }
//        return xmlapiresponse;
		return null;
    }
	

    public Object getTopazFullId(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
//            java.util.Vector vector = new Vector();
//            Integer integer = new Integer(s);
//            String s1 = api.getTopazFullId(integer.intValue());
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

    public Object refreshCache(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            com.dragonflow.Api.APISiteView.forceConfigurationRefresh();
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

//    public Object issueSiebelCmd(String s) {
//        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
//        try {
////            java.util.Vector vector = api.issueSiebelCmd(s);
//            xmlapiresponse.setReturnVector(vector);
//        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
//            xmlapiresponse.setErrorResponse(siteviewexception);
//        }
//        return xmlapiresponse;
//    }

    public Object getCurrentApiVersion(String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        com.dragonflow.Api.APISiteView _tmp = api;
        double d = com.dragonflow.Api.APISiteView.getCurrentApiVersion();
        String s1 = (new Double(d)).toString();
        java.util.Vector vector = new Vector();
        vector.add(s1);
        xmlapiresponse.setReturnVector(vector);
        return xmlapiresponse;
    }

    public Object getSystemTime(String s) {
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
    public Object getFileList(String s, String s1) {

        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector;
            StringBuffer stringbuffer = new StringBuffer();
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

    public Object hasSolutionLicense(String s) {
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
