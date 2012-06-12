package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:28
 */
public class QueryParameterTypeMethods {

	private String NamedQuestionMarkParamEnd = "?}";
	private String NamedQuestionMarkParamStart = "{";
	private String NamedQuestionMarkRegEx = @"(?<parm>{[0-9]+\?})";

	public QueryParameterTypeMethods(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param sbSql
	 * @param nParamNum
	 */
	public static void AppendNamedQuestionMarkParameter(StringBuilder sbSql, int nParamNum){

	}

	public String getNamedQuestionMarkParamEnd(){
		return NamedQuestionMarkParamEnd;
	}

	/**
	 * 
	 * @param nParamNum
	 */
	public static String GetNamedQuestionMarkParameter(int nParamNum){
		return "";
	}

	public String getNamedQuestionMarkParamStart(){
		return NamedQuestionMarkParamStart;
	}

	public String getNamedQuestionMarkRegEx(){
		return NamedQuestionMarkRegEx;
	}

	/**
	 * 
	 * @param typeParm
	 * @param nParamNum
	 */
	public static String GetParameterIndicator(QueryParameterType typeParm, int nParamNum){
		return "";
	}

	/**
	 * 
	 * @param typeParm
	 * @param nStartParamNum
	 * @param nEndParamNum
	 */
	public static String GetParameterIndicators(QueryParameterType typeParm, int nStartParamNum, int nEndParamNum){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNamedQuestionMarkParamEnd(String newVal){
		NamedQuestionMarkParamEnd = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNamedQuestionMarkParamStart(String newVal){
		NamedQuestionMarkParamStart = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNamedQuestionMarkRegEx(String newVal){
		NamedQuestionMarkRegEx = newVal;
	}

}