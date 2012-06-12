package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:24
 */
public class FieldPurposeValues {

	private String AutoFill = "AutoFill";
	private String BeforeSave = "BeforeSave";
	private String BeforeStateChange = "BeforeStateChange";
	private String Calculation = "Calculation";
	private String DefaultValue = "DefaultValue";
	private String ReadOnly = "ReadOnly";
	private String Required = "Required";
	private String Validation = "Validation";

	public FieldPurposeValues(){

	}

	public void finalize() throws Throwable {

	}

	public String getAutoFill(){
		return AutoFill;
	}

	public String getBeforeSave(){
		return BeforeSave;
	}

	public String getBeforeStateChange(){
		return BeforeStateChange;
	}

	public String getCalculation(){
		return Calculation;
	}

	public String getDefaultValue(){
		return DefaultValue;
	}

	public String getReadOnly(){
		return ReadOnly;
	}

	public String getRequired(){
		return Required;
	}

	public String getValidation(){
		return Validation;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAutoFill(String newVal){
		AutoFill = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBeforeSave(String newVal){
		BeforeSave = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBeforeStateChange(String newVal){
		BeforeStateChange = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCalculation(String newVal){
		Calculation = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDefaultValue(String newVal){
		DefaultValue = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setReadOnly(String newVal){
		ReadOnly = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRequired(String newVal){
		Required = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setValidation(String newVal){
		Validation = newVal;
	}

}