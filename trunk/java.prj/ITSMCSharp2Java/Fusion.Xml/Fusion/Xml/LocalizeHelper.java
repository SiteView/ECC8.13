package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:35
 */
public abstract class LocalizeHelper {



	public void finalize() throws Throwable {

	}

	protected LocalizeHelper(){

	}

	/**
	 * 
	 * @param type
	 */
	public static ResourceManager GetResourceManager(Type type){
		return null;
	}

	/**
	 * 
	 * @param type
	 * @param enumName
	 */
	public static string GetValue(Type type, string enumName){
		return "";
	}

	/**
	 * 
	 * @param type
	 */
	public static ICollection GetValues(Type type){
		return null;
	}

	/**
	 * 
	 * @param type
	 */
	public static ListDictionary Localize(Type type){
		return null;
	}

	/**
	 * 
	 * @param type
	 * @param strValue
	 */
	public static object Parse(Type type, string strValue){
		return null;
	}

	/**
	 * 
	 * @param type
	 * @param strValue
	 * @param bIgnoreCase
	 */
	public static object Parse(Type type, string strValue, bool bIgnoreCase){
		return null;
	}

}