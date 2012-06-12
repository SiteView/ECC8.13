package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:35
 */
public class TagFormatItems {

	private String DateTime = "DateTime";
	private String Prompt = "Prompt";
	private String String = "String";

	public TagFormatItems(){

	}

	public void finalize() throws Throwable {

	}

	public String getDateTime(){
		return DateTime;
	}

	public String getPrompt(){
		return Prompt;
	}

	public String getString(){
		return String;
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
	public void setPrompt(String newVal){
		Prompt = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setString(String newVal){
		String = newVal;
	}

}