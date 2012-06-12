package Fusion;

import java.io.Serializable;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-四月-2010 10:50:21
 */
public abstract class DbValidationInfo implements IDbValidationInfo,Serializable {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 21-四月-2010 10:50:21
	 */
	public protected enum IdentifierType {
		Table,
		Column,
		Index,
		Key
	}



	public void finalize() throws Throwable {
		super.finalize();
	}

	public DbValidationInfo(){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public DbValidationInfo(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param strStoredProcName
	 * @param strOwnerName
	 */
	public abstract String CreateStoredProcedureTemplate(String strStoredProcName, String strOwnerName);

	/**
	 * 
	 * @param strTriggerName
	 * @param strBusObStorageName
	 * @param strOwnerName
	 */
	public abstract String CreateTriggerTemplate(String strTriggerName, String strBusObStorageName, String strOwnerName);

	/**
	 * 
	 * @param strStoredProcName
	 * @param strOwnerName
	 */
	public abstract String DropStoredProcedureTemplate(String strStoredProcName, String strOwnerName);

	/**
	 * 
	 * @param strTriggerName
	 * @param strOwnerName
	 */
	public abstract String DropTriggerTemplate(String strTriggerName, String strOwnerName);

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param strAlias
	 * @param errList
	 * @param strValidAlias
	 */
	public boolean IsAliasValid(String strAlias, MessageInfoList errList, String strValidAlias){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public abstract boolean IsColumnNameValid(String strName, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public abstract boolean IsIndexNameValid(String strName, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public abstract boolean IsKeyNameValid(String strName, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public boolean IsNameValid(String strName, MessageInfoList errList, String strValidName){
		return null;
	}

	/**
	 * 
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 */
	public abstract boolean IsNumberTypeAvailable(int nWholeDigits, int nDecimalDigits);

	/**
	 * 
	 * @param strName
	 * @param errList
	 * @param strValidName
	 */
	public abstract boolean IsTableNameValid(String strName, MessageInfoList errList, String strValidName);

	/**
	 * 
	 * @param typeIdentifier
	 * @param strName
	 */
	protected String LoadNameInvalidMsg(IdentifierType typeIdentifier, String strName){
		return "";
	}

	/**
	 * 
	 * @param typeIdentifier
	 * @param strName
	 * @param nMaxLength
	 */
	protected String LoadNameTooLongMsg(IdentifierType typeIdentifier, String strName, int nMaxLength){
		return "";
	}

	/**
	 * 
	 * @param strValidName
	 */
	protected String LoadSuggestedValidName(String strValidName){
		return "";
	}

	public abstract int MaxBytesInForeignKey();

	public abstract int MaxBytesInIndex();

	public abstract int MaxBytesInPrimaryKey();

	public abstract int MaxBytesPerRow();

	public abstract int MaxColumnNameLength();

	public abstract int MaxColumnsInForeignKey();

	public abstract int MaxColumnsInIndex();

	public abstract int MaxColumnsInPrimaryKey();

	public abstract int MaxColumnsInTable();

	public abstract int MaxConstraintNameLength();

	public abstract int MaxDigitsForNumberField();

	public abstract int MaxInClauseItems();

	public abstract int MaxIndexNameLength();

	public abstract int MaxKeyNameLength();

	public abstract int MaxLengthBinaryField();

	public abstract int MaxLengthSearchableTextField();

	public abstract int MaxLengthTextField();

	public abstract int MaxTableNameLength();

	/**
	 * 
	 * @param strIdentifier
	 * @param nDesiredLength
	 */
	protected String TrimIdentifierToLength(String strIdentifier, int nDesiredLength){
		return "";
	}

	public String ValidAliasInfo(){
		return "";
	}

	/**
	 * 
	 * @param strStoredProcName
	 * @param strStoredProcText
	 * @param strError
	 */
	public boolean ValidateCreateStoredProcedureSyntax(String strStoredProcName, String strStoredProcText, String strError){
		return null;
	}

	/**
	 * 
	 * @param strTriggerName
	 * @param strTriggerText
	 * @param strError
	 */
	public boolean ValidateCreateTriggerSyntax(String strTriggerName, String strTriggerText, String strError){
		return null;
	}

	/**
	 * 
	 * @param strStoredProcName
	 * @param strStoredProcText
	 * @param strError
	 */
	public boolean ValidateDropStoredProcedureSyntax(String strStoredProcName, String strStoredProcText, String strError){
		return null;
	}

	/**
	 * 
	 * @param strTriggerName
	 * @param strTriggerText
	 * @param strError
	 */
	public boolean ValidateDropTriggerSyntax(String strTriggerName, String strTriggerText, String strError){
		return null;
	}

	public abstract String ValidColumnNameInfo();

	public abstract String ValidIndexNameInfo();

	public abstract String ValidKeyNameInfo();

	public String ValidNameInfo(){
		return "";
	}

	public abstract String ValidTableNameInfo();

}