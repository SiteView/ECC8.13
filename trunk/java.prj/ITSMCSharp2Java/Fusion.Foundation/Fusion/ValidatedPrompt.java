package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:50
 */
public class ValidatedPrompt extends SystemPromptDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:50
	 */
	public class ParameterName extends ParameterName {

		private String DefaultRecId = "DefaultRecId";
		private String ValidateBusOb = "ValidateBusOb";
		private String ValidateField = "ValidateField";

		public ParameterName(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		public String getDefaultRecId(){
			return DefaultRecId;
		}

		public String getValidateBusOb(){
			return ValidateBusOb;
		}

		public String getValidateField(){
			return ValidateField;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDefaultRecId(String newVal){
			DefaultRecId = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValidateBusOb(String newVal){
			ValidateBusOb = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValidateField(String newVal){
			ValidateField = newVal;
		}

	}

	private String ValidatedPromptDef = "ValidatedPrompt";

	public ValidatedPrompt(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String BusOb(){
		return "";
	}

	public String Category(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public String DefaultRecId(){
		return "";
	}

	public String Field(){
		return "";
	}

	public String getValidatedPromptDef(){
		return ValidatedPromptDef;
	}

	public static String PromptDisplayName(){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setValidatedPromptDef(String newVal){
		ValidatedPromptDef = newVal;
	}

}