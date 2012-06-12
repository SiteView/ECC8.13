package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:42
 */
public class AuthorizationProcedureDef extends DefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:42
	 */
	private class Tags {

		private String AuthorizationProcedureDef = "AuthorizationProcedureDef";
		private String AuthorizationProvider = "AuthorizationProvider";
		private String AuthorizationProviders = "AuthorizationProviders";
		private String ClassName = "AuthorizationProcedureDef";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAuthorizationProcedureDef(){
			return AuthorizationProcedureDef;
		}

		public String getAuthorizationProvider(){
			return AuthorizationProvider;
		}

		public String getAuthorizationProviders(){
			return AuthorizationProviders;
		}

		public String getClassName(){
			return ClassName;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAuthorizationProcedureDef(String newVal){
			AuthorizationProcedureDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAuthorizationProvider(String newVal){
			AuthorizationProvider = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAuthorizationProviders(String newVal){
			AuthorizationProviders = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setClassName(String newVal){
			ClassName = newVal;
		}

	}

	private ArrayList m_alAuthProviders = null;
	private String m_sProviders = "";



	public void finalize() throws Throwable {
		super.finalize();
	}

	public AuthorizationProcedureDef(){

	}

	public ArrayList AuthorizationProviders(){
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

	public static AuthorizationProcedureDef Create(){
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

	/**
	 * 
	 * @param authProvider
	 */
	public boolean HasAuthProvider(IAuthorizationProvider authProvider){
		return null;
	}

	/**
	 * 
	 * @param authName
	 */
	private boolean HasAuthProviderInXml(String authName){
		return null;
	}

	public String ProvidersXml(){
		return "";
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
	 * @param authProviders
	 */
	public void SetAuthProvidersInXml(List authProviders){

	}

	public String ToString(){
		return "";
	}

}