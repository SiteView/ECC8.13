package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:32
 */
public class SystemUpgradeConstants {

	private String CodeExtensionPurpose = "SystemUpgrade";

	public SystemUpgradeConstants(){

	}

	public void finalize() throws Throwable {

	}

	public String getCodeExtensionPurpose(){
		return CodeExtensionPurpose;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCodeExtensionPurpose(String newVal){
		CodeExtensionPurpose = newVal;
	}

}