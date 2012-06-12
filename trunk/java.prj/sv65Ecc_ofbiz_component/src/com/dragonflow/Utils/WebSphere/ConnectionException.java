/*
 * 
 * Created on 2005-3-9 18:55:36
 *
 * PDHRawCounterCache.java
 *
 * History:
 *
 */
package com.dragonflow.Utils.WebSphere;

public class ConnectionException extends Exception {

    Exception e;

    public ConnectionException(Exception exception) {
        super("Inner exception is: " + exception);
        e = exception;
    }

    public ConnectionException(String s) {
        super(s);
    }

    public Exception getInnerException() {
        return e;
    }
}
