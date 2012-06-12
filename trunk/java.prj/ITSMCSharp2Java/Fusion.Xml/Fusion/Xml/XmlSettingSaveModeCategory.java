package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:58
 */
public class XmlSettingSaveModeCategory {

	private string Full = "Full";
	private string Merge = "Merge";

	public XmlSettingSaveModeCategory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param ssc
	 */
	public static string CategoryToXmlCategory(SettingSaveModeCategory ssc){
		return "";
	}

	public string getFull(){
		return Full;
	}

	public string getMerge(){
		return Merge;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFull(string newVal){
		Full = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMerge(string newVal){
		Merge = newVal;
	}

	/**
	 * 
	 * @param strXmlCategory
	 */
	public static SettingSaveModeCategory XmlCategoryToCategory(string strXmlCategory){
		return null;
	}

}