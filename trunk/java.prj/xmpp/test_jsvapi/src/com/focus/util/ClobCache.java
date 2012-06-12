// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ClobCache.java

package com.focus.util;


// Referenced classes of package com.focus.util:
//            Cacheable

public final class ClobCache
    implements Cacheable
{

    public ClobCache()
    {
        lastaccess = System.currentTimeMillis();
        clob_content = null;
        byte_size = 0L;
        no_use = false;
    }

    public long getSize()
    {
        return byte_size;
    }

    public void makeNoUse()
    {
        no_use = true;
        clob_content = "";
    }

    public boolean isNoUse()
    {
        return no_use;
    }

    public String getClob_content()
    {
        return clob_content;
    }

    public void setClob_content(String clob_content)
    {
        byte_size = clob_content.getBytes().length;
        this.clob_content = clob_content;
    }

    public long getLastAccess()
    {
        return lastaccess;
    }

    public void setLastAccess(long time)
    {
        lastaccess = time;
    }

    long lastaccess;
    String clob_content;
    long byte_size;
    boolean no_use;
}
