package Fusion.ChangeManager;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:23
 */
public interface IChangeManagerLiaison {

	public String GetCacheInfo();

	/**
	 * 
	 * @param strServiceName
	 */
	public DateTime GetUpdateTime(String strServiceName);

	/**
	 * 
	 * @param strServiceName
	 */
	public DateTime SetUpdateTime(String strServiceName);

}