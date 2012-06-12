package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:02
 */
public class MessageLinkStatus {

	private EmailAddress m_emailAddress;
	private LinkToBusOb m_linkedTo;
	private LinkResults m_linkResults;
	private String m_strMessageId;

	public MessageLinkStatus(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strMessageId
	 */
	public MessageLinkStatus(String strMessageId){

	}

	/**
	 * 
	 * @param strMessageId
	 * @param emailAddress
	 */
	public MessageLinkStatus(String strMessageId, EmailAddress emailAddress){

	}

	/**
	 * 
	 * @param strMessageId
	 * @param linkTo
	 * @param emailAddress
	 */
	public MessageLinkStatus(String strMessageId, LinkToBusOb linkTo, EmailAddress emailAddress){

	}

	public EmailAddress Address(){
		return null;
	}

	public String AddressAsString(){
		return "";
	}

	public boolean IsLinked(){
		return null;
	}

	public LinkToBusOb LinkedTo(){
		return null;
	}

	public String MessageId(){
		return "";
	}

	public LinkResults Status(){
		return null;
	}

}