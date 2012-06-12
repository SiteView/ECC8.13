package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:04
 */
public class SearchParameter extends UserPrompt implements ISearchParameter {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:04
	 */
	public class ParameterName extends ParameterName {

		private String ParameterValue = "ParameterValue";

		public ParameterName(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		public String getParameterValue(){
			return ParameterValue;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParameterValue(String newVal){
			ParameterValue = newVal;
		}

	}

	private String SearchParameterDef = "SearchParameter";

	public SearchParameter(){

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

	public boolean EditMode(){
		return null;
	}

	public String getSearchParameterDef(){
		return SearchParameterDef;
	}

	public String SearchParameterCategoryType(){
		return "";
	}

	public Object SearchParameterDefaultValue(){
		return null;
	}

	public static String SearchParameterDisplayName(){
		return "";
	}

	public String SearchParameterId(){
		return "";
	}

	public String SearchParameterName(){
		return "";
	}

	public String SearchParameterType(){
		return "";
	}

	public String SearchParameterUIMessage(){
		return "";
	}

	public Object SearchParameterValue(){
		return null;
	}

	public String SerializeClassName(){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSearchParameterDef(String newVal){
		SearchParameterDef = newVal;
	}

	public String ToXml(){
		return "";
	}

	public Object Value(){
		return null;
	}

}