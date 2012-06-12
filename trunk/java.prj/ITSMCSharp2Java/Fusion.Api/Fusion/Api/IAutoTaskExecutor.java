package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:48
 */
public interface IAutoTaskExecutor {

	public void Abort();

	public void Execute();

	/**
	 * 
	 * @param api
	 * @param context
	 * @param def
	 */
	public void Initialize(IFusionApi api, AutoTaskContext context, AutoTaskDef def);

	public AutoTaskProgressHandler ProgressHandler();

}