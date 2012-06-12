package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:47
 */
public interface IActionExecutor {

	public void Abort();

	public void Execute();

	public void FinalizeAction();

	/**
	 * 
	 * @param api
	 * @param context
	 * @param def
	 */
	public void Initialize(IFusionApi api, AutoTaskContext context, ActionDef def);

}