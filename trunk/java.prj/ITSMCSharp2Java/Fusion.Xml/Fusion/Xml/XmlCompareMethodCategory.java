package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:46
 */
public class XmlCompareMethodCategory {

	private string defDate = "DATE";
	private string defDateTime = "DATETIME";
	private string defDefault = "DEFAULT";
	private string defLogical = "LOGICAL";
	private string defNumber = "NUMBER";
	private string defText = "TEXT";
	private string defTime = "TIME";

	public XmlCompareMethodCategory(){

	}

	public void finalize() throws Throwable {

	}

	public string getdefDate(){
		return defDate;
	}

	public string getdefDateTime(){
		return defDateTime;
	}

	public string getdefDefault(){
		return defDefault;
	}

	public string getdefLogical(){
		return defLogical;
	}

	public string getdefNumber(){
		return defNumber;
	}

	public string getdefText(){
		return defText;
	}

	public string getdefTime(){
		return defTime;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefDate(string newVal){
		defDate = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefDateTime(string newVal){
		defDateTime = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefDefault(string newVal){
		defDefault = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefLogical(string newVal){
		defLogical = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefNumber(string newVal){
		defNumber = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefText(string newVal){
		defText = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefTime(string newVal){
		defTime = newVal;
	}

	/**
	 * 
	 * @param strCategory
	 */
	public static CompareMethod ToCategory(string strCategory){
		return null;
	}

	/**
	 * 
	 * @param compareMethodValue
	 */
	public static string ToString(CompareMethod compareMethodValue){
		return "";
	}

}