package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:49
 */
public interface IBusObEventSubscriber {

	/**
	 * 
	 * @param sID
	 * @param busOb
	 * @param state
	 */
	public void HandleBusRule(String sID, BusinessObject busOb, BusinessObjectSaveState state);

	/**
	 * 
	 * @param eventItem
	 * @param busOb
	 * @param state
	 */
	public void HandleEvent(EventItem eventItem, BusinessObject busOb, BusinessObjectSaveState state);

	/**
	 * 
	 * @param eventItems
	 * @param busOb
	 * @param state
	 */
	public void HandleEvents(List eventItems, BusinessObject busOb, BusinessObjectSaveState state);

}