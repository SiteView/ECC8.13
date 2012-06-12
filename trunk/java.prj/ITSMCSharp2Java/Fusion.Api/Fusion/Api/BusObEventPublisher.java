package Fusion.Api;

import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:39
 */
public class BusObEventPublisher implements IBusObEventPublisher {

	private ArrayList m_alSubscribers = new ArrayList();
	private IFusionApi m_api;

	public BusObEventPublisher(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param api
	 */
	public BusObEventPublisher(IFusionApi api){

	}

	/**
	 * 
	 * @param subscriber
	 */
	public void DeRegister(IBusObEventSubscriber subscriber){

	}

	/**
	 * 
	 * @param eventItem
	 * @param busOb
	 * @param state
	 */
	public void Publish(EventItem eventItem, BusinessObject busOb, BusinessObjectSaveState state){

	}

	/**
	 * 
	 * @param eventItems
	 * @param busOb
	 * @param state
	 */
	public void Publish(List eventItems, BusinessObject busOb, BusinessObjectSaveState state){

	}

	/**
	 * 
	 * @param subscriber
	 */
	public void Register(IBusObEventSubscriber subscriber){

	}

	private void RegisterCoreSubscribers(){

	}

}