package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:46
 */
public class ReplicationValues {

	private int UseDatabaseDefault = -1;

	public ReplicationValues(){

	}

	public void finalize() throws Throwable {

	}

	public int getUseDatabaseDefault(){
		return UseDatabaseDefault;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUseDatabaseDefault(int newVal){
		UseDatabaseDefault = newVal;
	}

}