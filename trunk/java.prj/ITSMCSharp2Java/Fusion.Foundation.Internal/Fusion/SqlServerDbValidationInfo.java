package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-����-2010 10:50:29
 */
public class SqlServerDbValidationInfo extends DbValidationInfo {

	private DbReservedWords m_ReservedDbWords = new DbReservedWords();
	private IDataTypeResolver m_Resolver = DataTypeResolverFactory.Create(DatabaseEngine.SqlServer);



	public void finalize() throws Throwable {
		super.finalize();
	}

	public SqlServerDbValidationInfo(){

	}

	/**
	 * 
	 * @param strStoredProcName
	 * @param strOwnerName
	 */
	public String CreateStoredProcedureTemplate(String strStoredProcName, String strOwnerName){
		return "";
	}

	/**
	 * 
	 * @param strTriggerName
	 * @param strBusObStorageName
	 * @param strOwnerName
	 */
	public String CreateTriggerTemplate(String strTriggerName, String strBusObStorageName, String strOwnerName){
		return "";
	}

	/**
	 * 
	 * @param strStoredProcName
	 * @param strOwnerName
	 */
	public String DropStoredProcedureTemplate(String strStoredProcName, String strOwnerName){
		return "";
	}

	/**
	 * 
	 * @param strTriggerName
	 * @param strOwnerName
	 */
	public String DropTriggerTemplate(String strTriggerName, String strOwnerName){
		return "";
	}

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsColumnNameValid(String strName, MessageInfoList errList, String strValidName){
		return null;
	}

	/**
	 * 
	 * @param typeIdentifier
	 * @param strName
	 * @param nMaximumLength
	 * @param errList
	 * @param strValidIdentifier
	 */
	private boolean IsIdentifierValid(DbValidationInfo.IdentifierType typeIdentifier, String strName, int nMaximumLength, MessageInfoList errList, String strValidIdentifier){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsIndexNameValid(String strName, MessageInfoList errList, String strValidName){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsKeyNameValid(String strName, MessageInfoList errList, String strValidName){
		return null;
	}

	/**
	 * 
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 */
	public boolean IsNumberTypeAvailable(int nWholeDigits, int nDecimalDigits){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsTableNameValid(String strName, MessageInfoList errList, String strValidName){
		return null;
	}

	public int MaxBytesInForeignKey(){
		return 0;
	}

	public int MaxBytesInIndex(){
		return 0;
	}

	public int MaxBytesInPrimaryKey(){
		return 0;
	}

	public int MaxBytesPerRow(){
		return 0;
	}

	public int MaxColumnNameLength(){
		return 0;
	}

	public int MaxColumnsInForeignKey(){
		return 0;
	}

	public int MaxColumnsInIndex(){
		return 0;
	}

	public int MaxColumnsInPrimaryKey(){
		return 0;
	}

	public int MaxColumnsInTable(){
		return 0;
	}

	public int MaxConstraintNameLength(){
		return 0;
	}

	public int MaxDigitsForNumberField(){
		return 0;
	}

	public int MaxInClauseItems(){
		return 0;
	}

	public int MaxIndexNameLength(){
		return 0;
	}

	public int MaxKeyNameLength(){
		return 0;
	}

	public int MaxLengthBinaryField(){
		return 0;
	}

	public int MaxLengthSearchableTextField(){
		return 0;
	}

	public int MaxLengthTextField(){
		return 0;
	}

	public int MaxTableNameLength(){
		return 0;
	}

	public String ValidColumnNameInfo(){
		return "";
	}

	private String ValidIdentifierNameInfo(){
		return "";
	}

	public String ValidIndexNameInfo(){
		return "";
	}

	public String ValidKeyNameInfo(){
		return "";
	}

	public String ValidTableNameInfo(){
		return "";
	}

}