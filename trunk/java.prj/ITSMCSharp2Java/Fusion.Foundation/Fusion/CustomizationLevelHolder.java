package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:58
 */
public class CustomizationLevelHolder {

	private static boolean m_bCanEditXML = false;
	private static boolean m_bCreateMasterAndGroupBusOb = false;
	private static Fusion.Xml.CustomizationLevel m_CustomizationLevel = Fusion.Xml.CustomizationLevel.NotSet;

	public CustomizationLevelHolder(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strUserId
	 * @param strPassword
	 */
	public static void Authorize(String strUserId, String strPassword){

	}

	public static boolean CanCreateMasterAndGroupBusOb(){
		return null;
	}

	public static boolean CanEditXML(){
		return null;
	}

	public static Fusion.Xml.CustomizationLevel CustomizationLevel(){
		return null;
	}

}