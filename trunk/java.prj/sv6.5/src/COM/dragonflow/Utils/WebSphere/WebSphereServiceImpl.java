/*
 * 
 * Created on 2005-3-9 18:55:36
 *
 * PDHRawCounterCache.java
 *
 * History:
 *
 */
package COM.dragonflow.Utils.WebSphere;

import java.util.HashMap;

import COM.dragonflow.Utils.NullSecurityManager;

// Referenced classes of package COM.dragonflow.Utils.WebSphere:
// WebSphereRegistryHeartBeat, WebSphereServer, WebSphereServerImpl,
// WebSphereService,
// WebSphereConnectionProperties

public class WebSphereServiceImpl extends java.rmi.server.UnicastRemoteObject
    implements COM.dragonflow.Utils.WebSphere.WebSphereService
{

    protected java.util.Map servers;
    protected static final java.lang.String packagePrefix = "COM.dragonflow.Utils.WebSphere";
    protected java.lang.String url;
    boolean debug;
    private long token;

    public WebSphereServiceImpl()
        throws java.rmi.RemoteException
    {
        servers = java.util.Collections.synchronizedMap(new HashMap());
        url = null;
        debug = java.lang.Boolean.getBoolean("COM.dragonflow.Utils.WebSphere.debug");
        url = java.lang.System.getProperty("COM.dragonflow.Utils.WebSphere.registryURL", "");
        try
        {
            token = java.lang.Long.parseLong(java.lang.System.getProperty("COM.dragonflow.Utils.WebSphere.token"));
        }
        catch(java.lang.NumberFormatException numberformatexception)
        {
            token = -1L;
        }
    }

    public static void main(java.lang.String args[])
    {
        if(java.lang.System.getSecurityManager() == null)
        {
            java.lang.System.out.println("WebSphereServiceImpl installing new SecurityManager... ");
            java.lang.System.setSecurityManager(new NullSecurityManager());
        }
        Object obj = null;
        try
        {
            COM.dragonflow.Utils.WebSphere.WebSphereServiceImpl websphereserviceimpl = new WebSphereServiceImpl();
            java.lang.System.out.println("Attempting to bind WebSphereService in rmiregistry as " + websphereserviceimpl.url);
            java.rmi.Naming.rebind(websphereserviceimpl.url, websphereserviceimpl);
            java.lang.System.out.println("WebSphereService successfully bound in rmiregistry as " + websphereserviceimpl.url);
            java.lang.System.out.flush();
            long l;
            try
            {
                l = java.lang.Long.parseLong(java.lang.System.getProperty("COM.dragonflow.Utils.WebSphere.heartBeatFrequency", "3000"));
            }
            catch(java.lang.NumberFormatException numberformatexception)
            {
                l = 3000L;
                java.lang.System.err.println("WebSphereService process could not parse the heartBeatFrequencyproperty.  Using default of " + l + " milliseconds.");
            }
            java.lang.String s = java.lang.System.getProperty("COM.dragonflow.Utils.WebSphere.host", "localhost");
            int i;
            try
            {
                i = java.lang.Integer.parseInt(java.lang.System.getProperty("COM.dragonflow.Utils.WebSphere.port", "1099"));
            }
            catch(java.lang.NumberFormatException numberformatexception1)
            {
                i = 1099;
                java.lang.System.err.println("WebSphereService process could not parse the portproperty.  Using default of " + i + " milliseconds.");
            }
            (new WebSphereRegistryHeartBeat(websphereserviceimpl.token, websphereserviceimpl.url, s, i, l)).start();
        }
        catch(java.lang.Exception exception)
        {
            java.lang.System.err.println("WebSphereServiceImpl.main() encountered an exception: " + exception);
            exception.printStackTrace();
        }
    }

    public COM.dragonflow.Utils.WebSphere.WebSphereServer getServer(COM.dragonflow.Utils.WebSphere.WebSphereConnectionProperties websphereconnectionproperties)
        throws java.rmi.RemoteException
    {
        if(debug)
        {
            java.lang.System.err.println("Entering WebSphereServiceImpl.getServer() with connProps=" + websphereconnectionproperties);
        }
        java.lang.Object obj;
        synchronized(this)
        {
            obj = (COM.dragonflow.Utils.WebSphere.WebSphereServer)servers.get(websphereconnectionproperties.getHashID());
            if(debug)
            {
                java.lang.System.err.println("WebSphereServiceImpl.getServer() got cached server=" + obj + " with connProps.getHashID()=" + websphereconnectionproperties.getHashID());
            }
            if(obj == null)
            {
                if(debug)
                {
                    java.lang.System.err.println("WebSphereServiceImpl.getServer() is instantiating new server because none was found in the cache.");
                }
                obj = new WebSphereServerImpl(websphereconnectionproperties);
                servers.put(websphereconnectionproperties.getHashID(), obj);
            }
        }
        if(debug)
        {
            java.lang.System.err.println("Leaving WebSphereServiceImpl.getServer() with server=" + obj);
        }
        return ((COM.dragonflow.Utils.WebSphere.WebSphereServer) (obj));
    }

    public long getToken()
        throws java.rmi.RemoteException
    {
        return token;
    }
}
