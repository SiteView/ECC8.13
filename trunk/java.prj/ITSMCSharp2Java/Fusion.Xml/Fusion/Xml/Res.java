package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:38
 */
internal class Res {

	private static ResourceManager m_defaultResources = null;



	public void finalize() throws Throwable {

	}

	private Res(){

	}

	public static ResourceManager Default(){
		return null;
	}

	/**
	 * 
	 * @param strResourceId
	 */
	public static string GetExceptionString(string strResourceId){
		return "";
	}

}