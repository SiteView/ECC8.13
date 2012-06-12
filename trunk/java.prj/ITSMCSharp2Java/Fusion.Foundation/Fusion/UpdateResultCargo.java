package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:46
 */
public class UpdateResultCargo {

	private String CancelRelationshipSetCurrentObject = "CancelRelationshipSetCurrentObject";
	private String CancelSaveOperation = "CancelSaveOperation";
	private String EnforceLastestRecordInCache = "EnforceLastestRecordInCache";
	private String SupressInteractiveValidation = "SupressInteractiveValidation";
	private String ValidationRecId = "ValidationRecId";
	private String ValidationUseFirstValue = "ValidationUseFirstValue";

	public UpdateResultCargo(){

	}

	public void finalize() throws Throwable {

	}

	public String getCancelRelationshipSetCurrentObject(){
		return CancelRelationshipSetCurrentObject;
	}

	public String getCancelSaveOperation(){
		return CancelSaveOperation;
	}

	public String getEnforceLastestRecordInCache(){
		return EnforceLastestRecordInCache;
	}

	public String getSupressInteractiveValidation(){
		return SupressInteractiveValidation;
	}

	public String getValidationRecId(){
		return ValidationRecId;
	}

	public String getValidationUseFirstValue(){
		return ValidationUseFirstValue;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCancelRelationshipSetCurrentObject(String newVal){
		CancelRelationshipSetCurrentObject = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCancelSaveOperation(String newVal){
		CancelSaveOperation = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEnforceLastestRecordInCache(String newVal){
		EnforceLastestRecordInCache = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSupressInteractiveValidation(String newVal){
		SupressInteractiveValidation = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setValidationRecId(String newVal){
		ValidationRecId = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setValidationUseFirstValue(String newVal){
		ValidationUseFirstValue = newVal;
	}

}