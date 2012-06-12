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

import java.util.HashMap;

import com.dragonflow.Utils.NullSecurityManager;

// Referenced classes of package com.dragonflow.Utils.WebSphere:
// WebSphereRegistryHeartBeat, WebSphereServer, WebSphereServerImpl,
// WebSphereService,
// WebSphereConnectionProperties

public class WebSphereServiceImpl extends java.rmi.server.UnicastRemoteObject
    implements com.dragonflow.Utils.WebSphere.WebSphereService
{

    protected java.util.Map servers;
    protected static final String packagePrefix = "com.dragonflow.Utils.WebSphere";
    protected String url;
    boolean debug;
    private long token;

    public WebSphereServiceImpl()
        throws java.rmi.RemoteException
    {
        servers = java.util.Collections.synchronizedMap(new HashMap());
        url = null;
        debug = Boolean.getBoolean("com.dragonflow.Utils.WebSphere.debug");
        url = System.getProperty("com.dragonflow.Utils.WebSphere.registryURL", "");
        try
        {
            token = Long.parseLong(System.getProperty("com.dragonflow.Utils.WebSphere.token"));
        }
        catch(NumberFormatException numberformatexception)
        {
            token = -1L;
        }
    }

    public static void main(String args[])
    {
        if(System.getSecurityManager() == null)
        {
            System.out.println("WebSphereServiceImpl installing new SecurityManager... ");
            System.setSecurityManager(new NullSecurityManager());
        }
        Object obj = null;
        try
        {
            com.dragonflow.Utils.WebSphere.WebSphereServiceImpl websphereserviceimpl = new WebSphereServiceImpl();
            System.out.println("Attempting to bind WebSphereService in rmiregistry as " + websphereserviceimpl.url);
            java.rmi.Naming.rebind(websphereserviceimpl.url, websphereserviceimpl);
            System.out.println("WebSphereService successfully bound in rmiregistry as " + websphereserviceimpl.url);
            System.out.flush();
            long l;
            try
            {
                l = Long.parseLong(System.getProperty("com.dragonflow.Utils.WebSphere.heartBeatFrequency", "3000"));
            }
            catch(NumberFormatException numberformatexception)
            {
                l = 3000L;
                System.err.println("WebSphereService process could not parse the heartBeatFrequencyproperty.  Using default of " + l + " milliseconds.");
            }
            String s = System.getProperty("com.dragonflow.Utils.WebSphere.host", "localhost");
            int i;
            try
            {
                i = Integer.parseInt(System.getProperty("com.dragonflow.Utils.WebSphere.port", "1099"));
            }
            catch(NumberFormatException numberformatexception1)
            {
                i = 1099;
                System.err.println("WebSphereService process could not parse the portproperty.  Using default of " + i + " milliseconds.");
            }
            (new WebSphereRegistryHeartBeat(websphereserviceimpl.token, websphereserviceimpl.url, s, i, l)).start();
        }
        catch(Exception exception)
        {
            System.err.println("WebSphereServiceImpl.main() encountered an exception: " + exception);
            exception.printStackTrace();
        }
    }

    public com.dragonflow.Utils.WebSphere.WebSphereServer getServer(com.dragonflow.Utils.WebSphere.WebSphereConnectionProperties websphereconnectionproperties)
        throws java.rmi.RemoteException
    {
        if(debug)
        {
            System.err.println("Entering WebSphereServiceImpl.getServer() with connProps=" + websphereconnectionproperties);
        }
        Object obj;
        synchronized(this)
        {
            obj = (com.dragonflow.Utils.WebSphere.WebSphereServer)servers.get(websphereconnectionproperties.getHashID());
            if(debug)
            {
                System.err.println("WebSphereServiceImpl.getServer() got cached server=" + obj + " with connProps.getHashID()=" + websphereconnectionproperties.getHashID());
            }
            if(obj == null)
            {
                if(debug)
                {
                    System.err.println("WebSphereServiceImpl.getServer() is instantiating new server because none was found in the cache.");
                }
                obj = new WebSphereServerImpl(websphereconnectionproperties);
                servers.put(websphereconnectionproperties.getHashID(), obj);
            }
        }
        if(debug)
        {
            System.err.println("Leaving WebSphereServiceImpl.getServer() with server=" + obj);
        }
        return ((com.dragonflow.Utils.WebSphere.WebSphereServer) (obj));
    }

    public long getToken()
        throws java.rmi.RemoteException
    {
        return token;
    }
}
