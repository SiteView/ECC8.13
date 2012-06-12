package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:32
 */
public class PerspectiveValues {

	private String AllPerspectives = "(All)";
	private String BasePerspective = "(Base)";
	private String RolePerspective = "(Role)";

	public PerspectiveValues(){

	}

	public void finalize() throws Throwable {

	}

	public String getAllPerspectives(){
		return AllPerspectives;
	}

	public String getBasePerspective(){
		return BasePerspective;
	}

	public String getRolePerspective(){
		return RolePerspective;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAllPerspectives(String newVal){
		AllPerspectives = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBasePerspective(String newVal){
		BasePerspective = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRolePerspective(String newVal){
		RolePerspective = newVal;
	}

}