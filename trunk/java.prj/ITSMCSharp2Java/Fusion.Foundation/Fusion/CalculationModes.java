package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:47
 */
public class CalculationModes {

	private String FalseValue = "FALSE";
	private String IfEmpty = "IFEMPTY";
	private String TrueValue = "TRUE";

	public CalculationModes(){

	}

	public void finalize() throws Throwable {

	}

	public String getFalseValue(){
		return FalseValue;
	}

	public String getIfEmpty(){
		return IfEmpty;
	}

	public String getTrueValue(){
		return TrueValue;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFalseValue(String newVal){
		FalseValue = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setIfEmpty(String newVal){
		IfEmpty = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTrueValue(String newVal){
		TrueValue = newVal;
	}

}