package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:16
 */
public abstract class RecordBasedEventDef extends EventDef {

	public RecordBasedEventDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public RecordBasedEventDef(Object fusionObject){

	}

	public String BusObName(){
		return "";
	}

	/**
	 * 
	 * @param library
	 */
	public Fusion.Api.BusinessObjectDef GetBusObDef(Fusion.Api.DefinitionLibrary library){
		return null;
	}

	private Fusion.BusinessLogic.RecordBasedEventDef WhoAmI(){
		return null;
	}

}