/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Log;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;

class FileWithPath {

    private java.io.OutputStreamWriter logWriter;

    private java.lang.String currentPath;

    FileWithPath() {
        logWriter = null;
        currentPath = "";
    }

    public java.lang.String getPath() {
        return currentPath;
    }

    public java.io.OutputStreamWriter getFile(java.lang.String s, boolean flag) throws java.io.IOException {
        if (!currentPath.equals(s)) {
            if (logWriter != null) {
                logWriter.close();
            }
            if (com.dragonflow.Utils.I18N.isI18N) {
                logWriter = new OutputStreamWriter(new FileOutputStream(s, flag), com.dragonflow.Utils.I18N.nullEncoding());
            } else {
                logWriter = new OutputStreamWriter(new FileOutputStream(s, flag));
            }
            currentPath = s;
        }
        return logWriter;
    }

    protected void finalize() throws java.io.IOException {
        if (logWriter != null) {
            logWriter.close();
        }
    }
}
