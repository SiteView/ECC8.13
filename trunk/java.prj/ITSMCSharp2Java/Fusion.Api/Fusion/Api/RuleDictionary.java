package Fusion.Api;

import java.util.Hashtable;
import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:45:28
 */
public class RuleDictionary {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:45:28
	 */
	private class Tags {

		private String Function = "FUNCTION";
		private String Literal = "LITERAL";
		private String Rule = "RULE";
		private String RuleList = "RuleList";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getFunction(){
			return Function;
		}

		public String getLiteral(){
			return Literal;
		}

		public String getRule(){
			return Rule;
		}

		public String getRuleList(){
			return RuleList;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFunction(String newVal){
			Function = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLiteral(String newVal){
			Literal = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRule(String newVal){
			Rule = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRuleList(String newVal){
			RuleList = newVal;
		}

	}

	private static CaseInsensitiveComparer comparer = new CaseInsensitiveComparer();
	private static CaseInsensitiveHashCodeProvider hashProvider = new CaseInsensitiveHashCodeProvider();
	private IBllOrchestrator m_bllOrch = null;
	private Hashtable m_dictRules = new Hashtable(hashProvider, comparer);

	public RuleDictionary(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param purpose
	 * @param rule
	 */
	public void AddRule(String purpose, Fusion.Api.RuleDef rule){

	}

	/**
	 * 
	 * @param value
	 */
	public Fusion.Api.RuleDef CreateRule(String value){
		return null;
	}

	/**
	 * 
	 * @param serial
	 * @param parentDef
	 */
	public void DeserializeRuleList(DefSerializer serial, SerializableDef parentDef){

	}

	/**
	 * 
	 * @param purpose
	 * @param serial
	 * @param property
	 */
	public Fusion.Api.RuleDef GetGeneralRule(String purpose, DefSerializer serial, String property){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param serial
	 * @param property
	 * @param value
	 */
	public Fusion.Api.RuleDef GetGeneralRule(String purpose, DefSerializer serial, String property, String value){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 */
	public Fusion.Api.RuleDef GetRule(String purpose){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param serial
	 * @param property
	 * @param isGeneral
	 */
	private Fusion.BusinessLogic.Rules.RuleDef GetRuleImpl(String purpose, DefSerializer serial, String property, boolean isGeneral){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param serial
	 * @param property
	 * @param isGeneral
	 * @param value
	 */
	private Fusion.BusinessLogic.Rules.RuleDef GetRuleImpl(String purpose, DefSerializer serial, String property, boolean isGeneral, String value){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param serial
	 * @param property
	 */
	public Fusion.Api.RuleDef GetSpecificRule(String purpose, DefSerializer serial, String property){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param serial
	 * @param property
	 * @param value
	 */
	public Fusion.Api.RuleDef GetSpecificRule(String purpose, DefSerializer serial, String property, String value){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 */
	public boolean HasRule(String purpose){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 */
	public void RemoveRule(String purpose){

	}

	public Map Rules(){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public void SerializeRuleList(DefSerializer serial){

	}

	/**
	 * 
	 * @param purpose
	 * @param rule
	 */
	public void UpdateRule(String purpose, Fusion.Api.RuleDef rule){

	}

	/**
	 * 
	 * @param rule
	 * @param serial
	 * @param property
	 */
	public void WriteGeneralInstantValueRule(Fusion.Api.RuleDef rule, DefSerializer serial, String property){

	}

	/**
	 * 
	 * @param rule
	 * @param value
	 * @param serial
	 * @param property
	 */
	public void WriteGeneralInstantValueRule(Fusion.Api.RuleDef rule, String value, DefSerializer serial, String property){

	}

	/**
	 * 
	 * @param rule
	 * @param serial
	 * @param property
	 * @param isGeneral
	 */
	private void WriteInstantValueRuleImpl(Fusion.Api.RuleDef rule, DefSerializer serial, String property, boolean isGeneral){

	}

	/**
	 * 
	 * @param rule
	 * @param value
	 * @param serial
	 * @param property
	 * @param isGeneral
	 */
	private void WriteInstantValueRuleImpl(Fusion.Api.RuleDef rule, String value, DefSerializer serial, String property, boolean isGeneral){

	}

	/**
	 * 
	 * @param rule
	 * @param serial
	 * @param property
	 */
	public void WriteSpecificInstantValueRule(Fusion.Api.RuleDef rule, DefSerializer serial, String property){

	}

	/**
	 * 
	 * @param rule
	 * @param value
	 * @param serial
	 * @param property
	 */
	public void WriteSpecificInstantValueRule(Fusion.Api.RuleDef rule, String value, DefSerializer serial, String property){

	}

}