package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:47
 */
public class XmlConstraintFieldCategory {

	private string defNone = "NONE";
	private string defParentRecId = "PARENTRECID";
	private string defRecId = "RECID";

	public XmlConstraintFieldCategory(){

	}

	public void finalize() throws Throwable {

	}

	public string getdefNone(){
		return defNone;
	}

	public string getdefParentRecId(){
		return defParentRecId;
	}

	public string getdefRecId(){
		return defRecId;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefNone(string newVal){
		defNone = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefParentRecId(string newVal){
		defParentRecId = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefRecId(string newVal){
		defRecId = newVal;
	}

	/**
	 * 
	 * @param strCategory
	 */
	public static ValueSources ToCategory(string strCategory){
		return null;
	}

	/**
	 * 
	 * @param vsFieldCategory
	 */
	public static string ToString(ValueSources vsFieldCategory){
		return "";
	}

}