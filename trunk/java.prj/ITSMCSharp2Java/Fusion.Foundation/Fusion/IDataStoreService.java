package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:45
 */
public interface IDataStoreService {

	/**
	 * 
	 * @param defBusOb
	 * @param strDataStore
	 * @param strTable
	 * @param svcSettings
	 */
	public IDefinition BuildExternalTableBusinessObject(IDefinition defBusOb, String strDataStore, String strTable, ISettings svcSettings);

	/**
	 * 
	 * @param strDataStore
	 * @param nMaxBytes
	 * @param bFixedWidth
	 * @param errList
	 */
	public int BytesToStoreBinaryField(String strDataStore, int nMaxBytes, boolean bFixedWidth, MessageInfoList errList);

	/**
	 * 
	 * @param strDataStore
	 * @param bJustDate
	 * @param bJustTime
	 */
	public int BytesToStoreDateTimeField(String strDataStore, boolean bJustDate, boolean bJustTime);

	/**
	 * 
	 * @param strDataStore
	 */
	public int BytesToStoreLogicalField(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 * @param errList
	 */
	public int BytesToStoreNumberField(String strDataStore, int nWholeDigits, int nDecimalDigits, MessageInfoList errList);

	/**
	 * 
	 * @param strDataStore
	 * @param nLength
	 * @param bFixedWidth
	 * @param bUseUnicode
	 * @param strEncoding
	 * @param bAllowEolChars
	 * @param errList
	 */
	public int BytesToStoreTextField(String strDataStore, int nLength, boolean bFixedWidth, boolean bUseUnicode, String strEncoding, boolean bAllowEolChars, MessageInfoList errList);

	/**
	 * 
	 * @param strPublication
	 */
	public boolean CheckForReplicationSubscriptions(String strPublication);

	/**
	 * 
	 * @param dbEngine
	 * @param strStoredProcName
	 * @param strOwnerName
	 */
	public String CreateStoredProcedureTemplate(DatabaseEngine dbEngine, String strStoredProcName, String strOwnerName);

	/**
	 * 
	 * @param dbEngine
	 * @param strTriggerName
	 * @param strBusObStorageName
	 * @param strOwnerName
	 */
	public String CreateTriggerTemplate(DatabaseEngine dbEngine, String strTriggerName, String strBusObStorageName, String strOwnerName);

	/**
	 * 
	 * @param strDatabaseName
	 */
	public List DatabaseLoginIds(String strDatabaseName);

	/**
	 * 
	 * @param strDataStore
	 */
	public List DataStoreLoginIds(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 * @param strNotSupportedMessage
	 */
	public boolean DoesDatabaseSupportBasicSchemaInfo(String strDataStore, String strNotSupportedMessage);

	/**
	 * 
	 * @param dbEngine
	 * @param strStoredProcName
	 * @param strOwnerName
	 */
	public String DropStoredProcedureTemplate(DatabaseEngine dbEngine, String strStoredProcName, String strOwnerName);

	/**
	 * 
	 * @param dbEngine
	 * @param strTriggerName
	 * @param strOwnerName
	 */
	public String DropTriggerTemplate(DatabaseEngine dbEngine, String strTriggerName, String strOwnerName);

	/**
	 * 
	 * @param strDataStore
	 */
	public Hashtable GetAllTableKeyIndexNames(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public String GetDataStoreInfoAsXml(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 * @param nMaxBytes
	 * @param bFixedWidth
	 * @param nBytesToStore
	 * @param errList
	 */
	public String GetDataTypeForBinaryField(String strDataStore, int nMaxBytes, boolean bFixedWidth, int nBytesToStore, MessageInfoList errList);

	/**
	 * 
	 * @param strDataStore
	 * @param bJustDate
	 * @param bJustTime
	 * @param nBytesToStore
	 */
	public String GetDataTypeForDateTimeField(String strDataStore, boolean bJustDate, boolean bJustTime, int nBytesToStore);

	/**
	 * 
	 * @param strDataStore
	 * @param nBytesToStore
	 */
	public String GetDataTypeForLogicalField(String strDataStore, int nBytesToStore);

	/**
	 * 
	 * @param strDataStore
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 * @param nBytesToStore
	 * @param errList
	 */
	public String GetDataTypeForNumberField(String strDataStore, int nWholeDigits, int nDecimalDigits, int nBytesToStore, MessageInfoList errList);

	/**
	 * 
	 * @param strDataStore
	 * @param nLength
	 * @param bFixedWidth
	 * @param bUseUnicode
	 * @param strEncoding
	 * @param bAllowEolChars
	 * @param nBytesToStore
	 * @param errList
	 */
	public String GetDataTypeForTextField(String strDataStore, int nLength, boolean bFixedWidth, boolean bUseUnicode, String strEncoding, boolean bAllowEolChars, int nBytesToStore, MessageInfoList errList);

	/**
	 * 
	 * @param strDataStore
	 */
	public IDataTypeResolver GetDataTypeResolver(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public IDbValidationInfo GetDbValidationInfo(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public String GetEngine(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public ArrayList GetListOfTables(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public ArrayList GetListOfTablesAndViews(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public ArrayList GetListOfViews(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int GetMaxDigitsForNumberField(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int GetMaxLengthOfBinaryField(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int GetMaxLengthOfSearchableTextField(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int GetMaxLengthOfTextField(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public String GetName(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public String GetOwnerName(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public String GetServerName(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public String GetVersion(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 * @param strAlias
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsAliasValid(String strDataStore, String strAlias, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param strDataStore
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsColumnNameValid(String strDataStore, String strName, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param strDataStore
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsIndexNameValid(String strDataStore, String strName, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param strDataStore
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsKeyNameValid(String strDataStore, String strName, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param strDataStore
	 * @param strNameToCheck
	 * @param errList
	 */
	public boolean IsNameUniqueAmongTablesIndexesKeys(String strDataStore, String strNameToCheck, MessageInfoList errList);

	/**
	 * 
	 * @param strDataStore
	 * @param strNameToCheck
	 * @param strTableThatIndexOrKeyBelongsTo
	 * @param errList
	 */
	public boolean IsNameUniqueAmongTablesIndexesKeys(String strDataStore, String strNameToCheck, String strTableThatIndexOrKeyBelongsTo, MessageInfoList errList);

	/**
	 * 
	 * @param strDataStore
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsNameValid(String strDataStore, String strName, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param strDataStore
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 */
	public boolean IsNumberTypeAvailable(String strDataStore, int nWholeDigits, int nDecimalDigits);

	/**
	 * 
	 * @param strDataStore
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsTableNameValid(String strDataStore, String strName, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param strDataStore
	 */
	public int MaxBytesInForeignKey(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int MaxBytesInIndex(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int MaxBytesInPrimaryKey(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int MaxBytesPerRow(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int MaxColumnNameLength(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int MaxColumnsInForeignKey(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int MaxColumnsInIndex(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int MaxColumnsInPrimaryKey(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int MaxColumnsInTable(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int MaxInClauseItems(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int MaxIndexNameLength(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int MaxKeyNameLength(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public int MaxTableNameLength(String strDataStore);

	/**
	 * 
	 * @param strPublication
	 */
	public boolean ReplicationEnabled(String strPublication);

	public boolean ReplicationSupported();

	/**
	 * 
	 * @param dbEngine
	 * @param strStoredProcName
	 * @param strStoredProcText
	 * @param strError
	 */
	public boolean ValidateCreateStoredProcedureSyntax(DatabaseEngine dbEngine, String strStoredProcName, String strStoredProcText, String strError);

	/**
	 * 
	 * @param dbEngine
	 * @param strTriggerName
	 * @param strTriggerText
	 * @param strError
	 */
	public boolean ValidateCreateTriggerSyntax(DatabaseEngine dbEngine, String strTriggerName, String strTriggerText, String strError);

	/**
	 * 
	 * @param dbEngine
	 * @param strStoredProcName
	 * @param strStoredProcText
	 * @param strError
	 */
	public boolean ValidateDropStoredProcedureSyntax(DatabaseEngine dbEngine, String strStoredProcName, String strStoredProcText, String strError);

	/**
	 * 
	 * @param dbEngine
	 * @param strTriggerName
	 * @param strTriggerText
	 * @param strError
	 */
	public boolean ValidateDropTriggerSyntax(DatabaseEngine dbEngine, String strTriggerName, String strTriggerText, String strError);

	/**
	 * 
	 * @param strCommand
	 * @param strError
	 */
	public boolean ValidateSyntaxOfDataStoreCommand(String strCommand, String strError);

	/**
	 * 
	 * @param strDataStore
	 */
	public String ValidColumnNameInfo(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public String ValidIndexNameInfo(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public String ValidKeyNameInfo(String strDataStore);

	/**
	 * 
	 * @param strDataStore
	 */
	public String ValidTableNameInfo(String strDataStore);

}