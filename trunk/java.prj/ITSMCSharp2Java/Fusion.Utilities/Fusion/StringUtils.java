package Fusion;

import java.awt.Font;
import java.awt.Graphics;
import java.math.BigDecimal;

import Fusion.control.DateTime;
import Fusion.control.IDictionary;
import Fusion.control.SizeF;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 11:18:39
 */
public class StringUtils {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:39
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
	 * @created 15-四月-2010 11:18:39
	 */
	public enum NumberFormat {
		BigDecimal,
		Default,
		Integer
	}

	private String BEGIN_STANDARD_PARAMETER = "$$(";
	private String COMPANYNAME_TOKEN = "CompanyName";
	private String END_STANDARD_PARAMETER = ")$$";
	private String FALSE = "False";
	private String PRODUCTACRONYM_TOKEN = "ProductAcronym";
	private String PRODUCTNAME_TOKEN = "ProductName";
	private String SHORTPRODUCTNAME_TOKEN = "ShortProductName";
	private String TRUE = "True";

	public StringUtils(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strList
	 * @param strItem
	 */
	public static String AddCommaDelimitedItem(String strList, String strItem){
		return "";
	}

	/**
	 * 
	 * @param strOriginalValue
	 * @param strDelimiter
	 * @param strAppendValue
	 */
	public static String AppendWithDelimiter(String strOriginalValue, String strDelimiter, String strAppendValue){
		return "";
	}

	/**
	 * 
	 * @param sb
	 * @param strDelimiter
	 * @param strAppendValue
	 */
	public static void AppendWithDelimiter(StringBuilder sb, String strDelimiter, String strAppendValue){

	}

	/**
	 * 
	 * @param strFirst
	 * @param strSecond
	 * @param bIgnoreCase
	 */
	public static Boolean CompareLeft(String strFirst, String strSecond, Boolean bIgnoreCase){
		return null;
	}

	/**
	 * 
	 * @param strFirst
	 * @param strSecond
	 * @param bIgnoreCase
	 */
	public static Boolean CompareRight(String strFirst, String strSecond, Boolean bIgnoreCase){
		return null;
	}

	/**
	 * 
	 * @param strToCheck
	 * @param bLettersAllowed
	 * @param bDigitsAllowed
	 * @param strChars
	 */
	public static Boolean ContainsOnlyChars(String strToCheck, Boolean bLettersAllowed, Boolean bDigitsAllowed, String strChars){
		return null;
	}

	/**
	 * 
	 * @param strValue
	 * @param cCharacter
	 */
	public static int CountCharacter(String strValue, char cCharacter){
		return 0;
	}

	/**
	 * 
	 * @param strOne
	 * @param strTwo
	 * @param bIgnoreCase
	 */
	public static int CountSimilarCharacters(String strOne, String strTwo, Boolean bIgnoreCase){
		return 0;
	}

	/**
	 * 
	 * @param strSearch
	 * @param strFind
	 */
	public static int FindIndexOfOutsideQuotes(String strSearch, String strFind){
		return 0;
	}

	/**
	 * 
	 * @param strSearch
	 * @param strFind
	 * @param iStartPos
	 */
	public static int FindIndexOfOutsideQuotes(String strSearch, String strFind, int iStartPos){
		return 0;
	}

	public String getBEGIN_STANDARD_PARAMETER(){
		return BEGIN_STANDARD_PARAMETER;
	}

	public String getCOMPANYNAME_TOKEN(){
		return COMPANYNAME_TOKEN;
	}

	public String getEND_STANDARD_PARAMETER(){
		return END_STANDARD_PARAMETER;
	}

	public String getFALSE(){
		return FALSE;
	}

	public String getPRODUCTACRONYM_TOKEN(){
		return PRODUCTACRONYM_TOKEN;
	}

	public String getPRODUCTNAME_TOKEN(){
		return PRODUCTNAME_TOKEN;
	}

	/**
	 * 
	 * @param strString
	 * @param strSeparator
	 * @param nSeparator
	 */
	public static int GetSeparatorPosition(String strString, String strSeparator, int nSeparator){
		return 0;
	}

	public String getSHORTPRODUCTNAME_TOKEN(){
		return SHORTPRODUCTNAME_TOKEN;
	}

	/**
	 * 
	 * @param strString
	 * @param strSeparator
	 * @param nPosition
	 */
	public static String GetSubString(String strString, String strSeparator, int nPosition){
		return "";
	}

	public String getTRUE(){
		return TRUE;
	}

	/**
	 * 
	 * @param astrArray
	 * @param strValue
	 */
	public static void InitializeStringArray(String[] astrArray, String strValue){

	}

	/**
	 * 
	 * @param strValue
	 */
	public static Boolean IsEmpty(String strValue){
		return null;
	}

	/**
	 * 
	 * @param strServer
	 */
	public static Boolean IsIpAddress(String strServer){
		return null;
	}

	/**
	 * 
	 * @param str
	 * @param iLength
	 */
	public static String Left(String str, int iLength){
		return "";
	}

	/**
	 * 
	 * @param g
	 * @param font
	 */
	public static SizeF MeasureLocalizedString(Graphics g, Font font){
		return null;
	}

	/**
	 * 
	 * @param g
	 * @param font
	 * @param nMaxCount
	 * @param nCount
	 */
	public static SizeF MeasureLocalizedString(Graphics g, Font font, int nMaxCount, int nCount){
		return null;
	}

	/**
	 * 
	 * @param str
	 * @param iLength
	 */
	public static String Right(String str, int iLength){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBEGIN_STANDARD_PARAMETER(String newVal){
		BEGIN_STANDARD_PARAMETER = newVal;
	}

	/**
	 * 
	 * @param strText
	 */
	public static String SetBrandingInfo(String strText){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCOMPANYNAME_TOKEN(String newVal){
		COMPANYNAME_TOKEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEND_STANDARD_PARAMETER(String newVal){
		END_STANDARD_PARAMETER = newVal;
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
	public void setPRODUCTACRONYM_TOKEN(String newVal){
		PRODUCTACRONYM_TOKEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPRODUCTNAME_TOKEN(String newVal){
		PRODUCTNAME_TOKEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSHORTPRODUCTNAME_TOKEN(String newVal){
		SHORTPRODUCTNAME_TOKEN = newVal;
	}

	/**
	 * 
	 * @param strText
	 * @param dictValues
	 */
	public static String SetToken(String strText, IDictionary dictValues){
		return "";
	}

	/**
	 * 
	 * @param strText
	 * @param strToken
	 * @param dtValue
	 */
	public static String SetToken(String strText, String strToken, DateTime dtValue){
		return "";
	}

	/**
	 * 
	 * @param strText
	 * @param strToken
	 * @param dValue
	 */
	public static String SetToken(String strText, String strToken, BigDecimal dValue){
		return "";
	}

	/**
	 * 
	 * @param strText
	 * @param strToken
	 * @param nValue
	 */
	public static String SetToken(String strText, String strToken, int nValue){
		return "";
	}

	/**
	 * 
	 * @param strText
	 * @param strToken
	 * @param strValue
	 */
	public static String SetToken(String strText, String strToken, String strValue){
		return "";
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
	 * @param strInput
	 * @param strCharsToStrip
	 */
	public static String StripOutChars(String strInput, String strCharsToStrip){
		return "";
	}

	/**
	 * 
	 * @param strInput
	 * @param bLettersAllowed
	 * @param bDigitsAllowed
	 * @param strCharsToKeep
	 */
	public static String StripOutCharsExcept(String strInput, Boolean bLettersAllowed, Boolean bDigitsAllowed, String strCharsToKeep){
		return "";
	}

	/**
	 * 
	 * @param strInput
	 * @param bLettersAllowed
	 * @param bDigitsAllowed
	 * @param strCharsToKeep
	 */
	public static String TrimStartUntilCharFound(String strInput, Boolean bLettersAllowed, Boolean bDigitsAllowed, String strCharsToKeep){
		return "";
	}

	/**
	 * 
	 * @param strInput
	 */
	public static String TrimStartUntilLetter(String strInput){
		return "";
	}

}