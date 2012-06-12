package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:23
 */
public class SubscriberList {

	private ArrayList m_aTargets = new ArrayList();

	public SubscriberList(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param target
	 */
	public void AddSubscriber(INotifiableOnly target){

	}

	protected void EliminateDeadReferences(){

	}

	/**
	 * 
	 * @param notif
	 * @param ur
	 */
	public boolean HandleNotification(Notification notif, UpdateResult ur){
		return null;
	}

	/**
	 * 
	 * @param notif
	 * @param ur
	 */
	private boolean HandleNotificationDelegate(Notification notif, UpdateResult ur){
		return null;
	}

	/**
	 * 
	 * @param target
	 */
	protected int ItemInList(INotifiableOnly target){
		return 0;
	}

	public void RemoveAllSubscribers(){

	}

	/**
	 * 
	 * @param target
	 */
	public void RemoveSubscriber(INotifiableOnly target){

	}

}