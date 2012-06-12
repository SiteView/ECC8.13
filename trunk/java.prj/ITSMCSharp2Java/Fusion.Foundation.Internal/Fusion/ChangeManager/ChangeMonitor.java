package Fusion.ChangeManager;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:17
 */
public class ChangeMonitor {

	private IChangeManager m_chm = null;
	private double m_fuzzyFactor = 0.01;
	private Hashtable m_htServices = new Hashtable();
	private DateTime m_LastCheck = DateTime.Now;
	private TimeSpan m_maxCacheTime = new TimeSpan(0, 30, 0);
	private TimeSpan m_minCacheTime = new TimeSpan(0, 30, 0);
	private TimeSpan m_nominalCacheTime = new TimeSpan(0, 30, 0);

	public ChangeMonitor(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param chm
	 */
	public ChangeMonitor(IChangeManager chm){

	}

	/**
	 * 
	 * @param strServiceName
	 * @param service
	 */
	public void AddMonitoredService(String strServiceName, IMonitoredService service){

	}

	public TimeSpan CacheTime(){
		return null;
	}

	protected IChangeManager ChangeManager(){
		return null;
	}

	/**
	 * 
	 * @param strServiceName
	 */
	public void Check(String strServiceName){

	}

	public double FuzzyFactor(){
		return 0;
	}

	public String GetCacheInfo(){
		return "";
	}

	/**
	 * 
	 * @param strServiceName
	 */
	public DateTime SetUpdate(String strServiceName){
		return null;
	}

	/**
	 * 
	 * @param strServiceName
	 * @param o
	 */
	public DateTime SetUpdate(String strServiceName, Object o){
		return null;
	}

}