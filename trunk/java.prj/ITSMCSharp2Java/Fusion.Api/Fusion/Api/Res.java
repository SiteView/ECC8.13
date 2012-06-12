package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:23
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
	public static String GetExceptionString(String strResourceId){
		return "";
	}

}