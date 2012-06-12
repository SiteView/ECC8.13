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
import java.lang.reflect.Method;
import java.rmi.MarshalException;
import java.rmi.UnexpectedException;
import java.rmi.UnmarshalException;
import java.rmi.server.Operation;

// Referenced classes of package com.dragonflow.Utils.WebSphere:
// WebSphereServer, WebSphereCounter

public final class WebSphereServerImpl_Stub extends java.rmi.server.RemoteStub
    implements com.dragonflow.Utils.WebSphere.WebSphereServer, java.rmi.Remote
{

    private static final java.rmi.server.Operation operations[] = {
        new Operation("String getBrowseData()"), new Operation("com.dragonflow.Utils.WebSphere.WebSphereCounter getCounters(com.dragonflow.Utils.WebSphere.WebSphereCounter[])[]"), new Operation("String getServerName()")
    };
    private static final long interfaceHash = 0xf36e3583336c79d2L;
    private static final long serialVersionUID = 2L;
    private static boolean useNewInvoke;
    private static Method $method_getBrowseData_0;
    private static Method $method_getCounters_1;
    private static Method $method_getServerName_2;

    public WebSphereServerImpl_Stub()
    {
    }

    public WebSphereServerImpl_Stub(java.rmi.server.RemoteRef remoteref)
    {
        super(remoteref);
    }

    public String getBrowseData()
        throws java.rmi.RemoteException
    {
        try
        {
            if(useNewInvoke)
            {
                Object obj = super.ref.invoke(this, $method_getBrowseData_0, null, 0x8f52993aa062f7fbL);
                return (String)obj;
            }
            java.rmi.server.RemoteCall remotecall = super.ref.newCall(this, operations, 0, 0xf36e3583336c79d2L);
            super.ref.invoke(remotecall);
            String s;
            try
            {
                java.io.ObjectInput objectinput = remotecall.getInputStream();
                s = (String)objectinput.readObject();
            }
            catch(java.io.IOException ioexception)
            {
                throw new UnmarshalException("error unmarshalling return", ioexception);
            }
            catch(ClassNotFoundException classnotfoundexception)
            {
                throw new UnmarshalException("error unmarshalling return", classnotfoundexception);
            }
            finally
            {
                super.ref.done(remotecall);
            }
            return s;
        }
        catch(RuntimeException runtimeexception)
        {
            throw runtimeexception;
        }
        catch(java.rmi.RemoteException remoteexception)
        {
            throw remoteexception;
        }
        catch(Exception exception)
        {
            throw new UnexpectedException("undeclared checked exception", exception);
        }
    }

    public com.dragonflow.Utils.WebSphere.WebSphereCounter[] getCounters(com.dragonflow.Utils.WebSphere.WebSphereCounter awebspherecounter[])
        throws java.rmi.RemoteException
    {
        try
        {
            if(useNewInvoke)
            {
                Object obj = super.ref.invoke(this, $method_getCounters_1, new Object[] {
                    awebspherecounter
                }, 0x61a7d5ece71019b9L);
                return (com.dragonflow.Utils.WebSphere.WebSphereCounter[])obj;
            }
            java.rmi.server.RemoteCall remotecall = super.ref.newCall(this, operations, 1, 0xf36e3583336c79d2L);
            try
            {
                java.io.ObjectOutput objectoutput = remotecall.getOutputStream();
                objectoutput.writeObject(awebspherecounter);
            }
            catch(java.io.IOException ioexception)
            {
                throw new MarshalException("error marshalling arguments", ioexception);
            }
            super.ref.invoke(remotecall);
            com.dragonflow.Utils.WebSphere.WebSphereCounter awebspherecounter1[];
            try
            {
                java.io.ObjectInput objectinput = remotecall.getInputStream();
                awebspherecounter1 = (com.dragonflow.Utils.WebSphere.WebSphereCounter[])objectinput.readObject();
            }
            catch(java.io.IOException ioexception1)
            {
                throw new UnmarshalException("error unmarshalling return", ioexception1);
            }
            catch(ClassNotFoundException classnotfoundexception)
            {
                throw new UnmarshalException("error unmarshalling return", classnotfoundexception);
            }
            finally
            {
                super.ref.done(remotecall);
            }
            return awebspherecounter1;
        }
        catch(RuntimeException runtimeexception)
        {
            throw runtimeexception;
        }
        catch(java.rmi.RemoteException remoteexception)
        {
            throw remoteexception;
        }
        catch(Exception exception)
        {
            throw new UnexpectedException("undeclared checked exception", exception);
        }
    }

    public String getServerName()
        throws java.rmi.RemoteException
    {
        try
        {
            if(useNewInvoke)
            {
                Object obj = super.ref.invoke(this, $method_getServerName_2, null, 0x850816858666c3c4L);
                return (String)obj;
            }
            java.rmi.server.RemoteCall remotecall = super.ref.newCall(this, operations, 2, 0xf36e3583336c79d2L);
            super.ref.invoke(remotecall);
            String s;
            try
            {
                java.io.ObjectInput objectinput = remotecall.getInputStream();
                s = (String)objectinput.readObject();
            }
            catch(java.io.IOException ioexception)
            {
                throw new UnmarshalException("error unmarshalling return", ioexception);
            }
            catch(ClassNotFoundException classnotfoundexception)
            {
                throw new UnmarshalException("error unmarshalling return", classnotfoundexception);
            }
            finally
            {
                super.ref.done(remotecall);
            }
            return s;
        }
        catch(RuntimeException runtimeexception)
        {
            throw runtimeexception;
        }
        catch(java.rmi.RemoteException remoteexception)
        {
            throw remoteexception;
        }
        catch(Exception exception)
        {
            throw new UnexpectedException("undeclared checked exception", exception);
        }
    }

    static 
    {
        try
        {
            (java.rmi.server.RemoteRef.class).getMethod("invoke", new Class[] {
                java.rmi.Remote.class, Method.class, Object[].class, Long.TYPE
            });
            useNewInvoke = true;
            $method_getBrowseData_0 = (com.dragonflow.Utils.WebSphere.WebSphereServer.class).getMethod("getBrowseData", new Class[0]);
            $method_getCounters_1 = (com.dragonflow.Utils.WebSphere.WebSphereServer.class).getMethod("getCounters", new Class[] {
                com.dragonflow.Utils.WebSphere.WebSphereCounter[].class
            });
            $method_getServerName_2 = (com.dragonflow.Utils.WebSphere.WebSphereServer.class).getMethod("getServerName", new Class[0]);
        }
        catch(NoSuchMethodException _ex)
        {
            useNewInvoke = false;
        }
    }
}
