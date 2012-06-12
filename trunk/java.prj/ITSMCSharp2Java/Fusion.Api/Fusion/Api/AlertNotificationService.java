package Fusion.Api;

import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:22
 */
public class AlertNotificationService implements IAlertNotificationService, IAlertNotification {

	private IFusionApi m_api = null;
	private String m_cAddressType = "E-Mail";
	private String m_DefaultEmailPurpose = "";
	private IOrchestrator m_orch = null;

	public AlertNotificationService(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param api
	 * @param orch
	 */
	public AlertNotificationService(IFusionApi api, IOrchestrator orch){

	}

	/**
	 * 
	 * @param email
	 */
	private BusinessObject CreateEmailAddressObject(String email){
		return null;
	}

	/**
	 * 
	 * @param subject
	 * @param body
	 * @param fromEmployee
	 * @param alToEmployees
	 */
	public BusinessObject CreateNotificationObject(String subject, String body, BusinessObject fromEmployee, ArrayList alToEmployees){
		return null;
	}

	/**
	 * 
	 * @param subject
	 * @param body
	 * @param fromEmployee
	 * @param arrToAddr
	 */
	public BusinessObject CreateNotificationObject(String subject, String body, BusinessObject fromEmployee, String[] arrToAddr){
		return null;
	}

	private String DefaultEmailPurpose(){
		return "";
	}

	private String GetDefaultEmailPurposeType(){
		return "";
	}

	/**
	 * 
	 * @param id
	 * @param name
	 */
	public boolean SendMessageAsynch(String id, String name){
		return false;
	}

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
	public boolean SendMessageAsynch(String sSubject, String sBody, String guidFromEmployeeRecId, String sToAddr, String sCc, String sBcc, AlertNotificationFormatTypes fmtType, String sPerspective){
		return false;
	}

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
	public boolean SendMessageAsynch(String sSubject, String sBody, String sFromAddr, String sToAddr, String sCc, String sBcc, AlertNotificationFormatTypes fmtType, String sPerspective){
		return false;
	}

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
	public boolean SendMessageAsynch(String id, String name, String smtpServer, String smtpPort, String smtpAuthMode, String smtpUid, String smtpPwd, String defaultFromAddr, boolean bUseInvoker){
		return false;
	}

	/**
	 * 
	 * @param id
	 * @param name
	 */
	public boolean SendMessageSynch(String id, String name){
		return false;
	}

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
	public boolean SendMessageSynch(String sSubject, String sBody, Guid guidFromEmployeeRecId, String sToAddr, String sCc, String sBcc, AlertNotificationFormatTypes fmtType, String sPerspective){
		return false;
	}

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
	public boolean SendMessageSynch(String sSubject, String sBody, String sFromAddr, String sToAddr, String sCc, String sBcc, AlertNotificationFormatTypes fmtType, String sPerspective){
		return false;
	}

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
	public boolean SendMessageSynch(String id, String name, String smtpServer, String smtpPort, String smtpAuthMode, String smtpUid, String smtpPwd, String defaultFromAddr, boolean bUseInvoker){
		return false;
	}

	/**
	 * 
	 * @param smtpServer
	 * @param smtpUid
	 * @param smtpPwd
	 */
	public void SetSMTPServerConfig(String smtpServer, String smtpUid, String smtpPwd){

	}

	/**
	 * 
	 * @param smtpServer
	 * @param smtpPort
	 * @param authMode
	 * @param smtpUid
	 * @param smtpPwd
	 * @param defaultFromAddr
	 * @param bUseInvoker
	 */
	public void SetSMTPServerConfig(String smtpServer, String smtpPort, String authMode, String smtpUid, String smtpPwd, String defaultFromAddr, boolean bUseInvoker){

	}

	/**
	 * 
	 * @param fld
	 * @param fv
	 */
	private void SetValue(Field fld, FusionValue fv){

	}

	public void Start(){

	}

	public void Stop(){

	}

}
