// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   CacheMapOld.java

package com.focus.util;

import java.util.HashMap;

// Referenced classes of package com.focus.util:
//            Cacheable, CacheChkThreadOld

public class CacheMapOld extends HashMap
{

    public CacheMapOld()
    {
        thread_start = false;
    }

    public Object put(Object key, Object cacheRs)
    {
        if(!cache_used)
            return cacheRs;
        really_remove(key);
        total_size += ((Cacheable)cacheRs).getSize();
        super.put(key.toString(), (Cacheable)cacheRs);
        if((total_size >= max_size || cache_check_onsart) && !thread_start)
        {
            thread_start = true;
            (new CacheChkThreadOld(this)).start();
        }
        return cacheRs;
    }

    public Object get(Object key)
    {
        Cacheable rs = (Cacheable)super.get(key);
        if(rs == null || rs.isNoUse())
        {
            return null;
        } else
        {
            rs.setLastAccess(System.currentTimeMillis());
            return rs;
        }
    }

    public Cacheable safeGet(Object key)
    {
        return (Cacheable)super.get(key);
    }

    public Object remove(Object key)
    {
        Cacheable rs = (Cacheable)super.get(key);
        if(rs != null)
            rs.makeNoUse();
        return rs;
    }

    Object really_remove(Object key)
    {
        Cacheable rs = (Cacheable)super.remove(key);
        if(rs != null)
            total_size -= rs.getSize();
        return rs;
    }

    public static long timeoutValue = 0x36ee80L;
    public static long total_size = 0L;
    public static long max_size = 0x19000000L;
    public boolean thread_start;
    public static boolean cache_used = true;
    public static boolean cache_check_onsart = false;
    public static long cache_check_sleep = 0x493e0L;

}
