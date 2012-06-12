 /*
  * Created on 2005-2-9 3:06:20
  *
  * .java
  *
  * History:
  *
  */
  package com.dragonflow.Utils;

 /**
     * Comment for <code></code>
     * 
     * @author
     * @version 0.0
     * 
     * 
     */

import java.util.Date;

import jgl.Array;
import jgl.HashMap;

import org.apache.commons.httpclient.Header;

import com.dragonflow.Properties.HashMapOrdered;

// Referenced classes of package com.dragonflow.Utils:
// SocketStream, URLInfo, CommandLine, FileUtils,
// SSLSocketStream, TextUtils

public class SocketSession
{

    public static boolean hasJavaSSL = false;
    jgl.HashMap cache;
    long maxCachedSockets;
    public com.dragonflow.SiteView.Monitor context;
    public boolean inRemoteRequest;
    public jgl.Array cookies;
    public java.lang.String originalUserName;
    public java.lang.String originalPassword;
    public java.lang.String refererURL;
    private java.lang.String encodePostData;
    private java.lang.String domain;
    private java.lang.String authenticationWhenRequested;
    public boolean allowClose;
    static boolean debug = false;
    public java.lang.String certFilename;
    public java.lang.String certPassword;
    java.lang.String encodingForStream;
    public java.io.PrintWriter sslOut;
    public java.io.BufferedReader sslIn;
    public java.lang.Process sslProcess;
    public java.lang.String sslKey;
    private byte byteBuffer[];
    private char charBuffer[];

    public static com.dragonflow.Utils.SocketSession getSession(com.dragonflow.SiteView.Monitor monitor)
    {
        com.dragonflow.Utils.SocketSession socketsession = null;
        if(monitor != null)
        {
            socketsession = monitor.cachedSocketSession;
        }
        if(socketsession == null)
        {
            socketsession = new SocketSession();
        }
        socketsession.initialize(monitor);
        return socketsession;
    }

    private SocketSession()
    {
        cache = new HashMap();
        maxCachedSockets = 0L;
        context = null;
        inRemoteRequest = false;
        cookies = new Array();
        originalUserName = "";
        originalPassword = "";
        refererURL = "";
        encodePostData = null;
        domain = "";
        authenticationWhenRequested = "";
        allowClose = true;
        certFilename = "";
        certPassword = "";
        encodingForStream = "";
        sslOut = null;
        sslIn = null;
        sslProcess = null;
        sslKey = "";
        byteBuffer = null;
        charBuffer = null;
    }

    public void setStreamEncoding(java.lang.String s)
    {
        if(s != null)
        {
            encodingForStream = new String(s);
        }
    }

    public java.lang.String getStreamEncoding()
    {
        return new String(encodingForStream);
    }

    public java.lang.String getEncodePostData()
    {
        if(encodePostData == null)
        {
            return com.dragonflow.StandardMonitor.URLMonitor.urlencodedDropDown[0];
        } else
        {
            return encodePostData;
        }
    }

    public void setEncodePostData(java.lang.String s)
    {
        encodePostData = s;
    }

    public java.lang.String getDomain()
    {
        return domain;
    }

    public void setDomain(java.lang.String s)
    {
        domain = s;
    }

    public java.lang.String getAuthenticationWhenRequested()
    {
        if(authenticationWhenRequested == null)
        {
            return com.dragonflow.StandardMonitor.URLMonitor.authOn401DropDown[0];
        } else
        {
            return authenticationWhenRequested;
        }
    }

    public void setAuthenticationWhenRequested(java.lang.String s)
    {
        authenticationWhenRequested = s;
    }

    private void initialize(com.dragonflow.SiteView.Monitor monitor)
    {
        context = monitor;
        if(context == null)
        {
            context = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        }
        certFilename = context.getSetting("_urlClientCert");
        if(certFilename.length() > 0)
        {
            certPassword = context.getSetting("_urlClientCertPassword");
            java.lang.String s = context.getSetting("groupID");
            java.lang.String s1 = "templates.certificates";
            if(s.length() > 0)
            {
                certFilename = com.dragonflow.SiteView.Platform.getUsedDirectoryPath(s1, s) + java.io.File.separator + certFilename;
            } else
            {
                certFilename = com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + s1 + java.io.File.separator + certFilename;
            }
        }
        maxCachedSockets = 4L;
        long l = context.getSettingAsLong("_urlKeepAlive");
        if(l < 0L)
        {
            maxCachedSockets = 0L;
        } else
        if(l > 0L)
        {
            maxCachedSockets = l;
        }
        if(debug)
        {
            com.dragonflow.Log.LogManager.log("RunMonitor", "SocketSession created, max=" + maxCachedSockets);
        }
    }

    public byte[] getByteBuffer()
    {
        if(byteBuffer == null)
        {
            byteBuffer = new byte[16384];
        }
        return byteBuffer;
    }

    public char[] getCharBuffer()
    {
        if(charBuffer == null)
        {
            charBuffer = new char[16384];
        }
        return charBuffer;
    }

    void closeSSL()
    {
        if(sslProcess != null)
        {
            try
            {
                sslProcess.destroy();
            }
            catch(java.lang.Exception exception)
            {
                com.dragonflow.Log.LogManager.log("Error", "ssl process close, " + sslKey + ", " + exception);
            }
            sslProcess = null;
        }
        if(sslOut != null)
        {
            try
            {
                sslOut.close();
            }
            catch(java.lang.Exception exception1)
            {
                com.dragonflow.Log.LogManager.log("Error", "ssl output close, " + sslKey + ", " + exception1);
            }
            sslOut = null;
        }
        if(sslIn != null)
        {
            try
            {
                sslIn.close();
            }
            catch(java.lang.Exception exception2)
            {
                com.dragonflow.Log.LogManager.log("Error", "ssl input close, " + sslKey + ", " + exception2);
            }
            sslIn = null;
        }
        sslKey = "";
    }

    public boolean isSSLKeepAliveConnection(java.lang.String as[], java.lang.String s)
        throws java.io.IOException
    {
        if(sslProcess != null && sslKey.equals(s))
        {
            return true;
        }
        closeSSL();
        sslProcess = com.dragonflow.Utils.CommandLine.execSync(as);
        if(encodingForStream.length() == 0)
        {
            sslOut = com.dragonflow.Utils.FileUtils.MakeOutputWriter(sslProcess.getOutputStream());
            sslIn = com.dragonflow.Utils.FileUtils.MakeInputReader(sslProcess.getInputStream());
        } else
        {
            sslOut = com.dragonflow.Utils.FileUtils.MakeEncodedOutputWriter(sslProcess.getOutputStream(), encodingForStream);
            sslIn = com.dragonflow.Utils.FileUtils.MakeEncodedInputReader(sslProcess.getInputStream(), encodingForStream);
        }
        sslKey = s;
        return false;
    }

    public com.dragonflow.Utils.SocketStream get(java.lang.String s)
    {
        return (com.dragonflow.Utils.SocketStream)cache.get(s);
    }

    public void put(java.lang.String s, com.dragonflow.Utils.SocketStream socketstream)
    {
        cache.put(s, socketstream);
    }

    public com.dragonflow.Utils.SocketStream connect(java.lang.String s, java.net.InetAddress inetaddress, int i, java.lang.String s1)
        throws java.io.IOException
    {
        return connect(s, inetaddress, i, s1, null, null, -1, null, null, null, -1L);
    }

    public com.dragonflow.Utils.SocketStream connect(java.lang.String s, java.net.InetAddress inetaddress, int i, java.lang.String s1, java.lang.String s2, int j, java.lang.String s3, 
            java.lang.String s4, long l)
        throws java.io.IOException
    {
        return connect(s, inetaddress, i, s1, null, s2, j, null, s3, s4, l);
    }

    public com.dragonflow.Utils.SocketStream connect(java.lang.String s, java.net.InetAddress inetaddress, int i, java.lang.String s1, java.net.InetAddress inetaddress1, java.lang.String s2, int j, 
            java.lang.String s3, java.lang.String s4, java.lang.String s5, long l)
        throws java.io.IOException
    {
        com.dragonflow.Utils.SocketStream socketstream = (com.dragonflow.Utils.SocketStream)cache.get(s);
        if(socketstream == null)
        {
            socketstream = new SocketStream(this, s, inetaddress, i, s1, s2, j, s4, s5, l, encodingForStream);
            if(debug)
            {
                com.dragonflow.Log.LogManager.log("RunMonitor", "SocketSession.getSocket, created, " + s + ", " + socketstream.socket);
            }
        } else
        if(debug)
        {
            com.dragonflow.Log.LogManager.log("RunMonitor", "SocketSession.getSocket, cached, " + s + ", " + socketstream.socket);
        }
        return socketstream;
    }

    public void release(com.dragonflow.Utils.SocketStream socketstream)
    {
        if(socketstream.keepAlive && !socketstream.receivedEndOfStream && maxCachedSockets != 0L)
        {
            if(debug)
            {
                com.dragonflow.Log.LogManager.log("RunMonitor", "SocketSession.releaseSocket, cached, " + socketstream.key + ", " + socketstream.socket);
            }
            cache.put(socketstream.key, socketstream);
            if((long)cache.size() > maxCachedSockets)
            {
                java.util.Enumeration enumeration = cache.elements();
                com.dragonflow.Utils.SocketStream socketstream1 = (com.dragonflow.Utils.SocketStream)enumeration.nextElement();
                if(debug)
                {
                    com.dragonflow.Log.LogManager.log("RunMonitor", "SocketSession.releaseSocket, expired, " + socketstream1.key);
                }
                socketstream1.close();
                cache.remove(socketstream1.key);
            }
        } else
        {
            if(debug)
            {
                com.dragonflow.Log.LogManager.log("RunMonitor", "SocketSession.releaseSocket, closed, " + socketstream.key + ", " + socketstream.socket);
            }
            if(context == null)
            {
                context = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            }
            if(context.getSetting("_sslSessionKeepAlive").length() <= 0)
            {
                com.dragonflow.Utils.SSLSocketStream.invalidateSSLSession(socketstream.socket);
            }
            socketstream.close();
            if(cache != null)
            {
                cache.remove(socketstream.key);
            }
        }
    }

    public java.lang.String getVersion()
    {
        if(maxCachedSockets > 0L)
        {
            return "1.1";
        } else
        {
            return "1.0";
        }
    }

    public void close()
    {
        if(allowClose)
        {
            if(cache != null)
            {
                com.dragonflow.Utils.SocketStream socketstream;
                for(java.util.Enumeration enumeration = cache.elements(); enumeration.hasMoreElements(); socketstream.close())
                {
                    socketstream = (com.dragonflow.Utils.SocketStream)enumeration.nextElement();
                    if(debug)
                    {
                        com.dragonflow.Log.LogManager.log("RunMonitor", "SocketSession.closeSocketCache, closed, " + socketstream.key + ", " + socketstream.socket);
                    }
                }

                cache.clear();
            }
            closeSSL();
            if(debug)
            {
                com.dragonflow.Log.LogManager.log("RunMonitor", "SocketSession.socketSession, closed");
            }
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param hashmap
     * @return
     */
    private static boolean expiredCookie(jgl.HashMap hashmap)
    {
        java.util.Date date;
        java.util.Date date1;
        try {
        java.lang.String s = (java.lang.String)hashmap.get("expires");
        if(s != null)
        {
        date = new Date(s);
        date1 = new Date();
        if(date.before(date1))
        {
            return true;
        }
        }
        }
        catch (java.lang.Exception exception) {
            /* empty */
        }
        return false;
    }

    private static jgl.Array addCookie(jgl.Array array, jgl.HashMap hashmap)
    {
        boolean flag = false;
        boolean flag1 = com.dragonflow.Utils.SocketSession.expiredCookie(hashmap);
        if(flag1 && (com.dragonflow.StandardMonitor.URLMonitor.debugURL & com.dragonflow.StandardMonitor.URLMonitor.kDebugCookie) != 0)
        {
            com.dragonflow.Log.LogManager.log("RunMonitor", "expired-cookie");
        }
        java.lang.String s = com.dragonflow.Utils.TextUtils.getValue(hashmap, "key");
        int i = 0;
        do
        {
            if(i >= array.size())
            {
                break;
            }
            jgl.HashMap hashmap1 = (jgl.HashMap)array.at(i);
            if(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "key").equalsIgnoreCase(s) && com.dragonflow.Utils.TextUtils.getValue(hashmap1, "domain").equalsIgnoreCase(com.dragonflow.Utils.TextUtils.getValue(hashmap, "domain")) && com.dragonflow.Utils.TextUtils.getValue(hashmap1, "path").equalsIgnoreCase(com.dragonflow.Utils.TextUtils.getValue(hashmap, "path")))
            {
                if(flag1)
                {
                    array.remove(i);
                    if((com.dragonflow.StandardMonitor.URLMonitor.debugURL & com.dragonflow.StandardMonitor.URLMonitor.kDebugCookie) != 0)
                    {
                        com.dragonflow.Log.LogManager.log("RunMonitor", "remove-cookie");
                    }
                } else
                {
                    array.put(i, hashmap);
                    if((com.dragonflow.StandardMonitor.URLMonitor.debugURL & com.dragonflow.StandardMonitor.URLMonitor.kDebugCookie) != 0)
                    {
                        com.dragonflow.Log.LogManager.log("RunMonitor", "replace-cookie");
                    }
                    flag = true;
                }
                break;
            }
            i++;
        } while(true);
        if(!flag1 && !flag)
        {
            array.add(hashmap);
            if((com.dragonflow.StandardMonitor.URLMonitor.debugURL & com.dragonflow.StandardMonitor.URLMonitor.kDebugCookie) != 0)
            {
                com.dragonflow.Log.LogManager.log("RunMonitor", "append-cookie");
            }
        }
        if((com.dragonflow.StandardMonitor.URLMonitor.debugURL & com.dragonflow.StandardMonitor.URLMonitor.kDebugCookie) != 0)
        {
            com.dragonflow.Log.LogManager.log("RunMonitor", "            key=" + hashmap.get("key"));
            com.dragonflow.Log.LogManager.log("RunMonitor", "            value=" + hashmap.get("value"));
            com.dragonflow.Log.LogManager.log("RunMonitor", "            domain=" + hashmap.get("domain"));
            com.dragonflow.Log.LogManager.log("RunMonitor", "            path=" + hashmap.get("path"));
            com.dragonflow.Log.LogManager.log("RunMonitor", "            expires=" + hashmap.get("expires"));
            com.dragonflow.Log.LogManager.log("RunMonitor", "            secure=" + hashmap.get("secure"));
        }
        return array;
    }

    private static jgl.HashMap MakeCookie(java.lang.String s)
    {
        com.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
        if(s != null)
        {
            com.dragonflow.Utils.URLInfo urlinfo = new URLInfo(s);
            hashmapordered.put("domain", urlinfo.getHost());
            java.lang.String s1 = urlinfo.getFile();
            int i = s1.indexOf('?');
            if(i > 0)
            {
                s1 = s1.substring(0, i);
            }
            if(!s1.endsWith("/"))
            {
                int j = s1.lastIndexOf('/');
                if(j != -1)
                {
                    s1 = s1.substring(0, j);
                }
            }
            hashmapordered.put("path", s1);
        }
        return hashmapordered;
    }

    private static void update1Cookie(jgl.Array array, java.lang.String s, java.lang.String s1)
    {
        if(com.dragonflow.Utils.TextUtils.startsWithIgnoreCase(s, com.dragonflow.StandardMonitor.URLMonitor.SET_COOKIE_HEADER))
        {
            if((com.dragonflow.StandardMonitor.URLMonitor.debugURL & com.dragonflow.StandardMonitor.URLMonitor.kDebugCookie) != 0)
            {
                com.dragonflow.Log.LogManager.log("RunMonitor", "parse-cookie, line=" + s + ", url=" + s1);
            }
            boolean flag = true;
            jgl.HashMap hashmap = com.dragonflow.Utils.SocketSession.MakeCookie(s1);
            java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s.substring(com.dragonflow.StandardMonitor.URLMonitor.SET_COOKIE_HEADER.length()).trim(), ";");
            for(int i = 0; i < as.length; i++)
            {
                as[i] = as[i].trim();
                if(com.dragonflow.Utils.TextUtils.startsWithIgnoreCase(as[i], "path="))
                {
                    hashmap.put("path", as[i].substring("path=".length()));
                    continue;
                }
                if(com.dragonflow.Utils.TextUtils.startsWithIgnoreCase(as[i], "domain="))
                {
                    java.lang.String s2 = as[i].substring("domain=".length());
                    int k = s2.indexOf(":");
                    if(k != -1)
                    {
                        s2 = s2.substring(0, k);
                    }
                    hashmap.put("domain", s2);
                    continue;
                }
                if(com.dragonflow.Utils.TextUtils.startsWithIgnoreCase(as[i], "secure") && as[i].indexOf("=") == -1)
                {
                    hashmap.put("secure", "");
                    continue;
                }
                if(com.dragonflow.Utils.TextUtils.startsWithIgnoreCase(as[i], "expires="))
                {
                    hashmap.put("expires", as[i].substring("expires=".length()));
                    continue;
                }
                if(as[i].indexOf("=") != -1 && flag)
                {
                    flag = false;
                    int j = as[i].indexOf("=");
                    hashmap.put("key", as[i].substring(0, j));
                    hashmap.put("value", as[i].substring(j + 1));
                }
            }

            com.dragonflow.Utils.SocketSession.addCookie(array, hashmap);
        }
    }

    public void updateCookies(java.lang.String s, java.lang.String s1)
    {
        java.lang.String s2 = com.dragonflow.StandardMonitor.URLMonitor.getHTTPHeaders(s);
        int i = 0;
        int j;
        do
        {
            j = s2.indexOf('\n', i + 1);
            java.lang.String s3;
            if(j == -1)
            {
                s3 = s2.substring(i, s2.length()).trim();
            } else
            {
                s3 = s2.substring(i, j).trim();
            }
            com.dragonflow.Utils.SocketSession.update1Cookie(cookies, s3, s1);
            i = j;
        } while(j != -1);
    }

    public void addCookieParameters(jgl.Array array, java.lang.String s)
    {
        if(array != null)
        {
            java.lang.String s1;
            for(java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); com.dragonflow.Utils.SocketSession.update1Cookie(cookies, s1, s))
            {
                s1 = (java.lang.String)enumeration.nextElement();
            }

        }
    }

    public org.apache.commons.httpclient.Header getCookieHeader(java.lang.String s)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        org.apache.commons.httpclient.Header header = null;
        jgl.HashMap hashmap = getCookies(s);
        if(hashmap != null)
        {
            java.util.Enumeration enumeration = cookies.elements();
            while (enumeration.hasMoreElements()) {
                jgl.HashMap hashmap1 = (jgl.HashMap)enumeration.nextElement();
                if(hashmap.get(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "key")) == hashmap1)
                {
                    java.lang.String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "key") + "=" + com.dragonflow.Utils.TextUtils.getValue(hashmap1, "value");
                    if(stringbuffer.length() > 0)
                    {
                        stringbuffer.append("; ");
                    }
                    stringbuffer.append(s1);
                }
            } 
            header = new Header("Cookie", stringbuffer.toString());
        }
        return header;
    }

    private jgl.HashMap getCookies(java.lang.String s)
    {
        if((com.dragonflow.StandardMonitor.URLMonitor.debugURL & com.dragonflow.StandardMonitor.URLMonitor.kDebugCookie) != 0)
        {
            com.dragonflow.Log.LogManager.log("RunMonitor", "get-cookie=" + s);
        }
        com.dragonflow.Utils.URLInfo urlinfo = new URLInfo(s);
        if(cookies == null)
        {
            return null;
        }
        java.util.Enumeration enumeration = cookies.elements();
        jgl.HashMap hashmap = new HashMap();
        while (enumeration.hasMoreElements()) {
            jgl.HashMap hashmap1 = (jgl.HashMap)enumeration.nextElement();
            java.lang.String s1 = urlinfo.getHost();
            if(com.dragonflow.Utils.TextUtils.startsWithIgnoreCase(com.dragonflow.Utils.TextUtils.reverse(s1), com.dragonflow.Utils.TextUtils.reverse(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "domain"))) && com.dragonflow.Utils.TextUtils.startsWithIgnoreCase(urlinfo.getFile(), com.dragonflow.Utils.TextUtils.getValue(hashmap1, "path")) && (!urlinfo.getProtocol().equalsIgnoreCase("http") || hashmap1.get("secure") == null))
            {
                java.lang.String s2 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "key");
                jgl.HashMap hashmap2 = (jgl.HashMap)hashmap.get(s2);
                if(hashmap2 != null)
                {
                    if(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "path").length() > com.dragonflow.Utils.TextUtils.getValue(hashmap2, "path").length())
                    {
                        hashmap.put(s2, hashmap1);
                    }
                } else
                {
                    hashmap.put(s2, hashmap1);
                }
            }
        } 
        return hashmap;
    }

    public java.lang.String getCookieHeader(java.lang.String s, boolean flag)
    {
        jgl.HashMap hashmap = getCookies(s);
        java.lang.String s1 = "";
        if(hashmap != null)
        {
            java.util.Enumeration enumeration = cookies.elements();
            while (enumeration.hasMoreElements()) {
                jgl.HashMap hashmap1 = (jgl.HashMap)enumeration.nextElement();
                if(hashmap.get(com.dragonflow.Utils.TextUtils.getValue(hashmap1, "key")) == hashmap1)
                {
                    if(s1.length() > 0)
                    {
                        if(flag)
                        {
                            s1 = s1 + com.dragonflow.StandardMonitor.URLMonitor.CRLF + "Cookie: ";
                        } else
                        {
                            s1 = s1 + "; ";
                        }
                    } else
                    {
                        s1 = "Cookie: ";
                    }
                    s1 = s1 + com.dragonflow.Utils.TextUtils.getValue(hashmap1, "key") + "=" + com.dragonflow.Utils.TextUtils.getValue(hashmap1, "value");
                }
            } 
            if(s1.length() > 0)
            {
                s1 = s1 + com.dragonflow.StandardMonitor.URLMonitor.CRLF;
            }
            if((com.dragonflow.StandardMonitor.URLMonitor.debugURL & com.dragonflow.StandardMonitor.URLMonitor.kDebugCookie) != 0)
            {
                com.dragonflow.Log.LogManager.log("RunMonitor", "cookie-header=" + s1);
            }
        }
        return s1;
    }

    static 
    {
        debug = java.lang.System.getProperty("SocketSession.debug") != null;
    }
}
