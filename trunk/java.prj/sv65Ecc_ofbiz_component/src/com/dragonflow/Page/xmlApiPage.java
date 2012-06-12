/*
 * 
 * Created on 2005-3-9 22:12:36
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Page;

import com.dragonflow.XmlApi.XmlApiRequestXML;

// Referenced classes of package com.dragonflow.Page:
// CGI

public class xmlApiPage extends com.dragonflow.Page.CGI {

    public xmlApiPage() {
    }

    public void printBody() {
        String s = request.getValue("_login");
        String s1 = request.getValue("_password");
        String s2 = request.getValue("account");
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig
                .getMasterConfig();
        String s3 = "";
        String s6 = null;
        if (com.dragonflow.Utils.I18N.isI18N) {
            try {
                s6 = com.dragonflow.Utils.I18N.toNullEncoding(new String(request
                        .getValue("xml").getBytes("Cp437"), "UTF-8"));
            } catch (java.io.UnsupportedEncodingException unsupportedencodingexception) {
            }
            if (s6 == null) {
                s6 = request.getValue("xml");
            }
        } else {
            s6 = request.getValue("xml");
        }
        Boolean boolean1 = new Boolean(request
                .getValue("licenseExpired"));
        System.out.println("APIRequest: \r\n" + s6);
        com.dragonflow.XmlApi.XmlApiRequestXML xmlapirequestxml = new XmlApiRequestXML(
                s6);
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject = (com.dragonflow.XmlApi.XmlApiObject) xmlapirequestxml
                .getAPIRequest();
        java.util.Enumeration enumeration = xmlapiobject.elements();
        com.dragonflow.XmlApi.XmlApiObject xmlapiobject1 = (com.dragonflow.XmlApi.XmlApiObject) enumeration
                .nextElement();
        String s7 = xmlapiobject1.getName();
        if (!boolean1.booleanValue() || s7.equals("updateLicense")) {
            if (s2.length() == 0) {
                s2 = "administrator";
            }
            com.dragonflow.SiteView.User user = com.dragonflow.SiteView.User
                    .getUserForAccount(s2);
            if (user != null) {
                if (user.getProperty("_login").equalsIgnoreCase(s)
                        && user.getProperty("_password").equals(s1)) {
                    if (user.getProperty("_disabled").length() > 0) {
                        if (com.dragonflow.Utils.TextUtils.getValue(hashmap,
                                "_loginDisabledMessage").length() > 0) {
                            s3 = com.dragonflow.Utils.TextUtils.getValue(
                                    hashmap, "_loginDisabledMessage");
                        }
                        if (s3.length() == 0) {
                            s3 = "This account has been disabled.";
                        }
                        xmlapiobject.setProperty("errortype", "operational",
                                false);
                        xmlapiobject
                                .setProperty(
                                        "errorcode",
                                        (new Long(
                                                com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ACCOUNT_DISABLED))
                                                .toString(), false);
                        xmlapiobject.setProperty("error", s3, false);
                    } else {
                        xmlapirequestxml.doRequests();
                    }
                } else {
                    if (com.dragonflow.Utils.TextUtils.getValue(hashmap,
                            "_loginIncorrectMessage").length() > 0) {
                        s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap,
                                "_loginIncorrectMessage");
                    }
                    if (s3.length() == 0) {
                        s3 = "Login incorrect for account: " + s2;
                    }
                    xmlapiobject.setProperty("errortype", "operational", false);
                    xmlapiobject
                            .setProperty(
                                    "errorcode",
                                    (new Long(
                                            com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_LOGIN_INCORRECT))
                                            .toString(), false);
                    xmlapiobject.setProperty("error", s3, false);
                }
            } else {
                String s4 = com.dragonflow.Resource.SiteViewResource
                        .getFormattedString(
                                (new Long(
                                        com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ACCOUNT_DOES_NOT_EXIST))
                                        .toString(), new String[0]);
                xmlapiobject.setProperty("errortype", "operational", false);
                xmlapiobject
                        .setProperty(
                                "errorcode",
                                (new Long(
                                        com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ACCOUNT_DOES_NOT_EXIST))
                                        .toString(), false);
                xmlapiobject.setProperty("error", s4, false);
            }
        } else {
            String s5 = com.dragonflow.Resource.SiteViewResource
                    .getFormattedString(
                            (new Long(
                                    com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_LICENSE_EXPIRED))
                                    .toString(), new String[0]);
            xmlapiobject.setProperty("errortype", "operational", false);
            xmlapiobject
                    .setProperty(
                            "errorcode",
                            (new Long(
                                    com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_LICENSE_EXPIRED))
                                    .toString(), false);
            xmlapiobject.setProperty("error", s5, false);
        }
        xmlapirequestxml.setAPIRequest(xmlapiobject);
        String s8 = (String) xmlapirequestxml
                .getResponse(false);
        System.out.println("APIResponse: \r\n" + s8);
        outputStream.println(s8);
    }
}
