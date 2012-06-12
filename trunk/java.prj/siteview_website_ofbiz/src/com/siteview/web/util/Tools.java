package com.siteview.web.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.base.util.UtilProperties;

public class Tools {
	public static String getRequestUrl(HttpServletRequest request,String key1 ,String value1,String key2 ,String value2,String key3 ,String value3,String key4 ,String value4)
	{
		return getRequestUrl(request,UtilMisc.toMap(key1,value1,key2,value2,key3,value3,key4,value4));
	}
	public static String getRequestUrl(HttpServletRequest request,String key1 ,String value1,String key2 ,String value2,String key3 ,String value3)
	{
		return getRequestUrl(request,UtilMisc.toMap(key1,value1,key2,value2,key3,value3));
	}
	public static String getRequestUrl(HttpServletRequest request,String key1 ,String value1,String key2 ,String value2)
	{
		return getRequestUrl(request,UtilMisc.toMap(key1,value1,key2,value2));
	}
	public static String getRequestUrl(HttpServletRequest request,String key ,String value)
	{
		return getRequestUrl(request,UtilMisc.toMap(key,value));
	}

	public static String getRequestUrl(HttpServletRequest request,Object...params)
	{
		return getRequestUrl(request,UtilMisc.toMap(params));
	}
	public static String getRequestUrl(HttpServletRequest request,String...params)
	{
		return getRequestUrl(request,(Object[])params);
	}

	
	public static String getRequestUrl(HttpServletRequest request,Map<String, Object> addParameters)
	{
		StringBuffer bf = new StringBuffer();
		String queryString = getQueryString(request.getQueryString(),addParameters);
		bf.append(request.getRequestURI());
		if (queryString.length()>0){
			bf.append("?");
			bf.append(queryString);
		}
		return bf.toString();
	}
	public static String getQueryString(String queryString,Map<String, Object> addParameters)
	{
		StringBuffer bf = new StringBuffer();
		String filterString = filter(queryString,addParameters);
		String newQueryString = getQueryString(addParameters);
		if (filterString != null && !"".equals(filterString))
		{
			bf.append(filterString);
			bf.append("&");
		}
		bf.append(newQueryString);
		return bf.toString();
	}
	
	public static String getQueryString(Map<String, Object> parameters){
		StringBuffer bf = new StringBuffer();
		for (String key : parameters.keySet())
		{
			if (key == null) continue;
			Object value = parameters.get(key);
			if (value == null) continue;
			if ("".equals(value)) continue;
			if (bf.length() != 0){
				bf.append("&");
			}
			bf.append(key);
			bf.append("=");
			bf.append(value);
		}
		return bf.toString();
	}
	private static String filter(String queryString,Map<String, Object> parameters)
	{
		if ( queryString == null || "".equals(queryString)) return "";
		String qString = queryString;
		String[] paraArray = qString.split("&");
		List<String> newParam = new ArrayList<String>();
		for (String keyValPair : paraArray)
		{
			if (keyValPair == null) continue;
			String[] KeyValue = keyValPair.split("=");
			if (KeyValue.length != 2) continue;
			if (KeyValue[1] == null || "".equals(KeyValue[1])) continue;
			Object value = parameters.get(KeyValue[0]);
			if (value == null ){
				newParam.add(keyValPair);
			}
		}
		StringBuffer retbuf = new StringBuffer();
		for (String val : newParam){
			if (newParam.indexOf(val) > 0)retbuf.append("&");
			retbuf.append(val);
		}
		return retbuf.toString();
	}
	

	public static Map<String,Object> getResourceBundle(HttpServletRequest request,String resource)
	{
		Map<String,Object> retmap = new HashMap<String,Object>();
		try{
			//retmap.putAll(UtilProperties.getResourceBundleMap("CommonUiLabels", request.getLocale()));
			retmap.putAll(UtilProperties.getResourceBundleMap(resource, request.getLocale()));
		}catch(Exception e){
		}
		return retmap;
	}
	public static String getLocale(Locale locale)
	{
		return "en".compareToIgnoreCase(locale.getLanguage()) == 0 ? "en" : 
			   "zh".compareToIgnoreCase(locale.getLanguage()) == 0 ? "zh" :
			   "zh";
	}
	public static String getCountry(Locale locale)
	{
		return locale.getCountry();
	}
	
	public static String getStringLen(String str,int len)
	{
		if (str == null) return "";
		if (str.length() <= len) return str;
		return str.substring(0, len);
	}
	
	public static void main1(String[] args){
		String queryString = "abc=111&bbb=222&ccc=333";
		Map<String, Object> parameters = new HashMap<String, Object>();
		parameters.put("bbb", "0123");
		parameters.put("ffff", "ffff");
		parameters.put("abc", "aaa");
		String newQueryString = getQueryString(queryString,parameters);
		System.out.println(newQueryString);
	}
	public static void main(String[] args){
		System.out.println(subContentStringOrialBytes("我们都是我们都是我们都123111",12));
		System.out.println(subContentStringOrialBytes("abcdedshdgashdaohsdohaojhsdoahs",12));
		System.out.println(subContentStringOrialBytes("1221",12));
		System.out.println(subContentStringOrialBytes("我们都",12));
		System.out.println(subContentStringOrialBytes("",12));
		System.out.println(subContentStringOrialBytes(null,12));
	}
	 /**
	 * 获取指定长度字符串的字节长
	 * 
	 * @param str
	 *            被处理字符串
	 * @param maxlength
	 *            截取长度
	 * @author Strong Yuan
	 * @version 1.1
	 * @return String
	 */
	private static long getStringByteLength(String str, int maxlength) {
		if (str == null)
			return 0;
		int tmp_len = maxlength;

		if (str.length() < maxlength)
			tmp_len = str.length();
		else if (str.length() > maxlength * 2)
			tmp_len = maxlength * 2;

		char[] tempchar = str.substring(0, tmp_len).toCharArray();

		int intVariable = 0;
		String s1 = null;
		for (int i = 0; i < tempchar.length && intVariable <= maxlength; i++) {
			s1 = String.valueOf(tempchar[i]);
			intVariable += s1.getBytes().length;
		}
		s1 = null;
		tempchar = null;
		return intVariable;
	}

	/**
	 * 截取指定长度的字符串,基于bytes,即是中文的长度为2,英文为1
	 * @param str 被处理字符串
	 * @param targetCount 截取长度
	 * @param more 后缀字符串
	 * @author Strong Yuan
	 * @version 1.1
	 * @return
	 */
	public static String subContentStringOrialBytes(String str,
			int targetCount, String more) {
		if (str == null)
			return "";
		int initVariable = 0;
		StringBuffer restr = new StringBuffer();
		if (getStringByteLength(str, targetCount) <= targetCount)
			return str;

		String s1 = null;
		byte[] b;
		char[] tempchar = str.toCharArray();
		for (int i = 0; (i < tempchar.length && targetCount > initVariable); i++) {
			s1 = String.valueOf(tempchar[i]);
			b = s1.getBytes();
			initVariable += b.length;
			restr.append(tempchar[i]);
		}

		if (targetCount == initVariable || (targetCount == initVariable - 1)) {
			restr.append(more);
		}
		return restr.toString();
	}

	/**
	 * 截取指定长度的字符串,存在问题,但效率会高一点点.just a little
	 * @param str 被处理字符串
	 * @param targetCount 截取长度
	 * @param more 后缀字符串
	 * @version 1.1
	 * @author Strong Yuan
	 * @return String
	 */
	public static String subContentStringOrial(String str, int targetCount) {
		return subContentStringOrial(str, targetCount, "...");
	}

	/**
	 * 截取指定长度的字符串,存在问题,但效率会高一点点.just a little
	 * @param str 被处理字符串
	 * @param targetCount 截取长度
	 * @param more 后缀字符串
	 * @author Strong Yuan
	 * @return String
	 */
	public static String subContentStringOrial(String str, int targetCount,
			String more) {
		if (str == null)
			return "";
		int initVariable = 0;
		StringBuffer restr = new StringBuffer();
		if (str.length() <= targetCount)
			return str;

		String s1 = null;
		byte[] b;
		char[] tempchar = str.toCharArray();
		for (int i = 0; (i < tempchar.length && targetCount > initVariable); i++) {
			s1 = String.valueOf(tempchar[i]);
			b = s1.getBytes();
			initVariable += b.length;
			restr.append(tempchar[i]);
		}

		if (targetCount == initVariable || (targetCount == initVariable - 1)) {
			restr.append(more);
		}
		return restr.toString();
	}
	 /**
		 * 截取字符串的前targetCount个字符
		 * 
		 * @param str
		 *            被处理字符串
		 * @param targetCount
		 *            截取长度
		 * @version 1.1
		 * @author Strong Yuan
		 * @return String
		 */
	public static String subContentStringOrialBytes(String str, int targetCount) {
		return subContentStringOrialBytes(str, targetCount, "...");
	}	
}
