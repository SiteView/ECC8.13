package Fusion.Api;

import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:24
 */
public class RoleDef extends BllDefinitionObject {

	public RoleDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public RoleDef(Object fusionObject){

	}

	/**
	 * 
	 * @param sExtMod
	 */
	public int AddExtension(String sExtMod){
		return 0;
	}

	public boolean AddNewModules(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public static Fusion.Api.RoleDef CoreRole(){
		return null;
	}

	public String DefaultWorkspace(){
		return "";
	}

	public List ExtensionModules(){
		return null;
	}

	public ArrayList LicenseList(){
		return null;
	}

	public void RemoveAllExtensions(){

	}

	/**
	 * 
	 * @param sExt
	 */
	public void RemoveExtension(String sExt){

	}

	public String WebPerspective(){
		return "";
	}

	private Fusion.BusinessLogic.RoleDef WhoAmI(){
		return null;
	}

	public String WinPerspective(){
		return "";
	}

	public ArrayList WorkspaceList(){
		return null;
	}

}