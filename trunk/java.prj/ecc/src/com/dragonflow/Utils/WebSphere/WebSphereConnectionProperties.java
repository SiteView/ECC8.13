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

public class WebSphereConnectionProperties implements java.io.Serializable {

    public static final int VERSION_3_5 = 0;

    public static final int VERSION_4_X = 1;

    public static final int VERSION_5_X = 2;

    public static final java.lang.String VERSION_3_5_STR = "3.5x";

    public static final java.lang.String VERSION_4_X_STR = "4.x";

    public static final java.lang.String VERSION_5_X_STR = "5.x";

    java.lang.String serverName;

    java.lang.String username;

    java.lang.String password;

    java.lang.String clientProps;

    int port;

    int version;

    java.lang.String hashID;

    public WebSphereConnectionProperties(java.lang.String s, java.lang.String s1, java.lang.String s2, int i, java.lang.String s3) {
        serverName = s;
        username = s1;
        password = s2;
        port = i;
        detectVersion(s3);
        java.lang.StringBuffer stringbuffer = (new StringBuffer(s)).append(s1).append(s2);
        stringbuffer.append(i).append(s3);
        hashID = stringbuffer.toString();
    }

    private void detectVersion(java.lang.String s) {
        if (s.equals("4.x")) {
            version = 1;
        } else {
            version = 2;
        }
    }

    public java.lang.String getHashID() {
        return hashID;
    }

    public java.lang.String getServerName() {
        return serverName;
    }

    public java.lang.String getUsername() {
        return username;
    }

    public java.lang.String getPassword() {
        return password;
    }

    public int getPort() {
        return port;
    }

    public int getVersion() {
        return version;
    }

    public java.lang.String getAPI() {
        if (version == 1) {
            return "PMI";
        } else {
            return "JMX";
        }
    }
}
