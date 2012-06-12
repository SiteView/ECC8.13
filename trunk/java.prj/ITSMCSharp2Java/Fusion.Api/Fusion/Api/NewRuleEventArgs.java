package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:45:06
 */
public class NewRuleEventArgs extends MadDefEventArgs {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:45:06
	 */
	public enum RuleClass {
		NotDefined,
		Expression,
		Condition
	}

	private boolean m_bInLine;
	private RuleCategory m_RuleCategory;
	private RuleClass m_RuleClass;

	public NewRuleEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param api
	 * @param defLib
	 * @param bInline
	 * @param classRule
	 * @param boDef
	 */
	public NewRuleEventArgs(IFusionApi api, DefinitionLibrary defLib, boolean bInline, RuleClass classRule, BusinessObjectDef boDef){

	}

	/**
	 * 
	 * @param api
	 * @param defLib
	 * @param bInline
	 * @param catRule
	 * @param boDef
	 */
	public NewRuleEventArgs(IFusionApi api, DefinitionLibrary defLib, boolean bInline, RuleCategory catRule, BusinessObjectDef boDef){

	}

	public boolean Inline(){
		return null;
	}

	public RuleCategory NewRuleCategory(){
		return null;
	}

	public RuleClass NewRuleClass(){
		return null;
	}

}