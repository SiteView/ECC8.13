package Fusion.Api;

import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:51
 */
public interface ILinkObjects {

	/**
	 * 
	 * @param strName
	 */
	public void AddEmailBusinessObjectName(String strName);

	public String AppointmentHistoryDefName();

	/**
	 * 
	 * @param strName
	 */
	public boolean ContainsEmailBusinessObjectName(String strName);

	/**
	 * 
	 * @param busOb
	 */
	public PersistenceInfo CreateTransportObject(BusinessObject busOb);

	/**
	 * 
	 * @param strMessageId
	 * @param bIsMeeting
	 * @param collBusObKeys
	 */
	public List DeleteLink(String strMessageId, boolean bIsMeeting, List collBusObKeys);

	public String EmailHistoryDefName();

	/**
	 * 
	 * @param busOb
	 */
	public EmailAddress GetEmailAddress(BusinessObject busOb);

	public Map GetEmailBusinessObjectNames();

	/**
	 * 
	 * @param perInfo
	 */
	public List GetLinkedBusObjs(PersistenceInfo perInfo);

	/**
	 * 
	 * @param collMessageLinkStatus
	 */
	public void IsLinked(List collMessageLinkStatus);

	/**
	 * 
	 * @param strMessageId
	 * @param linkTo
	 */
	public boolean IsLinked(String strMessageId, LinkToBusOb linkTo);

	/**
	 * 
	 * @param strMessageId
	 * @param linkTo
	 * @param emailAddress
	 */
	public boolean IsLinked(String strMessageId, LinkToBusOb linkTo, EmailAddress emailAddress);

	/**
	 * 
	 * @param data
	 */
	public LinkOperation Link(PersistenceInfo data);

	/**
	 * 
	 * @param data
	 * @param strName
	 * @param strId
	 */
	public LinkOperation Link(PersistenceInfo data, String strName, String strId);

	/**
	 * 
	 * @param strEmail
	 */
	public List LookupByEmail(String strEmail);

	public String MeetingHistoryDefName();

	/**
	 * 
	 * @param strName
	 */
	public void RemoveEmailBusinessObjectName(String strName);

	public void SaveEmailBusinessObjectNames();

	/**
	 * 
	 * @param data
	 */
	public LinkOperation UpdateLink(PersistenceInfo data);

}