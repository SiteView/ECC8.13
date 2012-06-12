package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:27
 */
public class OracleDataTypeResolver extends DataTypeResolver {

	private int MaxLengthBFile = 0x7fffffff;
	private int MaxLengthBlob = 0x7fffffff;
	private int MaxLengthChar = 0x7d0;
	private int MaxLengthClob = 0x7fffffff;
	private int MaxLengthLong = 0x7fffffff;
	private int MaxLengthLongRaw = 0x7fffffff;
	private int MaxLengthNChar = 0x7d0;
	private int MaxLengthNClob = 0x7fffffff;
	private int MaxLengthNumber = 0x1c;
	private int MaxLengthNVarChar = 0xfa0;
	private int MaxLengthRaw = 0x7d0;
	private int MaxLengthVarchar = 0xfa0;

	public OracleDataTypeResolver(){

	}

	public void finalize() throws Throwable {
		super.finalize();
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

	public int getMaxLengthBFile(){
		return MaxLengthBFile;
	}

	public int getMaxLengthBlob(){
		return MaxLengthBlob;
	}

	public int getMaxLengthChar(){
		return MaxLengthChar;
	}

	public int getMaxLengthClob(){
		return MaxLengthClob;
	}

	public int getMaxLengthLong(){
		return MaxLengthLong;
	}

	public int getMaxLengthLongRaw(){
		return MaxLengthLongRaw;
	}

	public int getMaxLengthNChar(){
		return MaxLengthNChar;
	}

	public int getMaxLengthNClob(){
		return MaxLengthNClob;
	}

	public int getMaxLengthNumber(){
		return MaxLengthNumber;
	}

	public int getMaxLengthNVarChar(){
		return MaxLengthNVarChar;
	}

	public int getMaxLengthRaw(){
		return MaxLengthRaw;
	}

	public int getMaxLengthVarchar(){
		return MaxLengthVarchar;
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

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthBFile(int newVal){
		MaxLengthBFile = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthBlob(int newVal){
		MaxLengthBlob = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthChar(int newVal){
		MaxLengthChar = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthClob(int newVal){
		MaxLengthClob = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthLong(int newVal){
		MaxLengthLong = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthLongRaw(int newVal){
		MaxLengthLongRaw = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthNChar(int newVal){
		MaxLengthNChar = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthNClob(int newVal){
		MaxLengthNClob = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthNumber(int newVal){
		MaxLengthNumber = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthNVarChar(int newVal){
		MaxLengthNVarChar = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthRaw(int newVal){
		MaxLengthRaw = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthVarchar(int newVal){
		MaxLengthVarchar = newVal;
	}

}