package Fusion.Api;

import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:46:00
 */
public class TriggerElementDef extends ElementDef {

	public TriggerElementDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public TriggerElementDef(Object fusionObject){

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

	public Fusion.Api.ElementDef NextElementDef(){
		return null;
	}

	public int PrimaryNextElementDefCount(){
		return 0;
	}

	/**
	 * 
	 * @param refDef
	 */
	public void Remove(Fusion.Api.ReferenceDef refDef){

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

	private Fusion.BusinessLogic.TriggerElementDef WhoAmI(){
		return null;
	}

}