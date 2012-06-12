package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:29
 */
public class AutoTaskExecutor implements IAutoTaskExecutor {

	private IFusionApi m_Api;
	private boolean m_bAbort = false;
	private AutoTaskContext m_Context;
	private AutoTaskDef m_Def;
	private int m_nTotalNumActionStages;
	private AutoTaskProgressHandler m_ProgressHandler;
	private String m_strActionMessage;
	private String m_strNavigateMessage;
	private String m_strPostActionMessage;
	private String m_strPreActionMessage;
	private String m_strSaveMessage;
	private int NavigationStagesCount = 3;
	private int SavingStagesCount = 6;

	public AutoTaskExecutor(){

	}

	public void finalize() throws Throwable {

	}

	public void Abort(){

	}

	/**
	 * 
	 * @param executor
	 */
	private void AbortIfNecessary(IActionExecutor executor){

	}

	/**
	 * 
	 * @param aExecutors
	 */
	private void AbortIfNecessary(IActionExecutor[] aExecutors){

	}

	public IFusionApi Api(){
		return null;
	}

	public AutoTaskContext Context(){
		return null;
	}

	public AutoTaskDef Def(){
		return null;
	}

	public void Execute(){

	}

	/**
	 * 
	 * @param api
	 * @param busOb
	 * @param def
	 * @param interaction
	 * @param bSaveObjects
	 */
	public static void ExecuteTask(IFusionApi api, BusinessObject busOb, AutoTaskDef def, IUIInteraction interaction, boolean bSaveObjects){

	}

	/**
	 * 
	 * @param api
	 * @param context
	 * @param def
	 */
	public void Initialize(IFusionApi api, AutoTaskContext context, AutoTaskDef def){

	}

	private void PerformActions(){

	}

	/**
	 * 
	 * @param aExecutors
	 */
	private void PerformActionsExecution(IActionExecutor[] aExecutors){

	}

	/**
	 * 
	 * @param aExecutors
	 */
	private void PerformActionsFinalization(IActionExecutor[] aExecutors){

	}

	private IActionExecutor[] PerformActionsInitialization(){
		return null;
	}

	private void PerformPostActions(){

	}

	private void PerformPreActions(){

	}

	private void PerformUIActions(){

	}

	public AutoTaskProgressHandler ProgressHandler(){
		return null;
	}

	private void SaveAffectedObjects(){

	}

	/**
	 * 
	 * @param actionType
	 * @param actionStage
	 * @param nPosition
	 * @param nBusOb
	 */
	private void UpdateProgress(ActionType actionType, ActionStage actionStage, int nPosition, int nBusOb){

	}

}