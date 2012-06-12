package Fusion;

import Fusion.control.ArgumentException;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:19
 */
public class ExceptionUtils {

	public ExceptionUtils(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strParamName
	 * @param strSource
	 */
	public static ArgumentException BuildArgumentException(String strParamName, String strSource){
		return null;
	}

	/**
	 * 
	 * @param msgInfo
	 * @param strMessage
	 * @param strSource
	 * @param eInner
	 */
	public static RuleEvaluationException BuildRuleEvaluationException(MessageInfo msgInfo, String strMessage, String strSource, Exception eInner){
		return null;
	}

	/**
	 * 
	 * @param strMessage
	 * @param strSource
	 * @param eInner
	 */
	public static FusionSecurityException BuildSecurityException(String strMessage, String strSource, Exception eInner){
		return null;
	}

	/**
	 * 
	 * @param msgInfo
	 * @param strMessage
	 * @param strSource
	 * @param eInner
	 */
	public static FusionSecurityException BuildSecurityException(MessageInfo msgInfo, String strMessage, String strSource, Exception eInner){
		return null;
	}

	/**
	 * 
	 * @param ex
	 */
	public static String GetDataStoreErrorMsgs(Exception ex){
		return "";
	}

	/**
	 * 
	 * @param ex
	 */
	public static String GetErrorMsgs(Exception ex){
		return "";
	}

	/**
	 * 
	 * @param o
	 * @param strParamName
	 * @param strSource
	 */
	public static void ThrowIfNullArgument(Object o, String strParamName, String strSource){

	}

	/**
	 * 
	 * @param strValue
	 * @param strParamName
	 * @param strSource
	 */
	public static void ThrowIfNullOrEmptyArgument(String strValue, String strParamName, String strSource){

	}

	/**
	 * 
	 * @param abytes
	 * @param strParamName
	 * @param strSource
	 */
	public static void ThrowIfNullOrEmptyArgument(byte[] abytes, String strParamName, String strSource){

	}

}