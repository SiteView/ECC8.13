package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:31
 */
public class FusionQuery extends IDeserializationCallback {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:31
	 */
	public class RelationshipPageInfo {

		private String m_sID = null;
		private String m_sRelToPage = null;

		public RelationshipPageInfo(){

		}

		public void finalize() throws Throwable {

		}

		/**
		 * 
		 * @param sRelName
		 * @param sMainBOID
		 */
		public RelationshipPageInfo(String sRelName, String sMainBOID){

		}

		public String MainBOID(){
			return "";
		}

		public String RelToPage(){
			return "";
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:31
	 */
	private class Tags {

		private String Before = "Before";
		private String BusinessObjectQuery = "BusinessObjectQuery";
		private String BusinessObjectQueryList = "BusinessObjectQueryList";
		private String CacheRequested = "CacheRequested";
		private String Criteria = "Criteria";
		private String Field = "Field";
		private String FilterOutDuplicateData = "FilterOutDuplicateData";
		private String First = "First";
		private String FusionQuery = "FusionQuery";
		private String GetAllMembersOfGroup = "GetAllMembersOfGroup";
		private String GroupByItemList = "GroupByItemList";
		private String IgnoreMissingFields = "IgnoreMissingFields";
		private String Info = "Info";
		private String LargeTextFields = "LargeTextFields";
		private String Last = "Last";
		private String LastOrderByValue = "LastOrderByValue";
		private String LastOrderByValues = "LastOrderByValues";
		private String Length = "Length";
		private String ListProperties = "ListProperties";
		private String Location = "Location";
		private String Max = "Max";
		private String Name = "Name";
		private String Next = "Next";
		private String Parameter = "ParameterDef";
		private String ParameterList = "SearchParameterList";
		private String Prev = "Prev";
		private String QueryId = "QueryID";
		private String RelationshipQuery = "RelationshipQuery";
		private String RelationshipQueryList = "RelationshipQueryList";
		private String RequestedField = "RequestedField";
		private String RequestedFieldList = "RequestedFieldList";
		private String RequestedFunctionList = "RequestedFunctionList";
		private String Trim = "Trim";
		private String VirtualMode = "VirtualMode";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getBefore(){
			return Before;
		}

		public String getBusinessObjectQuery(){
			return BusinessObjectQuery;
		}

		public String getBusinessObjectQueryList(){
			return BusinessObjectQueryList;
		}

		public String getCacheRequested(){
			return CacheRequested;
		}

		public String getCriteria(){
			return Criteria;
		}

		public String getField(){
			return Field;
		}

		public String getFilterOutDuplicateData(){
			return FilterOutDuplicateData;
		}

		public String getFirst(){
			return First;
		}

		public String getFusionQuery(){
			return FusionQuery;
		}

		public String getGetAllMembersOfGroup(){
			return GetAllMembersOfGroup;
		}

		public String getGroupByItemList(){
			return GroupByItemList;
		}

		public String getIgnoreMissingFields(){
			return IgnoreMissingFields;
		}

		public String getInfo(){
			return Info;
		}

		public String getLargeTextFields(){
			return LargeTextFields;
		}

		public String getLast(){
			return Last;
		}

		public String getLastOrderByValue(){
			return LastOrderByValue;
		}

		public String getLastOrderByValues(){
			return LastOrderByValues;
		}

		public String getLength(){
			return Length;
		}

		public String getListProperties(){
			return ListProperties;
		}

		public String getLocation(){
			return Location;
		}

		public String getMax(){
			return Max;
		}

		public String getName(){
			return Name;
		}

		public String getNext(){
			return Next;
		}

		public String getParameter(){
			return Parameter;
		}

		public String getParameterList(){
			return ParameterList;
		}

		public String getPrev(){
			return Prev;
		}

		public String getQueryId(){
			return QueryId;
		}

		public String getRelationshipQuery(){
			return RelationshipQuery;
		}

		public String getRelationshipQueryList(){
			return RelationshipQueryList;
		}

		public String getRequestedField(){
			return RequestedField;
		}

		public String getRequestedFieldList(){
			return RequestedFieldList;
		}

		public String getRequestedFunctionList(){
			return RequestedFunctionList;
		}

		public String getTrim(){
			return Trim;
		}

		public String getVirtualMode(){
			return VirtualMode;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBefore(String newVal){
			Before = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBusinessObjectQuery(String newVal){
			BusinessObjectQuery = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBusinessObjectQueryList(String newVal){
			BusinessObjectQueryList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCacheRequested(String newVal){
			CacheRequested = newVal;
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
		public void setField(String newVal){
			Field = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFilterOutDuplicateData(String newVal){
			FilterOutDuplicateData = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFirst(String newVal){
			First = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFusionQuery(String newVal){
			FusionQuery = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setGetAllMembersOfGroup(String newVal){
			GetAllMembersOfGroup = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setGroupByItemList(String newVal){
			GroupByItemList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setIgnoreMissingFields(String newVal){
			IgnoreMissingFields = newVal;
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
		public void setLargeTextFields(String newVal){
			LargeTextFields = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLast(String newVal){
			Last = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLastOrderByValue(String newVal){
			LastOrderByValue = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLastOrderByValues(String newVal){
			LastOrderByValues = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLength(String newVal){
			Length = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setListProperties(String newVal){
			ListProperties = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLocation(String newVal){
			Location = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMax(String newVal){
			Max = newVal;
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
		public void setNext(String newVal){
			Next = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParameter(String newVal){
			Parameter = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParameterList(String newVal){
			ParameterList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPrev(String newVal){
			Prev = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setQueryId(String newVal){
			QueryId = newVal;
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
		public void setRelationshipQueryList(String newVal){
			RelationshipQueryList = newVal;
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
		public void setRequestedFunctionList(String newVal){
			RequestedFunctionList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTrim(String newVal){
			Trim = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setVirtualMode(String newVal){
			VirtualMode = newVal;
		}

	}

	protected ArrayList m_alOrderByFields;
	private ArrayList m_alSearchParamList;
	private boolean m_bAdditionalRows;
	private boolean m_bCacheRequested;
	private boolean m_bFilterOutDuplicateData;
	private boolean m_bGetAllMembersOfGroup;
	private boolean m_bIgnoreFieldsNotFound;
	private boolean m_bLargeTextFieldTrim;
	private boolean m_bVirtualMode;
	protected List m_colRequestedFields;
	private DataTable m_dtMainBO;
	protected QueryInfoToGet m_eInfoToGet;
	private ListDictionary m_hdRelationshipQueries;
	private int m_nLargeTextFieldLimit;
	private int m_nMaxRecordsToGet;
	private Fusion.PagingInfo m_pagingInfo;
	private QueryPosition m_posQuery;
	private RelationshipPageInfo m_rpi;
	protected SearchCriteria m_srchCriteria;
	private String m_strBusObName;
	private String m_strGroupByItems;
	private String m_strLargeTextTrimLocation;
	private String m_strRequestedFunctions;
	protected String m_strSearchCriteria;
	private System.TimeZone m_TimeZone;
	private System.Xml.XmlDocument m_xd;
	private XmlElement m_xeGroupByItems;
	private XmlElement m_xeRequestedFunctions;
	protected XmlElement m_xeSearchCriteria;
	private int NoMaximumRecords = -1;
	private String TrimLargeTextAtDataStore = "DataStore";
	private String TrimLargeTextAtServer = "Server";



	public void finalize() throws Throwable {
		super.finalize();
	}

	public FusionQuery(){

	}

	/**
	 * 
	 * @param strXml
	 */
	public FusionQuery(String strXml){

	}

	public FusionQuery ActiveQuery(){
		return null;
	}

	/**
	 * 
	 * @param catRelationship
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 */
	public RelationshipQuery AddAllRelationships(RelationshipCategory catRelationship, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet){
		return null;
	}

	/**
	 * 
	 * @param catRelationship
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 * @param astrQualifiedFieldNames
	 */
	public RelationshipQuery AddAllRelationships(RelationshipCategory catRelationship, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet, string[] astrQualifiedFieldNames){
		return null;
	}

	/**
	 * 
	 * @param strBusObName
	 * @param eInfoToGet
	 */
	public void AddBusObQuery(String strBusObName, QueryInfoToGet eInfoToGet){

	}

	/**
	 * 
	 * @param strBusObName
	 * @param eInfoToGet
	 * @param colQualifiedFieldNames
	 */
	public void AddBusObQuery(String strBusObName, QueryInfoToGet eInfoToGet, List colQualifiedFieldNames){

	}

	/**
	 * 
	 * @param strBusObName
	 * @param eInfoToGet
	 * @param strQualifiedFieldName
	 */
	public void AddBusObQuery(String strBusObName, QueryInfoToGet eInfoToGet, String strQualifiedFieldName){

	}

	/**
	 * 
	 * @param strBusObName
	 * @param eInfoToGet
	 * @param astrQualifiedFieldNames
	 */
	public void AddBusObQuery(String strBusObName, QueryInfoToGet eInfoToGet, string[] astrQualifiedFieldNames){

	}

	/**
	 * 
	 * @param strBusObName
	 * @param eInfoToGet
	 * @param strQualifiedFieldName1
	 * @param strQualifiedFieldName2
	 */
	public void AddBusObQuery(String strBusObName, QueryInfoToGet eInfoToGet, String strQualifiedFieldName1, String strQualifiedFieldName2){

	}

	/**
	 * 
	 * @param strBusObName
	 * @param eInfoToGet
	 * @param strQualifiedFieldName1
	 * @param strQualifiedFieldName2
	 * @param strQualifiedFieldName3
	 */
	public void AddBusObQuery(String strBusObName, QueryInfoToGet eInfoToGet, String strQualifiedFieldName1, String strQualifiedFieldName2, String strQualifiedFieldName3){

	}

	/**
	 * 
	 * @param astrField
	 */
	public void AddGroupBy(string[] astrField){

	}

	/**
	 * 
	 * @param strField
	 */
	public void AddGroupBy(String strField){

	}

	/**
	 * 
	 * @param xeItem
	 */
	public void AddGroupBy(XmlElement xeItem){

	}

	/**
	 * 
	 * @param strField1
	 * @param strField2
	 */
	public void AddGroupBy(String strField1, String strField2){

	}

	/**
	 * 
	 * @param strField1
	 * @param strField2
	 * @param strField3
	 */
	public void AddGroupBy(String strField1, String strField2, String strField3){

	}

	public boolean AdditionalRows(){
		return null;
	}

	/**
	 * 
	 * @param col
	 */
	public void AddOrderBy(List col){

	}

	/**
	 * 
	 * @param strField
	 */
	public void AddOrderBy(String strField){

	}

	/**
	 * 
	 * @param astrField
	 */
	public void AddOrderBy(string[] astrField){

	}

	/**
	 * 
	 * @param bAscending
	 * @param astrField
	 */
	private void AddOrderBy(boolean bAscending, string[] astrField){

	}

	/**
	 * 
	 * @param bAscending
	 * @param strField
	 */
	private void AddOrderBy(boolean bAscending, String strField){

	}

	/**
	 * 
	 * @param strField1
	 * @param strField2
	 */
	public void AddOrderBy(String strField1, String strField2){

	}

	/**
	 * 
	 * @param bAscending
	 * @param strField1
	 * @param strField2
	 */
	private void AddOrderBy(boolean bAscending, String strField1, String strField2){

	}

	/**
	 * 
	 * @param strField1
	 * @param strField2
	 * @param strField3
	 */
	public void AddOrderBy(String strField1, String strField2, String strField3){

	}

	/**
	 * 
	 * @param bAscending
	 * @param strField1
	 * @param strField2
	 * @param strField3
	 */
	private void AddOrderBy(boolean bAscending, String strField1, String strField2, String strField3){

	}

	/**
	 * 
	 * @param strField
	 */
	public void AddOrderByDesc(String strField){

	}

	/**
	 * 
	 * @param astrField
	 */
	public void AddOrderByDesc(string[] astrField){

	}

	/**
	 * 
	 * @param strField1
	 * @param strField2
	 */
	public void AddOrderByDesc(String strField1, String strField2){

	}

	/**
	 * 
	 * @param strField1
	 * @param strField2
	 * @param strField3
	 */
	public void AddOrderByDesc(String strField1, String strField2, String strField3){

	}

	/**
	 * 
	 * @param xeQueryFunction
	 */
	public void AddQueryFunction(XmlElement xeQueryFunction){

	}

	/**
	 * 
	 * @param strRelationshipName
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 */
	public RelationshipQuery AddRelationship(String strRelationshipName, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet){
		return null;
	}

	/**
	 * 
	 * @param strRelationshipName
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 * @param astrQualifiedFieldNames
	 */
	public RelationshipQuery AddRelationship(String strRelationshipName, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet, string[] astrQualifiedFieldNames){
		return null;
	}

	/**
	 * 
	 * @param strRelationshipName
	 * @param strBusObName
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 * @param astrQualifiedFieldNames
	 */
	public RelationshipQuery AddRelationship(String strRelationshipName, String strBusObName, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet, string[] astrQualifiedFieldNames){
		return null;
	}

	/**
	 * 
	 * @param strRelationshipName
	 * @param strRollUpDefId
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 */
	public RelationshipQuery AddRollupRelationship(String strRelationshipName, String strRollUpDefId, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet){
		return null;
	}

	/**
	 * 
	 * @param strRelationshipName
	 * @param strRollUpDefId
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 * @param astrQualifiedFieldNames
	 */
	public RelationshipQuery AddRollupRelationship(String strRelationshipName, String strRollUpDefId, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet, string[] astrQualifiedFieldNames){
		return null;
	}

	/**
	 * 
	 * @param strRelationshipName
	 * @param strRollUpDefId
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 * @param colQualifiedFieldNames
	 */
	public RelationshipQuery AddRollupRelationship(String strRelationshipName, String strRollUpDefId, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet, List colQualifiedFieldNames){
		return null;
	}

	/**
	 * 
	 * @param strRelationshipName
	 * @param strRollUpDefName
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 */
	public RelationshipQuery AddRollupRelationshipByName(String strRelationshipName, String strRollUpDefName, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet){
		return null;
	}

	/**
	 * 
	 * @param strRelationshipName
	 * @param strRollUpDefName
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 * @param astrQualifiedFieldNames
	 */
	public RelationshipQuery AddRollupRelationshipByName(String strRelationshipName, String strRollUpDefName, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet, string[] astrQualifiedFieldNames){
		return null;
	}

	/**
	 * 
	 * @param strRelationshipName
	 * @param strRollUpDefName
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 * @param colQualifiedFieldNames
	 */
	public RelationshipQuery AddRollupRelationshipByName(String strRelationshipName, String strRollUpDefName, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet, List colQualifiedFieldNames){
		return null;
	}

	public String BusinessObjectName(){
		return "";
	}

	public XmlElement BusObSearchCriteria(){
		return null;
	}

	public boolean CacheRequested(){
		return null;
	}

	public FusionQuery Clone(){
		return null;
	}

	public boolean ContainsRelationships(){
		return null;
	}

	/**
	 * 
	 * @param query
	 */
	public void CopyContents(FusionQuery query){

	}

	/**
	 * 
	 * @param result
	 */
	private void CopyLastOrderByValues(IQueryResult result){

	}

	/**
	 * 
	 * @param result
	 */
	public void CopyQueryResultsIfVirtualMode(IQueryResult result){

	}

	/**
	 * 
	 * @param strBusObName
	 * @param eInfoToGet
	 * @param colQualifiedFieldNames
	 */
	private void CreateBusObQuery(String strBusObName, QueryInfoToGet eInfoToGet, List colQualifiedFieldNames){

	}

	public SearchCriteria CriteriaBuilder(){
		return null;
	}

	public boolean FilterOutDuplicateData(){
		return null;
	}

	/**
	 * 
	 * @param strXml
	 */
	public void FromXml(String strXml){

	}

	public boolean GetAllMembersOfGroup(){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param eInfoToGet
	 * @param xeSearchCriteria
	 */
	public void GetBusObQueryInfo(String strName, QueryInfoToGet eInfoToGet, XmlElement xeSearchCriteria){

	}

	/**
	 * 
	 * @param xeListProperties
	 */
	private void GetGroupByFieldsFromXml(XmlElement xeListProperties){

	}

	/**
	 * 
	 * @param result
	 * @param strBusObId
	 * @param strBusObName
	 */
	private static void GetMainBusObInfoFromResult(IQueryResult result, String strBusObId, String strBusObName){

	}

	public int getNoMaximumRecords(){
		return NoMaximumRecords;
	}

	/**
	 * 
	 * @param xeListProperties
	 */
	private void GetOrderByFieldsFromXml(XmlElement xeListProperties){

	}

	/**
	 * 
	 * @param query
	 * @param strBusObId
	 * @param strBusObName
	 * @param strRelName
	 * @param strRelBusObName
	 * @param xeSearchCriteria
	 * @param eInfoToGet
	 * @param astrQualifiedFieldNames
	 */
	public static FusionQuery GetPageQueryForRelationship(FusionQuery query, String strBusObId, String strBusObName, String strRelName, String strRelBusObName, XmlElement xeSearchCriteria, QueryInfoToGet eInfoToGet, string[] astrQualifiedFieldNames){
		return null;
	}

	/**
	 * 
	 * @param xeListProperties
	 */
	private void GetRecordsToRetrieveFromXml(XmlElement xeListProperties){

	}

	/**
	 * 
	 * @param strName
	 */
	public Object GetSearchParameter(String strName){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Object GetSearchParameterValue(String strName){
		return null;
	}

	public String getTrimLargeTextAtDataStore(){
		return TrimLargeTextAtDataStore;
	}

	public String getTrimLargeTextAtServer(){
		return TrimLargeTextAtServer;
	}

	public XmlElement GroupByItemList(){
		return null;
	}

	public boolean HasAggregateFunctions(){
		return null;
	}

	public boolean HasGroupBy(){
		return null;
	}

	/**
	 * 
	 * @param obField
	 */
	public int HasOrderBy(FusionQueryOrderByField obField){
		return 0;
	}

	/**
	 * 
	 * @param sName
	 */
	public int HasOrderBy(String sName){
		return 0;
	}

	public boolean HaveSearchParameters(){
		return null;
	}

	public boolean IgnoreFieldsNotFound(){
		return null;
	}

	public QueryInfoToGet InfoToGet(){
		return null;
	}

	public boolean IsPagingRelationships(){
		return null;
	}

	public int LargeTextFieldLimit(){
		return 0;
	}

	public boolean LargeTextFieldTrim(){
		return null;
	}

	public String LargeTextTrimLocation(){
		return "";
	}

	public DataTable MainBODataTable(){
		return null;
	}

	public int MaximumRecords(){
		return 0;
	}

	/**
	 * 
	 * @param sender
	 */
	public void OnDeserialization(Object sender){

	}

	public List OrderByList(){
		return null;
	}

	public Fusion.PagingInfo PagingInfo(){
		return null;
	}

	public RelationshipQuery PagingRelationshipQuery(){
		return null;
	}

	public QueryPosition PositionToGet(){
		return null;
	}

	public Fusion.QueryFunction QueryFunction(){
		return null;
	}

	public List RelationshipQueries(){
		return null;
	}

	public Map RelationshipQueriesDict(){
		return null;
	}

	public RelationshipPageInfo RelPageInfo(){
		return null;
	}

	public void RemoveGroupByFields(){

	}

	/**
	 * 
	 * @param aFields
	 */
	public void RemoveOrderBy(string[] aFields){

	}

	public void RemoveOrderByFields(){

	}

	public void RemoveRelationshipQueries(){

	}

	public List RequestedFields(){
		return null;
	}

	public XmlElement RequestedFunctions(){
		return null;
	}

	public void ResyncSearchCriteria(){

	}

	public List SearchParameters(){
		return null;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNoMaximumRecords(int newVal){
		NoMaximumRecords = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTrimLargeTextAtDataStore(String newVal){
		TrimLargeTextAtDataStore = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTrimLargeTextAtServer(String newVal){
		TrimLargeTextAtServer = newVal;
	}

	public System.TimeZone TimeZone(){
		return null;
	}

	public String ToXml(){
		return "";
	}

	/**
	 * 
	 * @param bTrimLargeTextFields
	 * @param nLargeTextFieldLimit
	 * @param strLargeTextTrimLocation
	 */
	public void TrimLargeTextFields(boolean bTrimLargeTextFields, int nLargeTextFieldLimit, String strLargeTextTrimLocation){

	}

	/**
	 * 
	 * @param strName
	 * @param value
	 */
	public void UpdateBusObSearchCriteria(String strName, Object value){

	}

	/**
	 * 
	 * @param strName
	 * @param value
	 */
	public void UpdateParameterValue(String strName, Object value){

	}

	public boolean VirtualMode(){
		return null;
	}

	protected System.Xml.XmlDocument XmlDocument(){
		return null;
	}

}