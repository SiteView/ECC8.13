package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:36
 */
public class FusionValue extends IComparable {

	private byte m_aBinaryValue[];
	private static FusionValue m_BlankFusionValue = new FusionValue("");
	private boolean m_bValue;
	private CultureInfo m_CultureInfo;
	private Fusion.Xml.DateFormat m_DateFormat;
	private Fusion.DateTimeCategory m_DateTimeCategory;
	private DateTime m_dtValue;
	private decimal m_dValue;
	private static FusionValue m_FalseFusionValue = new FusionValue(false);
	private String m_strCustomDateFormat;
	private String m_strCustomFormat;
	private String m_strCustomTimeFormat;
	private String m_strValue;
	private Fusion.Xml.TimeFormat m_TimeFormat;
	private static FusionValue m_TrueFusionValue = new FusionValue(true);
	private FieldCategory m_typeNative;

	public FusionValue(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param bValue
	 */
	public FusionValue(boolean bValue){

	}

	/**
	 * 
	 * @param dtValue
	 */
	public FusionValue(DateTime dtValue){

	}

	/**
	 * 
	 * @param dValue
	 */
	public FusionValue(decimal dValue){

	}

	/**
	 * 
	 * @param o
	 */
	public FusionValue(Object o){

	}

	/**
	 * 
	 * @param aBytes
	 */
	public FusionValue(byte[] aBytes){

	}

	/**
	 * 
	 * @param strValue
	 */
	public FusionValue(String strValue){

	}

	/**
	 * 
	 * @param fv1
	 * @param fv2
	 */
	public static int BinaryCompare(FusionValue fv1, FusionValue fv2){
		return 0;
	}

	/**
	 * 
	 * @param fv1
	 * @param fv2
	 * @param bConservative
	 */
	public static int BinaryCompare(FusionValue fv1, FusionValue fv2, boolean bConservative){
		return 0;
	}

	public static FusionValue Blank(){
		return null;
	}

	/**
	 * 
	 * @param fv
	 */
	public int Compare(FusionValue fv){
		return 0;
	}

	/**
	 * 
	 * @param fv
	 * @param bConservative
	 */
	public int Compare(FusionValue fv, boolean bConservative){
		return 0;
	}

	/**
	 * 
	 * @param fv
	 */
	public int CompareAsDates(FusionValue fv){
		return 0;
	}

	/**
	 * 
	 * @param fv
	 * @param bConservative
	 */
	public int CompareAsDates(FusionValue fv, boolean bConservative){
		return 0;
	}

	/**
	 * 
	 * @param fv
	 */
	public int CompareAsDateTime(FusionValue fv){
		return 0;
	}

	/**
	 * 
	 * @param fv
	 * @param bConservative
	 */
	public int CompareAsDateTime(FusionValue fv, boolean bConservative){
		return 0;
	}

	/**
	 * 
	 * @param fv
	 */
	public int CompareAsLogical(FusionValue fv){
		return 0;
	}

	/**
	 * 
	 * @param fv
	 * @param bConservative
	 */
	public int CompareAsLogical(FusionValue fv, boolean bConservative){
		return 0;
	}

	/**
	 * 
	 * @param fv
	 */
	public int CompareAsNumber(FusionValue fv){
		return 0;
	}

	/**
	 * 
	 * @param fv
	 * @param bConservative
	 */
	public int CompareAsNumber(FusionValue fv, boolean bConservative){
		return 0;
	}

	/**
	 * 
	 * @param fv
	 */
	public int CompareAsText(FusionValue fv){
		return 0;
	}

	/**
	 * 
	 * @param fv
	 * @param bConservative
	 */
	public int CompareAsText(FusionValue fv, boolean bConservative){
		return 0;
	}

	/**
	 * 
	 * @param fv
	 */
	public int CompareTo(Object fv){
		return 0;
	}

	/**
	 * 
	 * @param rightValue
	 */
	public int CompareValue(Object rightValue){
		return 0;
	}

	/**
	 * 
	 * @param fvConvert
	 * @param catFieldToConvertTo
	 */
	public static FusionValue ConvertToDataType(FusionValue fvConvert, FieldCategory catFieldToConvertTo){
		return null;
	}

	public FieldCategory DataType(){
		return null;
	}

	/**
	 * 
	 * @param fv1
	 * @param fv2
	 * @param bConservative
	 */
	public static int DateCompare(FusionValue fv1, FusionValue fv2, boolean bConservative){
		return 0;
	}

	public Fusion.Xml.DateFormat DateFormat(){
		return null;
	}

	public Fusion.DateTimeCategory DateTimeCategory(){
		return null;
	}

	/**
	 * 
	 * @param fv1
	 * @param fv2
	 */
	public static int DateTimeCompare(FusionValue fv1, FusionValue fv2){
		return 0;
	}

	/**
	 * 
	 * @param fv1
	 * @param fv2
	 * @param bConservative
	 */
	public static int DateTimeCompare(FusionValue fv1, FusionValue fv2, boolean bConservative){
		return 0;
	}

	public boolean Empty(){
		return null;
	}

	public static FusionValue False(){
		return null;
	}

	/**
	 * 
	 * @param m_dtValue
	 */
	private String GetDataTimeValue(DateTime m_dtValue){
		return "";
	}

	private String GetShortTimePattern(){
		return "";
	}

	/**
	 * 
	 * @param fvPattern
	 * @param bIgnoreCase
	 */
	public boolean IsMatch(FusionValue fvPattern, boolean bIgnoreCase){
		return null;
	}

	/**
	 * 
	 * @param fv1
	 * @param fv2
	 * @param bIgnoreCase
	 */
	private static boolean IsMatch(FusionValue fv1, FusionValue fv2, boolean bIgnoreCase){
		return null;
	}

	/**
	 * 
	 * @param fv1
	 * @param fv2
	 */
	public static int LogicalCompare(FusionValue fv1, FusionValue fv2){
		return 0;
	}

	/**
	 * 
	 * @param fv1
	 * @param fv2
	 * @param bConservative
	 */
	public static int LogicalCompare(FusionValue fv1, FusionValue fv2, boolean bConservative){
		return 0;
	}

	/**
	 * 
	 * @param fv1
	 * @param fv2
	 */
	public static int NumberCompare(FusionValue fv1, FusionValue fv2){
		return 0;
	}

	/**
	 * 
	 * @param fv1
	 * @param fv2
	 * @param bConservative
	 */
	public static int NumberCompare(FusionValue fv1, FusionValue fv2, boolean bConservative){
		return 0;
	}

	/**
	 * 
	 * @param oValue
	 */
	public static String ObjectToString(Object oValue){
		return "";
	}

	/**
	 * 
	 * @param oValue
	 * @param provider
	 */
	public static String ObjectToString(Object oValue, IFormatProvider provider){
		return "";
	}

	/**
	 * 
	 * @param cat
	 */
	public static String StringFromType(FieldCategory cat){
		return "";
	}

	public Type SystemType(){
		return null;
	}

	/**
	 * 
	 * @param fv1
	 * @param fv2
	 */
	public static int TextCompare(FusionValue fv1, FusionValue fv2){
		return 0;
	}

	/**
	 * 
	 * @param fv1
	 * @param fv2
	 * @param bConservative
	 */
	public static int TextCompare(FusionValue fv1, FusionValue fv2, boolean bConservative){
		return 0;
	}

	public Fusion.Xml.TimeFormat TimeFormat(){
		return null;
	}

	public byte[] ToBinary(){
		return 0;
	}

	public boolean ToBool(){
		return null;
	}

	public DateTime ToDateTime(){
		return null;
	}

	public String ToInvariantCultureString(){
		return "";
	}

	public boolean ToLogical(){
		return null;
	}

	public decimal ToNumber(){
		return 0;
	}

	public Object ToObject(){
		return null;
	}

	public String ToString(){
		return "";
	}

	public String ToText(){
		return "";
	}

	/**
	 * 
	 * @param cultureinfo
	 */
	public String ToText(CultureInfo cultureinfo){
		return "";
	}

	public static FusionValue True(){
		return null;
	}

	/**
	 * 
	 * @param strType
	 */
	public static FieldCategory TypeFromString(String strType){
		return null;
	}

	public String Visualize(){
		return "";
	}

}