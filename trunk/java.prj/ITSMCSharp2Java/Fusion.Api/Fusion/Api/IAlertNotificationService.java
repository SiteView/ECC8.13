package Fusion.Api;

import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:48
 */
public interface IAlertNotificationService extends IAlertNotification {

	/**
	 * 
	 * @param subject
	 * @param body
	 * @param fromEmployee
	 * @param alToAddr
	 */
	public BusinessObject CreateNotificationObject(String subject, String body, BusinessObject fromEmployee, String[] alToAddr);

	/**
	 * 
	 * @param subject
	 * @param body
	 * @param fromEmployee
	 * @param alToEmployees
	 */
	public BusinessObject CreateNotificationObject(String subject, String body, BusinessObject fromEmployee, ArrayList alToEmployees);

}