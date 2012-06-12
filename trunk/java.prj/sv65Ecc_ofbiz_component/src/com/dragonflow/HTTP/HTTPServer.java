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

import java.net.ServerSocket;
import java.util.HashSet;

import jgl.Array;
import jgl.HashMap;

// Referenced classes of package com.dragonflow.HTTP:
// HTTPRequestThread, VirtualDirectory

public class HTTPServer
    implements Runnable
{

    private java.net.ServerSocket serverSocket;
    private boolean running;
    private jgl.Array virtualDirectories;
    private jgl.HashMap typeMap;
    private boolean sslEnabled;
    public boolean keepAliveEnabled;
    public int port;
    private int numConnections;
    private int maxConnections;
    protected Thread serverThread;
    static boolean debug = false;
    static jgl.HashMap config;
    static String strPages[];
    static java.util.HashSet filter;
    long lastTime;

    public HTTPServer(int i, int j, boolean flag, boolean flag1)
    {
        serverSocket = null;
        running = true;
        virtualDirectories = new Array();
        typeMap = new HashMap();
        sslEnabled = false;
        keepAliveEnabled = false;
        port = 8888;
        numConnections = 0;
        maxConnections = 0;
        lastTime = 0L;
        port = i;
        sslEnabled = flag;
        keepAliveEnabled = flag1;
        if(j > 0)
        {
            maxConnections = j;
        }
        addType(".old", "text/plain");
        addType(".log", "text/plain");
        addType(".config", "text/plain");
        addType(".dyn", "text/plain");
        addType(".mg", "text/plain");
        addType(".html", "text/html");
        addType(".pdf", "application/pdf");
        addType(".htm", "text/html");
        addType(".gif", "image/gif");
        addType(".png", "image/png");
        addType(".jpg", "image/jpeg");
        addType(".jpeg", "image/jpeg");
        addType(".au", "audio/basic");
        addType(".wav", "audio/x-wav");
    }

    static void dump(String as[])
    {
        for(int i = 0; i < as.length; i++)
        {
            com.dragonflow.Utils.TextUtils.debugPrint(i + ": " + as[i]);
        }

    }

    public void startServer()
        throws java.io.IOException
    {
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        String s = siteviewgroup.getSetting("_httpListenerIP");
        javax.net.ServerSocketFactory serversocketfactory = null;
        String s1 = "HTTP";
        if(sslEnabled)
        {
            serversocketfactory = com.dragonflow.Utils.SocketStream.getSSLServerFactory();
            s1 = "HTTPS";
        }
        if(s.length() > 0)
        {
            java.net.InetAddress inetaddress = java.net.InetAddress.getByName(s);
            com.dragonflow.Log.LogManager.log("RunMonitor", "Starting " + s1 + " Server listener on " + s + ":" + port);
            int i = 0;
            if(maxConnections > 0)
            {
                i = maxConnections;
            } else
            {
                i = 20;
            }
            com.dragonflow.Log.LogManager.log("RunMonitor", "Number of maximum connections accepted is : " + i + " on " + s + ":" + port);
            if(serversocketfactory != null)
            {
                serverSocket = serversocketfactory.createServerSocket(port, i, inetaddress);
            } else
            {
                serverSocket = new ServerSocket(port, i, inetaddress);
            }
        } else
        {
            com.dragonflow.Log.LogManager.log("RunMonitor", "Starting " + s1 + " Server listener on " + port);
            if(serversocketfactory != null)
            {
                serverSocket = serversocketfactory.createServerSocket(port);
            } else
            {
                serverSocket = new ServerSocket(port);
            }
        }
        if(sslEnabled)
        {
            com.dragonflow.Log.LogManager.log("RunMonitor", com.dragonflow.Utils.SSLSocketStream.certificateDescription);
        }
        serverThread = new Thread(this);
        serverThread.setName("HTTP Server on port " + port);
        serverThread.setPriority(6);
        serverThread.start();
    }

    public void stopServer()
    {
        running = false;
        serverThread.stop();
        try
        {
            serverThread.join(15000L);
        }
        catch(InterruptedException interruptedexception) { }
        com.dragonflow.Log.LogManager.log("RunMonitor", "Shut down HTTP Server on port " + port);
        serverThread = null;
    }

    void timeStamp()
    {
        long l = System.currentTimeMillis();
        if(lastTime != 0L)
        {
            System.out.print((l - lastTime) + ":");
        }
        lastTime = l;
    }

    public void incConnections()
    {
        numConnections++;
    }

    public void decConnections()
    {
        numConnections--;
    }

    public int getConnections()
    {
        return numConnections;
    }

    public int getMaxConnections()
    {
        return maxConnections;
    }

    public void run()
    {
        int i = 10000;
        try
        {
            do
            {
                if(!running)
                {
                    break;
                }
                i++;
                java.net.Socket socket = null;
                try
                {
                    if(debug)
                    {
                        System.out.println(i + "-HTTPSERVER - waiting for a request ");
                    }
                    socket = serverSocket.accept();
					// if(debug)
					{
						System.out.println(i + "-HTTPSERVER - got a request from :" + socket.getRemoteSocketAddress());
					}
                    if(getMaxConnections() > 0)
                    {
                        if(debug)
                        {
                            System.out.println(i + "-HTTPSERVER - maxConnections > 0");
                        }
                        incConnections();
                    }
                }
                catch(java.io.IOException ioexception)
                {
                    System.out.println("Could not accept() on port " + port + ": " + ioexception.getMessage());
                    continue;
                }
                if(debug)
                {
                    System.out.println(i + "-HTTPSERVER - making new HTTPRequestThread ");
                }
                new HTTPRequestThread(this, socket, keepAliveEnabled);
                if(debug)
                {
                    System.out.println(i + "-HTTPSERVER - back from HTTPRequestThread ");
                }
            } while(true);
        }
        finally
        {
            try
            {
                serverSocket.close();
            }
            catch(java.io.IOException ioexception1)
            {
                System.out.println("Could not close server socket." + ioexception1.getMessage());
            }
            catch(Exception exception1)
            {
                exception1.printStackTrace();
            }
        }
    }

    public void addVirtualDirectory(String s, String s1)
    {
        virtualDirectories.add(new VirtualDirectory(s, s1));
    }

    public void addCGIVirtualDirectory(String s, String s1)
    {
        virtualDirectories.add(new VirtualDirectory(s, s1, true));
    }

    com.dragonflow.HTTP.VirtualDirectory getVirtualDirectory(String s)
    {
        for(java.util.Enumeration enumeration = virtualDirectories.elements(); enumeration.hasMoreElements();)
        {
            com.dragonflow.HTTP.VirtualDirectory virtualdirectory = (com.dragonflow.HTTP.VirtualDirectory)enumeration.nextElement();
            String s1 = virtualdirectory.getFullDocumentPath(s);
            if(s1 != null)
            {
                return virtualdirectory;
            }
        }

        return null;
    }

    public void addType(String s, String s1)
    {
        typeMap.put(s, s1);
    }

    String getType(String s)
    {
        String s1 = (String)typeMap.get(s);
        if(s1 == null)
        {
            s1 = "text/plain";
        }
        return s1;
    }

    static 
    {
        config = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        strPages = com.dragonflow.Utils.TextUtils.split(com.dragonflow.Utils.TextUtils.getValue(config, "_serverFilter").toLowerCase(), ";");
        filter = new HashSet();
        String s = System.getProperty("HTTPServer.debug");
        if(s != null && s.length() > 0)
        {
            debug = true;
        }
        for(int i = 0; i < strPages.length; i++)
        {
            filter.add(strPages[i]);
        }

    }
}
