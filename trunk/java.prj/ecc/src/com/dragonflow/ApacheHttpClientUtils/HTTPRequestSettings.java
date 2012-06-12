/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.ApacheHttpClientUtils;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.util.Vector;

import org.apache.commons.httpclient.URI;

public class HTTPRequestSettings {

    public static final java.lang.String CONTENT_TYPE = "Content-Type";

    public static final java.lang.String CONTENT_TYPE_DEFAULT = "application/x-www-form-urlencoded";

    public static final int DEFAULT_PROXY_PORT = 80;

    private static final int DEFAULT_RECOVERABLE_RETRIES = 3;

    public static final java.lang.String CHARSET = "; charset=";

    public static final java.lang.String CHARSET_DEFAULT = "UTF-8";

    private java.lang.String url;

    private java.lang.String host;

    private int port;

    private java.lang.String scheme;

    private java.lang.String authUserName;

    private java.lang.String authPassword;

    private java.lang.String authNTLMDomain;

    private java.lang.Boolean authenticationOnFirstRequest;

    private java.lang.String proxy;

    private java.lang.String proxyHost;

    private int proxyPort;

    private java.lang.String proxyUserName;

    private java.lang.String proxyPassword;

    private java.lang.String proxyAuthDomain;

    private java.util.Vector headers;

    private int requestTimeoutMS;

    private int connectionTimeoutMS;

    private int retriesOnRecoverableException;

    private java.lang.String certFilename;

    private java.lang.String certPassword;

    private boolean http11;

    private java.util.Vector Cookies;

    private static int mTimeOutToConnectMS;

    private static int mTimeOutNoTrafficMS;

    private java.lang.Boolean acceptAllUntrustedCerts;

    private java.lang.Boolean acceptInvalidCerts;

    private boolean encodePostData;

    static final boolean $assertionsDisabled; /* synthetic field */

    public HTTPRequestSettings(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.Boolean boolean1, java.lang.String s4, java.lang.String s5, java.lang.String s6, java.util.Vector vector, int i, int j, int k) {
        url = null;
        host = "";
        port = 0;
        scheme = null;
        authUserName = null;
        authPassword = null;
        authNTLMDomain = "";
        authenticationOnFirstRequest = new Boolean(false);
        proxy = null;
        proxyHost = null;
        proxyPort = 80;
        proxyUserName = null;
        proxyPassword = null;
        proxyAuthDomain = "";
        headers = new Vector();
        requestTimeoutMS = -1;
        connectionTimeoutMS = -1;
        retriesOnRecoverableException = 3;
        certFilename = null;
        certPassword = null;
        http11 = true;
        Cookies = null;
        acceptAllUntrustedCerts = null;
        acceptInvalidCerts = null;
        encodePostData = true;
        setUrl(s);
        authUserName = s1;
        authPassword = s2;
        authNTLMDomain = s3;
        setAuthenticationOnFirstRequest(boolean1);
        proxy = s4;
        proxyUserName = s5;
        if (s5 != null && s5.length() > 0) {
            int l = s5.indexOf('\\');
            if (l != -1) {
                proxyAuthDomain = s5.substring(0, l);
                proxyUserName = s5.substring(l + 1, s5.length());
            }
        }
        proxyPassword = s6;
        if (vector != null) {
            headers.addAll(vector);
        }
        if (s4 != null && s4.length() > 0) {
            int i1 = s4.indexOf(':');
            if (i1 != -1) {
                proxyHost = s4.substring(0, i1);
                proxyPort = com.dragonflow.Utils.TextUtils.toInt(s4.substring(i1 + 1, s4.length()));
            } else {
                proxyHost = s4;
            }
        }
        retriesOnRecoverableException = i;
        connectionTimeoutMS = j;
        requestTimeoutMS = k;
    }

    public HTTPRequestSettings(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4, java.lang.String s5, java.lang.String s6, java.util.Vector vector) {
        this(s, s1, s2, s3, java.lang.Boolean.TRUE, s4, s5, s6, vector, 3, mTimeOutToConnectMS, mTimeOutNoTrafficMS);
    }

    public java.lang.String getUrl() {
        return url;
    }

    public int getPort() {
        return port;
    }

    public java.lang.String getScheme() {
        return scheme;
    }

    public java.lang.String getAuthUserName() {
        return authUserName;
    }

    public java.lang.String getAuthPassword() {
        return authPassword;
    }

    public java.lang.String getProxy() {
        return proxy;
    }

    public java.lang.String getProxyHost() {
        return proxyHost;
    }

    public int getProxyPort() {
        return proxyPort;
    }

    public java.lang.String getProxyUserName() {
        return proxyUserName;
    }

    public java.lang.String getProxyPassword() {
        return proxyPassword;
    }

    public java.util.Vector getHeaders() {
        return headers;
    }

    public java.lang.String getAuthNTLMDomain() {
        return authNTLMDomain;
    }

    public void setAuthNTLMDomain(java.lang.String s) {
        if (s != null) {
            authNTLMDomain = s;
        }
    }

    public java.lang.Boolean getAuthenticationOnFirstRequest() {
        return authenticationOnFirstRequest;
    }

    public void setAuthenticationOnFirstRequest(java.lang.Boolean boolean1) {
        authenticationOnFirstRequest = boolean1;
    }

    public java.lang.String getProxyAuthDomain() {
        return proxyAuthDomain;
    }

    public void setProxyAuthDomain(java.lang.String s) {
        proxyAuthDomain = s;
    }

    public void setUrl(java.lang.String s) {
        if (s == null || s.equals("")) {
            s = "/";
        }
        Object obj = null;
        try {
            org.apache.commons.httpclient.URI uri = new URI(s, com.dragonflow.Utils.I18N.getDefaultEncoding());
            s = s.trim();
            s = s.replaceAll(" ", "%20");
            url = s;
            if (uri.isAbsoluteURI()) {
                host = uri.getHost();
                port = uri.getPort();
                scheme = uri.getScheme();
            }
            if (scheme == null) {
                scheme = "";
            }
        } catch (org.apache.commons.httpclient.URIException uriexception) {
            throw new IllegalArgumentException("Invalid uri, which is the url: '" + s + "': " + uriexception.getMessage());
        }
    }

    public void setAuthUserName(java.lang.String s) {
        authUserName = s;
    }

    public void setAuthPassword(java.lang.String s) {
        authPassword = s;
    }

    public void setProxy(java.lang.String s) {
        proxy = s;
    }

    public void setProxyHost(java.lang.String s) {
        proxyHost = s;
    }

    public void setProxyPort(int i) {
        proxyPort = i;
    }

    public void setProxyUserName(java.lang.String s) {
        proxyUserName = s;
    }

    public void setProxyPassword(java.lang.String s) {
        proxyPassword = s;
    }

    public void setHeaders(java.util.Vector vector) {
        headers = vector;
    }

    public void addHeaders(java.util.Vector vector) {
        headers.addAll(vector);
    }

    public java.lang.String getHost() {
        return host;
    }

    public void setHost(java.lang.String s) {
        host = s;
    }

    public int getRetries() {
        return retriesOnRecoverableException;
    }

    public void setRetries(int i) {
        retriesOnRecoverableException = i;
    }

    public int getConnectionTimeoutMS() {
        if (connectionTimeoutMS > 0) {
            return connectionTimeoutMS;
        } else {
            return mTimeOutToConnectMS;
        }
    }

    public void setConnectionTimeoutMS(int i) {
        connectionTimeoutMS = i;
    }

    public int getRequestTimeoutMS() {
        if (mTimeOutNoTrafficMS > 0) {
            return requestTimeoutMS;
        } else {
            return mTimeOutNoTrafficMS;
        }
    }

    public void setRequestTimeoutMS(int i) {
        requestTimeoutMS = i;
    }

    public java.lang.String getCertFilename() {
        if (certFilename == null) {
            jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
            java.lang.String s = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_urlClientCert").trim();
            if (s.length() > 0) {
                certFilename = com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "templates.certificates" + java.io.File.separator + s;
            } else {
                certFilename = "";
            }
        }
        if (!$assertionsDisabled && certFilename == null) {
            throw new AssertionError();
        } else {
            return certFilename;
        }
    }

    public void setCertFilename(java.lang.String s) {
        certFilename = s;
    }

    public java.lang.String getCertPassword() {
        if (certPassword == null) {
            jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
            certPassword = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_urlClientCertPassword").trim();
        }
        if (!$assertionsDisabled && certPassword == null) {
            throw new AssertionError();
        } else {
            return certPassword;
        }
    }

    public void setCertPassword(java.lang.String s) {
        certPassword = s;
    }

    public boolean getHttp11() {
        return http11;
    }

    public void setHttp11(boolean flag) {
        http11 = flag;
    }

    public org.apache.commons.httpclient.Cookie[] getCookies() {
        if (Cookies != null) {
            org.apache.commons.httpclient.Cookie acookie[] = new org.apache.commons.httpclient.Cookie[Cookies.size()];
            Cookies.copyInto(acookie);
            return acookie;
        } else {
            return null;
        }
    }

    public void setCookies(java.util.Vector vector) {
        Cookies = vector;
    }

    public java.lang.Boolean getAcceptAllUntrustedCerts() {
        if (acceptAllUntrustedCerts == null) {
            jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
            acceptAllUntrustedCerts = new Boolean(com.dragonflow.Utils.TextUtils.getValue(hashmap, "_sslAcceptAllUntrustedCerts").trim().equalsIgnoreCase("true"));
        }
        if (!$assertionsDisabled && acceptAllUntrustedCerts == null) {
            throw new AssertionError();
        } else {
            return acceptAllUntrustedCerts;
        }
    }

    public void setAcceptAllUntrustedCerts(boolean flag) {
        acceptAllUntrustedCerts = new Boolean(flag);
    }

    public java.lang.Boolean getAcceptInvalidCerts() {
        if (acceptInvalidCerts == null) {
            jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
            acceptInvalidCerts = new Boolean(com.dragonflow.Utils.TextUtils.getValue(hashmap, "_sslAcceptInvalidCerts").trim().equalsIgnoreCase("true"));
        }
        if (!$assertionsDisabled && acceptInvalidCerts == null) {
            throw new AssertionError();
        } else {
            return acceptInvalidCerts;
        }
    }

    public void setAcceptInvalidCerts(boolean flag) {
        acceptInvalidCerts = new Boolean(flag);
    }

    public boolean getEncodePostData() {
        return encodePostData;
    }

    public void setEncodePostData(boolean flag) {
        encodePostData = flag;
    }

    static {
        $assertionsDisabled = !(com.dragonflow.ApacheHttpClientUtils.HTTPRequestSettings.class).desiredAssertionStatus();
        mTimeOutToConnectMS = 0x1d4c0;
        mTimeOutNoTrafficMS = 0x1d4c0;
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        if (hashmap != null) {
            java.lang.String s = (java.lang.String) hashmap.get("_httpTimeOutToConnectMS");
            try {
                if (s != null) {
                    mTimeOutToConnectMS = java.lang.Integer.parseInt(s);
                }
            } catch (java.lang.NumberFormatException numberformatexception) {
                com.dragonflow.Log.LogManager.log("error", "Wrong _httpTimeOutToConnectMS format, default value was set " + mTimeOutToConnectMS);
            }
            s = (java.lang.String) hashmap.get("_httpTimeOutNoTrafficMS");
            try {
                if (s != null) {
                    mTimeOutNoTrafficMS = java.lang.Integer.parseInt(s);
                }
            } catch (java.lang.NumberFormatException numberformatexception1) {
                com.dragonflow.Log.LogManager.log("error", "Wrong _httpTimeOutNoTrafficMS format, default value was set " + mTimeOutNoTrafficMS);
            }
        }
    }
}
