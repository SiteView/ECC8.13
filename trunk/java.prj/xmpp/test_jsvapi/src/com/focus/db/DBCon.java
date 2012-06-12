// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   DBCon.java

package com.focus.db;

import com.focus.util.Util;
import java.io.*;
import java.sql.*;
import java.util.*;
import javax.naming.Context;
import javax.naming.InitialContext;
import javax.sql.DataSource;

// Referenced classes of package com.focus.db:
//            DBConIni, SQLParameter, Column, QueryResult, 
//            DBConItem

public class DBCon
{

    public void close()
    {
        try
        {
            if(con != null)
                con.close();
            con = null;
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    public void closeByConfig()
    {
        try
        {
            setAutoCommit(true);
            if(DBConIni.pool == null)
            {
                DBConIni.pool = new Hashtable();
                Vector v = new Vector();
                v.add(this);
                DBConIni.pool.put(DSN, v);
            } else
            {
                Vector v = (Vector)DBConIni.pool.get(DSN);
                if(v == null)
                {
                    Vector v1 = new Vector();
                    v1.add(this);
                    DBConIni.pool.put(DSN, v1);
                } else
                {
                    if(v.indexOf(this) == -1)
                        v.add(this);
                    DBConIni.pool.put(DSN, v);
                }
            }
        }
        catch(Exception e)
        {
            try
            {
                con.close();
            }
            catch(Exception exception) { }
        }
    }

    public void commit()
        throws SQLException
    {
        con.commit();
    }

    public void rollback()
    {
        try
        {
            con.rollback();
        }
        catch(Exception exception) { }
    }

    public boolean getAutoCommit()
        throws SQLException
    {
        return con.getAutoCommit();
    }

    public void setAutoCommit(boolean commit)
    {
        try
        {
            con.setAutoCommit(commit);
        }
        catch(Exception exception) { }
    }

    public DBCon(Connection con)
    {
        this.con = null;
        sql = null;
        all_num_rows = -1;
        changeCode = false;
        DBType = null;
        DSN = null;
        para_vec = new Vector();
        schema = null;
        useStrPara = false;
        this.con = con;
    }

    public boolean execute()
        throws SQLException
    {
        try
        {
            commitParameter();
            
            
            psmt = con.prepareStatement(sql);
            int i;
            for(i = 0; i < para_vec.size(); i++)
                setP1(i + 1, ((SQLParameter)para_vec.elementAt(i)).value);

            
            return psmt.execute();
        }
        catch(SQLException e)
        {
            if(DBType.equals("ORACLE") && e.getErrorCode() == 1)
                throw new SQLException("\u8BB0\u5F55\u5DF2\u7ECF\u5B58\u5728!");
            if(e.getMessage() != null && e.getMessage().toUpperCase().indexOf("DUPLICATE") != -1)
                throw new SQLException("\u8BB0\u5F55\u5DF2\u7ECF\u5B58\u5728!");
            else
                throw e;
        }
    }

    private String findTableNameByCommitSql()
        throws SQLException
    {
        try
        {
            if(sql.trim().toLowerCase().startsWith("update "))
            {
                int pos2 = sql.trim().toLowerCase().indexOf(" set ");
                return sql.substring(7, pos2).trim();
            }
            if(sql.trim().toLowerCase().startsWith("delete"))
            {
                int pos1 = sql.trim().toLowerCase().indexOf(" from ");
                int pos2 = sql.trim().toLowerCase().indexOf(" where ");
                if(pos2 == -1)
                    return sql.substring(pos1 + 6).trim();
                else
                    return sql.substring(pos1 + 6, pos2).trim();
            }
            if(sql.trim().toLowerCase().startsWith("insert"))
            {
                int pos1 = sql.trim().toLowerCase().indexOf("into ");
                int pos2 = sql.trim().toLowerCase().indexOf(" values");
                return sql.substring(pos1 + 5, pos2).trim();
            }
            if(sql.trim().toLowerCase().startsWith("create"))
            {
                int pos1 = sql.trim().toLowerCase().indexOf(" table ");
                int pos2 = sql.trim().toLowerCase().indexOf(" select", pos1);
                if(pos2 == -1)
                    pos2 = sql.length();
                return sql.substring(pos1 + 7, pos2).trim();
            }
            if(sql.trim().toLowerCase().startsWith("select"))
            {
                int pos1 = sql.trim().toLowerCase().indexOf(" from ");
                int pos2 = sql.trim().toLowerCase().indexOf(" where", pos1);
                if(pos2 == -1)
                    pos2 = sql.length();
                return sql.substring(pos1 + 6, pos2).trim();
            }
        }
        catch(Exception e)
        {
            System.out.println("\u89E3\u6790SQL\u4E2D\u542B\u6709\u7684\u8868\u540D\u5931\u8D25\uFF01" + sql);
            throw new SQLException("\u89E3\u6790SQL\u4E2D\u542B\u6709\u7684\u8868\u540D\u5931\u8D25\uFF01");
        }
        throw new SQLException("SQL \u672A\u77E5SQL\u8BED\u53E5\uFF0C\u65E0\u6CD5\u89E3\u6790SQL\u4E2D\u542B\u6709\u7684\u8868\u540D\uFF01");
    }

    public QueryResult query()
        throws SQLException
    {
        return query(0, 0x3b9ac9ff);
    }

    private String getKey(int begin, int end)
    {
        StringBuffer keyBuf = new StringBuffer(sql);
        for(int i = 0; i < para_vec.size(); i++)
            keyBuf.append(":").append(((SQLParameter)para_vec.elementAt(i)).toString());

        keyBuf.append(":").append(begin).append(":").append(end);
        return keyBuf.reverse().toString();
    }

    public QueryResult query(int begin, int end)
        throws SQLException
    {
        long l = System.currentTimeMillis();
        commitParameter();
        psmt = con.prepareStatement(sql, 1004, 1007);
        for(int i = 0; i < para_vec.size(); i++)
            setP1(i + 1, ((SQLParameter)para_vec.elementAt(i)).value);

        QueryResult rs = null;
        rs = makeResultMySql(psmt, begin, end);
        return rs;
    }

    public void setSQL(String sql)
    {
        if(debug_sql)
            System.out.println(sql);
        this.sql = sql;
        para_vec = new Vector();
        all_num_rows = 0;
        clearStatment();
        psmt = null;
        useStrPara = false;
    }

    public ResultSet getResultSet()
        throws Exception
    {
        try
        {
            return psmt.getResultSet();
        }
        catch(Exception e)
        {
            throw new Exception(e.getMessage());
        }
    }

    public void setParameter(int index, Object value, int length)
        throws Exception
    {
        if(debug_sql)
        {
            System.out.print(index);
            System.out.print("=");
            System.out.println(value);
        }
        try
        {
            if(value instanceof FileInputStream)
                psmt.setBinaryStream(index, (FileInputStream)value, length);
            else
                throw new Exception("\u672A\u77E5\u7684\u6570\u636E\u7C7B\u578B\uFF01");
        }
        catch(Exception e)
        {
            throw new Exception(e.getMessage());
        }
    }

    private void commitParameter()
    {
        if(!useStrPara)
            return;
        Vector sort_vec = new Vector();
        for(int i = 0; i < para_vec.size(); i++)
        {
            SQLParameter sp1 = (SQLParameter)para_vec.elementAt(i);
            if(i == 0)
            {
                sort_vec.addElement(sp1);
            } else
            {
                for(int j = 0; j < sort_vec.size(); j++)
                {
                    SQLParameter sp2 = (SQLParameter)sort_vec.elementAt(j);
                    if(sp1.pos <= sp2.pos)
                    {
                        sort_vec.insertElementAt(sp1, j);
                        break;
                    }
                    if(j != sort_vec.size() - 1)
                        continue;
                    sort_vec.addElement(sp1);
                    break;
                }

            }
        }

        para_vec = sort_vec;
        for(int i = 0; i < para_vec.size(); i++)
        {
        	sql = Util.replace(sql, ":" + ((SQLParameter)para_vec.elementAt(i)).name+",", "?,");
        	sql = Util.replace(sql, ":" + ((SQLParameter)para_vec.elementAt(i)).name+")", "?)");
        	sql = Util.replace(sql, ":" + ((SQLParameter)para_vec.elementAt(i)).name+" ", "? ");
        	if(sql.endsWith(((SQLParameter)para_vec.elementAt(i)).name))
        		sql = Util.replace(sql, ":" + ((SQLParameter)para_vec.elementAt(i)).name, "?");
        }
       if(debug_sql)
    	   System.out.println(sql);
    }

    public void doInsert(String tableName, Column cs[])
        throws SQLException
    {
        try
        {
            StringBuffer sqlBuf = new StringBuffer("insert into ");
            if(cs == null)
                return;
            if(cs.length == 0)
                throw new SQLException("\u9519\u8BEF\u7684\u5217\u53C2\u6570");
            sqlBuf.append(tableName);
            sqlBuf.append("(");
            for(int i = 0; i < cs.length; i++)
            {
                sqlBuf.append(cs[i].getName());
                sqlBuf.append(i != cs.length - 1 ? "," : ")");
            }

            sqlBuf.append(" values(");
            for(int i = 0; i < cs.length; i++)
            {
                sqlBuf.append("?");
                sqlBuf.append(i != cs.length - 1 ? "," : ")");
            }

            for(int row = 0; row < cs[0].value_vec.size(); row++)
            {
                clearStatment();
                psmt = con.prepareStatement(sqlBuf.toString());
                for(int i = 0; i < cs.length; i++)
                    setP1(i + 1, cs[i].getValue(row));

                if(debug_sql)
                    System.out.println(sqlBuf.toString());
                psmt.execute();
            }

        }
        catch(SQLException e)
        {
            if(e.getErrorCode() == 1)
                throw new SQLException("\u8BB0\u5F55\u5DF2\u7ECF\u5B58\u5728");
            if(e.getMessage() != null && e.getMessage().toUpperCase().indexOf("DUPLICATE") != -1)
                throw new SQLException("\u8BB0\u5F55\u5DF2\u7ECF\u5B58\u5728");
            else
                throw e;
        }
    }

    private String getTableNameByPstm()
        throws SQLException
    {
        StringBuffer sb = new StringBuffer();
        for(int i = 1; i <= psmt.getMetaData().getColumnCount(); i++)
        {
            String tName = psmt.getMetaData().getTableName(i);
            if(sb.indexOf(tName) == -1)
            {
                if(sb.length() > 0)
                    sb.append(",");
                sb.append(tName);
            }
        }

        return sb.toString();
    }

    private String getTableNameByQueryResult(QueryResult rs)
        throws SQLException
    {
        StringBuffer sb = new StringBuffer();
        for(int i = 0; i < rs.getCols().length; i++)
        {
            String tName = rs.getCols()[i].getTableName();
            if(sb.indexOf(tName) == -1)
            {
                if(sb.length() > 0)
                    sb.append(",");
                sb.append(tName);
            }
        }

        return sb.toString();
    }

    public void excuteNoWarningPk()
        throws SQLException
    {
        try
        {
            execute();
        }
        catch(SQLException e)
        {
            if(e.getMessage() != null && e.getMessage().toUpperCase().indexOf("\u8BB0\u5F55\u5DF2\u7ECF\u5B58\u5728") == -1)
                throw e;
        }
    }

    private ResultSet executeQuery()
        throws SQLException
    {
        commitParameter();
        psmt = con.prepareStatement(sql);
        for(int i = 0; i < para_vec.size(); i++)
            setP1(i + 1, ((SQLParameter)para_vec.elementAt(i)).value);

        psmt.setCursorName("myTest");
        ResultSet rs = psmt.executeQuery();
        rs.setFetchDirection(1000);
        rs.first();
        rs.next();
        rs.last();
        int numrow = rs.getFetchSize();
        int row = rs.getRow();
        rs.absolute(10);
        row = rs.getRow();
        int size2 = psmt.getFetchSize();
        int rows = psmt.getMaxRows();
        return rs;
    }

    public String getColComment(String dsnDotTableDotcol)
    {
        return null;
    }

    public static DBCon getConnection(String DSN)
        throws Exception
    {
        Context ctx = null;
        Exception err;
        DBCon dbcon;
        try
        {
            ctx = new InitialContext();
            DataSource ds = (DataSource)ctx.lookup("java:comp/env/" + DSN);
            if(ds == null)
                return null;
            Connection con = ds.getConnection();
            DBCon myCon = new DBCon(con);
            if(con.getMetaData().getDatabaseProductName().indexOf("Microsoft SQL Server") != -1)
                myCon.DBType = "SQLSERVER";
            else
            if(con.getMetaData().getDatabaseProductName().toUpperCase().indexOf("ORACLE") != -1)
                myCon.DBType = "ORACLE";
            else
            if(con.getMetaData().getDatabaseProductName().toUpperCase().indexOf("MYSQL") != -1)
                myCon.DBType = "MYSQL";
            else
                throw new Exception(con.getMetaData().getDatabaseProductName());
            myCon.changeCode = false;
            dbcon = myCon;
        }catch(Exception e)
        {
        	System.out.println(e.getMessage());
          throw e;	
        }
        finally
        {
            if(ctx != null)
                ctx.close();
        }
        return dbcon;
        
        
        
        
    }

    public static DBCon getConnectionByConfig(String DSN)
        throws SQLException
    {
        DriverManager.setLoginTimeout(5);
        long l = System.currentTimeMillis();
        try
        {
            DBConItem item = DBConIni.getDBConItem(DSN);
            DBCon con = null;
            if(DBConIni.pool == null)
            {
                Class.forName(item.driverName).newInstance();
                con = new DBCon(DriverManager.getConnection(item.url, item.user, item.password));
            } else
            {
                Vector v = (Vector)DBConIni.pool.get(DSN);
                if(v == null)
                {
                    Class.forName(item.driverName).newInstance();
                    con = new DBCon(DriverManager.getConnection(item.url, item.user, item.password));
                } else
                {
                    for(int j = v.size(); j > 0; j--)
                    {
                        con = (DBCon)v.remove(j - 1);
                        if(!con.isClosed())
                            break;
                        con = null;
                    }

                    if(con == null)
                        con = new DBCon(DriverManager.getConnection(item.url, item.user, item.password));
                }
            }
            con.DSN = DSN;
            con.DBType = item.DBType;
            con.changeCode = item.changeCode;
            con.schema = item.user.toUpperCase();
            return con;
        }
        catch(Exception e)
        {
            throw new SQLException(e.getMessage());
        }
    }

    public String getDBType()
    {
        return DBType;
    }

   

    public boolean isClosed()
        throws Exception
    {
        try
        {
            if(con != null)
                return con.isClosed();
            else
                return true;
        }
        catch(Exception e)
        {
            throw new Exception(e.getMessage());
        }
    }

    public QueryResult query(String recNumPerPage, String pageIdx)
        throws SQLException
    {
        long l = System.currentTimeMillis();
        int begin = Integer.parseInt(recNumPerPage) * (Integer.parseInt(pageIdx) - 1);
        int end = Integer.parseInt(recNumPerPage) + begin;
        QueryResult rs = query(begin, end);
        rs.recNumPerPage = recNumPerPage;
        rs.pageIdx = pageIdx;
        rs.totalPageNum = String.valueOf((int)Math.ceil(0.5D + (double)(rs.all_numrow / Integer.parseInt(recNumPerPage))));
        return rs;
    }

    public String setColComment(String dsnDotTableDotcol, String comment)
    {
        return null;
    }

    private void setP1(int index, Object value)
        throws SQLException
    {
        setP1(psmt, index, value);
    }

    public void setParameter(String para_name, Object para_value)
        throws Exception
    {
        if(debug_sql)
            System.out.println((new StringBuffer(para_name)).append("=").append(para_value));
        useStrPara = true;
        try
        {
            int pos = 0;
            int idx = -1;
            
            do
            {
            	int tmp;	
            	tmp=sql.indexOf(":" + para_name+",", idx + 1);
                if(tmp<0)
                	tmp=sql.indexOf(":" + para_name+")", idx + 1);
                if(tmp<0)
                	tmp=sql.indexOf(":" + para_name+" ", idx + 1);
                
                if(tmp<0)
                 if(sql.endsWith(":" + para_name))
                	tmp=sql.indexOf(":" + para_name,idx + 1);
                
                if(tmp < 0)
                    break;
                else
                	idx=tmp+(":" + para_name).length();
                
                pos = idx;
                para_vec.addElement(new SQLParameter(para_name, para_value, idx));
            } while(true);
            if(pos == 0)
                throw new Exception(para_name);
        }
        catch(Exception e)
        {
            throw new Exception(e.getMessage());
        }
    }

    public Column[] getcolumns(String tableName)
        throws SQLException
    {
        String schema = DBConIni.getDBConItem(DSN).user.toUpperCase();
        Vector v = new Vector();
        DatabaseMetaData dmd = con.getMetaData();
        Column c;
        for(ResultSet rs = dmd.getColumns(null, null, tableName, null); rs.next(); v.addElement(c))
        {
            ResultSetMetaData rsm = rs.getMetaData();
            String str = rs.getString("COLUMN_NAME").trim();
            c = new Column();
            c.setName(str.toLowerCase());
            c.setTableName(tableName.toUpperCase());
            str = rs.getString("TYPE_NAME").trim();
            c.setDataType(str.toUpperCase());
            c.setIsNullable(rs.getString("IS_NULLABLE").equals("YES"));
            c.setLength(rs.getInt("COLUMN_SIZE"));
        }

        Column re[] = new Column[v.size()];
        v.copyInto(re);
        return re;
    }

    public String[] getTables(String SQLStr)
    {
        String s = SQLStr.toLowerCase();
        StringTokenizer st = new StringTokenizer(s, " ");
        Vector v = new Vector();
        while(st.hasMoreElements()) 
        {
            String tmp = st.nextElement().toString().trim();
            if(tmp.equals("from"))
            {
                tmp = st.nextElement().toString().trim();
                for(StringTokenizer st_tmp = new StringTokenizer(tmp, ","); st_tmp.hasMoreElements();)
                {
                    String name = st_tmp.nextElement().toString().trim();
                    if(v.indexOf(name) == -1)
                        v.addElement(name);
                }

            }
        }
        String tableName[] = new String[v.size()];
        v.copyInto(tableName);
        return tableName;
    }

    private QueryResult makeResultMySql(PreparedStatement psmt, int begin, int end)
        throws SQLException
    {
        ResultSet rs;
        long l = System.currentTimeMillis();
        rs = null;
        Exception e;
        QueryResult queryresult;
        try
        {
            QueryResult qr = new QueryResult();
            qr.changeCode = changeCode;
            qr.DBType = getDBType();
            rs = psmt.executeQuery();
            ResultSetMetaData rsm = rs.getMetaData();
            qr.cols = new Column[rsm.getColumnCount()];
            for(int i = 0; i < rsm.getColumnCount(); i++)
            {
                String table = rsm.getTableName(i + 1);
                String colName = rsm.getColumnName(i + 1);
                String commentStr = getColComment("" + DSN + "." + table + "." + colName);
                boolean isPk;
                String comment;
                if(commentStr == null)
                {
                    comment = null;
                    isPk = false;
                    int dispLength = -1;
                } else
                {
                    StringTokenizer st = new StringTokenizer(commentStr, ",");
                    comment = st.nextElement().toString();
                    int dispLength = Integer.parseInt(st.nextElement().toString());
                    isPk = st.hasMoreElements();
                }
                qr.cols[i] = new Column();
                qr.cols[i].setDSN(DSN);
                qr.cols[i].setTableName(table);
                qr.cols[i].setName(colName);
                qr.cols[i].setDataType(rsm.getColumnTypeName(i + 1).toUpperCase());
                qr.cols[i].setLength(0x5f5e0ff);
                qr.cols[i].setComment(comment != null ? comment : rsm.getColumnLabel(i + 1));
                qr.cols[i].setIsPk(isPk);
                qr.cols[i].setIsNullable(rsm.isNullable(i + 1) != 0);
                qr.cols[i].setScale(rsm.getScale(i + 1));
            }

            if(begin > 0)
                rs.absolute(begin);
            boolean no_rec = true;
            while(rs.next()) 
            {
                no_rec = false;
                for(int i = 0; i < qr.cols.length; i++)
                    qr.cols[i].value_vec.add(rs.getObject(i + 1));

                if(rs.getRow() == end)
                    break;
            }
            rs.last();
            if(begin == 0 && no_rec)
                qr.all_numrow = 0;
            else
                qr.all_numrow = rs.getRow();
            queryresult = qr;
        }catch(Exception eee)
        {
        	throw new SQLException(eee.getMessage());
        }
        finally
        {
            if(rs != null)
                rs.close();
        }
        return queryresult;
        
        
    }

    private byte[] readbyte(InputStream is)
        throws IOException
    {
        Vector byteV = new Vector();
        Vector lenV = new Vector();
        do
        {
            int len = is.available();
            if(len <= 0)
                len = 10240;
            byte b[] = new byte[len];
            int r = is.read(b);
            if(r < 0)
                break;
            if(r != 0)
            {
                byteV.addElement(b);
                lenV.addElement(new Integer(r));
            }
        } while(true);
        return null;
    }

    private void setP1(PreparedStatement psmt, int index, Object value)
        throws SQLException
    {
        if(value == null)
            psmt.setNull(index, 1);
        else
        if((value instanceof String) && value.toString().getBytes().length < 2000)
            psmt.setString(index, (String)value);
        else
        if(value instanceof String)
            psmt.setObject(index, (String)value);
        else
        if(value instanceof StringBuffer)
            psmt.setObject(index, ((StringBuffer)value).toString());
        
        else
        if(value instanceof Integer)
        {
            Integer i = (Integer)value;
            int ii = i.intValue();
            psmt.setInt(index, ii);
        } else
        if(value instanceof Float)
        {
            Float f = (Float)value;
            float ff = f.floatValue();
            psmt.setFloat(index, ff);
        } else
        if(value instanceof Double)
        {
            Double d = (Double)value;
            double dd = d.doubleValue();
            psmt.setDouble(index, dd);
        } else
        if(value instanceof Long)
        {
            Long d = (Long)value;
            long dd = d.longValue();
            psmt.setDouble(index, dd);
        } else
        if(value instanceof byte[])
            psmt.setBytes(index, (byte[])value);
        else
            psmt.setObject(index, value);
    }

    public void clearStatment()
    {
        try
        {
            if(psmt != null)
                psmt.clearParameters();
        }
        catch(Exception exception) { }
        try
        {
            if(psmt != null)
                psmt.close();
        }
        catch(Exception exception1) { }
    }

    public int doUpdate(String tableName, Column updateCol[], Column whereCol[])
        throws SQLException
    {
        StringBuffer sqlBuf = new StringBuffer("update ");
        sqlBuf.append(tableName);
        sqlBuf.append(" set ");
        for(int i = 0; i < updateCol.length; i++)
        {
            sqlBuf.append(updateCol[i].getName());
            sqlBuf.append("=?");
            sqlBuf.append(i != updateCol.length - 1 ? "," : " ");
        }

        sqlBuf.append(" where ");
        for(int i = 0; i < whereCol.length; i++)
        {
            sqlBuf.append(whereCol[i].getName());
            sqlBuf.append("=?");
            sqlBuf.append(i != whereCol.length - 1 ? " and " : " ");
        }

        int count = 0;
        for(int row = 0; row < updateCol[0].value_vec.size(); row++)
        {
            clearStatment();
            psmt = con.prepareStatement(sqlBuf.toString());
            for(int i = 0; i < updateCol.length; i++)
                setP1(i + 1, updateCol[i].getValue(row));

            for(int i = 0; i < whereCol.length; i++)
                setP1(i + 1 + updateCol.length, whereCol[i].getValue(row));

            if(debug_sql)
                System.out.println(sqlBuf.toString());
            count += psmt.executeUpdate();
        }

        return count;
    }

    public int doUpdate(String tableName, String pk[], Column col[])
        throws SQLException
    {
        Vector v = new Vector();
        for(int j = 0; j < pk.length; j++)
        {
            for(int i = 0; i < col.length; i++)
            {
                if(!col[i].getName().toUpperCase().equals(pk[j].toUpperCase()) && !col[i].getFullName().toUpperCase().equals(pk[j].toUpperCase()))
                    continue;
                v.addElement(col[i]);
                break;
            }

        }

        Column c[] = new Column[v.size()];
        v.copyInto(c);
        return doUpdate(tableName, col, c);
    }

    public int executeUpdate()
        throws SQLException
    {
        try
        {
            commitParameter();
            psmt = con.prepareStatement(sql);
            int i;
            for(i = 0; i < para_vec.size(); i++)
                setP1(i + 1, ((SQLParameter)para_vec.elementAt(i)).value);

            i = psmt.executeUpdate();
            return i;
        }
        catch(SQLException e)
        {
            if(e.getMessage() != null && e.getMessage().toUpperCase().indexOf("DUPLICATE") != -1)
                throw new SQLException("\u8BB0\u5F55\u5DF2\u7ECF\u5B58\u5728!");
            else
                throw e;
        }
    }

    public Connection con;
    public static boolean debug_sql = false;
    String sql;
    PreparedStatement psmt;
    private int all_num_rows;
    boolean changeCode;
    String DBType;
    public String DSN;
    private Vector para_vec;
    String schema;
    boolean useStrPara;

}
