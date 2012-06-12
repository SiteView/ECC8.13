package com.siteview.export;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import java.util.Vector;

import com.focus.db.DBCon;
import com.focus.db.QueryResult;
import com.focus.util.Util;
import com.siteview.jsvapi.Jsvapi;

public class SvCiTypeCategory implements Runnable {

	public static int recordCommited = 0;
	Jsvapi svapi = new Jsvapi();
	HashMap<String, HashMap<String, String>> allEntityTempletInfo = null;
	HashMap addedMap = new HashMap();
	StringBuffer errorMsg = new StringBuffer();

	public static void main(String[] args) {

		SvCiTypeCategory svCiTypeCategory = new SvCiTypeCategory();
		svCiTypeCategory.run();
		System.out.println("关键信息:\n" + svCiTypeCategory.errorMsg);
	}

	public void run() {

		long l = System.currentTimeMillis();
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();

		ndata.put("dowhat", "GetAllEntityGroups");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);

		/*
		 * Jsvapi.DisplayUtilMapInMap(fmap);
		 * 
		 * System.out.println("GetUnivData:" + ret); System.out.println("estr:" +
		 * estr); System.out.println("get " + fmap.size() + " node");
		 * System.out.println("time:"+(System.currentTimeMillis()-l));
		 */

		if (fmap.isEmpty()) {
			errorMsg.append("no data in svdb when GetAllEntityGroups!\n");
			return;
		}
		DBCon con = null;
		try {
			con = DBCon.getConnectionByConfig("ofbiz");
			con.setAutoCommit(false);

			con.setSQL("delete from sv_ci_attr");
			con.execute();

			con.setSQL("delete from sv_ci");
			con.execute();

			con.setSQL("delete from sv_group");
			con.execute();

			con.setSQL("delete from sv_ci_type_attr");
			con.execute();
			con.setSQL("delete from sv_ci_type");
			con.execute();
			con.setSQL("delete from sv_ci_type_category");
			con.execute();

			importGroup(con, "default");

			Set<String> keySet = fmap.keySet();
			Iterator iterator = keySet.iterator();
			while (iterator.hasNext()) {
				String key = iterator.next().toString();
				if (key.equals("return")) {
					continue;
				}
				System.out.println("-----------------------" + key
						+ "-----------------------");
				Object value = fmap.get(key);
				if (value instanceof HashMap) {
					dumpHashMap(con, key, (HashMap) value);
				}
			}

			importEntity(con, "default");

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

	/*
	 * 分组数据
	 */
	public void importGroup(DBCon con, String parentid) throws Exception {
		Vector<HashMap<String, String>> fmap = new Vector<HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();

		ndata.put("dowhat", "GetTreeData");
		ndata.put("parentid", parentid);
		ndata.put("onlySon", "true");

		boolean ret = svapi.GetForestData(fmap, ndata, estr);
		for (int i = 0; i < fmap.size(); i++) {
			HashMap<String, String> map = fmap.get(i);

			if (map.get("type").toString().equals("entity")) {
				// importEntityInstance(con,parentid,map);
				continue;
			}
			if (map.get("type").toString().equals("monitor")) {
				// importEntityInstance(con,map);
				continue;
			}

			con
					.setSQL("insert into sv_group(GROUP_ID,GROUP_NAME,DISABLED,STATUS_TYPE_ID,DEPENDON,DEPENDON_STATUS,PARENT_GROUP_ID,SUB_MONITOR_NULL_SUM,SUB_MONITOR_ERROR_SUM,SUB_ENTITY_SUM,SUB_MONITOR_SUM,SUB_POINT_REDUCE_SUM,SV_DESCRIPTION,GRP_TYPE,SUB_NETWORK_SUM,SUB_MONITOR_OK_SUM,SUB_MONITOR_WARNING_SUM,SUB_MONITOR_DISABLE_SUM,SV_INDEX,HAS_SON) values(:GROUP_ID,:GROUP_NAME,:DISABLED,:STATUS_TYPE_ID,:DEPENDON,:DEPENDON_STATUS,:PARENT_GROUP_ID,:SUB_MONITOR_NULL_SUM,:SUB_MONITOR_ERROR_SUM,:SUB_ENTITY_SUM,:SUB_MONITOR_SUM,:SUB_POINT_REDUCE_SUM,:SV_DESCRIPTION,:GRP_TYPE,:SUB_NETWORK_SUM,:SUB_MONITOR_OK_SUM,:SUB_MONITOR_WARNING_SUM,:SUB_MONITOR_DISABLE_SUM,:SV_INDEX,:HAS_SON)");

			con.setParameter("GROUP_ID", map.get("sv_id"));
			con.setParameter("GROUP_NAME", map.get("sv_name"));

			if (map.get("sv_disable") != null
					&& map.get("sv_disable").toString().equals("true"))
				con.setParameter("DISABLED", "T");
			else
				con.setParameter("DISABLED", "F");

			if (map.get("status") != null
					&& !map.get("status").toString().equals("null"))
				con.setParameter("STATUS_TYPE_ID", map.get("status"));
			else
				con.setParameter("STATUS_TYPE_ID", "ok");

			con.setParameter("DEPENDON", map.get("sv_dependson"));

			con.setParameter("DEPENDON_STATUS", map.get("sv_dependscondtion"));

			if (parentid.equals("default"))
				con.setParameter("PARENT_GROUP_ID", null);
			else
				con.setParameter("PARENT_GROUP_ID", parentid);

			con.setParameter("SUB_MONITOR_NULL_SUM", map
					.get("sub_monitor_null_sum"));
			con.setParameter("SUB_MONITOR_ERROR_SUM", map
					.get("sub_monitor_error_sum"));
			con.setParameter("SUB_ENTITY_SUM", map.get("sub_entity_sum"));
			con.setParameter("SUB_MONITOR_SUM", map.get("sub_monitor_sum"));
			con.setParameter("SUB_POINT_REDUCE_SUM", map
					.get("sub_point_reduce_sum"));
			con.setParameter("SV_DESCRIPTION", map.get("sv_description"));

			con.setParameter("GRP_TYPE", map.get("type"));

			con.setParameter("SUB_NETWORK_SUM", map.get("sub_network_sum"));
			con.setParameter("SUB_MONITOR_OK_SUM", map
					.get("sub_monitor_ok_sum"));
			con.setParameter("SUB_MONITOR_WARNING_SUM", map
					.get("sub_monitor_warning_sum"));
			con.setParameter("SUB_MONITOR_DISABLE_SUM", map
					.get("sub_monitor_disable_sum"));
			con.setParameter("SV_INDEX", map.get("sv_index"));

			if (map.get("has_son") != null
					&& map.get("has_son").toString().equals("true"))
				con.setParameter("HAS_SON", "T");
			else
				con.setParameter("HAS_SON", "F");

			con.execute();

			if (map.get("has_son") != null
					&& map.get("has_son").toString().equals("true"))
				importGroup(con, map.get("sv_id"));

			/*
			 * Iterator iterator=map.keySet().iterator();
			 * System.out.println("====================");
			 * while(iterator.hasNext()) { String
			 * key=iterator.next().toString();
			 * System.out.println(key+"="+map.get(key));
			 *  }
			 */
		}

	}

	private void importEntity(DBCon con, String parentid) throws Exception {
		Vector<HashMap<String, String>> fmap = new Vector<HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();

		ndata.put("dowhat", "GetTreeData");
		ndata.put("parentid", parentid);
		ndata.put("onlySon", "true");

		boolean ret = svapi.GetForestData(fmap, ndata, estr);
		for (int i = 0; i < fmap.size(); i++) {
			HashMap<String, String> map = fmap.get(i);

			if (map.get("type").toString().equals("entity"))
				importEntityInstance(con, parentid, map);
			else if (map.get("has_son") != null
					&& map.get("has_son").toString().equals("true"))
				importEntity(con, map.get("sv_id"));

		}
	}

	/* 设备实例数据 */
	private void importEntityInstance(DBCon con, String parentid, HashMap map)
			throws Exception {

		if (map.get("sv_devicetype").equals("")) {
			errorMsg.append("data error:entity " + map.get("sv_id")
					+ " no sv_devicetype\n");
			return;
		}

		/*
		 * Iterator iterator=map.keySet().iterator();
		 * System.out.println("===================="); while(iterator.hasNext()) {
		 * String key=iterator.next().toString();
		 * System.out.println(key+"="+map.get(key));
		 *  }
		 */
		con
				.setSQL("insert into sv_ci(CI_ID,CI_TYPE_ID,CI_NAME,PARENT_GROUP_ID,CI_DESCIPTION,SV_STATUS,CI_DEPEND,CI_DEPEND_STATUS,HAS_SON,SV_DISABLE,SV_NETWORK,SUB_MONITOR_NULL_SUM,SUB_MONITOR_SUM,SUB_MONITOR_OK_SUM,SUB_MONITOR_WARNING_SUM,SUB_MONITOR_DISABLE_SUM,SUB_MONITOR_ERROR_SUM) values(:CI_ID,:CI_TYPE_ID,:CI_NAME,:PARENT_GROUP_ID,:CI_DESCIPTION,:SV_STATUS,:CI_DEPEND,:CI_DEPEND_STATUS,:HAS_SON,:SV_DISABLE,:SV_NETWORK,:SUB_MONITOR_NULL_SUM,:SUB_MONITOR_SUM,:SUB_MONITOR_OK_SUM,:SUB_MONITOR_WARNING_SUM,:SUB_MONITOR_DISABLE_SUM,:SUB_MONITOR_ERROR_SUM)");

		con.setParameter("CI_ID", map.get("sv_id"));

		con.setParameter("CI_TYPE_ID", map.get("sv_devicetype"));
		con.setParameter("CI_NAME", map.get("sv_name"));

		con.setParameter("PARENT_GROUP_ID", parentid);
		con.setParameter("CI_DESCIPTION", map.get("sv_description"));
		con.setParameter("SV_STATUS", map.get("status"));
		con.setParameter("CI_DEPEND", map.get("sv_dependson"));
		con.setParameter("CI_DEPEND_STATUS", map.get("sv_dependscondition"));

		if (map.get("has_son") != null && map.get("has_son").equals("true"))
			con.setParameter("HAS_SON", "T");
		else
			con.setParameter("HAS_SON", "F");

		if (map.get("sv_disable") != null
				&& map.get("sv_disable").equals("true"))
			con.setParameter("SV_DISABLE", "T");
		else
			con.setParameter("SV_DISABLE", "F");

		if (map.get("sv_network") != null
				&& map.get("sv_network").equals("true"))
			con.setParameter("SV_NETWORK", "T");
		else
			con.setParameter("SV_NETWORK", "F");

		con.setParameter("SUB_MONITOR_NULL_SUM", map
				.get("sub_monitor_null_sum"));

		con.setParameter("SUB_MONITOR_SUM", map.get("sub_monitor_sum"));
		con.setParameter("SUB_MONITOR_OK_SUM", map.get("sub_monitor_ok_sum"));

		con.setParameter("SUB_MONITOR_WARNING_SUM", map
				.get("sub_monitor_warning_sum"));
		con.setParameter("SUB_MONITOR_DISABLE_SUM", map
				.get("sub_monitor_disable_sum"));
		con.setParameter("SUB_MONITOR_ERROR_SUM", map
				.get("sub_monitor_error_sum"));

		con.execute();

		// 以下从设备模板得到参数并设置sv_ci_attr
		String CI_TYPE_ID = map.get("sv_devicetype").toString();
		con
				.setSQL("select ATTR_NAME from sv_ci_type_attr where CI_TYPE_ID=:CI_TYPE_ID");
		con.setParameter("CI_TYPE_ID", CI_TYPE_ID);
		QueryResult rs = con.query();
		for (int i = 0; i < rs.size(); i++) {
			con
					.setSQL("insert into sv_ci_attr(CI_ID,ATTR_NAME,ATTR_VALUE) values(:CI_ID,:ATTR_NAME,:ATTR_VALUE)");
			con.setParameter("CI_ID", map.get("sv_id"));
			con.setParameter("ATTR_NAME", rs.getObject(i, "ATTR_NAME"));
			con.setParameter("ATTR_VALUE", map
					.get(rs.getObject(i, "ATTR_NAME")));
			con.execute();
		}

	}

	/*
	 * 导入设备模板大类表
	 */
	public void dumpHashMap(DBCon con, String groupKey, HashMap fmap)
			throws Exception {

		con
				.setSQL("insert into sv_ci_type_category(SV_ID,SV_NAME,SV_LABEL,SV_DESCRIPTION,SV_INDEX,SV_HIDDEN,FILE_NAME,SV_FUNC) values(:SV_ID,:SV_NAME,:SV_LABEL,:SV_DESCRIPTION,:SV_INDEX,:SV_HIDDEN,:FILE_NAME,:SV_FUNC)");
		con.setParameter("SV_ID", groupKey);
		setParameter(con, "SV_NAME", fmap, "sv_name");
		setParameter(con, "SV_LABEL", fmap, "sv_label");
		setParameter(con, "SV_DESCRIPTION", fmap, "sv_description");
		if (fmap.get("sv_hidden") != null
				&& fmap.get("sv_hidden").equals("true"))
			con.setParameter("SV_HIDDEN", "Y");
		else
			con.setParameter("SV_HIDDEN", "N");

		setParameter(con, "FILE_NAME", fmap, "file_name");
		setParameter(con, "SV_FUNC", fmap, "sv_func");
		setParameter(con, "SV_INDEX", fmap, "sv_index");

		con.execute();
		recordCommited++;

		createSvCiType(con, groupKey, fmap);

	}

	/*
	 * 导入设备模板表
	 */
	private void createSvCiType(DBCon con, String groupKey, HashMap fmap)
			throws Exception {
		Object entityTemplateId = fmap.get("entityTemplateId");
		if (entityTemplateId == null)
			return;

		String[] deviceIdArray = entityTemplateId.toString().split(",");

		for (String deviceId : deviceIdArray) {
			con
					.setSQL("insert into sv_ci_type(CI_TYPE_ID,CAT_ID,HAS_TABLE,SV_NAME,SV_LABEL,SV_DESCRIPTION) values(:CI_TYPE_ID,:CAT_ID,:HAS_TABLE,:SV_NAME,:SV_LABEL,:SV_DESCRIPTION)");

			System.out.println(groupKey + "." + deviceId);
			if (addedMap.get(deviceId) != null)
				continue;

			HashMap<String, String> map = getOneEntityTempletInfo(deviceId);

			// CI_TYPE_ID,CAT_ID,HAS_TABLE,SV_NAME,SV_LABEL,SV_DESCRIPTION

			con.setParameter("CI_TYPE_ID", deviceId);
			con.setParameter("CAT_ID", groupKey);
			con.setParameter("HAS_TABLE", "F");

			setParameter(con, "SV_NAME", map, "sv_name");
			setParameter(con, "SV_LABEL", map, "sv_label");
			setParameter(con, "SV_DESCRIPTION", map, "sv_description");

			con.execute();
			recordCommited++;

			createSvCiTypeAttr(con, deviceId);
			addedMap.put(deviceId, groupKey);
		}

	}

	/*
	 * 导入设备模板属性定义表
	 */

	private void createSvCiTypeAttr(DBCon con, String deviceID)
			throws Exception {

		HashMap<String, HashMap<String, String>> attrInfo = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();

		ndata.put("dowhat", "GetEntityTemplet");
		ndata.put("id", deviceID);
		boolean ret = svapi.GetUnivData(attrInfo, ndata, estr);

		Object device_name = null;
		Object SV_VALUE = null;
		Object SV_TYPE = null;
		HashMap<String, String> metaMap =null;
		Iterator iterator = attrInfo.keySet().iterator();
		while (iterator.hasNext()) {
			String key = iterator.next().toString();
			if (!key.startsWith("EntityItem"))
				continue;

			System.out.println("---------" + key + "---------");

			Object value = attrInfo.get(key);
			if (value instanceof HashMap) 
			{
				HashMap curMap = (HashMap) value;
				device_name = curMap.get("sv_name");
				SV_VALUE = curMap.get("sv_value");
				SV_TYPE = curMap.get("sv_type");

				Iterator curIterator = curMap.keySet().iterator();

				metaMap= new HashMap<String, String>();
				while (curIterator.hasNext()) 
				{

					String curKey = curIterator.next().toString();
					if (curKey.equals("sv_name") || curKey.equals("sv_value")
							|| curKey.equals("sv_type"))
						continue;

					System.out.println(curKey + "=" + curMap.get(curKey));
					// metaXml.append("<").append(curKey).append("
					// value=\"").append(curMap.get(curKey)).append("\"/>");
					metaMap.put(curKey, curMap.get(curKey).toString());
				}
			}

			if (device_name == null) {
				System.out.println("错误的数据:deviceID=" + deviceID);
				return;
			}

			/* 写meta表 */

			String fieldid = MetaField.writeMeta(con, SV_TYPE.toString(), metaMap);

			con
					.setSQL("insert into sv_ci_type_attr(CI_TYPE_ID,ATTR_NAME,SV_VALUE,SV_TYPE,METAID) values(:CI_TYPE_ID,:ATTR_NAME,:SV_VALUE,:SV_TYPE,:METAID)");
			con.setParameter("CI_TYPE_ID", deviceID);
			con.setParameter("ATTR_NAME", device_name);
			con.setParameter("METAID", fieldid);
			con.setParameter("SV_VALUE", SV_VALUE);
			con.setParameter("SV_TYPE", SV_TYPE);

			con.execute();
		}

	}

	

	/* 返回map套map结构 */
	private HashMap<String, HashMap<String, String>> getAllEntityTempletInfo() {
		if (allEntityTempletInfo == null) {
			allEntityTempletInfo = new HashMap<String, HashMap<String, String>>();
			HashMap<String, String> ndata = new HashMap<String, String>();
			StringBuilder estr = new StringBuilder();

			ndata.put("dowhat", "GetAllEntityTempletInfo");
			boolean ret = svapi.GetUnivData(allEntityTempletInfo, ndata, estr);
		}
		return allEntityTempletInfo;
	}

	private HashMap<String, String> getOneEntityTempletInfo(String deviceId) {
		return getAllEntityTempletInfo().get(deviceId);
	}

	private static void setParameter(DBCon con, String para, HashMap map,
			String key) {
		try {
			if (map.get(key) != null)
				con.setParameter(para, map.get(key).toString().trim());
			else
				con.setParameter(para, null);
		} catch (Exception e) {
			System.out.println("设置参数" + para + "失败" + e.getMessage());
		}

	}

	private void debugMap(HashMap map) {
		System.out.println("--------------------------------dbugMapStart");
		Iterator iterator = map.keySet().iterator();
		while (iterator.hasNext()) {
			String key = iterator.next().toString();
			if (key.equals("return"))
				continue;

			System.out.println("---------" + key + "---------");
			Object value = map.get(key);
			if (value instanceof HashMap) {
				HashMap curMap = (HashMap) value;
				Iterator curIterator = curMap.keySet().iterator();

				while (curIterator.hasNext()) {
					String curKey = curIterator.next().toString();
					System.out.println(curKey + "=" + curMap.get(curKey));
				}

			}

		}
		System.out.println("--------------------------------dbugMapEnd");
	}
}
