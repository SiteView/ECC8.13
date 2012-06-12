package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:38
 */
public class FusionConnection {

	private static FusionConnection instance;
	private String m_connection;
	private IFusionApi m_fusionAPI;
	private String m_password;
	private String m_strToken;
	private String m_userName;
	private String m_userType = "User";
	private static final Object padlock = new object();

	public FusionConnection(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param fusionAPI
	 */
	private FusionConnection(IFusionApi fusionAPI){

	}

	/**
	 * 
	 * @param connection
	 * @param userName
	 * @param password
	 */
	private FusionConnection(String connection, String userName, String password){

	}

	public static void DestroyInstance(){

	}

	public IFusionApi GetAPIHandle(){
		return null;
	}

	/**
	 * 
	 * @param fusionAPI
	 */
	public static FusionConnection GetInstance(IFusionApi fusionAPI){
		return null;
	}

	/**
	 * 
	 * @param connection
	 * @param userName
	 * @param password
	 */
	public static FusionConnection GetInstance(String connection, String userName, String password){
		return null;
	}

	public void LogoutAndDisconnect(){

	}

}