package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:33
 */
public class ServiceRequestEventArgs {

	private Object m_oService = null;
	private String m_strService = "";
	private String UserAgentManager = "UserAgentManager";

	public ServiceRequestEventArgs(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strService
	 */
	public ServiceRequestEventArgs(String strService){

	}

	public String getUserAgentManager(){
		return UserAgentManager;
	}

	public Object Service(){
		return null;
	}

	public String ServiceName(){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUserAgentManager(String newVal){
		UserAgentManager = newVal;
	}

}