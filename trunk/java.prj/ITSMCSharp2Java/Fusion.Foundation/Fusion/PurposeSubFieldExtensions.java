package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:36
 */
public class PurposeSubFieldExtensions {

	private String Brief = "_BRIEF";
	private String Category = "_Category";
	private String RecID = "_RecID";
	private String Rtf = "_RTF";
	private String Uppercase = "_UCASE";
	private String ValidationId = "_VID";
	private String VRecID = "_VRecID";

	public PurposeSubFieldExtensions(){

	}

	public void finalize() throws Throwable {

	}

	public String getBrief(){
		return Brief;
	}

	public String getCategory(){
		return Category;
	}

	public String getRecID(){
		return RecID;
	}

	public String getRtf(){
		return Rtf;
	}

	public String getUppercase(){
		return Uppercase;
	}

	public String getValidationId(){
		return ValidationId;
	}

	public String getVRecID(){
		return VRecID;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBrief(String newVal){
		Brief = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCategory(String newVal){
		Category = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRecID(String newVal){
		RecID = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRtf(String newVal){
		Rtf = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUppercase(String newVal){
		Uppercase = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setValidationId(String newVal){
		ValidationId = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setVRecID(String newVal){
		VRecID = newVal;
	}

}