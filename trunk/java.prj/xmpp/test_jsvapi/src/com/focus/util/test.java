// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   test.java

package com.focus.util;

import java.io.PrintStream;
import java.text.DateFormat;
import java.util.Date;
import java.util.GregorianCalendar;

public class test
{

    public test()
    {
    }

    public static void main(String args[])
    {
        DateFormat dateFormat = DateFormat.getDateInstance(0);
        GregorianCalendar cal = new GregorianCalendar();
        cal.setTime(new Date());
        System.out.println("System Date: " + dateFormat.format(cal.getTime()));
        cal.set(7, 6);
        System.out.println("After Setting Day of Week to Friday: " + dateFormat.format(cal.getTime()));
        for(int friday13Counter = 0; friday13Counter <= 10;)
        {
            cal.add(5, 7);
            if(cal.get(5) == 13)
            {
                friday13Counter++;
                System.out.println(dateFormat.format(cal.getTime()));
            }
        }

    }
}
