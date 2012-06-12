package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:47
 */
public class XmlConstraintValueCategory {

	private string defField = "FIELD";
	private string defFunction = "FUNCTION";
	private string defLiteral = "LITERAL";
	private string defParentRecID = "PARENTRECID";
	private string defRecID = "RECID";
	private string defToken = "TOKEN";

	public XmlConstraintValueCategory(){

	}

	public void finalize() throws Throwable {

	}

	public string getdefField(){
		return defField;
	}

	public string getdefFunction(){
		return defFunction;
	}

	public string getdefLiteral(){
		return defLiteral;
	}

	public string getdefParentRecID(){
		return defParentRecID;
	}

	public string getdefRecID(){
		return defRecID;
	}

	public string getdefToken(){
		return defToken;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefField(string newVal){
		defField = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefFunction(string newVal){
		defFunction = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefLiteral(string newVal){
		defLiteral = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefParentRecID(string newVal){
		defParentRecID = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefRecID(string newVal){
		defRecID = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefToken(string newVal){
		defToken = newVal;
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
	 * @param vsValueCategory
	 */
	public static string ToString(ValueSources vsValueCategory){
		return "";
	}

}