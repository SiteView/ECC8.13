package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:46
 */
public interface IDbValidationInfo {

	/**
	 * 
	 * @param strStoredProcName
	 * @param strOwnerName
	 */
	public String CreateStoredProcedureTemplate(String strStoredProcName, String strOwnerName);

	/**
	 * 
	 * @param strTriggerName
	 * @param strBusObStorageName
	 * @param strOwnerName
	 */
	public String CreateTriggerTemplate(String strTriggerName, String strBusObStorageName, String strOwnerName);

	/**
	 * 
	 * @param strStoredProcName
	 * @param strOwnerName
	 */
	public String DropStoredProcedureTemplate(String strStoredProcName, String strOwnerName);

	/**
	 * 
	 * @param strTriggerName
	 * @param strOwnerName
	 */
	public String DropTriggerTemplate(String strTriggerName, String strOwnerName);

	/**
	 * 
	 * @param strAlias
	 * @param errList
	 * @param strValidAlias
	 */
	public boolean IsAliasValid(String strAlias, MessageInfoList errList, String strValidAlias);

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsColumnNameValid(String strName, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsIndexNameValid(String strName, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsKeyNameValid(String strName, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsNameValid(String strName, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 */
	public boolean IsNumberTypeAvailable(int nWholeDigits, int nDecimalDigits);

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsTableNameValid(String strName, MessageInfoList errList, String strValidName);

	public int MaxBytesInForeignKey();

	public int MaxBytesInIndex();

	public int MaxBytesInPrimaryKey();

	public int MaxBytesPerRow();

	public int MaxColumnNameLength();

	public int MaxColumnsInForeignKey();

	public int MaxColumnsInIndex();

	public int MaxColumnsInPrimaryKey();

	public int MaxColumnsInTable();

	public int MaxConstraintNameLength();

	public int MaxDigitsForNumberField();

	public int MaxInClauseItems();

	public int MaxIndexNameLength();

	public int MaxKeyNameLength();

	public int MaxLengthBinaryField();

	public int MaxLengthSearchableTextField();

	public int MaxLengthTextField();

	public int MaxTableNameLength();

	public String ValidAliasInfo();

	/**
	 * 
	 * @param strStoredProcName
	 * @param strStoredProcText
	 * @param strError
	 */
	public boolean ValidateCreateStoredProcedureSyntax(String strStoredProcName, String strStoredProcText, String strError);

	/**
	 * 
	 * @param strTriggerName
	 * @param strTriggerText
	 * @param strError
	 */
	public boolean ValidateCreateTriggerSyntax(String strTriggerName, String strTriggerText, String strError);

	/**
	 * 
	 * @param strStoredProcName
	 * @param strStoredProcText
	 * @param strError
	 */
	public boolean ValidateDropStoredProcedureSyntax(String strStoredProcName, String strStoredProcText, String strError);

	/**
	 * 
	 * @param strTriggerName
	 * @param strTriggerText
	 * @param strError
	 */
	public boolean ValidateDropTriggerSyntax(String strTriggerName, String strTriggerText, String strError);

	public String ValidColumnNameInfo();

	public String ValidIndexNameInfo();

	public String ValidKeyNameInfo();

	public String ValidNameInfo();

	public String ValidTableNameInfo();

}