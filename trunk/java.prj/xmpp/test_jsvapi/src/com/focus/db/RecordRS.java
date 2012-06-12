// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   RecordRS.java

package com.focus.db;

import com.focus.util.Cacheable;
import java.util.HashMap;

public final class RecordRS
    implements Cacheable
{

    public RecordRS(String rec_id)
    {
        lastAccess = System.currentTimeMillis();
        hm = new HashMap();
        byteSize = 0L;
        is_no_use = false;
        id = rec_id;
    }

    public Object getObject(String fildName)
    {
        Object val = hm.get(fildName);
        if(val == null)
            return "";
        else
            return val;
    }

    public void setObject(String fieldName, Object value)
    {
        if(value != null)
        {
            byteSize += value.toString().getBytes().length;
            hm.put(fieldName, value);
        }
    }

    public boolean equals(Object obj)
    {
        return ((RecordRS)obj).id.equals(id);
    }

    public long getSize()
    {
        return byteSize;
    }

    public void makeNoUse()
    {
        is_no_use = true;
    }

    public boolean isNoUse()
    {
        return is_no_use;
    }

    public long getLastAccess()
    {
        return lastAccess;
    }

    public void setLastAccess(long time)
    {
        lastAccess = time;
    }

    long lastAccess;
    public String id;
    private HashMap hm;
    private long byteSize;
    private boolean is_no_use;
}
