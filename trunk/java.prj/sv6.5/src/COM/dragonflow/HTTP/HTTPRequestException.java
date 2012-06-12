/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.HTTP;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

public class HTTPRequestException extends java.lang.Exception {

    int statusCode;

    java.lang.String url;

    public java.lang.String message;

    public HTTPRequestException(int i) {
        statusCode = 0;
        url = "";
        message = "";
        statusCode = i;
    }

    public HTTPRequestException(int i, java.lang.String s) {
        statusCode = 0;
        url = "";
        message = "";
        statusCode = i;
        url = s;
    }

    public int getStatusCode() {
        return statusCode;
    }

    public java.lang.String getURL() {
        return url;
    }
}
