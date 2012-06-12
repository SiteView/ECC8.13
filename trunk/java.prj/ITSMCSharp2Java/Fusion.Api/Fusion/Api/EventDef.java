package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:06
 */
public abstract class EventDef extends DefinitionObject {

	public EventDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public EventDef(Object fusionObject){

	}

	public static String ClassName(){
		return "";
	}

	public abstract String EventItem();

	/**
	 * 
	 * @param library
	 */
	public abstract String ToString(Fusion.Api.DefinitionLibrary library);

	private Fusion.BusinessLogic.EventDef WhoAmI(){
		return null;
	}

}