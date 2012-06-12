package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:28
 */
public class SqlServerDataTypeResolver extends DataTypeResolver {

	private int MaxBytesInBinaryDataType = 0x1f40;
	private int MaxBytesInImageDataType = 0x7fffffff;
	private int MaxBytesInVarbinaryDataType = 0x1f40;
	private int MaxDigitsDecimalDataType = 0x1c;
	private int MaxDigitsIntDataType = 9;
	private int MaxDigitsSmallIntDataType = 4;
	private int MaxDigitsTinyIntDataType = 2;
	private int MaxSizeCharDataType = 0x1f40;
	private int MaxSizeNCharDataType = 0xfa0;
	private int MaxSizeNTextDataType = 0x3fffffff;
	private int MaxSizeNVarcharDataType = 0xfa0;
	private int MaxSizeTextDataType = 0x7fffffff;
	private int MaxSizeVarcharDataType = 0x1f40;

	public SqlServerDataTypeResolver(){

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

	public int getMaxBytesInBinaryDataType(){
		return MaxBytesInBinaryDataType;
	}

	public int getMaxBytesInImageDataType(){
		return MaxBytesInImageDataType;
	}

	public int getMaxBytesInVarbinaryDataType(){
		return MaxBytesInVarbinaryDataType;
	}

	public int getMaxDigitsDecimalDataType(){
		return MaxDigitsDecimalDataType;
	}

	public int getMaxDigitsIntDataType(){
		return MaxDigitsIntDataType;
	}

	public int getMaxDigitsSmallIntDataType(){
		return MaxDigitsSmallIntDataType;
	}

	public int getMaxDigitsTinyIntDataType(){
		return MaxDigitsTinyIntDataType;
	}

	public int getMaxSizeCharDataType(){
		return MaxSizeCharDataType;
	}

	public int getMaxSizeNCharDataType(){
		return MaxSizeNCharDataType;
	}

	public int getMaxSizeNTextDataType(){
		return MaxSizeNTextDataType;
	}

	public int getMaxSizeNVarcharDataType(){
		return MaxSizeNVarcharDataType;
	}

	public int getMaxSizeTextDataType(){
		return MaxSizeTextDataType;
	}

	public int getMaxSizeVarcharDataType(){
		return MaxSizeVarcharDataType;
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

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxBytesInBinaryDataType(int newVal){
		MaxBytesInBinaryDataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxBytesInImageDataType(int newVal){
		MaxBytesInImageDataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxBytesInVarbinaryDataType(int newVal){
		MaxBytesInVarbinaryDataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxDigitsDecimalDataType(int newVal){
		MaxDigitsDecimalDataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxDigitsIntDataType(int newVal){
		MaxDigitsIntDataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxDigitsSmallIntDataType(int newVal){
		MaxDigitsSmallIntDataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxDigitsTinyIntDataType(int newVal){
		MaxDigitsTinyIntDataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxSizeCharDataType(int newVal){
		MaxSizeCharDataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxSizeNCharDataType(int newVal){
		MaxSizeNCharDataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxSizeNTextDataType(int newVal){
		MaxSizeNTextDataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxSizeNVarcharDataType(int newVal){
		MaxSizeNVarcharDataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxSizeTextDataType(int newVal){
		MaxSizeTextDataType = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxSizeVarcharDataType(int newVal){
		MaxSizeVarcharDataType = newVal;
	}

}