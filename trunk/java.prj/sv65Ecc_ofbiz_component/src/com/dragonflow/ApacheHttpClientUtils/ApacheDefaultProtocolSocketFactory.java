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

import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

import org.apache.commons.httpclient.ConnectTimeoutException;
import org.apache.commons.httpclient.params.HttpConnectionParams;
import org.apache.commons.httpclient.protocol.DefaultProtocolSocketFactory;

// Referenced classes of package com.dragonflow.ApacheHttpClientUtils:
// ApacheSocketFactoryBase

public class ApacheDefaultProtocolSocketFactory extends com.dragonflow.ApacheHttpClientUtils.ApacheSocketFactoryBase implements org.apache.commons.httpclient.protocol.ProtocolSocketFactory {

    private org.apache.commons.httpclient.protocol.DefaultProtocolSocketFactory originalSocketFactory;

    public ApacheDefaultProtocolSocketFactory() {
        originalSocketFactory = new DefaultProtocolSocketFactory();
    }

    public java.net.Socket createSocket(String s, int i, java.net.InetAddress inetaddress, int j) throws java.io.IOException, java.net.UnknownHostException {
        resolveDNS(s);
        java.net.Socket socket = originalSocketFactory.createSocket(s, i, inetaddress, j);
        calculateEndTime();
        return socket;
    }

    public java.net.Socket createSocket(String s, int i) throws java.io.IOException, java.net.UnknownHostException {
        resolveDNS(s);
        java.net.Socket socket = originalSocketFactory.createSocket(s, i);
        calculateEndTime();
        return socket;
    }

	public Socket createSocket(String arg0, int arg1, InetAddress arg2,
			int arg3, HttpConnectionParams arg4) throws IOException,
			UnknownHostException, ConnectTimeoutException {
		// TODO Auto-generated method stub
		return null;
	}


}
