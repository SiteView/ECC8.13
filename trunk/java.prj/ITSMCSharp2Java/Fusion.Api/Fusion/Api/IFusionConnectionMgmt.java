package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:51
 */
public interface IFusionConnectionMgmt {

	public FusionConnectionSettings GetFusionConnectionSettings();

	/**
	 * 
	 * @param settings
	 */
	public void SetFusionConnection(FusionConnectionSettings settings);

}