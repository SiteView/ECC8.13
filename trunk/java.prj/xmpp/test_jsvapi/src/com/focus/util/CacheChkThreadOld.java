// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   CacheChkThreadOld.java

package com.focus.util;

import java.io.PrintStream;
import java.util.Set;

// Referenced classes of package com.focus.util:
//            CacheMapOld, Cacheable

public class CacheChkThreadOld extends Thread
{

    public CacheChkThreadOld(CacheMapOld cachemap)
    {
        this.cachemap = null;
        this.cachemap = cachemap;
    }

    public void start()
    {
        super.start();
    }

    public void run()
    {
        try
        {
            do
                try
                {
                    do
                    {
                        cachemap.thread_start = true;
                        if(cachemap.size() != 0)
                            checkTimeout();
                        Thread.sleep(CacheMapOld.cache_check_sleep);
                    } while(true);
                }
                catch(Exception e)
                {
                    System.out.print("CahceChkThread-run:");
                    System.out.println(e.getMessage());
                }
            while(true);
        }
        finally
        {
            cachemap.thread_start = false;
        }
    }

    public void checkTimeout()
    {
        try
        {
            Set set = cachemap.keySet();
            Object keys[] = set.toArray();
            for(int i = 0; i < keys.length; i++)
            {
                Cacheable cacheable = cachemap.safeGet(keys[i]);
                if(cacheable != null)
                {
                    CacheMapOld _tmp = cachemap;
                    if(System.currentTimeMillis() - cacheable.getLastAccess() > CacheMapOld.timeoutValue)
                        cachemap.really_remove(keys[i]);
                }
            }

        }
        catch(Exception err)
        {
            System.out.print("CacheChkThread:");
            System.out.println(err.getMessage());
        }
    }

    CacheMapOld cachemap;
}
