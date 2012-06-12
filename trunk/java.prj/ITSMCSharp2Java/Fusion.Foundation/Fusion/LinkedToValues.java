package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:05
 */
public class LinkedToValues {

	private String Alllinked = "(Alllinked)";
	private String Unlinked = "(Unlinked)";

	public LinkedToValues(){

	}

	public void finalize() throws Throwable {

	}

	public String getAlllinked(){
		return Alllinked;
	}

	public String getUnlinked(){
		return Unlinked;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAlllinked(String newVal){
		Alllinked = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUnlinked(String newVal){
		Unlinked = newVal;
	}

}