package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:53
 */
public class DbHintManager extends FusionAggregate {

	public DbHintManager(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public DbHintManager(Object fusionObject){

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
	public Fusion.Api.DbHint AddCustomProcedureDbHint(String strName, String strDropCommand, String strCreateCommand, CustomProcedureType eCustProcType, String strEngine, String strVersion){
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
	public Fusion.Api.DbHint AddCustomProcedureRefDbHint(String strName, String strRef, CustomProcedureType eCustProcType, String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param hint
	 */
	public void AddDbHint(Fusion.Api.DbHint hint){

	}

	/**
	 * 
	 * @param strName
	 * @param strTableFkReferences
	 * @param strEngine
	 * @param strVersion
	 */
	public Fusion.Api.DbHint AddForeignKeyDbHint(String strName, String strTableFkReferences, String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strIndexName
	 * @param bUnique
	 * @param strEngine
	 * @param strVersion
	 */
	public Fusion.Api.DbHint AddIndexDbHint(String strIndexName, boolean bUnique, String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strContent
	 * @param strEngine
	 * @param strVersion
	 */
	public Fusion.Api.DbHint AddMetaDbHint(String strName, String strContent, String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strEngine
	 * @param strVersion
	 */
	public Fusion.Api.DbHint AddPrimaryKeyDbHint(String strName, String strEngine, String strVersion){
		return null;
	}

	private void CheckChangeRights(){

	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param strId
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public boolean ContainsMetaDbHintForId(String strId, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public boolean ContainsMetaDbHintForName(String strName, String strEngine, String strVersion, boolean bExactEngineVersion){
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
	public Fusion.Api.DbHint GetCustomProcedureDbHintById(String strId, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public Fusion.Api.DbHint GetCustomProcedureDbHintByName(String strName, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param engine
	 * @param strVersion
	 */
	public Fusion.Api.DbEngineHints GetDbHintsForClosestEngineVersion(DatabaseEngine engine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strEngine
	 * @param strVersion
	 */
	public Fusion.Api.DbEngineHints GetDbHintsForClosestEngineVersion(String strEngine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param engine
	 * @param strVersion
	 */
	public Fusion.Api.DbEngineHints GetDbHintsForExactEngineVersion(DatabaseEngine engine, String strVersion){
		return null;
	}

	/**
	 * 
	 * @param strEngine
	 * @param strVersion
	 */
	public Fusion.Api.DbEngineHints GetDbHintsForExactEngineVersion(String strEngine, String strVersion){
		return null;
	}

	public Fusion.Api.DbEngineHints GetDefaultDbHintsCollection(){
		return null;
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
	public Fusion.Api.DbHint GetIndexDbHintById(String strId, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param strIndexName
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public Fusion.Api.DbHint GetIndexDbHintByName(String strIndexName, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param strId
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public Fusion.Api.DbHint GetKeyDbHintById(String strId, String strEngine, String strVersion, boolean bExactEngineVersion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public Fusion.Api.DbHint GetKeyDbHintByName(String strName, String strEngine, String strVersion, boolean bExactEngineVersion){
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
	public boolean GetMetaDbHintContentAsboolean(String strName, String strEngine, String strVersion, boolean bExactEngineVersion, boolean bDefaultIfNotFound){
		return null;
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
	 * @param strField
	 * @param strEngine
	 * @param strVersion
	 * @param bExactEngineVersion
	 */
	public boolean IsFieldPrimaryKey(String strField, String strEngine, String strVersion, boolean bExactEngineVersion){
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
	public void RemoveDbHint(Fusion.Api.DbHint hint, String strEngine, String strVersion){

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
	 * @param colAggregateHints
	 */
	private List UnaggregateHintCollection(List colAggregateHints){
		return null;
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

	private Fusion.DbHintManager WhoAmI(){
		return null;
	}

}