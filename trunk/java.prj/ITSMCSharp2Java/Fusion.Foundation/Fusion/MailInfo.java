package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:08
 */
public class MailInfo extends DataTransport {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:08
	 */
	public enum FlowDirection {
		Inbound,
		Outbound,
		Unknown
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:08
	 */
	public enum ProcessingOptions {
		SendWithComposerGui,
		SendWithoutPrompt
	}

	private boolean m_bUseEncryption;
	private boolean m_bUseSignature;
	private ArrayList m_contactObjs;
	private Hashtable m_dictProviderInfo;
	private FlowDirection m_flowDirection;
	private Hashtable m_htSavePropToFusion;
	private EmailAddress m_originalSenderAddr;
	private ProcessingOptions m_processingOption;
	private String m_strBodyHtml;
	private String m_strBodyRtf;
	private String m_strBodyText;
	private String m_strConversationIndex;
	private String m_strLayout;
	private String m_strReplyTo;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public MailInfo(){

	}

	/**
	 * 
	 * @param flowDirection
	 */
	public MailInfo(FlowDirection flowDirection){

	}

	public String AnnotationGroup(){
		return "";
	}

	public String BodyHtml(){
		return "";
	}

	public String BodyRtf(){
		return "";
	}

	public String BodyText(){
		return "";
	}

	/**
	 * 
	 * @param strFormat
	 */
	public String BuildLayout(String strFormat){
		return "";
	}

	public String ConversationId(){
		return "";
	}

	public ArrayList EmailContactBusinessObjects(){
		return null;
	}

	/**
	 * 
	 * @param prop
	 */
	public boolean IsPropertyPersistable(PropertyInfo prop){
		return null;
	}

	public String Layout(){
		return "";
	}

	public LinkToBusOb LinkedTo(){
		return null;
	}

	public FlowDirection MessageDirection(){
		return null;
	}

	public EmailAddress OriginalSender(){
		return null;
	}

	public ProcessingOptions ProcessingOption(){
		return null;
	}

	public Hashtable ProviderInfo(){
		return null;
	}

	public String ReplyTo(){
		return "";
	}

	/**
	 * 
	 * @param prop
	 * @param bYesSaveToFusion
	 */
	public void SetPropertySaveState(PropertyInfo prop, boolean bYesSaveToFusion){

	}

	public boolean UseSMimeSecurity(){
		return null;
	}

	public boolean UseSMimeSignature(){
		return null;
	}

	/**
	 * 
	 * @param prop
	 */
	public boolean YesSaveToFusion(PropertyInfo prop){
		return null;
	}

}