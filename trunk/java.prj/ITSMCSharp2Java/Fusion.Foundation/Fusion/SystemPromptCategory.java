package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:28
 */
public class SystemPromptCategory {

	private String DateTimeAdjustFunction = "DateTimeAdjustFunction";
	private String SearchParameter = "SearchParameter";
	private String UserPrompt = "UserPrompt";
	private String ValidatedPrompt = "ValidatedPrompt";
	private String ValidatedSearchParameter = "ValidatedSearchParameter";

	public SystemPromptCategory(){

	}

	public void finalize() throws Throwable {

	}

	public String getDateTimeAdjustFunction(){
		return DateTimeAdjustFunction;
	}

	public String getSearchParameter(){
		return SearchParameter;
	}

	public String getUserPrompt(){
		return UserPrompt;
	}

	public String getValidatedPrompt(){
		return ValidatedPrompt;
	}

	public String getValidatedSearchParameter(){
		return ValidatedSearchParameter;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDateTimeAdjustFunction(String newVal){
		DateTimeAdjustFunction = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSearchParameter(String newVal){
		SearchParameter = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUserPrompt(String newVal){
		UserPrompt = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setValidatedPrompt(String newVal){
		ValidatedPrompt = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setValidatedSearchParameter(String newVal){
		ValidatedSearchParameter = newVal;
	}

}