package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:33
 */
public class TagConversionHelper {

	private String LeftBracket = "[";
	private String RightBracket = "]";
	private String TagCargo = "Cargo";
	private String TagDispText = "DispText";
	private String TagRoot = "ExprBldrLink";

	public TagConversionHelper(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strName
	 * @param strRelationship
	 * @param strLinkField
	 */
	public static String BuildSubcategoryBusObInfo(String strName, String strRelationship, String strLinkField){
		return "";
	}

	/**
	 * 
	 * @param tagInfo
	 */
	public static String BuildTag(Fusion.TagInfo tagInfo){
		return "";
	}

	/**
	 * 
	 * @param info
	 */
	public static String BuildXmlTag(TagItemInfo info){
		return "";
	}

	/**
	 * 
	 * @param strCategory
	 * @param strSubcategory
	 * @param strItem
	 */
	public static String BuildXmlTag(String strCategory, String strSubcategory, String strItem){
		return "";
	}

	/**
	 * 
	 * @param strPersistedContents
	 */
	public static boolean ContentsHasTags(String strPersistedContents){
		return null;
	}

	/**
	 * 
	 * @param strPersistedContents
	 */
	public static String ConvertContentsForDisplaying(String strPersistedContents){
		return "";
	}

	/**
	 * 
	 * @param strPersistedContents
	 */
	public static String ConvertContentsForResolving(String strPersistedContents){
		return "";
	}

	/**
	 * 
	 * @param correction
	 * @param bJustCollect
	 * @param strAssociatedBusOb
	 * @param strXmlTag
	 */
	public static boolean CorrectNamedReferenceInTag(NamedReferenceCorrection correction, boolean bJustCollect, String strAssociatedBusOb, String strXmlTag){
		return null;
	}

	public static String DetailedTagFormat(){
		return "";
	}

	/**
	 * 
	 * @param strDisplayText
	 */
	private static String FormatDisplayText(String strDisplayText){
		return "";
	}

	/**
	 * 
	 * @param strXml
	 */
	private static String GetCargoFromXml(String strXml){
		return "";
	}

	/**
	 * 
	 * @param match
	 */
	private static String GetContentsForDisplayingMatchEvaluator(Match match){
		return "";
	}

	/**
	 * 
	 * @param match
	 */
	private static String GetContentsForResolvingMatchEvaluator(Match match){
		return "";
	}

	/**
	 * 
	 * @param strXml
	 */
	public static String GetDisplayTextFromXml(String strXml){
		return "";
	}

	public String getLeftBracket(){
		return LeftBracket;
	}

	public String getRightBracket(){
		return RightBracket;
	}

	public String getTagCargo(){
		return TagCargo;
	}

	public String getTagDispText(){
		return TagDispText;
	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public static String GetTagFormatRegExForTagCategory(String strTagCategoryName){
		return "";
	}

	/**
	 * 
	 * @param strTagCategoryName
	 * @param strTagSubCategory
	 */
	public static String GetTagFormatRegExForTagCategoryAndSubCategory(String strTagCategoryName, String strTagSubCategory){
		return "";
	}

	/**
	 * 
	 * @param strPersistedContents
	 */
	public static IList GetTagInfosFromContents(String strPersistedContents){
		return null;
	}

	public String getTagRoot(){
		return TagRoot;
	}

	/**
	 * 
	 * @param strSubcategory
	 * @param strBusObName
	 * @param strRelationship
	 * @param strLinkField
	 */
	public static void ParseSubcategoryBusObInfo(String strSubcategory, String strBusObName, String strRelationship, String strLinkField){

	}

	/**
	 * 
	 * @param strXml
	 */
	public static Fusion.TagInfo ParseTag(String strXml){
		return null;
	}

	/**
	 * 
	 * @param strTag
	 * @param strCategory
	 * @param strSubcategory
	 * @param strItem
	 */
	public static void ParseXmlTag(String strTag, String strCategory, String strSubcategory, String strItem){

	}

	private static String RelatedBusObNameFormat(){
		return "";
	}

	private static String RelatedBusObNameFormatRegEx(){
		return "";
	}

	private static String RelatedBusObNameWithLinkFormat(){
		return "";
	}

	private static String RelatedBusObNameWithLinkFormatRegEx(){
		return "";
	}

	/**
	 * 
	 * @param strPersistedContents
	 * @param lstTagInfos
	 */
	public static String ReplaceContentsWithTagInfos(String strPersistedContents, IList lstTagInfos){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLeftBracket(String newVal){
		LeftBracket = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRightBracket(String newVal){
		RightBracket = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTagCargo(String newVal){
		TagCargo = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTagDispText(String newVal){
		TagDispText = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTagRoot(String newVal){
		TagRoot = newVal;
	}

	public static String TagFormat(){
		return "";
	}

	public static String TagFormatParseRegEx(){
		return "";
	}

	public static String TagFormatRegEx(){
		return "";
	}

}