package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:49
 */
public class ControlWithActionDef extends ControlDef implements IControlAction {

	public ControlWithActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ControlWithActionDef(Object fusionObject){

	}

	public String Action(){
		return "";
	}

	public String ActionCategory(){
		return "";
	}

	public Hashtable ActionParameters(){
		return null;
	}

	/**
	 * 
	 * @param strParameterName
	 * @param rule
	 */
	public void AddParameter(String strParameterName, Fusion.Api.RuleDef rule){

	}

	public String AlternateText(){
		return "";
	}

	public Fusion.Api.RuleDef AlternateTextRule(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public IControlAction ControlActions(){
		return null;
	}

	/**
	 * 
	 * @param strParameterName
	 */
	public Fusion.Api.RuleDef GetParameter(String strParameterName){
		return null;
	}

	public String GuardBehavior(){
		return "";
	}

	public String GuardMessageText(){
		return "";
	}

	public Fusion.Api.RuleDef GuardRule(){
		return null;
	}

	public int MinimumParameters(){
		return 0;
	}

	public boolean OpenInNewWindow(){
		return null;
	}

	public int ParameterCount(){
		return 0;
	}

	public void RemoveAllParameters(){

	}

	/**
	 * 
	 * @param strParameterName
	 */
	public void RemoveParameter(String strParameterName){

	}

	/**
	 * 
	 * @param strParameterName
	 * @param rule
	 */
	public void SetParameter(String strParameterName, Fusion.Api.RuleDef rule){

	}

	private Fusion.Presentation.ControlWithActionDef WhoAmI(){
		return null;
	}

}