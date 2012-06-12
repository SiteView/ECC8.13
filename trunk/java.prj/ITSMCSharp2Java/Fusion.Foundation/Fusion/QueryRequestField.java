package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:42
 */
public class QueryRequestField {

	private ArrayList m_alRelationships;
	private String m_strAlias;
	private String m_strFieldName;



	public void finalize() throws Throwable {

	}

	public QueryRequestField(){

	}

	/**
	 * 
	 * @param strBusObFieldName
	 */
	public QueryRequestField(String strBusObFieldName){

	}

	/**
	 * 
	 * @param queryRelationshipInfo
	 */
	public int AddQueryRelationshipInfo(QueryRelationshipInfo queryRelationshipInfo){
		return 0;
	}

	public String Alias(){
		return "";
	}

	public String BusObFieldName(){
		return "";
	}

	public String BusObName(){
		return "";
	}

	public QueryRequestField Copy(){
		return null;
	}

	/**
	 * 
	 * @param strQualifiedValue
	 */
	public static QueryRequestField Create(String strQualifiedValue){
		return null;
	}

	public String FieldName(){
		return "";
	}

	/**
	 * 
	 * @param queryRelationshipInfo
	 */
	private boolean HasQueryRelationshipInfo(QueryRelationshipInfo queryRelationshipInfo){
		return null;
	}

	/**
	 * 
	 * @param nIndex
	 * @param queryRelationshipInfo
	 */
	public void InsertQueryRelationshipInfo(int nIndex, QueryRelationshipInfo queryRelationshipInfo){

	}

	/**
	 * 
	 * @param nIndex
	 * @param queryRelationshipInfos
	 */
	public void InsertQueryRelationshipInfos(int nIndex, QueryRelationshipInfo[] queryRelationshipInfos){

	}

	public String QualifiedValue(){
		return "";
	}

	public QueryRelationshipInfo[] QueryRelationshipInfos(){
		return null;
	}

	/**
	 * 
	 * @param QueryRelationshipInfo
	 */
	public void RemoveQueryRelationshipInfo(QueryRelationshipInfo QueryRelationshipInfo){

	}

	/**
	 * 
	 * @param nIndex
	 */
	public void RempveQueryRelationshipInfoAt(int nIndex){

	}

	/**
	 * 
	 * @param strQualifiedValue
	 */
	private static string[] Split(String strQualifiedValue){
		return "";
	}

	/**
	 * 
	 * @param strColumnName
	 */
	public static String TranslateColumnName(String strColumnName){
		return "";
	}

	public String VirtualKeyFieldValue(){
		return "";
	}

}