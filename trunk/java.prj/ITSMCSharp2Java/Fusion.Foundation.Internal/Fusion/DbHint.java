package Fusion;

import java.util.List;
import java.util.Map;

import Fusion.Foundation.CompareInfo;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-四月-2010 10:50:20
 */
public abstract class DbHint extends SerializableDef implements IAggregate {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 21-四月-2010 10:50:20
	 */
	private class Tags {

		private String DatabaseEngine = "DatabaseEngine";
		private String DatabaseVersion = "DatabaseVersion";
		private String Description = "Description";
		private String Hint = "Hint";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getDatabaseEngine(){
			return DatabaseEngine;
		}

		public String getDatabaseVersion(){
			return DatabaseVersion;
		}

		public String getDescription(){
			return Description;
		}

		public String getHint(){
			return Hint;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDatabaseEngine(String newVal){
			DatabaseEngine = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDatabaseVersion(String newVal){
			DatabaseVersion = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDescription(String newVal){
			Description = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setHint(String newVal){
			Hint = newVal;
		}

	}

	private AggregateBase m_aggregate = null;
	private DbHintCategory m_dbHintCategory;
	private DefinitionObject m_defParent = null;
	private String m_strDatabaseEngine = "";
	private String m_strDatabaseVersion = "";
	private String m_strDesc = "";

	public DbHint(){

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
	public DbHint(DefinitionObject defParent, String strDatabaseEngine, String strDatabaseVersion){

	}

	public AggregateBase Aggregate(){
		return null;
	}

	public String AggregateClassName(){
		return "";
	}

	public DbHintCategory Category(){
		return null;
	}

	public String CategoryAsString(){
		return "";
	}

	/**
	 * 
	 * @param dbCategory
	 */
	protected static String CategoryToXmlCategory(DbHintCategory dbCategory){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public DbHint Clone(){
		return null;
	}

	/**
	 * 
	 * @param defParent
	 */
	public abstract DbHint Clone(DefinitionObject defParent);

	public DbHint CloneForEdit(){
		return null;
	}

	/**
	 * 
	 * @param defParent
	 */
	public abstract DbHint CloneForEdit(DefinitionObject defParent);

	/**
	 * 
	 * @param hint
	 */
	public boolean Compare(DbHint hint){
		return false;
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
	 * @param category
	 * @param defParent
	 * @param strDatabaseEngine
	 * @param strDatabaseVersion
	 */
	public static DbHint Create(DbHintCategory category, DefinitionObject defParent, String strDatabaseEngine, String strDatabaseVersion){
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

	public String Description(){
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

	public DefinitionObject ParentDef(){
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

	public String SerializeClassName(){
		return "";
	}

	public String SerializeGeneralPropertyRoot(){
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
		return false;
	}

	/**
	 * 
	 * @param strCategory
	 */
	protected static DbHintCategory XmlCategoryToCategory(String strCategory){
		return null;
	}

}