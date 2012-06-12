package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:41
 */
public class QueryRelationshipInfo {

	private char JoinCategoryWrapperEnd = ')';
	private char JoinCategoryWrapperStart = '(';
	private char LinkPurposeSeparator = ',';
	private QueryJoinCategory m_QueryJoinCategory;
	private String m_strLinkFieldOrPurpose;
	private String m_strRelationshipName;
	private char PurposeWrapperEnd = ')';
	private char PurposeWrapperStart = '(';
	private char RelationshipWrapperEnd = ']';
	private char RelationshipWrapperStart = '[';

	public QueryRelationshipInfo(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param queryJoinCategory
	 * @param strRelationshipName
	 * @param strLinkFieldOrPurpose
	 */
	public QueryRelationshipInfo(QueryJoinCategory queryJoinCategory, String strRelationshipName, String strLinkFieldOrPurpose){

	}

	public QueryRelationshipInfo Copy(){
		return null;
	}

	public char getJoinCategoryWrapperEnd(){
		return JoinCategoryWrapperEnd;
	}

	public char getJoinCategoryWrapperStart(){
		return JoinCategoryWrapperStart;
	}

	public char getLinkPurposeSeparator(){
		return LinkPurposeSeparator;
	}

	/**
	 * 
	 * @param strLinkField
	 */
	public static String GetPurposeFromLinkField(String strLinkField){
		return "";
	}

	public char getPurposeWrapperEnd(){
		return PurposeWrapperEnd;
	}

	public char getPurposeWrapperStart(){
		return PurposeWrapperStart;
	}

	public char getRelationshipWrapperEnd(){
		return RelationshipWrapperEnd;
	}

	public char getRelationshipWrapperStart(){
		return RelationshipWrapperStart;
	}

	public QueryJoinCategory JoinType(){
		return null;
	}

	/**
	 * 
	 * @param strLinkField
	 */
	public static boolean LinkFieldIsPurpose(String strLinkField){
		return null;
	}

	public String LinkFieldOrPurpose(){
		return "";
	}

	public String QualifiedValue(){
		return "";
	}

	public String RelationshipName(){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setJoinCategoryWrapperEnd(char newVal){
		JoinCategoryWrapperEnd = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setJoinCategoryWrapperStart(char newVal){
		JoinCategoryWrapperStart = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLinkPurposeSeparator(char newVal){
		LinkPurposeSeparator = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPurposeWrapperEnd(char newVal){
		PurposeWrapperEnd = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPurposeWrapperStart(char newVal){
		PurposeWrapperStart = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRelationshipWrapperEnd(char newVal){
		RelationshipWrapperEnd = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRelationshipWrapperStart(char newVal){
		RelationshipWrapperStart = newVal;
	}

	public String VirtualKeyFieldValue(){
		return "";
	}

}