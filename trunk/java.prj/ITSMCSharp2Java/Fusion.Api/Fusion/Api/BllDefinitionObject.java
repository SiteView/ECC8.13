package Fusion.Api;

import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:31
 */
public abstract class BllDefinitionObject extends DefinitionObject {



	public void finalize() throws Throwable {
		super.finalize();
	}

	public BllDefinitionObject(){

	}

	/**
	 * 
	 * @param fusionObject
	 */
	public BllDefinitionObject(Object fusionObject){

	}

	public boolean CanGenerateEvents(){
		return false;
	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param correction
	 * @param justCollect
	 */
	public void CorrectNamedReference(NamedReferenceCorrection correction, boolean justCollect){

	}

	public Fusion.Api.DbHintManager DbHintManager(){
		return null;
	}

	private Fusion.BusinessLogic.BllDefinitionObject WhoAmI(){
		return null;
	}

	/**
	 * 
	 * @param collDefs
	 */
	protected List WrapAsAggregateCollectionIfRequired(List collDefs){
		return null;
	}

	/**
	 * 
	 * @param iDef
	 */
	protected IDefinition WrapAsAggregateIfRequired(IDefinition iDef){
		return null;
	}

}