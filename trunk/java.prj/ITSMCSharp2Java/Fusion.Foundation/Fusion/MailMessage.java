package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:09
 */
public class MailMessage {

	private ArrayList m_alAttachments = new ArrayList();
	private Hashtable m_htCustomHeaders = new Hashtable();
	private Fusion.MailFormat m_mailFormat = Fusion.MailFormat.Text;
	private Fusion.MailPriority m_mailPriority = Fusion.MailPriority.Normal;
	private String m_strBCC = "";
	private String m_strBody = "";
	private String m_strCC = "";
	private String m_strFrom = "";
	private String m_strSubject = "";
	private String m_strTo = "";

	public MailMessage(){

	}

	public void finalize() throws Throwable {

	}

	public IList Attachments(){
		return null;
	}

	public String BCC(){
		return "";
	}

	public String Body(){
		return "";
	}

	public String CC(){
		return "";
	}

	public String From(){
		return "";
	}

	public Map Headers(){
		return null;
	}

	public Fusion.MailFormat MailFormat(){
		return null;
	}

	public Fusion.MailPriority MailPriority(){
		return null;
	}

	public String Subject(){
		return "";
	}

	public String To(){
		return "";
	}

}