package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:04
 */
public class SearchParameterCategory {

	private String SearchParameter = "SearchParameter";
	private String ValidatedSearchParameter = "ValidatedSearchParameter";

	public SearchParameterCategory(){

	}

	public void finalize() throws Throwable {

	}

	public String getSearchParameter(){
		return SearchParameter;
	}

	public String getValidatedSearchParameter(){
		return ValidatedSearchParameter;
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
	public void setValidatedSearchParameter(String newVal){
		ValidatedSearchParameter = newVal;
	}

}