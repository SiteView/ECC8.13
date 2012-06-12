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

import java.io.File;
import java.io.FileInputStream;
import java.util.StringTokenizer;
import java.util.Vector;

import jgl.Array;
import jgl.ArrayIterator;
import jgl.HashMap;
import com.dragonflow.Properties.HashMapOrdered;

// Referenced classes of package com.dragonflow.Utils:
// TextUtils

public class MgParser
{

    public final int URL_POINTS = 1;
    final java.lang.String CLASS_KEY = "_class";
    java.lang.String groupsPath;
    final java.lang.String urlSequenceMonitor = "URLSequenceMonitor";
    final java.lang.String urlListMonitor = "URLListMonitor";
    final java.lang.String apacheMonitor = "ApacheMonitor";
    final java.lang.String aribaMonitor = "AribaMonitor";
    final java.lang.String aspMonitor = "ASPMonitor";
    final java.lang.String checkpointMonitor = "CheckPointMonitor";
    final java.lang.String coldfusionMonitor = "ColdFusionMonitor";
    final java.lang.String iisserverMonitor = "IISServerMonitor";
    final java.lang.String netscapeMonitor = "NetscapeMonitor";
    final java.lang.String realMonitor = "RealMonitor";
    final java.lang.String silverstreamMonitor = "SilverStreamMonitor";
    final java.lang.String windowsmediaMonitor = "WindowsMediaMonitor";
    final java.lang.String ebusinessChainMonitor = "EBusinessTransactionMonitor";
    final java.lang.String compositeMonitor = "CompositeMonitor";

    public MgParser(java.lang.String s)
    {
        groupsPath = "";
        java.io.File file = new File(s);
        if(file.exists() && file.isDirectory())
        {
            groupsPath = s;
        } else
        {
            java.lang.System.out.println(s + "unreadable");
        }
    }

    public static void main(java.lang.String args[])
    {
        com.dragonflow.Utils.MgParser mgparser;
        if(args.length == 1)
        {
            mgparser = new MgParser(args[0]);
        } else
        {
            java.lang.System.out.println("Usage: MgParser </path/to/groups/directory>");
            return;
        }
        java.lang.System.out.println();
        java.lang.Object aobj[] = new java.lang.Object[3];
        aobj[0] = aobj[1] = aobj[2] = new Integer(0);
        aobj = mgparser.getUsageStatistics(true, true, true);
        java.lang.System.out.println("points used: " + aobj[0]);
        java.lang.System.out.println("monitors used: " + aobj[1]);
        java.lang.System.out.println("monitor types used: ");
        jgl.HashMap hashmap = (jgl.HashMap)aobj[2];
        for(java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements(); java.lang.System.out.println())
        {
            java.lang.String s = (java.lang.String)enumeration.nextElement();
            java.lang.System.out.print("   " + s + ": " + com.dragonflow.Utils.TextUtils.getValue(hashmap, s) + " monitor");
            if((new Integer((java.lang.String)hashmap.get(s))).intValue() > 1)
            {
                java.lang.System.out.print("s");
            }
            java.lang.System.out.print(".");
        }

    }

    private java.util.Vector _getMgFiles()
    {
        java.io.File file = new File(com.dragonflow.SiteView.Platform.getRoot() + "/groups/");
        java.util.Vector vector = new Vector();
        int i = 0;
        if(file.isDirectory())
        {
            java.lang.String as[] = file.list();
            for(int j = 0; j < as.length; j++)
            {
                if(as[j].endsWith(".mg"))
                {
                    vector.addElement(as[j]);
                    i++;
                }
            }

        } else
        {
            java.lang.System.out.println(groupsPath + " is not a directory");
            return null;
        }
        return vector;
    }

    public java.lang.Object[] getUsageStatistics(boolean flag, boolean flag1, boolean flag2)
    {
        java.lang.Object aobj[] = new java.lang.Object[5];
        int i = 0;
        int j = 0;
        int k = 0;
        int l = 0;
        jgl.HashMap hashmap = new HashMap();
        aobj[2] = new Integer(-1);
        java.util.Vector vector;
        if((vector = _getMgFiles()) == null)
        {
            return null;
        }

        for(int i1 = 0; i1 < vector.size(); i1++)
        {
            jgl.Array array;
            try
            {
                array = com.dragonflow.Utils.MgParser.readFromFile(groupsPath + java.io.File.separatorChar + vector.elementAt(i1));
            }
            catch(java.io.IOException ioexception)
            {
                java.lang.System.out.println("readFromFile " + vector.elementAt(i1) + " failed");
                return null;
            }
            jgl.ArrayIterator arrayiterator = new ArrayIterator(array, 0);
            jgl.HashMap hashmap1 = new HashMap();
            while (arrayiterator.hasMoreElements())
                {
                jgl.HashMap hashmap2 = (jgl.HashMap)arrayiterator.nextElement();
                java.lang.String s = "";
                s = com.dragonflow.Utils.TextUtils.getValue(hashmap2, "_class");
                if(!s.equals("") && s.indexOf("Monitor") != -1)
                {
                    if(flag)
                    {
                        i += _countPointsInUse(hashmap2);
                    }
                    if(flag1)
                    {
                        j++;
                    }
                    if(flag2)
                    {
                        java.lang.String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, s);
                        if(s1.equals(""))
                        {
                            hashmap.add(s, "1");
                        } else
                        {
                            int j1 = (new Integer(s1)).intValue() + 1;
                            hashmap.put(s, java.lang.String.valueOf(j1));
                        }
                        if(s.equals("URLSequenceMonitor"))
                        {
                            k += _countURLSequenceMonitor(hashmap2);
                        } else
                        if(s.equals("URLListMonitor"))
                        {
                            l += _countURLListMonitor(hashmap2);
                        }
                    }
                }
            }
        }

        aobj[0] = new Integer(i);
        aobj[1] = new Integer(j);
        aobj[2] = hashmap;
        aobj[3] = new Integer(k);
        aobj[4] = new Integer(l);
        return aobj;
    }

    private int _countPointsInUse(jgl.HashMap hashmap)
    {
        int i = 0;
        jgl.HashMap hashmap1 = _defineAppPointUsage();
        java.util.Vector vector = _findSpecialMonitors();
        java.lang.String s = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_class");
        if(vector.contains(s))
        {
            int j = _countSpecialMonitor(hashmap, hashmap1, s);
            i += j;
        } else
        {
            i++;
        }
        return i;
    }

    private java.util.Vector _findSpecialMonitors()
    {
        java.util.Vector vector = new Vector();
        getClass();
        vector.addElement("URLSequenceMonitor");
        getClass();
        vector.addElement("URLListMonitor");
        getClass();
        vector.addElement("ApacheMonitor");
        getClass();
        vector.addElement("AribaMonitor");
        getClass();
        vector.addElement("ASPMonitor");
        getClass();
        vector.addElement("CheckPointMonitor");
        getClass();
        vector.addElement("ColdFusionMonitor");
        getClass();
        vector.addElement("IISServerMonitor");
        getClass();
        vector.addElement("NetscapeMonitor");
        getClass();
        vector.addElement("RealMonitor");
        getClass();
        vector.addElement("SilverStreamMonitor");
        getClass();
        vector.addElement("WindowsMediaMonitor");
        getClass();
        vector.addElement("EBusinessTransactionMonitor");
        getClass();
        vector.addElement("CompositeMonitor");
        return vector;
    }

    private int _countSpecialMonitor(jgl.HashMap hashmap, jgl.HashMap hashmap1, java.lang.String s)
    {
        if(s.equals("URLListMonitor"))
        {
            return _countURLListMonitor(hashmap);
        }
        if(s.equals("URLSequenceMonitor"))
        {
            return _countURLSequenceMonitor(hashmap);
        }
        if(s.equals("EBusinessTransactionMonitor"))
        {
            return 0;
        }
        if(s.equals("CompositeMonitor"))
        {
            return 0;
        } else
        {
            return _countAppMonitor(s, hashmap1);
        }
    }

    private int _countURLListMonitor(jgl.HashMap hashmap)
    {
        int i = 0;
        try
        {
            java.lang.StringBuffer stringbuffer = com.dragonflow.Utils.MgParser.readFile(com.dragonflow.Utils.TextUtils.getValue(hashmap, "_filename").toString());
            for(java.util.StringTokenizer stringtokenizer = new StringTokenizer(stringbuffer.toString()); stringtokenizer.hasMoreElements(); stringtokenizer.nextElement())
            {
                i++;
            }

        }
        catch(java.io.IOException ioexception)
        {
            java.lang.System.out.println("Couldn't read URL List file " + com.dragonflow.Utils.TextUtils.getValue(hashmap, "_filename"));
        }
        return i;
    }

    private int _countURLSequenceMonitor(jgl.HashMap hashmap)
    {
        java.util.Enumeration enumeration = hashmap.keys();
        java.lang.String s = "";
        int i = 0;
        while (enumeration.hasMoreElements()) {
            java.lang.String s1 = enumeration.nextElement().toString();
            if(s1.indexOf("_reference") > -1 && s1.indexOf("_referenceType") == -1 && !com.dragonflow.Utils.TextUtils.getValue(hashmap, s1).toString().equals(""))
            {
                i++;
            }
        }
        return i;
    }

    private int _countAppMonitor(java.lang.String s, jgl.HashMap hashmap)
    {
        java.lang.Integer integer = new Integer(com.dragonflow.Utils.TextUtils.getValue(hashmap, s).toString());
        return integer.intValue();
    }

    private jgl.HashMap _defineAppPointUsage()
    {
        jgl.HashMap hashmap = new HashMap();
        hashmap.add("ApacheMonitor", "5");
        hashmap.add("AribaMonitor", "10");
        hashmap.add("ASPMonitor", "10");
        hashmap.add("CheckPointMonitor", "8");
        hashmap.add("ColdFusionMonitor", "6");
        hashmap.add("IISServerMonitor", "10");
        hashmap.add("NetscapeMonitor", "6");
        hashmap.add("RealMonitor", "5");
        hashmap.add("SilverStreamMonitor", "10");
        hashmap.add("WindowsMediaMonitor", "10");
        return hashmap;
    }

    private boolean _checkValidClass(java.lang.String s)
    {
        return true;
    }

    public static jgl.Array readFromFile(java.lang.String s)
        throws java.io.IOException
    {
        java.lang.StringBuffer stringbuffer = com.dragonflow.Utils.MgParser.readFile(s);
        java.lang.String s1 = stringbuffer.toString();
        s1 = com.dragonflow.Utils.MgParser.replaceChar(s1, '\r', "");
        jgl.Array array = com.dragonflow.Utils.MgParser.split('\n', s1);
        return com.dragonflow.Utils.MgParser.readFrames(array.elements());
    }

    private static jgl.Array readFrames(java.util.Enumeration enumeration)
        throws java.io.IOException
    {
        jgl.Array array = new Array();
        do
        {
            jgl.HashMap hashmap = com.dragonflow.Utils.MgParser.readFrame(enumeration, "#");
            if(hashmap != null)
            {
                array.add(hashmap);
            } else
            {
                return array;
            }
        } while(true);
    }

    private static jgl.HashMap readFrame(java.util.Enumeration enumeration, java.lang.String s)
        throws java.io.IOException
    {
        com.dragonflow.Properties.HashMapOrdered hashmapordered = null;
        while (enumeration.hasMoreElements()) {
            java.lang.String s1 = (java.lang.String)enumeration.nextElement();
            if(s1 == null)
            {
                break;
            }
            if(!s1.startsWith("//"))
            {
                if(hashmapordered == null)
                {
                    hashmapordered = new HashMapOrdered(true);
                }
                if(s1.startsWith(s))
                {
                    return hashmapordered;
                }
                int i = s1.indexOf('=');
                if(i > 0)
                {
                    java.lang.String s2 = s1.substring(0, i);
                    java.lang.String s3 = s1.substring(i + 1);
                    hashmapordered.add(s2, s3);
                }
            }
        } 
        return hashmapordered;
    }

    private static java.lang.String replaceChar(java.lang.String s, char c, java.lang.String s1)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        for(int i = 0; i < s.length(); i++)
        {
            if(c == s.charAt(i))
            {
                stringbuffer.append(s1);
            } else
            {
                stringbuffer.append(s.charAt(i));
            }
        }

        return stringbuffer.toString();
    }

    private static java.lang.StringBuffer readFile(java.lang.String s)
        throws java.io.IOException
    {
        java.io.FileInputStream fileinputstream = null;
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        fileinputstream = new FileInputStream(s);
        int i = 0;
        byte abyte0[] = new byte[32768];
        while((i = fileinputstream.read(abyte0)) != -1) 
        {
            stringbuffer.append(new String(abyte0, 0, i));
        }
        fileinputstream.close();
        return stringbuffer;
    }

    private static jgl.Array split(char c, java.lang.String s)
    {
        jgl.Array array = new Array();
        int i = 0;
        for(int j = 0; j < s.length(); j++)
        {
            if(s.charAt(j) == c)
            {
                java.lang.String s2 = s.substring(i, j);
                array.add(s2);
                i = j + 1;
            }
        }

        if(i != s.length())
        {
            java.lang.String s1 = s.substring(i, s.length());
            array.add(s1);
        }
        return array;
    }
}
