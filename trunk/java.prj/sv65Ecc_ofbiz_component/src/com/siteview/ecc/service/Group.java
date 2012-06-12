package com.siteview.ecc.service;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONObject;
import org.ofbiz.base.util.Debug;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

import com.dragonflow.Api.APIGroup;
import com.dragonflow.Api.SSInstanceProperty;
import com.dragonflow.Properties.PropertiedObject;
import com.dragonflow.SiteView.AtomicMonitor;
import com.dragonflow.SiteView.MonitorGroup;
import com.dragonflow.SiteView.SiteViewGroup;

class Group {
	public static final String module = Group.class.getName();

	public static List<MonitorGroup> getGroupById(String id) throws Exception {
		APIGroup api = new APIGroup();
		Collection<PropertiedObject> groups = null;
		if (id == null) {
			SiteViewGroup siteViewGroup = SiteViewGroup.currentSiteView();
			String viewid = siteViewGroup.getProperty(SiteViewGroup.pID);
			groups = api.getChildGroupInstances(viewid);
		} else {
			groups = api.getChildGroupInstances(id);
		}
		Iterator iterator = groups.iterator();

		List<MonitorGroup> retlist = new ArrayList<MonitorGroup>();

		while (iterator.hasNext()) {
			MonitorGroup monitorGroup = (MonitorGroup) iterator.next();
			if (id == null) {
				if (monitorGroup.getParent() == null)
				{
					retlist.add(monitorGroup);
				}
			}else{
				retlist.add(monitorGroup);
			}
		}
		return retlist;
	}


	public static Boolean haveChildren(String id) throws Exception {
		APIGroup api = new APIGroup();
		if (id == null)
			return false;
		Collection<PropertiedObject> groups = api.getChildGroupInstances(id);
		Iterator iterator = groups.iterator();

		while (iterator.hasNext()) {
			return true;
		}
		return Monitor.haveMonitor(id);
	}

	public static Map<?, ?> getChildren(DispatchContext ctx, Map<?, ?> context) {
		try {
			String parentId = (String) context.get("parentId");
			parentId = parentId == null ? null : "".equals(parentId) ? null
					: "null".equals(parentId) ? null : parentId;
			List<MonitorGroup> list = getGroupById(parentId);

			JSONArray result = new JSONArray();

			for (MonitorGroup group : list) {
				JSONObject jsonGnmkObject = new JSONObject();
				String name = group.getProperty(MonitorGroup.pName);
				String id = group.getProperty(MonitorGroup.pID);
				jsonGnmkObject.put("label","(" + id + ")" + name);
				jsonGnmkObject.put("id", id);
				jsonGnmkObject.put("isLeaf", !haveChildren(group
						.getProperty(MonitorGroup.pID)));
				jsonGnmkObject.put("labelStyle", "icon-group");
				jsonGnmkObject.put("href",
						"/svecc/control/listMonitor?groupId="
								+ id);

				result.put(jsonGnmkObject);
			}

			if (parentId != null) {
				List<AtomicMonitor> monitors = Monitor
						.getMonitorByGroupId(parentId);
				for (AtomicMonitor monitor : monitors) {
					JSONObject jsonGnmkObject = new JSONObject();
					jsonGnmkObject.put("label", monitor
							.getProperty(MonitorGroup.pName));
					jsonGnmkObject.put("id", monitor
							.getProperty(MonitorGroup.pID));
					jsonGnmkObject.put("isLeaf", Boolean.TRUE);
					jsonGnmkObject.put("labelStyle", "icon-monitor");
					jsonGnmkObject.put("href",
							"/svecc/control/monitorDetail?monitorId="
									+ monitor
									.getProperty(MonitorGroup.pID));
					result.put(jsonGnmkObject);
				}
			}

			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("outtext", result.toString());
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			return ServiceUtil.returnError("Error getChildren: "
					+ e.toString());
		}

	}

	public static Map<?, ?> addGroup(DispatchContext ctx, Map<?, ?> context) {
		try {
			String groupName = (String) context.get("groupName");
			if (groupName == null || "".equals(groupName.trim()))
				throw new Exception("group name is null!");
			String description = (String) context.get("_description");
			String dependsOn = (String) context.get("_dependsOn");
			String dependsCondition = (String) context.get("_dependsCondition");
			String refreshTime = (String) context.get("_frequency");
			String refreshTimeUtil = (String) context.get("_frequencyUnits");

			APIGroup api = new APIGroup();
			List<SSInstanceProperty> properties = new ArrayList<SSInstanceProperty>();
			
			properties.add(new SSInstanceProperty("_description", description));
			properties.add(new SSInstanceProperty("_dependsOn", dependsOn));
			properties.add(new SSInstanceProperty("_dependsCondition", dependsCondition));
			properties.add(new SSInstanceProperty("_frequency", refreshTime));
			properties.add(new SSInstanceProperty("_frequencyUnits", refreshTimeUtil));
			
			
			api.create(groupName, dependsOn, properties.toArray(new SSInstanceProperty[0]));

			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			return ServiceUtil.returnError("Error addGroup: "
					+ e.toString());
		}
	}
}
