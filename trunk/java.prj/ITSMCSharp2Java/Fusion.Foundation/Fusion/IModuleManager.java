package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:49
 */
public interface IModuleManager {

	public List FailedModules();

	/**
	 * 
	 * @param strName
	 */
	public ModuleInfo GetModuleInfo(String strName);

	/**
	 * 
	 * @param strAssembly
	 */
	public ModuleInfo GetModuleInfoFromAssemblyName(String strAssembly);

	/**
	 * 
	 * @param strName
	 */
	public IModule GetModuleSnapin(String strName);

	/**
	 * 
	 * @param strName
	 * @param strAssembly
	 */
	public boolean IsRegisteredModule(String strName, String strAssembly);

	/**
	 * 
	 * @param strAssembly
	 */
	public boolean IsSystemAssembly(String strAssembly);

	/**
	 * 
	 * @param strName
	 */
	public boolean IsSystemModuleName(String strName);

	public List RegisteredModules();

	/**
	 * 
	 * @param strName
	 * @param strAssembly
	 */
	public void RegisterInstantModule(String strName, String strAssembly);

	/**
	 * 
	 * @param strName
	 * @param strAssembly
	 */
	public void RegisterModule(String strName, String strAssembly);

	/**
	 * 
	 * @param ms
	 */
	public void RegisterModuleService(IModuleService ms);

	public void SetConnected();

	/**
	 * 
	 * @param strName
	 */
	public void UnregisterInstantModule(String strName);

	/**
	 * 
	 * @param strName
	 */
	public void UnregisterModule(String strName);

}