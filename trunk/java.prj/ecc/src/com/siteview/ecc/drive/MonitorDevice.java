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
import com.siteview.ecc.data.MethodDB;

public class MonitorDevice {
	public static final String module = MonitorDevice.class.getName();
	
	private static APIMonitor apimonitor = null;
	
	private static String runTimeout = "30";

	//ɾ�������߳�
	public static void deleteMonitor(String monitorID,
			GenericDelegator delegator) throws Exception {
		if (monitorID == null) throw new Exception("method id is null!");
		
		
		Collection collection = getAPIMonitor().getAllMonitors();
		for (Iterator iterator = collection.iterator(); iterator.hasNext();)
		{
			AtomicMonitor monitor = (AtomicMonitor) iterator.next();
			if (monitorID.equals(monitor.getProperty(AtomicMonitor.pID))){
				deleteMonitor(monitor);
    			return;
			}
		}
		throw new Exception("Monitor ID :" + monitorID + " delete fail!");
	}
	
    public static void deleteMonitor(AtomicMonitor atomicmonitor) throws Exception
    {
        
        String id = atomicmonitor.getProperty(AtomicMonitor.pID);
        jgl.Array array = ReadGroupFrames(id);
        AtomicMonitor atomicmonitor1 = AtomicMonitor.MonitorCreate(array, id, "");
        
        SiteViewGroup siteviewgroup = SiteViewGroup.currentSiteView();
        siteviewgroup.notifyMonitorDeletion(atomicmonitor);
        
        ScheduleManager schedulemanager = ScheduleManager.getInstance();
        schedulemanager.deleteMonitorFromScheduleObject(schedulemanager.getScheduleIdFromMonitor(atomicmonitor1), atomicmonitor.getFullID());
        int index = monitorUtils.findMonitorIndex(array, id);
        array.remove(index);
        WriteGroupFrames(id, array);
        
        siteviewgroup.monitorScheduler.unschedule(atomicmonitor.getAction());
     }
    private static jgl.Array ReadGroupFrames(java.lang.String id)
            throws Exception {
        jgl.Array array = com.dragonflow.Properties.FrameFile.readFromFile(getGroupMg());
        if (array.size() == 0) {
            array.add(new HashMap());
        }
        return array;
    }
    private static void WriteGroupFrames(java.lang.String id, jgl.Array array)
            throws Exception {
        String filename = getGroupMg();
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
    public static String getGroupMg() throws Exception
    {
    	return Platform.getRoot() + "/groups/" + getFirstGroupId() + ".mg";
    }

	//���¼����߳�����
	public static void updateMonitor(AtomicMonitor monitor) throws Exception
	{
		String methodId = (String) monitor.getMethodId();
		if (methodId == null) return ;
		
		//�����ݿ�ȡ�ò�����Ϣ
		List<Map<String, String>> method = MethodDB.getMethod(methodId);
		
		for (Map<String, String> parameters : method)
		{
			//��ʾsvdb�еĲ�����Ϣ
			Debug.logInfo("---------------------svdb parameters-------------------------",module);
			for (String key : parameters.keySet()){
				Debug.logInfo(key + " = " + parameters.get(key),module);
			}
			//ȡ��sitescope�еļ�����������
			String methodName = parameters.get("method_name");
			String monitorClass = MonitorDict.getMonitorClass(methodName);
			if (monitorClass == null) {
				Debug.logError("Monitor : " + methodName + " not be found!",module);
				return;
			}
			//svdb�Ĳ���ת����sitescope�Ĳ���(Map��)
			Map<String, String> monitorParams = MonitorDict.convert(parameters);
			
		}
	}
    
    
	//���Ӽ����߳�
	public static void addMonitor(Map<String, String> parameters,
			GenericDelegator delegator) throws Exception {
		
		String methodId = parameters.get("method_id");
		
		//��ʾsvdb�еĲ�����Ϣ
		Debug.logInfo("---------------------svdb parameters-------------------------",module);
		for (String key : parameters.keySet()){
			Debug.logInfo(key + " = " + parameters.get(key),module);
		}
		
		//ȡ��Ҫ������sitescope�еļ�����������
		String methodName = parameters.get("method_name");
		String monitorClass = MonitorDict.getMonitorClass(methodName);
		if (monitorClass == null) {
			Debug.logError("Monitor : " + methodName + " not be found!",module);
			return;
		}

		//svdb�Ĳ���ת����sitescope�Ĳ���(Map��)
		Map<String, String> monitorParams = MonitorDict.convert(parameters);
		
		//������ת��List<SSInstanceProperty>��
		List<SSInstanceProperty> properties = new ArrayList<SSInstanceProperty>();
		Debug.logInfo("---------------------sitescope parameters-------------------------",module);
		for (String key : monitorParams.keySet()){
			Debug.logInfo(key + "=" + monitorParams.get(key),module);
			properties.add(new SSInstanceProperty(key, monitorParams.get(key)));
		}
		
		
	
		Debug.logInfo("createMonitorGroupID=" + getFirstGroupId(),module);
		SSStringReturnValue retvalue = getAPIMonitor().create(monitorClass, getFirstGroupId(), properties.toArray(new SSInstanceProperty[0]),methodId);
        SSMonitorInstance ssmonitorinstance = getAPIMonitor().runExisting(retvalue.getValue(), getFirstGroupId(), (new Long(runTimeout)).longValue());

		Debug.logInfo(" �����������ɹ�! : monitorClass=" +  monitorClass, module);

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
