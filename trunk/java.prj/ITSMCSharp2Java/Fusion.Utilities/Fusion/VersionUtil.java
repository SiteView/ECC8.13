package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:44
 */
public class VersionUtil {

	private String ClientBuildNumber = "1.1.0.101";
	private String CommonBuildNumber = "1.1.0.101";
	private String ServerBuildNumber = "1.1.0.101";

	public VersionUtil(){

	}

	public void finalize() throws Throwable {

	}

	public String getClientBuildNumber(){
		return ClientBuildNumber;
	}

	public String getCommonBuildNumber(){
		return CommonBuildNumber;
	}

	public String getServerBuildNumber(){
		return ServerBuildNumber;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setClientBuildNumber(String newVal){
		ClientBuildNumber = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCommonBuildNumber(String newVal){
		CommonBuildNumber = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setServerBuildNumber(String newVal){
		ServerBuildNumber = newVal;
	}

}
