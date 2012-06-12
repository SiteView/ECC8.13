package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:04
 */
public class EditFieldDefEventArgs extends MadDefEventArgs {

	public EditFieldDefEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param api
	 * @param defLib
	 * @param busObDef
	 * @param defField
	 */
	public EditFieldDefEventArgs(IFusionApi api, DefinitionLibrary defLib, BusinessObjectDef busObDef, FieldDef defField){

	}

	public FieldDef HeldFieldDef(){
		return null;
	}

}