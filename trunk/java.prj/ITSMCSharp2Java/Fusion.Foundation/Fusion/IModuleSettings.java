package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:50
 */
public interface IModuleSettings {

	/**
	 * 
	 * @param FusionApi
	 */
	public Form GetMainSettingsForm(Object FusionApi);

	public IList GetServerSettingsForms();

	/**
	 * 
	 * @param settings
	 * @param strGroupName
	 */
	public IDefinition GetSettingGroupDef(ISettings settings, String strGroupName);

}