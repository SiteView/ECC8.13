package com.siteview.ecc.testcase;

import java.net.URL;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.xml.namespace.QName;
import javax.xml.rpc.ParameterMode;

import org.apache.axis.Constants;
import org.apache.axis.client.Call;
import org.apache.axis.client.Service;

public class TestGroup {

	public static void main(String argv[]) {
		try {
			String newid=testSubmitSVSE();
			testGetSVSE(newid);
			testGetSVSEMany();
			testDeleteSVSE(newid);
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
    
	public static String testSubmitSVSE() throws Exception {
		String url = "http://192.168.6.51:8181/webtools/control/SOAPService/sv_submitSVSE";

		Call call = (Call) new Service().createCall();
		call.setProperty("", "");

		call.setTargetEndpointAddress(new URL(url));
		call.setOperationName(new QName("sv_submitSVSE", "sv_submitSVSE"));
		//call.addParameter("dependon", Constants.XSD_STRING,
		//ParameterMode.IN);
		//call.addParameter("dependon_status", Constants.XSD_STRING,
		// ParameterMode.IN);
		call.addParameter("disabled", Constants.XSD_STRING, ParameterMode.IN);
		// call.addParameter("group_id", Constants.XSD_STRING,
		// ParameterMode.IN);
		call.addParameter("group_name", Constants.XSD_STRING, ParameterMode.IN);
		// call.addParameter("grp_type", Constants.XSD_STRING,
		// ParameterMode.IN);
		// call.addParameter("has_son", Constants.XSD_STRING, ParameterMode.IN);
		// call.addParameter("parent_group_id", Constants.XSD_STRING,
		// ParameterMode.IN);
		// call.addParameter("status_type_id", Constants.XSD_STRING,
		// ParameterMode.IN);
		call.addParameter("sv_description", Constants.XSD_STRING,	ParameterMode.IN);
		//call.addParameter("sv_index", Constants.XSD_STRING,ParameterMode.IN);

		call.setReturnType(Constants.XSD_ANY);
		Object result = call.invoke(new Object[] {"F","testSvSE","我测试SVSE得提交"});
		Map out = call.getOutputParams();

		Object errorMessage=out.get(new QName("","errorMessage"));
		if(errorMessage!=null)
			System.out.println(errorMessage.toString());
		
		Object errorMessageList = (Object) out.get(new QName("","errorMessageList"));
		String msg1 = null;
		
		if (errorMessageList instanceof Object[]) 
		{
			for (int i = 0; i < ((Object[]) errorMessageList).length; i++) {
				msg1 = (((Object[]) errorMessageList)[i]).toString();
				System.out.println(msg1);
			}

		}
		Object successMessage=out.get(new QName("","successMessage"));
		if(successMessage!=null)
			System.out.println(successMessage.toString());
		return result.toString();

	}
	public static void testGetSVSE(String newid) throws Exception 
	{
		String url = "http://192.168.6.51:8181/webtools/control/SOAPService/sv_getSVSE";

		Call call = (Call) new Service().createCall();
		call.setProperty("", "");

		call.setTargetEndpointAddress(new URL(url));
		call.setOperationName(new QName("sv_getSVSE", "sv_getSVSE"));
		call.addParameter("group_id", Constants.XSD_STRING,
		  ParameterMode.IN);

		call.setReturnType(Constants.XSD_ANY);
		Object result = call.invoke(new Object[] {newid});
		Map out = call.getOutputParams();

		Object errorMessage=out.get(new QName("","errorMessage"));
		if(errorMessage!=null)
			System.out.println(errorMessage.toString());
		
		Object errorMessageList = (Object) out.get(new QName("",
				"errorMessageList"));
		String msg1 = null;
		if (errorMessageList instanceof Object[]) {
			for (int i = 0; i < ((Object[]) errorMessageList).length; i++) {
				msg1 = (((Object[]) errorMessageList)[i]).toString();

				System.out.println(msg1);
			}

		}
		Object successMessage=out.get(new QName("","successMessage"));
		if(successMessage!=null)
			System.out.println(successMessage.toString());

		/*System.out.println("group_id="+out.get(new QName("","group_id")));
		System.out.println("disabled="+out.get(new QName("","disabled")));
		System.out.println("group_name="+out.get(new QName("","group_name")));
		System.out.println("sv_description="+out.get(new QName("","sv_description")));
		System.out.println("has_son="+out.get(new QName("","has_son")));
		*/
		
		Iterator iterator=out.keySet().iterator();
		while(iterator.hasNext())
		{
			Object key=iterator.next();
			Object value=out.get(key);
			System.out.println(key+"="+value);
		}
	}
	public static void testGetSVSEMany() throws Exception 
	{
		String url = "http://192.168.6.51:8181/webtools/control/SOAPService/sv_getSVSEMany";

		Call call = (Call) new Service().createCall();
		call.setProperty("", "");

		call.setTargetEndpointAddress(new URL(url));
		call.setOperationName(new QName("sv_getSVSEMany", "sv_getSVSEMany"));
		//call.addParameter("group_id", Constants.XSD_STRING, ParameterMode.IN);

		call.setReturnType(Constants.XSD_ANY);
		//Object result = call.invoke(new Object[] {"10113"});
		Object result = call.invoke(new Object[] {});
		
		
		
		
		Map out = call.getOutputParams();
		System.out.print(out.toString());
		
		Object errorMessage=out.get(new QName("","errorMessage"));
		if(errorMessage!=null)
			System.out.println(errorMessage.toString());
		
		Object errorMessageList = (Object) out.get(new QName("",
				"errorMessageList"));
		String msg1 = null;
		if (errorMessageList instanceof Object[]) {
			for (int i = 0; i < ((Object[]) errorMessageList).length; i++) {
				msg1 = (((Object[]) errorMessageList)[i]).toString();

				System.out.println(msg1);
			}

		}
		Object successMessage=out.get(new QName("","successMessage"));
		if(successMessage!=null)
			System.out.println(successMessage.toString());

		/*System.out.println("group_id="+out.get(new QName("","group_id")));
		System.out.println("disabled="+out.get(new QName("","disabled")));
		System.out.println("group_name="+out.get(new QName("","group_name")));
		System.out.println("sv_description="+out.get(new QName("","sv_description")));
		System.out.println("has_son="+out.get(new QName("","has_son")));
		*/
		
		Iterator iterator=out.keySet().iterator();
		while(iterator.hasNext())
		{
			Object key=iterator.next();
			Object value=out.get(key);
			System.out.println(key+"="+value);
		}
		
		if(result instanceof Object[])
		{	
			for(int i=0;i<((Object[])result).length;i++)
			{
				Map map=(Map)(((Object[])result)[i]);
				System.out.println("group_name="+map.get("group_name"));
				System.out.println("sub_monitor_null_sum="+map.get("sub_monitor_null_sum"));
				System.out.println("group_id="+map.get("group_id"));
				System.out.println("sub_entity_sum="+map.get("sub_entity_sum"));
				System.out.println("sub_monitor_sum="+map.get("sub_monitor_sum"));
				System.out.println("status_type_id="+map.get("status_type_id"));
				System.out.println("grp_type="+map.get("grp_type"));
				System.out.println("disabled="+map.get("disabled"));
				System.out.println("has_son="+map.get("has_son"));
			}
		}
	}
	
	public static void testDeleteSVSE(String newid) throws Exception {
		String url = "http://192.168.6.51:8181/webtools/control/SOAPService/sv_deleteSVSE";

		Call call = (Call) new Service().createCall();
		call.setProperty("", "");

		call.setTargetEndpointAddress(new URL(url));
		call.setOperationName(new QName("sv_deleteSVSE", "sv_deleteSVSE"));
		
		 call.addParameter("group_id", Constants.XSD_STRING,
		 ParameterMode.IN);

		call.setReturnType(Constants.XSD_ANY);
		Object result = call.invoke(new Object[] {newid});
		Map out = call.getOutputParams();

		Object errorMessage=out.get(new QName("","errorMessage"));
		if(errorMessage!=null)
			System.out.println(errorMessage.toString());
		
		Object errorMessageList = (Object) out.get(new QName("","errorMessageList"));
		String msg1 = null;
		if (errorMessageList instanceof Object[]) {
			for (int i = 0; i < ((Object[]) errorMessageList).length; i++) {
				msg1 = (((Object[]) errorMessageList)[i]).toString();

				System.out.println(msg1);
			}

		}
		Object successMessage=out.get(new QName("","successMessage"));
		if(successMessage!=null)
			System.out.println(successMessage.toString());


	}
}
