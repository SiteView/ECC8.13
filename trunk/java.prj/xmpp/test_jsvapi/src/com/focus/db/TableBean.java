// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   TableBean.java

package com.focus.db;

import java.sql.SQLException;
import java.util.*;

// Referenced classes of package com.focus.db:
//            DBCon, QueryResult, Column

public class TableBean
{

    public TableBean()
    {
    }

    public static Column[] getColumns(DBCon con, String tableName)
        throws Exception
    {
        QueryResult rs = null;
        Column c[] = (Column[])table_info.get(("" + con.DSN + "." + tableName).toUpperCase());
        if(c == null)
        {
            con.setSQL("select * from " + tableName + " where 1=0");
            rs = con.query();
            c = rs.getCols();
        }
        return c;
    }

    public static boolean insert(DBCon con, String tableName, Column c[])
        throws SQLException
    {
        try
        {
            con.doInsert(tableName, c);
        }
        catch(SQLException e)
        {
            if(e.getMessage().toLowerCase().indexOf("duplicate entry") != -1)
                throw new SQLException("\u8BB0\u5F55\u5DF2\u7ECF\u5B58\u5728\uFF01");
            else
                throw e;
        }
        return true;
    }

    public static boolean insert(DBCon con, String tableName, HashMap values)
        throws Exception
    {
        Column c[] = makeCommitColumn(con, tableName, values);
        insert(con, tableName, c);
        return true;
    }

    public static QueryResult query(String DSN, String sql)
        throws Exception
    {
        return query(DSN, sql, null, null, "999999999", "1");
    }

    public static QueryResult query(String DSN, String sql, String paraName[], Object paraValue[])
        throws Exception
    {
        return query(DSN, sql, paraName, paraValue, "999999999", "1");
    }

    public static QueryResult query(String DSN, String sql, String paraName[], Object paraValue[], String recNumPerPage, String pageIdx)
        throws Exception
    {
        DBCon con;
        con = null;
        QueryResult rs = null;
        Exception e;
        QueryResult queryresult=null;
        try
        {
            con = DBCon.getConnection(DSN);
            con.setSQL(sql);
            if(paraName != null)
            {
                for(int i = 0; i < paraName.length; i++)
                    con.setParameter(paraName[i], paraValue[i]);

            }
            rs = con.query(recNumPerPage, pageIdx);
            
        }
        finally
        {
            if(con != null)
                con.close();
        }
        return queryresult;
        
    }

    public static QueryResult query(String DSN, String sql, String recNumPerPage, String pageIdx)
        throws Exception
    {
        return query(DSN, sql, null, null, recNumPerPage, pageIdx);
    }

    public static Column[] makeCommitColumn(DBCon con, String tableName, HashMap oldvalues)
        throws Exception
    {
        HashMap valClone = new HashMap();
        String key;
        String value;
        Iterator myenum = oldvalues.keySet().iterator();
        
        while( myenum.hasNext())
        {
        	key = myenum.next().toString();
        	value=oldvalues.get(key).toString();
        	valClone.put(key.toUpperCase(),value);
        }
            

        Column c[] = getColumns(con, tableName);
        Vector commitV = new Vector();
        for(int i = 0; i < c.length; i++)
        {
            Object o = valClone.get(c[i].getName().toUpperCase());
            if(o != null)
                if(o instanceof Object[])
                {
                    Object val[] = (Object[])o;
                    c[i].setCheckValue(true);
                    c[i].value_vec = new ArrayList();
                    for(int j = 0; j < val.length; j++)
                    {
                        c[i].value_vec.add(null);
                        c[i].setValue(j, val[j]);
                    }

                    commitV.addElement(c[i]);
                } else
                {
                    c[i].value_vec = new ArrayList();
                    c[i].value_vec.add(null);
                    c[i].setCheckValue(true);
                    if(o.toString().trim().equals("") && (c[i].getDataType().indexOf("NUM") > -1 || c[i].getDataType().indexOf("INT") > -1 || c[i].getDataType().indexOf("DEC") > -1 || c[i].getDataType().indexOf("FLOAT") > -1))
                        o = null;
                    c[i].setValue(0, o);
                    commitV.addElement(c[i]);
                }
        }

        c = new Column[commitV.size()];
        commitV.copyInto(c);
        return c;
    }

    public static int update(DBCon con, String tableName, Column c[], String pk[])
        throws Exception
    {
        return con.doUpdate(tableName, pk, c);
    }

    public static int update(DBCon con, String tableName, HashMap values, String pk[])
        throws Exception
    {
        Column c[] = makeCommitColumn(con, tableName, values);
        return update(con, tableName, c, pk);
    }

    public static HashMap table_info = new HashMap();

}
