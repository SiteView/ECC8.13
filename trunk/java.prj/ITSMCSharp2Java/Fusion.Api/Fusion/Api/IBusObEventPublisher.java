package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:49
 */
public interface IBusObEventPublisher {

	/**
	 * 
	 * @param subscriber
	 */
	public void DeRegister(IBusObEventSubscriber subscriber);

	/**
	 * 
	 * @param eventItem
	 * @param busOb
	 * @param state
	 */
	public void Publish(EventItem eventItem, BusinessObject busOb, BusinessObjectSaveState state);

	/**
	 * 
	 * @param eventItems
	 * @param busOb
	 * @param state
	 */
	public void Publish(List eventItems, BusinessObject busOb, BusinessObjectSaveState state);

	/**
	 * 
	 * @param subscriber
	 */
	public void Register(IBusObEventSubscriber subscriber);

}