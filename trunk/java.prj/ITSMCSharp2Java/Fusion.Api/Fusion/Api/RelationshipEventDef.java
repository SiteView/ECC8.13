package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:21
 */
public class RelationshipEventDef extends RecordBasedEventDef {

	public RelationshipEventDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public RelationshipEventDef(Object fusionObject){

	}

	public String EventItem(){
		return "";
	}

	public RelationshipEventDefEventTypes EventType(){
		return null;
	}

	public Fusion.Api.FieldEventDef FieldEventDef(){
		return null;
	}

	/**
	 * 
	 * @param library
	 */
	public Fusion.Api.RelationshipDef GetRelationshipDef(Fusion.Api.DefinitionLibrary library){
		return null;
	}

	/**
	 * 
	 * @param library
	 */
	public Fusion.Api.BusinessObjectDef GetTargetBusObDef(Fusion.Api.DefinitionLibrary library){
		return null;
	}

	public String GroupObject(){
		return "";
	}

	public String RelationshipName(){
		return "";
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

	private Fusion.BusinessLogic.RelationshipEventDef WhoAmI(){
		return null;
	}

}