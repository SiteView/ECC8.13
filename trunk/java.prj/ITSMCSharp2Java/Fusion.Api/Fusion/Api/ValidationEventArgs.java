package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:46:01
 */
public class ValidationEventArgs extends FusionAggregate {

	public ValidationEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ValidationEventArgs(Object fusionObject){

	}

	/**
	 * 
	 * @param fld
	 * @param rule
	 */
	public ValidationEventArgs(Fusion.Api.Field fld, Fusion.Api.RuleDef rule){

	}

	public Fusion.Api.BusinessObject BusOb(){
		return null;
	}

	public Fusion.Api.BusinessObject CloseMatch(){
		return null;
	}

	public Fusion.Api.Field Field(){
		return null;
	}

	public boolean Helpful(){
		return null;
	}

	public boolean IsCombo(){
		return null;
	}

	public boolean MultipleRecords(){
		return null;
	}

	public Fusion.Api.RuleDef Rule(){
		return null;
	}

	public boolean TryAgain(){
		return null;
	}

	public Fusion.UpdateResult UpdateResult(){
		return null;
	}

	public FusionValue Value(){
		return null;
	}

	public String ValueRecId(){
		return "";
	}

	private Fusion.BusinessLogic.ValidationEventArgs WhoAmI(){
		return null;
	}

}