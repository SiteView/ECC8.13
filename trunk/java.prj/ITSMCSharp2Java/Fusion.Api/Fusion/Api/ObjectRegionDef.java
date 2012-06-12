package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:08
 */
public class ObjectRegionDef extends RegionDef {

	public ObjectRegionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ObjectRegionDef(Object fusionObject){

	}

	public static String ClassName(){
		return "";
	}

	private Fusion.Presentation.ObjectRegionDef WhoAmI(){
		return null;
	}

}