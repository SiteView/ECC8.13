package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:22
 */
public class StorageSources {

	private String ExternalTable = "ExternalTable";
	private String Internal = "Internal";

	public StorageSources(){

	}

	public void finalize() throws Throwable {

	}

	public String getExternalTable(){
		return ExternalTable;
	}

	public String getInternal(){
		return Internal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setExternalTable(String newVal){
		ExternalTable = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setInternal(String newVal){
		public = newVal;
	}

}