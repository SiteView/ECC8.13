package Fusion;

import java.io.Serializable;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:22
 */
public class ExternalDbDataTypeResolver extends DataTypeResolver implements Serializable {

	private int m_nMaxDigitsForNumberField;
	private int m_nMaxLengthBinaryField;
	private int m_nMaxLengthFixedTextField;
	private int m_nMaxLengthImageField;
	private int m_nMaxLengthMemo;
	private int m_nMaxLengthUnicodeFixedTextField;
	private int m_nMaxLengthUnicodeMemo;
	private int m_nMaxLengthUnicodeVaryingTextField;
	private int m_nMaxLengthVaryingBinaryField;
	private int m_nMaxLengthVaryingTextField;

	public ExternalDbDataTypeResolver(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public ExternalDbDataTypeResolver(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param nMaxLengthMemo
	 * @param nMaxLengthFixedTextField
	 * @param nMaxLengthVaryingTextField
	 * @param nMaxLengthUnicodeMemo
	 * @param nMaxLengthUnicodeFixedTextField
	 * @param nMaxLengthUnicodeVaryingTextField
	 * @param nMaxLengthBinaryField
	 * @param nMaxLengthVaryingBinaryField
	 * @param nMaxLengthImageField
	 * @param nMaxDigitsForNumberField
	 */
	public ExternalDbDataTypeResolver(int nMaxLengthMemo, int nMaxLengthFixedTextField, int nMaxLengthVaryingTextField, int nMaxLengthUnicodeMemo, int nMaxLengthUnicodeFixedTextField, int nMaxLengthUnicodeVaryingTextField, int nMaxLengthBinaryField, int nMaxLengthVaryingBinaryField, int nMaxLengthImageField, int nMaxDigitsForNumberField){

	}

	/**
	 * 
	 * @param nMaxBytes
	 * @param nBytesToStore
	 * @param errList
	 */
	protected String GetBinaryDataType(int nMaxBytes, int nBytesToStore, MessageInfoList errList){
		return "";
	}

	/**
	 * 
	 * @param nMaxBytes
	 * @param nBytesToStore
	 * @param errList
	 */
	protected String GetBinaryVaryingDataType(int nMaxBytes, int nBytesToStore, MessageInfoList errList){
		return "";
	}

	/**
	 * 
	 * @param nBytesToStore
	 */
	protected String GetDateDataType(int nBytesToStore){
		return "";
	}

	/**
	 * 
	 * @param nBytesToStore
	 */
	protected String GetDateTimeDataType(int nBytesToStore){
		return "";
	}

	/**
	 * 
	 * @param nLength
	 * @param nBytesToStore
	 */
	protected String GetFixedTextDataType(int nLength, int nBytesToStore){
		return "";
	}

	/**
	 * 
	 * @param nMaxBytes
	 * @param nBytesToStore
	 * @param errList
	 */
	protected String GetImageDataType(int nMaxBytes, int nBytesToStore, MessageInfoList errList){
		return "";
	}

	/**
	 * 
	 * @param nBytesToStore
	 */
	protected String GetLogicalDataType(int nBytesToStore){
		return "";
	}

	/**
	 * 
	 * @param nLength
	 * @param nBytesToStore
	 */
	protected String GetMemoDataType(int nLength, int nBytesToStore){
		return "";
	}

	/**
	 * 
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 * @param nBytesToStore
	 * @param errList
	 */
	protected String GetNumberDataType(int nWholeDigits, int nDecimalDigits, int nBytesToStore, MessageInfoList errList){
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
	 * @param nBytesToStore
	 */
	protected String GetTimeDataType(int nBytesToStore){
		return "";
	}

	/**
	 * 
	 * @param nLength
	 * @param nBytesToStore
	 */
	protected String GetUnicodeFixedTextDataType(int nLength, int nBytesToStore){
		return "";
	}

	/**
	 * 
	 * @param nLength
	 * @param nBytesToStore
	 */
	protected String GetUnicodeMemoDataType(int nLength, int nBytesToStore){
		return "";
	}

	/**
	 * 
	 * @param nLength
	 * @param nBytesToStore
	 */
	protected String GetUnicodeVaryingTextDataType(int nLength, int nBytesToStore){
		return "";
	}

	/**
	 * 
	 * @param nLength
	 * @param nBytesToStore
	 */
	protected String GetVaryingTextDataType(int nLength, int nBytesToStore){
		return "";
	}

	/**
	 * 
	 * @param strDataType
	 * @param nPrecision
	 * @param nScale
	 * @param catExpected
	 */
	protected boolean IsLogicalDataType(String strDataType, int nPrecision, int nScale, FieldCategory catExpected){
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

	public int MaxDigitsForNumberField(){
		return 0;
	}

	public int MaxLengthBinaryField(){
		return 0;
	}

	public int MaxLengthFixedTextField(){
		return 0;
	}

	public int MaxLengthImageField(){
		return 0;
	}

	public int MaxLengthMemo(){
		return 0;
	}

	public int MaxLengthUnicodeFixedTextField(){
		return 0;
	}

	public int MaxLengthUnicodeMemo(){
		return 0;
	}

	public int MaxLengthUnicodeVaryingTextField(){
		return 0;
	}

	public int MaxLengthVaryingBinaryField(){
		return 0;
	}

	public int MaxLengthVaryingTextField(){
		return 0;
	}

}