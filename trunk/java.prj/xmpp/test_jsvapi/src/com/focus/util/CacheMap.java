// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   CacheMap.java

package com.focus.util;

import com.opensymphony.oscache.base.Cache;
import com.opensymphony.oscache.base.NeedsRefreshException;

// Referenced classes of package com.focus.util:
//            Cacheable

public class CacheMap extends Cache
{

    public CacheMap()
    {
        super(true, false, true);
        thread_start = false;
    }

    public static void main(String args1[])
    {
    }

    public Object put(Object key, Object cacheRs)
    {
        if(!cache_used)
        {
            return cacheRs;
        } else
        {
            super.putInCache(key.toString(), (Cacheable)cacheRs);
            return cacheRs;
        }
    }

    public Object get(Object key)
    {
        try
        {
            Cacheable rs = (Cacheable)super.getFromCache(key.toString());
            if(rs == null || rs.isNoUse())
                return null;
            else
                return rs;
        }
        catch(NeedsRefreshException e)
        {
            return null;
        }
    }

    public Cacheable safeGet(Object key)
    {
        return (Cacheable)get(key);
    }

    public Object remove(Object key)
    {
        Object o = get(key);
        super.removeEntry(key.toString());
        return o;
    }

    Object really_remove(Object key)
    {
        Object o = get(key);
        remove(key);
        return o;
    }

    public static long timeoutValue = 0x36ee80L;
    public static long total_size = 0L;
    public static long max_size = 0x19000000L;
    public boolean thread_start;
    public static boolean cache_used = true;
    public static boolean cache_check_onsart = false;
    public static long cache_check_sleep = 0x493e0L;

}
