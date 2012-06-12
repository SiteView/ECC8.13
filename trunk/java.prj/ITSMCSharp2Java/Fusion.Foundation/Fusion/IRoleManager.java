package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:54
 */
public interface IRoleManager {

	public IDefinition GetCurrentRole();

	public String GetCurrentRoleName();

	public String PerspectiveFromRole();

	/**
	 * 
	 * @param rDef
	 */
	public void SetCurrentRole(IDefinition rDef);

}