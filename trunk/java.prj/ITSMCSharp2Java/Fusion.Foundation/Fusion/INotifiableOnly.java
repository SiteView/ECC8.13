package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:51
 */
public interface INotifiableOnly {

	/**
	 * 
	 * @param notif
	 * @param ur
	 */
	public boolean HandleNotification(Notification notif, UpdateResult ur);

}