package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:47
 */
public class ConstraintDef extends FusionAggregate {

	public ConstraintDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionApi
	 */
	public ConstraintDef(IFusionApi fusionApi){

	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ConstraintDef(Object fusionObject){

	}

	/**
	 * 
	 * @param collConstraints
	 * @param query
	 * @param busObCurrent
	 * @param strTarget
	 */
	public static XmlElement BuildConstraintsForQuery(List collConstraints, FusionQuery query, Fusion.Api.BusinessObject busObCurrent, String strTarget){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public boolean ConstrainedEnforced(){
		return null;
	}

	public Operator ConstraintOperator(){
		return null;
	}

	public EventHandler DefinitionChanged(){
		return null;
	}

	public String EnglishOperator(){
		return "";
	}

	public String Field(){
		return "";
	}

	public ValueSources FieldCategory(){
		return null;
	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnDefChanged(Object sender, EventArgs e){

	}

	/**
	 * 
	 * @param defBusOb
	 */
	public Fusion.Api.FieldDef ResolveFieldUsedForValue(Fusion.Api.BusinessObjectDef defBusOb){
		return null;
	}

	public boolean SourceValueRequired(){
		return null;
	}

	public String Value(){
		return "";
	}

	public ValueSources ValueCategory(){
		return null;
	}

	private Fusion.BusinessLogic.ConstraintDef WhoAmI(){
		return null;
	}

}