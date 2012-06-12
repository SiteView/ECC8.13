package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:57
 */
public class XmlFieldCategory {

	private String Binary = "Binary";
	private String DateTime = "DateTime";
	private String Logical = "Logical";
	private String Number = "Number";
	private String Text = "Text";

	public XmlFieldCategory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param fc
	 */
	public static Type CategoryToSystemType(FieldCategory fc){
		return null;
	}

	/**
	 * 
	 * @param fc
	 */
	public static String CategoryToXmlCategory(FieldCategory fc){
		return "";
	}

	public String getBinary(){
		return Binary;
	}

	public String getDateTime(){
		return DateTime;
	}

	public String getLogical(){
		return Logical;
	}

	public String getNumber(){
		return Number;
	}

	public String getText(){
		return Text;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBinary(String newVal){
		Binary = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDateTime(String newVal){
		DateTime = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLogical(String newVal){
		Logical = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNumber(String newVal){
		Number = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setText(String newVal){
		Text = newVal;
	}

	/**
	 * 
	 * @param strXmlCategory
	 */
	public static FieldCategory XmlCategoryToCategory(String strXmlCategory){
		return null;
	}

}