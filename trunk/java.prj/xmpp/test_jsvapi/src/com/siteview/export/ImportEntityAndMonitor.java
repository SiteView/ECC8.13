package com.siteview.export;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Vector;

import com.focus.db.DBCon;
import com.focus.db.QueryResult;
import com.siteview.jsvapi.Jsvapi;

public class ImportEntityAndMonitor {

	
	public static int recordCommited = 0;
	Jsvapi svapi = new Jsvapi();
	HashMap<String, HashMap<String, String>> allMonitorTempletInfo = null;
	HashMap addedMap = new HashMap();
	StringBuffer errorMsg = new StringBuffer();

	public static void main(String[] args) {

		ImportEntityAndMonitor monitor = new ImportEntityAndMonitor();
		monitor.run();
		System.out.println("关键信息:\n" + monitor.errorMsg);
		
	}

	public void run() {
		DBCon con = null;
		try {
			con = DBCon.getConnectionByConfig("ofbiz");
			con.setAutoCommit(false);

			 con.setSQL("delete from sv_ci_method_attr");
			 con.execute();
			 con.setSQL("delete from sv_ci_method");
			 con.execute();
			 con.setSQL("delete from sv_ci_method_type_attr");
			 con.execute();
			 con.setSQL("delete from sv_ci_method_type");
			 con.execute();
			 
			importMonitorTmplate(con);

			importMonitor(con, "default");

			con.commit();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (con != null)
				con.close();
		}
	}

	public void importMonitorTmplate(DBCon con) throws Exception {
		allMonitorTempletInfo = new HashMap<String, HashMap<String, String>>();

		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();

		ndata.put("dowhat", "GetAllMonitorTempletInfo");
		boolean ret = svapi.GetUnivData(allMonitorTempletInfo, ndata, estr);

		//Jsvapi.DisplayUtilMapInMap(allMonitorTempletInfo);
		Iterator iterator = allMonitorTempletInfo.keySet().iterator();
		while (iterator.hasNext()) {
			String key = iterator.next().toString();
			if (key.equals("return"))
				continue;
			HashMap map = allMonitorTempletInfo.get(key);
			con
					.setSQL("insert into sv_ci_method_type(METHOD_TYPE_ID,SV_LABEL,SV_DESCRIPTION,SV_EXTRAFUNC,SV_NAME,SV_HELPLINK,SV_FUNC,SV_DLL,SV_CLASS,SV_EXTRADLL,SV_EXTRASAVE,HAS_TABLE)values(:METHOD_TYPE_ID,:SV_LABEL,:SV_DESCRIPTION,:SV_EXTRAFUNC,:SV_NAME,:SV_HELPLINK,:SV_FUNC,:SV_DLL,:SV_CLASS,:SV_EXTRADLL,:SV_EXTRASAVE,:HAS_TABLE)");
			con.setParameter("METHOD_TYPE_ID", key);
			con.setParameter("SV_LABEL", map.get("sv_label"));
			con.setParameter("SV_DESCRIPTION", map.get("sv_description"));
			con.setParameter("SV_EXTRAFUNC", map.get("sv_extrafunc"));
			con.setParameter("SV_NAME", map.get("sv_name"));
			con.setParameter("SV_HELPLINK", map.get("sv_helplink"));
			con.setParameter("SV_FUNC", map.get("sv_func"));
			con.setParameter("SV_DLL", map.get("sv_dll"));
			con.setParameter("SV_CLASS", map.get("sv_class"));
			con.setParameter("SV_EXTRADLL", map.get("sv_extradll"));
			con.setParameter("SV_EXTRASAVE", map.get("sv_extrasave"));
			con.setParameter("HAS_TABLE", "F");
			con.execute();
			importMonitoyTmplateAttr(con, key);
		}
	}

	public void importMonitoyTmplateAttr(DBCon con, String monitorTmplateId)
			throws Exception {
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();

		// temp= new String("5");

		ndata.put("dowhat", "GetMonitorTemplet");
		ndata.put("id", monitorTmplateId);
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);

		// Jsvapi.DisplayUtilMapInMap(fmap);

		Iterator iterator = fmap.keySet().iterator();
		while (iterator.hasNext()) {
			String key = iterator.next().toString();
			if (key.equals("return")||key.equals("property"))
				continue;

			HashMap map = fmap.get(key);
			if(map==null)
				continue;
			
			
			if(map.get("sv_type")==null)
			{
				errorMsg.append("monitor模板异常,no sv_type "+monitorTmplateId+"."+key+"."+fmap.get("sv_name")+"\n");
				continue;
			}
			HashMap<String, String> metaMap = new HashMap<String, String>();
			Iterator tmp = map.keySet().iterator();
			while (tmp.hasNext()) {
				String tmpkey = tmp.next().toString();
				if (tmpkey.equals("sv_name") || tmpkey.equals("sv_value")
						|| tmpkey.equals("sv_type"))
					continue;

				metaMap.put(tmpkey,map.get(tmpkey).toString());
			}

			if(map.get("sv_type").toString().trim().equals("13")||map.get("sv_type").toString().trim().equals("41"))
			{
				System.out.println("okok");
			}
			String fieldid = MetaField.writeMeta(con, map.get("sv_type").toString(), metaMap);
			
			con
					.setSQL("insert into sv_ci_method_type_attr(METHOD_TYPE_ID,ATTR_NAME,SV_VALUE,SV_TYPE,SV_GROUP,METAID) values(:METHOD_TYPE_ID,:ATTR_NAME,:SV_VALUE,:SV_TYPE,:SV_GROUP,:METAID)");

			con.setParameter("METHOD_TYPE_ID", monitorTmplateId);
			con.setParameter("ATTR_NAME", map.get("sv_name"));
			con.setParameter("SV_VALUE", map.get("sv_value"));
			con.setParameter("SV_TYPE", map.get("sv_type"));
			con.setParameter("SV_GROUP", key);
			con.setParameter("METAID", fieldid);
			
			con.execute();

			importMonitoyTmplateAttr(con, key);
		}
	}

	/*
	 * 设备实例数据
	 * 
	 * condition sv_name sv_label sv_expression sv_operate1 sv_type sv_value
	 * sv_paramnameN sv_paramvalueN sv_helptext good _goodParameter 正常 1(and) <
	 * textarea [进程总数(个) < 1] ProcessCount 1 设置错误条件 error _warningParameter 危险
	 * 2(or) > textarea [进程总数(个) > 1] ProcessCount 1 warning _errorParameter 错误
	 * 1(and) < textarea [进程总数(个) < 1] ProcessCount 1 丢弃信息
	 * sv_conditioncount，原因，冗余 monitorid idx condition sv_expression
	 * sv_paramname sv_operate sv_paramvalue
	 * 
	 */
	private void importMonitorInstance(DBCon con, String parentid, HashMap inMap)
			throws Exception {

		if (inMap.get("sv_monitortype").equals("")) {
			errorMsg.append("data error:monitor " + parentid + "."
					+ inMap.get("sv_name") + " no sv_monitortype\n");
			return;
		}
		/***********************************************************************
		 * Iterator iterator=map.keySet().iterator();
		 * System.out.println("===================="); while(iterator.hasNext()) {
		 * String key=iterator.next().toString();
		 * System.out.println(key+"="+map.get(key)); } /
		 * System.out.println("-----------------------------比较上面的------------");
		 **********************************************************************/

		HashMap<String, HashMap<String, String>> map = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();

		ndata.put("dowhat", "GetMonitor");
		ndata.put("id", inMap.get("sv_id").toString());
		boolean ret = svapi.GetUnivData(map, ndata, estr);
		/*
		 * iterator = map.keySet().iterator();
		 * System.out.println("===================="); while
		 * (iterator.hasNext()) { String key = iterator.next().toString();
		 * System.out.println(key + "=" + map.get(key)); }
		 */

		con
				.setSQL("insert into sv_ci_method(METHOD_ID,CI_ID,METHOD_TYPE_ID,METHOD_NAME,K_L_S_TIMES,K_L_S_SECONDS,METHOD_STATUS,DEPENDON,DEPENDON_STATUS,SV_INTPOS,SV_DISABLE,SV_STARTTIME,SV_ENDTIME) values(:METHOD_ID,:CI_ID,:METHOD_TYPE_ID,:METHOD_NAME,:K_L_S_TIMES,:K_L_S_SECONDS,:METHOD_STATUS,:DEPENDON,:DEPENDON_STATUS,:SV_INTPOS,:SV_DISABLE,:SV_STARTTIME,:SV_ENDTIME)");
		con.setParameter("METHOD_ID", inMap.get("sv_id"));
		con.setParameter("CI_ID", parentid);
		con.setParameter("METHOD_TYPE_ID", inMap.get("sv_monitortype"));
		con.setParameter("METHOD_NAME", inMap.get("sv_name"));
		con.setParameter("DEPENDON", inMap.get("sv_dependson"));
		con.setParameter("DEPENDON_STATUS", inMap.get("dependscondtion"));
		con.setParameter("METHOD_STATUS", inMap.get("status"));
		con.setParameter("SV_INTPOS", inMap.get("sv_intpos"));

		if (inMap.get("sv_disable") != null
				&& inMap.get("sv_disable").equals("true"))
			con.setParameter("SV_DISABLE", "T");
		else
			con.setParameter("SV_DISABLE", "F");

		con.setParameter("SV_STARTTIME", inMap.get("sv_starttime"));
		con.setParameter("SV_ENDTIME", inMap.get("sv_endtime"));

		con.setParameter("K_L_S_TIMES", inMap.get("KLS_times"));
		con.setParameter("K_L_S_SECONDS", inMap.get("KLS_seconds"));

		con.execute();

		/* 构造一个map来取值 */
		HashMap paraMap = (HashMap) map.get("parameter");
		if (paraMap != null) {
			String sv_monitortype = inMap.get("sv_monitortype").toString();
			con
					.setSQL("select ATTR_NAME from sv_ci_method_type_attr where METHOD_TYPE_ID=:METHOD_TYPE_ID");

			con.setParameter("METHOD_TYPE_ID", sv_monitortype);
			QueryResult rs = con.query();
			for (int i = 0; i < rs.size(); i++) {
				con
						.setSQL("insert into sv_ci_method_attr(METHOD_ID,ATTR_NAME,ATTR_VALUE) values(:METHOD_ID,:ATTR_NAME,:ATTR_VALUE)");
				con.setParameter("METHOD_ID", inMap.get("sv_id"));
				con.setParameter("ATTR_NAME", rs.getObject(i, "ATTR_NAME"));
				con.setParameter("ATTR_VALUE", paraMap.get(rs.getObject(i,
						"ATTR_NAME")));
				con.execute();
			}

		}

		/* 以下处理条件域值 */

		importCondition(con, inMap.get("sv_id").toString(), (HashMap) map
				.get("good"), "good");
		importCondition(con, inMap.get("sv_id").toString(), (HashMap) map
				.get("error"), "error");
		importCondition(con, inMap.get("sv_id").toString(), (HashMap) map
				.get("warning"), "warning");

	}

	private void importCondition(DBCon con, String METHOD_ID, HashMap conMap,
			String status) throws Exception {
		
		if(conMap==null)
		{
			errorMsg.append("错误的监测器:没有详细数据"+METHOD_ID+"\n");
			return;
		}
		for (int i = 1; i < 999; i++) 
		{
			if (conMap.get("sv_paramname" + i) == null)
				break;

			con
					.setSQL("insert into sv_ci_method_condition(METHOD_ID,IDX,SV_STATUS,SV_RELATION,SV_PARAMNAME,SV_OPERATE,SV_PARAMVALUE) values(:METHOD_ID,:IDX,:SV_STATUS,:SV_RELATION,:SV_PARAMNAME,:SV_OPERATE,:SV_PARAMVALUE)");

			con.setParameter("METHOD_ID", METHOD_ID);
			con.setParameter("IDX", i);
			con.setParameter("SV_STATUS", status);
			
			con.setParameter("SV_RELATION", conMap.get("sv_relation" + i));
			
				
			con.setParameter("SV_PARAMNAME", conMap.get("sv_paramname" + i));
			con.setParameter("SV_OPERATE", conMap.get("sv_operate" + i));
			con.setParameter("SV_PARAMVALUE", conMap.get("sv_paramvalue" + i));
			con.execute();
		}
	}

	private void importMonitor(DBCon con, String parentid) throws Exception {
		Vector<HashMap<String, String>> fmap = new Vector<HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();

		ndata.put("dowhat", "GetTreeData");
		ndata.put("parentid", parentid);
		ndata.put("onlySon", "true");

		boolean ret = svapi.GetForestData(fmap, ndata, estr);
		for (int i = 0; i < fmap.size(); i++) {
			HashMap<String, String> map = fmap.get(i);

			if (map.get("type").toString().equals("monitor"))
				importMonitorInstance(con, parentid, map);
			else if (map.get("has_son") != null
					&& map.get("has_son").toString().equals("true"))
				importMonitor(con, map.get("sv_id"));

		}
	}
	
	}


