package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:09
 */
public class DefRequest {

	private boolean m_bAutoScopeOwner = false;
	private boolean m_bStepUpChain = false;
	private boolean m_bUseId = false;
	private PlaceHolder m_PlaceHolder = null;
	private ResourceInfo m_ResourceInfo = null;
	private Scope m_scopeType = Scope.Global;
	private String m_strCategory = "";
	private String m_strId = "";
	private String m_strLinkedTo = "";
	private String m_strName = "";
	private String m_strPerspective = "(Base)";
	private String m_strScopeOwner = "GLOBAL";
	private String m_strType = "";



	public void finalize() throws Throwable {

	}

	private DefRequest(){

	}

	public boolean AutoScopeOwner(){
		return null;
	}

	/**
	 * 
	 * @param strType
	 */
	public static DefRequest ByCategory(String strType){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strCategory
	 */
	public static DefRequest ByCategory(String strType, String strCategory){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strCategory
	 * @param strPerspective
	 */
	public static DefRequest ByCategory(String strType, String strCategory, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strType
	 * @param strCategory
	 */
	public static DefRequest ByCategory(Scope scopeType, String strScopeOwner, String strType, String strCategory){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strType
	 * @param strCategory
	 * @param strPerspective
	 */
	public static DefRequest ByCategory(Scope scopeType, String strScopeOwner, String strType, String strCategory, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param holder
	 */
	public static DefRequest ByHolder(PlaceHolder holder){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strId
	 */
	public static DefRequest ById(String strType, String strId){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strId
	 * @param strPerspective
	 */
	public static DefRequest ById(String strType, String strId, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strType
	 * @param strId
	 * @param bStepUpChain
	 */
	public static DefRequest ById(Scope scopeType, String strScopeOwner, String strType, String strId, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strType
	 * @param strId
	 */
	public static DefRequest ById(Scope scopeType, String strScopeOwner, String strLinkedTo, String strType, String strId){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strType
	 * @param strId
	 * @param bStepUpChain
	 */
	public static DefRequest ById(Scope scopeType, String strScopeOwner, String strLinkedTo, String strType, String strId, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strType
	 * @param strId
	 * @param strPerspective
	 * @param bStepUpChain
	 */
	public static DefRequest ById(Scope scopeType, String strScopeOwner, String strLinkedTo, String strType, String strId, String strPerspective, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strName
	 */
	public static DefRequest ByName(String strType, String strName){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strName
	 * @param strPerspective
	 */
	public static DefRequest ByName(String strType, String strName, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strType
	 * @param strName
	 */
	public static DefRequest ByName(Scope scopeType, String strScopeOwner, String strType, String strName){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strType
	 * @param strName
	 * @param bStepUpChain
	 */
	public static DefRequest ByName(Scope scopeType, String strScopeOwner, String strType, String strName, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strType
	 * @param strName
	 * @param bStepUpChain
	 */
	public static DefRequest ByName(Scope scopeType, String strScopeOwner, String strLinkedTo, String strType, String strName, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strType
	 * @param strName
	 * @param strPerspective
	 * @param bStepUpChain
	 */
	public static DefRequest ByName(Scope scopeType, String strScopeOwner, String strLinkedTo, String strType, String strName, String strPerspective, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strType
	 * @param strName
	 * @param strPerspective
	 * @param bStepUpChain
	 */
	public static DefRequest ByNameAndPerspective(Scope scopeType, String strScopeOwner, String strType, String strName, String strPerspective, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param ri
	 */
	public static DefRequest ByResource(String strType, ResourceInfo ri){
		return null;
	}

	public String Category(){
		return "";
	}

	public String DefType(){
		return "";
	}

	/**
	 * 
	 * @param strType
	 * @param strId
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strName
	 */
	public static DefRequest ForDupeCheck(String strType, String strId, Scope scopeType, String strScopeOwner, String strName){
		return null;
	}

	/**
	 * 
	 * @param strType
	 */
	public static DefRequest ForList(String strType){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strPerspective
	 */
	public static DefRequest ForList(String strType, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strType
	 */
	public static DefRequest ForList(Scope scopeType, String strScopeOwner, String strType){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strType
	 */
	public static DefRequest ForList(Scope scopeType, String strScopeOwner, String strLinkedTo, String strType){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strType
	 * @param strPerspective
	 */
	public static DefRequest ForList(Scope scopeType, String strScopeOwner, String strLinkedTo, String strType, String strPerspective){
		return null;
	}

	public PlaceHolder Holder(){
		return null;
	}

	public String Id(){
		return "";
	}

	public String LinkedTo(){
		return "";
	}

	public String Name(){
		return "";
	}

	public String Perspective(){
		return "";
	}

	public ResourceInfo ResInfo(){
		return null;
	}

	public String ScopeOwner(){
		return "";
	}

	public Scope ScopeType(){
		return null;
	}

	public boolean StepUpChain(){
		return null;
	}

	public boolean UseId(){
		return null;
	}

	public boolean UseName(){
		return null;
	}

	public boolean UsePlaceHolder(){
		return null;
	}

	public boolean UseResourceInfo(){
		return null;
	}

}