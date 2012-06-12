// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Util.java

package com.focus.util;

import java.io.*;
import java.util.*;
import javax.servlet.http.*;

// Referenced classes of package com.focus.util:
//            DateTool, BaseServlet, Encript, Mail

public class Util
{

    public Util()
    {
    }

    public static void debugHashtable(Hashtable ht)
    {
        Object key;
        for(Enumeration enum1 = ht.keys(); enum1.hasMoreElements(); System.out.println(key + "=" + ht.get(key)))
            key = enum1.nextElement();

    }

    public static String createId()
        throws Exception
    {
        long id;
        do
            id = System.currentTimeMillis() - Long.parseLong("999089069099");
        while(lastid == id);
        lastid = id;
        return String.valueOf(id);
    }

    public static void deleteRecursive(File _file)
        throws IOException
    {
        if(_file.exists())
        {
            if(_file.isDirectory())
            {
                File files[] = _file.listFiles();
                for(int i = 0; i < files.length; i++)
                    deleteRecursive(files[i]);

            }
            boolean flag = _file.delete();
        }
    }

    public static void deleteFile(String file)
        throws Exception
    {
        File f = new File(file);
        if(!f.exists())
        {
            return;
        } else
        {
            f.delete();
            return;
        }
    }

    
    public static void deleteFileAs(String dir, String name)
    {
        try
        {
            File file = new File(dir);
            File files[] = file.listFiles();
            for(int i = 0; i < files.length; i++)
                if(files[i].getName().startsWith(name))
                    files[i].delete();

        }
        catch(Exception exception) { }
    }

    public static void dispatchImage(HttpServletRequest req, HttpServletResponse res, String file)
        throws Exception
    {
        DataInputStream in = null;
        DataOutputStream out = null;
        try
        {
            in = new DataInputStream(new FileInputStream(file));
            out = new DataOutputStream(res.getOutputStream());
            do
                out.writeByte(in.readByte());
            while(true);
        }
        catch(EOFException eofexception) { }
        finally
        {
            try
            {
                in.close();
            }
            catch(Exception exception1) { }
        }
        return;
    }

    public static String getCurrentDate(String format)
    {
        return (new DateTool()).toDateString(format);
    }

    public static String getCurrentDateTime()
    {
        return (new DateTool()).toDateString("YYYY-MM-DD HH:MI:SS");
    }

    public static String getDateStr(Object obj)
    {
        return (new DateTool((Date)obj)).toDateString();
    }

    public static String getDateTime(long l)
    {
        return (new DateTool(l)).toDateString("YYYY-MM-DD HH:MI:SS");
    }

    public static String getLineSeparator()
    {
        return (String)System.getProperties().get("line.separator");
    }

    public static String getSpace(int num)
    {
        StringBuffer space = new StringBuffer("");
        for(int i = 0; i < num; i++)
            space.append("&nbsp;");

        return space.toString();
    }

    public static Vector split(String source, String sp)
    {
        if(source == null)
            return new Vector();
        String s[] = source.split(sp);
        Vector v = new Vector();
        for(int i = 0; i < s.length; i++)
            v.addElement(s[i]);

        return v;
    }

    public static Object getValue(HttpServletRequest req, String name)
    {
        return req.getSession().getAttribute(name);
    }

    public static Object getValue(HttpSession hs, String name)
    {
        return hs.getAttribute(name);
    }

    public static void println(Object obj)
    {
        if(obj == null)
        {
            System.out.println();
            return;
        }
        if(obj instanceof Throwable)
        {
            ((Throwable)obj).printStackTrace();
            return;
        } else
        {
            System.out.println(obj);
            return;
        }
    }

    public static void putValue(HttpSession hs, String name, Object value)
    {
        hs.setAttribute(name, value);
    }

    public static String readFile(String file)
        throws Exception
    {
        File f = new File(file);
        if(!f.exists())
            return "\u672A\u627E\u5230 " + file;
        BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream(file)));
        StringBuffer txt = new StringBuffer();
        try
        {
            for(String line = in.readLine(); line != null; line = in.readLine())
            {
                txt.append(line);
                txt.append(getLineSeparator());
            }

        }
        finally
        {
            try
            {
                in.close();
            }
            catch(Exception exception1) { }
        }
        return txt.toString();
    }

    public static String replace(String source, String tobereplace, String usetoreplace)
    {
        StringBuffer sourceBuffer = new StringBuffer(source);
        int start = source.toLowerCase().indexOf(tobereplace.toLowerCase());
        int end = 0;
        if(start == -1)
            return source;
        do
        {
            end = start + tobereplace.length();
            sourceBuffer = sourceBuffer.replace(start, end, usetoreplace);
            end = (end + usetoreplace.length()) - tobereplace.length();
            start = sourceBuffer.substring(end).toLowerCase().indexOf(tobereplace.toLowerCase());
            if(start != -1)
                start += end;
            else
                return sourceBuffer.toString();
        } while(true);
    }

    public static String replaceModel(String src, Object oldStr[], Object newStr[])
        throws Exception
    {
        if(oldStr != null)
        {
            for(int i = 0; i < oldStr.length; i++)
                src = replace(src, oldStr[i].toString(), newStr[i].toString());

        }
        return src;
    }

    public static String txtToHtm(String s)
    {
        if(s.trim().indexOf("<p>") != -1 || s.trim().indexOf("<br>") != -1)
        {
            return s;
        } else
        {
            s = replace(s, "\n", "<br>");
            return s;
        }
    }

    public static void writeFile(String file, String text)
        throws Exception
    {
        if(text == null)
            return;
        int idx = file.lastIndexOf("\\");
        int idx2 = file.lastIndexOf("/");
        if(idx < idx2)
            idx = idx2;
        String dir = file.substring(0, idx);
        File fdir = new File(dir);
        if(!fdir.exists())
            fdir.mkdirs();
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file)));
        try
        {
            out.write(text);
        }
        finally
        {
            try
            {
                out.close();
            }
            catch(Exception exception1) { }
        }
    }

    public static String cn(String str)
        throws UnsupportedEncodingException
    {
        String temp_p = str;
        byte temp_t[] = temp_p.getBytes();
        String temp = new String(temp_t, "GBK");
        return temp;
    }

    protected static void encodeByte(byte byte0, StringWriter stringwriter)
    {
        if(byte0 == 0)
        {
            stringwriter.write(103);
        } else
        {
            String s = Integer.toHexString(byte0);
            if(s.length() < 2)
            {
                stringwriter.write(48);
                stringwriter.write(s);
            } else
            {
                char ac[] = new char[2];
                s.getChars(s.length() - 2, s.length(), ac, 0);
                stringwriter.write(ac, 0, 2);
            }
        }
    }

    public static String encodeData(byte abyte0[], int i)
    {
        StringWriter stringwriter = new StringWriter();
        for(int j = 0; j < abyte0.length; j++)
        {
            encodeByte(abyte0[j], stringwriter);
            if((j + 1) % i == 0)
                stringwriter.write("\n");
        }

        return stringwriter.toString();
    }

    public static String encodePassword(String s)
    {
        return (new Encript()).encrypt(s);
    }

    public static Object getSession(HttpServletRequest request, String name)
    {
        return request.getSession().getAttribute(name);
    }

    public static String getVar(HttpServletRequest request, String name)
    {
        return request.getParameter(name);
    }

    public static String getVarNotNull(HttpServletRequest request, String name)
    {
        String result = getVar(request, name);
        if(result == null)
            return "";
        else
            return result;
    }

    public static void setSession(HttpServletRequest request, String name, Object value)
    {
        request.getSession().setAttribute(name, value);
    }

    public static void setVar(HttpServletRequest request, String name, Object value)
    {
        request.setAttribute(name, value);
    }

    public static String gbToUnicode(String src)
    {
        if(src == null || src.length() == 0)
            return src;
        char c[] = src.toCharArray();
        int n = c.length;
        byte b[] = new byte[n];
        for(int i = 0; i < n; i++)
            b[i] = (byte)c[i];

        return new String(b);
    }

    public static String to8859_1(String src)
        throws UnsupportedEncodingException
    {
        byte b[] = src.getBytes("GBK");
        return new String(b, "8859_1");
    }

    public static String toGBK(String src)
        throws UnsupportedEncodingException
    {
        if(src == null)
        {
            return null;
        } else
        {
            byte b[] = src.getBytes("8859_1");
            return new String(b, "GBK");
        }
    }

    public static String toOnlyUnicode(String src)
        throws UnsupportedEncodingException
    {
        char c[] = src.toCharArray();
        StringBuffer sb = new StringBuffer();
        for(int i = 0; i < c.length; i++)
            sb.append("%u" + (int)c[i]);

        return sb.toString();
    }

    public static String tounicode(String src)
        throws UnsupportedEncodingException
    {
        char c[] = src.toCharArray();
        StringBuffer sb = new StringBuffer();
        for(int i = 0; i < c.length; i++)
        {
            if(sb.length() > 0)
                sb.append(",");
            sb.append(c[i]);
        }

        return sb.toString();
    }

    public static String unicodeToGb(String src)
    {
        if(src == null || src.length() == 0)
            return src;
        byte b[] = src.getBytes();
        int n = b.length;
        char c[] = new char[n];
        for(int i = 0; i < n; i++)
            c[i] = (char)((short)b[i] & 0xff);

        return new String(c);
    }

    public static boolean checkCode(String kenid[], String code[], int kencount, int codecount)
    {
        int i = 0;
        String codeup = null;
        String codecurrent = null;
        do
        {
            codeup = code[i];
            i++;
            codecurrent = code[i];
            if(!codecurrent.substring(0, codeup.length()).equals(codeup) || codecurrent.length() - codeup.length() != Integer.parseInt(kenid[i]))
                return false;
        } while(i != codecount);
        return true;
    }

    public StringBuffer replace(StringBuffer data, char oldchar, String newString)
    {
        int i = 0;
        if(data.length() == 0)
            return data;
        do
            if(data.charAt(i) == oldchar)
            {
                data.replace(i, i + 1, newString);
                i += newString.length();
            } else
            {
                i++;
            }
        while(i < data.length());
        return data;
    }

    public static String replace(String src, String startStr, String endStr, String replaceStr)
    {
        StringBuffer sb = new StringBuffer();
        int idx1 = src.toLowerCase().indexOf(startStr.toLowerCase());
        int idx2 = src.toLowerCase().indexOf(endStr.toLowerCase());
        if(idx1 == -1 || idx2 == -1)
        {
            return src;
        } else
        {
            sb.append(src.substring(0, idx1 + startStr.toLowerCase().length()));
            sb.append(replaceStr);
            sb.append(src.substring(idx2));
            src = sb.toString();
            return src;
        }
    }

    public static Vector split(String content, int len)
    {
        if(content != null)
        {
            Vector v = new Vector();
            int cur;
            for(cur = 0; len < content.length() - cur; cur += len)
                v.addElement(content.substring(cur, len + cur));

            if(len == content.length() - cur)
            {
                v.addElement(content.substring(cur, len + cur));
                cur += len;
                return v;
            } else
            {
                v.addElement(content.substring(cur));
                return v;
            }
        } else
        {
            return null;
        }
    }

    public static String getPathFile(String path, String file)
    {
        String pathfile = "";
        if(path.endsWith("/") || path.endsWith("\\"))
            pathfile = path + file;
        else
            pathfile = path + "/" + file;
        return pathfile;
    }

    public static String getPathPath(String path1, String path2)
    {
        if(path2.startsWith("/") || path2.startsWith("\\"))
            path2 = path2.substring(1);
        String pathfile = "";
        if(path1.endsWith("/") || path1.endsWith("\\"))
            pathfile = path1 + path2;
        else
            pathfile = path1 + "/" + path2;
        return pathfile;
    }

    public static Hashtable bufferModel = new Hashtable();
    public static long lastid = 0L;
    public static Hashtable ruletable = new Hashtable();

}
