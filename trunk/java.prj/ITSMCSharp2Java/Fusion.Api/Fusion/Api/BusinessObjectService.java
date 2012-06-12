package Fusion.Api;

import java.util.ArrayList;

import javax.xml.bind.annotation.XmlSchema;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:36
 */
public class BusinessObjectService implements IBusinessObjectService {

	private FusionApi m_api = null;
	private String m_nsFusion = "http://localhost/FusionBOWS/Fusion.xsd";
	private String m_nsFusionQuery = "http://localhost/FusionBOWS/FusionQuery.xsd";
	private String m_nsQuickAction = "http://localhost/FusionBOWS/FusionQuickAction.xsd";
	private String m_nsW3 = "http://www.w3.org/2001/XMLSchema";
	private String m_nsXSI = "http://www.w3.org/2001/XMLSchema-instance";
	private IOrchestrator m_orch = null;
	private Fusion.Api.PagedQueryResolver m_qrPaged = null;
	private Fusion.Api.SimpleQueryResolver m_qrSimple = null;
	private Fusion.Api.VirtualQueryResolver m_qrVirtual = null;
	private String m_sBOT = "BusinessObjectType";
	private XmlSchema m_schemaXML = null;
	private String m_sFNS = "fusion";
	private String m_sFusionLinkedTo = "LinkedTo";
	private String m_sFusionParam = "Param";
	private String m_sFusionParamMessage = "Message";
	private String m_sFusionParamName = "Name";
	private String m_sFusionParamValue = "Value";
	private String m_sFusionPrompt = "Prompt";
	private String m_sFusionPromptCaption = "Caption";
	private String m_sFusionPromptMessage = "Message";
	private String m_sFusionPromptValue = "Value";
	private String m_sFusionQuery = "FusionQuery";
	private String m_sFusionQueryAlias = "Alias";
	private String m_sFusionQueryName = "Name";
	private String m_sFusionQueryParam = "FusionQueryParam";
	private String m_sFusionQueryParamList = "FusionQueryParamList";
	private String m_sFusionQueryParamListType = "FusionQueryParamListType";
	private String m_sFusionQueryParamType = "FusionQueryParamType";
	private String m_sFusionQueryType = "FusionQueryType";
	private String m_sFusionQuickActionAlias = "Alias";
	private String m_sFusionQuickActionName = "Name";
	private String m_sFusionQuickActionPrompt = "FusionQuickActionPrompt";
	private String m_sFusionQuickActionPromptListType = "FusionQuickActionPromptListType";
	private String m_sFusionQuickActionPromptType = "FusionQuickActionPromptType";
	private String m_sId = "ContextBusObId";
	private String m_sParamList = "ParamList";
	private String m_sPromptList = "PromptList";
	private String m_sQuickAction = "FusionQuickAction";
	private String m_sQuickActionType = "FusionQuickActionType";
	private String m_sType = "Type";

	public BusinessObjectService(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param orch
	 * @param api
	 */
	public BusinessObjectService(IOrchestrator orch, FusionApi api){

	}

	/**
	 * 
	 * @param businessObjects
	 * @param groupName
	 */
	public void AddObjectsToGroup(Fusion.Api.BusinessObjectCollection businessObjects, String groupName){

	}

	/**
	 * 
	 * @param recID
	 * @param businessObjectName
	 * @param groupName
	 */
	public void AddObjectToGroup(String recID, String businessObjectName, String groupName){

	}

	/**
	 * 
	 * @param bo
	 */
	public XmlDocument BO2XML(Fusion.Api.BusinessObject bo){
		return null;
	}

	/**
	 * 
	 * @param bos
	 */
	public XmlDocument BO2XML(List bos){
		return null;
	}

	/**
	 * 
	 * @param bo
	 * @param bIncludeEmptyFields
	 */
	public XmlDocument BO2XML(Fusion.Api.BusinessObject bo, boolean bIncludeEmptyFields){
		return null;
	}

	/**
	 * 
	 * @param bos
	 * @param bIncludeEmptyFields
	 */
	public XmlDocument BO2XML(List bos, boolean bIncludeEmptyFields){
		return null;
	}

	/**
	 * 
	 * @param bo
	 */
	public String BO2XMLString(Fusion.Api.BusinessObject bo){
		return "";
	}

	/**
	 * 
	 * @param bos
	 */
	public String BO2XMLString(List bos){
		return "";
	}

	/**
	 * 
	 * @param bo
	 * @param bIncludeEmptyFields
	 */
	public String BO2XMLString(Fusion.Api.BusinessObject bo, boolean bIncludeEmptyFields){
		return "";
	}

	/**
	 * 
	 * @param bos
	 * @param bIncludeEmptyFields
	 */
	public String BO2XMLString(List bos, boolean bIncludeEmptyFields){
		return "";
	}

	/**
	 * 
	 * @param schemaXML
	 */
	private String ConvertXmlSchemaToString(XmlSchema schemaXML){
		return "";
	}

	/**
	 * 
	 * @param defObjectName
	 */
	public Fusion.Api.BusinessObject Create(String defObjectName){
		return null;
	}

	/**
	 * 
	 * @param defObjectName
	 * @param init
	 */
	public Fusion.Api.BusinessObject Create(String defObjectName, boolean init){
		return null;
	}

	/**
	 * 
	 * @param defObjectName
	 * @param recId
	 * @param init
	 */
	public Fusion.Api.BusinessObject Create(String defObjectName, String recId, boolean init){
		return null;
	}

	/**
	 * 
	 * @param sPromptName
	 * @param pd
	 * @param schemaXML
	 */
	private XmlSchemaElement CreateAutoTaskPrompt(String sPromptName, SystemPromptDef pd, XmlSchema schemaXML){
		return null;
	}

	/**
	 * 
	 * @param Id
	 * @param Name
	 */
	public IBusObKey CreateBusObKey(String Id, String Name){
		return null;
	}

	/**
	 * 
	 * @param typeName
	 */
	private XmlSchemaComplexType CreateComplexType(String typeName){
		return null;
	}

	/**
	 * 
	 * @param sIn
	 */
	private String CreateElementNameFromString(String sIn){
		return "";
	}

	/**
	 * 
	 * @param sElementName
	 * @param sValue
	 */
	private XmlSchemaElement CreateElementWithOneValidEntry(String sElementName, String sValue){
		return null;
	}

	public IBusObKeyList CreateEmptyKeyList(){
		return null;
	}

	public IVirtualBusObKeyList CreateEmptyVirtualKeyList(){
		return null;
	}

	/**
	 * 
	 * @param sParamName
	 * @param param
	 * @param schemaXML
	 */
	private XmlSchemaElement CreateQueryParam(String sParamName, ISearchParameter param, XmlSchema schemaXML){
		return null;
	}

	/**
	 * 
	 * @param data
	 * @param recIdName
	 */
	public IVirtualBusObKeyList CreateVirtualKeyListByDataTable(DataTable data, String recIdName){
		return null;
	}

	/**
	 * 
	 * @param defBusOb
	 * @param busObId
	 */
	public void DeleteBusinessObject(Fusion.Api.BusinessObjectDef defBusOb, String busObId){

	}

	/**
	 * 
	 * @param busObName
	 * @param busObId
	 */
	public void DeleteBusinessObject(String busObName, String busObId){

	}

	public void ExpireCache(){

	}

	/**
	 * 
	 * @param BusObName
	 */
	public void ExpireSpecificCache(String BusObName){

	}

	/**
	 * 
	 * @param busOb
	 */
	private Fusion.Api.BusinessObject GetAggregate(Fusion.BusinessLogic.BusinessObject busOb){
		return null;
	}

	/**
	 * 
	 * @param busObDef
	 */
	private Fusion.Api.BusinessObjectDef GetAggregate(Fusion.BusinessLogic.BusinessObjectDef busObDef){
		return null;
	}

	/**
	 * 
	 * @param sClassName
	 */
	private List GetAllDefPlaceHolders(String sClassName){
		return null;
	}

	/**
	 * 
	 * @param sObName
	 */
	public XmlSchema GetBOSchema(String sObName){
		return null;
	}

	/**
	 * 
	 * @param sObName
	 * @param bForce
	 */
	public XmlSchema GetBOSchema(String sObName, boolean bForce){
		return null;
	}

	/**
	 * 
	 * @param sObName
	 */
	public String GetBOSchemaString(String sObName){
		return "";
	}

	/**
	 * 
	 * @param sObName
	 * @param bForce
	 */
	public String GetBOSchemaString(String sObName, boolean bForce){
		return "";
	}

	/**
	 * 
	 * @param query
	 */
	public Fusion.Api.BusinessObject GetBusinessObject(FusionQuery query){
		return null;
	}

	/**
	 * 
	 * @param busObKey
	 */
	public Fusion.Api.BusinessObject GetBusinessObject(IBusObKey busObKey){
		return null;
	}

	/**
	 * 
	 * @param busObKey
	 */
	public Fusion.Api.BusinessObject GetBusinessObject(IVirtualBusObKey busObKey){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strId
	 */
	public Fusion.Api.BusinessObject GetBusinessObject(String strName, String strId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strRecIdFieldName
	 * @param strId
	 */
	public Fusion.Api.BusinessObject GetBusinessObject(String strName, String strRecIdFieldName, String strId){
		return null;
	}

	/**
	 * 
	 * @param keyList
	 */
	public Fusion.Api.BusinessObject GetCurrentBusinessObject(IBusObKeyList keyList){
		return null;
	}

	/**
	 * 
	 * @param keyList
	 */
	public Fusion.Api.BusinessObject GetCurrentBusinessObject(IVirtualKeyList keyList){
		return null;
	}

	/**
	 * 
	 * @param defHOP
	 * @param StartDateTime
	 * @param EndDateTime
	 */
	public double GetDuration(Fusion.Api.HoursOfOperationDef defHOP, Date StartDateTime, Date EndDateTime){
		return 0;
	}

	/**
	 * 
	 * @param strHopID
	 * @param StartDateTime
	 * @param EndDateTime
	 */
	public double GetDuration(String strHopID, Date StartDateTime, Date EndDateTime){
		return 0;
	}

	/**
	 * 
	 * @param sName
	 */
	protected String GetFieldName(String sName){
		return "";
	}

	/**
	 * 
	 * @param RecID
	 * @param LookupDate
	 * @param LookupParameter
	 */
	public String GetParameterValueByEmployee(String RecID, Date LookupDate, String LookupParameter){
		return "";
	}

	/**
	 * 
	 * @param sQueryName
	 */
	private String GetParamListElementName(String sQueryName){
		return "";
	}

	/**
	 * 
	 * @param busObKey
	 * @param relationships
	 */
	public Fusion.Api.BusinessObject GetParentBusinessObject(IBusObKey busObKey, QueryRelationshipInfo[] relationships){
		return null;
	}

	/**
	 * 
	 * @param sName
	 */
	public String GetQualifiedName(String sName){
		return "";
	}

	/**
	 * 
	 * @param sName
	 */
	public XmlSchema GetQuerySchema(String sName){
		return null;
	}

	/**
	 * 
	 * @param sName
	 */
	public String GetQuerySchemaString(String sName){
		return "";
	}

	/**
	 * 
	 * @param sName
	 */
	public XmlSchema GetQuickActionSchema(String sName){
		return null;
	}

	/**
	 * 
	 * @param sName
	 */
	public String GetQuickActionSchemaString(String sName){
		return "";
	}

	/**
	 * 
	 * @param sClassName
	 * @param sDefName
	 */
	private IDefinition GetSpecificDefPlaceHolder(String sClassName, String sDefName){
		return null;
	}

	/**
	 * 
	 * @param HopID
	 * @param CreateDateTime
	 * @param OffSet
	 */
	public Date GetTargetDateTime(String HopID, Date CreateDateTime, int OffSet){
		return null;
	}

	/**
	 * 
	 * @param sId
	 */
	private boolean IsValidId(String sId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strRecId
	 */
	private Fusion.BusinessLogic.BusinessObject LoadBusinessObject(String strName, String strRecId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strRecIdFieldName
	 * @param strRecId
	 */
	private Fusion.BusinessLogic.BusinessObject LoadBusinessObject(String strName, String strRecIdFieldName, String strRecId){
		return null;
	}

	public Fusion.Api.PagedQueryResolver PagedQueryResolver(){
		return null;
	}

	/**
	 * 
	 * @param schemaXML
	 * @param def
	 */
	private void ProcessAutoTaskDef(XmlSchema schemaXML, AutoTaskDef def){

	}

	/**
	 * 
	 * @param schemaXML
	 * @param promptDefList
	 * @param sQuickActionName
	 */
	private void ProcessAutoTaskPrompts(XmlSchema schemaXML, IList promptDefList, String sQuickActionName){

	}

	/**
	 * 
	 * @param fd
	 * @param el
	 */
	protected void ProcessField(Fusion.Api.FieldDef fd, XmlSchemaElement el){

	}

	/**
	 * 
	 * @param xmlDoc
	 * @param el
	 * @param bo
	 * @param bIncludeEmptyFields
	 */
	protected void ProcessObject(XmlDocument xmlDoc, XmlElement el, Fusion.Api.BusinessObject bo, boolean bIncludeEmptyFields){

	}

	/**
	 * 
	 * @param schemaXML
	 * @param def
	 */
	private void ProcessQueryDef(XmlSchema schemaXML, QueryGroupDef def){

	}

	/**
	 * 
	 * @param schemaXML
	 * @param defQuery
	 * @param sQueryName
	 */
	private void ProcessQueryParamList(XmlSchema schemaXML, FusionQuery defQuery, String sQueryName){

	}

	/**
	 * 
	 * @param strBusObName
	 * @param rows
	 */
	public List SerializeFromDataRows(String strBusObName, DataRowCollection rows){
		return null;
	}

	public Fusion.Api.SimpleQueryResolver SimpleQueryResolver(){
		return null;
	}

	public Fusion.Api.VirtualQueryResolver VirtualQueryResolver(){
		return null;
	}

	/**
	 * 
	 * @param stream
	 * @param aBOs
	 */
	public boolean XML2BO(Stream stream, ArrayList aBOs){
		return null;
	}

	/**
	 * 
	 * @param sXML
	 * @param aBOs
	 */
	public boolean XML2BO(String sXML, ArrayList aBOs){
		return null;
	}

	/**
	 * 
	 * @param reader
	 * @param aBOs
	 */
	public boolean XML2BO(XmlTextReader reader, ArrayList aBOs){
		return null;
	}

	/**
	 * 
	 * @param stream
	 * @param aBOs
	 * @param bSkipXMLValidation
	 * @param ur
	 */
	public boolean XML2BO(Stream stream, ArrayList aBOs, boolean bSkipXMLValidation, UpdateResult ur){
		return null;
	}

	/**
	 * 
	 * @param sXML
	 * @param aBOs
	 * @param bSkipXMLValidation
	 * @param ur
	 */
	public boolean XML2BO(String sXML, ArrayList aBOs, boolean bSkipXMLValidation, UpdateResult ur){
		return null;
	}

	/**
	 * 
	 * @param reader
	 * @param aBOs
	 * @param bSkipXMLValidation
	 * @param ur
	 */
	public boolean XML2BO(XmlTextReader reader, ArrayList aBOs, boolean bSkipXMLValidation, UpdateResult ur){
		return null;
	}

}