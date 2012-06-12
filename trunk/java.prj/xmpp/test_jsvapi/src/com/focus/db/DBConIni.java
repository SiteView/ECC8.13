// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   DBConIni.java

package com.focus.db;

import com.focus.util.Util;
import java.io.*;
import java.sql.SQLException;
import java.util.*;

// Referenced classes of package com.focus.db:
//            DBConItem, DBCon, QueryResult

public class DBConIni
    implements Serializable
{

    public DBConIni()
    {
    }

    public void addDBConItem(DBConItem item)
        throws Exception
    {
        getDBConItemPool().put(item.dsn, "" + item.driverName + "," + item.url + "," + item.user + "," + item.password + "," + item.changeCode);
    }

    public static DBConItem getDBConItem(String DSN)
        throws SQLException
    {
        try
        {
            String con = getDBConItemPool().get(DSN).toString();
            StringTokenizer st = new StringTokenizer(con, ",");
            if(st.countTokens() != 6)
            {
                throw new SQLException("\u6570\u636E\u5E93\u8FDE\u63A5\u914D\u7F6E\u9519\u8BEF,\u683C\u5F0F\u9519\u8BEF:" + con);
            } else
            {
                DBConItem item = new DBConItem(DSN, st.nextElement().toString(), st.nextElement().toString(), st.nextElement().toString(), st.nextElement().toString(), (new Boolean(st.nextElement().toString())).booleanValue(), st.nextElement().toString());
                return item;
            }
        }
        catch(Exception e)
        {
            throw new SQLException("\u6CA1\u6709\u627E\u5230\u6570\u636E\u6E90\u914D\u7F6E\u7684\u76F8\u5173\u4FE1\u606F," + e.getMessage());
        }
    }

    public static Properties getDBConItemPool()
        throws Exception
    {
        try
        {
            if(prop != null)
                return prop;
            File f = new File(getDBconFile());
            if(f.exists())
            {
                prop = new Properties();
                FileInputStream fin = new FileInputStream(f);
                prop.load(fin);
                fin.close();
                Object key_tmp;
                Object value;
                for(Enumeration myenum = prop.keys(); myenum.hasMoreElements(); prop.put(key_tmp, value))
                {
                    key_tmp = myenum.nextElement();
                    value = Util.gbToUnicode(prop.get(key_tmp).toString());
                }

            } else
            {
                System.out.println("\u8054\u7ED3\u914D\u7F6E\u6587\u4EF6\u672A\u627E\u5230" + getDBconFile());
            }
            return prop;
        }
        catch(Exception e)
        {
            throw new Exception("getDBConItemPool\u51FA\u73B0\u5F02\u5E38:" + e.getMessage());
        }
    }

    public static String getHome()
    {
        return System.getProperty("user.dir");
    }

    public static void main(String args[])
    {
        System.out.println(getHome());
        DBCon con = null;
        try
        {
            con = DBCon.getConnection("portalDS");
            System.out.println("\u5F53\u524D\u6570\u636E\u5E93\u7C7B\u578B" + con.getDBType());
            con.setSQL("drop table test");
            con.execute();
        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());
        }
        try
        {
            con.setSQL("create table test(id char(10))");
            con.execute();
            con.setSQL("insert into test(id) values(:ID)");
            con.setParameter("ID", "\u6211\u7684\u5B9E\u9A8C");
            con.execute();
            con.setSQL("select * from test where id<>:ID1 and id=:ID2 and id<>:ID1");
            con.setParameter("ID1", "\u5B9E");
            con.setParameter("ID2", "\u6211\u7684\u5B9E\u9A8C");
            QueryResult rs = con.query();
            for(int i = 0; i < rs.size(); i++)
                System.out.println(rs.getObject(i, "id"));

        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());
        }
        finally
        {
            if(con != null)
                con.close();
        }
        return;
    }

    public void removeDBConItem(String DSN)
        throws Exception
    {
        getDBConItemPool().remove(DSN);
    }

    public static String getDBconFile()
    {
        StringBuffer s = (new StringBuffer(Util.getPathPath(getHome(), "conf"))).append(System.getProperty("file.separator")).append("dbcon.txt");
        System.out.println(s.toString());
        return s.toString();
    }

    public void saveIni()
        throws Exception
    {
        try
        {
            File f = new File(getDBconFile());
            FileOutputStream fo = new FileOutputStream(f);
            PrintStream prn = new PrintStream(fo);
            getDBConItemPool().list(prn);
            fo.close();
        }
        catch(Exception e)
        {
            throw new Exception(e.getMessage());
        }
    }

    static Hashtable pool = null;
    public static Properties prop = null;

}
