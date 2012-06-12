package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:28
 */
internal class Res {

	private static ResourceManager m_databaseResources = null;
	private static ResourceManager m_defaultResources = null;



	public void finalize() throws Throwable {

	}

	private Res(){

	}

	public static ResourceManager DatabaseResources(){
		return null;
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