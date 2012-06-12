package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:48
 */
public class UserPrompt extends SystemPromptDef {

	private String UserPromptDef = "UserPrompt";

	public UserPrompt(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String Category(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public String getUserPromptDef(){
		return UserPromptDef;
	}

	public static String PromptDisplayName(){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUserPromptDef(String newVal){
		UserPromptDef = newVal;
	}

}