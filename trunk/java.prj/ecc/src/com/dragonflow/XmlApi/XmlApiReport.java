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

import com.dragonflow.Api.APIReport;

// Referenced classes of package com.dragonflow.XmlApi:
// XmlApiResponse

public class XmlApiReport {

    private com.dragonflow.Api.APIReport api;

    public XmlApiReport() {
        api = null;
        api = new APIReport();
    }

    public java.lang.Object add(jgl.Array array, jgl.Array array1, jgl.Array array2, java.lang.String s) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            int i = 0;
            Object obj = null;
            java.util.Enumeration enumeration = array.elements();
            java.util.Vector vector = new Vector();
            while (enumeration.hasMoreElements()) {
                java.lang.String s1 = (java.lang.String) enumeration.nextElement();
                java.lang.String s2 = (java.lang.String) array1.at(i);
                jgl.HashMap hashmap = (jgl.HashMap) array2.at(i);
                api.create(s1, s2, hashmap);
                vector.add(hashmap);
                i ++;
            }
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object update(jgl.Array array, jgl.Array array1, jgl.Array array2, jgl.Array array3, jgl.Array array4) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            int i = 0;
            Object obj = null;
            java.util.Enumeration enumeration = array.elements();
            java.util.Vector vector = new Vector();
            while (enumeration.hasMoreElements()) {
                java.lang.String s = (java.lang.String) enumeration.nextElement();
                java.lang.String s1 = (java.lang.String) array1.at(i);
                jgl.HashMap hashmap = (jgl.HashMap) array2.at(i);
                api.update(s, s1, hashmap);
                vector.add(hashmap);
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
            int i = 0;
            java.util.Enumeration enumeration = array.elements();
            java.util.Vector vector = new Vector();
            while (enumeration.hasMoreElements()) {
                java.lang.String s = (java.lang.String) enumeration.nextElement();
                java.lang.String s1 = (java.lang.String) array1.at(i);
                api.delete("", s1, com.dragonflow.Utils.TextUtils.toInt(s));
                java.lang.String as[] = new java.lang.String[2];
                as[0] = s;
                as[1] = s1;
                vector.add(as);
                i ++;
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
            java.util.Vector vector = api.getTemplateList();
            java.lang.String as[] = new java.lang.String[vector.size()];
            java.lang.String as1[] = new java.lang.String[vector.size()];
            for (int i = 0; i < vector.size(); i ++) {
                java.lang.String as2[] = (java.lang.String[]) vector.get(i);
                as[i] = as2[0];
                as1[i] = as2[1];
            }

            java.util.Vector vector1 = new Vector();
            vector1.add(s);
            vector1.add(as);
            vector1.add(as1);
            xmlapiresponse.setReturnVector(vector1);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }

    public java.lang.Object getInstances(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.Integer integer) {
        com.dragonflow.XmlApi.XmlApiResponse xmlapiresponse = new XmlApiResponse();
        try {
            java.util.Vector vector = api.getInstances(s1, s, integer.intValue());
            xmlapiresponse.setReturnVector(vector);
        } catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
            xmlapiresponse.setErrorResponse(siteviewexception);
        }
        return xmlapiresponse;
    }
}
