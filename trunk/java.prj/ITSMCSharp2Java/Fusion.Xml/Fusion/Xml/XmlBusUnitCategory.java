package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:45
 */
public class XmlBusUnitCategory {

	private string BusinessObject = "BusinessObject";
	private string None = "None";

	public XmlBusUnitCategory(){

	}

	public void finalize() throws Throwable {

	}

	public string getBusinessObject(){
		return BusinessObject;
	}

	public string getNone(){
		return None;
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
	public void setNone(string newVal){
		None = newVal;
	}

	/**
	 * 
	 * @param strBusUnitCategory
	 */
	public static BusUnitCategory ToCategory(string strBusUnitCategory){
		return null;
	}

	/**
	 * 
	 * @param busUnitCategory
	 */
	public static string ToString(BusUnitCategory busUnitCategory){
		return "";
	}

}