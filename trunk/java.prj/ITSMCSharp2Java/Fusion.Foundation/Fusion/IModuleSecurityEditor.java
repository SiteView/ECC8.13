package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:50
 */
public interface IModuleSecurityEditor {

	public UserControl Control();

	public boolean LoadData();

	public ISecurityGroupEditor Parent();

	public boolean SaveData();

	public String Title();

}