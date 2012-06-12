package com.siteview.jsvapi;

import java.util.HashMap;
import java.util.Scanner;
import java.util.Vector;

//import com.siteview.jsvapi.*;

//  测试结果1： 获取国际化资源的 3600个值(数据长度 143k bytes), 从 dll 缓存中获取,用时 120 ms 。 
//         			如果从 svdb 远程首次获取，需增加 700 ms 。 
//  				如果c++端不转为 utf8 编码，降低 66 ms ，提速 55% 。 
//  				如果不把 swig 的 map ,转为 java 标准 map, 降低 20 ms ,提速 16% 。 
//  		    (java 端 cache ,解决了模板数据的问题, 其他的？)

public class testJsvapi
{
	public static void main(String[] args)
	{
		Jsvapi svapi = new Jsvapi();
		String temp = new String("temp");
		 test2(svapi, temp, true);
//		 test2(svapi, temp, true);
		 
		while (temp.compareToIgnoreCase("q") != 0)
		{
			long start = System.currentTimeMillis();
			try
			{		
//				 String qname = test36(svapi, temp, true);
//				 System.out.println("queue name: \"" + qname + "\"");
//				 while (test39(svapi, qname, true))
//				 {
//				 System.out.println("RefreshData...");
//				 }
//				 test76(svapi, temp, true);
				
//				for (int i = 1; i <= 100; ++i)
//					test9(svapi, temp, false);
				
//				 for (Integer i = 1; i <= 1; ++i)
//					test8(svapi, i.toString(), false);
				
//				 test28(svapi, temp, true);
				
				// test31(svapi, test30(svapi, temp, true), true);
//				 test31(svapi, "G7NNcONzG1PKQzcLKN1PJOzKceJNIJIz", true);
				
				
				test76(svapi, temp, true);
				
			} catch (Exception e)
			{
				System.out.println("\n\n");
				e.printStackTrace();
			}
			System.out.println("\n run: " + (float) (System.currentTimeMillis() - start) / 1000 + " s");
			System.out.println("press enter key to continue, q + enter to quit.");
			Scanner in = new Scanner(System.in);
			try
			{
				temp = in.nextLine();
			} catch (Exception e)
			{
				System.exit(1);
			}
		}
	}
	
	public static void test1(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "SetSvdbAddrByFile");
		ndata.put("filename", "svapi.ini");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test2(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetSvdbAddr");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test4(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetGroup");
		ndata.put("id", "1.1");
		ndata.put("sv_depends", "true");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test5(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetEntity");
		ndata.put("id", "1.4");
		ndata.put("sv_depends", "true");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test6(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetMonitor");
		ndata.put("id", "1.4.1");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test7(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "LoadResourceByKeys");
		ndata.put("needkeys", "IDS_Close,IDS_Saturday");
		ndata.put("language", "default");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (show)
			Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
		System.out.println("get " + fmap.size() + " node");
	}
	
	public static void test8(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "LoadResource");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		System.out.println("\n\n");
		if (show)
			Jsvapi.DisplayUtilMapInMap(fmap);
		
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
		System.out.println("get " + fmap.size() + " node");
		if (fmap.containsKey("property"))
			System.out.println("get " + fmap.get("property").size() + " key");
	}
	
	public static void test9(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		// temp= new String("5");
		
		ndata.put("dowhat", "GetMonitorTemplet");
		ndata.put("id", temp);
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (show)
			Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
		System.out.println("get " + fmap.size() + " node");
	}
	
	public static void test10(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetEntityTemplet");
		ndata.put("id", "Informix");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (show)
			Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
		System.out.println("get " + fmap.size() + " node");
	}
	
	public static void test11(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetEntityGroup");
		ndata.put("id", "_Database");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (show)
			Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
		System.out.println("get " + fmap.size() + " node");
	}
	
	public static void test13(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetSvIniFileBySections");
		ndata.put("filename", "user.ini");
		ndata.put("sections", "default");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test14(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetSVSE");
		ndata.put("id", "1");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (show)
		{
			Jsvapi.DisplayUtilMapInMap(fmap);
			System.out.println("GetUnivData:" + ret);
			System.out.println("estr:" + estr);
		}
		
		String label = fmap.get("return").get("svse_label");
		label += " ++";
		fmap.get("return").put("svse_label", label);
		fmap.put("return", fmap.get("return"));
		
		// if (show)
		// Jsvapi.DisplayUtilMapInMap(fmap);
		
		ndata.put("dowhat", "SubmitSVSE");
		ret = svapi.SubmitUnivData(fmap, ndata, estr);
		
		if (show)
		{
			Jsvapi.DisplayUtilMapInMap(fmap);
			System.out.println("SubmitUnivData:" + ret);
			System.out.println("estr:" + estr);
		}
	}
	
	public static void test17(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetGroup");
		ndata.put("id", "1.1");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (show)
		{
			Jsvapi.DisplayUtilMapInMap(fmap);
			System.out.println("GetUnivData:" + ret);
			System.out.println("estr:" + estr);
		}
		
		fmap.get("return").put("id", "");
		fmap.put("return", fmap.get("return"));
		ndata.put("dowhat", "SubmitGroup");
		ndata.put("parentid", "1.1");
		ret = svapi.SubmitUnivData(fmap, ndata, estr);
		
		if (show)
		{
			Jsvapi.DisplayUtilMapInMap(fmap);
			System.out.println("SubmitUnivData:" + ret);
			System.out.println("estr:" + estr);
		}
	}
	
	public static void test18(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetEntity");
		ndata.put("id", "1.3");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (show)
		{
			Jsvapi.DisplayUtilMapInMap(fmap);
			System.out.println("GetUnivData:" + ret);
			System.out.println("estr:" + estr);
		}
		
		fmap.get("return").put("id", "");
		fmap.put("return", fmap.get("return"));
		ndata.put("dowhat", "SubmitEntity");
		ndata.put("parentid", "1");
		ret = svapi.SubmitUnivData(fmap, ndata, estr);
		
		if (show)
		{
			Jsvapi.DisplayUtilMapInMap(fmap);
			System.out.println("SubmitUnivData:" + ret);
			System.out.println("estr:" + estr);
		}
	}
	
	public static void test19(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetMonitor");
		ndata.put("id", "1.2.2");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (show)
		{
			Jsvapi.DisplayUtilMapInMap(fmap);
			System.out.println("GetUnivData:" + ret);
			System.out.println("estr:" + estr);
		}
		
		fmap.get("return").put("id", "");
		fmap.put("return", fmap.get("return"));
		ndata.put("dowhat", "SubmitMonitor");
		ndata.put("parentid", "1.2");
		ret = svapi.SubmitUnivData(fmap, ndata, estr);
		
		if (show)
		{
			Jsvapi.DisplayUtilMapInMap(fmap);
			System.out.println("SubmitUnivData:" + ret);
			System.out.println("estr:" + estr);
		}
	}
	
	public static void test20(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "DelChildren");
		ndata.put("parentid", "1.26");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test21(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "DeleteSVSE");
		ndata.put("id", "12");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test22(Jsvapi svapi, String temp, boolean show)
	{
		Vector<HashMap<String, String>> fmap = new Vector<HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "QueryRecordsByTime");
		ndata.put("id", "1.1.2.3");
		
		ndata.put("end_year", "2008");
		ndata.put("end_month", "9");
		ndata.put("end_day", "21");
		ndata.put("end_hour", "10");
		ndata.put("end_minute", "20");
		ndata.put("end_second", "3");
		
		ndata.put("begin_year", "2006");
		ndata.put("begin_month", "9");
		ndata.put("begin_day", "19");
		ndata.put("begin_hour", "7");
		ndata.put("begin_minute", "5");
		ndata.put("begin_second", "2");
		
		boolean ret = svapi.GetForestData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInVector(fmap);
		System.out.println("GetForestData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test23(Jsvapi svapi, String temp, boolean show)
	{
		Vector<HashMap<String, String>> fmap = new Vector<HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "QueryRecordsByCount");
		ndata.put("id", "1.27.136.22");
//		ndata.put("count", "1");
//		ndata.put("id", "1.27.2.1");
		ndata.put("count", "20");
		boolean ret = svapi.GetForestData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInVector(fmap);
		System.out.println("GetForestData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test25(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetAllMonitorTempletInfo");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test26(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetCommonData");
		ndata.put("id", "1.1");
		ndata.put("type", "group");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test28(Jsvapi svapi, String temp, boolean show)
	{
		Vector<HashMap<String, String>> fmap = new Vector<HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		if (temp.compareToIgnoreCase("temp") == 0)
			temp = "1";
		
		ndata.put("dowhat", "GetTreeData");
		ndata.put("parentid", temp);
		ndata.put("onlySon", "true");
		boolean ret = svapi.GetForestData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInVector(fmap);
		System.out.println("GetForestData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test29(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "TryLogin");
		ndata.put("LoginName", "admin");
		ndata.put("PassWord", temp);
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static String test30(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "encrypt");
		ndata.put(temp, "");
		// ndata.put("1000", "");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		String str = fmap.get("return").get(temp);
		
		if (show)
		{
			Jsvapi.DisplayUtilMapInMap(fmap);
			System.out.println("GetUnivData:" + ret);
			System.out.println("estr:" + estr);
		}
		return str;
	}
	
	public static String test31(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "decrypt");
		ndata.put(temp, "");
		// ndata.put("1G44JQJeJLe4e4NN", "");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		String str = fmap.get("return").get(temp);
		
		if (show)
		{
			Jsvapi.DisplayUtilMapInMap(fmap);
			System.out.println("GetUnivData:" + ret);
			System.out.println("estr:" + estr);
		}
		return str;
	}
	
	public static void test35(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetDynamicData");
		ndata.put("entityId", "1.28.3");
		ndata.put("monitorTplId", temp); // localhost: 11 14 41 net work: 39 433
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static String test36(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "RefreshMonitors");
		ndata.put("parentid", "1");
//		ndata.put("id", "1.28.3.8,1.28.3.9,1.28.3.10,");// 1.63.5,1.63.6,1.63.7,
		ndata.put("id", "1.27.2.1,1.27.7.1,1.27.136.3,1.27.136.12,");
		ndata.put("instantReturn", "true");
		
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return "";
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
		
		return fmap.get("return").get("queueName");
	}
	
	public static boolean test39(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetLatestRefresh");
		ndata.put("queueName", temp);
		
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return ret;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
		return ret;
	}
	
	public static void test41(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "TestEntity");
		ndata.put("entityId", temp);
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test71(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "SubmitCiInstance");
		ndata.put("del_supplement", "false");
		ndata.put("onecmdb_alias", "sv5-103");
//		ndata.put("create", "false");
		ndata.put("create", "true");
		boolean ret = svapi.SubmitUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test72(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetCiInstance");
		ndata.put("onecmdb_alias", "sv5-102");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	public static void test73(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetCiInstance");
		ndata.put("onecmdb_alias", "sv_win-101");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
		
		
		
		ndata.clear();
		ndata.put("dowhat", "SubmitCiInstance");
		ndata.put("del_supplement", "false");
		ndata.put("onecmdb_alias", "sv_win-101");
		ndata.put("create", "false");
//		ndata.put("create", "true");
		ret = svapi.SubmitUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("SubmitUnivData:" + ret);
		System.out.println("estr:" + estr);		
	}
	
	public static void test74(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "GetJobInstance");
		ndata.put("onecmdb_alias", "sv10-101");  // 103
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
		
		
		
		ndata.clear();
		ndata.put("dowhat", "SubmitJobInstance");
		ndata.put("del_supplement", "false");
		ndata.put("parentCiInstance", "sv5-102");
		ndata.put("onecmdb_alias", "sv10-104");
//		ndata.put("create", "false");
		ndata.put("create", "true");
		
		fmap.clear();
		HashMap<String, String> ndata1 = new HashMap<String, String>();
		ndata1.put("sv_monitortype", "366");
		fmap.put("property", ndata1);
		ret = svapi.SubmitUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);		
	}
	
	public static void test75(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "DeleteCMDBInstance");
		ndata.put("onecmdb_alias", "sv_win-102");
		ndata.put("autoDelTable", "true");
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}	
	
	public static void test76(Jsvapi svapi, String temp, boolean show)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		HashMap<String, String> ndata = new HashMap<String, String>();
		StringBuilder estr = new StringBuilder();
		
		ndata.put("dowhat", "RefreshLatestRecords");
		ndata.put("command", temp);
		boolean ret = svapi.GetUnivData(fmap, ndata, estr);
		
		if (!show)
			return;
		Jsvapi.DisplayUtilMapInMap(fmap);
		System.out.println("GetUnivData:" + ret);
		System.out.println("estr:" + estr);
	}
	
	
	
}
