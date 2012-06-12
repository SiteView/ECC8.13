package com.siteview.eccservice;

import java.util.HashMap;
import java.util.Vector;

import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebResult;
import javax.jws.WebService;


@WebService(serviceName = "eccapi", targetNamespace = "http://www.siteview.com")
public interface InterfaceEccService
{
	/**
	 * 测试接口
	 */
	public String test1(String str);
	
	/**
	 * 测试接口
	 */
	public HashMap<String, String> test2(HashMap<String, HashMap<String, String>> fmap);

	
	public keyValue[] test3(keyValue[] inwhat);
	
	
	public RetMapInVector php_GetUnivData2(keyValue[] inwhat);
	public RetMapInVector php_SubmitUnivData2(keyValue[][] inlist, keyValue[] inwhat);
	public RetMapInVector php_GetForestData(keyValue[] inwhat);
	
	
	/**
	 * 此函数对应于 Jsvapi.GetUnivData
	 * 
	 * @return 从 ecc api(业务逻辑层)返回的数据 RetMapInMap
	 * @inwhat 传入的请求
	 * 
	 */
	public RetMapInMap GetUnivData(HashMap<String, String> inwhat);

	/**
	 * 此函数对应于 Jsvapi.GetUnivData
	 * 
	 * @return 从 ecc api(业务逻辑层)返回的数据 RetMapInMap
	 * @inwhat 传入的请求
	 * 
	 */
	public RetMapInVector GetUnivData2(HashMap<String, String> inwhat);
	
	/**
	 * 此函数对应于 Jsvapi.SubmitUnivData
	 * 
	 * @return 从 ecc api(业务逻辑层)返回的数据 RetMapInMap
	 * @fmap 要提交给 ecc api 的数据
	 * @inwhat 传入的请求
	 * 
	 */
	public RetMapInMap SubmitUnivData(HashMap<String, HashMap<String, String>> fmap, HashMap<String, String> inwhat);
	
	/**
	 * 此函数对应于 Jsvapi.SubmitUnivData
	 * 
	 * @return 从 ecc api(业务逻辑层)返回的数据 RetMapInMap
	 * @invmap 要提交给 ecc api 的数据
	 * @inwhat 传入的请求
	 * 
	 */
	public RetMapInVector SubmitUnivData2(Vector<HashMap<String, String>> invmap,HashMap<String, String> inwhat);
	
	/**
	 * 此函数对应于 Jsvapi.GetForestData
	 * 
	 * @return 从 ecc api(业务逻辑层)请求获得的树数据 RetMapInVector
	 * @inwhat 传入的请求
	 * 
	 */
	public RetMapInVector GetForestData(HashMap<String, String> inwhat);
	
	
	
}

