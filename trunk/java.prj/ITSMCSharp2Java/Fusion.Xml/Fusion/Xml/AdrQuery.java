package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-四月-2010 11:37:20
 */
public class AdrQuery {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 22-四月-2010 11:37:20
	 */
	private class Tags {

		private string AdrQuery = "AdrQuery";
		private string AdrQueryList = "AdrQueryList";
		private string Alias = "Alias";
		private string AssociatedImage = "AssociatedImage";
		private string Category = "Category";
		private string CultureName = "CultureName";
		private string DefClassName = "DefClassName";
		private string Description = "Description";
		private string Flags = "Flags";
		private string Folder = "Folder";
		private string Fusion = "Fusion";
		private string Id = "Id";
		private string LinkedTo = "LinkedTo";
		private string Name = "Name";
		private string OriginalOwner = "OriginalOwner";
		private string OriginalScope = "OriginalScope";
		private string Owner = "Owner";
		private string Perspective = "Perspective";
		private string Scope = "Scope";
		private string Version = "Version";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public string getAdrQuery(){
			return AdrQuery;
		}

		public string getAdrQueryList(){
			return AdrQueryList;
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

		public string getCultureName(){
			return CultureName;
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

		public string getOriginalOwner(){
			return OriginalOwner;
		}

		public string getOriginalScope(){
			return OriginalScope;
		}

		public string getOwner(){
			return Owner;
		}

		public string getPerspective(){
			return Perspective;
		}

		public string getScope(){
			return Scope;
		}

		public string getVersion(){
			return Version;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAdrQuery(string newVal){
			AdrQuery = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAdrQueryList(string newVal){
			AdrQueryList = newVal;
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
		public void setCultureName(string newVal){
			CultureName = newVal;
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
		public void setOriginalOwner(string newVal){
			OriginalOwner = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setOriginalScope(string newVal){
			OriginalScope = newVal;
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
		public void setScope(string newVal){
			Scope = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setVersion(string newVal){
			Version = newVal;
		}

	}

	private bool m_bInQuery = false;
	private bool m_bReadMode = true;
	private XmlDocument m_docReader = null;
	private IEnumerator m_QueryListEnumerator = null;
	private IEnumerator m_ScopeListEnumerator = null;
	private StringWriter m_writerString = null;
	private XmlTextWriter m_writerXml = null;
	private XmlNodeList m_xnlQueryList = null;
	private XmlNodeList m_xnlScopeList = null;



	public void finalize() throws Throwable {

	}

	protected AdrQuery(){

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
	 * @param strName
	 * @param strId
	 * @param strPerspective
	 * @param strLinkedTo
	 */
	public void AddDeleteRequest(string strDefClassName, string strName, string strId, string strPerspective, string strLinkedTo){

	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strName
	 * @param strId
	 */
	public void AddDupeCheckRequest(string strDefClassName, string strName, string strId){

	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strLinkedTo
	 */
	public void AddItemListRequest(string strDefClassName, string strLinkedTo){

	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strLinkedTo
	 */
	public void AddPlaceholderListRequest(string strDefClassName, string strLinkedTo){

	}

	/**
	 * 
	 * @param queryCat
	 * @param strDefClassName
	 * @param strName
	 * @param strId
	 * @param strCultureName
	 * @param strPerspective
	 * @param strLinkedTo
	 */
	public void AddRequest(AdrQueryCategory queryCat, string strDefClassName, string strName, string strId, string strCultureName, string strPerspective, string strLinkedTo){

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
	 * @param scopeType
	 * @param strScopeOwner
	 * @param scopeTypeOriginal
	 * @param strScopeOwnerOriginal
	 * @param strFlags
	 * @param strDef
	 */
	public void AddScopeWithDef(Fusion.Xml.Scope scopeType, string strScopeOwner, Fusion.Xml.Scope scopeTypeOriginal, string strScopeOwnerOriginal, string strFlags, string strDef){

	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strName
	 * @param strId
	 * @param strPerspective
	 * @param strLinkedTo
	 */
	public void AddSpecifiedItemsRequest(string strDefClassName, string strName, string strId, string strPerspective, string strLinkedTo){

	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param strLinkedTo
	 * @param strCultureName
	 */
	public void AddUpdateRequest(string strDefClassName, string strId, string strLinkedTo, string strCultureName){

	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param strLinkedTo
	 * @param strPerspective
	 * @param strCultureName
	 */
	public void AddUpdateRequest(string strDefClassName, string strId, string strLinkedTo, string strPerspective, string strCultureName){

	}

	protected void ClearScope(){

	}

	protected void CloseCurrentQuery(){

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
	public static AdrQuery CreateFromQuery(string strXml){
		return null;
	}

	public static AdrQuery CreateWriter(){
		return null;
	}

	protected XmlElement CurrentQuery(){
		return null;
	}

	protected XmlElement CurrentScope(){
		return null;
	}

	protected bool MoveToNextQuery(){
		return null;
	}

	protected bool MoveToNextScope(){
		return null;
	}

	protected void OpenNewQuery(){

	}

	/**
	 * 
	 * @param queryCat
	 * @param strDefClassName
	 * @param strName
	 * @param strId
	 * @param strCultureName
	 * @param strPerspective
	 * @param strLinkedTo
	 */
	public bool ReadNextQuery(AdrQueryCategory queryCat, string strDefClassName, string strName, string strId, string strCultureName, string strPerspective, string strLinkedTo){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 */
	public bool ReadNextScope(Fusion.Xml.Scope scopeType, string strScopeOwner){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param scopeTypeOriginal
	 * @param strScopeOwnerOriginal
	 * @param strName
	 * @param iVersion
	 * @param strAlias
	 * @param strDescription
	 * @param strFolder
	 * @param strCategory
	 * @param strPerspective
	 * @param strLinkedTo
	 * @param strFlags
	 * @param strAssociatedImage
	 * @param strDef
	 */
	public bool ReadNextUpdateScope(Fusion.Xml.Scope scopeType, string strScopeOwner, Fusion.Xml.Scope scopeTypeOriginal, string strScopeOwnerOriginal, string strName, int iVersion, string strAlias, string strDescription, string strFolder, string strCategory, string strPerspective, string strLinkedTo, string strFlags, string strAssociatedImage, string strDef){
		return null;
	}

	public string ToXml(){
		return "";
	}

}