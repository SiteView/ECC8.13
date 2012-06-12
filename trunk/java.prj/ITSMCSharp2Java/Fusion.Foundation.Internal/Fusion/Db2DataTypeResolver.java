package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:18
 */
public class Db2DataTypeResolver extends DataTypeResolver {

	private int MaxClobInKB = 0x1fffff;
	private int MaxLengthBigInt = 0x13;
	private int MaxLengthBlob = 0x7fffffff;
	private int MaxLengthBoolean = 1;
	private int MaxLengthChar = 0xfe;
	private int MaxLengthClob = 0x7fffffff;
	private int MaxLengthDbClob = 0x7fffffff;
	private int MaxLengthDecimal = 0x1c;
	private int MaxLengthDouble = 15;
	private int MaxLengthGraphic = 0x7f;
	private int MaxLengthInteger = 9;
	private int MaxLengthLongVarchar = 0x7fbc;
	private int MaxLengthLongVargraphic = 0x3fde;
	private int MaxLengthReal = 7;
	private int MaxLengthSmallInt = 5;
	private int MaxLengthUnicodeClob = 0x7ffffffe;
	private int MaxLengthVarchar = 0xfa0;
	private int MaxLengthVarGraphic = 0x7d0;

	public Db2DataTypeResolver(){

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

	public int getMaxClobInKB(){
		return MaxClobInKB;
	}

	public int getMaxLengthBigInt(){
		return MaxLengthBigInt;
	}

	public int getMaxLengthBlob(){
		return MaxLengthBlob;
	}

	public int getMaxLengthBoolean(){
		return MaxLengthBoolean;
	}

	public int getMaxLengthChar(){
		return MaxLengthChar;
	}

	public int getMaxLengthClob(){
		return MaxLengthClob;
	}

	public int getMaxLengthDbClob(){
		return MaxLengthDbClob;
	}

	public int getMaxLengthDecimal(){
		return MaxLengthDecimal;
	}

	public int getMaxLengthDouble(){
		return MaxLengthDouble;
	}

	public int getMaxLengthGraphic(){
		return MaxLengthGraphic;
	}

	public int getMaxLengthInteger(){
		return MaxLengthInteger;
	}

	public int getMaxLengthLongVarchar(){
		return MaxLengthLongVarchar;
	}

	public int getMaxLengthLongVargraphic(){
		return MaxLengthLongVargraphic;
	}

	public int getMaxLengthReal(){
		return MaxLengthReal;
	}

	public int getMaxLengthSmallInt(){
		return MaxLengthSmallInt;
	}

	public int getMaxLengthUnicodeClob(){
		return MaxLengthUnicodeClob;
	}

	public int getMaxLengthVarchar(){
		return MaxLengthVarchar;
	}

	public int getMaxLengthVarGraphic(){
		return MaxLengthVarGraphic;
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
	 * @param nBytes
	 * @param nBytesToStore
	 */
	private String GetSizeOfLobInKilobytes(int nBytes, int nBytesToStore){
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
	public void setMaxClobInKB(int newVal){
		MaxClobInKB = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthBigInt(int newVal){
		MaxLengthBigInt = newVal;
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
	public void setMaxLengthBoolean(int newVal){
		MaxLengthBoolean = newVal;
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
	public void setMaxLengthDbClob(int newVal){
		MaxLengthDbClob = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthDecimal(int newVal){
		MaxLengthDecimal = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthDouble(int newVal){
		MaxLengthDouble = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthGraphic(int newVal){
		MaxLengthGraphic = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthInteger(int newVal){
		MaxLengthInteger = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthLongVarchar(int newVal){
		MaxLengthLongVarchar = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthLongVargraphic(int newVal){
		MaxLengthLongVargraphic = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthReal(int newVal){
		MaxLengthReal = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthSmallInt(int newVal){
		MaxLengthSmallInt = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthUnicodeClob(int newVal){
		MaxLengthUnicodeClob = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthVarchar(int newVal){
		MaxLengthVarchar = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxLengthVarGraphic(int newVal){
		MaxLengthVarGraphic = newVal;
	}

}