package Fusion.Api;

import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:09
 */
public class PerspectiveDef extends BllDefinitionObject {

	public PerspectiveDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public PerspectiveDef(Object fusionObject){

	}

	/**
	 * 
	 * @param voi
	 */
	public int AddOverride(IViewOverrideInfo voi){
		return 0;
	}

	public static String ClassName(){
		return "";
	}

	public String Culture(){
		return "";
	}

	public ViewBehavior DefaultBehavior(){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strName
	 */
	public IViewOverrideInfo GetViewForDefinition(String strType, String strName){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strId
	 */
	public IViewOverrideInfo GetViewForDefinitionById(String strType, String strId){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strName
	 * @param strPerspective
	 * @param behavior
	 */
	public void GetViewInfoForDefinition(String strType, String strName, String strPerspective, ViewBehavior behavior){

	}

	/**
	 * 
	 * @param strType
	 * @param strId
	 * @param strPerspective
	 * @param behavior
	 */
	public void GetViewInfoForDefinitionById(String strType, String strId, String strPerspective, ViewBehavior behavior){

	}

	/**
	 * 
	 * @param strType
	 */
	public List GetViewsForDefinitionType(String strType){
		return null;
	}

	public List OverriddenViewCollection(){
		return null;
	}

	public void RemoveAllOverrides(){

	}

	/**
	 * 
	 * @param voi
	 */
	public void RemoveOverride(IViewOverrideInfo voi){

	}

	public TargetMedium Target(){
		return null;
	}

	private Fusion.BusinessLogic.PerspectiveDef WhoAmI(){
		return null;
	}

}