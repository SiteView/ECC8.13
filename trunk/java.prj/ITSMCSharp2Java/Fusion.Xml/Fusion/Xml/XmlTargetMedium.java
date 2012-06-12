package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:38:27
 */
public class XmlTargetMedium {

	private string Mobile = "Mobile";
	private string Standard = "Standard";
	private string WebClient = "WebClient";

	public XmlTargetMedium(){

	}

	public void finalize() throws Throwable {

	}

	public string getMobile(){
		return Mobile;
	}

	public string getStandard(){
		return Standard;
	}

	public string getWebClient(){
		return WebClient;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMobile(string newVal){
		Mobile = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setStandard(string newVal){
		Standard = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setWebClient(string newVal){
		WebClient = newVal;
	}

	/**
	 * 
	 * @param strTargetMedium
	 */
	public static TargetMedium StringToTargetMedium(string strTargetMedium){
		return null;
	}

	/**
	 * 
	 * @param eTargetMedium
	 */
	public static string TargetMediumToString(TargetMedium eTargetMedium){
		return "";
	}

}