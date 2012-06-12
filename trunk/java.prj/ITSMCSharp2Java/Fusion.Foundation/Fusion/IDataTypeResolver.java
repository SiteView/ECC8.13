package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:46
 */
public interface IDataTypeResolver {

	/**
	 * 
	 * @param nMaxBytes
	 * @param bFixedWidth
	 * @param errList
	 */
	public int BytesToStoreBinaryField(int nMaxBytes, boolean bFixedWidth, MessageInfoList errList);

	/**
	 * 
	 * @param bJustDate
	 * @param bJustTime
	 */
	public int BytesToStoreDateTimeField(boolean bJustDate, boolean bJustTime);

	public int BytesToStoreLogicalField();

	/**
	 * 
	 * @param nLength
	 * @param bUseUnicode
	 */
	public int BytesToStoreMemoField(int nLength, boolean bUseUnicode);

	/**
	 * 
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 * @param errList
	 */
	public int BytesToStoreNumberField(int nWholeDigits, int nDecimalDigits, MessageInfoList errList);

	/**
	 * 
	 * @param nLength
	 * @param bFixedWidth
	 * @param bUseUnicode
	 * @param strEncoding
	 * @param bAllowEolChars
	 * @param errList
	 */
	public int BytesToStoreTextField(int nLength, boolean bFixedWidth, boolean bUseUnicode, String strEncoding, boolean bAllowEolChars, MessageInfoList errList);

	/**
	 * 
	 * @param nBytes
	 * @param bFixedWidth
	 * @param nBytesToStore
	 * @param errList
	 */
	public String GetDataTypeForBinaryField(int nBytes, boolean bFixedWidth, int nBytesToStore, MessageInfoList errList);

	/**
	 * 
	 * @param bJustDate
	 * @param bJustTime
	 * @param nBytesToStore
	 */
	public String GetDataTypeForDateTimeField(boolean bJustDate, boolean bJustTime, int nBytesToStore);

	/**
	 * 
	 * @param nBytesToStore
	 */
	public String GetDataTypeForLogicalField(int nBytesToStore);

	/**
	 * 
	 * @param nLength
	 * @param bUseUnicode
	 * @param nBytesToStore
	 */
	public String GetDataTypeForMemoField(int nLength, boolean bUseUnicode, int nBytesToStore);

	/**
	 * 
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 * @param nBytesToStore
	 * @param errList
	 */
	public String GetDataTypeForNumberField(int nWholeDigits, int nDecimalDigits, int nBytesToStore, MessageInfoList errList);

	/**
	 * 
	 * @param nLength
	 * @param bFixedWidth
	 * @param bUseUnicode
	 * @param strEncoding
	 * @param bAllowEolChars
	 * @param nBytesToStore
	 * @param errList
	 */
	public String GetDataTypeForTextField(int nLength, boolean bFixedWidth, boolean bUseUnicode, String strEncoding, boolean bAllowEolChars, int nBytesToStore, MessageInfoList errList);

	/**
	 * 
	 * @param catExpected
	 * @param strDataType
	 * @param strPrecision
	 * @param strScale
	 * @param nSize
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 * @param bDateOnly
	 * @param bTimeOnly
	 * @param bUnicode
	 * @param bFixedWidth
	 */
	public FieldCategory GetFieldCategory(FieldCategory catExpected, String strDataType, String strPrecision, String strScale, int nSize, int nWholeDigits, int nDecimalDigits, boolean bDateOnly, boolean bTimeOnly, boolean bUnicode, boolean bFixedWidth);

	/**
	 * 
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 */
	public boolean IsNumberTypeAvailable(int nWholeDigits, int nDecimalDigits);

	public int MaxDigitsForNumberField();

	public int MaxLengthBinaryField();

	public int MaxLengthFixedTextField();

	public int MaxLengthImageField();

	public int MaxLengthMemo();

	public int MaxLengthUnicodeFixedTextField();

	public int MaxLengthUnicodeMemo();

	public int MaxLengthUnicodeVaryingTextField();

	public int MaxLengthVaryingBinaryField();

	public int MaxLengthVaryingTextField();

}