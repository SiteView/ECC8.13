package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:43
 */
public class ColumnDef extends BllDefinitionObject {

	public ColumnDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ColumnDef(Object fusionObject){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param defParentGrid
	 */
	public ColumnDef(IFusionApi fusionApi, Fusion.Api.GridDef defParentGrid){

	}

	public String Alias(){
		return "";
	}

	public String Alignment(){
		return "";
	}

	public Fusion.Api.RuleDef CellBackColorRule(){
		return null;
	}

	public Fusion.Api.RuleDef CellBorderColorRule(){
		return null;
	}

	public Fusion.Api.RuleDef CellImageRule(){
		return null;
	}

	public Fusion.Api.RuleDef CellTextColorRule(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public String Name(){
		return "";
	}

	public String QualifiedName(){
		return "";
	}

	public HorizontalAlignment TextAlignment(){
		return null;
	}

	private Fusion.Presentation.ColumnDef WhoAmI(){
		return null;
	}

	public int Width(){
		return 0;
	}

}