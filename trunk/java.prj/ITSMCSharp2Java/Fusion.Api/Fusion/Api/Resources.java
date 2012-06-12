package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:24
 */
public class Resources implements IResources {

	private IOrchestrator m_orch = null;

	public Resources(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param orch
	 */
	public Resources(IOrchestrator orch){

	}

	public List GetListOfImages(){
		return null;
	}

	/**
	 * 
	 * @param module
	 */
	public Assembly GetModuleAssembly(String module){
		return null;
	}

	/**
	 * 
	 * @param resource
	 */
	public Stream GetResourceStreamFromModule(String resource){
		return null;
	}

	/**
	 * 
	 * @param module
	 * @param resource
	 */
	public Stream GetResourceStreamFromModule(String module, String resource){
		return null;
	}

	public void Initialize(){

	}

}