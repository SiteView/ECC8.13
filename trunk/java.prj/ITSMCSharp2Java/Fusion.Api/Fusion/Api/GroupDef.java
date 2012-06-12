package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:44
 */
public class GroupDef extends FusionAggregate {

	public GroupDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public GroupDef(Object fusionObject){

	}

	public String Category(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public EventHandler DefinitionChanged(){
		return null;
	}

	public String GroupId(){
		return "";
	}

	public String GroupName(){
		return "";
	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnDefChanged(Object sender, EventArgs e){

	}

	private Fusion.Presentation.GroupDef WhoAmI(){
		return null;
	}

}