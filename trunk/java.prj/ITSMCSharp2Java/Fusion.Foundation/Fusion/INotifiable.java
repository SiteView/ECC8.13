package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:50
 */
public interface INotifiable extends INotifiableOnly {

	/**
	 * 
	 * @param target
	 */
	public void AddSubscriber(INotifiableOnly target);

	public void RemoveAllSubscribers();

	/**
	 * 
	 * @param target
	 */
	public void RemoveSubscriber(INotifiableOnly target);

}