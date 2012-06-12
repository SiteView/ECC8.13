package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:37
 */
public class PurposeValues {

	private String Brief = "fusion/brief";
	private String LinkCategory = "LinkCategory";
	private String LinkId = "LinkID";
	private String Rtf = "text/rtf";
	private String Uppercase = "fusion/uppercase";
	private String ValidationId = "fusion/validation";
	private String VLinkId = "VLinkID";

	public PurposeValues(){

	}

	public void finalize() throws Throwable {

	}

	public String getBrief(){
		return Brief;
	}

	public String getLinkCategory(){
		return LinkCategory;
	}

	public String getLinkId(){
		return LinkId;
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

	public String getVLinkId(){
		return VLinkId;
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
	public void setLinkCategory(String newVal){
		LinkCategory = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLinkId(String newVal){
		LinkId = newVal;
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
	public void setVLinkId(String newVal){
		VLinkId = newVal;
	}

}