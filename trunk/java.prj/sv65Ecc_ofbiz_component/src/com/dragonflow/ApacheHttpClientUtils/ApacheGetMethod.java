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

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

// Referenced classes of package com.dragonflow.ApacheHttpClientUtils:
// CommonMethodImpl, ICommonMethod
public class ApacheGetMethod extends org.apache.commons.httpclient.methods.GetMethod implements com.dragonflow.ApacheHttpClientUtils.ICommonMethod {

    com.dragonflow.ApacheHttpClientUtils.CommonMethodImpl myMethodImpl;

    public ApacheGetMethod(String s) {
        myMethodImpl = null;
        myMethodImpl = new CommonMethodImpl(this);
        com.dragonflow.ApacheHttpClientUtils.CommonMethodImpl.initMethod(this, s);
    }

    public long getResponseDuration() {
        return myMethodImpl.getResponseDuration();
    }

    public long getDownloadDuration() {
        return myMethodImpl.getDownloadDuration();
    }

    public long getConnectDuration() {
        return myMethodImpl.getConnectDuration();
    }

    public void setConnectStartTime(long l) {
        myMethodImpl.setConnectStartTime(l);
    }

	public int execute(org.apache.commons.httpclient.HttpState httpstate, org.apache.commons.httpclient.HttpConnection httpconnection) throws org.apache.commons.httpclient.HttpException, 
            java.io.IOException {
        myMethodImpl.executeTimingInit(httpstate, httpconnection);
        return super.execute(httpstate, httpconnection);
    }

    public String getRequestString(boolean flag) {
        return myMethodImpl.getRequestString(flag);
    }

    public long getDNSDuration() {
        return myMethodImpl.getDNSDuration();
    }

    public long getDaysUntilCertExpires() {
        return myMethodImpl.getDaysUntilCertExpires();
    }

    @SuppressWarnings("deprecation")
	protected void readStatusLine(org.apache.commons.httpclient.HttpState httpstate, org.apache.commons.httpclient.HttpConnection httpconnection) throws java.io.IOException, 
            org.apache.commons.httpclient.HttpException {
        super.readStatusLine(httpstate, httpconnection);
        myMethodImpl.readStatusLine(httpstate, httpconnection);
    }

    public byte[] getResponseBody() throws IOException {
        byte abyte0[] = super.getResponseBody();
        myMethodImpl.computeDownloadDuration();
        return abyte0;
    }

    public long getResponseContentLength() {
        return super.getResponseContentLength();
    }

    protected void addCookieRequestHeader(org.apache.commons.httpclient.HttpState httpstate, org.apache.commons.httpclient.HttpConnection httpconnection) throws java.io.IOException, org.apache.commons.httpclient.HttpException {
        myMethodImpl.addCookieRequestHeader(httpstate, httpconnection, getRequestHeaderGroup());
    }
}
