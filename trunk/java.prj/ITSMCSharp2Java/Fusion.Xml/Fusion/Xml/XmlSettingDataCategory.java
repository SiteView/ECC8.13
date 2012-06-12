package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:57
 */
public class XmlSettingDataCategory {

	private string Bool = "Bool";
	private string DateTime = "DateTime";
	private string Double = "Double";
	private string Group = "Group";
	private string Integer = "Integer";
	private string None = "None";
	private string String = "String";

	public XmlSettingDataCategory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param sdc
	 */
	public static string CategoryToXmlCategory(SettingDataCategory sdc){
		return "";
	}

	public string getBool(){
		return Bool;
	}

	public string getDateTime(){
		return DateTime;
	}

	public string getDouble(){
		return Double;
	}

	public string getGroup(){
		return Group;
	}

	public string getInteger(){
		return Integer;
	}

	public string getNone(){
		return None;
	}

	public string getString(){
		return String;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBool(string newVal){
		Bool = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDateTime(string newVal){
		DateTime = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDouble(string newVal){
		Double = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGroup(string newVal){
		Group = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setInteger(string newVal){
		Integer = newVal;
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
	 * @param newVal
	 */
	public void setString(string newVal){
		String = newVal;
	}

	/**
	 * 
	 * @param strXmlCategory
	 */
	public static SettingDataCategory XmlCategoryToCategory(string strXmlCategory){
		return null;
	}

}