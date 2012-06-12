package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-四月-2010 10:50:17
 */
public class CustomProcedureDbHint extends DbHint {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 21-四月-2010 10:50:17
	 */
	private class Tags {

		private String CreateCommand = "CreateCommand";
		private String CustomProcedure = "CustomProcedure";
		private String CustomProcedureHintDetails = "CustomProcedureHintDetails";
		private String CustomProcedureRef = "CustomProcedureRef";
		private String DropCommand = "DropCommand";
		private String Hint = "Hint";
		private String ProcType = "ProcType";
		private String URL = "URL";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getCreateCommand(){
			return CreateCommand;
		}

		public String getCustomProcedure(){
			return CustomProcedure;
		}

		public String getCustomProcedureHintDetails(){
			return CustomProcedureHintDetails;
		}

		public String getCustomProcedureRef(){
			return CustomProcedureRef;
		}

		public String getDropCommand(){
			return DropCommand;
		}

		public String getHint(){
			return Hint;
		}

		public String getProcType(){
			return ProcType;
		}

		public String getURL(){
			return URL;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCreateCommand(String newVal){
			CreateCommand = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCustomProcedure(String newVal){
			CustomProcedure = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCustomProcedureHintDetails(String newVal){
			CustomProcedureHintDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCustomProcedureRef(String newVal){
			CustomProcedureRef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDropCommand(String newVal){
			DropCommand = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setHint(String newVal){
			Hint = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setProcType(String newVal){
			ProcType = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setURL(String newVal){
			URL = newVal;
		}

	}

	private CustomProcedureType m_eTypeCustomProc;
	private String m_strCreateCommand;
	private String m_strDropCommand;
	private String m_strRef;

	public CustomProcedureDbHint(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param defParent
	 * @param strDatabaseEngine
	 * @param strDatabaseVersion
	 */
	public CustomProcedureDbHint(DefinitionObject defParent, String strDatabaseEngine, String strDatabaseVersion){

	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param defParent
	 */
	public DbHint Clone(DefinitionObject defParent){
		return null;
	}

	/**
	 * 
	 * @param defParent
	 */
	public DbHint CloneForEdit(DefinitionObject defParent){
		return null;
	}

	/**
	 * 
	 * @param hint
	 */
	public boolean Compare(DbHint hint){
		return null;
	}

	/**
	 * 
	 * @param hint
	 */
	protected void CopyContents(DbHint hint){

	}

	public String CreateCommand(){
		return "";
	}

	/**
	 * 
	 * @param eTypeCustProc
	 */
	private String CustomProcedureTypeToString(CustomProcedureType eTypeCustProc){
		return "";
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public String DropCommand(){
		return "";
	}

	public String ProcedureReference(){
		return "";
	}

	public CustomProcedureType ProcedureType(){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param parentDef
	 */
	public void ReportConflicts(DefinitionObject def, DefinitionObject parentDef){

	}

	/**
	 * 
	 * @param serial
	 */
	public DefSerializer Serialize(DefSerializer serial){
		return null;
	}

	public String SerializeSpecificPropertyRoot(){
		return "";
	}

	/**
	 * 
	 * @param strProcType
	 */
	private CustomProcedureType StringToCustomProcedureType(String strProcType){
		return null;
	}

	/**
	 * 
	 * @param defHoldersParent
	 * @param dbValInfo
	 * @param colColumnNames
	 * @param dictDbNames
	 */
	public boolean Validate(DefinitionObject defHoldersParent, DbValidationInfo dbValInfo, List colColumnNames, Map dictDbNames){
		return null;
	}

}