package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:23
 */
public class AlwaysNull extends RuleDef {

	public AlwaysNull(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public AlwaysNull(Object fusionObject){

	}

	public static String ClassName(){
		return "";
	}

	public String DefToBriefString(){
		return "";
	}

	public Object Value(){
		return null;
	}

	private Fusion.BusinessLogic.Rules.AlwaysNull WhoAmI(){
		return null;
	}

}

