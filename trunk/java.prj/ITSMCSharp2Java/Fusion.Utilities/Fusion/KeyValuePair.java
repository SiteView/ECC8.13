package Fusion;

import java.util.ArrayList;

import Fusion.control.ComboBox;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:25
 */
public class KeyValuePair {

	private Object m_oTag;
	private String m_strKey;
	private String m_strValue;



	public void finalize() throws Throwable {

	}

	public KeyValuePair(){

	}

	/**
	 * 
	 * @param strKey
	 * @param strValue
	 */
	public KeyValuePair(String strKey, String strValue){

	}

	/**
	 * 
	 * @param KeyValuePairs
	 */
	public static ArrayList GetNamesList(ArrayList KeyValuePairs){
		return null;
	}

	/**
	 * 
	 * @param items
	 */
	public static ArrayList GetNamesList(ComboBox.ObjectCollection items){
		return null;
	}

	public String Key(){
		return "";
	}

	public Object Tag(){
		return null;
	}

	public String ToString(){
		return "";
	}

	public String Value(){
		return "";
	}

}