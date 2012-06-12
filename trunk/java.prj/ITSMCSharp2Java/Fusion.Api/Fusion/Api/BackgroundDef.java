package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:30
 */
public class BackgroundDef extends BllDefinitionObject {

	public BackgroundDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public BackgroundDef(Object fusionObject){

	}

	public Fusion.Api.ImageDef BackgroundImage(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public Fusion.Api.RuleDef FirstColorRule(){
		return null;
	}

	public String FirstLiteralColor(){
		return "";
	}

	public boolean IsGradientColor(){
		return null;
	}

	public boolean IsLeftToRightGradient(){
		return null;
	}

	public boolean IsSolidColor(){
		return null;
	}

	public boolean IsTopToBottomGradient(){
		return null;
	}

	public Fusion.Api.RuleDef SecondColorRule(){
		return null;
	}

	public String SecondLiteralColor(){
		return "";
	}

	private Fusion.Presentation.BackgroundDef WhoAmI(){
		return null;
	}

}