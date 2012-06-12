package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:58
 */
public class XmlSettingSourceCategory {

	private string DataBase = "DataBase";
	private string Local = "Local";

	public XmlSettingSourceCategory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param ssc
	 */
	public static string CategoryToXmlCategory(SettingSourceCategory ssc){
		return "";
	}

	public string getDataBase(){
		return DataBase;
	}

	public string getLocal(){
		return Local;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDataBase(string newVal){
		DataBase = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLocal(string newVal){
		Local = newVal;
	}

	/**
	 * 
	 * @param strXmlCategory
	 */
	public static SettingSourceCategory XmlCategoryToCategory(string strXmlCategory){
		return null;
	}

}