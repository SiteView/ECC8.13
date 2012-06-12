package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-四月-2010 11:37:21
 */
public class AdrResult {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 22-四月-2010 11:37:21
	 */
	public class Tags {

		private string AdrResult = "AdrResult";
		private string AdrResultList = "AdrResultList";
		private string Alias = "Alias";
		private string AssociatedImage = "AssociatedImage";
		private string Category = "Category";
		private string ClassCategory = "ClassCategory";
		private string Count = "Count";
		private string DefClassName = "DefClassName";
		private string Description = "Description";
		private string Flags = "Flags";
		private string Folder = "Folder";
		private string Fusion = "Fusion";
		private string Id = "ID";
		private string LinkedTo = "LinkedTo";
		private string Name = "Name";
		private string Owner = "Owner";
		private string Perspective = "Perspective";
		private string Placeholder = "Placeholder";
		private string Scope = "Scope";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public string getAdrResult(){
			return AdrResult;
		}

		public string getAdrResultList(){
			return AdrResultList;
		}

		public string getAlias(){
			return Alias;
		}

		public string getAssociatedImage(){
			return AssociatedImage;
		}

		public string getCategory(){
			return Category;
		}

		public string getClassCategory(){
			return ClassCategory;
		}

		public string getCount(){
			return Count;
		}

		public string getDefClassName(){
			return DefClassName;
		}

		public string getDescription(){
			return Description;
		}

		public string getFlags(){
			return Flags;
		}

		public string getFolder(){
			return Folder;
		}

		public string getFusion(){
			return Fusion;
		}

		public string getId(){
			return Id;
		}

		public string getLinkedTo(){
			return LinkedTo;
		}

		public string getName(){
			return Name;
		}

		public string getOwner(){
			return Owner;
		}

		public string getPerspective(){
			return Perspective;
		}

		public string getPlaceholder(){
			return Placeholder;
		}

		public string getScope(){
			return Scope;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAdrResult(string newVal){
			AdrResult = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAdrResultList(string newVal){
			AdrResultList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAlias(string newVal){
			Alias = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAssociatedImage(string newVal){
			AssociatedImage = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCategory(string newVal){
			Category = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setClassCategory(string newVal){
			ClassCategory = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCount(string newVal){
			Count = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDefClassName(string newVal){
			DefClassName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDescription(string newVal){
			Description = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFlags(string newVal){
			Flags = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFolder(string newVal){
			Folder = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFusion(string newVal){
			Fusion = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setId(string newVal){
			Id = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLinkedTo(string newVal){
			LinkedTo = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setName(string newVal){
			Name = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setOwner(string newVal){
			Owner = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPerspective(string newVal){
			Perspective = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPlaceholder(string newVal){
			Placeholder = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setScope(string newVal){
			Scope = newVal;
		}

	}

	private bool m_bInResult = false;
	private bool m_bInScope = false;
	private bool m_bReadMode = true;
	private XmlDocument m_docReader = null;
	private IEnumerator m_ResultListEnumerator = null;
	private IEnumerator m_ScopeListEnumerator = null;
	private StringWriter m_writerString = null;
	private XmlTextWriter m_writerXml = null;
	private XmlNodeList m_xnlResultList = null;
	private XmlNodeList m_xnlScopeList = null;



	public void finalize() throws Throwable {

	}

	protected AdrResult(){

	}

	/**
	 * 
	 * @param strDef
	 */
	public void AddDef(string strDef){

	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param strPerspective
	 * @param strLinkedTo
	 */
	public void AddDeleteResult(string strDefClassName, string strId, string strPerspective, string strLinkedTo){

	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strName
	 * @param nCount
	 */
	public void AddDupeCheckResult(string strDefClassName, string strName, int nCount){

	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strLinkedTo
	 */
	public void AddItemListResult(string strDefClassName, string strLinkedTo){

	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strLinkedTo
	 */
	public void AddPlaceholderListResult(string strDefClassName, string strLinkedTo){

	}

	/**
	 * 
	 * @param strCategory
	 * @param strId
	 * @param strName
	 * @param strAlias
	 * @param strDesc
	 * @param strFolder
	 * @param strPerspective
	 * @param strLinkedTo
	 * @param strFlags
	 * @param strAssociatedImage
	 */
	public void AddPlaceholderListResultItem(string strCategory, string strId, string strName, string strAlias, string strDesc, string strFolder, string strPerspective, string strLinkedTo, string strFlags, string strAssociatedImage){

	}

	/**
	 * 
	 * @param resultCat
	 * @param strDefClassName
	 * @param strName
	 * @param strId
	 * @param strPerspective
	 * @param strLinkedTo
	 */
	public void AddResult(AdrQueryCategory resultCat, string strDefClassName, string strName, string strId, string strPerspective, string strLinkedTo){

	}

	/**
	 * 
	 * @param resultCat
	 * @param strDefClassName
	 * @param strName
	 * @param strId
	 * @param strPerspective
	 * @param strLinkedTo
	 * @param nCount
	 */
	public void AddResult(AdrQueryCategory resultCat, string strDefClassName, string strName, string strId, string strPerspective, string strLinkedTo, int nCount){

	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 */
	public void AddScope(Fusion.Xml.Scope scopeType, string strScopeOwner){

	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strName
	 * @param strId
	 * @param strPerspective
	 * @param strLinkedTo
	 */
	public void AddSpecifiedItemsResult(string strDefClassName, string strName, string strId, string strPerspective, string strLinkedTo){

	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param strPerspective
	 * @param strLinkedTo
	 */
	public void AddUpdateResult(string strDefClassName, string strId, string strPerspective, string strLinkedTo){

	}

	protected void ClearScope(){

	}

	protected void CloseCurrentResult(){

	}

	protected void CloseCurrentScope(){

	}

	protected void CloseFinalTags(){

	}

	/**
	 * 
	 * @param strXml
	 */
	protected void ConfigureAsReader(string strXml){

	}

	protected void ConfigureAsWriter(){

	}

	protected void ConfirmReadMode(){

	}

	protected void ConfirmWriteMode(){

	}

	/**
	 * 
	 * @param strXml
	 */
	public static AdrResult CreateFromResult(string strXml){
		return null;
	}

	public static AdrResult CreateWriter(){
		return null;
	}

	protected XmlElement CurrentResult(){
		return null;
	}

	protected XmlElement CurrentScope(){
		return null;
	}

	protected bool MoveToNextResult(){
		return null;
	}

	protected bool MoveToNextScope(){
		return null;
	}

	protected void OpenNewResult(){

	}

	protected void OpenNewScope(){

	}

	/**
	 * 
	 * @param resultCat
	 * @param strDefClassName
	 * @param strName
	 * @param strId
	 * @param strPerspective
	 * @param strLinkedTo
	 */
	public bool ReadNextResult(AdrQueryCategory resultCat, string strDefClassName, string strName, string strId, string strPerspective, string strLinkedTo){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param xnlItems
	 */
	public bool ReadNextScope(Fusion.Xml.Scope scopeType, string strScopeOwner, XmlNodeList xnlItems){
		return null;
	}

	/**
	 * 
	 * @param resultCat
	 * @param strDefClassName
	 * @param strName
	 * @param strId
	 * @param strLinkedTo
	 * @param nCount
	 */
	public bool ReadResultWithCount(AdrQueryCategory resultCat, string strDefClassName, string strName, string strId, string strLinkedTo, int nCount){
		return null;
	}

	public string ToXml(){
		return "";
	}

	/**
	 * 
	 * @param strTag
	 * @param strContent
	 * @param bWriteIfEmpty
	 */
	protected void WriteCompleteTag(string strTag, string strContent, bool bWriteIfEmpty){

	}

}