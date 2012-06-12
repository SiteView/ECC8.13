package Fusion.Api.FusionUpgrade;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:46:01
 */
public class ValidateMessageArgs extends EventArgs {

	private IValidateDefinition m_valDef;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public ValidateMessageArgs(){

	}

	/**
	 * 
	 * @param valDef
	 */
	public ValidateMessageArgs(IValidateDefinition valDef){

	}

	public IValidateDefinition ValidateDefinition(){
		return null;
	}

}