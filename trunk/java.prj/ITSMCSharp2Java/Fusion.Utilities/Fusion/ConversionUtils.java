package Fusion;

import java.math.BigDecimal;

import Fusion.control.CultureInfo;
import Fusion.control.DateTime;
import Fusion.control.IFormatProvider;


/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 11:18:11
 */
public class ConversionUtils {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:11
	 */
	public enum DateTimeFormat {
		Default,
		ExcludeSeconds,
		ISOFormat,
		JustDate,
		JustTime,
		SystemDisplayFormat
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:11
	 */
	public enum NumberFormat {
		BigDecimal,
		Default,
		Integer
	}

	private String FALSE = "False";
	private String TRUE = "True";

	public ConversionUtils(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param aBytes
	 */
	public static DateTime BinaryToDateTime(byte[] aBytes){
		return null;
	}

	/**
	 * 
	 * @param aBytes
	 */
	public static Boolean BinaryToLogical(byte[] aBytes){
		return null;
	}

	/**
	 * 
	 * @param aBytes
	 */
	public static BigDecimal BinaryToNumber(byte[] aBytes){
		return null;
	}

	/**
	 * 
	 * @param aBytes
	 */
	public static String BinaryToString(byte[] aBytes){
		return "";
	}

	/**
	 * 
	 * @param dtValue
	 */
	public static byte[] DateTimeToBinary(DateTime dtValue){
		return null;
	}

	/**
	 * 
	 * @param dtValue
	 */
	public static Boolean DateTimeToLogical(DateTime dtValue){
		return null;
	}

	/**
	 * 
	 * @param dtValue
	 */
	public static BigDecimal DateTimeToNumber(DateTime dtValue){
		return null;
	}

	/**
	 * 
	 * @param dtValue
	 * @param df
	 */
	public static String DateTimeToString(DateTime dtValue, DateTimeFormat df){
		return "";
	}

	/**
	 * 
	 * @param dt
	 */
	public static DateTime DBToLocal(DateTime dt){
		return null;
	}

	/**
	 * 
	 * @param dValue
	 */
	public static BigDecimal DoubleToNumber(double dValue){
		return null;
	}

	public String getFALSE(){
		return FALSE;
	}

	public String getTRUE(){
		return TRUE;
	}

	/**
	 * 
	 * @param dt
	 */
	public static DateTime LocalToDB(DateTime dt){
		return null;
	}

	/**
	 * 
	 * @param bValue
	 */
	public static byte[] LogicalToBinary(Boolean bValue){
		return null;
	}

	/**
	 * 
	 * @param bValue
	 */
	public static DateTime LogicalToDateTime(Boolean bValue){
		return null;
	}

	/**
	 * 
	 * @param bValue
	 */
	public static BigDecimal LogicalToNumber(Boolean bValue){
		return null;
	}

	/**
	 * 
	 * @param bValue
	 */
	public static String LogicalToString(Boolean bValue){
		return "";
	}

	/**
	 * 
	 * @param dValue
	 */
	public static byte[] NumberToBinary(BigDecimal dValue){
		return null;
	}

	/**
	 * 
	 * @param dValue
	 */
	public static DateTime NumberToDateTime(BigDecimal dValue){
		return null;
	}

	/**
	 * 
	 * @param dValue
	 */
	public static Boolean NumberToLogical(BigDecimal dValue){
		return null;
	}

	/**
	 * 
	 * @param dValue
	 */
	public static String NumberToString(BigDecimal dValue){
		return "";
	}

	/**
	 * 
	 * @param nValue
	 */
	public static String NumberToString(int nValue){
		return "";
	}

	/**
	 * 
	 * @param dValue
	 * @param provider
	 */
	public static String NumberToString(BigDecimal dValue, IFormatProvider provider){
		return "";
	}

	/**
	 * 
	 * @param dValue
	 * @param provider
	 */
	public static String NumberToString(double dValue, IFormatProvider provider){
		return "";
	}

	/**
	 * 
	 * @param nValue
	 * @param provider
	 */
	public static String NumberToString(int nValue, IFormatProvider provider){
		return "";
	}

	/**
	 * 
	 * @param oValue
	 */
	public static Boolean ObjectToLogical(Object oValue){
		return null;
	}

	/**
	 * 
	 * @param o
	 * @param provider
	 */
	public static String ObjectToString(Object o, IFormatProvider provider){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFALSE(String newVal){
		FALSE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTRUE(String newVal){
		TRUE = newVal;
	}

	/**
	 * 
	 * @param strValue
	 */
	public static byte[] StringToBinary(String strValue){
		return null;
	}

	/**
	 * 
	 * @param strValue
	 */
	public static DateTime StringToDateTime(String strValue){
		return null;
	}

	/**
	 * 
	 * @param strValue
	 */
	public static Boolean StringToLogical(String strValue){
		return null;
	}

	/**
	 * 
	 * @param strValue
	 */
	public static BigDecimal StringToNumber(String strValue){
		return null;
	}

	/**
	 * 
	 * @param strValue
	 * @param provider
	 */
	public static BigDecimal StringToNumber(String strValue, IFormatProvider provider){
		return null;
	}

	/**
	 * 
	 * @param strDateTime
	 * @param cultureInfo
	 */
	public static DateTime TryParseDateTime(String strDateTime, CultureInfo cultureInfo){
		return null;
	}

}