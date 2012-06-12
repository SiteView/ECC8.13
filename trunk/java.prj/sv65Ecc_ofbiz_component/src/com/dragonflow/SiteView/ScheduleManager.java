/*
 * 
 * Created on 2005-2-16 16:44:12
 *
 * ScheduleManager.java
 *
 * History:
 *
 */
package com.dragonflow.SiteView;

/**
 * Comment for <code>ScheduleManager</code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;

import com.dragonflow.StandardAction.UpdateMonitor;
import com.dragonflow.Utils.TextUtils;

// Referenced classes of package com.dragonflow.SiteView:
// AtomicMonitor, MonitorGroup, Monitor, SubGroup,
// SiteViewGroup, Scheduler, Platform

public class ScheduleManager {
    class ScheduleObject {

        private String scheduleCache;

        private List<String> associatedMonitorIds = null;

        public String getScheduleCache() {
            return scheduleCache;
        }

        public void setScheduleCache(String s) {
            scheduleCache = s;
        }

        public List<String> getAssociatedMonitors() {
            return associatedMonitorIds;
        }

        public void addToAssociatedMonitors(String s) {
            if (associatedMonitorIds == null) {
                associatedMonitorIds = new ArrayList<String>();
            }
            if (!associatedMonitorIds.contains(s)) {
                associatedMonitorIds.add(s);
            }
        }

        public void deleteFromAssociatedMonitors(String s) {
            if (associatedMonitorIds == null) {
                return;
            }
            if (associatedMonitorIds.contains(s)) {
                associatedMonitorIds.remove(s);
            }
            if (associatedMonitorIds.size() == 0) {
                associatedMonitorIds = null;
                scheduleCache = null;
            }
        }

        public ScheduleObject(String s, ArrayList<String> arraylist) {
            super();
            associatedMonitorIds = arraylist;
            scheduleCache = s;
        }
    }

    private static ScheduleManager _scheduleManagerSingleton;

    private static HashMap<String,ScheduleObject> scheduleMonitorMap = new HashMap<String,ScheduleObject>();

    /* synthetic field */
    static final boolean $assertionsDisabled = !(com.dragonflow.SiteView.ScheduleManager.class).desiredAssertionStatus();

    public static ScheduleManager getInstance() {
        if (_scheduleManagerSingleton == null) {
            synchronized (scheduleMonitorMap) {
                if (_scheduleManagerSingleton == null) {
                    _scheduleManagerSingleton = new ScheduleManager();
                }
            }
        }
        return _scheduleManagerSingleton;
    }

    private ScheduleManager() {
        initScheduleMonitorMap();
    }

    public String getSchedule(Monitor monitor) {
        String scheduleId = getScheduleIdFromMonitor(monitor);
        ScheduleObject scheduleobject = getScheduleObjectFromMap(scheduleId);
        if (scheduleobject == null) {
            addMonitorToScheduleObject((AtomicMonitor) monitor);
            scheduleobject = getScheduleObjectFromMap(scheduleId);
        }
        if (!$assertionsDisabled && scheduleobject == null) {
            throw new AssertionError();
        } else {
        	return scheduleobject.getScheduleCache();
        }
    }

    public void updateSchedule(String scheduleId, String s1) {
        ScheduleObject scheduleobject = getScheduleObjectFromMap(scheduleId);
        if (scheduleobject != null) {
            scheduleobject.setScheduleCache(s1);
            rescheduleMonitorsForSchedule(scheduleId);
        }
    }

    public void addMonitorToScheduleObject(AtomicMonitor atomicmonitor) {
        synchronized (scheduleMonitorMap) {
            String scheduleId = getScheduleIdFromMonitor(atomicmonitor);
            ScheduleObject scheduleobject = getScheduleObjectFromMap(scheduleId);
            if (scheduleobject != null) {
                scheduleobject.addToAssociatedMonitors(atomicmonitor
                        .getFullID());
                if (scheduleobject.getScheduleCache() == null) {
                    scheduleobject.setScheduleCache(getScheduleFromMonitor(atomicmonitor));
                }
            } else {
                ArrayList<String> arraylist = new ArrayList<String>();
                arraylist.add(atomicmonitor.getFullID());
                scheduleobject = new ScheduleObject(getScheduleFromMonitor(atomicmonitor), arraylist);
            }
            putScheduleObjectInMap(scheduleId, scheduleobject);
        }
    }

    public void updateMonitorInScheduleObject(String s,
            AtomicMonitor atomicmonitor) {
        synchronized (scheduleMonitorMap) {
            String s1 = getScheduleIdFromMonitor(atomicmonitor);
            if (!s.equals(s1)) {
                deleteMonitorFromScheduleObject(s, atomicmonitor.getFullID());
                addMonitorToScheduleObject(atomicmonitor);
                SiteViewGroup.currentSiteView().monitorScheduler
                        .unschedule(atomicmonitor.action);
            }
        }
    }

    public void deleteMonitorFromScheduleObject(String scheduleId, String s1) {
        synchronized (scheduleMonitorMap) {
            ScheduleObject scheduleobject = getScheduleObjectFromMap(scheduleId);
            if (!$assertionsDisabled && scheduleobject == null) {
                throw new AssertionError();
            }
            scheduleobject.deleteFromAssociatedMonitors(s1);
            putScheduleObjectInMap(scheduleId, scheduleobject);
        }
    }

    public String getScheduleIdFromMonitor(Monitor monitor) {
        String scheduleId = monitor.getProperty(AtomicMonitor.pSchedule);
        int index = scheduleId.indexOf("_id=");
        if (index != -1) {
        	scheduleId = scheduleId.substring(index + 4);
        }
        return scheduleId;
    }

    public String getScheduleFromMonitor(Monitor monitor) {
        String s = monitor.getProperty(AtomicMonitor.pSchedule);
        int i = s.indexOf("_id=");
        if (i != -1) {
            String scheduleId = s.substring(i + 4);
            s = monitor.getScheduleSettings(scheduleId);
            jgl.HashMap hashmap = TextUtils.stringToHashMap(s);
            s = TextUtils.getValue(hashmap, "_schedule");
        }
        return s;
    }

    public boolean hasMonitorReferences(String scheduleId) {
        boolean flag = false;
        ScheduleObject scheduleobject = getScheduleObjectFromMap(scheduleId);
        if (scheduleobject != null) {
            List<String> list = scheduleobject.getAssociatedMonitors();
            if (list != null && list.size() > 0) {
                flag = true;
            }
        }
        return flag;
    }

    private void initScheduleMonitorMap() {
        for (Enumeration<?> enumeration = currentSiteView()
                .getMonitors(); enumeration.hasMoreElements();) {
            MonitorGroup monitorgroup = (MonitorGroup) enumeration
                    .nextElement();
            Enumeration<?> enumeration1 = monitorgroup.getMonitors();
            while (enumeration1.hasMoreElements()) {
                Monitor monitor = (Monitor) enumeration1.nextElement();
                if (!(monitor instanceof SubGroup)) {
                    addMonitorToScheduleObject((AtomicMonitor) monitor);
                }
            }
        }

    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @return
     */
    private ScheduleObject getScheduleObjectFromMap(String scheduleId) {
        synchronized (ScheduleManager.scheduleMonitorMap) {
            return (ScheduleObject) scheduleMonitorMap.get(scheduleId);
        }
    }

    private void putScheduleObjectInMap(String scheduleId, ScheduleObject scheduleobject) {
        synchronized (scheduleMonitorMap) {
            scheduleMonitorMap.put(scheduleId, scheduleobject);
        }
    }

    private void rescheduleMonitorsForSchedule(String scheduleId) {
        ScheduleObject scheduleobject = getScheduleObjectFromMap(scheduleId);
        if (scheduleobject != null) {
            List<String> list = scheduleobject.getAssociatedMonitors();
            if (list != null) {
                for (String s1 : list) {
                    AtomicMonitor atomicmonitor = (AtomicMonitor) currentSiteView().getElement(s1);
                    currentSiteView().monitorScheduler.unschedule(atomicmonitor.action);
                    rescheduleMonitor(atomicmonitor, scheduleobject.getScheduleCache(), 0L);
                }

            }
        }
    }

    private void rescheduleMonitor(AtomicMonitor atomicmonitor, String s, long l) {
        UpdateMonitor updatemonitor = new UpdateMonitor(atomicmonitor);
        if (l == 0L) {
            l = Platform.timeMillis();
        }
        if (s.startsWith("*")) {
            currentSiteView().monitorScheduler.scheduleAbsolutePeriodicAction(updatemonitor, s, l);
        } else {
            long l1 = atomicmonitor.getPropertyAsLong(AtomicMonitor.pFrequency) * 1000L;
            if (l1 != 0L) {
                currentSiteView().monitorScheduler.scheduleRepeatedPeriodicAction(updatemonitor, l1, l);
            }
        }
    }
    
    private SiteViewGroup currentSiteView()
    {
    	return SiteViewGroup.currentSiteView();
    }

 }
