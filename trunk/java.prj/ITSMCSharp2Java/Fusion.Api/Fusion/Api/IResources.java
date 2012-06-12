package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:53
 */
public interface IResources {

	public List GetListOfImages();

	/**
	 * 
	 * @param module
	 */
	public Assembly GetModuleAssembly(String module);

	/**
	 * 
	 * @param resource
	 */
	public Stream GetResourceStreamFromModule(String resource);

	/**
	 * 
	 * @param module
	 * @param resource
	 */
	public Stream GetResourceStreamFromModule(String module, String resource);

}