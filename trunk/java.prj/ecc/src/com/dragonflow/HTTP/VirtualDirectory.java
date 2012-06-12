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

public class VirtualDirectory {

    java.lang.String virtualPath;

    java.lang.String documentPath;

    boolean cgiDirectory;

    VirtualDirectory(java.lang.String s, java.lang.String s1) {
        cgiDirectory = false;
        virtualPath = s;
        documentPath = s1;
    }

    VirtualDirectory(java.lang.String s, java.lang.String s1, boolean flag) {
        this(s, s1);
        cgiDirectory = flag;
    }

    java.lang.String getVirtualPath() {
        return virtualPath;
    }

    java.lang.String getDocumentPath() {
        return documentPath;
    }

    boolean isCGIDirectory() {
        return cgiDirectory;
    }

    java.lang.String getFullDocumentPath(java.lang.String s) {
        if (s.startsWith(virtualPath)) {
            return documentPath + s.substring(virtualPath.length());
        } else {
            return null;
        }
    }

    public java.lang.String toString() {
        return "VirtualDirectory\n  virtual=" + virtualPath + "\n  document=" + documentPath + "\n  isCGI=" + cgiDirectory;
    }
}
