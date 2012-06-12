 /*
  * Created on 2005-2-9 3:06:20
  *
  * .java
  *
  * History:
  *
  */
  package com.dragonflow.Utils;

 /**
     * Comment for <code></code>
     * 
     * @author
     * @version 0.0
     * 
     * 
     */

import java.util.Properties;

import jgl.Array;

public class ArgsPackagerUtil
{

    public ArgsPackagerUtil()
    {
    }

    public static String packageArgs(jgl.Array array)
    {
        return com.dragonflow.Utils.ArgsPackagerUtil.packageArgs(array, 0, array.size() - 1);
    }

    public static String packageArgs(jgl.Array array, int i, int j)
    {
        StringBuffer stringbuffer = new StringBuffer();
        int k = array.size();
        for(int l = i; l <= j; l++)
        {
            Object obj = array.at(l);
            String s = "";
            if(obj instanceof String)
            {
                s = (String)obj;
            } else
            {
                jgl.Array array1 = (jgl.Array)array.at(l);
                s = com.dragonflow.Utils.ArgsPackagerUtil.packageArgs(array1, 0, array1.size() - 1);
            }
            stringbuffer.append(com.dragonflow.Utils.ArgsPackagerUtil.packageArg(s));
        }

        return stringbuffer.toString();
    }

    public static String packageArg(String s)
    {
        String s1 = Integer.toString(s.length());
        return s1 + " " + s;
    }

    public static String packageArgs(String as[], int i, int j)
    {
        StringBuffer stringbuffer = new StringBuffer();
        int k = as.length;
        for(int l = i; l <= j; l++)
        {
            String s = as[l];
            stringbuffer.append(com.dragonflow.Utils.ArgsPackagerUtil.packageArg(s));
        }

        return stringbuffer.toString();
    }

    public static int getNextArg(String s, int i, StringBuffer stringbuffer)
    {
        boolean flag = false;
        int j = s.indexOf(' ', i);
        if(j < 0)
        {
            return -1;
        } else
        {
            int k = Integer.parseInt(s.substring(i, j));
            stringbuffer.append(s.substring(j + 1, j + 1 + k));
            return j + 1 + k;
        }
    }

    public static jgl.Array unpackageArgs(String s)
    {
        jgl.Array array = new Array();
        int i = 0;
        do
        {
            StringBuffer stringbuffer = new StringBuffer();
            i = com.dragonflow.Utils.ArgsPackagerUtil.getNextArg(s, i, stringbuffer);
            if(i < 0)
            {
                return array;
            }
            array.add(stringbuffer.toString());
        } while(true);
    }

    public static String[] unpackageArgsToStrArray(String s)
    {
        int i = com.dragonflow.Utils.ArgsPackagerUtil.getArgsNum(s);
        if(i <= 0)
        {
            return null;
        }
        String as[] = new String[i];
        int j = 0;
        for(int k = 0; k < i; k++)
        {
            StringBuffer stringbuffer = new StringBuffer();
            j = com.dragonflow.Utils.ArgsPackagerUtil.getNextArg(s, j, stringbuffer);
            as[k] = stringbuffer.toString();
        }

        return as;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param bufferedreader
     * @param stringbuffer
     * @return
     */
    public static String unpackageStreamArgsToStrings(java.io.BufferedReader bufferedreader, StringBuffer stringbuffer)
    {
       try {
        char ac[];
        ac = new char[1];
        if(bufferedreader == null || stringbuffer == null)
        {
            return null;
        }
        stringbuffer.delete(0, stringbuffer.length());
        char ac1[];
        if(bufferedreader.ready())
        {
        for (int i = 0; i < 1; )/*dingbing.xu ???*/
            {
            bufferedreader.read(ac);
            stringbuffer.append(ac[0]);
            if(ac[0] == ' ')
            {
                i++;
            }
        }
        
        int j = Integer.parseInt((new String(stringbuffer)).trim());
        ac1 = new char[j];
        bufferedreader.read(ac1);
        return new String(ac1);
        }
        return null;
       }
        catch (java.io.IOException ioexception) {
        ioexception.printStackTrace();
        return null;
        }
    }

    public static int getArgsNum(String s)
    {
        int i = 0;
        int j = 0;
        boolean flag = false;
        do
        {
            int k = s.indexOf(' ', j);
            if(k < 0)
            {
                return i;
            }
            i++;
            int l = Integer.parseInt(s.substring(j, k));
            j = k + 1 + l;
        } while(true);
    }

    public static String encodeArgs(String s)
    {
        StringBuffer stringbuffer = new StringBuffer();
        for(int i = 0; i < s.length(); i++)
        {
            if(i != 0)
            {
                stringbuffer.append('.');
            }
            stringbuffer.append(s.charAt(i));
        }

        return stringbuffer.toString();
    }

    public static String decodeArgs(String s)
    {
        int i = 0;
        boolean flag = false;
        StringBuffer stringbuffer = new StringBuffer();
        int j;
        for(int k = s.length(); i < k; i = j + 1)
        {
            j = s.indexOf('.', i);
            if(j < 0)
            {
                j = k;
            }
            String s1 = s.substring(i, j);
            stringbuffer.append((char)Integer.parseInt(s1));
        }

        return stringbuffer.toString();
    }

    public static void main(String args[])
    {
        String s = "str1_1";
        String s1 = "str1_2";
        String s2 = "";
        jgl.Array array = new Array();
        array.add(s);
        array.add(s1);
        array.add(s2);
        String s3 = com.dragonflow.Utils.ArgsPackagerUtil.packageArgs(array, 0, array.size() - 1);
        String s4 = "6 str1_16 str1_20 ";
        if(s3.compareTo(s4) != 0)
        {
            System.out.println("Error");
        } else
        {
            System.out.println("Success");
        }
        System.out.println("input   : " + s4);
        System.out.println("output  : " + s3);
        jgl.Array array1 = new Array();
        String s5 = "str2";
        array1.add(array);
        array1.add(s5);
        s3 = com.dragonflow.Utils.ArgsPackagerUtil.packageArgs(array1, 0, array1.size() - 1);
        s4 = "18 6 str1_16 str1_20 4 str2";
        if(s3.compareTo(s4) != 0)
        {
            System.out.println("Error");
        } else
        {
            System.out.println("Success");
        }
        System.out.println("input   : " + s4);
        System.out.println("output  : " + s3);
        String s6 = com.dragonflow.Utils.ArgsPackagerUtil.encodeArgs(s3);
        String s7 = com.dragonflow.Utils.ArgsPackagerUtil.decodeArgs(s6);
        if(s7.compareTo(s3) != 0)
        {
            System.out.println("Encode Error");
        } else
        {
            System.out.println("Encode Success");
        }
        System.out.println("input   : " + s3);
        System.out.println("output  : " + s7);
    }

    public static java.util.Properties unpackageToProperties(String s)
    {
        String as[] = com.dragonflow.Utils.ArgsPackagerUtil.unpackageArgsToStrArray(s);
        java.util.Properties properties = new Properties();
        for(int i = 0; i < as.length; i++)
        {
            String as1[] = com.dragonflow.Utils.ArgsPackagerUtil.unpackageArgsToStrArray(as[i]);
            if(as1.length != 2)
            {
                return null;
            }
            properties.setProperty(as1[0], as1[1]);
        }

        return properties;
    }

    public static String packageProps(java.util.Properties properties)
    {
        String as[] = new String[properties.size()];
        java.util.Set set = properties.entrySet();
        java.util.Iterator iterator = set.iterator();
        for(int i = 0; i < properties.size(); i++)
        {
            java.util.Map.Entry entry = (java.util.Map.Entry)iterator.next();
            String as1[] = new String[2];
            as1[0] = (String)entry.getKey();
            as1[1] = (String)entry.getValue();
            as[i] = com.dragonflow.Utils.ArgsPackagerUtil.packageArgs(as1, 0, 1);
        }

        return com.dragonflow.Utils.ArgsPackagerUtil.packageArgs(as, 0, as.length - 1);
    }
}
