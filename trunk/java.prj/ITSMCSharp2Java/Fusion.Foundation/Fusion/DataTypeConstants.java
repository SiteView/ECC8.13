package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:00
 */
public class DataTypeConstants {

	private int USE_MAX_LENGTH = -1;
	private int USE_MAX_SEARCHABLE_LENGTH = -2;

	public DataTypeConstants(){

	}

	public void finalize() throws Throwable {

	}

	public int getUSE_MAX_LENGTH(){
		return USE_MAX_LENGTH;
	}

	public int getUSE_MAX_SEARCHABLE_LENGTH(){
		return USE_MAX_SEARCHABLE_LENGTH;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUSE_MAX_LENGTH(int newVal){
		USE_MAX_LENGTH = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUSE_MAX_SEARCHABLE_LENGTH(int newVal){
		USE_MAX_SEARCHABLE_LENGTH = newVal;
	}

}