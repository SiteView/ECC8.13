package com.siteview.svecc.service;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;

import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericEntityException;
import org.ofbiz.entity.GenericPK;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityConditionList;
import org.ofbiz.entity.condition.EntityExpr;
import org.ofbiz.entity.condition.EntityOperator;
import org.ofbiz.entity.util.EntityFindOptions;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

import com.dragonflow.Api.*;
import com.dragonflow.Properties.HashMapOrdered;

import jgl.Array;
import jgl.HashMap;

public class SvAlert extends BaseClass {

	public static final String module = Group.class.getName();

	private static com.dragonflow.Api.APIAlert apialert = new APIAlert();

	public static Map<?, ?> alertAdd(DispatchContext dctx, Map<?, ?> context) {
		GenericDelegator delegator = dctx.getDelegator();
		try {
			String category_res = (String) context.get("category_res"); // get
																		// the
																		// input

			// String defid = delegator.getNextSeqId("SvAlertDef"); // gets next
			// available key for HelloPerson
			// Debug.logInfo("defid = " + defid, module); // prints to the
			// console
			// // or console.log
			// GenericValue svAlertSet = delegator.makeValue("SvAlertDef",
			// UtilMisc.toMap("defid", defid)); // create a GenericValue from ID
			// we just got
			// svAlertSet.setNonPKFields(context); // move non-primary key
			// fields from input parameters to GenericValue
			// delegator.create(svAlertSet); // store the generic value, ie
			// persists it
			//
			Map<String, Object> result = ServiceUtil.returnSuccess(); // gets
																		// standard
																		// Map
																		// for
																		// successful
																		// service
																		// operations
			result.put("idOut", category_res); // puts output parameter into
												// Map to return
			return result; // return Map
			// } catch (GenericEntityException ex) { // required if you use
			// delegator
		} catch (Exception ex) { // required if you use delegator
			// in Java
			Debug.logWarning(ex, module);
			Map<String, Object> retresult = ServiceUtil
					.returnError("Error addAlertSet: " + ex.toString());
			retresult.put("message", ex.toString());
			return retresult;
		}
	}

	public static Map<?, ?> getAlert(DispatchContext dctx, Map<?, ?> context) {
		try {
			jgl.Array al = apialert.getConditions();
			List<java.util.HashMap> lh = new ArrayList<java.util.HashMap>();
			for (int i = 0; i < al.size(); i++) {
				jgl.HashMap jhm = (jgl.HashMap) al.at(i);
				java.util.HashMap hm = new java.util.HashMap();
				hm.put("raw", jhm.get("raw"));
				hm.put("group", jhm.get("group"));
				hm.put("monitor", jhm.get("monitor"));
				hm.put("expression", jhm.get("expression"));
				hm.put("id", jhm.get("id"));
				hm.put("action", jhm.get("action"));
				hm.put("category", jhm.get("category"));
				hm.put("disabled", jhm.get("disabled"));
				hm.put("on", jhm.get("on"));
				hm.put("command", jhm.get("command"));
				hm.put("do", jhm.get("do"));
				hm.put("for", jhm.get("for"));
				hm.put("groupName", jhm.get("groupName"));
				lh.add(hm);
			}
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			Debug.logInfo("result = " + lh, module);

			if (lh != null)
				retresult.put("result", lh);
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError(e
					.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
		// GenericDelegator delegator = dctx.getDelegator(); // always passed in
		// with DispatchContext
		// try {
		// Map<String, Object> retresult = ServiceUtil.returnSuccess();
		// List<?> ll = delegator.findList("SvAlertDef", null, null, null, null,
		// false);
		// Debug.logInfo("result = " + ll, module);
		//
		// if(ll != null)
		// retresult.put("result", ll);
		// return retresult;
		// } catch (Exception e) {
		// Debug.logWarning(e, module);
		// Map<String, Object> retresult =
		// ServiceUtil.returnError(e.toString());
		// retresult.put("message", e.toString());
		// return retresult;
		// }
	}

	public static Map<?, ?> getAlertById(DispatchContext dctx, Map<?, ?> context) {
		GenericDelegator delegator = dctx.getDelegator();
		try {
			String setId = (String) context.get("defid");
			Debug.logInfo("defid = " + setId, module);

			// query the entity HelloPerson looking based on a findByPrimaryKey
			// method
			Map queryResult = delegator.findByPrimaryKey("SvAlertDef", UtilMisc
					.toMap("defid", setId));
			Debug.logInfo("queryResult = " + queryResult, module);

			// create the output Map object
			Map result = UtilMisc.toMap("defid", setId);
			// fill the output object with the query results if any
			if (queryResult != null) {
				result.put("alerton", queryResult.get("alerton"));
				result.put("typename", queryResult.get("typename"));
				result.put("subjects", queryResult.get("subjects"));
				result.put("action", queryResult.get("action"));
				result.put("msgtemplate", queryResult.get("msgtemplate"));
				result.put("whendo", queryResult.get("whendo"));
				result.put("disable", queryResult.get("disable"));
				result.put("nameflt", queryResult.get("nameflt"));
				result.put("statusflt", queryResult.get("statusflt"));
				result.put("monitorflt", queryResult.get("monitorflt"));
				result.put("extenddata", queryResult.get("extenddata"));
			}
			Debug.logInfo("result = " + result, module);
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("mapOut", result);
			return retresult;
		} catch (GenericEntityException ex) { // required if you use delegator
			// in Java
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	public static Map<?, ?> getAlertDefBySubject(DispatchContext dctx,
			Map<?, ?> context) {
		// GenericDelegator delegator =
		// GenericDelegator.getGenericDelegator("default");
		GenericDelegator delegator = dctx.getDelegator();
		try {
			String subjectids = (String) context.get("SubjectId");
			Debug.logInfo("SubjectId = " + subjectids, module);

			String[] idlist = subjectids.split(",");
			String entityName = "SvAlertDef";
			List andExprs = new ArrayList();
			EntityConditionList mainCond = null;

			if (idlist.length > 0) {
				for (int i = 0; i < idlist.length; ++i) {
					andExprs.add(new EntityExpr("subjects", true,
							EntityOperator.LIKE, "%" + idlist[i] + "%", true));
				}
			}

			// 要显示的字段列表
			List fieldsToSelect = new ArrayList();
			fieldsToSelect.add("DEFID");
			fieldsToSelect.add("ALERTON");
			fieldsToSelect.add("TYPENAME");
			fieldsToSelect.add("SUBJECTS");
			fieldsToSelect.add("ACTION");
			fieldsToSelect.add("MSGTEMPLATE");
			fieldsToSelect.add("WHENDO");

			// Distinct列表
			EntityFindOptions findOpts = new EntityFindOptions(true,
					EntityFindOptions.TYPE_SCROLL_INSENSITIVE,
					EntityFindOptions.CONCUR_READ_ONLY, true);

			EntityCondition conditionOne = EntityCondition.makeCondition(
					andExprs, EntityOperator.OR);

			List<?> ll = delegator.findList("SvAlertDef", conditionOne, null,
					null, null, false);

			Debug.logInfo("result = " + ll, module);

			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			if (ll != null)
				retresult.put("mapOut", ll);
			return retresult;
		} catch (GenericEntityException ex) { // required if you use delegator
			// in Java
			return ServiceUtil.returnError(ex.getMessage());
		}
	}

	private static List getHistoryById(String alertid) {
		List list_res = new ArrayList();
		return list_res;
	}

	public static Map<?, ?> alertHistory(DispatchContext dctx,
			Map<String, ?> context) {
		try {
			String alertid = (String) context.get("alertid");
			List res_list = getHistoryById(alertid);
			Map<String, Object> result = ServiceUtil.returnSuccess();
			result.put("alertid", alertid);
			result.put("data_history", res_list);
			return result;
		} catch (Exception ex) {
			Debug.logWarning(ex, module);
			Map<String, Object> retresult = ServiceUtil
					.returnError("Error alertHistory: " + ex.toString());
			retresult.put("message", ex.toString());
			return retresult;
		}
	}

	public static Map<?, ?> alertEdit(DispatchContext dctx,
			Map<String, ?> context) {

		try {
			String alertid = (String) context.get("alertid");
			com.dragonflow.Api.Alert alert = com.dragonflow.Api.Alert
					.getInstance().getByID((new Long(alertid)).longValue());
			String raw = alert.getCondStr();
			jgl.Array array = com.dragonflow.SiteView.Platform.split('\t', raw);
			String monitorId = alert.getMonitorID();
			String groupId = alert.getGroup();
			jgl.HashMap hashmap1 = new jgl.HashMap();
			jgl.HashMap hashmap = (new APIAlert()).parseCondition(raw,
					hashmap1, groupId, monitorId);

			Map<String, Object> result = ServiceUtil.returnSuccess();

			result.put("alertid", alertid);
			result.put("alertdata", hashmap);
			return result;
		} catch (Exception ex) {
			Debug.logWarning(ex, module);
			Map<String, Object> retresult = ServiceUtil
					.returnError("Error alertEdit: " + ex.toString());
			retresult.put("message", ex.toString());
			return retresult;
		}

		// GenericDelegator delegator = dctx.getDelegator();
		// try {
		// GenericValue svAlertSet = delegator
		// .makeValue("SvAlertDef", context);
		// delegator.createOrStore(svAlertSet);
		// Map<String, Object> result = ServiceUtil.returnSuccess();
		// result.put("idOut", context.get("defid"));
		// return result;
		// } catch (GenericEntityException ex) {
		// Debug.logWarning(ex, module);
		// Map<String, Object> retresult = ServiceUtil
		// .returnError("Error alertEdit: " + ex.toString());
		// retresult.put("message", ex.toString());
		// return retresult;
		// }
	}

	private static Map<?, ?> getAlertData() {
		Map<String, Object> result = ServiceUtil.returnSuccess();
		return result;
	}

	public static Map<?, ?> alertDefine(DispatchContext dctx,
			Map<String, ?> context) {
//		GenericDelegator delegator = dctx.getDelegator();
		try {
			String category_alert = (String) context.get("category_alert");
			String class_alert = (String) context.get("class_alert");
			String define_flag = (String) context.get("define_flag");
			String alertid = (String) context.get("alertid");

			List<Map<String, Object>> group_list = Group.getAllGroup();// (ArrayList)context.get("group_list");
			List<Map<String, Object>> monitor_list = new ArrayList<Map<String, Object>>();
			for (Map<String, Object> m : group_list) {
				monitor_list.addAll(Monitor.getMonitorByGroupId(m
						.get("groupID").toString()));
			}
			Map<String, Object> result = ServiceUtil.returnSuccess();
			result.put("alertid", alertid);
			result.put("category_alert", category_alert);
			result.put("class_alert", class_alert);
			result.put("define_flag", define_flag);
			result.put("group_list", group_list);
			result.put("monitor_list", monitor_list);

			jgl.HashMap hashmap = new jgl.HashMap();
			if (!alertid.isEmpty() && !alertid.equalsIgnoreCase("none")) {
				com.dragonflow.Api.Alert alert = com.dragonflow.Api.Alert
				.getInstance().getByID(Long.parseLong(alertid));
				String raw = alert.getCondStr();
				String monitorId = alert.getMonitorID();
				String groupId = alert.getGroup();
				jgl.HashMap hashmap1 = new jgl.HashMap();
				hashmap = (new APIAlert()).parseCondition(raw,
						hashmap1, groupId, monitorId);
			}
			result.put("Data_alert", hashmap);
			return result;
		} catch (Exception ex) {
			Debug.logWarning(ex, module);
			Map<String, Object> retresult = ServiceUtil
					.returnError("Error alertDefine: " + ex.toString());
			retresult.put("message", ex.toString());
			return retresult;
		}
	}

	private static String getActionClass(String s) {
		int i = s.indexOf(" ");
		if (i >= 0) {
			return com.dragonflow.Utils.TextUtils.toInitialUpper(s.substring(0,
					i));
		} else {
			return com.dragonflow.Utils.TextUtils.toInitialUpper(s);
		}
	}

	public static Map<?, ?> alertSave(DispatchContext dctx, Map<?, ?> context) {
		GenericDelegator delegator = dctx.getDelegator();
		try {
			String category = (String) context.get("category_alert") == null ? ""
					: (String) context.get("category_alert");
			String class_alert = (String) context.get("class_alert");
			if (class_alert.equals("none"))
				class_alert = "";
			String define_flag = (String) context.get("define_flag");
			String alertid = (String) context.get("alertid");
			String when = (String) context.get("when") == null ? ""
					: (String) context.get("when");
			String targets = (String) context.get("target_alert") == null ? ""
					: (String) context.get("target_alert");
			String errorCount = (String) context.get("errorCount") == null ? ""
					: (String) context.get("errorCount");
			String alwaysErrorCount = (String) context.get("alwaysErrorCount") == null ? ""
					: (String) context.get("alwaysErrorCount");

			String multipleStartCount = (String) context
					.get("multipleStartCount") == null ? "" : (String) context
					.get("multipleStartCount");
			String multipleErrorCount = (String) context
					.get("multipleErrorCount") == null ? "" : (String) context
					.get("multipleErrorCount");
			String maxErrorCount = (String) context.get("maxErrorCount") == null ? ""
					: (String) context.get("maxErrorCount");

			String nameMatchString = (String) context.get("nameMatchString") == null ? ""
					: (String) context.get("nameMatchString");
			String statusMatchString = (String) context
					.get("statusMatchString") == null ? "" : (String) context
					.get("statusMatchString");
			String classMatchString = (String) context.get("classMatchString") == null ? ""
					: (String) context.get("classMatchString");

			String usePreviousErrorCount = (String) context
					.get("usePreviousErrorCount") == null ? ""
					: (String) context.get("usePreviousErrorCount");
			String previousErrorCount = (String) context
					.get("previousErrorCount") == null ? "" : (String) context
					.get("previousErrorCount");
			String alertDisable = (String) context.get("alertDisable") == null ? ""
					: (String) context.get("alertDisable");

			String disableAlertTime = (String) context.get("disableAlertTime") == null ? ""
					: (String) context.get("disableAlertTime");
			String disableAlertUnits = (String) context
					.get("disableAlertUnits") == null ? "" : (String) context
					.get("disableAlertUnits");

			String startTimeDate = (String) context.get("startTimeDate") == null ? ""
					: (String) context.get("startTimeDate");
			String startTimeTime = (String) context.get("startTimeTime") == null ? ""
					: (String) context.get("startTimeTime");
			String endTimeDate = (String) context.get("endTimeDate") == null ? ""
					: (String) context.get("endTimeDate");
			String endTimeTime = (String) context.get("endTimeTime") == null ? ""
					: (String) context.get("endTimeTime");

			jgl.HashMap hashmap = new HashMap();
			hashmap.put("alertDisable", alertDisable);
			hashmap.put("alwaysErrorCount", alwaysErrorCount);
			hashmap.put("category", category);
			hashmap.put("classMatchString", classMatchString);
			hashmap.put("disableAlertTime", disableAlertTime);
			hashmap.put("disableAlertUnits", disableAlertUnits);
			hashmap.put("endTimeDate", endTimeDate);
			hashmap.put("endTimeTime", endTimeTime);
			hashmap.put("errorCount", errorCount);
			hashmap.put("maxErrorCount", maxErrorCount);
			hashmap.put("multipleErrorCount", multipleErrorCount);
			hashmap.put("multipleStartCount", multipleStartCount);
			hashmap.put("nameMatchString", nameMatchString);
			hashmap.put("previousErrorCount", previousErrorCount);
			hashmap.put("startTimeDate", startTimeDate);
			hashmap.put("startTimeTime", startTimeTime);
			hashmap.put("statusMatchString", statusMatchString);
			hashmap.put("usePreviousErrorCount", usePreviousErrorCount);
			hashmap.put("when", when);

			Alert alert = Alert.getInstance();
			Alert alertnew;
			if (define_flag.equals("Update")) {
				alertnew = alert.getByID(Long.parseLong(alertid));
				jgl.Array array = com.dragonflow.SiteView.Platform.split('\t',
						alertnew.getCondStr());
				class_alert = getActionClass((String) array.at(1));
			} else {
				String ts[] = com.dragonflow.Utils.TextUtils
						.split(targets, ",");
				alertnew = alert.createAlert(ts);
			}
			com.dragonflow.SiteView.Action action = com.dragonflow.SiteView.Action
					.createAction(class_alert);

			jgl.HashMap hashmap1 = new HashMap();
			String alertCond = apialert.packCondition(hashmap, action
					.getActionString(), hashmap1);

			if (hashmap1.size() == 0) {
				if (define_flag.equals("Update")) {
					apialert.removeCondition(alertnew);
					jgl.HashMap jglmap = apialert.addCondition(alertnew,
							alertCond);
				} else {
					action.getClassProperty("name");
					apialert.addCondition(alertnew, alertCond);
				}
			}

			Map Data_alert = (Map) context.get("data_alert");
			Map<String, Object> result = ServiceUtil.returnSuccess();
			result.put("category_alert", category);
			result.put("class_alert", class_alert);
			result.put("alertid", "");
			result.put("Data_alert", Data_alert);
			result.put("define_flag", define_flag);
			result.put("message", "OK");
			return result;
			// } catch (GenericEntityException ex) { // required if you use
			// delegator in java
		} catch (Exception ex) {
			Debug.logWarning(ex, module);
			Map<String, Object> retresult = ServiceUtil
					.returnError("Error addAlertSet: " + ex.toString());
			retresult.put("message", ex.toString());
			return retresult;
		}
	}

	public static Map<?, ?> alertDelete(DispatchContext dctx, Map<?, ?> context) {
//		GenericDelegator delegator = dctx.getDelegator(); 
//		try {
//			Debug.logInfo("remove alertset, defid = " + context.get("defid"),
//					module);
//			int ii = delegator.removeByPrimaryKey((GenericPK) (context
//					.get("defid")));
//			Map<String, Object> result = ServiceUtil.returnSuccess(); 
//			result.put("idOut", context.get("defid")); 
//			return result; // return Map
//		} catch (Exception e) {
//			Debug.logWarning(e, module);
//			return ServiceUtil.returnError(e.getMessage());
//		}

		try {
			Map<String, Object> result = ServiceUtil.returnSuccess();
			result.put("alertid", "none");
			if(context.get("alertid") != null)
			{
				String alertid = (String)context.get("alertid");				
				com.dragonflow.Api.Alert alert = com.dragonflow.Api.Alert
				.getInstance().getByID(Long.parseLong(alertid));
				Debug.logInfo("remove alertid = " + alertid, module);
				(new APIAlert()).removeCondition(alert);
				result.put("alertid", alertid);
			}
			return result; // return Map
		} catch (Exception e) {
			Debug.logWarning(e, module);
			return ServiceUtil.returnError(e.getMessage());
		}
	}

	public static Map<?, ?> alertTest(DispatchContext dctx, Map<?, ?> context) {
		GenericDelegator delegator = dctx.getDelegator(); // always passed in
		// with
		// DispatchContext
		try {
			Debug.logInfo("remove alertset, defid = " + context.get("defid"),
					module);
			int ii = delegator.removeByPrimaryKey((GenericPK) (context
					.get("defid")));
			Map<String, Object> result = ServiceUtil.returnSuccess();
			result.put("idOut", context.get("defid"));
			return result; // return Map
		} catch (Exception e) {
			Debug.logWarning(e, module);
			return ServiceUtil.returnError(e.getMessage());
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		GenericDelegator delegator = GenericDelegator
				.getGenericDelegator("defalut");
		try {
			Debug.logInfo("remove alertdef, defid = 10000", module);
			List<?> ll = delegator.findList("SvAlertDef", null, null, null,
					null, false);
			// int ii = delegator.removeByPrimaryKey((GenericPK)("10000"));
			Map<String, Object> result = ServiceUtil.returnSuccess();
			result.put("idOut", "10000"); // puts output parameter into Map to
			// return
			return; // return Map
		} catch (Exception e) {
			Debug.logWarning(e, module);
			return;
		}

	}

}
