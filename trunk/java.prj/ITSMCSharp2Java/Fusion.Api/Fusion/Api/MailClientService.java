package Fusion.Api;

import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:01
 */
public class MailClientService extends LinkObjects implements ILinkObjects {

	public MailClientService(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param orch
	 */
	public MailClientService(IOrchestrator orch){

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
	 * @param collBusObKeys
	 */
	public List DeleteLink(String strMessageId, List collBusObKeys){
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
	 * @param message
	 */
	private MailInfo FillMailInfo(Fusion.BusinessLogic.BusinessObject message){
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
	 * @param collMessages
	 * @param bWithHints
	 */
	private MailInfo GetMailInfo(List collMessages, boolean bWithHints){
		return null;
	}

	/**
	 * 
	 * @param message
	 * @param bWithHints
	 * @param mailInfo
	 */
	private MailInfo GetMailInfo(Fusion.BusinessLogic.BusinessObject message, boolean bWithHints, MailInfo mailInfo){
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

}