package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:16
 */
public class ReferenceDef extends DefinitionObject {

	public ReferenceDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ReferenceDef(Object fusionObject){

	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param correction
	 * @param bJustCollect
	 */
	public void CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect){

	}

	public String DefClassName(){
		return "";
	}

	public String DefId(){
		return "";
	}

	public String DefLinkedTo(){
		return "";
	}

	public String DefOwner(){
		return "";
	}

	public Scope DefScope(){
		return null;
	}

	/**
	 * 
	 * @param library
	 */
	public Fusion.Api.DefinitionObject GetDefinition(Fusion.Api.DefinitionLibrary library){
		return null;
	}

	/**
	 * 
	 * @param ph
	 */
	public void SetFromPlaceHolder(PlaceHolder ph){

	}

	/**
	 * 
	 * @param library
	 */
	public String ToString(Fusion.Api.DefinitionLibrary library){
		return "";
	}

	private Fusion.BusinessLogic.ReferenceDef WhoAmI(){
		return null;
	}

}