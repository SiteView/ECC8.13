package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:08
 */
public class OverwriteOptions {

	private String Append = "Append";
	private String InsertBefore = "InsertBefore";
	private String No = "No";
	private String Yes = "Yes";

	public OverwriteOptions(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strConst
	 */
	public static String ConvertConstantToDisplayText(String strConst){
		return "";
	}

	/**
	 * 
	 * @param strDisp
	 */
	public static String ConvertDisplayTextToConstant(String strDisp){
		return "";
	}

	public String getAppend(){
		return Append;
	}

	public String getInsertBefore(){
		return InsertBefore;
	}

	public String getNo(){
		return No;
	}

	public String getYes(){
		return Yes;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAppend(String newVal){
		Append = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setInsertBefore(String newVal){
		InsertBefore = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNo(String newVal){
		No = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setYes(String newVal){
		Yes = newVal;
	}

}