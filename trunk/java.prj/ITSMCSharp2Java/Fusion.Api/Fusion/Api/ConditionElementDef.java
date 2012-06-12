package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:46
 */
public class ConditionElementDef extends ElementDef {

	public ConditionElementDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ConditionElementDef(Object fusionObject){

	}

	/**
	 * 
	 * @param nPosition
	 * @param defElementNext
	 */
	public void AddPrimayElementDef(int nPosition, Fusion.Api.ElementDef defElementNext){

	}

	/**
	 * 
	 * @param defElementNext
	 */
	public void AddSecondaryElementDef(Fusion.Api.ElementDef defElementNext){

	}

	public boolean CanHaveSecondaryNextElementDef(){
		return null;
	}

	public String ElementItem(){
		return "";
	}

	public Fusion.Api.ElementDef FalseElementDef(){
		return null;
	}

	/**
	 * 
	 * @param defElementNext
	 * @param eLabelPlacement
	 * @param strLabel
	 */
	public void GetConnectionLabel(Fusion.Api.ElementDef defElementNext, LabelPlacement eLabelPlacement, String strLabel){

	}

	/**
	 * 
	 * @param nPosition
	 */
	public Fusion.Api.ElementDef GetPrimaryNextElementDef(int nPosition){
		return null;
	}

	public Fusion.Api.ElementDef GetSecondaryNextElementDef(){
		return null;
	}

	public int PrimaryNextElementDefCount(){
		return 0;
	}

	public Fusion.Api.ReferenceDef QueryGroupDefReference(){
		return null;
	}

	/**
	 * 
	 * @param defElementRemoved
	 * @param defElementReplacement
	 */
	public void ReplaceElementDef(Fusion.Api.ElementDef defElementRemoved, Fusion.Api.ElementDef defElementReplacement){

	}

	public static String SElementItem(){
		return "";
	}

	public Fusion.Api.ElementDef TrueElementDef(){
		return null;
	}

	private Fusion.BusinessLogic.ConditionElementDef WhoAmI(){
		return null;
	}

}