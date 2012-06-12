package Fusion;

import Fusion.control.RegistryKey;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:35
 */
public class RegistryUtils {

	private String BEGIN_LOCAL_TOKEN = "##(";
	private String END_LOCAL_TOKEN = ")##";
	private String LOCAL_SETTINGS_KEY = "Software\\FrontRange Solutions\\FRS Application";
	private String LOCAL_TOKENS = "LocalTokens";

	public RegistryUtils(){

	}

	public void finalize() throws Throwable {

	}

	public String getBEGIN_LOCAL_TOKEN(){
		return BEGIN_LOCAL_TOKEN;
	}

	/**
	 * 
	 * @param subKeys
	 * @param strName
	 */
	public static Object GetCurrentUserSetting(String[] subKeys, String strName){
		return null;
	}

	/**
	 * 
	 * @param strSubKey
	 * @param strName
	 * @param oDefault
	 */
	public static Object GetCurrentUserSetting(String strSubKey, String strName, Object oDefault){
		return null;
	}

	/**
	 * 
	 * @param subKeys
	 * @param strName
	 * @param oDefault
	 */
	public static Object GetCurrentUserSetting(String[] subKeys, String strName, Object oDefault){
		return null;
	}

	/**
	 * 
	 * @param subKeys
	 * @param strName
	 * @param bDefault
	 */
	public static Boolean GetCurrentUserSettingAsBoolean(String[] subKeys, String strName, Boolean bDefault){
		return null;
	}

	/**
	 * 
	 * @param subKeys
	 * @param strName
	 * @param nDefault
	 */
	public static int GetCurrentUserSettingAsInt(String[] subKeys, String strName, int nDefault){
		return 0;
	}

	/**
	 * 
	 * @param subKeys
	 * @param strName
	 * @param strDefault
	 */
	public static String GetCurrentUserSettingAsString(String[] subKeys, String strName, String strDefault){
		return "";
	}

	public String getEND_LOCAL_TOKEN(){
		return END_LOCAL_TOKEN;
	}

	public String getLOCAL_SETTINGS_KEY(){
		return LOCAL_SETTINGS_KEY;
	}

	public String getLOCAL_TOKENS(){
		return LOCAL_TOKENS;
	}

	/**
	 * 
	 * @param subKeys
	 * @param strName
	 */
	public static Object GetLocalMachineSetting(String[] subKeys, String strName){
		return null;
	}

	/**
	 * 
	 * @param strSubKey
	 * @param strName
	 * @param oDefault
	 */
	public static Object GetLocalMachineSetting(String strSubKey, String strName, Object oDefault){
		return null;
	}

	/**
	 * 
	 * @param subKeys
	 * @param strName
	 * @param oDefault
	 */
	public static Object GetLocalMachineSetting(String[] subKeys, String strName, Object oDefault){
		return null;
	}

	/**
	 * 
	 * @param subKeys
	 * @param strName
	 * @param bDefault
	 */
	public static Boolean GetLocalMachineSettingAsBoolean(String[] subKeys, String strName, Boolean bDefault){
		return null;
	}

	/**
	 * 
	 * @param subKeys
	 * @param strName
	 * @param nDefault
	 */
	public static int GetLocalMachineSettingAsInt(String[] subKeys, String strName, int nDefault){
		return 0;
	}

	/**
	 * 
	 * @param subKeys
	 * @param strName
	 * @param strDefault
	 */
	public static String GetLocalMachineSettingAsString(String[] subKeys, String strName, String strDefault){
		return "";
	}

	/**
	 * 
	 * @param localToken
	 */
	public static String GetLocalTokenValue(String localToken){
		return "";
	}

	/**
	 * 
	 * @param keyRoot
	 * @param subKeys
	 * @param strName
	 */
	private static Object GetValue(RegistryKey keyRoot, String[] subKeys, String strName){
		return null;
	}

	/**
	 * 
	 * @param keyRoot
	 * @param subKeys
	 * @param strName
	 * @param oDefault
	 */
	private static Object GetValue(RegistryKey keyRoot, String[] subKeys, String strName, Object oDefault){
		return null;
	}

	/**
	 * 
	 * @param keyRoot
	 * @param subKeys
	 */
	private static RegistryKey OpenSubKey(RegistryKey keyRoot, String[] subKeys){
		return null;
	}

	/**
	 * 
	 * @param original
	 */
	public static String ResolveLocalTokensInString(String original){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBEGIN_LOCAL_TOKEN(String newVal){
		BEGIN_LOCAL_TOKEN = newVal;
	}

	/**
	 * 
	 * @param subKeys
	 * @param strName
	 * @param oValue
	 */
	public static void SetCurrentUserSetting(String[] subKeys, String strName, Object oValue){

	}

	/**
	 * 
	 * @param strSubKey
	 * @param strName
	 * @param oValue
	 */
	public static void SetCurrentUserSetting(String strSubKey, String strName, Object oValue){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEND_LOCAL_TOKEN(String newVal){
		END_LOCAL_TOKEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLOCAL_SETTINGS_KEY(String newVal){
		LOCAL_SETTINGS_KEY = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLOCAL_TOKENS(String newVal){
		LOCAL_TOKENS = newVal;
	}

	/**
	 * 
	 * @param strSubKey
	 * @param strName
	 * @param oValue
	 */
	public static void SetLocalMachineSetting(String strSubKey, String strName, Object oValue){

	}

	/**
	 * 
	 * @param subKeys
	 * @param strName
	 * @param oValue
	 */
	public static void SetLocalMachineSetting(String[] subKeys, String strName, Object oValue){

	}

	/**
	 * 
	 * @param keyRoot
	 * @param subKeys
	 * @param strName
	 * @param oValue
	 */
	private static void SetValue(RegistryKey keyRoot, String[] subKeys, String strName, Object oValue){

	}

}