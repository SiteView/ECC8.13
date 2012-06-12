package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:43
 */
public interface IAlertNotification {

	/**
	 * 
	 * @param id
	 * @param name
	 */
	public boolean SendMessageAsynch(String id, String name);

	/**
	 * 
	 * @param sSubject
	 * @param sBody
	 * @param guidFromEmployeeRecId
	 * @param sToAddr
	 * @param sCc
	 * @param sBcc
	 * @param fmtType
	 * @param sPerspective
	 */
	public boolean SendMessageAsynch(String sSubject, String sBody, Guid guidFromEmployeeRecId, String sToAddr, String sCc, String sBcc, AlertNotificationFormatTypes fmtType, String sPerspective);

	/**
	 * 
	 * @param sSubject
	 * @param sBody
	 * @param sFromAddr
	 * @param sToAddr
	 * @param sCc
	 * @param sBcc
	 * @param fmtType
	 * @param sPerspective
	 */
	public boolean SendMessageAsynch(String sSubject, String sBody, String sFromAddr, String sToAddr, String sCc, String sBcc, AlertNotificationFormatTypes fmtType, String sPerspective);

	/**
	 * 
	 * @param id
	 * @param name
	 * @param smtpServer
	 * @param smtpPort
	 * @param smtpAuthMode
	 * @param smtpUid
	 * @param smtpPwd
	 * @param defaultFromAddr
	 * @param bUseInvoker
	 */
	public boolean SendMessageAsynch(String id, String name, String smtpServer, String smtpPort, String smtpAuthMode, String smtpUid, String smtpPwd, String defaultFromAddr, boolean bUseInvoker);

	/**
	 * 
	 * @param id
	 * @param name
	 */
	public boolean SendMessageSynch(String id, String name);

	/**
	 * 
	 * @param sSubject
	 * @param sBody
	 * @param guidFromEmployeeRecId
	 * @param sToAddr
	 * @param sCc
	 * @param sBcc
	 * @param fmtType
	 * @param sPerspective
	 */
	public boolean SendMessageSynch(String sSubject, String sBody, Guid guidFromEmployeeRecId, String sToAddr, String sCc, String sBcc, AlertNotificationFormatTypes fmtType, String sPerspective);

	/**
	 * 
	 * @param sSubject
	 * @param sBody
	 * @param sFromAddr
	 * @param sToAddr
	 * @param sCc
	 * @param sBcc
	 * @param fmtType
	 * @param sPerspective
	 */
	public boolean SendMessageSynch(String sSubject, String sBody, String sFromAddr, String sToAddr, String sCc, String sBcc, AlertNotificationFormatTypes fmtType, String sPerspective);

	/**
	 * 
	 * @param id
	 * @param name
	 * @param smtpServer
	 * @param smtpPort
	 * @param smtpAuthMode
	 * @param smtpUid
	 * @param smtpPwd
	 * @param defaultFromAddr
	 * @param bUseInvoker
	 */
	public boolean SendMessageSynch(String id, String name, String smtpServer, String smtpPort, String smtpAuthMode, String smtpUid, String smtpPwd, String defaultFromAddr, boolean bUseInvoker);

	/**
	 * 
	 * @param smtpServer
	 * @param smtpPort
	 * @param smtpAuthMode
	 * @param smtpUid
	 * @param smtpPwd
	 * @param defaultFromAddr
	 * @param bUseInvoker
	 */
	public void SetSMTPServerConfig(String smtpServer, String smtpPort, String smtpAuthMode, String smtpUid, String smtpPwd, String defaultFromAddr, boolean bUseInvoker);

	public void Start();

	public void Stop();

}