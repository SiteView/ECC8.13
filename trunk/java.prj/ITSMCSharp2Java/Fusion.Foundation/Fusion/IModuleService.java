package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:50
 */
public interface IModuleService {

	/**
	 * 
	 * @param mi
	 */
	public void RegisterModule(ModuleInfo mi);

	/**
	 * 
	 * @param mi
	 */
	public void UnregisterModule(ModuleInfo mi);

}