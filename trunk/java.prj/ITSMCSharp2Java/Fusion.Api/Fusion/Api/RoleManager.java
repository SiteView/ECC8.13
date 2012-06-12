package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:25
 */
public class RoleManager extends AggregateUser {

	private IOrchestrator m_orch = null;
	private Fusion.BusinessLogic.RoleManager m_RoleManager = null;

	public RoleManager(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param roleManager
	 * @param orch
	 */
	public RoleManager(Fusion.BusinessLogic.RoleManager roleManager, IOrchestrator orch){

	}

	/**
	 * 
	 * @param fusionApi
	 */
	public static Fusion.Api.RoleManager CreateInstance(IFusionApi fusionApi){
		return null;
	}

	public String CurrentCulture(){
		return "";
	}

	public IDefinition GetCoreRole(){
		return null;
	}

	public IDefinition GetCurrentRole(){
		return null;
	}

	public String GetCurrentRoleName(){
		return "";
	}

	/**
	 * 
	 * @param rDef
	 */
	public void JustSetRole(IDefinition rDef){

	}

	/**
	 * 
	 * @param rDef
	 * @param sTgt
	 */
	public void JustSetRole(IDefinition rDef, String sTgt){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	protected void OnRoleChanged(Object sender, EventArgs e){

	}

	/**
	 * 
	 * @param sPersp
	 */
	public String PerspectiveCulture(String sPersp){
		return "";
	}

	public String PerspectiveFromRole(){
		return "";
	}

	/**
	 * 
	 * @param sPersp
	 */
	public String PerspectiveNameforCulture(String sPersp){
		return "";
	}

	/**
	 * 
	 * @param sPersp
	 */
	public String PerspectiveNameWithoutCulture(String sPersp){
		return "";
	}

	public EventHandler RoleChanged(){
		return null;
	}

	/**
	 * 
	 * @param sLang
	 */
	public void SetCulture(String sLang){

	}

	/**
	 * 
	 * @param rDef
	 */
	public void SetCurrentRole(IDefinition rDef){

	}

	/**
	 * 
	 * @param rDef
	 * @param sTgt
	 */
	public void SetCurrentRole(IDefinition rDef, String sTgt){

	}

	private Fusion.BusinessLogic.RoleManager WhoAmI(){
		return null;
	}

}