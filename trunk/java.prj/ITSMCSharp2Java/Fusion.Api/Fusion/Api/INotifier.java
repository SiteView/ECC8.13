package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:52
 */
public interface INotifier {

	/**
	 * 
	 * @param strCategory
	 * @param strTarget
	 * @param strSource
	 * @param strDetails
	 */
	public void RegisterNotification(String strCategory, String strTarget, String strSource, String strDetails);

	/**
	 * 
	 * @param strCategory
	 * @param strTarget
	 * @param strSource
	 */
	public void RemoveNotification(String strCategory, String strTarget, String strSource);

}