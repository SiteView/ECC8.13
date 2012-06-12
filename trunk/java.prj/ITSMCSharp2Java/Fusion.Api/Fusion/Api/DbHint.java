package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:53
 */
public class DbHint extends FusionAggregate {

	private String DataType = "DataType";
	private String DefaultValue = "DefaultValue";
	private String FixedWidth = "FixedWidth";
	private String NullAllowed = "NullAllowed";
	private String PreferredDataType = "PreferredDataType";
	private String Unique = "Unique";
	private String UseUnicode = "UseUnicode";

	public DbHint(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public DbHint(Object fusionObject){

	}

	public DbHintCategory Category(){
		return null;
	}

	private void CheckChangeRights(){

	}

	public static String ClassName(){
		return "";
	}

	public Fusion.Api.DbHint Clone(){
		return null;
	}

	/**
	 * 
	 * @param defParent
	 */
	public Fusion.Api.DbHint Clone(Fusion.Api.DefinitionObject defParent){
		return null;
	}

	public Fusion.Api.DbHint CloneForEdit(){
		return null;
	}

	/**
	 * 
	 * @param defParent
	 */
	public Fusion.Api.DbHint CloneForEdit(Fusion.Api.DefinitionObject defParent){
		return null;
	}

	/**
	 * 
	 * @param hint
	 */
	public boolean Compare(Fusion.Api.DbHint hint){
		return null;
	}

	public String CustomProcedureCreateCommand(){
		return "";
	}

	public String CustomProcedureDropCommand(){
		return "";
	}

	public String CustomProcedureReference(){
		return "";
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

	public boolean ForeignKey(){
		return null;
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

	private CustomProcedureDbHint IAmCustomProcedureDbHint(){
		return null;
	}

	private IndexDbHint IAmIndexDbHint(){
		return null;
	}

	private KeyDbHint IAmKeyDbHint(){
		return null;
	}

	private MetaDbHint IAmMetaDbHint(){
		return null;
	}

	public String Id(){
		return "";
	}

	/**
	 * 
	 * @param strColumnName
	 * @param bAscending
	 */
	public void IndexAddColumn(String strColumnName, boolean bAscending){

	}

	public int IndexColumnCount(){
		return 0;
	}

	/**
	 * 
	 * @param nColumnNumber
	 * @param strColumnName
	 * @param bAscending
	 */
	public void IndexGetColumnInfo(int nColumnNumber, String strColumnName, boolean bAscending){

	}

	/**
	 * 
	 * @param nColumnNumber
	 * @param strColumnName
	 * @param bAscending
	 */
	public void IndexInsertColumn(int nColumnNumber, String strColumnName, boolean bAscending){

	}

	public boolean IndexIsUnique(){
		return null;
	}

	/**
	 * 
	 * @param nColumnNumber
	 */
	public void IndexRemoveColumn(int nColumnNumber){

	}

	/**
	 * 
	 * @param strColumnName
	 */
	public void IndexRemoveColumn(String strColumnName){

	}

	public boolean IsCustomProcedureDbHint(){
		return false;
	}

	/**
	 * 
	 * @param strField
	 */
	public boolean IsFieldPrimaryKey(String strField){
		return false;
	}

	public boolean IsIndexDbHint(){
		return false;
	}

	public boolean IsKeyDbHint(){
		return false;
	}

	public boolean IsMetaDbHint(){
		return false;
	}

	/**
	 * 
	 * @param strColumnName
	 * @param strForeignKeyMapToColumn
	 */
	public void KeyAddColumn(String strColumnName, String strForeignKeyMapToColumn){

	}

	public int KeyColumnCount(){
		return 0;
	}

	/**
	 * 
	 * @param nColumnNumber
	 * @param strColumnName
	 * @param strForeignKeyMapToColumn
	 */
	public void KeyGetColumnInfo(int nColumnNumber, String strColumnName, String strForeignKeyMapToColumn){

	}

	/**
	 * 
	 * @param nColumnNumber
	 * @param strColumnName
	 * @param strForeignKeyMapToColumn
	 */
	public void KeyInsertColumn(int nColumnNumber, String strColumnName, String strForeignKeyMapToColumn){

	}

	/**
	 * 
	 * @param nColumnNumber
	 */
	public void KeyRemoveColumn(int nColumnNumber){

	}

	/**
	 * 
	 * @param strColumnName
	 */
	public void KeyRemoveColumn(String strColumnName){

	}

	public String MetaDbHintContent(){
		return "";
	}

	public String Name(){
		return "";
	}

	public boolean PrimaryKey(){
		return null;
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

	public String TableForeignKeyReferences(){
		return "";
	}

	public CustomProcedureType TypeOfCustomProcedure(){
		return null;
	}

	public Fusion.DbHint WhoAmI(){
		return null;
	}

}