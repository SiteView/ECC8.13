package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:05
 */
public abstract class ElementDef extends DefinitionObject {

	public ElementDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ElementDef(Object fusionObject){

	}

	/**
	 * 
	 * @param nPosition
	 * @param defElementNext
	 */
	public abstract void AddPrimayElementDef(int nPosition, Fusion.Api.ElementDef defElementNext);

	/**
	 * 
	 * @param defElementNext
	 */
	public abstract void AddSecondaryElementDef(Fusion.Api.ElementDef defElementNext);

	public abstract boolean CanHaveSecondaryNextElementDef();

	public static String ClassName(){
		return "";
	}

	public abstract String ElementItem();

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
	public abstract Fusion.Api.ElementDef GetPrimaryNextElementDef(int nPosition);

	public abstract Fusion.Api.ElementDef GetSecondaryNextElementDef();

	public Fusion.Api.ElementDef PreviousElementDef(){
		return null;
	}

	public abstract int PrimaryNextElementDefCount();

	public void RemoveElementDef(){

	}

	/**
	 * 
	 * @param defElementRemoved
	 * @param defElementReplacement
	 */
	public abstract void ReplaceElementDef(Fusion.Api.ElementDef defElementRemoved, Fusion.Api.ElementDef defElementReplacement);

	private Fusion.BusinessLogic.ElementDef WhoAmI(){
		return null;
	}

}