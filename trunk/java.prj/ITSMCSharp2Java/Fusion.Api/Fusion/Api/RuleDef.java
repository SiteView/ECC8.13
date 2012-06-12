package Fusion.Api;

import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:27
 */
public abstract class RuleDef extends BllDefinitionObject {



	public void finalize() throws Throwable {
		super.finalize();
	}

	public RuleDef(){

	}

	/**
	 * 
	 * @param fusionObject
	 */
	public RuleDef(Object fusionObject){

	}

	public static Fusion.Api.AlwaysNull AlwaysBlank(){
		return null;
	}

	public static Fusion.Api.Alwaysbooleanean AlwaysFalse(){
		return null;
	}

	public static Fusion.Api.AlwaysNull AlwaysNull(){
		return null;
	}

	public static Fusion.Api.Alwaysbooleanean AlwaysTrue(){
		return null;
	}

	public boolean Append(){
		return false;
	}

	public boolean Cascade(){
		return false;
	}

	public String CategoryAsLocalizedString(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param strName
	 */
	public boolean Contains(String strName){
		return false;
	}

	/**
	 * 
	 * @param fusionApi
	 * @param query
	 */
	public static Fusion.Api.RuleDef Create(IFusionApi fusionApi, FusionQuery query){
		return null;
	}

	/**
	 * 
	 * @param fusionApi
	 * @param value
	 */
	public static Fusion.Api.RuleDef Create(IFusionApi fusionApi, String value){
		return null;
	}

	/**
	 * 
	 * @param orch
	 * @param value
	 */
	public static Fusion.Api.RuleDef Create(IBllOrchestrator orch, String value){
		return null;
	}

	/**
	 * 
	 * @param ruleType
	 * @param fusionApi
	 */
	public static Fusion.Api.RuleDef Create(RuleCategory ruleType, IFusionApi fusionApi){
		return null;
	}

	public String DefToBriefString(){
		return "";
	}

	/**
	 * 
	 * @param evalBundle
	 */
	public FusionValue EvaluateToFusionValue(Fusion.Api.EvaluationBundle evalBundle){
		return null;
	}

	/**
	 * 
	 * @param evalBundle
	 */
	public boolean EvaluateToLogical(Fusion.Api.EvaluationBundle evalBundle){
		return false;
	}

	/**
	 * 
	 * @param evalBundle
	 */
	public String EvaluateToString(Fusion.Api.EvaluationBundle evalBundle){
		return "";
	}

	public static Fusion.Api.GuidRule GenerateGuid(){
		return null;
	}

	/**
	 * 
	 * @param defLib
	 * @param ruleCat
	 */
	public static Fusion.Api.RuleDef GetNewRuleDefForEditing(Fusion.Api.DefinitionLibrary defLib, RuleCategory ruleCat){
		return null;
	}

	/**
	 * 
	 * @param defLib
	 */
	public static List GetPlaceHoldersForNamedRules(Fusion.Api.DefinitionLibrary defLib){
		return null;
	}

	/**
	 * 
	 * @param cat
	 */
	public Fusion.Api.RuleDef GetRuleDefByCategory(RuleCategory cat){
		return null;
	}

	/**
	 * 
	 * @param defLib
	 * @param strRuleID
	 */
	public static Fusion.Api.RuleDef GetRuleDefForEditing(Fusion.Api.DefinitionLibrary defLib, String strRuleID){
		return null;
	}

	/**
	 * 
	 * @param defLib
	 * @param ruleDef
	 */
	public static Fusion.Api.RuleDef GetRuleDefFromRuleDef(Fusion.Api.DefinitionLibrary defLib, Fusion.Api.RuleDef ruleDef){
		return null;
	}

	/**
	 * 
	 * @param defLib
	 * @param ruleDef
	 */
	public static Fusion.Api.RuleDef GetRuleToEdit(Fusion.Api.DefinitionLibrary defLib, Fusion.Api.RuleDef ruleDef){
		return null;
	}

	/**
	 * 
	 * @param strFunction
	 */
	public Fusion.Api.RuleDef GetSystemFunction(String strFunction){
		return null;
	}

	/**
	 * 
	 * @param fusionApi
	 * @param strFunction
	 */
	public static Fusion.Api.RuleDef GetSystemFunction(IFusionApi fusionApi, String strFunction){
		return null;
	}

	public boolean IsInLine(){
		return false;
	}

	public boolean IsInstant(){
		return false;
	}

	public String Key(){
		return "";
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.RuleDef Lookup(String strName){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.RuleDef LookupExact(String strName){
		return null;
	}

	public String Purpose(){
		return "";
	}

	public String RelFor(){
		return "";
	}

	public String RelWhich(){
		return "";
	}

	/**
	 * 
	 * @param rule
	 */
	public static boolean RuleNotNull(Fusion.Api.RuleDef rule){
		return false;
	}

	public RuleCategory RuleType(){
		return null;
	}

	public String ValueFromAsString(){
		return "";
	}

	public ValueFrom ValueType(){
		return null;
	}

	private Fusion.BusinessLogic.Rules.RuleDef WhoAmI(){
		return null;
	}

}