// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Cacheable.java

package com.focus.util;


public interface Cacheable
{

    public abstract long getSize();

    public abstract void makeNoUse();

    public abstract boolean isNoUse();

    public abstract long getLastAccess();

    public abstract void setLastAccess(long l);
}
