package Fusion;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.Map;

import Fusion.Foundation.CompareInfo;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:20
 */
public class DbHintManager implements IAggregate {

	private String ALL_ENGINES_KEY = "ALLENGINES";
	private AggregateBase m_aggregate = null;
	private ArrayList m_alDbEngineHints = null;
	private boolean m_bEditMode = false;
	private DefinitionObject m_defParent = null;
	private Hashtable m_htEngineToHintsCollection = new Hashtable();
	private String m_strDbHintsXmlTag;

	public DbHintManager(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strDbHintsXmlTag
	 * @param alDbEngineHints
	 * @param defParent
	 */
	protected DbHintManager(String strDbHintsXmlTag, ArrayList alDbEngineHints, DefinitionObject defParent){

	}

	/**
	 * 
	 * @param strName
	 * @param strDropCommand
	 * @param strCreateCommand
	 * @param eCustProcType
	 * @param strEngine
	 * @param strVersion
	 */
	public CustomProcedureDbHint AddCustomProcedureDbHint(String strName, String strDropCommand, String strCreateCommand, CustomProcedureType eCustProcType, String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strRef
	 * @param eCustProcType
	 * @param strEngine
	 * @param strVersion
	 */
	public CustomProcedureDbHint AddCustomProcedureRefDbHint(String strName, String strRef, CustomProcedureType eCustProcType, String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strKey
	 * @param hints
	 */
	private void AddDbEngineHintsToCollections(String strKey, DbEngineHints hints){

	}

	/**
	 * 
	 * @param strEngine
	 * @param strVersion
	 * @param hints
	 */
	private void AddDbEngineHintsToCollections(String strEngine, String strVersion, DbEngineHints hints){

	}

	/**
	 * 
	 * @param hint
	 */
	public void AddDbHint(DbHint hint){

	}

	/**
	 * 
	 * @param strName
	 * @param strTableFkReferences
	 * @param strEngine
	 * @param strVersion
	 */
	public KeyDbHint AddForeignKeyDbHint(String strName, String strTableFkReferences, String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strTableFkReferences
	 * @param colKeyColumns
	 * @param strEngine
	 * @param strVersion
	 */
	public KeyDbHint AddForeignKeyDbHint(String strName, String strTableFkReferences, KeyColumnCollection colKeyColumns, String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param mgrHints
	 */
	public void AddHints(DbHintManager mgrHints){

	}

	/**
	 * 
	 * @param strIndexName
	 * @param bUnique
	 * @param strEngine
	 * @param strVersion
	 */
	public IndexDbHint AddIndexDbHint(String strIndexName, boolean bUnique, String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strIndexName
	 * @param bUnique
	 * @param colIndexColumns
	 * @param strEngine
	 * @param strVersion
	 */
	public IndexDbHint AddIndexDbHint(String strIndexName, boolean bUnique, IndexColumnCollection colIndexColumns, String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strContent
	 * @param strEngine
	 * @param strVersion
	 */
	public MetaDbHint AddMetaDbHint(String strName, String strContent, String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strEngine
	 * @param strVersion
	 */
	public KeyDbHint AddPrimaryKeyDbHint(String strName, String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param colKeyColumns
	 * @param strEngine
	 * @param strVersion
	 */
	public KeyDbHint AddPrimaryKeyDbHint(String strName, KeyColumnCollection colKeyColumns, String strEngine, String strVersion){
		return null;
	}

	public AggregateBase Aggregate(){
		return null;
	}

	public String AggregateClassName(){
		return "";
	}

	/**
	 * 
	 * @param strDesiredHintName
	 * @param strDesiredValue
	 * @param defFieldContainer
	 * @param defField
	 */
	public void CheckForMetaDbHint(String strDesiredHintName, String strDesiredValue, DefinitionObject defFieldContainer, DefinitionObject defField){

	}

	private void ClearCollections(){

	}

	/**
	 * 
	 * @param defParent
	 */
	public DbHintManager Clone(DefinitionObject defParent){
		return null;
	}

	/**
	 * 
	 * @param mgrHintsToCompare
	 * @param ciParent
	 */
	public void CompareContents(DbHintManager mgrHintsToCompare, CompareInfo ciParent){

	}

	/**
	 * 
	 * @param strId
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public boolean ContainsMetaDbHintForId(String strId, String strEngine, String strVersion, boolean bExactEngineVersion){
		return false;
	}

	/**
	 * 
	 * @param strName
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public boolean ContainsMetaDbHintForName(String strName, String strEngine, String strVersion, boolean bExactEngineVersion){
		return false;
	}

	/**
	 * 
	 * @param mgrHints
	 */
	public void CopyContents(DbHintManager mgrHints){

	}

	/**
	 * 
	 * @param strDbHintsXmlTag
	 * @param alDbEngineHints
	 * @param defParent
	 */
	public static DbHintManager Create(String strDbHintsXmlTag, ArrayList alDbEngineHints, DefinitionObject defParent){
		return null;
	}

	/**
	 * 
	 * @param factory
	 */
	public AggregateBase CreateAggregate(IAggregateFactory factory){
		return null;
	}

	/**
	 * 
	 * @param strEngine
	 * @param strVersion
	 */
	private DbEngineHints CreateDbEngineHints(String strEngine, String strVersion){
		return null;
	}

	public List DbEngineHintsCollection(){
		return null;
	}

	/**
	 * 
	 * @param colHints
	 */
	public void DeleteDbHints(List colHints){

	}

	public boolean EditMode(){
		return false;
	}

	/**
	 * 
	 * @param strEngine
	 */
	public List GetAllDbHintsForEngine(String strEngine){
		return null;
	}

	/**
	 * 
	 * @param strEngine
	 * @param catHint
	 */
	public List GetAllDbHintsForEngine(String strEngine, DbHintCategory catHint){
		return null;
	}

	/**
	 * 
	 * @param strId
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public CustomProcedureDbHint GetCustomProcedureDbHintById(String strId, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public CustomProcedureDbHint GetCustomProcedureDbHintByName(String strName, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param engine
	 * @param strVersion
	 */
	public DbEngineHints GetDbHintsForClosestEngineVersion(DatabaseEngine engine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strEngine
	 * @param strVersion
	 */
	public DbEngineHints GetDbHintsForClosestEngineVersion(String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param engine
	 * @param strVersion
	 */
	public DbEngineHints GetDbHintsForExactEngineVersion(DatabaseEngine engine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strEngine
	 * @param strVersion
	 */
	public DbEngineHints GetDbHintsForExactEngineVersion(String strEngine, String strVersion){
		return null;
	}

	public DbEngineHints GetDefaultDbHintsCollection(){
		return null;
	}

	/**
	 * 
	 * @param strEngine
	 * @param strVersion
	 */
	private String GetEngineToHintsCollectionKey(String strEngine, String strVersion){
		return "";
	}

	/**
	 * 
	 * @param strEngine
	 * @param strVersion
	 */
	public List GetForeignKeyDbHints(String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strId
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public IndexDbHint GetIndexDbHintById(String strId, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param strIndexName
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public IndexDbHint GetIndexDbHintByName(String strIndexName, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param strId
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public KeyDbHint GetKeyDbHintById(String strId, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public KeyDbHint GetKeyDbHintByName(String strName, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param strId
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public MetaDbHint GetMetaDbHintById(String strId, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public MetaDbHint GetMetaDbHintByName(String strName, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 * @param bDefaultIfNotFound
	 */
	public boolean GetMetaDbHintContentAsBool(String strName, String strEngine, String strVersion, boolean bExactEngineVersion, boolean bDefaultIfNotFound){
		return false;
	}

	/**
	 * 
	 * @param strId
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public String GetMetaDbHintContentById(String strId, String strEngine, String strVersion, boolean bExactEngineVersion){
		return "";
	}

	/**
	 * 
	 * @param strName
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public String GetMetaDbHintContentByName(String strName, String strEngine, String strVersion, boolean bExactEngineVersion){
		return "";
	}

	/**
	 * 
	 * @param hints
	 */
	private String GetStringForEngineVersion(DbEngineHints hints){
		return "";
	}

	/**
	 * 
	 * @param strField
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public boolean IsFieldPrimaryKey(String strField, String strEngine, String strVersion, boolean bExactEngineVersion){
		return false;
	}

	public DefinitionObject ParentDef(){
		return null;
	}

	/**
	 * 
	 * @param strEngine
	 * @param strVersion
	 */
	public void RemoveAllDbHints(String strEngine, String strVersion){

	}

	/**
	 * 
	 * @param hint
	 * @param strEngine
	 * @param strVersion
	 */
	public void RemoveDbHint(DbHint hint, String strEngine, String strVersion){

	}

	/**
	 * 
	 * @param strId
	 * @param strEngine
	 * @param strVersion
	 */
	public void RemoveDbHintById(String strId, String strEngine, String strVersion){

	}

	/**
	 * 
	 * @param strName
	 * @param strEngine
	 * @param strVersion
	 */
	public void RemoveDbHintByName(String strName, String strEngine, String strVersion){

	}

	/**
	 * 
	 * @param def
	 * @param defParent
	 */
	public void ReportConflicts(DefinitionObject def, DefinitionObject defParent){

	}

	private void SetEditModeOnHints(){

	}

	/**
	 * 
	 * @param colHints
	 */
	public void UpdateDbHints(List colHints){

	}

	/**
	 * 
	 * @param colHintsUpdate
	 * @param colHintsDelete
	 */
	public void UpdateDbHints(List colHintsUpdate, List colHintsDelete){

	}

	/**
	 * 
	 * @param defHoldersParent
	 * @param colColumnNames
	 * @param dictDbNames
	 */
	public boolean Validate(DefinitionObject defHoldersParent, List colColumnNames, Map dictDbNames){
		return false;
	}

	/**
	 * 
	 * @param def
	 * @param defParent
	 * @param colColumnNames
	 * @param dss
	 */
	public void ValidateAllHintsAreForField(DefinitionObject def, DefinitionObject defParent, List colColumnNames, IDataStoreService dss){

	}

	/**
	 * 
	 * @param def
	 * @param defParent
	 * @param colColumnNames
	 * @param dss
	 */
	public void ValidateAllHintsAreForFieldDefContainer(DefinitionObject def, DefinitionObject defParent, List colColumnNames, IDataStoreService dss){

	}

	/**
	 * 
	 * @param def
	 * @param defParent
	 * @param colColumnNames
	 * @param dictDbNames
	 */
	public void ValidateHintsForField(DefinitionObject def, DefinitionObject defParent, List colColumnNames, Map dictDbNames){

	}

	/**
	 * 
	 * @param def
	 * @param defParent
	 * @param colColumnNames
	 * @param dictDbNames
	 */
	public void ValidateHintsForFieldDefContainer(DefinitionObject def, DefinitionObject defParent, List colColumnNames, Map dictDbNames){

	}

	/**
	 * 
	 * @param defHoldersParent
	 */
	public void ValidateTableHasPrimaryKey(DefinitionObject defHoldersParent){

	}

}