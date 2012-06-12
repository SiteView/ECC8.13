package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:34
 */
public class FusionServerConfiguration {

	private Fusion.LicenseFrameworkSettings m_licenseFrameworkSettings;
	private static FusionServerConfiguration m_serverConfig;
	private String m_strConnectionName = "";
	private String m_strInstanceId;
	private String m_strSessionId;
	private Fusion.UserSessionManagement m_userSessionManagement;

	public FusionServerConfiguration(){

	}

	public void finalize() throws Throwable {

	}

	public String ConnectionName(){
		return "";
	}

	private static FusionServerConfiguration CreateDefaultInstance(){
		return null;
	}

	private static void InitializeInstance(){

	}

	public static FusionServerConfiguration Instance(){
		return null;
	}

	public String InstanceId(){
		return "";
	}

	public Fusion.LicenseFrameworkSettings LicenseFrameworkSettings(){
		return null;
	}

	public String SessionId(){
		return "";
	}

	public Fusion.UserSessionManagement UserSessionManagement(){
		return null;
	}

}