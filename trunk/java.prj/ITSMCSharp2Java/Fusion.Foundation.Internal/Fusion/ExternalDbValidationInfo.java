package Fusion;

import java.io.Serializable;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:22
 */
public class ExternalDbValidationInfo extends DbValidationInfo implements Serializable {

	private int m_nMaxDigitsForNumberField;
	private int m_nMaxInClauseItems;
	private int m_nMaxLengthBinaryField;
	private int m_nMaxLengthSearchableTextField;
	private int m_nMaxLengthTextField;

	public ExternalDbValidationInfo(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public ExternalDbValidationInfo(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param nMaxLengthTextField
	 * @param nMaxLengthSearchableTextField
	 * @param nMaxLengthBinaryField
	 * @param nMaxDigitsForNumberField
	 * @param nMaxInClauseItems
	 */
	public ExternalDbValidationInfo(int nMaxLengthTextField, int nMaxLengthSearchableTextField, int nMaxLengthBinaryField, int nMaxDigitsForNumberField, int nMaxInClauseItems){

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
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

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