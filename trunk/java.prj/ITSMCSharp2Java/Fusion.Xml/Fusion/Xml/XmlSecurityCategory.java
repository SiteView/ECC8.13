package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:56
 */
public class XmlSecurityCategory {

	private string BusinessObject = "BusinessObject";
	private string Module = "Module";
	private string Relationship = "Relationship";

	public XmlSecurityCategory(){

	}

	public void finalize() throws Throwable {

	}

	public string getBusinessObject(){
		return BusinessObject;
	}

	public string getModule(){
		return Module;
	}

	public string getRelationship(){
		return Relationship;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBusinessObject(string newVal){
		BusinessObject = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setModule(string newVal){
		Module = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRelationship(string newVal){
		Relationship = newVal;
	}

	/**
	 * 
	 * @param strXmlCategory
	 */
	public static SecurityCategory ToCategory(string strXmlCategory){
		return null;
	}

	/**
	 * 
	 * @param sc
	 */
	public static string ToString(SecurityCategory sc){
		return "";
	}

}