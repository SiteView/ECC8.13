package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:46
 */
public class XmlCommitActionCategory {

	private string AddData = "AddData";

	public XmlCommitActionCategory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param cat
	 */
	public static string CategoryToXmlCategory(CommitActionCategory cat){
		return "";
	}

	public string getAddData(){
		return AddData;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAddData(string newVal){
		AddData = newVal;
	}

	/**
	 * 
	 * @param strXmlCategory
	 */
	public static CommitActionCategory XmlCategoryToCategory(string strXmlCategory){
		return null;
	}

}