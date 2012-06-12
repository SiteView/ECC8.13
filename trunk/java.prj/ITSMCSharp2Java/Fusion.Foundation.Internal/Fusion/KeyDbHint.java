package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-四月-2010 10:50:26
 */
public class KeyDbHint extends DbHint {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 21-四月-2010 10:50:26
	 */
	private class Tags {

		private String Column = "Column";
		private String KeyHintDetails = "KeyHintDetails";
		private String MapTo = "MapTo";
		private String Name = "Name";
		private String Table = "Table";
		private String Type = "Type";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getColumn(){
			return Column;
		}

		public String getKeyHintDetails(){
			return KeyHintDetails;
		}

		public String getMapTo(){
			return MapTo;
		}

		public String getName(){
			return Name;
		}

		public String getTable(){
			return Table;
		}

		public String getType(){
			return Type;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setColumn(String newVal){
			Column = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setKeyHintDetails(String newVal){
			KeyHintDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMapTo(String newVal){
			MapTo = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setName(String newVal){
			Name = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTable(String newVal){
			Table = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setType(String newVal){
			Type = newVal;
		}

	}

	private Fusion.KeyColumnCollection m_colKeyColumns;
	private String m_strTableFkReferences;
	private String m_strType;

	public KeyDbHint(){

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
	public KeyDbHint(DefinitionObject defParent, String strDatabaseEngine, String strDatabaseVersion){

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

	public String ColumnsAsString(){
		return "";
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
	 * @param keyCol1
	 * @param keyCol2
	 */
	private boolean CompareKeyCollections(Fusion.KeyColumnCollection keyCol1, Fusion.KeyColumnCollection keyCol2){
		return null;
	}

	/**
	 * 
	 * @param hint
	 */
	protected void CopyContents(DbHint hint){

	}

	/**
	 * 
	 * @param correction
	 * @param bJustCollect
	 */
	public void CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect){

	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public boolean ForeignKey(){
		return null;
	}

	public String ForeignKeyMapToColumnsAsString(){
		return "";
	}

	/**
	 * 
	 * @param strField
	 */
	public boolean IsFieldPrimaryKey(String strField){
		return null;
	}

	public Fusion.KeyColumnCollection KeyColumnCollection(){
		return null;
	}

	public boolean PrimaryKey(){
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

	public String TableForeignKeyReferences(){
		return "";
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