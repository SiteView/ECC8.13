package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:47
 */
public class User {

	private boolean m_bAllowExternalAuth = false;
	private boolean m_bAllowInternalAuth = false;
	private boolean m_bAllowLDAPAuth = false;
	private boolean m_bAllowPubCookiesAuth = false;
	private boolean m_bLockout = false;
	private boolean m_bTrackPresence = false;
	private boolean m_bUseLDAP = false;
	private DateTime m_dtLastLogin = DateTime.Now;
	private DateTime m_dtLastModDateTime = DateTime.Now;
	private IUserInfo m_ExternalUserInfo = null;
	private Hashtable m_htOtherExternalUserInfos = new Hashtable();
	private IUserInfo m_InternalUserInfo = null;
	private String m_strBusObId = "";
	private String m_strBusObName = "";
	private String m_strBusUnitDefId = "";
	private String m_strGroupId = "";
	private String m_strGroupName = "";
	private String m_strLastModUser = "";
	private String m_strLoginId = "";
	private String m_strOldLoginId = "";
	private String m_strUserType = "";

	public User(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strUserType
	 * @param strLoginId
	 */
	public User(String strUserType, String strLoginId){

	}

	public boolean AllowExternalAuthentication(){
		return null;
	}

	public boolean AllowInternalAuthentication(){
		return null;
	}

	public boolean AllowLDAPAuthentication(){
		return null;
	}

	public boolean AllowPubCookiesAuthentication(){
		return null;
	}

	public String BusObId(){
		return "";
	}

	public String BusObName(){
		return "";
	}

	public String BusUnitDefId(){
		return "";
	}

	public IUserInfo ExternalUserInfo(){
		return null;
	}

	/**
	 * 
	 * @param authSource
	 */
	public IUserInfo GetUserInfo(String authSource){
		return null;
	}

	public IUserInfo InternalUserInfo(){
		return null;
	}

	public DateTime LastLogin(){
		return null;
	}

	public DateTime LastModDateTime(){
		return null;
	}

	public String LastModUser(){
		return "";
	}

	public IUserInfo LDAPUserInfo(){
		return null;
	}

	public boolean Lockout(){
		return null;
	}

	public String LoginId(){
		return "";
	}

	public String OriginalLoginId(){
		return "";
	}

	public IUserInfo PubCookiesUserInfo(){
		return null;
	}

	public String SecurityGroupId(){
		return "";
	}

	public String SecurityGroupName(){
		return "";
	}

	/**
	 * 
	 * @param authSource
	 * @param userInfo
	 */
	public void SetUserInfo(String authSource, IUserInfo userInfo){

	}

	public String ToString(){
		return "";
	}

	public boolean TrackPresence(){
		return null;
	}

	public boolean UseLDAP(){
		return null;
	}

	public String UserType(){
		return "";
	}

}