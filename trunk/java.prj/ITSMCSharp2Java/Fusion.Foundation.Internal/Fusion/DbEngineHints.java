package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-四月-2010 10:50:19
 */
public class DbEngineHints extends SerializableDef implements IAggregate {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 21-四月-2010 10:50:19
	 */
	private class Tags {

		private String DbEngine = "DbEngine";
		private String DbVersion = "DbVersion";
		private String FieldDbHints = "FieldDbHints";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getDbEngine(){
			return DbEngine;
		}

		public String getDbVersion(){
			return DbVersion;
		}

		public String getFieldDbHints(){
			return FieldDbHints;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDbEngine(String newVal){
			DbEngine = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDbVersion(String newVal){
			DbVersion = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFieldDbHints(String newVal){
			FieldDbHints = newVal;
		}

	}

	private AggregateBase m_aggregate = null;
	private DefinitionObject m_defParent = null;
	private Hashtable m_htDbHint = new Hashtable();
	private String m_strDatabaseVersion;
	private String m_strEngine;
	private String m_strXmlTag;

	public DbEngineHints(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param defParent
	 */
	public DbEngineHints(DefinitionObject defParent){

	}

	/**
	 * 
	 * @param strName
	 * @param strDropCommand
	 * @param strCreateCommand
	 * @param eCustProcType
	 */
	public CustomProcedureDbHint AddCustomProcedureDbHint(String strName, String strDropCommand, String strCreateCommand, CustomProcedureType eCustProcType){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strRef
	 * @param eCustProcType
	 */
	public CustomProcedureDbHint AddCustomProcedureRefDbHint(String strName, String strRef, CustomProcedureType eCustProcType){
		return null;
	}

	/**
	 * 
	 * @param hint
	 */
	public void AddDbHint(DbHint hint){

	}

	/**
	 * 
	 * @param hints
	 */
	public void AddDbHints(DbEngineHints hints){

	}

	/**
	 * 
	 * @param strId
	 * @param hint
	 */
	private void AddDbHintWithProperEditMode(String strId, DbHint hint){

	}

	/**
	 * 
	 * @param strName
	 * @param strTableFkReferences
	 */
	public KeyDbHint AddForeignKeyDbHint(String strName, String strTableFkReferences){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strTableFkReferences
	 * @param colKeyColumns
	 */
	public KeyDbHint AddForeignKeyDbHint(String strName, String strTableFkReferences, KeyColumnCollection colKeyColumns){
		return null;
	}

	/**
	 * 
	 * @param strIndexName
	 * @param bUnique
	 */
	public IndexDbHint AddIndexDbHint(String strIndexName, boolean bUnique){
		return null;
	}

	/**
	 * 
	 * @param strIndexName
	 * @param bUnique
	 * @param colIndexColumns
	 */
	public IndexDbHint AddIndexDbHint(String strIndexName, boolean bUnique, IndexColumnCollection colIndexColumns){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strContent
	 */
	public MetaDbHint AddMetaDbHint(String strName, String strContent){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public KeyDbHint AddPrimaryKeyDbHint(String strName){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param colKeyColumns
	 */
	public KeyDbHint AddPrimaryKeyDbHint(String strName, KeyColumnCollection colKeyColumns){
		return null;
	}

	public AggregateBase Aggregate(){
		return null;
	}

	public String AggregateClassName(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param defParent
	 */
	public DbEngineHints Clone(DefinitionObject defParent){
		return null;
	}

	/**
	 * 
	 * @param defToCompare
	 * @param ci
	 */
	public void CompareContents(SerializableDef defToCompare, CompareInfo ci){

	}

	/**
	 * 
	 * @param hints
	 */
	public void CopyContents(DbEngineHints hints){

	}

	/**
	 * 
	 * @param strDbHintsXmlTag
	 * @param strEngine
	 * @param strVersion
	 * @param defParent
	 */
	public static DbEngineHints Create(String strDbHintsXmlTag, String strEngine, String strVersion, DefinitionObject defParent){
		return null;
	}

	/**
	 * 
	 * @param factory
	 */
	public AggregateBase CreateAggregate(IAggregateFactory factory){
		return null;
	}

	public String DatabaseEngine(){
		return "";
	}

	public String DatabaseVersion(){
		return "";
	}

	public List DbHintCollection(){
		return null;
	}

	public String DbHintsXmlTag(){
		return "";
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

	public boolean EditMode(){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public CustomProcedureDbHint GetCustomProcedureDbHintById(String strId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public CustomProcedureDbHint GetCustomProcedureDbHintByName(String strName){
		return null;
	}

	public List GetCustomProcedureDbHints(){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public DbHint GetDbHintById(String strId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public DbHint GetDbHintByName(String strName){
		return null;
	}

	public List GetForeignKeyDbHints(){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public IndexDbHint GetIndexDbHintById(String strId){
		return null;
	}

	/**
	 * 
	 * @param strIndexName
	 */
	public IndexDbHint GetIndexDbHintByName(String strIndexName){
		return null;
	}

	public List GetIndexDbHints(){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public KeyDbHint GetKeyDbHintById(String strId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public KeyDbHint GetKeyDbHintByName(String strName){
		return null;
	}

	public List GetKeyDbHints(){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public MetaDbHint GetMetaDbHintById(String strId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public MetaDbHint GetMetaDbHintByName(String strName){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public String GetMetaDbHintContentById(String strId){
		return "";
	}

	/**
	 * 
	 * @param strId
	 * @param bDefault
	 */
	public boolean GetMetaDbHintContentByIdAsBool(String strId, boolean bDefault){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public String GetMetaDbHintContentByName(String strName){
		return "";
	}

	/**
	 * 
	 * @param strName
	 * @param bDefault
	 */
	public boolean GetMetaDbHintContentByNameAsBool(String strName, boolean bDefault){
		return null;
	}

	public List GetMetaDbHints(){
		return null;
	}

	public KeyDbHint GetPrimaryKeyDbHint(){
		return null;
	}

	/**
	 * 
	 * @param strField
	 */
	public boolean IsFieldPrimaryKey(String strField){
		return null;
	}

	public DefinitionObject ParentDef(){
		return null;
	}

	public void RemoveAllDbHints(){

	}

	/**
	 * 
	 * @param hint
	 */
	public void RemoveDbHint(DbHint hint){

	}

	/**
	 * 
	 * @param strId
	 */
	public void RemoveDbHintById(String strId){

	}

	/**
	 * 
	 * @param strName
	 */
	public void RemoveDbHintByName(String strName){

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

	public String SerializeClassName(){
		return "";
	}

	public String SerializeGeneralPropertyRoot(){
		return "";
	}

	private void SetEditModeOnHints(){

	}

	/**
	 * 
	 * @param defHoldersParent
	 * @param colColumnNames
	 * @param dictDbNames
	 */
	public boolean Validate(DefinitionObject defHoldersParent, List colColumnNames, Map dictDbNames){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param parentDef
	 */
	public void ValidateAllHintsAreForField(DefinitionObject def, DefinitionObject parentDef){

	}

	/**
	 * 
	 * @param def
	 * @param parentDef
	 */
	public void ValidateAllHintsAreForFieldDefContainer(DefinitionObject def, DefinitionObject parentDef){

	}

}