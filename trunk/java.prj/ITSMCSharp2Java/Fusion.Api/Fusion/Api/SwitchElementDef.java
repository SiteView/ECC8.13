package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:40
 */
public class SwitchElementDef extends ElementDef {

	public SwitchElementDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public SwitchElementDef(Object fusionObject){

	}

	/**
	 * 
	 * @param elmDef
	 */
	public void Add(Fusion.Api.ElementDef elmDef){

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

	public void Clear(){

	}

	public String ElementItem(){
		return "";
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

	public List NextElementDefs(){
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

	private Fusion.BusinessLogic.SwitchElementDef WhoAmI(){
		return null;
	}

}