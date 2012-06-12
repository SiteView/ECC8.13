package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:06
 */
public class EvaluationBundle extends FusionAggregate {

	private System.Globalization.CultureInfo m_cultureInfo;
	private Fusion.Api.BusinessObject m_currentBusinessObject;
	private Fusion.Api.Field m_currentField;
	private Object m_notifier;
	private String m_strAssociatedRelationship;
	private UpdateResult m_updateResult;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public EvaluationBundle(){

	}

	/**
	 * 
	 * @param fusionObject
	 */
	public EvaluationBundle(Object fusionObject){

	}

	/**
	 * 
	 * @param busOb
	 * @param fld
	 */
	public EvaluationBundle(Fusion.Api.BusinessObject busOb, Fusion.Api.Field fld){

	}

	/**
	 * 
	 * @param busOb
	 * @param fld
	 * @param ruleReason
	 */
	public EvaluationBundle(Fusion.Api.BusinessObject busOb, Fusion.Api.Field fld, Fusion.Xml.Reason ruleReason){

	}

	/**
	 * 
	 * @param busOb
	 * @param fld
	 * @param strAssociatedRelationship
	 */
	public EvaluationBundle(Fusion.Api.BusinessObject busOb, Fusion.Api.Field fld, String strAssociatedRelationship){

	}

	/**
	 * 
	 * @param busOb
	 * @param fld
	 * @param strAssociatedRelationship
	 * @param ruleReason
	 */
	public EvaluationBundle(Fusion.Api.BusinessObject busOb, Fusion.Api.Field fld, String strAssociatedRelationship, Fusion.Xml.Reason ruleReason){

	}

	/**
	 * 
	 * @param busOb
	 * @param fld
	 * @param notifier
	 * @param updResult
	 * @param strAssociatedRelationship
	 */
	public EvaluationBundle(Fusion.Api.BusinessObject busOb, Fusion.Api.Field fld, Object notifier, UpdateResult updResult, String strAssociatedRelationship){

	}

	/**
	 * 
	 * @param busOb
	 * @param fld
	 * @param notifier
	 * @param updResult
	 * @param strAssociatedRelationship
	 * @param ruleReason
	 */
	public EvaluationBundle(Fusion.Api.BusinessObject busOb, Fusion.Api.Field fld, Object notifier, UpdateResult updResult, String strAssociatedRelationship, Fusion.Xml.Reason ruleReason){

	}

	public String AssociatedRelationship(){
		return "";
	}

	public System.Globalization.CultureInfo CultureInfo(){
		return null;
	}

	public Fusion.Api.BusinessObject CurrentBusinessObject(){
		return null;
	}

	public Fusion.Api.Field CurrentField(){
		return null;
	}

	public Fusion.BusinessLogic.BusinessObject FusionBusinessObject(){
		return null;
	}

	public Fusion.BusinessLogic.Rules.EvaluationBundle FusionEvaluationBundle(){
		return null;
	}

	public Fusion.BusinessLogic.Field FusionField(){
		return null;
	}

	public Object Notifier(){
		return null;
	}

	public Fusion.Xml.Reason Reason(){
		return null;
	}

	public UpdateResult UpdResult(){
		return null;
	}

	private Fusion.BusinessLogic.Rules.EvaluationBundle WhoAmI(){
		return null;
	}

}