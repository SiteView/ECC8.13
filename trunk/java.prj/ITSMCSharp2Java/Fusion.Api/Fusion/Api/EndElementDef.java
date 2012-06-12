package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:05
 */
public class EndElementDef extends ElementDef {

	public EndElementDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public EndElementDef(Object fusionObject){

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

	public String ElementItem(){
		return "";
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

	private Fusion.BusinessLogic.EndElementDef WhoAmI(){
		return null;
	}

}