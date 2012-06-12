package Fusion.LDAP;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 11:18:26
 */
public class LDAPUtil {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:26
	 */
	public class LDAPInfo {

		private String m_sDirType = "MicrosoftActiveDirectory";
		private String m_strEncryptedPassword = "";
		private String m_strLogLocation = "";
		private String m_strServerPath = "";
		private String m_strUserName = "";

		public LDAPInfo(){

		}

		public void finalize() throws Throwable {

		}

		public String DirType(){
			return "";
		}

		public String EncryptedPassword(){
			return "";
		}

		public String LogLocation(){
			return "";
		}

		public String ServerPath(){
			return "";
		}

		public String UserName(){
			return "";
		}

	}

	private static String DEFAULT_CONFIG = "LDAPInfo.xml";

	public LDAPUtil(){

	}

	public void finalize() throws Throwable {

	}

	public static LDAPInfo LoadLDAPInfo(){
		return null;
	}

	/**
	 * 
	 * @param strFileName
	 */
	public static LDAPInfo LoadLDAPInfo(String strFileName){
		return null;
	}

	/**
	 * 
	 * @param ldapInfo
	 * @param strDomainAndUserName
	 * @param strPassword
	 */
	public static Boolean Login(LDAPInfo ldapInfo, String strDomainAndUserName, String strPassword){
		return null;
	}

}