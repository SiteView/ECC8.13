package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:42
 */
public class TextFormat {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:42
	 */
	private enum MaskCharacter {
		None,
		Literal,
		LiteralEscape,
		UpperCase,
		LowerCase,
		Letter,
		LetterWithSpace,
		LetterNumber,
		LetterNumberWithSpace,
		LetterDigit,
		LetterDigitWithUnderscore,
		Character,
		Digit,
		Number,
		Hexadecimal,
		Octal,
		Binary
	}

	private char DEFAULTBLANK = ' ';
	private char DEFAULTDECIMALSEPARATOR = '.';
	private char DEFAULTNEGATIVESIGN = '-';
	private char INTERNALLITERAL = 'L';
	private boolean m_bAllowPush;
	private boolean m_bTrimStart;
	private Fusion.Xml.CharacterFormat m_CharacterFormat;
	private CultureInfo m_CultureInfo;
	private char m_HexLetters[];
	private char m_LetterMaskCharacters[];
	private String m_strDefaultMaskedText;
	private String m_strDefaultMaskedTextWithBlank;
	private String m_strMaskString;
	private char UNDERSCORE = '_';



	public void finalize() throws Throwable {

	}

	public TextFormat(){

	}

	/**
	 * 
	 * @param characterFormat
	 * @param strMaskString
	 * @param bAllowPush
	 * @param bTrimStart
	 * @param cultureInfo
	 */
	public TextFormat(Fusion.Xml.CharacterFormat characterFormat, String strMaskString, boolean bAllowPush, boolean bTrimStart, CultureInfo cultureInfo){

	}

	/**
	 * 
	 * @param nPosition
	 * @param strText
	 */
	private String AdjustCase(int nPosition, String strText){
		return "";
	}

	public boolean AllowPush(){
		return null;
	}

	/**
	 * 
	 * @param nPosition
	 */
	public boolean BlankSymbolValidAt(int nPosition){
		return null;
	}

	/**
	 * 
	 * @param strText
	 * @param nStartPosition
	 * @param nLength
	 */
	public boolean CanPushTextToLeft(String strText, int nStartPosition, int nLength){
		return null;
	}

	/**
	 * 
	 * @param strText
	 * @param nStartPosition
	 * @param nLength
	 */
	public boolean CanPushTextToRight(String strText, int nStartPosition, int nLength){
		return null;
	}

	public Fusion.Xml.CharacterFormat CharacterFormat(){
		return null;
	}

	/**
	 * 
	 * @param tf
	 */
	public boolean Compare(TextFormat tf){
		return null;
	}

	/**
	 * 
	 * @param oldTextFormat
	 * @param strOldText
	 */
	public String ConvertFormat(TextFormat oldTextFormat, String strOldText){
		return "";
	}

	/**
	 * 
	 * @param strText
	 * @param nStartPosition
	 */
	public int CountConsecutiveLiteralCharacterBackward(String strText, int nStartPosition){
		return 0;
	}

	/**
	 * 
	 * @param strText
	 * @param nStartPosition
	 */
	public int CountConsecutiveLiteralCharacterForward(String strText, int nStartPosition){
		return 0;
	}

	/**
	 * 
	 * @param strText
	 */
	public String Format(String strText){
		return "";
	}

	/**
	 * 
	 * @param nStartPosition
	 * @param nLength
	 * @param strText
	 */
	public String Format(int nStartPosition, int nLength, String strText){
		return "";
	}

	/**
	 * 
	 * @param strText
	 */
	private String FormatCase(String strText){
		return "";
	}

	/**
	 * 
	 * @param nStartPosition
	 * @param nLength
	 * @param strText
	 */
	private String FormatMask(int nStartPosition, int nLength, String strText){
		return "";
	}

	/**
	 * 
	 * @param nStartPosition
	 * @param nLength
	 * @param strText
	 */
	private String FormatMaskLiteral(int nStartPosition, int nLength, String strText){
		return "";
	}

	/**
	 * 
	 * @param nStartPosition
	 * @param nLength
	 * @param cChar
	 */
	public String FormatTextToOverWrite(int nStartPosition, int nLength, char cChar){
		return "";
	}

	/**
	 * 
	 * @param nPosition
	 */
	private Fusion.Xml.CharacterFormat GetCharacterFormat(int nPosition){
		return null;
	}

	/**
	 * 
	 * @param strText
	 */
	public int GetCountBlankSymbolsFromEnd(String strText){
		return 0;
	}

	private CultureInfo GetCultureInfo(){
		return null;
	}

	private char GetDecimalSeparator(){
		return 0;
	}

	private String GetDefaultCasedText(){
		return "";
	}

	/**
	 * 
	 * @param bUseDefaultBlank
	 */
	protected String GetDefaultMaskedText(boolean bUseDefaultBlank){
		return "";
	}

	public String GetDefaultValue(){
		return "";
	}

	/**
	 * 
	 * @param strText
	 * @param nStartPosition
	 * @param nLength
	 */
	public int GetLastCharPosition(String strText, int nStartPosition, int nLength){
		return 0;
	}

	/**
	 * 
	 * @param nPosition
	 */
	private char GetLiteral(int nPosition){
		return 0;
	}

	/**
	 * 
	 * @param nStartPosition
	 * @param nLength
	 */
	public ArrayList GetLiteralPositions(int nStartPosition, int nLength){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private MaskCharacter GetMaskCharacter(char cChar){
		return null;
	}

	/**
	 * 
	 * @param nPosition
	 */
	private MaskCharacter GetMaskCharacter(int nPosition){
		return null;
	}

	private int GetMaskedTextLength(){
		return 0;
	}

	private char GetNegativeSign(){
		return 0;
	}

	/**
	 * 
	 * @param nStartPosition
	 * @param nLength
	 */
	public ArrayList GetNonLiteralPositions(int nStartPosition, int nLength){
		return null;
	}

	private NumberFormatInfo GetNumberFormat(){
		return null;
	}

	/**
	 * 
	 * @param strText
	 */
	public int GetTextLength(String strText){
		return 0;
	}

	/**
	 * 
	 * @param strText
	 * @param nPosition
	 */
	public boolean HasEmpty(String strText, int nPosition){
		return null;
	}

	/**
	 * 
	 * @param strText
	 * @param nStartPosition
	 * @param strTextToInsert
	 */
	private String InsertMaskedText(String strText, int nStartPosition, String strTextToInsert){
		return "";
	}

	/**
	 * 
	 * @param strText
	 * @param nStartPosition
	 * @param strTextToInsert
	 */
	public String InsertText(String strText, int nStartPosition, String strTextToInsert){
		return "";
	}

	private boolean IsAllowPush(){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsBinary(char cChar){
		return null;
	}

	/**
	 * 
	 * @param strText
	 */
	private boolean IsCaseFormatted(String strText){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsCharacter(char cChar){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsDigit(char cChar){
		return null;
	}

	/**
	 * 
	 * @param strText
	 */
	public boolean IsEmpty(String strText){
		return null;
	}

	/**
	 * 
	 * @param strText
	 * @param nPosition
	 */
	public boolean IsEmpty(String strText, int nPosition){
		return null;
	}

	/**
	 * 
	 * @param strText
	 */
	public boolean IsFormatted(String strText){
		return null;
	}

	/**
	 * 
	 * @param nStartPosition
	 * @param nLength
	 * @param strText
	 */
	public boolean IsFormatted(int nStartPosition, int nLength, String strText){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsHexLetter(char cChar){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsLetter(char cChar){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsLetterDigit(char cChar){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsLetterDigitUnderscore(char cChar){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsLetterNumber(char cChar){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsLetterNumberWithSpace(char cChar){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsLetterWithSpace(char cChar){
		return null;
	}

	/**
	 * 
	 * @param nPosition
	 */
	private boolean IsLiteral(int nPosition){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsLower(char cChar){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsLowerLetter(char cChar){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	public static boolean IsMaskChar(char cChar){
		return null;
	}

	public boolean IsMasked(){
		return null;
	}

	/**
	 * 
	 * @param nStartPosition
	 * @param nLength
	 * @param strText
	 */
	private boolean IsMaskFormatted(int nStartPosition, int nLength, String strText){
		return null;
	}

	/**
	 * 
	 * @param nStartPosition
	 * @param nLength
	 * @param strText
	 */
	private boolean IsMaskLiteralFormatted(int nStartPosition, int nLength, String strText){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsNumber(char cChar){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsOctal(char cChar){
		return null;
	}

	/**
	 * 
	 * @param nPosition
	 * @param cChar
	 */
	public boolean IsPriviousLiteral(int nPosition, char cChar){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsUpper(char cChar){
		return null;
	}

	/**
	 * 
	 * @param cChar
	 */
	private boolean IsUpperLetter(char cChar){
		return null;
	}

	/**
	 * 
	 * @param nPosition
	 * @param cChar
	 */
	public boolean IsValidLiteral(int nPosition, char cChar){
		return null;
	}

	public CultureInfo Language(){
		return null;
	}

	public String MaskString(){
		return "";
	}

	/**
	 * 
	 * @param strText
	 * @param nStartPosition
	 * @param nLength
	 * @param strTextToOverWrite
	 */
	public String OverWriteText(String strText, int nStartPosition, int nLength, String strTextToOverWrite){
		return "";
	}

	/**
	 * 
	 * @param strText
	 * @param nStartPosition
	 * @param nLength
	 */
	public String PushTextToLeft(String strText, int nStartPosition, int nLength){
		return "";
	}

	/**
	 * 
	 * @param strText
	 * @param nStartPosition
	 * @param nLength
	 */
	public String PushTextToRight(String strText, int nStartPosition, int nLength){
		return "";
	}

	/**
	 * 
	 * @param strText
	 * @param nStartPosition
	 * @param nLength
	 */
	public String RemoveText(String strText, int nStartPosition, int nLength){
		return "";
	}

	/**
	 * 
	 * @param strText
	 */
	private String TrimLiteralCharacters(String strText){
		return "";
	}

	public boolean TrimStart(){
		return null;
	}

	/**
	 * 
	 * @param strText
	 */
	private String TrimToFormat(String strText){
		return "";
	}

	/**
	 * 
	 * @param strText
	 */
	public String Unformat(String strText){
		return "";
	}

	/**
	 * 
	 * @param nPosition
	 * @param cChar
	 */
	public boolean ValidateChar(int nPosition, char cChar){
		return null;
	}

}