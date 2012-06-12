package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:16
 */
public class RegionDef extends BllDefinitionObject {

	public RegionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public RegionDef(Object fusionObject){

	}

	public String AllowedDisplays(){
		return "";
	}

	public Fusion.Categories.Region.Category Category(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param parentRegion
	 * @param cat
	 */
	public static Fusion.Api.RegionDef CreateForEdit(Fusion.Api.RegionDef parentRegion, Fusion.Categories.Region.Category cat){
		return null;
	}

	public String DefaultDisplay(){
		return "";
	}

	public Fusion.Api.RegionDef ParentRegion(){
		return null;
	}

	private Fusion.Presentation.RegionDef WhoAmI(){
		return null;
	}

}