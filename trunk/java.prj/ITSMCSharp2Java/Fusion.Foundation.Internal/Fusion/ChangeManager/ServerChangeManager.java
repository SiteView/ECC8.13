package Fusion.ChangeManager;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:28
 */
public class ServerChangeManager implements IChangeManager {

	private Hashtable m_htChangeInfo = new Hashtable();
	private Hashtable m_htServiceUpdates = new Hashtable();

	public ServerChangeManager(){

	}

	public void finalize() throws Throwable {

	}

	public String GetCacheInfo(){
		return "";
	}

	/**
	 * 
	 * @param strServiceName
	 */
	public DateTime GetUpdateTime(String strServiceName){
		return null;
	}

	/**
	 * 
	 * @param strServiceName
	 */
	public DateTime SetUpdateTime(String strServiceName){
		return null;
	}

	public void UpdateCacheInfo(){

	}

}