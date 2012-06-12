/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.ApacheHttpClientUtils;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import org.apache.commons.httpclient.protocol.SSLProtocolSocketFactory;

// Referenced classes of package COM.dragonflow.ApacheHttpClientUtils:
// ApacheSocketFactoryBase, IApacheHttpConnectTiming, ApacheHttpUtils

public class ApacheSSLProtocolSocketFactory extends COM.dragonflow.ApacheHttpClientUtils.ApacheSocketFactoryBase implements org.apache.commons.httpclient.protocol.SecureProtocolSocketFactory, COM.dragonflow.ApacheHttpClientUtils.IApacheHttpConnectTiming {

    private org.apache.commons.httpclient.protocol.SSLProtocolSocketFactory originalSocketFactory;

    private long daysUntilCertExpires;

    public ApacheSSLProtocolSocketFactory() {
        originalSocketFactory = new SSLProtocolSocketFactory();
        daysUntilCertExpires = 0L;
    }

    public long getDaysUntilCertExpires() {
        return daysUntilCertExpires;
    }

    public java.net.Socket createSocket(java.lang.String s, int i, java.net.InetAddress inetaddress, int j) throws java.io.IOException, java.net.UnknownHostException {
        resolveDNS(s);
        java.net.Socket socket = originalSocketFactory.createSocket(s, i, inetaddress, j);
        calculateEndTime();
        daysUntilCertExpires = COM.dragonflow.ApacheHttpClientUtils.ApacheHttpUtils.getDaysUntilCertExpires(socket);
        return socket;
    }

    public java.net.Socket createSocket(java.lang.String s, int i) throws java.io.IOException, java.net.UnknownHostException {
        resolveDNS(s);
        java.net.Socket socket = originalSocketFactory.createSocket(s, i);
        calculateEndTime();
        daysUntilCertExpires = COM.dragonflow.ApacheHttpClientUtils.ApacheHttpUtils.getDaysUntilCertExpires(socket);
        return socket;
    }

    public java.net.Socket createSocket(java.net.Socket socket, java.lang.String s, int i, boolean flag) throws java.io.IOException, java.net.UnknownHostException {
        socket = originalSocketFactory.createSocket(socket, s, i, flag);
        return socket;
    }
}
