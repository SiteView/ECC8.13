/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.SSH;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.util.HashMap;

// Referenced classes of package com.dragonflow.SSH:
// SSHRemote, SSHCloser, SSHPlinkClient, SSHJavaClient

public class SSHManager {

    private static com.dragonflow.SSH.SSHManager manager;

    private java.util.HashMap remotesMap;

    static boolean debug = false;

    public static final java.lang.String SSH_CLIENT_PLINK = "plink";

    public static final java.lang.String SSH_CLIENT_JAVA = "java";

    private java.lang.String clientOverride;

    private java.lang.String globalCacheSetting;

    private java.lang.String numClientConnections;

    public static synchronized com.dragonflow.SSH.SSHManager getInstance() {
        if (manager == null) {
            manager = new SSHManager();
        }
        return manager;
    }

    public int execute(com.dragonflow.Utils.RemoteCommandLine remotecommandline, com.dragonflow.SiteView.Machine machine, java.lang.String s, int i, boolean flag, java.io.PrintWriter printwriter, jgl.Array array) {
        com.dragonflow.SSH.SSHRemote sshremote = null;
        java.lang.String s1 = !machine.getProperty(com.dragonflow.SiteView.Machine.pOS).equals("NT") && !machine.getProperty(com.dragonflow.SiteView.Machine.pOS).equals("NT") ? "" : "NT";
        java.lang.String s2 = machine.getProperty(com.dragonflow.SiteView.Machine.pID) + s1;
        synchronized (remotesMap) {
            sshremote = (com.dragonflow.SSH.SSHRemote) remotesMap.get(s2);
            if (sshremote == null) {
                if (debug) {
                    com.dragonflow.Log.LogManager.log("Error", "SSHManager Info: adding a new remote to the map, key=" + s2);
                }
                sshremote = new SSHRemote(machine, i);
                remotesMap.put(s2, sshremote);
            }
        }
        return sshremote.execute(remotecommandline, s, flag, printwriter, array);
    }

    SSHManager() {
        remotesMap = new HashMap();
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        clientOverride = (java.lang.String) hashmap.get("_sshGlobalClient");
        numClientConnections = (java.lang.String) hashmap.get("_sshGlobalNumConnections");
        globalCacheSetting = (java.lang.String) hashmap.get("_sshGlobalCache");
    }

    public void deleteRemote(java.lang.String s) {
        com.dragonflow.SSH.SSHRemote sshremote = null;
        synchronized (remotesMap) {
            sshremote = (com.dragonflow.SSH.SSHRemote) remotesMap.remove(s);
        }
        if (sshremote != null) {
            sshremote.close();
        }
    }

    public java.lang.String checkClient(java.lang.String s) {
        if (s == null || s.length() == 0 || s.equals("plink")) {
            return com.dragonflow.SSH.SSHPlinkClient.checkClient();
        }
        if (s.equals("java")) {
            return com.dragonflow.SSH.SSHJavaClient.checkClient();
        } else {
            return "SSH client not defined";
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     */
    public void closeAll() {
        synchronized (remotesMap) {
            java.lang.Thread athread[];
            long l;
            long l1;
            java.util.Collection collection = remotesMap.values();
            athread = new java.lang.Thread[collection.size()];
            int i = 0;
            for (java.util.Iterator iterator = collection.iterator(); iterator.hasNext();) {
                com.dragonflow.SSH.SSHRemote sshremote = (com.dragonflow.SSH.SSHRemote) iterator.next();
                java.lang.Thread thread = new Thread(new SSHCloser(sshremote));
                thread.start();
                athread[i ++] = thread;
            }

            l = java.lang.System.currentTimeMillis() + 6000L;
            l1 = 4000L;

            for (int j = 0; j < athread.length; j ++) {
                long l3;
                long l2 = l - java.lang.System.currentTimeMillis();
                l3 = l1 >= l2 ? l2 : l1;
                if (l3 < 0L) {
                    break;
                }
                try {
                    athread[j].join(l3);
                } catch (java.lang.InterruptedException interruptedexception) {
                    break;
                }
            }

            remotesMap.clear();
        }
    }

    public java.lang.String getClientOverride() {
        return clientOverride;
    }

    public boolean globalClientIsSet() {
        return clientOverride != null && clientOverride.length() > 0;
    }

    public boolean globalCacheIsSet() {
        return globalCacheSetting != null && globalCacheSetting.length() > 0;
    }

    public boolean globalCacheSetting() {
        return globalCacheSetting != null && globalCacheSetting.length() != 0 && !globalCacheSetting.equals("false");
    }

    public boolean globalNumClientsIsSet() {
        return numClientConnections != null && numClientConnections.length() > 0;
    }

    public java.lang.String getNumClientConnections() {
        return numClientConnections;
    }

    static {
        java.lang.String s = java.lang.System.getProperty("SSHManager.debug");
        if (s != null && s.length() > 0) {
            debug = true;
        }
    }
}
