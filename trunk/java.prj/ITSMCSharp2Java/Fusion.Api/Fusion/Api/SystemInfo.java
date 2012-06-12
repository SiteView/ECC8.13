package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:44
 */
public class SystemInfo implements ISystemInfo {

	private IOrchestrator m_orch = null;
	private String m_strConnectionName = "";

	public SystemInfo(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param orch
	 * @param strConnectionName
	 */
	public SystemInfo(IOrchestrator orch, String strConnectionName){

	}

	public String ConnectionDisplayName(){
		return "";
	}

	public String ConnectionName(){
		return "";
	}

	public String CurrentLoginId(){
		return "";
	}

	public String CurrentUserName(){
		return "";
	}

	public String LicenseName(){
		return "";
	}

	public String SerialNumber(){
		return "";
	}

	public String Version(){
		return "";
	}

	public String VerticalName(){
		return "";
	}

	public String VerticalVersion(){
		return "";
	}

}