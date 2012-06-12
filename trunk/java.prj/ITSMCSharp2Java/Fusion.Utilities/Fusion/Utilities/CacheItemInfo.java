package Fusion.Utilities;

import Fusion.control.DateTime;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:07
 */
public class CacheItemInfo {

	private String m_busObjName;
	private DateTime m_lastUpdated;
	private String m_tableName;

	public CacheItemInfo(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param tableName
	 * @param busObjName
	 */
	public CacheItemInfo(String tableName, String busObjName){

	}

	/**
	 * 
	 * @param tableName
	 * @param busObjName
	 * @param lastUpdated
	 */
	public CacheItemInfo(String tableName, String busObjName, DateTime lastUpdated){

	}

	public String BusinessObjectName(){
		return "";
	}

	public DateTime LastUpdated(){
		return null;
	}

	public String TableName(){
		return "";
	}

}