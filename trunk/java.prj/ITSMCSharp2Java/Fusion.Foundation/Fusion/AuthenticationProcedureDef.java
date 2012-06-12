package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:41
 */
public class AuthenticationProcedureDef extends DefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:41
	 */
	private class Tags {

		private String AuthenticationProcedureDef = "AuthenticationProcedureDef";
		private String AuthenticationProvider = "AuthenticationProvider";
		private String AuthenticationProviders = "AuthenticationProviders";
		private String ClassName = "AuthenticationProcedureDef";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAuthenticationProcedureDef(){
			return AuthenticationProcedureDef;
		}

		public String getAuthenticationProvider(){
			return AuthenticationProvider;
		}

		public String getAuthenticationProviders(){
			return AuthenticationProviders;
		}

		public String getClassName(){
			return ClassName;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAuthenticationProcedureDef(String newVal){
			AuthenticationProcedureDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAuthenticationProvider(String newVal){
			AuthenticationProvider = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAuthenticationProviders(String newVal){
			AuthenticationProviders = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setClassName(String newVal){
			ClassName = newVal;
		}

	}

	private String InternalLogonProc = "Internal";
	private ArrayList m_alAuthProviders = new ArrayList();
	private String PubCookiesLogonProc = "PubCookies";



	public void finalize() throws Throwable {
		super.finalize();
	}

	public AuthenticationProcedureDef(){

	}

	public List AuthenticationProviders(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param def
	 * @param defOwner
	 */
	protected void CopyContents(SerializableDef def, SerializableDef defOwner){

	}

	public static AuthenticationProcedureDef Create(){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	/**
	 * 
	 * @param serial
	 * @param defParent
	 */
	public static SerializableDef DeserializeCreate(DefSerializer serial, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strSubType
	 */
	public static IDefinition DeserializeCreateNewForEditing(String strSubType){
		return null;
	}

	public String getInternalLogonProc(){
		return InternalLogonProc;
	}

	public String getPubCookiesLogonProc(){
		return PubCookiesLogonProc;
	}

	/**
	 * 
	 * @param provider
	 */
	public boolean HasAuthProvider(IAuthenticationProvider provider){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public DefSerializer Serialize(DefSerializer serial){
		return null;
	}

	public String SerializeClassName(){
		return "";
	}

	public String SerializeGeneralPropertyRoot(){
		return "";
	}

	/**
	 * 
	 * @param authProviders
	 */
	public void SetAuthProviders(List authProviders){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setInternalLogonProc(String newVal){
		InternalLogonProc = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPubCookiesLogonProc(String newVal){
		PubCookiesLogonProc = newVal;
	}

	public String ToString(){
		return "";
	}

}