package com.siteview.ecc.service;

import java.io.StringReader;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import jgl.Array;

import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.collections.MapStack;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericEntityException;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;
import org.w3c.dom.Document;
import org.xml.sax.InputSource;

import com.dragonflow.Api.APIGroup;
import com.dragonflow.Api.APIMonitor;
import com.dragonflow.Api.SSInstanceProperty;
import com.dragonflow.Page.monitorPage;
import com.dragonflow.Properties.NumericProperty;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.AtomicMonitor;
import com.dragonflow.Utils.EmsDummyMonitor;
import com.siteview.ecc.drive.MonitorDevice;

public class Monitor {
	public static final String module = Group.class.getName();
	
	public static final String MONITOR_KEY = "monitorId";
	
	public static List<AtomicMonitor> getMonitorByGroupId(String id) throws Exception
	{
		APIMonitor api = new APIMonitor();
		Collection<AtomicMonitor> monitors = null;
		if (id == null){
			monitors = api.getAllMonitors();
		} else {
			monitors = api.getChildMonitors(id);
		}
		Iterator iterator = monitors.iterator();
		
		List<AtomicMonitor> retlist = new ArrayList<AtomicMonitor>();
		
		while(iterator.hasNext())
		{
			AtomicMonitor monitor = (AtomicMonitor) iterator.next();
			try{
				if (monitor.isScheduleEnabled())
					retlist.add(monitor);
			}catch(Exception e){}
		}
		//updateExportMonitorInfor();
		return retlist;
	}
	
	public static Boolean haveMonitor(String groupid) throws Exception {
		if (groupid == null)
			return false;
		APIMonitor api = new APIMonitor();
		Collection<Monitor> monitors = api.getChildMonitors(groupid);
		Iterator iterator = monitors.iterator();

		while (iterator.hasNext()) {
			return true;
		}
		return false;
	}
	
	
	public static AtomicMonitor getMonitor(String id) throws Exception
	{
		if (id==null) return null;
		APIMonitor api = new APIMonitor();
		
		Collection<Monitor> monitors = api.getAllMonitors();
		Iterator iterator = monitors.iterator();
		
		while(iterator.hasNext())
		{
			AtomicMonitor monitor = (AtomicMonitor) iterator.next();
			if (id.equals(monitor.getProperty(AtomicMonitor.pID)))
			{
				return monitor;
			}
		}
		return null;
	}	
    /*
     * 删除一个监测器
     * edit by hailong.yi
     */
    public static Map deleteMonitor(DispatchContext dctx, Map context)
    {
        try {
        	String monitorId = (String)context.get("monitorId");
        	String groupId = (String)context.get("groupId");
        	MonitorDevice.deleteMonitor(monitorId,groupId, dctx.getDelegator());
        	Map<String,Object> result = ServiceUtil.returnSuccess();
	        return result;
        } catch (Exception ex) {
            Debug.logError(ex, "Cannot delete monitor", module);
            return ServiceUtil.returnError("Cannot delete monitor: " + ex.getMessage());
        }        	
     }

    /*
     * 取能实现的监测器类
     * create by hailong.yi
     */
	private static List<AtomicMonitor> monitorClasses = null;
	
	public static List<AtomicMonitor> getMonitorClass() throws Exception
	{
		if (monitorClasses == null){
			List<AtomicMonitor> monitors = new ArrayList<AtomicMonitor>();
			for (String className : getMonitorClassNames()) {
				try{
					AtomicMonitor instance = APIMonitor.instantiateMonitor(className.replace("com.dragonflow.StandardMonitor.", ""));
					if (instance == null) continue;
					monitors.add(instance);
				}catch (Exception e){
					
				}
			}
			monitorClasses = monitors;
		}
		return monitorClasses;
	}

    public static List<String> getMonitorClassNames() throws Exception
	{
		return getMonitorClassNames(GenericDelegator.getGenericDelegator("default"));
	}

	private static List<String> monitorClasseNames = null;
	public static List<String> getMonitorClassNames(GenericDelegator delegator)
			throws Exception {
		if (monitorClasseNames==null){
			List<GenericValue> vals = delegator.findList("SvMonitorType", null, null,
					null, null, false);
			List<String> monitors = new ArrayList<String>();
			for (GenericValue val : vals) {
				String className = val.getString("className");
				if (className == null)continue;
				monitors.add(className);
			}
			monitorClasseNames = monitors;
		}
		return monitorClasseNames;
	}
	
	
	public static String getProperty(AtomicMonitor atomicMonitor,String key)
	{
		Object object = atomicMonitor.getClassPropertyByObject(atomicMonitor.getClass().getName(),key);
		System.out.println(key + "=" + object);
		if (object instanceof String ) return object == null ? "" : ("" + object);
		return "";
	}
	private static void setPropertyValue(StringProperty stringProperty,String className)
	{
		try {
			GenericDelegator genericdelegator = GenericDelegator.getGenericDelegator("default");
			GenericValue val = genericdelegator.makeValue("SvMonitorAttr");
			val.set("className", className);
			val.set("attrName", "" + stringProperty);
			val.set("label", stringProperty.getLabel());
			val.set("description", stringProperty.getDescription());

			
			if (stringProperty instanceof  NumericProperty){
				NumericProperty numericProperty = (NumericProperty)stringProperty;
				val.set("unit", numericProperty.getUnits());
			}

			val.create();
		} catch (GenericEntityException e) {
			e.printStackTrace();
		}
	}
	
	private static String[] classnames = {
	};
	
	private static boolean existin(String str)
	{
		if (str == null) return false;
		for (String classname : classnames)
		{
			if (str.equals(classname)) return true;
		}
		return false;
	}
	
	public static void updateExportMonitorInfor() throws Exception
	{
		GenericDelegator delegator = GenericDelegator.getGenericDelegator("default");
		List<GenericValue> vals = delegator.findList("SvMonitorType", null, null,
				null, null, false);
		for (GenericValue val : vals) {
			try {
				//if (vals.indexOf(val) <= 100) continue;
				String className = val.getString("className");
				if (className == null) continue;
				//if (!existin(className)) continue;
				if (!className.startsWith("com.dragonflow.SiteView.")) continue;
				AtomicMonitor instance = getAtomicMonitor(className);
				if (instance == null) continue;
				updateExportMonitorInfor(instance,val,className);
				//if (vals.indexOf(val) > 99)break;
			} catch (Exception e) {
			}
		}
	}
	
	private static List<String> getCommAttribute() throws Exception
	{
		Class classz = Class.forName(EmsDummyMonitor.class.getName());
		AtomicMonitor atomicMonitor = (AtomicMonitor)classz.newInstance();
		Array properties = atomicMonitor.getProperties();
		Enumeration enumeration = properties.elements();
		List<String> retlist = new ArrayList<String>();
		while(enumeration.hasMoreElements())
		{
			Object object = enumeration.nextElement();
			retlist.add("" + object);
		}
		return retlist;
	}
	public static void setCommAttribute() throws Exception{
		GenericDelegator genericdelegator = GenericDelegator.getGenericDelegator("default");
		   for (String attr : getCommAttribute())
		   {
				try {
					
					GenericValue val = genericdelegator.makeValue("SvMonitorCommonAttr");
					val.set("attrName", attr);

					val.create();
				} catch (GenericEntityException e) {
					e.printStackTrace();
				}
		   }
	}
		   
	private static AtomicMonitor getAtomicMonitor(String className) throws Exception
	{
		if (className==null) return null;
		for (String atomicmonitor : getMonitorClassNames())
		{
			if (className.equals(atomicmonitor)) {
				try {
					Class classz = Class.forName(atomicmonitor);
					return (AtomicMonitor)classz.newInstance();
				} catch (Exception e) {
					return null;
				}
			}
		}
		return null;
	}
	
	public static void updateExportMonitorInfor(AtomicMonitor atomicMonitor,GenericValue val,String className)
	{
		try {
			val.set("description", getProperty(atomicMonitor,"description"));
			val.set("title", getProperty(atomicMonitor,"title"));
			val.set("target", getProperty(atomicMonitor,"target"));
			val.set("toolName", getProperty(atomicMonitor,"toolName"));
			val.set("toolDescription", getProperty(atomicMonitor,"toolDescription"));
			val.set("topazName", getProperty(atomicMonitor,"topazName"));
			val.set("topazType", getProperty(atomicMonitor,"topazType"));
			val.set("classType", getProperty(atomicMonitor,"classType"));
			val.set("applicationType", getProperty(atomicMonitor,"applicationType"));
			val.store();
		} catch (GenericEntityException e) {
			e.printStackTrace();
		}
		//if (true)return ;
		Array properties = atomicMonitor.getProperties();
		Enumeration enumeration = properties.elements();
		while(enumeration.hasMoreElements())
		{
			Object object = enumeration.nextElement();
			if (object instanceof StringProperty)
			{
				StringProperty stringProperty = (StringProperty) object;
				setPropertyValue(stringProperty,className);
			}
			
		}
	}
	
	public static Map<?, ?> addMonitor(DispatchContext ctx, Map<?, ?> context) {
		try {
			setCommAttribute();
			
			String groupId = (String) context.get("groupId");
			String className = (String) context.get("className");
			className = className.replace("com.dragonflow.StandardMonitor.", "");
			String name = (String) context.get("_name");
			String hostname = (String) context.get("_hostname");
			String frequency = (String) context.get("_frequency");
			String frequencyUnit = (String) context.get("_frequencyUnit");

			APIMonitor api = new APIMonitor();
			List<SSInstanceProperty> properties = new ArrayList<SSInstanceProperty>();
			
			properties.add(new SSInstanceProperty("_frequency",frequency));
			properties.add(new SSInstanceProperty("_hostname",hostname));
			properties.add(new SSInstanceProperty("_name",name));
			
			api.create(className, groupId, properties.toArray(new SSInstanceProperty[0]));

			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			return ServiceUtil.returnError("Error addMonitor: "
					+ e.toString());
		}
	}
	
	public static Document getDocument(MapStack<?> context) throws Exception {
		if (context==null) return null;
		String monitorId = (String) context.get(MONITOR_KEY);
		AtomicMonitor atomicMonitor = null;
		if (monitorId!=null) {
			atomicMonitor = getMonitor(monitorId);
		}
		if (atomicMonitor==null) {
			String className = (String)context.get("className");
			if (className==null) return null;
			className = className.replace("", "");
			String groupId = (String)context.get("groupId");
			if (groupId==null) return null;
			Class<?> classz = Class.forName(className);
			atomicMonitor =  (AtomicMonitor) classz.newInstance();
		}
		String s18 = atomicMonitor.getProperty("_URLEncoding");
		Array array = atomicMonitor.getProperties();
		int i = new monitorPage().calculateVariablePropertyCount(array, atomicMonitor);
		
		Enumeration enumeration = array.elements();
		StringBuffer buff = new StringBuffer();
		while(enumeration.hasMoreElements())
		{
            StringProperty stringproperty = (StringProperty)enumeration.nextElement();
            if(s18 != null && s18.length() > 0)
            {
                stringproperty.setEncoding(s18);
            }
            if(stringproperty.isEditable && !stringproperty.isAdvanced)
            {
            	if(!stringproperty.isVariableCountProperty() || stringproperty.shouldPrintVariableCountProperty(i))
            	{
            		buff.append(stringproperty.getPrivateForOfbizForm());
            	}
            }else  if(stringproperty.isMultiLine && !stringproperty.isEditable){
            	
            }
		}
		
		enumeration = array.elements();
		while(enumeration.hasMoreElements())
		{
            StringProperty stringproperty = (StringProperty)enumeration.nextElement();
            if(stringproperty.isEditable && stringproperty.isAdvanced && (!stringproperty.isVariableCountProperty() || stringproperty.shouldPrintVariableCountProperty(i)))
            {
        		buff.append(stringproperty.getPrivateForOfbizForm());
            }
		}
		String outtext = buff.toString();
		StringReader reader = new StringReader(outtext);
		InputSource source = new InputSource(reader);
		DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
		DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
		return (documentBuilder.parse(source));
	}

}
