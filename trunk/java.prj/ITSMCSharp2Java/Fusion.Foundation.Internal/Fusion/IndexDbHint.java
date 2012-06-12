package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-四月-2010 10:50:24
 */
public class IndexDbHint extends DbHint {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 21-四月-2010 10:50:24
	 */
	private class Tags {

		private String Content = "Content";
		private String IndexHintDetails = "IndexHintDetails";
		private String Unique = "Unique";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getContent(){
			return Content;
		}

		public String getIndexHintDetails(){
			return IndexHintDetails;
		}

		public String getUnique(){
			return Unique;
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
		public void setIndexHintDetails(String newVal){
			IndexHintDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setUnique(String newVal){
			Unique = newVal;
		}

	}

	private boolean m_bUnique;
	private Fusion.IndexColumnCollection m_colIndexColumns;

	public IndexDbHint(){

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
	public IndexDbHint(DefinitionObject defParent, String strDatabaseEngine, String strDatabaseVersion){

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
	 * @param indexCol1
	 * @param indexCol2
	 */
	private boolean CompareIndexCollections(Fusion.IndexColumnCollection indexCol1, Fusion.IndexColumnCollection indexCol2){
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

	public Fusion.IndexColumnCollection IndexColumnCollection(){
		return null;
	}

	public boolean IsUnique(){
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
	 * @param defHoldersParent
	 * @param dbValInfo
	 * @param colColumnNames
	 * @param dictDbNames
	 */
	public boolean Validate(DefinitionObject defHoldersParent, DbValidationInfo dbValInfo, List colColumnNames, Map dictDbNames){
		return null;
	}

}