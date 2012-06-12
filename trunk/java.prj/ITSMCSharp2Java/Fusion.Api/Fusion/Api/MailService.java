package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:01
 */
public class MailService {

	private Fusion.BusinessLogic.MailService m_mailService;

	public MailService(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param mailService
	 */
	public MailService(Fusion.BusinessLogic.MailService mailService){

	}

	/**
	 * 
	 * @param strEmailAddress
	 */
	public boolean IsValidAddress(String strEmailAddress){
		return false;
	}

	protected Fusion.BusinessLogic.MailService RealMailService(){
		return null;
	}

	/**
	 * 
	 * @param message
	 */
	public void SendMessage(Fusion.MailMessage message){

	}

	/**
	 * 
	 * @param message
	 */
	public void SendMessage(System.Web.Mail.MailMessage message){

	}

	/**
	 * 
	 * @param strFrom
	 * @param strTo
	 * @param strSubject
	 * @param strMessageText
	 */
	public void SendMessage(String strFrom, String strTo, String strSubject, String strMessageText){

	}

}