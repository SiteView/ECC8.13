package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:19
 */
public class EmailSettingNames {

	private String EmailSettings = "Fusion.Pim.Email";

	public EmailSettingNames(){

	}

	public void finalize() throws Throwable {

	}

	public String getEmailSettings(){
		return EmailSettings;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEmailSettings(String newVal){
		EmailSettings = newVal;
	}

}