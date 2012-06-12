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

    // ��Ӽ����
    public static Map addMonitor(DispatchContext dctx, Map context) {
        try {
        	System.out.println("=================== addMonitor ==============================");
        	// ���ݿ��������
	    	//GenericDelegator delegator = dctx.getDelegator();	    	
	    	
        	String key, value;
        	String machineName = "";
        	//String newid;
        	
        	/*
        	 * ��ȡ���������ֵ, д�����ݿ���       	 
        	 * 
        	 * */ 
        	
        	Iterator<?> it = context.keySet().iterator();
        	while (it.hasNext()){
        	    key = it.next().toString();
        	    value = context.get(key).toString();
        	    
        	    if(key == "_MachineName")
        	    {
        	    	machineName = value;
        	    }
        	    System.out.println("addMonitor: key=" + key + "; value=" + value);        	    
        	    
        	    /*
        	    newid = delegator.getNextSeqId("svCiMethod");
        	    GenericValue monitorTable = delegator.makeValue("svXXX");
    	    	monitorTable.set( "id", newid);
    	    	monitorTable.set( "name", key);
    	    	monitorTable.set( "value", value);    	    	
    	    	monitorTable.create();
    	    	*/
        	}     
	    	
        	System.out.println("=================== addMonitor =============================="); 
        	
        	Map<String,Object> result = ServiceUtil.returnSuccess();	 
        	result.put("_result", "�������ӳɹ���");		// eventMessage
	        result.put("_MachineName", machineName);
	        
	        //
	        loadMonitor(dctx, context);
	        
	        return result;
        } catch (Exception ex) {
            Debug.logError(ex, "Cannot add ping monitor", module);
            return ServiceUtil.returnError("Cannot add ping monitor: " + ex.getMessage());
        }
    }
    
    /*
     * װ�ؼ�������ݣ��ɽ������
     */
    public static Map loadMonitor(DispatchContext dctx, Map context) {
        try {
        	loadMonitor();
        	
        	Map<String,Object> result = ServiceUtil.returnSuccess();
           	result.put("_result", "װ�سɹ���");		// eventMessage        	
	        return result;
        } catch (Exception ex) {
            Debug.logError(ex, "Cannot run monitor", module);
            return ServiceUtil.returnError("Cannot run monitor: " + ex.getMessage());
        }        	
    }
    
    /*
     * װ�ؼ����������ӵ��ƻ��������
     */    
    public static void loadMonitor() throws Exception{
        	GenericDelegator delegator = GenericDelegator.getGenericDelegator("default");   	        	

        	LocalDispatcher dispatcher = GenericDispatcher.getLocalDispatcher("UniqueName",delegator);
     	
        	List<GenericValue> allMonitors = MethodDB.getMethods(delegator);            	        	        	
        	int totalMonitor = allMonitors.size();
        	int count=1;
        	
        	System.out.println("=============== ��ʼװ�ؼ���� =====================");      
        	
        	List<List<Map<String, String>>> perScheduleJob = new ArrayList<List<Map<String, String>>>();
        	for(GenericValue tmpMonitor: allMonitors){
        		if(tmpMonitor == null) continue;
        		
        		//for test -- hailong.yi
        		if(!"1.27.11".equals(tmpMonitor.get("ci_id"))) continue;
        		//for test end
        		
        		// System.out.println("> ��ȡ�� " + count + " ������� <");
        		List<Map<String, String>> monitorParameters = MethodDB.getMethod(tmpMonitor, delegator);
        		
        		if(monitorParameters == null)
        			continue;
        		
        		if(count<5)
        		{
                	String key, value;
                	Object tmpObj;        			
	        		for(Map<String, String> perParameter: monitorParameters){
	        			Iterator<?> it = perParameter.keySet().iterator();
	        			while (it.hasNext()){
	                	    key = it.next().toString();
	                	    tmpObj = perParameter.get(key);
	                	    if( tmpObj== null)
	                	    	value = "";
	                	    else
	                	    	value = tmpObj.toString();            	                		
	                		System.out.println(key.toString()+"="+value);             		
	                	} 
	        		}        		
        		}        		
        		
        		for(Map<String, String> perParameter: monitorParameters){
            		String methodID = perParameter.get("method_id");
            		System.out.println(">>> ��Ӽ������" + methodID);
            		
            		//��Ӽ�������SiteScope��,(����Monitor�߳�)
            		MonitorDevice.addMonitor(perParameter, delegator);
            		
            		//��ʱ��ӵ�һ��
            		break;
            	}
        		
            	/* 
            	 * �ƻ�����
            	 * "sv_RunMonitor" ��Ӧ�� services.xml �ж���ķ���
             	 */    
        		if(totalMonitor > 200 ){
        			if(perScheduleJob.size()< (totalMonitor/200) ){
        				perScheduleJob.add(monitorParameters);
        			}
        			else{
        				dispatcher.schedule("sv_RunMonitor", UtilMisc.toMap("_Context", perScheduleJob), new Date().getTime() + 100, RecurrenceRule.SECONDLY, 20, -1 );
        				perScheduleJob.clear();
        			}        				
        		}
        		else{
        			perScheduleJob.add(monitorParameters);
        			dispatcher.schedule("sv_RunMonitor", UtilMisc.toMap("_Context", perScheduleJob), new Date().getTime() + 100, RecurrenceRule.SECONDLY, 20, -1 );
        			perScheduleJob.clear();
        		}
        		
	        	//dispatcher.schedule("sv_RunMonitor", UtilMisc.toMap("_Context", monitorParameters), new Date().getTime() + 100, RecurrenceRule.SECONDLY, 20, -1 );
	        	count++;
	            if(count>10) break;

	            //for test -- hailong.yi
        		break;
        		//for test end
        	}  
        	
    		if(totalMonitor > 200 && perScheduleJob.size()>0){
    				dispatcher.schedule("sv_RunMonitor", UtilMisc.toMap("_Context", perScheduleJob), new Date().getTime() + 100, RecurrenceRule.SECONDLY, 20, -1 );
    		}        				

        	count--;
        	System.out.println("=============== ��ϣ�װ�ؼ����: "+ count +" ��");            	
    }
    
    /*
     * ���м����
     */
    public static Map runMonitor(DispatchContext dctx, Map context) {
        try {
        	Map<String,Object> result = ServiceUtil.returnSuccess();
/*            String host =  null;
            List<Map<String, String>> monitorParameters=(List<Map<String, String>>) context.get("_Context");
        	for(Map<String, String> perParameter: monitorParameters){
        		String methodID =  perParameter.get("method_id");
    			host =  perParameter.get("_MachineName");
        		System.out.println("----->> run monitor " + methodID);
        		//MonitorDevice.addMonitor(perParameter, dctx.getDelegator());
        		break;
        	}        	
*/        	
//        	result.put("_MachineName", host);        	
        	result.put("_MachineName", "Unknown");        	
        	result.put("_result", "�ɹ�");	
        	
	        return result;
        } catch (Exception ex) {
            Debug.logError(ex, "Cannot run monitor", module);
            return ServiceUtil.returnError("Cannot run monitor: " + ex.getMessage());
        }        	
    }
    
    /*
     * ȡָ�������ģ��Ĳ���
     */
    public static Map<String, String> loadMonitorTemplateParameters(String monitorTemplateID)
    {
    	Map<String, String> tmpMonitor = new HashMap();
    	
    	return tmpMonitor;
    }
    
    /*
     * ȡָ��������Ĳ���
     */
    public static Map<String, String> loadMonitorParameters(String monitorID)
    {
    	Map<String, String> tmpMonitor = new HashMap();
    	
    	return tmpMonitor;
    }
    
    /*
     * ɾ��һ�������ģ��
     */
    public static boolean deleteMonitorTemplate(String monitorTemplateID)
    {
    	boolean result = false;
    	
    	return result;
    }
    
    /*
     * ɾ��һ�������
     * edit by hailong.yi
     */
    public static Map deleteMonitor(DispatchContext dctx, Map context)
    {
        try {
        	String MonitorID = (String)context.get("MonitorID");
        	MonitorDevice.deleteMonitor(MonitorID, dctx.getDelegator());
        	Map<String,Object> result = ServiceUtil.returnSuccess();
        	result.put("_result", "�ɹ�");	
	        return result;
        } catch (Exception ex) {
            Debug.logError(ex, "Cannot delete monitor", module);
            return ServiceUtil.returnError("Cannot delete monitor: " + ex.getMessage());
        }        	
     }
}
