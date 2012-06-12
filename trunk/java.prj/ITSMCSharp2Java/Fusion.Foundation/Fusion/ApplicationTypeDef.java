package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:41
 */
public class ApplicationTypeDef extends DefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:41
	 */
	private class Tags {

		private String ApplicationTypeDef = "ApplicationTypeDef";
		private String AuthenticationProcedureDefRef = "AuthenticationProcedureDefRef";
		private String AuthenticationProcedureName = "AuthenticationProcedureName";
		private String AuthorizationProcedureDefRef = "AuthorizationProcedureDefRef";
		private String AuthorizationProcedureName = "AuthorizationProcedureName";
		private String ClassName = "ApplicationTypeDef";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getApplicationTypeDef(){
			return ApplicationTypeDef;
		}

		public String getAuthenticationProcedureDefRef(){
			return AuthenticationProcedureDefRef;
		}

		public String getAuthenticationProcedureName(){
			return AuthenticationProcedureName;
		}

		public String getAuthorizationProcedureDefRef(){
			return AuthorizationProcedureDefRef;
		}

		public String getAuthorizationProcedureName(){
			return AuthorizationProcedureName;
		}

		public String getClassName(){
			return ClassName;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setApplicationTypeDef(String newVal){
			ApplicationTypeDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAuthenticationProcedureDefRef(String newVal){
			AuthenticationProcedureDefRef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAuthenticationProcedureName(String newVal){
			AuthenticationProcedureName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAuthorizationProcedureDefRef(String newVal){
			AuthorizationProcedureDefRef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAuthorizationProcedureName(String newVal){
			AuthorizationProcedureName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setClassName(String newVal){
			ClassName = newVal;
		}

	}

	private String AdminApplicationType = "Admin";
	private String DefaultApplicationType = "User";
	private String m_strAuthenticationProcedureName = "";
	private String m_strAuthorizationProcedureName = "";
	private String SelfServiceApplicationType = "SelfService";
	private String SmartClientApplicationType = "SmartClient";
	private String WebApplicationType = "Web";



	public void finalize() throws Throwable {
		super.finalize();
	}

	public ApplicationTypeDef(){

	}

	public String AuthenticationProcedureName(){
		return "";
	}

	public String AuthorizationProcedureName(){
		return "";
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

	public static ApplicationTypeDef Create(){
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

	public String getAdminApplicationType(){
		return AdminApplicationType;
	}

	public String getDefaultApplicationType(){
		return DefaultApplicationType;
	}

	public String getSelfServiceApplicationType(){
		return SelfServiceApplicationType;
	}

	public String getSmartClientApplicationType(){
		return SmartClientApplicationType;
	}

	public String getWebApplicationType(){
		return WebApplicationType;
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
	 * @param newVal
	 */
	public void setAdminApplicationType(String newVal){
		AdminApplicationType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDefaultApplicationType(String newVal){
		DefaultApplicationType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSelfServiceApplicationType(String newVal){
		SelfServiceApplicationType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSmartClientApplicationType(String newVal){
		SmartClientApplicationType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setWebApplicationType(String newVal){
		WebApplicationType = newVal;
	}

	public String ToString(){
		return "";
	}

}