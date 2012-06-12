package com.siteview.ecc.drive;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import jgl.HashMap;

import org.ofbiz.base.util.Debug;
import org.ofbiz.entity.GenericDelegator;

import com.dragonflow.Api.APIGroup;
import com.dragonflow.Api.APIMonitor;
import com.dragonflow.Api.SSInstanceProperty;
import com.dragonflow.Api.SSMonitorInstance;
import com.dragonflow.Api.SSStringReturnValue;
import com.dragonflow.SiteView.AtomicMonitor;
import com.dragonflow.SiteView.MonitorGroup;
import com.dragonflow.SiteView.Platform;
import com.dragonflow.SiteView.ScheduleManager;
import com.dragonflow.SiteView.SiteViewGroup;
import com.dragonflow.SiteView.monitorUtils;
import com.siteview.ecc.api.GroupEntity;
import com.siteview.ecc.api.MonitorEntity;
import com.siteview.ecc.data.MethodDB;

public class MonitorDevice {
	public static final String module = MonitorDevice.class.getName();
	
	private static APIMonitor apimonitor = null;
	
	private static String runTimeout = "30";

	//…æ≥˝º‡ ”œﬂ≥Ã
	public static void deleteMonitor(String monitorId,String groupId,
			GenericDelegator delegator) throws Exception {
		if (monitorId == null) throw new Exception("method id is null!");
		if (groupId == null) throw new Exception("group id is null!");
		Collection collection = getAPIMonitor().getChildMonitors(groupId);
		for (Iterator iterator = collection.iterator(); iterator.hasNext();)
		{
			AtomicMonitor monitor = (AtomicMonitor) iterator.next();
			if (monitorId.equals(monitor.getProperty(AtomicMonitor.pID))
			){
				deleteMonitor(monitor);
    			return;
			}
		}
		throw new Exception("Monitor ID :" + monitorId + " delete fail!");
	}

    public static void deleteMonitor(AtomicMonitor atomicmonitor) throws Exception
    {
        
        String id = atomicmonitor.getProperty(AtomicMonitor.pID);
        String groupId = atomicmonitor.getProperty(AtomicMonitor.pGroupID);
        jgl.Array array = ReadGroupFrames(id ,groupId);
        AtomicMonitor atomicmonitor1 = AtomicMonitor.MonitorCreate(array, id, "");
        
        SiteViewGroup siteviewgroup = SiteViewGroup.currentSiteView();
        siteviewgroup.notifyMonitorDeletion(atomicmonitor);
        
        ScheduleManager schedulemanager = ScheduleManager.getInstance();
        schedulemanager.deleteMonitorFromScheduleObject(schedulemanager.getScheduleIdFromMonitor(atomicmonitor1), atomicmonitor.getFullID());
        MonitorEntity.delete(groupId,GroupEntity.FILENAME_EXT_MG, id);
        
        siteviewgroup.monitorScheduler.unschedule(atomicmonitor.getAction());
     }
    private static jgl.Array ReadGroupFrames(String id,String groupId)
            throws Exception {
        jgl.Array array = com.dragonflow.Properties.FrameFile.readFromFile(getGroupMg(groupId));
        if (array.size() == 0) {
            array.add(new HashMap());
        }
        return array;
    }
    private static void WriteGroupFrames(String id, jgl.Array array,String groupId)
            throws Exception {
        String filename = getGroupMg(groupId);
        for (int i = 0; i < array.size(); i++) {
            jgl.HashMap hashmap = (jgl.HashMap) array.at(i);
            if (com.dragonflow.Utils.TextUtils.getValue(hashmap, "_encoding")
                    .length() == 0) {
                hashmap.put("_encoding", com.dragonflow.Utils.I18N
                        .nullEncoding());
            }
        }

        com.dragonflow.Properties.FrameFile.writeToFile(filename, array, "_", true);
    }    
    public static String getGroupMg(String groupId) throws Exception
    {
    	return Platform.getRoot() + "/groups/" + groupId + ".mg";
    }


    

	public static APIMonitor getAPIMonitor() throws Exception
	{
		if (apimonitor==null) apimonitor = new APIMonitor();
		return apimonitor;
	}
	
	private static String createMonitorGroupID = null;
	public static String getFirstGroupId() throws Exception
	{
		if (createMonitorGroupID == null){
			APIGroup api = new APIGroup();
			Collection<?> groups = api.getAllGroupInstances();
			Iterator<?> iterator = groups.iterator();
			while(iterator.hasNext()){
				MonitorGroup monitorGroup = (MonitorGroup)iterator.next();
				createMonitorGroupID = monitorGroup.getProperty(MonitorGroup.pGroupID);
				return createMonitorGroupID;
			}
			createMonitorGroupID = "SiteViewGroup";
		}
		return createMonitorGroupID;
	}
}
