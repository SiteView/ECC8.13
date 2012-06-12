package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:26
 */
public class RollUpLevel extends FusionAggregate {

	public RollUpLevel(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionApi
	 */
	public RollUpLevel(IFusionApi fusionApi){

	}

	/**
	 * 
	 * @param fusionObject
	 */
	public RollUpLevel(Object fusionObject){

	}

	public String ChildRelationshipId(){
		return "";
	}

	public String ChildRelationshipName(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public EventHandler DefinitionChanged(){
		return null;
	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnDefChanged(Object sender, EventArgs e){

	}

	public String ParentRelationshipId(){
		return "";
	}

	public String ParentRelationshipName(){
		return "";
	}

	private Fusion.BusinessLogic.RollUpLevel WhoAmI(){
		return null;
	}

}