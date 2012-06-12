package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:29
 */
public class FieldEventDef extends RecordBasedEventDef {

	public FieldEventDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public FieldEventDef(Object fusionObject){

	}

	public String EventItem(){
		return "";
	}

	public FieldEventDefEventTypes EventType(){
		return null;
	}

	public String FieldName(){
		return "";
	}

	public String FromValue(){
		return "";
	}

	/**
	 * 
	 * @param library
	 */
	public Fusion.Api.FieldDef GetFieldDef(Fusion.Api.DefinitionLibrary library){
		return null;
	}

	public static String SEventItem(){
		return "";
	}

	/**
	 * 
	 * @param library
	 */
	public String ToString(Fusion.Api.DefinitionLibrary library){
		return "";
	}

	public String ToValue(){
		return "";
	}

	private Fusion.BusinessLogic.FieldEventDef WhoAmI(){
		return null;
	}

}