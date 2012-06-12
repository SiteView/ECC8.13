package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:00
 */
public abstract class MadDefEventArgs extends EventArgs {

	private BusinessObjectDef m_BoDef;
	private Object m_Cargo;
	private IDefinition m_Def;
	private FieldDef m_FieldDef;
	private DefinitionLibrary m_HeldDefinitionLibrary;
	private IFusionApi m_HeldFusionApi;

	public MadDefEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param api
	 * @param defLib
	 */
	public MadDefEventArgs(IFusionApi api, DefinitionLibrary defLib){

	}

	/**
	 * 
	 * @param api
	 * @param defLib
	 * @param boDef
	 */
	public MadDefEventArgs(IFusionApi api, DefinitionLibrary defLib, BusinessObjectDef boDef){

	}

	/**
	 * 
	 * @param api
	 * @param defLib
	 * @param defField
	 */
	public MadDefEventArgs(IFusionApi api, DefinitionLibrary defLib, FieldDef defField){

	}

	/**
	 * 
	 * @param api
	 * @param defLib
	 * @param def
	 */
	public MadDefEventArgs(IFusionApi api, DefinitionLibrary defLib, IDefinition def){

	}

	/**
	 * 
	 * @param api
	 * @param defLib
	 * @param boDef
	 * @param defField
	 */
	public MadDefEventArgs(IFusionApi api, DefinitionLibrary defLib, BusinessObjectDef boDef, FieldDef defField){

	}

	/**
	 * 
	 * @param api
	 * @param defLib
	 * @param boDef
	 * @param def
	 */
	public MadDefEventArgs(IFusionApi api, DefinitionLibrary defLib, BusinessObjectDef boDef, IDefinition def){

	}

	/**
	 * 
	 * @param api
	 * @param defLib
	 * @param boDef
	 * @param defField
	 * @param def
	 */
	public MadDefEventArgs(IFusionApi api, DefinitionLibrary defLib, BusinessObjectDef boDef, FieldDef defField, IDefinition def){

	}

	public Object Cargo(){
		return null;
	}

	public BusinessObjectDef HeldBusinessObjectDef(){
		return null;
	}

	public IDefinition HeldDefinition(){
		return null;
	}

	public DefinitionLibrary HeldDefinitionLibrary(){
		return null;
	}

	public FieldDef HeldFieldDef(){
		return null;
	}

	public IFusionApi HeldFusionApi(){
		return null;
	}

}