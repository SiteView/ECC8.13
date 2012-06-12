package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:52
 */
public class DbEngineHints extends FusionAggregate {

	public DbEngineHints(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public DbEngineHints(Object fusionObject){

	}

	/**
	 * 
	 * @param strName
	 * @param strDropCommand
	 * @param strCreateCommand
	 * @param eCustProcType
	 */
	public Fusion.Api.DbHint AddCustomProcedureDbHint(String strName, String strDropCommand, String strCreateCommand, CustomProcedureType eCustProcType){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strRef
	 * @param eCustProcType
	 */
	public Fusion.Api.DbHint AddCustomProcedureRefDbHint(String strName, String strRef, CustomProcedureType eCustProcType){
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
	 * @param colKeyColumns
	 */
	public Fusion.Api.DbHint AddForeignKeyDbHint(String strName, String strTableFkReferences, KeyColumnCollection colKeyColumns){
		return null;
	}

	/**
	 * 
	 * @param strIndexName
	 * @param bUnique
	 * @param colIndexColumns
	 */
	public Fusion.Api.DbHint AddIndexDbHint(String strIndexName, boolean bUnique, IndexColumnCollection colIndexColumns){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strContent
	 */
	public Fusion.Api.DbHint AddMetaDbHint(String strName, String strContent){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param colKeyColumns
	 */
	public Fusion.Api.DbHint AddPrimaryKeyDbHint(String strName, KeyColumnCollection colKeyColumns){
		return null;
	}

	private void CheckChangeRights(){

	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param defParent
	 */
	public Fusion.Api.DbEngineHints Clone(Fusion.Api.DefinitionObject defParent){
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

	/**
	 * 
	 * @param strId
	 */
	public Fusion.Api.DbHint GetCustomProcedureDbHintById(String strId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.DbHint GetCustomProcedureDbHintByName(String strName){
		return null;
	}

	public List GetCustomProcedureDbHints(){
		return null;
	}

	public List GetForeignKeyDbHints(){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public Fusion.Api.DbHint GetIndexDbHintById(String strId){
		return null;
	}

	/**
	 * 
	 * @param strIndexName
	 */
	public Fusion.Api.DbHint GetIndexDbHintByName(String strIndexName){
		return null;
	}

	public List GetIndexDbHints(){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public Fusion.Api.DbHint GetKeyDbHintById(String strId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.DbHint GetKeyDbHintByName(String strName){
		return null;
	}

	public List GetKeyDbHints(){
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
	 * @param strName
	 */
	public String GetMetaDbHintContentByName(String strName){
		return "";
	}

	public List GetMetaDbHints(){
		return null;
	}

	public Fusion.Api.DbHint GetPrimaryKeyDbHint(){
		return null;
	}

	/**
	 * 
	 * @param strField
	 */
	public boolean IsFieldPrimaryKey(String strField){
		return null;
	}

	public void RemoveAllDbHints(){

	}

	/**
	 * 
	 * @param hint
	 */
	public void RemoveDbHint(Fusion.Api.DbHint hint){

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

	private Fusion.DbEngineHints WhoAmI(){
		return null;
	}

}