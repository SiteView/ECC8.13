package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:02
 */
public class LinkAnnotationNames {

	private String AttachmentName = "AttachmentName";
	private String EntryId = "EntryId";
	private String LinkToActivity = "LinkToActivity";
	private String LinkToMessage = "LinkToMessage";
	private String MessageId = "MessageID";
	private String ParentLink = "ParentLink";

	public LinkAnnotationNames(){

	}

	public void finalize() throws Throwable {

	}

	public String getAttachmentName(){
		return AttachmentName;
	}

	public String getEntryId(){
		return EntryId;
	}

	public String getLinkToActivity(){
		return LinkToActivity;
	}

	public String getLinkToMessage(){
		return LinkToMessage;
	}

	public String getMessageId(){
		return MessageId;
	}

	public String getParentLink(){
		return ParentLink;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAttachmentName(String newVal){
		AttachmentName = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEntryId(String newVal){
		EntryId = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLinkToActivity(String newVal){
		LinkToActivity = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLinkToMessage(String newVal){
		LinkToMessage = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMessageId(String newVal){
		MessageId = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setParentLink(String newVal){
		ParentLink = newVal;
	}

}