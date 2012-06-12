package com.siteview.svecc.service;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import jgl.Array;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;
import com.dragonflow.Properties.HashMapOrdered;

public class DynamicUpdOperate {

	private static jgl.HashMap privateConfigCache;

	public static String dynamicFilePath;

	private static jgl.HashMap privateLocalConfigCache = null;

	public static com.dragonflow.HTTP.HTTPRequest request = null;

	public void initialize(com.dragonflow.HTTP.HTTPRequest httprequest,
			java.io.PrintWriter printwriter) {
		request = httprequest;
	}

	public static Map<String, Object> getDynamicUpdPreferences(
			DispatchContext ctx, Map<?, ?> context) {
		try {
			Map<String, Object> map2 = ServiceUtil.returnSuccess();
			map2.put("result", getDynamicUpdPreferences());
			return map2;
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static List<Map<?, ?>> getDynamicUpdPreferences() throws Exception {
		List<Map<?, ?>> list = new ArrayList<Map<?, ?>>();
		jgl.Array array = new Array();
		java.io.File file = new File(dynamicFilePath);

		if (file.exists()) {

			array = com.dragonflow.Properties.FrameFile
					.readFromFile(dynamicFilePath);
		}
		for (int i = 0; i < array.size(); i++) {
			if (array.at(i) instanceof jgl.HashMap) {
				jgl.HashMap map = (jgl.HashMap) array.at(i);
				Map<String, String> value = (Map<String, String>) BaseClass
						.convert(map);
				if (value.get("_name") == null) {
					value.put("_name", "");
				}
				if (value.get("_host") == null) {
					value.put("_host", "");
				}

				list.add(value);
			}
		}

		return list;
	}

	public static Map<String, Object> getValueById(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			Map<String, Object> map2 = ServiceUtil.returnSuccess();
			map2.put("result", getValueById(context));
			return map2;
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static Map<?, ?> getValueById(Map<?, ?> context) throws Exception {
		String id = (String) context.get("id");
		Map retmap = new HashMap();

		jgl.Array array = new Array();
		java.io.File file = new File(dynamicFilePath);
		if (file.exists()) {
			array = com.dragonflow.Properties.FrameFile
					.readFromFile(dynamicFilePath);
		}
		for (int i = 0; i < array.size(); i++) {
			if (array.at(i) instanceof jgl.HashMap) {
				jgl.HashMap map = (jgl.HashMap) array.at(i);
				retmap = BaseClass.convert(map);
				if (id.equals(retmap.get("_id"))) {
					break;
				}
			}
		}
		return retmap;
	}

	public static Map<String, Object> addDynamicSet(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			addDynamicSet(context);
			Map<String, Object> map2 = ServiceUtil.returnSuccess();
			return map2;
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static void addDynamicSet(Map<?, ?> context) throws Exception {
		Map<?, ?> map = (Map<?, ?>) context.get("result");
		adjustDynamicConfig(BaseClass.convert(map), null);
	}

	public static Map<String, Object> editDynamicSet(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			editDynamicSet(context);
			Map<String, Object> map2 = ServiceUtil.returnSuccess();
			return map2;
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static void editDynamicSet(Map<?, ?> context) throws Exception {
		Map<?, ?> map = (Map<?, ?>) context.get("result");
		String id = (String) context.get("id");
		adjustDynamicConfig(BaseClass.convert(map), id);
	}

	public static Map<String, Object> deleteDynamicSet(DispatchContext ctx,
			Map<?, ?> context) {
		try {
			deleteDynamicSet(context);
			Map<String, Object> map2 = ServiceUtil.returnSuccess();
			return map2;
		} catch (Exception e) {
			return ServiceUtil.returnFailure(e.getMessage());
		}
	}

	public static void deleteDynamicSet(Map<?, ?> context) throws Exception {

		String id = (String) context.get("id");
		adjustDynamicConfig(null, id);
	}

	public static void adjustDynamicConfig(jgl.HashMap hashmap, String s)
			throws Exception {

		jgl.Array array = null;
		array = com.dragonflow.Page.vMachinePage.readDynamicSets();
		jgl.Array array1;
		if (hashmap != null && s == null) {

			jgl.HashMap hashmap1 = getMasterConfig();

			hashmap1 = getMasterConfig();

			s = com.dragonflow.Utils.TextUtils.getValue(hashmap1,
					"_nextDynamicID");
			if (s.length() == 0) {
				s = "10";
			}
			//hashmap1.put("_nextDynamicID", com.dragonflow.Utils.TextUtils
			//        .increment(s));

			Config.configPut("_nextDynamicID", com.dragonflow.Utils.TextUtils
					.increment(s));
			//saveMasterConfig(hashmap1);

			hashmap.put("_id", s);

			array1 = array;
			array1.add(hashmap);
		} else {
			array1 = new Array();
			java.util.Enumeration enumeration = array.elements();
			while (enumeration.hasMoreElements()) {
				jgl.HashMap hashmap2 = (jgl.HashMap) enumeration.nextElement();
				String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap2,
						"_id");
				if (s1 != null
						&& s1.equals(s)
						&& com.dragonflow.SiteView.Monitor
								.isDynamicFrame(hashmap2)) {
					if (hashmap != null) {

						array1.add(hashmap);
					}
				} else {

					array1.add(hashmap2);
				}
			}
		}

		saveDynamicFrameList(array1, "administrator");

	}

	public static void saveDynamicFrameList(jgl.Array array, String s)
			throws Exception {
		try {

			if (!com.dragonflow.SiteView.Platform.isStandardAccount(s)) {
				WriteGroupFrames(s, array);
				com.dragonflow.SiteView.SiteViewGroup.updateStaticPages(s);
			} else {
				com.dragonflow.Properties.FrameFile.writeToFile(
						com.dragonflow.SiteView.Platform.getRoot()
								+ java.io.File.separator + "groups"
								+ java.io.File.separator + "dynamic.config",
						array);
				com.dragonflow.SiteView.SiteViewGroup.updateStaticPages();
			}
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
	}

	static {
		dynamicFilePath = com.dragonflow.SiteView.Platform.getRoot()
				+ java.io.File.separator + "groups" + java.io.File.separator
				+ "dynamic.config";
	}

	public static jgl.HashMap getMasterConfig() {
		if (privateConfigCache == null) {
			privateConfigCache = loadMasterConfig();
		}
		return privateConfigCache;
	}

	public static jgl.HashMap getLocalMasterConfig() {
		if (privateLocalConfigCache == null) {
			privateLocalConfigCache = com.dragonflow.Page.CGI
					.loadMasterConfig(null);
		}
		return privateLocalConfigCache;
	}

	public static jgl.HashMap loadMasterConfig() {
		return com.dragonflow.Page.CGI.loadMasterConfig(request);
	}

	public static jgl.HashMap loadMasterConfig(
			com.dragonflow.HTTP.HTTPRequest httprequest) {
		Object obj = new HashMapOrdered(true);
		try {
			String s = com.dragonflow.Page.CGI.getGroupFilePath("_master",
					httprequest);
			jgl.Array array = com.dragonflow.Properties.FrameFile
					.readFromFile(s);
			obj = (jgl.HashMap) array.front();
		} catch (Exception exception) {
		}
		return ((jgl.HashMap) (obj));
	}

	public static void WriteGroupFrames(String s, jgl.Array array)
			throws Exception {
		com.dragonflow.Page.CGI.WriteGroupFrames(s, array, request);
	}

	public static void WriteGroupFrames(String s, jgl.Array array,
			com.dragonflow.HTTP.HTTPRequest httprequest) throws Exception {
		String s1 = com.dragonflow.Page.CGI.getGroupFilePath(s, httprequest);
		for (int i = 0; i < array.size(); i++) {
			jgl.HashMap hashmap = (jgl.HashMap) array.at(i);
			if (com.dragonflow.Utils.TextUtils.getValue(hashmap, "_encoding")
					.length() == 0) {
				hashmap.put("_encoding", com.dragonflow.Utils.I18N
						.nullEncoding());
			}
		}

		com.dragonflow.Properties.FrameFile.writeToFile(s1, array, "_", true);
	}

}
