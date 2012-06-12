package Fusion.Api;

import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:42
 */
public class CalendarClientService extends LinkObjects implements ILinkObjects {

	public CalendarClientService(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param orch
	 */
	public CalendarClientService(IOrchestrator orch){

	}

	/**
	 * 
	 * @param text1
	 */
	private void AddEmailBusinessObjectName(String text1){

	}

	private String AppointmentHistoryDefName(){
		return "";
	}

	/**
	 * 
	 * @param text1
	 */
	private boolean ContainsEmailBusinessObjectName(String text1){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 */
	public PersistenceInfo CreateTransportObject(Fusion.Api.BusinessObject busOb){
		return null;
	}

	/**
	 * 
	 * @param strMessageId
	 * @param bIsMeeting
	 * @param collBusObKeys
	 */
	public List DeleteLink(String strMessageId, boolean bIsMeeting, List collBusObKeys){
		return null;
	}

	private String EmailHistoryDefName(){
		return "";
	}

	/**
	 * 
	 * @param activity
	 */
	private CalendarSet FillCalendarSet(Fusion.BusinessLogic.BusinessObject activity){
		return null;
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
	 * @param activity
	 * @param bWithHints
	 * @param calSet
	 */
	private CalendarSet GetCalendarSet(Fusion.BusinessLogic.BusinessObject activity, boolean bWithHints, CalendarSet calSet){
		return null;
	}

	/**
	 * 
	 * @param obj1
	 */
	private EmailAddress GetEmailAddress(Fusion.Api.BusinessObject obj1){
		return null;
	}

	private Map GetEmailBusinessObjectNames(){
		return null;
	}

	/**
	 * 
	 * @param perInfo
	 */
	public List GetLinkedBusObjs(PersistenceInfo perInfo){
		return null;
	}

	/**
	 * 
	 * @param collection1
	 */
	private void IsLinked(List collection1){

	}

	/**
	 * 
	 * @param text1
	 * @param ob1
	 */
	private boolean IsLinked(String text1, LinkToBusOb ob1){
		return null;
	}

	/**
	 * 
	 * @param text1
	 * @param ob1
	 * @param address1
	 */
	private boolean IsLinked(String text1, LinkToBusOb ob1, EmailAddress address1){
		return null;
	}

	/**
	 * 
	 * @param perInfo
	 */
	public LinkOperation Link(PersistenceInfo perInfo){
		return null;
	}

	/**
	 * 
	 * @param perInfo
	 * @param strName
	 * @param strId
	 */
	public LinkOperation Link(PersistenceInfo perInfo, String strName, String strId){
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
	 * @param text1
	 */
	private List LookupByEmail(String text1){
		return null;
	}

	private String MeetingHistoryDefName(){
		return "";
	}

	/**
	 * 
	 * @param text1
	 */
	private void RemoveEmailBusinessObjectName(String text1){

	}

	private void SaveEmailBusinessObjectNames(){

	}

	/**
	 * 
	 * @param perInfo
	 */
	public LinkOperation UpdateLink(PersistenceInfo perInfo){
		return null;
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