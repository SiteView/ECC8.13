package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:46:09
 */
public class WaitEventElementDef extends ElementDef {

	public WaitEventElementDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public WaitEventElementDef(Object fusionObject){

	}

	/**
	 * 
	 * @param refDef
	 */
	public void Add(Fusion.Api.ReferenceDef refDef){

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
		return false;
	}

	public void Clear(){

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

	public List TriggerReferenceDefs(){
		return null;
	}

	public Fusion.Api.ElementDef TrueElementDef(){
		return null;
	}

	private Fusion.BusinessLogic.WaitEventElementDef WhoAmI(){
		return null;
	}

}