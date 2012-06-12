package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-四月-2010 10:50:26
 */
public class MetaDbHint extends DbHint {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 21-四月-2010 10:50:26
	 */
	private class Tags {

		private String Content = "Content";
		private String MetaHintDetails = "MetaHintDetails";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getContent(){
			return Content;
		}

		public String getMetaHintDetails(){
			return MetaHintDetails;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setContent(String newVal){
			Content = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMetaHintDetails(String newVal){
			MetaHintDetails = newVal;
		}

	}

	private String DataType = "DataType";
	private String DefaultValue = "DefaultValue";
	private String FixedWidth = "FixedWidth";
	private String m_strContent;
	private String NullAllowed = "NullAllowed";
	private String PreferredDataType = "PreferredDataType";
	private String Unique = "Unique";
	private String UseUnicode = "UseUnicode";

	public MetaDbHint(){

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
	public MetaDbHint(DefinitionObject defParent, String strDatabaseEngine, String strDatabaseVersion){

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

	public String Content(){
		return "";
	}

	/**
	 * 
	 * @param hint
	 */
	protected void CopyContents(DbHint hint){

	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public String getDataType(){
		return DataType;
	}

	public String getDefaultValue(){
		return DefaultValue;
	}

	public String getFixedWidth(){
		return FixedWidth;
	}

	public String getNullAllowed(){
		return NullAllowed;
	}

	public String getPreferredDataType(){
		return PreferredDataType;
	}

	public String getUnique(){
		return Unique;
	}

	public String getUseUnicode(){
		return UseUnicode;
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
	 * @param newVal
	 */
	public void setDataType(String newVal){
		DataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDefaultValue(String newVal){
		DefaultValue = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFixedWidth(String newVal){
		FixedWidth = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNullAllowed(String newVal){
		NullAllowed = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPreferredDataType(String newVal){
		PreferredDataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUnique(String newVal){
		Unique = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUseUnicode(String newVal){
		UseUnicode = newVal;
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