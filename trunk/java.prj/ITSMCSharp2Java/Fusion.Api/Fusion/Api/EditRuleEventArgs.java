package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:04
 */
public class EditRuleEventArgs extends MadDefEventArgs {

	public EditRuleEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param api
	 * @param defLib
	 * @param busObDef
	 * @param ruleDef
	 */
	public EditRuleEventArgs(IFusionApi api, DefinitionLibrary defLib, BusinessObjectDef busObDef, RuleDef ruleDef){

	}

	public RuleDef HeldRuleDef(){
		return null;
	}

}