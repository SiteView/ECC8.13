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
	 * ���Խӿ�
	 */
	public String test1(String str);
	
	/**
	 * ���Խӿ�
	 */
	public HashMap<String, String> test2(HashMap<String, HashMap<String, String>> fmap);

	
	public keyValue[] test3(keyValue[] inwhat);
	
	
	public RetMapInVector php_GetUnivData2(keyValue[] inwhat);
	public RetMapInVector php_SubmitUnivData2(keyValue[][] inlist, keyValue[] inwhat);
	public RetMapInVector php_GetForestData(keyValue[] inwhat);
	
	
	/**
	 * �˺�����Ӧ�� Jsvapi.GetUnivData
	 * 
	 * @return �� ecc api(ҵ���߼���)���ص����� RetMapInMap
	 * @inwhat ���������
	 * 
	 */
	public RetMapInMap GetUnivData(HashMap<String, String> inwhat);

	/**
	 * �˺�����Ӧ�� Jsvapi.GetUnivData
	 * 
	 * @return �� ecc api(ҵ���߼���)���ص����� RetMapInMap
	 * @inwhat ���������
	 * 
	 */
	public RetMapInVector GetUnivData2(HashMap<String, String> inwhat);
	
	/**
	 * �˺�����Ӧ�� Jsvapi.SubmitUnivData
	 * 
	 * @return �� ecc api(ҵ���߼���)���ص����� RetMapInMap
	 * @fmap Ҫ�ύ�� ecc api ������
	 * @inwhat ���������
	 * 
	 */
	public RetMapInMap SubmitUnivData(HashMap<String, HashMap<String, String>> fmap, HashMap<String, String> inwhat);
	
	/**
	 * �˺�����Ӧ�� Jsvapi.SubmitUnivData
	 * 
	 * @return �� ecc api(ҵ���߼���)���ص����� RetMapInMap
	 * @invmap Ҫ�ύ�� ecc api ������
	 * @inwhat ���������
	 * 
	 */
	public RetMapInVector SubmitUnivData2(Vector<HashMap<String, String>> invmap,HashMap<String, String> inwhat);
	
	/**
	 * �˺�����Ӧ�� Jsvapi.GetForestData
	 * 
	 * @return �� ecc api(ҵ���߼���)�����õ������� RetMapInVector
	 * @inwhat ���������
	 * 
	 */
	public RetMapInVector GetForestData(HashMap<String, String> inwhat);
	
	
	
}

