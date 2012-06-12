package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:44
 */
public class XmlApplicationType {

	private string Administrator = "Administrator";
	private string MainApplication = "MainApplication";
	private string Other = "Other";
	private string Web = "Web";
	private string WebSelfService = "WebSelfService";

	public XmlApplicationType(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param applicationType
	 */
	public static string ApplicationTypeToString(ApplicationType applicationType){
		return "";
	}

	public string getAdministrator(){
		return Administrator;
	}

	public string getMainApplication(){
		return MainApplication;
	}

	public string getOther(){
		return Other;
	}

	public string getWeb(){
		return Web;
	}

	public string getWebSelfService(){
		return WebSelfService;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAdministrator(string newVal){
		Administrator = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMainApplication(string newVal){
		MainApplication = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOther(string newVal){
		Other = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setWeb(string newVal){
		Web = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setWebSelfService(string newVal){
		WebSelfService = newVal;
	}

	/**
	 * 
	 * @param strApplicationType
	 */
	public static ApplicationType StringToApplicationType(string strApplicationType){
		return null;
	}

}