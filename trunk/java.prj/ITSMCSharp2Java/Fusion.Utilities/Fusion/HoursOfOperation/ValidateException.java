package Fusion.HoursOfOperation;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:43
 */
public class ValidateException extends Exception {

	private String mControlName;

	public ValidateException(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param message
	 * @param controlName
	 */
	public ValidateException(String message, String controlName){

	}

	public String ControlName(){
		return "";
	}

}