/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.HTTP;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

// Referenced classes of package com.dragonflow.HTTP:
// HTTPRequest
public abstract class HTTPRequestHandler {

    protected java.io.PrintWriter outputStream;

    protected java.io.OutputStream rawOutput;

    public HTTPRequestHandler() {
    }

    public void handleRequest(com.dragonflow.HTTP.HTTPRequest httprequest, java.io.PrintWriter printwriter, java.io.OutputStream outputstream) throws java.lang.Exception {
        outputStream = printwriter;
        rawOutput = outputstream;
        handleRequest(httprequest);
    }

    public abstract void handleRequest(com.dragonflow.HTTP.HTTPRequest httprequest) throws java.lang.Exception;
}
