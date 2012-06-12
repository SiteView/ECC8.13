package com.siteview.export;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;
import java.util.Vector;

import com.focus.db.DBCon;
import com.focus.db.QueryResult;
import com.focus.db.TableBean;
import com.siteview.jsvapi.Jsvapi;

public class AlertImport {

	
	public static int recordCommited = 0;
	Jsvapi svapi = new Jsvapi();
	HashMap<String, HashMap<String, String>> allAlertTempletInfo = null;
	HashMap addedMap = new HashMap();
	public static StringBuffer errorMsg = new StringBuffer();

	public static void main(String[] args) throws Exception{
		AlertImport alert = new AlertImport();
		alert.run();
		System.out.println("关键信息:" + alert.errorMsg);
	}

	public void run() {

		DBCon con = null;
		try {
			con = DBCon.getConnectionByConfig("ofbiz");
			con.setAutoCommit(false);
			con.setSQL("delete from sv_alert_task");
			con.execute();
			con.setSQL("delete from sv_alert_target");
			con.execute();
			con.setSQL("delete from sv_alert_attr");
			con.execute();
			con.setSQL("delete from sv_alert");
			con.execute();
			importTask(con);
			importAlert(con);
			con.commit();
			System.out.println("okokok!!!!!!!!!");

		} catch (Exception e) {
			e.printStackTrace();
			if (con != null)
				con.rollback();

		} finally {
			if (con != null)
				con.close();
		}

	}

	public void importAlert(DBCon con) throws Exception{
		
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();

		ndata.put("dowhat", "GetSvIniFileBySections");
		ndata.put("filename", "alert.ini");
		ndata.put("sections", "default");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);

		//svapi.DisplayUtilMapInMap(fmap);

		
		  Iterator  iterator=fmap.keySet().iterator(); 
		  while(iterator.hasNext()) 
		  { 
		     String  key=iterator.next().toString(); 
		     if(key.equals("return"))
		    	 continue;
		     
		     HashMap<String,String> map=fmap.get(key); 
		    //以下增加sv_alert
		     map.put("ALERT_ID",key);
		     map.put("ALERT_NAME",map.remove("AlertName"));
		     map.put("ALERT_TYPE",map.remove("AlertType"));
		     map.put("ALERT_COND",map.remove("AlertCond"));
		     map.put("ALERT_CATEGORY",map.remove("AlertCategory"));
		     if(map.get("AlertState")!=null&&map.remove("AlertState").equals("true"))
		    	 map.put("ALERT_STATE","T");
		     else
		    	 map.put("ALERT_STATE","F");
		     
		     map.put("ALWAYS_TIMES",map.remove("AlwaysTimes"));
		     map.put("ONLY_TIMES",map.remove("OnlyTimes"));
		     map.put("SEL_TIMES1",map.remove("SelTimes1"));
		     map.put("SEL_TIMES2",map.remove("SelTimes2"));
		     TableBean.insert(con,"sv_alert",map);
		     
		     //以下增加sv_alert_target
		     String[] alertTarget=map.get("AlertTarget").toString().split(",");
		     for(int i=0;i<alertTarget.length;i++)
		     {
		    	 if(alertTarget[i].trim().equals(""))
		    		 continue;
		    	 
		    	 con.setSQL("select * from sv_group where GROUP_ID='"+alertTarget[i]+"'");
		    	 QueryResult rs=con.query();
		    	 if(rs.size()==0)
		    	 {
		    		 con.setSQL("select * from sv_ci where CI_ID='"+alertTarget[i]+"'");
		    		 rs=con.query();
		    	 }
		    	 if(rs.size()==0)
		    	 {
		    		 con.setSQL("select * from sv_ci_method where METHOD_ID='"+alertTarget[i]+"'");
		    		 rs=con.query();
		    	 }
		    	 if(rs.size()==0)
		    	 {
		    		 errorMsg.append("告警目标已经不存在,"+"ALERT_ID="+key+":TARGET_ID="+alertTarget[i]+"\n");
		    		 continue;
		    	 }
		    	 
		    	 
		    	 con.setSQL("insert into sv_alert_target(ALERT_ID,TARGET_ID) values(:ALERT_ID,:TARGET_ID)");
		    	 con.setParameter("ALERT_ID", key);
		    	 con.setParameter("TARGET_ID", alertTarget[i]);
		    	 try
		    	 {
		    	   con.execute();
		    	 }catch(Exception e)
		    	 {
		    		 
		    		 errorMsg.append(e.getMessage()+"ALERT_ID="+key+":TARGET_ID="+alertTarget[i]+"\n");
		    	 }
		     }
		     
		     
		     //以下增加sv_alert_attr
		     con.setSQL("select ATTR_NAME from sv_alert_type_attr where ALERT_TYPE=:ALERT_TYPE");
		     con.setParameter("ALERT_TYPE",map.get("ALERT_TYPE") );
		     
		     QueryResult rs=con.query();
		     for(int i=0;i<rs.size();i++)
		     {
		    	 String ATTR_NAME=rs.getObject(i, "ATTR_NAME").toString();
		    	 Object value=map.get(ATTR_NAME);
		    	 if(value!=null)
		    	 {
		    		 con.setSQL("insert into sv_alert_attr(ALERT_ID,ATTR_NAME,ATTR_VALUE) values(:ALERT_ID,:ATTR_NAME,:ATTR_VALUE)");
		    		 con.setParameter("ALERT_ID",key);
		    		 con.setParameter("ATTR_NAME",ATTR_NAME);
		    		 con.setParameter("ATTR_VALUE",value);
		    		 System.out.println(key+"."+ATTR_NAME+"="+value);
		    		 con.execute();
		    	 }
		     }
		     
		   }
	}

	

	private void importTask(DBCon con) throws Exception{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		ndata.put("dowhat", "GetAllTask");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		Iterator iterator = fmap.keySet().iterator();
		
		while (iterator.hasNext()) 
		{
			String taskKey=iterator.next().toString();
			if(taskKey.equals("return"))
				continue;
			
			HashMap map=fmap.get(taskKey);
			
			HashMap commitMap=new HashMap();
			System.out.println("---------"+taskKey);
			Iterator tmpIterator = map.keySet().iterator();
			while (tmpIterator.hasNext()) {
				String key = tmpIterator.next().toString();
				String value=map.get(key).toString();
				System.out.println(key+"="+value);
				commitMap.put(key.toUpperCase(), value);
			}
			commitMap.put("SVNAME", taskKey);
			commitMap.put("TASK_TYPE", commitMap.remove("TYPE"));
			TableBean.insert(con, "sv_alert_task", commitMap);	
		}
	}

}
