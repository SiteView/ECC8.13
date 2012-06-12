package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:21
 */
public class NumberFormat {

	private boolean m_bAllowDecimals = true;
	private boolean m_bAllowEmpty = false;
	private boolean m_bAllowNegative = true;
	private boolean m_bObeySystemSettings = false;
	private boolean m_bShowCurrency = false;
	private boolean m_bShowSeparator = true;
	private CultureInfo m_CultureInfo = CultureInfo.CurrentCulture;
	private int m_nNumberOfDecimalDigits = 0;
	private int m_nNumberOfDigits = 0;
	private int m_nNumberOfWholeDigits = 0;
	private String m_strCurrencySymbol = "";
	private int MAX_LENGTH = 15;
	private int ROUNDUP = 4;
	private String ZERO = "0";

	public NumberFormat(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strNumber
	 * @param nNumberOfDecimalDigits
	 */
	private String AdjustNumberOfDecimalDigits(String strNumber, int nNumberOfDecimalDigits){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 * @param nfi
	 */
	private String AdjustNumberOfDigits(String strNumber, NumberFormatInfo nfi){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	private String AdjustNumberOfWholeDigits(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param dIncrement
	 */
	private double AdjustValueToIncrement(double dIncrement){
		return 0;
	}

	public boolean AllowDecimals(){
		return null;
	}

	public boolean AllowEmpty(){
		return null;
	}

	public boolean AllowNegative(){
		return null;
	}

	/**
	 * 
	 * @param strNumber
	 */
	public boolean ContainNegativeSigns(String strNumber){
		return null;
	}

	/**
	 * 
	 * @param strNumber
	 */
	public String ConvertToNegative(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	private String ConvertToNegativeCurrency(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	private String ConvertToNegativeNumber(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	public String ConvertToPositive(String strNumber){
		return "";
	}

	public String CurrencySymbol(){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	public String Format(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	private String FormatCurrency(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param nfi
	 * @param strNumber
	 */
	private String FormatNegativeCurrency(NumberFormatInfo nfi, String strNumber){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	private String FormatNumber(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param nfi
	 * @param strNumber
	 */
	private String FormatPositiveCurrency(NumberFormatInfo nfi, String strNumber){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	private String GetAbsoluteFractionalPart(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	public String GetAbsoluteWholePart(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param nfi
	 * @param styles
	 */
	private void GetCurrencyFormatStyle(NumberFormatInfo nfi, NumberStyles styles){

	}

	public String GetDecimalSeparator(){
		return "";
	}

	/**
	 * 
	 * @param nfi
	 * @param styles
	 */
	private void GetFormatStyle(NumberFormatInfo nfi, NumberStyles styles){

	}

	public String GetGroupSeparator(){
		return "";
	}

	public NumberFormatInfo GetNumberFormat(){
		return null;
	}

	/**
	 * 
	 * @param nfi
	 * @param styles
	 */
	private void GetNumberFormatStyle(NumberFormatInfo nfi, NumberStyles styles){

	}

	private int GetNumberOfDecimalDigits(){
		return 0;
	}

	/**
	 * 
	 * @param strNumber
	 */
	public int GetNumberOfDecimalDigits(String strNumber){
		return 0;
	}

	/**
	 * 
	 * @param strNumber
	 */
	public int GetNumberOfWholeDigits(String strNumber){
		return 0;
	}

	/**
	 * 
	 * @param strNumber
	 */
	public String GetValidValue(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 * @param dIncrement
	 */
	public double IncrementValue(String strNumber, double dIncrement){
		return 0;
	}

	/**
	 * 
	 * @param strNumber
	 */
	public boolean IsValidValue(String strNumber){
		return null;
	}

	public CultureInfo Language(){
		return null;
	}

	public int NumberOfDecimalDigits(){
		return 0;
	}

	public int NumberOfDigits(){
		return 0;
	}

	public int NumberOfWholeDigits(){
		return 0;
	}

	public boolean ObeySystemSettings(){
		return null;
	}

	/**
	 * 
	 * @param strNumber
	 */
	public double Parse(String strNumber){
		return 0;
	}

	/**
	 * 
	 * @param strNumber
	 * @param nfi
	 */
	private String PutGroupSeparator(String strNumber, NumberFormatInfo nfi){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 * @param groupSeparators
	 */
	private String RemoveGroupSeparators(String strNumber, char[] groupSeparators){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	public String RemoveNegativeSigns(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	private String RemoveSpaces(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	private String RemoveZeroDecimals(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param nStartIndex
	 * @param nGroupSizes
	 * @param strGroupSeparator
	 * @param strNumber
	 */
	private String RepeatGroupSeparator(int nStartIndex, int nGroupSizes, String strGroupSeparator, String strNumber){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 * @param nNumberOfDigits
	 */
	private String RoundUp(String strNumber, int nNumberOfDigits){
		return "";
	}

	public boolean ShowCurrency(){
		return null;
	}

	public boolean ShowSeparator(){
		return null;
	}

	/**
	 * 
	 * @param strNumber
	 */
	public String Unformat(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	private String UnformatCurrency(String strNumber){
		return "";
	}

	/**
	 * 
	 * @param strNumber
	 */
	private String UnformatNumber(String strNumber){
		return "";
	}

}