package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:44
 */
public class XmlBusinessObjectCategory {

	private string External = "EXTERNAL";
	private string Standard = "STANDARD";

	public XmlBusinessObjectCategory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param eBusinessObjectCategory
	 */
	public static string CategoryToXmlCategory(BusinessObjectCategory eBusinessObjectCategory){
		return "";
	}

	public string getExternal(){
		return External;
	}

	public string getStandard(){
		return Standard;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setExternal(string newVal){
		External = newVal;
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
	 * @param strXmlCategory
	 */
	public static BusinessObjectCategory XmlCategoryToCategory(string strXmlCategory){
		return null;
	}

}