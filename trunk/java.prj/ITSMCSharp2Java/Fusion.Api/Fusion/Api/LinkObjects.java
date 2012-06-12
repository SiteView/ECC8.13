package Fusion.Api;

import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:57
 */
public class LinkObjects {

	private IOrchestrator m_orch = null;
	private UserAgentAdminSettings m_uaSettings;

	public LinkObjects(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param orch
	 */
	public LinkObjects(IOrchestrator orch){

	}

	/**
	 * 
	 * @param strName
	 */
	public void AddEmailBusinessObjectName(String strName){

	}

	/**
	 * 
	 * @param collAddresses
	 * @param dictHints
	 * @param busObDef
	 * @param xmlSearchCriteria
	 * @param criteriaBuilder
	 */
	protected XmlElement AddSearchCriteria(List collAddresses, Map dictHints, Fusion.BusinessLogic.BusinessObjectDef busObDef, XmlElement xmlSearchCriteria, SearchCriteria criteriaBuilder){
		return null;
	}

	/**
	 * 
	 * @param strFieldName
	 * @param oper
	 * @param strValue
	 * @param xmlSearchCriteria
	 * @param criteriaBuilder
	 */
	private XmlElement AddSearchCriteria(String strFieldName, Fusion.Operators oper, String strValue, XmlElement xmlSearchCriteria, SearchCriteria criteriaBuilder){
		return null;
	}

	public String AppointmentHistoryDefName(){
		return "";
	}

	/**
	 * 
	 * @param def
	 * @param strAnnotationGroup
	 * @param strMessageId
	 * @param strParentRecId
	 * @param strParentRecName
	 * @param criteriaBuilder
	 */
	protected XmlElement BuildMessageIdCriteria(Fusion.BusinessLogic.BusinessObjectDef def, String strAnnotationGroup, String strMessageId, String strParentRecId, String strParentRecName, SearchCriteria criteriaBuilder){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public boolean ContainsEmailBusinessObjectName(String strName){
		return false;
	}

	/**
	 * 
	 * @param linkTo
	 * @param strMessageId
	 * @param key
	 */
	protected LinkStatus DeleteLinkedBusOb(LinkToBusOb linkTo, String strMessageId, IBusObDisplayKey key){
		return null;
	}

	public String EmailHistoryDefName(){
		return "";
	}

	/**
	 * 
	 * @param dataTransport
	 * @param lookupAddress
	 */
	protected String GetAddressesAsString(DataTransport dataTransport, EmailAddressGroup lookupAddress){
		return "";
	}

	/**
	 * 
	 * @param dataTransport
	 * @param lookupAddress
	 */
	protected List GetAddressList(DataTransport dataTransport, EmailAddressGroup lookupAddress){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 * @param strAnnotationGroup
	 * @param strAnnotation
	 */
	public static Fusion.BusinessLogic.Field GetAnnotatedField(Fusion.BusinessLogic.BusinessObject busOb, String strAnnotationGroup, String strAnnotation){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param strAnnotationGroup
	 * @param strAnnotation
	 */
	public static Fusion.BusinessLogic.FieldDef GetAnnotatedField(Fusion.BusinessLogic.BusinessObjectDef def, String strAnnotationGroup, String strAnnotation){
		return null;
	}

	/**
	 * 
	 * @param linkTo
	 */
	protected String GetAnnotationGroup(LinkToBusOb linkTo){
		return "";
	}

	/**
	 * 
	 * @param busOb
	 */
	public EmailAddress GetEmailAddress(Fusion.Api.BusinessObject busOb){
		return null;
	}

	public Map GetEmailBusinessObjectNames(){
		return null;
	}

	/**
	 * 
	 * @param perInfo
	 * @param lookupAddress
	 */
	protected List GetLinkedBusObjs(PersistenceInfo perInfo, EmailAddressGroup lookupAddress){
		return null;
	}

	/**
	 * 
	 * @param linkTo
	 */
	protected Fusion.BusinessLogic.BusinessObjectDef GetStorageDef(LinkToBusOb linkTo){
		return null;
	}

	/**
	 * 
	 * @param collMessageLinkStatus
	 */
	public void IsLinked(List collMessageLinkStatus){

	}

	/**
	 * 
	 * @param strMessageId
	 * @param linkTo
	 */
	public boolean IsLinked(String strMessageId, LinkToBusOb linkTo){
		return false;
	}

	/**
	 * 
	 * @param strMessageId
	 * @param linkTo
	 * @param emailAddress
	 */
	public boolean IsLinked(String strMessageId, LinkToBusOb linkTo, EmailAddress emailAddress){
		return false;
	}

	/**
	 * 
	 * @param def
	 * @param strAnnotationGroup
	 * @param strMessageId
	 * @param strEmailAddress
	 */
	protected LinkResults IsLinkedToEmail(Fusion.BusinessLogic.BusinessObjectDef def, String strAnnotationGroup, String strMessageId, String strEmailAddress){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param strAnnotationGroup
	 * @param strMessageId
	 * @param strParentRecId
	 */
	protected boolean IsLinkedToId(Fusion.BusinessLogic.BusinessObjectDef def, String strAnnotationGroup, String strMessageId, String strParentRecId){
		return null;
	}

	/**
	 * 
	 * @param perInfo
	 * @param lookupAddress
	 */
	protected void LinkInfoToBusOb(PersistenceInfo perInfo, EmailAddressGroup lookupAddress){

	}

	/**
	 * 
	 * @param perInfo
	 * @param key
	 */
	protected void LinkInfoToBusOb(PersistenceInfo perInfo, IBusObDisplayKey key){

	}

	/**
	 * 
	 * @param perInfo
	 * @param strName
	 * @param strId
	 */
	protected void LinkInfoToBusOb(PersistenceInfo perInfo, String strName, String strId){

	}

	/**
	 * 
	 * @param strName
	 * @param strId
	 */
	protected DataRow LookupBusOb(String strName, String strId){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param strFilter
	 */
	private List LookupBusObByEmail(Fusion.BusinessLogic.BusinessObjectDef def, String strFilter){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param strFilter
	 */
	private List LookupBusObByLinkedEmail(Fusion.BusinessLogic.BusinessObjectDef def, String strFilter){
		return null;
	}

	/**
	 * 
	 * @param strEmail
	 */
	protected List LookupBusObsByEmail(String strEmail){
		return null;
	}

	/**
	 * 
	 * @param dataTransport
	 * @param address
	 */
	protected IBusObDisplayKey LookupBusObToLink(DataTransport dataTransport, EmailAddress address){
		return null;
	}

	/**
	 * 
	 * @param strEmail
	 */
	public List LookupByEmail(String strEmail){
		return null;
	}

	/**
	 * 
	 * @param strId
	 * @param strName
	 */
	public PersistenceInfo LookupLinkInfo(String strId, String strName){
		return null;
	}

	public String MeetingHistoryDefName(){
		return "";
	}

	protected IOrchestrator Orchestrator(){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public void RemoveEmailBusinessObjectName(String strName){

	}

	/**
	 * 
	 * @param busOb
	 * @param updateResult
	 */
	protected void Save(Fusion.BusinessLogic.BusinessObject busOb, UpdateResult updateResult){

	}

	/**
	 * 
	 * @param collAttachmentInfo
	 * @param busOb
	 * @param updateResult
	 */
	private void SaveAttachmentInfo(List collAttachmentInfo, Fusion.BusinessLogic.BusinessObject busOb, UpdateResult updateResult){

	}

	public void SaveEmailBusinessObjectNames(){

	}

	/**
	 * 
	 * @param fldDef
	 * @param dataOb
	 * @param transport
	 */
	protected void SetDataFromField(Fusion.BusinessLogic.FieldDef fldDef, Fusion.BusinessLogic.BusinessObject dataOb, PersistenceInfo transport){

	}

	/**
	 * 
	 * @param transport
	 * @param dataOb
	 * @param updateResult
	 * @param key
	 */
	protected void SetDataIntoBusOb(DataTransport transport, Fusion.BusinessLogic.BusinessObject dataOb, UpdateResult updateResult, IBusObDisplayKey key){

	}

	/**
	 * 
	 * @param transport
	 * @param dataOb
	 * @param updateResult
	 * @param fldDef
	 */
	private void SetDataIntoField(PersistenceInfo transport, Fusion.BusinessLogic.BusinessObject dataOb, UpdateResult updateResult, Fusion.BusinessLogic.FieldDef fldDef){

	}

	/**
	 * 
	 * @param transport
	 * @param dataOb
	 * @param updateResult
	 */
	protected void SetPersistentData(PersistenceInfo transport, Fusion.BusinessLogic.BusinessObject dataOb, UpdateResult updateResult){

	}

	/**
	 * 
	 * @param linkTo
	 */
	protected String StorageDefName(LinkToBusOb linkTo){
		return "";
	}

	/**
	 * 
	 * @param perInfo
	 * @param lookupAddress
	 */
	protected void UpdateLinkToBusOb(PersistenceInfo perInfo, EmailAddressGroup lookupAddress){

	}

	/**
	 * 
	 * @param perInfo
	 * @param key
	 */
	protected void UpdateLinkToBusOb(PersistenceInfo perInfo, IBusObDisplayKey key){

	}

}