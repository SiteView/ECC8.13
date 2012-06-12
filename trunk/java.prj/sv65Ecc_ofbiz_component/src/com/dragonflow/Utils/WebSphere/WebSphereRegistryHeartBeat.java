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
// WebSphereService

public class WebSphereRegistryHeartBeat extends Thread {

    int registryPort;

    String registryHost;

    long frequency;

    String url;

    long token;

    public WebSphereRegistryHeartBeat(long l, String s, String s1, int i, long l1) {
        registryPort = 1099;
        registryHost = "localhost";
        frequency = 2000L;
        token = l;
        url = s;
        registryHost = s1;
        registryPort = i;
        frequency = l1;
    }

    public void run() {
        do {
            Object obj = null;
            try {
                com.dragonflow.Utils.WebSphere.WebSphereService websphereservice = (com.dragonflow.Utils.WebSphere.WebSphereService) java.rmi.Naming.lookup(url);
                if (websphereservice.getToken() != token) {
                    System.exit(0);
                }
            } catch (Exception exception) {
                exception.printStackTrace();
                System.exit(0);
            }
            try {
                Thread.sleep(frequency);
            } catch (InterruptedException interruptedexception) {
                System.err.println("Sleep interrupted in HeartBeat Thread in WebSphereService process.");
            }
        } while (true);
    }
}
