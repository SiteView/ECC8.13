package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:16
 */
public class AnyEngineDbValidationInfo extends DbValidationInfo {

	private DbValidationInfo m_aDbValidationInfo[] = null;
	private int m_nMaxBytesInForeignKey = 0;
	private int m_nMaxBytesInIndex = 0;
	private int m_nMaxBytesInPrimaryKey = 0;
	private int m_nMaxBytesPerRow = 0;
	private int m_nMaxColumnNameLength = 0;
	private int m_nMaxColumnsInForeignKey = 0;
	private int m_nMaxColumnsInIndex = 0;
	private int m_nMaxColumnsInPrimaryKey = 0;
	private int m_nMaxColumnsInTable = 0;
	private int m_nMaxConstraintNameLength = 0;
	private int m_nMaxDigitsForNumberField = 0;
	private int m_nMaxInClauseItems = 0;
	private int m_nMaxIndexNameLength = 0;
	private int m_nMaxKeyNameLength = 0;
	private int m_nMaxLengthBinaryField = 0;
	private int m_nMaxLengthSearchableTextField = 0;
	private int m_nMaxLengthTextField = 0;
	private int m_nMaxTableNameLength = 0;
	private DbReservedWords m_ReservedDbWords = new DbReservedWords();



	public void finalize() throws Throwable {
		super.finalize();
	}

	public AnyEngineDbValidationInfo(){

	}

	private DbValidationInfo[] CreateEngineCollection(){
		return null;
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

	private int GetMaxBytesInForeignKey(){
		return 0;
	}

	private int GetMaxBytesInIndex(){
		return 0;
	}

	private int GetMaxBytesInPrimaryKey(){
		return 0;
	}

	private int GetMaxBytesPerRow(){
		return 0;
	}

	private int GetMaxColumnNameLength(){
		return 0;
	}

	private int GetMaxColumnsInForeignKey(){
		return 0;
	}

	private int GetMaxColumnsInIndex(){
		return 0;
	}

	private int GetMaxColumnsInPrimaryKey(){
		return 0;
	}

	private int GetMaxColumnsInTable(){
		return 0;
	}

	private int GetMaxConstraintNameLength(){
		return 0;
	}

	private int GetMaxDigitsForNumberField(){
		return 0;
	}

	private int GetMaxInClauseItems(){
		return 0;
	}

	private int GetMaxIndexNameLength(){
		return 0;
	}

	private int GetMaxKeyNameLength(){
		return 0;
	}

	private int GetMaxLengthBinaryField(){
		return 0;
	}

	private int GetMaxLengthSearchableTextField(){
		return 0;
	}

	private int GetMaxLengthTextField(){
		return 0;
	}

	private int GetMaxTableNameLength(){
		return 0;
	}

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsColumnNameValid(String strName, MessageInfoList errList, String strValidName){
		return false;
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
		return false;
	}

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsIndexNameValid(String strName, MessageInfoList errList, String strValidName){
		return false;
	}

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsKeyNameValid(String strName, MessageInfoList errList, String strValidName){
		return false;
	}

	/**
	 * 
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 */
	public boolean IsNumberTypeAvailable(int nWholeDigits, int nDecimalDigits){
		return false;
	}

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsTableNameValid(String strName, MessageInfoList errList, String strValidName){
		return false;
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