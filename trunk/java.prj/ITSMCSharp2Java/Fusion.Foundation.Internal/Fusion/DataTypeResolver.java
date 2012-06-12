package Fusion;

import java.io.Serializable;
import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:18
 */
public abstract class DataTypeResolver implements IDataTypeResolver,Serializable {

	protected ArrayList m_alSupportedDataTypes;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public DataTypeResolver(){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public DataTypeResolver(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param nMaxBytes
	 * @param bFixedWidth
	 * @param errList
	 */
	public int BytesToStoreBinaryField(int nMaxBytes, boolean bFixedWidth, MessageInfoList errList){
		return 0;
	}

	/**
	 * 
	 * @param bJustDate
	 * @param bJustTime
	 */
	public int BytesToStoreDateTimeField(boolean bJustDate, boolean bJustTime){
		return 0;
	}

	public int BytesToStoreLogicalField(){
		return 0;
	}

	/**
	 * 
	 * @param nLength
	 * @param bUseUnicode
	 */
	public int BytesToStoreMemoField(int nLength, boolean bUseUnicode){
		return 0;
	}

	/**
	 * 
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 * @param errList
	 */
	public int BytesToStoreNumberField(int nWholeDigits, int nDecimalDigits, MessageInfoList errList){
		return 0;
	}

	/**
	 * 
	 * @param nLength
	 * @param bFixedWidth
	 * @param bUseUnicode
	 * @param strEncoding
	 * @param bAllowEolChars
	 * @param errList
	 */
	public int BytesToStoreTextField(int nLength, boolean bFixedWidth, boolean bUseUnicode, String strEncoding, boolean bAllowEolChars, MessageInfoList errList){
		return 0;
	}

	/**
	 * 
	 * @param strDataType1
	 * @param strDataType2
	 */
	private boolean CompareDataTypes(String strDataType1, String strDataType2){
		return false;
	}

	/**
	 * 
	 * @param nMaxBytes
	 * @param nBytesToStore
	 * @param errList
	 */
	protected abstract String GetBinaryDataType(int nMaxBytes, int nBytesToStore, MessageInfoList errList);

	/**
	 * 
	 * @param nMaxBytes
	 * @param nBytesToStore
	 * @param errList
	 */
	protected abstract String GetBinaryVaryingDataType(int nMaxBytes, int nBytesToStore, MessageInfoList errList);

	/**
	 * 
	 * @param nMaxBytes
	 * @param bFixedWidth
	 * @param nBytesToStore
	 * @param errList
	 */
	public String GetDataTypeForBinaryField(int nMaxBytes, boolean bFixedWidth, int nBytesToStore, MessageInfoList errList){
		return "";
	}

	/**
	 * 
	 * @param bJustDate
	 * @param bJustTime
	 * @param nBytesToStore
	 */
	public String GetDataTypeForDateTimeField(boolean bJustDate, boolean bJustTime, int nBytesToStore){
		return "";
	}

	/**
	 * 
	 * @param nBytesToStore
	 */
	public String GetDataTypeForLogicalField(int nBytesToStore){
		return "";
	}

	/**
	 * 
	 * @param nLength
	 * @param bUseUnicode
	 * @param nBytesToStore
	 */
	public String GetDataTypeForMemoField(int nLength, boolean bUseUnicode, int nBytesToStore){
		return "";
	}

	/**
	 * 
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 * @param nBytesToStore
	 * @param errList
	 */
	public String GetDataTypeForNumberField(int nWholeDigits, int nDecimalDigits, int nBytesToStore, MessageInfoList errList){
		return "";
	}

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
	public String GetDataTypeForTextField(int nLength, boolean bFixedWidth, boolean bUseUnicode, String strEncoding, boolean bAllowEolChars, int nBytesToStore, MessageInfoList errList){
		return "";
	}

	/**
	 * 
	 * @param nBytesToStore
	 */
	protected abstract String GetDateDataType(int nBytesToStore);

	/**
	 * 
	 * @param nBytesToStore
	 */
	protected abstract String GetDateTimeDataType(int nBytesToStore);

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
	public FieldCategory GetFieldCategory(FieldCategory catExpected, String strDataType, String strPrecision, String strScale, int nSize, int nWholeDigits, int nDecimalDigits, boolean bDateOnly, boolean bTimeOnly, boolean bUnicode, boolean bFixedWidth){
		return null;
	}

	/**
	 * 
	 * @param nLength
	 * @param nBytesToStore
	 */
	protected abstract String GetFixedTextDataType(int nLength, int nBytesToStore);

	/**
	 * 
	 * @param nMaxBytes
	 * @param nBytesToStore
	 * @param errList
	 */
	protected abstract String GetImageDataType(int nMaxBytes, int nBytesToStore, MessageInfoList errList);

	/**
	 * 
	 * @param nBytesToStore
	 */
	protected abstract String GetLogicalDataType(int nBytesToStore);

	/**
	 * 
	 * @param nLength
	 * @param nBytesToStore
	 */
	protected abstract String GetMemoDataType(int nLength, int nBytesToStore);

	/**
	 * 
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 * @param nBytesToStore
	 * @param errList
	 */
	protected abstract String GetNumberDataType(int nWholeDigits, int nDecimalDigits, int nBytesToStore, MessageInfoList errList);

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
	protected abstract String GetTimeDataType(int nBytesToStore);

	/**
	 * 
	 * @param nLength
	 * @param nBytesToStore
	 */
	protected abstract String GetUnicodeFixedTextDataType(int nLength, int nBytesToStore);

	/**
	 * 
	 * @param nLength
	 * @param nBytesToStore
	 */
	protected abstract String GetUnicodeMemoDataType(int nLength, int nBytesToStore);

	/**
	 * 
	 * @param nLength
	 * @param nBytesToStore
	 */
	protected abstract String GetUnicodeVaryingTextDataType(int nLength, int nBytesToStore);

	/**
	 * 
	 * @param nLength
	 * @param nBytesToStore
	 */
	protected abstract String GetVaryingTextDataType(int nLength, int nBytesToStore);

	/**
	 * 
	 * @param strDataType
	 * @param nPrecision
	 * @param nScale
	 * @param catExpected
	 */
	protected abstract boolean IsLogicalDataType(String strDataType, int nPrecision, int nScale, FieldCategory catExpected);

	/**
	 * 
	 * @param nWholeDigits
	 * @param nDecimalDigits
	 */
	public abstract boolean IsNumberTypeAvailable(int nWholeDigits, int nDecimalDigits);

	public abstract int MaxDigitsForNumberField();

	public abstract int MaxLengthBinaryField();

	public abstract int MaxLengthFixedTextField();

	public abstract int MaxLengthImageField();

	public abstract int MaxLengthMemo();

	public abstract int MaxLengthUnicodeFixedTextField();

	public abstract int MaxLengthUnicodeMemo();

	public abstract int MaxLengthUnicodeVaryingTextField();

	public abstract int MaxLengthVaryingBinaryField();

	public abstract int MaxLengthVaryingTextField();

}