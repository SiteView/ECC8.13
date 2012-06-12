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

import java.util.Date;

import com.dragonflow.Utils.HTMLTagParser;

// Referenced classes of package com.dragonflow.ApacheHttpClientUtils:
// ICommonMethod

public class ApacheHttpMethod {

    private org.apache.commons.httpclient.HttpMethodBase method;

    private java.lang.String connection;

    private java.lang.String location;

    private long contentLength;

    private long lastModified;

    private long date;

    private boolean refreshRedirect;

    private java.lang.String responseHeaders;

    private boolean headersProcessed;

    static final boolean $assertionsDisabled; /* synthetic field */

    public ApacheHttpMethod(
            org.apache.commons.httpclient.HttpMethodBase httpmethodbase) {
        method = null;
        connection = "";
        location = "";
        contentLength = -1L;
        lastModified = 0L;
        date = 0L;
        refreshRedirect = false;
        responseHeaders = null;
        headersProcessed = false;
        method = httpmethodbase;
    }

    private org.apache.commons.httpclient.HttpMethod getMethod() {
        return method;
    }

    public java.lang.String getConnection() {
        if (!headersProcessed) {
            headersProcessed = processHeaders();
        }
        return connection;
    }

    public java.lang.String getLocation() {
        if (!headersProcessed) {
            headersProcessed = processHeaders();
        }
        return location;
    }

    public long getContentLength() {
        if (!headersProcessed) {
            headersProcessed = processHeaders();
        }
        return contentLength;
    }

    public long getLastModified() {
        if (!headersProcessed) {
            headersProcessed = processHeaders();
        }
        return lastModified;
    }

    public long getDate() {
        if (!headersProcessed) {
            headersProcessed = processHeaders();
        }
        return date;
    }

    public boolean getRefreshRedirect() {
        if (!headersProcessed) {
            headersProcessed = processHeaders();
        }
        return refreshRedirect;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @return
     */
    public byte[] getResponseBody() {
        try {
            return method.getResponseBody();
        } catch (java.lang.Exception exception) {
            return null;
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @return
     */
    public java.io.InputStream getResponseBodyAsStream() {
        try {
            return method.getResponseBodyAsStream();
        } catch (java.lang.Exception exception) {
            return null;
        }
    }

    public java.lang.String getResponseBodyAsString() {
        java.lang.String s = null;
        try {
            s = method.getResponseBodyAsString();
        } catch (java.lang.Exception exception) {
        }
        if (s == null) {
            return "";
        } else {
            return s;
        }
    }

    public java.lang.String getResponseHeadersAsString() {
        if (responseHeaders != null) {
            return responseHeaders;
        }
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        if (getMethod().getStatusLine() != null) {
            stringbuffer.append(getMethod().getStatusLine().toString());
            stringbuffer.append("\r\n");
        }
        org.apache.commons.httpclient.Header aheader[] = getMethod()
                .getResponseHeaders();
        if (aheader != null) {
            for (int i = 0; i < aheader.length; i++) {
                org.apache.commons.httpclient.Header header = aheader[i];
                stringbuffer.append(header.toString());
            }

        }
        org.apache.commons.httpclient.Header aheader1[] = getMethod()
                .getResponseFooters();
        if (aheader1 != null) {
            for (int j = 0; j < aheader1.length; j++) {
                org.apache.commons.httpclient.Header header1 = aheader1[j];
                stringbuffer.append(header1.toString());
            }

        }
        java.lang.String s = stringbuffer.toString();
        responseHeaders = s == null ? "" : s;
        return responseHeaders;
    }

    public boolean processHeaders() {
        if (method != null) {
            org.apache.commons.httpclient.Header header = method
                    .getResponseHeader("Connection");
            if (header != null) {
                connection = header.getValue();
            }
            if (connection == null) {
                connection = "";
            }
            org.apache.commons.httpclient.Header header1 = method
                    .getResponseHeader("Location");
            if (header1 == null) {
                header1 = method.getResponseHeader("Content-Location");
            }
            if (header1 != null) {
                location = header1.getValue();
                int i = 0;
                i = location.indexOf(", ");
                if (i >= 0) {
                    java.lang.String s = "";
                    int j = location.indexOf("://");
                    if (j >= 0) {
                        s = s + location.substring(0, j + 3);
                    }
                    j = location.lastIndexOf(", ");
                    if (j >= 0) {
                        s = s + location.substring(j + 2);
                    }
                    location = s.trim();
                }
            }
            if (location.equals("")) {
                location = getMetaRefreshForRedirectIfFound();
            }
            if (!$assertionsDisabled
                    && (method == null || !(method instanceof com.dragonflow.ApacheHttpClientUtils.ICommonMethod))) {
                throw new AssertionError(
                        "The post or get method is null or does not implement ICommonMethod. No content-length:");
            }
            if (method != null
                    && (method instanceof com.dragonflow.ApacheHttpClientUtils.ICommonMethod)) {
                contentLength = ((com.dragonflow.ApacheHttpClientUtils.ICommonMethod) method)
                        .getResponseContentLength();
            }
            lastModified = turnDateStringIntoLongEpochSeconds("Last-Modified");
            date = turnDateStringIntoLongEpochSeconds("Date");
        }
        return true;
    }

    private java.lang.String getMetaRefreshForRedirectIfFound() {
        java.lang.String s;
        s = "";
        try {
            java.lang.String as[] = { "META", "/HEAD" };
            java.lang.String s1 = "url=";
            java.lang.String s2 = getResponseBodyAsString();
            if (s2.indexOf("http-equiv") >= 0 || s2.indexOf("HTTP-EQUIV") >= 0) {
                com.dragonflow.Utils.HTMLTagParser htmltagparser = new HTMLTagParser(
                        s2, as, true, "/HEAD");
                htmltagparser.process();
                java.util.Enumeration enumeration = htmltagparser
                        .findTags("meta");
                java.lang.String s3;
                int i;
                int j;
                jgl.HashMap hashmap;
                while (enumeration.hasMoreElements()) {
                    hashmap = (jgl.HashMap) enumeration.nextElement();
                    if (com.dragonflow.Utils.TextUtils.getValue(hashmap,
                            "http-equiv").equalsIgnoreCase("refresh")) {
                        s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap,
                                "content");
                        byte byte0 = -1;
                        j = s3.indexOf(";");
                        if (j >= 0) {
                            i = com.dragonflow.Utils.TextUtils.readInteger(s3
                                    .substring(0, j), 0);
                            if (i == 0) {
                                s = s3.substring(j + 1).trim();
                                if (com.dragonflow.Utils.TextUtils
                                        .startsWithIgnoreCase(s, s1)) {
                                    s = s.substring(s1.length()).trim();
                                }
                                if (s.startsWith("'") || s.startsWith("\"")) {
                                    s = s.substring(1).trim();
                                }
                                if (s.endsWith("'") || s.endsWith("\"")) {
                                    s = s.substring(0, s.length() - 1).trim();
                                }
                                refreshRedirect = true;
                            }
                        }
                    }
                }
            }
        } catch (java.lang.Exception exception) {
            exception.printStackTrace();
        }

        return s;
    }

    private long turnDateStringIntoLongEpochSeconds(java.lang.String s) {
        java.util.Date date1 = new Date();
        java.lang.String s1 = "";
        try {
            s1 = method.getResponseHeader(s).getValue();
        } catch (java.lang.Exception exception) {
            return 0L;
        }
        try {
            date1 = org.apache.commons.httpclient.util.DateParser.parseDate(s1);
        } catch (java.lang.Exception exception1) {
            date1 = new Date();
        }
        return date1.getTime() / 1000L;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @return
     */
    public int getStatusCode() {
        try {
            return method.getStatusCode();
        } catch (java.lang.Exception exception) {
            return -1;
        }
    }

    public long getDNSDuration() {
        long l = 0L;
        if (getMethod() != null) {
            l = ((com.dragonflow.ApacheHttpClientUtils.ICommonMethod) getMethod())
                    .getDNSDuration();
        }
        return l;
    }

    public long getConnectDuration() {
        long l = 0L;
        if (getMethod() != null) {
            l = ((com.dragonflow.ApacheHttpClientUtils.ICommonMethod) getMethod())
                    .getConnectDuration();
        }
        return l;
    }

    public long getResponseDuration() {
        long l = 0L;
        if (method != null
                && (method instanceof com.dragonflow.ApacheHttpClientUtils.ICommonMethod)) {
            l = ((com.dragonflow.ApacheHttpClientUtils.ICommonMethod) method)
                    .getResponseDuration();
        }
        return l;
    }

    public long getDownloadDuration() {
        long l = 0L;
        if (method != null
                && (method instanceof com.dragonflow.ApacheHttpClientUtils.ICommonMethod)) {
            l = ((com.dragonflow.ApacheHttpClientUtils.ICommonMethod) getMethod())
                    .getDownloadDuration();
        }
        return l;
    }

    public long getDaysUntilCertExpires() {
        long l = 0L;
        if (method != null
                && (method instanceof com.dragonflow.ApacheHttpClientUtils.ICommonMethod)) {
            l = ((com.dragonflow.ApacheHttpClientUtils.ICommonMethod) getMethod())
                    .getDaysUntilCertExpires();
        }
        return l;
    }

    public java.lang.String getRequestString(boolean flag) {
        java.lang.String s = "";
        if (method != null
                && (method instanceof com.dragonflow.ApacheHttpClientUtils.ICommonMethod)) {
            com.dragonflow.ApacheHttpClientUtils.ICommonMethod icommonmethod = (com.dragonflow.ApacheHttpClientUtils.ICommonMethod) method;
            s = icommonmethod.getRequestString(flag);
        }
        return s == null ? "" : s;
    }

    static {
        $assertionsDisabled = !(com.dragonflow.ApacheHttpClientUtils.ApacheHttpMethod.class)
                .desiredAssertionStatus();
    }
}
