package com.siteview.export;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Vector;

import com.focus.db.DBCon;
import com.siteview.jsvapi.Jsvapi;

public class SvMonitorEntityRelation {

	public static int recordCommited = 0;
	Jsvapi svapi = new Jsvapi();
	HashMap<String, HashMap<String, String>> allEntityTempletInfo = null;
	HashMap addedMap = new HashMap();
	StringBuffer errorMsg = new StringBuffer();

	public static void main(String[] args) {
		SvMonitorEntityRelation relation = new SvMonitorEntityRelation();
		relation.run();
		System.out.println("关键信息:\n" + relation.errorMsg);

	}
	public void run() {
		DBCon con = null;
		try {
			con = DBCon.getConnectionByConfig("ofbiz");
			con.setAutoCommit(false);

			con.setSQL("delete from sv_ci_type_method_type");
			con.execute();
			importMonitorEntityRelation(con);

			con.commit();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (con != null)
				con.close();
		}
	}
	private void importMonitorEntityRelation(DBCon con) throws Exception 
	{
		allEntityTempletInfo =getAllEntityTempletInfo();
		svapi.DisplayUtilMapInMap(allEntityTempletInfo);
		
		Iterator iterator= allEntityTempletInfo.keySet().iterator();
		while(iterator.hasNext())
		{
			String key=iterator.next().toString();
			HashMap map=allEntityTempletInfo.get(key);
			Iterator tmp= map.keySet().iterator();
			while(tmp.hasNext())
			{
				String tmpKey=tmp.next().toString();
				if(map.get(tmpKey)!=null&&map.get(tmpKey).equals("sub_monitor"))
				{
					con.setSQL("insert into sv_ci_type_method_type(CI_TYPE_ID,METHOD_TYPE_ID) values(:CI_TYPE_ID,:METHOD_TYPE_ID)");
					con.setParameter("CI_TYPE_ID", key);
					con.setParameter("METHOD_TYPE_ID", tmpKey);
					try{
					con.execute();
					}catch(Exception e)
					{
						errorMsg.append("非法数据:设备模板对应检测器类型已经不存在,CI_TYPE_ID="+key+",METHOD_TYPE_ID="+tmpKey+"\n");
					}
				}
				
			}
		}
		
		
	}
		
		/*返回map套map结构*/
		private HashMap<String,HashMap<String,String>> getAllEntityTempletInfo()
		{
			if(allEntityTempletInfo==null)
			{	
				allEntityTempletInfo = new HashMap<String, HashMap<String, String>>();
			    HashMap<String, String> ndata = new HashMap<String, String>();
			    StringBuilder estr = new StringBuilder();
			
				ndata.put("dowhat", "GetAllEntityTempletInfo");
				boolean ret = svapi.GetUnivData(allEntityTempletInfo, ndata, estr);
				
			}
			return allEntityTempletInfo;
		}
}
