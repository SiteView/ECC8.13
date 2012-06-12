package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:01
 */
public class LDAPAuthenticationProviderDef extends AuthenticationProviderDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:01
	 */
	private class Tags {

		private String DirectoryType = "DirectoryType";
		private String ServerPath = "ServerPath";
		private String UserName = "UserName";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getDirectoryType(){
			return DirectoryType;
		}

		public String getServerPath(){
			return ServerPath;
		}

		public String getUserName(){
			return UserName;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDirectoryType(String newVal){
			DirectoryType = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setServerPath(String newVal){
			ServerPath = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setUserName(String newVal){
			UserName = newVal;
		}

	}

	private Fusion.DirectoryType m_dirType;
	private String m_sServerPath;
	private String m_sUserName;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public LDAPAuthenticationProviderDef(){

	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public Fusion.DirectoryType DirectoryType(){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public DefSerializer Serialize(DefSerializer serial){
		return null;
	}

	public String ServerPath(){
		return "";
	}

	public String ToXml(){
		return "";
	}

	public String UserName(){
		return "";
	}

}