package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:45
 */
public class Condition extends FusionAggregate {

	public Condition(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionApi
	 */
	public Condition(IFusionApi fusionApi){

	}

	/**
	 * 
	 * @param fusionObject
	 */
	public Condition(Object fusionObject){

	}

	public Fusion.Api.RuleDef Case(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public EventHandler DefinitionChanged(){
		return null;
	}

	public String DefToBriefString(){
		return "";
	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnDefChanged(Object sender, EventArgs e){

	}

	public ValueSource Value(){
		return null;
	}

	private Fusion.BusinessLogic.Rules.Condition WhoAmI(){
		return null;
	}

}