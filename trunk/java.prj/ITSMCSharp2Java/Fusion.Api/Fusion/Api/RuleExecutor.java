package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:30
 */
public abstract class RuleExecutor implements IBusObEventSubscriber {

	private IFusionApi m_api;

	public RuleExecutor(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param api
	 */
	public RuleExecutor(IFusionApi api){

	}

	protected IFusionApi Api(){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param busOb
	 * @param state
	 */
	protected abstract void ExecuteAction(AutoTaskDef def, BusinessObject busOb, BusinessObjectSaveState state);

	protected abstract BusinessRuleExecutionType ExecutionTypeToHandle();

	/**
	 * 
	 * @param sID
	 * @param busOb
	 * @param state
	 */
	public void HandleBusRule(String sID, BusinessObject busOb, BusinessObjectSaveState state){

	}

	/**
	 * 
	 * @param eventItem
	 * @param busOb
	 * @param state
	 */
	public void HandleEvent(EventItem eventItem, BusinessObject busOb, BusinessObjectSaveState state){

	}

	/**
	 * 
	 * @param eventItems
	 * @param busOb
	 * @param state
	 */
	public void HandleEvents(List eventItems, BusinessObject busOb, BusinessObjectSaveState state){

	}

}