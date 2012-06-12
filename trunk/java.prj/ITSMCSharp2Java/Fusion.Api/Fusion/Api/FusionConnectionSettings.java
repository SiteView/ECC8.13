package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:39
 */
public class FusionConnectionSettings extends MarshalByRefObject {

	private String m_connectionHostName;
	private String m_connectionName;
	private String m_connectionPort;
	private String m_logLevel;
	private String m_password;
	private String m_userName;

	public FusionConnectionSettings(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ConnectionName(){
		return "";
	}

	public String HostName(){
		return "";
	}

	public String LogLevel(){
		return "";
	}

	public String Password(){
		return "";
	}

	public String Port(){
		return "";
	}

	public String UserName(){
		return "";
	}

}