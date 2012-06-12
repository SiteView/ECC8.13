package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:51
 */
public abstract class CriteriaDef extends DefinitionObject {

	public CriteriaDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public CriteriaDef(Object fusionObject){

	}

	public static String ClassName(){
		return "";
	}

	public abstract String CriteriaItem();

	/**
	 * 
	 * @param library
	 */
	public abstract String ToString(Fusion.Api.DefinitionLibrary library);

	private Fusion.BusinessLogic.CriteriaDef WhoAmI(){
		return null;
	}

}