package Fusion.ChangeManager;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:17
 */
public class ClientChangeManager implements IChangeManager {

	private Hashtable m_htServiceUpdates = new Hashtable();
	private IChangeManagerLiaison m_liaison = null;

	public ClientChangeManager(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param liaison
	 */
	public ClientChangeManager(IChangeManagerLiaison liaison){

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
	 * @param strChangeData
	 */
	protected void ParseChangeData(String strChangeData){

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