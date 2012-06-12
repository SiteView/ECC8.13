package Fusion.ChangeManager;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:23
 */
public interface IMonitoredService {

	public void InvalidateCache();

	/**
	 * 
	 * @param o
	 */
	public void InvalidateCache(Object o);

	public DateTime LastUpdate();

	public String ServiceName();

}