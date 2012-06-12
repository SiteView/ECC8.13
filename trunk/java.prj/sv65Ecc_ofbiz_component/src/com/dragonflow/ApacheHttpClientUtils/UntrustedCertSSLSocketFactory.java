/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.ApacheHttpClientUtils;

import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

import org.apache.commons.httpclient.ConnectTimeoutException;
import org.apache.commons.httpclient.params.HttpConnectionParams;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

// Referenced classes of package com.dragonflow.ApacheHttpClientUtils:
// ApacheSocketFactoryBase, UntrustedCertTrustManager, IApacheHttpConnectTiming,
// ApacheHttpUtils
public class UntrustedCertSSLSocketFactory extends com.dragonflow.ApacheHttpClientUtils.ApacheSocketFactoryBase implements org.apache.commons.httpclient.protocol.SecureProtocolSocketFactory, com.dragonflow.ApacheHttpClientUtils.IApacheHttpConnectTiming {

    private static final org.apache.commons.logging.Log LOG;

    private static java.security.KeyStore keystore = null;

    private static boolean acceptAllUntrusted = false;

    private static boolean acceptInvalid = false;

    private long daysUntilCertExpires;

    public UntrustedCertSSLSocketFactory(java.security.KeyStore keystore1, boolean flag, boolean flag1) {
        daysUntilCertExpires = 0L;
        com.dragonflow.ApacheHttpClientUtils.UntrustedCertSSLSocketFactory _tmp = this;
        keystore = keystore1;
        com.dragonflow.ApacheHttpClientUtils.UntrustedCertSSLSocketFactory _tmp1 = this;
        acceptAllUntrusted = flag;
        com.dragonflow.ApacheHttpClientUtils.UntrustedCertSSLSocketFactory _tmp2 = this;
        acceptInvalid = flag1;
    }

    public long getDaysUntilCertExpires() {
        return daysUntilCertExpires;
    }

    private static javax.net.ssl.SSLSocketFactory getUntrustedCertSSLSocketFactory() {
        javax.net.ssl.SSLContext sslcontext = null;
        try {
            sslcontext = javax.net.ssl.SSLContext.getInstance("SSL");
            sslcontext.init(null, new javax.net.ssl.TrustManager[] { new UntrustedCertTrustManager(keystore, acceptAllUntrusted, acceptInvalid) }, null);
        } catch (Exception exception) {
            LOG.error(exception.getMessage(), exception);
            throw new RuntimeException(exception.toString());
        }
        return sslcontext.getSocketFactory();
    }

    public java.net.Socket createSocket(String s, int i, java.net.InetAddress inetaddress, int j) throws java.io.IOException, java.net.UnknownHostException {
        java.net.InetAddress inetaddress1 = resolveDNS(s);
        java.net.Socket socket = com.dragonflow.ApacheHttpClientUtils.UntrustedCertSSLSocketFactory.getUntrustedCertSSLSocketFactory().createSocket(inetaddress1, i, inetaddress, j);
        calculateEndTime();
        daysUntilCertExpires = com.dragonflow.ApacheHttpClientUtils.ApacheHttpUtils.getDaysUntilCertExpires(socket);
        return socket;
    }

    public java.net.Socket createSocket(String s, int i) throws java.io.IOException, java.net.UnknownHostException {
        java.net.InetAddress inetaddress = resolveDNS(s);
        java.net.Socket socket = com.dragonflow.ApacheHttpClientUtils.UntrustedCertSSLSocketFactory.getUntrustedCertSSLSocketFactory().createSocket(inetaddress, i);
        calculateEndTime();
        daysUntilCertExpires = com.dragonflow.ApacheHttpClientUtils.ApacheHttpUtils.getDaysUntilCertExpires(socket);
        return socket;
    }

    public java.net.Socket createSocket(java.net.Socket socket, String s, int i, boolean flag) throws java.io.IOException, java.net.UnknownHostException {
        return com.dragonflow.ApacheHttpClientUtils.UntrustedCertSSLSocketFactory.getUntrustedCertSSLSocketFactory().createSocket(socket, s, i, flag);
    }

    static {
        LOG = org.apache.commons.logging.LogFactory.getLog(com.dragonflow.ApacheHttpClientUtils.UntrustedCertSSLSocketFactory.class);
    }

	public Socket createSocket(String arg0, int arg1, InetAddress arg2,
			int arg3, HttpConnectionParams arg4) throws IOException,
			UnknownHostException, ConnectTimeoutException {
		// TODO Auto-generated method stub
		return null;
	}


}
