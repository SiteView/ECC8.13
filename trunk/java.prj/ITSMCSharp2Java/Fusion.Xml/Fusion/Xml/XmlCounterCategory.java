package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:49
 */
public class XmlCounterCategory {

	private string Binary = "BINARY";
	private string Custom = "CUSTOM";
	private string Hex = "HEX";
	private string Numeric = "NUMERIC";
	private string Octal = "OCTAL";
	private string RomanAlphabet = "ROMANALPHABET";

	public XmlCounterCategory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param catCounter
	 */
	public static string CounterCategoryToString(CounterCategory catCounter){
		return "";
	}

	public string getBinary(){
		return Binary;
	}

	public string getCustom(){
		return Custom;
	}

	public string getHex(){
		return Hex;
	}

	public string getNumeric(){
		return Numeric;
	}

	public string getOctal(){
		return Octal;
	}

	public string getRomanAlphabet(){
		return RomanAlphabet;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBinary(string newVal){
		Binary = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCustom(string newVal){
		Custom = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setHex(string newVal){
		Hex = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNumeric(string newVal){
		Numeric = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOctal(string newVal){
		Octal = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRomanAlphabet(string newVal){
		RomanAlphabet = newVal;
	}

	/**
	 * 
	 * @param strCounterCategory
	 */
	public static CounterCategory StringToCounterCategory(string strCounterCategory){
		return null;
	}

}