package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:40
 */
public class SystemExtensions extends AggregateUser {

	private IOrchestrator m_orch = null;
	private String m_PresentationRegionExtension = "PresentationRegionExtension";

	public SystemExtensions(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param orch
	 */
	public SystemExtensions(IOrchestrator orch){

	}

	/**
	 * 
	 * @param purpose
	 * @param busObName
	 * @param name
	 */
	public Object GetBusinessObjectCodeExtension(String purpose, String busObName, String name){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param busObName
	 */
	public List GetBusinessObjectContextPackageDefs(String purpose, String busObName){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param defClassName
	 * @param busObName
	 * @param checkDb
	 * @param secondCall
	 */
	public List GetBusinessObjectSnapIns(String purpose, String defClassName, String busObName, boolean checkDb, boolean secondCall){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param purpose
	 * @param busObName
	 * @param relationship
	 */
	public Object GetCodeExtension(CodeExtensionContextPackageDef def, String purpose, String busObName, String relationship){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param name
	 */
	public Object GetCoreCodeExtension(String purpose, String name){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 */
	public List GetCoreContextPackageDefs(String purpose){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param defClassName
	 * @param checkDb
	 * @param secondCall
	 */
	public List GetCoreSnapIns(String purpose, String defClassName, boolean checkDb, boolean secondCall){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param purpose
	 * @param busObName
	 * @param relationship
	 */
	public Object GetDisplayExtension(DisplayTargetExtensionContextPackageDef def, String purpose, String busObName, String relationship){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param busObName
	 * @param relationship
	 * @param fieldName
	 * @param annotations
	 * @param fldCategory
	 */
	public List GetFieldContextPackageDefs(String purpose, String busObName, String relationship, String fieldName, List annotations, FieldCategory fldCategory){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param defClassName
	 * @param busObName
	 * @param relationship
	 * @param fieldName
	 * @param annotations
	 * @param fldCategory
	 * @param secondCall
	 */
	public List GetFieldSnapIns(String purpose, String defClassName, String busObName, String relationship, String fieldName, List annotations, FieldCategory fldCategory, boolean secondCall){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param item
	 */
	public List GetOtherContextPackageDefs(String purpose, String item){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param defClassName
	 * @param item
	 * @param checkDb
	 * @param secondCall
	 */
	public List GetOtherSnapIns(String purpose, String defClassName, String item, boolean checkDb, boolean secondCall){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param busObName
	 * @param relationship
	 * @param name
	 */
	public Object GetRelatedBusinessObjectCodeExtension(String purpose, String busObName, String relationship, String name){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param busObName
	 * @param relationship
	 */
	public List GetRelatedBusinessObjectContextPackageDefs(String purpose, String busObName, String relationship){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param defClassName
	 * @param busObName
	 * @param relationship
	 * @param checkDb
	 * @param secondCall
	 */
	public List GetRelatedBusinessObjectSnapIns(String purpose, String defClassName, String busObName, String relationship, boolean checkDb, boolean secondCall){
		return null;
	}

	public List GetRolePackageDefs(){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param target
	 */
	public List GetTargetContextPackageDefs(String purpose, String target){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param defClassName
	 * @param target
	 * @param checkDb
	 * @param secondCall
	 */
	public List GetTargetSnapIns(String purpose, String defClassName, String target, boolean checkDb, boolean secondCall){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param busObName
	 */
	public List ListBusinessObjectCodeExtensions(String purpose, String busObName){
		return null;
	}

	public List ListCommandHandlers(){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 */
	public List ListCoreCodeExtensions(String purpose){
		return null;
	}

	/**
	 * 
	 * @param strBusObName
	 * @param strRelationship
	 */
	public List ListDisplayTargetExtensions(String strBusObName, String strRelationship){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param busObName
	 * @param relationship
	 */
	public List ListRelatedBusinessObjectCodeExtensions(String purpose, String busObName, String relationship){
		return null;
	}

	/**
	 * 
	 * @param purpose
	 * @param busObName
	 * @param relationship
	 */
	public List ListRelatedBusinessObjectDisplayTargetExtensions(String purpose, String busObName, String relationship){
		return null;
	}

}