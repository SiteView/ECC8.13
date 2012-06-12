package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:45
 */
public class RelationshipQuery extends FusionQuery {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:45
	 */
	private class Tags {

		private String Category = "Category";
		private String Criteria = "Criteria";
		private String Info = "Info";
		private String Name = "Name";
		private String OrderByField = "OrderByField";
		private String OrderByList = "OrderByList";
		private String RelationshipQuery = "RelationshipQuery";
		private String RequestedField = "RequestedField";
		private String RequestedFieldList = "RequestedFieldList";
		private String SortOrder = "SortOrder";
		private String valAscending = "ASC";
		private String valDescending = "DESC";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getCategory(){
			return Category;
		}

		public String getCriteria(){
			return Criteria;
		}

		public String getInfo(){
			return Info;
		}

		public String getName(){
			return Name;
		}

		public String getOrderByField(){
			return OrderByField;
		}

		public String getOrderByList(){
			return OrderByList;
		}

		public String getRelationshipQuery(){
			return RelationshipQuery;
		}

		public String getRequestedField(){
			return RequestedField;
		}

		public String getRequestedFieldList(){
			return RequestedFieldList;
		}

		public String getSortOrder(){
			return SortOrder;
		}

		public String getvalAscending(){
			return valAscending;
		}

		public String getvalDescending(){
			return valDescending;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCategory(String newVal){
			Category = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCriteria(String newVal){
			Criteria = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setInfo(String newVal){
			Info = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setName(String newVal){
			Name = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setOrderByField(String newVal){
			OrderByField = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setOrderByList(String newVal){
			OrderByList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRelationshipQuery(String newVal){
			RelationshipQuery = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRequestedField(String newVal){
			RequestedField = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRequestedFieldList(String newVal){
			RequestedFieldList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSortOrder(String newVal){
			SortOrder = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setvalAscending(String newVal){
			valAscending = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setvalDescending(String newVal){
			valDescending = newVal;
		}

	}

	private String AllRelationships = "*";
	private boolean m_bRollUpQuery;
	private RelationshipCategory m_eCategory;
	private FusionQuery m_FusionQuery;
	private String m_strName;
	private String m_strRollUpDefId;
	private String m_strRollUpDefName;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public RelationshipQuery(){

	}

	/**
	 * 
	 * @param query
	 * @param eCategory
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 * @param astrQualifiedFieldNames
	 */
	public RelationshipQuery(FusionQuery query, RelationshipCategory eCategory, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet, string[] astrQualifiedFieldNames){

	}

	/**
	 * 
	 * @param query
	 * @param eCategory
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 * @param colQualifiedFieldNames
	 */
	public RelationshipQuery(FusionQuery query, RelationshipCategory eCategory, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet, List colQualifiedFieldNames){

	}

	/**
	 * 
	 * @param query
	 * @param strName
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 * @param astrQualifiedFieldNames
	 */
	public RelationshipQuery(FusionQuery query, String strName, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet, string[] astrQualifiedFieldNames){

	}

	/**
	 * 
	 * @param query
	 * @param strName
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 * @param colQualifiedFieldNames
	 */
	public RelationshipQuery(FusionQuery query, String strName, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet, List colQualifiedFieldNames){

	}

	public FusionQuery BusinessObjectQuery(){
		return null;
	}

	public RelationshipCategory Category(){
		return null;
	}

	public RelationshipQuery Clone(){
		return null;
	}

	/**
	 * 
	 * @param query
	 */
	public void CopyContents(RelationshipQuery query){

	}

	/**
	 * 
	 * @param xeRelationshipQuery
	 */
	public void FromXml(XmlElement xeRelationshipQuery){

	}

	public String getAllRelationships(){
		return AllRelationships;
	}

	/**
	 * 
	 * @param xeRelationshipQuery
	 */
	private void GetOrderByFieldsFromXml(XmlElement xeRelationshipQuery){

	}

	public String Name(){
		return "";
	}

	public String RollUpDefId(){
		return "";
	}

	public String RollUpDefName(){
		return "";
	}

	public boolean RollUpQuery(){
		return null;
	}

	public XmlElement SearchCriteria(){
		return null;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAllRelationships(String newVal){
		AllRelationships = newVal;
	}

	/**
	 * 
	 * @param writerXml
	 */
	public void ToXml(XmlTextWriter writerXml){

	}

}