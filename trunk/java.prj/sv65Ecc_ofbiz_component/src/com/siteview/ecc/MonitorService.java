package com.siteview.ecc;

//import java.util.ArrayList;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.GenericDispatcher;
import org.ofbiz.service.LocalDispatcher;
import org.ofbiz.service.ServiceUtil;
import org.ofbiz.service.calendar.RecurrenceRule;

//import com.siteview.ecc.data.MethodBean;
import com.dragonflow.Api.APIMonitor;
import com.dragonflow.Api.SSInstanceProperty;
import com.dragonflow.SiteView.AtomicMonitor;
import com.dragonflow.SiteView.Monitor;
import com.dragonflow.SiteView.Platform;
import com.dragonflow.StandardMonitor.PingMonitor;
import com.dragonflow.Utils.LUtils;
import com.siteview.ecc.data.MethodDB;
import com.siteview.ecc.drive.MonitorDevice;


public class MonitorService {
    public static final String module = MonitorService.class.getName();

     /*
     * 删除一个监测器
     * edit by hailong.yi
     */
    public static Map deleteMonitor(DispatchContext dctx, Map context)
    {
        try {
        	String MonitorID = (String)context.get("MonitorID");
        	MonitorDevice.deleteMonitor(MonitorID,"", dctx.getDelegator());
        	Map<String,Object> result = ServiceUtil.returnSuccess();
        	result.put("_result", "成功");	
	        return result;
        } catch (Exception ex) {
            Debug.logError(ex, "Cannot delete monitor", module);
            return ServiceUtil.returnError("Cannot delete monitor: " + ex.getMessage());
        }        	
     }
}
