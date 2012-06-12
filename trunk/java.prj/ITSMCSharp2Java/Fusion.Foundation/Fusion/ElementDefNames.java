package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:17
 */
public class ElementDefNames {

	private String False = "False";
	private String True = "True";

	public ElementDefNames(){

	}

	public void finalize() throws Throwable {

	}

	public String getFalse(){
		return False;
	}

	public String getTrue(){
		return True;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFalse(String newVal){
		False = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTrue(String newVal){
		True = newVal;
	}

}