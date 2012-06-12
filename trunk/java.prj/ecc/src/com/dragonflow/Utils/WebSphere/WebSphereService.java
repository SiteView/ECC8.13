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

// Referenced classes of package com.dragonflow.Utils.WebSphere:
// WebSphereConnectionProperties, WebSphereServer

public interface WebSphereService extends java.rmi.Remote {

    public static final java.lang.String URL_PROPERTY = "registryURL";

    public static final java.lang.String DEBUG_PROPERTY = "debug";

    public static final java.lang.String HEART_BEAT_FREQUENCY = "heartBeatFrequency";

    public static final java.lang.String HOST = "host";

    public static final java.lang.String PORT = "port";

    public static final java.lang.String TOKEN_PROPERTY = "token";

    public abstract com.dragonflow.Utils.WebSphere.WebSphereServer getServer(com.dragonflow.Utils.WebSphere.WebSphereConnectionProperties websphereconnectionproperties) throws java.rmi.RemoteException;

    public abstract long getToken() throws java.rmi.RemoteException;
}
