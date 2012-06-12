package com.siteview.svecc.service;

import java.io.FileOutputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import jgl.Array;

import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.StringOutputStream;
import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;
import org.w3c.dom.Attr;
import org.w3c.dom.DOMImplementation;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

import com.dragonflow.Api.APIMonitor;
import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Page.CGI;
import com.dragonflow.Page.monitorPage;
import com.dragonflow.Properties.BooleanProperty;
import com.dragonflow.Properties.FrequencyProperty;
import com.dragonflow.Properties.ScalarProperty;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.AtomicMonitor;
import com.dragonflow.SiteViewException.SiteViewException;

public class MonitorEditProperties extends BaseClass{
	public static final String module = MonitorEditProperties.class.getName();

	public static Map<String,Object> getDefaultValue(AtomicMonitor atomicMonitor)
	{
		Array array = atomicMonitor.getProperties();
		Enumeration<?> enumeration = array.elements();
		Map<String, Object> map = new HashMap<String, Object>();
		while (enumeration.hasMoreElements()) {
			StringProperty stringproperty = (StringProperty)enumeration.nextElement();
			if (hasUnit(stringproperty))
			{
				map.put(getUnitName(stringproperty.getName()), ((FrequencyProperty)stringproperty).getCurUnit(stringproperty.getDefault()));
				int val = ((FrequencyProperty)stringproperty).getRealValueWithUnit(stringproperty.getDefault());
				map.put(stringproperty.getName(), val == 0 ? "" : val );
			}else{
				map.put(stringproperty.getName(), stringproperty.getDefault());
			}
		}
		return map;
	}
	public static Map<String,Object> getIsEditable(AtomicMonitor atomicMonitor,String operation)
	{
		Array array = atomicMonitor.getProperties();
		Enumeration<?> enumeration = array.elements();
		Map<String, Object> map = new HashMap<String, Object>();
		while (enumeration.hasMoreElements()) {
			StringProperty stringproperty = (StringProperty)enumeration.nextElement();
			map.put(stringproperty.getName(), stringproperty.isEditable);
		}
		return map;
	}
	public static Map<String,Object> getIsVisible(AtomicMonitor atomicMonitor,String operation)
	{
		Array array = atomicMonitor.getProperties();
		Enumeration<?> enumeration = array.elements();
		Map<String, Object> map = new HashMap<String, Object>();
		while (enumeration.hasMoreElements()) {
			StringProperty stringproperty = (StringProperty)enumeration.nextElement();
			map.put(stringproperty.getName(), stringproperty.isEditable);
		}
		return map;
	}
	public static Map<String,Object> getLabel(AtomicMonitor atomicMonitor)
	{
		Array array = atomicMonitor.getProperties();
		Enumeration<?> enumeration = array.elements();
		Map<String, Object> map = new HashMap<String, Object>();
		while (enumeration.hasMoreElements()) {
			StringProperty stringproperty = (StringProperty)enumeration.nextElement();
			map.put(stringproperty.getName(), stringproperty.getLabel());
		}
		return map;
	}
	public static Map<String,Object> getDescription(AtomicMonitor atomicMonitor)
	{
		Array array = atomicMonitor.getProperties();
		Enumeration<?> enumeration = array.elements();
		Map<String, Object> map = new HashMap<String, Object>();
		while (enumeration.hasMoreElements()) {
			StringProperty stringproperty = (StringProperty)enumeration.nextElement();
			map.put(stringproperty.getName(), stringproperty.getDescription());
		}
		return map;
	}
	public static Map<?, ?> getMonitorFormsString(DispatchContext ctx, Map<?, ?> context) {
		try {
			String className = (String) getNotOptionalValue(context,"className");
			String groupId = (String) getOptionalValue(context,"groupId");
			String id = (String) getOptionalValue(context,"id");
			
			Map<?, ?> retmap = ctx.getDispatcher().runSync("getMonitorFormsDocument",UtilMisc.toMap("className",className,"groupId",groupId,"id",id)); 
			
			Document doc = (Document) retmap.get("result");
			OutputStream os = new StringOutputStream();
			output(doc,os);
			String result = os.toString();
			os.close();
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", result);
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getMonitorFormsString: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}

	
	public static Map<?, ?> getMonitorFormsDocument(DispatchContext ctx, Map<?, ?> context) {
		try {
			String className = (String) getNotOptionalValue(context,"className");
			String groupId = (String) getOptionalValue(context,"groupId");
			String id = (String) getOptionalValue(context,"id");
			Document doc = getDocument(className,groupId,id);
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", doc);
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getMonitorFormsDocument: " + e.toString());
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
	
	
	private static Document getDocument(String className,String groupId,String id) throws Exception {
		
		Map<?,?> groupMaps = getDispatcher().runSync("getGroupByParentId", UtilMisc.toMap("parentId",groupId));
		Map<?,?> monitorMaps = getDispatcher().runSync("getMonitorByGroupId", UtilMisc.toMap("groupId",groupId));
		
		List<Map<String, Object>> subGrouplist = (List<Map<String, Object>>) groupMaps.get("result");
		List<Map<String, Object>> subMonitorList = (List<Map<String, Object>>) monitorMaps.get("result");
		
		List<Map<String, Object>> sublist = new ArrayList<Map<String, Object>>();
		sublist.addAll(subGrouplist);
		sublist.addAll(subMonitorList);
		
		DOMImplementation domImpl = getDOMImplementation();
		Document document = domImpl.createDocument("", getRootName(), null);
		Element root = getRoot(document);
		
		Element child = document.createElement("form");

		//Form属性
		child.setAttribute("name", "Monitor");
		child.setAttribute("type", "single");
		child.setAttribute("target", id == null ? "addMonitor" : "updateMonitor");
		child.setAttribute("header-row-style", "header-row");
		child.setAttribute("default-table-style", "basic-table");
		child.setAttribute("default-map-name", "retmap.result");
		child.setAttribute("default-table-style", "basic-table");
		child.setAttribute("default-table-style", "basic-table");

		Element actionsField = document.createElement("actions");
		
		Element serviceField = document.createElement("service");
		serviceField.setAttribute("service-name", "getMonitorEditProperties");
		serviceField.setAttribute("result-map-name", "retmap");
		
		Element fieldmapField = document.createElement("field-map");
		fieldmapField.setAttribute("field-name", "className");
		fieldmapField.setAttribute("env-name", "className");
		serviceField.appendChild(fieldmapField);

		fieldmapField = document.createElement("field-map");
		fieldmapField.setAttribute("field-name", "groupId");
		fieldmapField.setAttribute("value", groupId);
		serviceField.appendChild(fieldmapField);
		
		fieldmapField = document.createElement("field-map");
		fieldmapField.setAttribute("field-name", "id");
		fieldmapField.setAttribute("value", id);
		serviceField.appendChild(fieldmapField);

		actionsField.appendChild(serviceField);
		
		child.appendChild(actionsField);
		
		
		AtomicMonitor atomicMonitor = APIMonitor.instantiateMonitor(className);
		String s18 = atomicMonitor.getProperty("_URLEncoding");
		int i =0;
		Map<String, StringProperty> map = getStringProperties(atomicMonitor,i);
		
		//title字段
		Element classNameField = document.createElement("field");
		classNameField.setAttribute("name", "className");
		classNameField.setAttribute("map-name", "parameters");
		Element classNameFieldContent = document.createElement("hidden");
		classNameField.appendChild(classNameFieldContent);
		child.appendChild(classNameField);

		Element groupIdField = document.createElement("field");
		groupIdField.setAttribute("name", "groupId");
		groupIdField.setAttribute("map-name", "parameters");
		Element groupIdFieldContent = document.createElement("hidden");
		groupIdField.appendChild(groupIdFieldContent);
		child.appendChild(groupIdField);

		
		//--------------------------
		if (id!=null){
			Element idField = document.createElement("field");
			idField.setAttribute("name", "id");
			idField.setAttribute("map-name", "parameters");
			Element idFieldContent = document.createElement("hidden");
			idField.appendChild(idFieldContent);
			child.appendChild(idField);
		}
		//------------------------
		
		Element titleField = document.createElement("field");
		titleField.setAttribute("name", "monitorType");
		titleField.setAttribute("title","Monitor Type");
		Element titleFieldContent = document.createElement("display");
		titleFieldContent.setAttribute("description", getProperty(atomicMonitor, "title"));
		titleField.appendChild(titleFieldContent);
		child.appendChild(titleField);
		
		
		Element field = null;
		Element content = null;
		for (String key : map.keySet())
		{
			StringProperty stringproperty = map.get(key);
			if (stringproperty == null) continue;
            if(s18 != null && s18.length() > 0)
            {
                stringproperty.setEncoding(s18);
            }
            
            //基本的属性放前面
			if(stringproperty.isEditable && !stringproperty.isAdvanced)
			{
				if(!stringproperty.isVariableCountProperty() || stringproperty.shouldPrintVariableCountProperty(i))
				{
					field = document.createElement("field");
					field.setAttribute("name", stringproperty.getName());
					field.setAttribute("title", stringproperty.getLabel());
					field.appendChild(getInputField(document,atomicMonitor,stringproperty));
					if (hasUnit(stringproperty)){
						field.setAttribute("position", "1");
						child.appendChild(field);

						Element newfield = document.createElement("field");
						newfield.setAttribute("title", "");
						newfield.setAttribute("name", getUnitName(stringproperty.getName()));
						newfield.setAttribute("tooltip", stringproperty.getDescription());
						newfield.appendChild(getUnits(document,(FrequencyProperty)stringproperty));
						newfield.setAttribute("position", "2");
						child.appendChild(newfield);
					} else {
						field.setAttribute("tooltip", stringproperty.getDescription());
						child.appendChild(field);
					}
				}
			} else  if(stringproperty.isMultiLine && !stringproperty.isEditable){
				field = document.createElement("field");
				field.setAttribute("name", stringproperty.getName());
				field.setAttribute("title", stringproperty.getLabel());
				field.setAttribute("tooltip", stringproperty.getDescription());
				content = document.createElement("display");
				field.appendChild(content);
				child.appendChild(field);
			}
		}

		//ADD按钮
		field = document.createElement("field");
		field.setAttribute("name", "submitButton");
		field.setAttribute("title", "${uiLabelMap.eccAdd}");
		field.setAttribute("widget-style", "buttontext");
		content = document.createElement("submit");
		content.setAttribute("button-type", "button");
		field.appendChild(content);
		field.setAttribute("position", "1");
		child.appendChild(field);
		
		//cancel按钮
		field = document.createElement("field");
		field.setAttribute("name", "cancelButton");
		field.setAttribute("title", "");
		field.setAttribute("widget-style", "buttontext");
		content = document.createElement("hyperlink");
		content.setAttribute("target", "listMonitor?groupId=${groupId}");
		content.setAttribute("description", "${uiLabelMap.eccCancel}");
		content.setAttribute("also-hidden", "false");
		field.appendChild(content);
		field.setAttribute("position", "2");
		child.appendChild(field);
		
		//扩展属性
		for (String key : map.keySet())
		{
			StringProperty stringproperty = map.get(key);
			if (stringproperty == null) continue;
			
			if(stringproperty.isEditable && stringproperty.isAdvanced && (!stringproperty.isVariableCountProperty() || stringproperty.shouldPrintVariableCountProperty(i)))
			{
	 			field = document.createElement("field");
				field.setAttribute("name", stringproperty.getName());
				field.setAttribute("title", stringproperty.getLabel());
				//field.setAttribute("tooltip", stringproperty.getDescription());
				field.appendChild(getInputField(document,atomicMonitor,stringproperty));
				if (hasUnit(stringproperty)){
					field.setAttribute("position", "1");
					child.appendChild(field);

					Element newfield = document.createElement("field");
					newfield.setAttribute("title", "");
					newfield.setAttribute("name", getUnitName(stringproperty.getName()));
					newfield.setAttribute("tooltip", stringproperty.getDescription());
					newfield.appendChild(getUnits(document,(FrequencyProperty)stringproperty));
					newfield.setAttribute("position", "2");
					child.appendChild(newfield);
				} else {
					field.setAttribute("tooltip", stringproperty.getDescription());
					child.appendChild(field);
				}
			}
		}
		
		
		//child.appendChild(getOrdering(document,atomicMonitor,sublist));
		
		root.appendChild(child);
		
		return document;
		
	}
	public static Boolean hasUnit(StringProperty stringproperty)
	{
		
		if (stringproperty instanceof FrequencyProperty)
		{
			return true;
		}
		return false;
	}
	
	public static Element getUnits(Document document,FrequencyProperty frequencyProperty)
	{
		Element content = document.createElement("drop-down");
		content.setAttribute("allow-empty", "false");
		Map<String,Integer> unitsmap = frequencyProperty.getListOption();
		for (String val : unitsmap.keySet())
		{
			Element child = document.createElement("option");
			child.setAttribute("key", val);
			child.setAttribute("description", val);
			content.appendChild(child);
		}
		return content;
	}
	
	public static String getUnitName(String name)
	{
		return name + "_Units";
	}
	
	public static Element getOrdering(Document document,AtomicMonitor atomicMonitor,List<Map<String, Object>> subgroupList)
	{
		String id = atomicMonitor.getProperty(com.dragonflow.SiteView.Monitor.pID);
		
		Element field = document.createElement("field");
		field.setAttribute("title", "<B>List Order</B>");
		field.setAttribute("name", "ordering");
		field.setAttribute("tooltip", "choose where this monitor appears in the list of monitors on the Monitor Detail page");

		Element content = document.createElement("drop-down");
		content.setAttribute("allow-empty", "false");

		Element child = document.createElement("option");
		child.setAttribute("key", "0");
		child.setAttribute("description", "first");
		content.appendChild(child);
		
		for (Map<String, Object> val : subgroupList)
		{
			if (val.get("_class")==null)continue;
			String curid = (String)val.get("_id");
			String curname = (String)val.get("_name");
			
			child = document.createElement("option");
			if (id.equals(curid)){
				
			}
			
			child.setAttribute("key", "" + subgroupList.indexOf(val));
			child.setAttribute("description", " before " + curname);
			content.appendChild(child);
		}

		child = document.createElement("option");
		child.setAttribute("key", "" + subgroupList.size());
		child.setAttribute("description", "last");
		content.appendChild(child);
		
		field.appendChild(content);
		return field;
	}
	
	private static Element getInputField(Document document,AtomicMonitor atomicMonitor,StringProperty stringproperty)
	{
		Element content = null;
		if (stringproperty instanceof BooleanProperty)
		{
			content = document.createElement("check");
		}else if (stringproperty instanceof ScalarProperty){
			Vector<String> vector = null;
			try {
				CGI cgi = new monitorPage();
				cgi.initialize(new HTTPRequest(), null);
				vector = atomicMonitor.getScalarValues((ScalarProperty)stringproperty,null,cgi);
			} catch (SiteViewException e) {
			}
			content = document.createElement("drop-down");
			content.setAttribute("allow-empty", "false");
			Enumeration<String> enumeration = vector.elements();
			while(enumeration.hasMoreElements()){
				String key = enumeration.nextElement();
				Element child = document.createElement("option");
				child.setAttribute("key", key);
				String val = enumeration.nextElement();
				child.setAttribute("description", val);
				content.appendChild(child);
			}
		} else if (stringproperty.isMultiLine){
			content = document.createElement("textarea");
			content.setAttribute("rows", "5");
			content.setAttribute("cols", "60");
		} else if (stringproperty.isPassword){
			content = document.createElement("password");
		} else {
			content = document.createElement("text");
		}
		return content;
	}
	
	public static void main(String args[]) throws Exception {
		output(getDocument("","",""),new FileOutputStream("c:\\a.xml"));
	}

	private static void output(Document doc,OutputStream os) throws Exception {
		TransformerFactory tf = TransformerFactory.newInstance();
	    Transformer transformer = tf.newTransformer();

	    DOMSource source = new DOMSource(doc);
	    StreamResult result = new StreamResult(os);  
	    transformer.transform(source, result);
	    os.flush();
	}
	
	private static DOMImplementation getDOMImplementation() throws Exception {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder = factory.newDocumentBuilder();
		DOMImplementation domImpl = builder.getDOMImplementation();
		return domImpl;
	}
	private static String getRootName() {
		return "forms";
	}
	private static Element getRoot(Document doc) throws Exception {
		Element root = doc.getDocumentElement();
		Attr rootattr1 = doc.createAttribute("xmlns:xsi");
		rootattr1.setValue(getXmlnsXsi());
		root.setAttributeNode(rootattr1);
		Attr rootattr2 = doc.createAttribute("xsi:noNamespaceSchemaLocation");
		rootattr2.setValue(getXsiNoNamespaceSchemaLocation());
		root.setAttributeNode(rootattr2);
		return root;
	}
	private static String getXsiNoNamespaceSchemaLocation() {
		return XSI_NONAMESPACESCHEMALOCATION;
	}
	private static String getXmlnsXsi() {
		return XMLNS_XSI;
	}
	
	private static final String XMLNS_XSI = "http://www.w3.org/2001/XMLSchema-instance";
	private static final String XSI_NONAMESPACESCHEMALOCATION = "http://ofbiz.apache.org/dtds/widget-form.xsd";
	
}
