package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:50
 */
public class CounterService implements ICounterService {

	private IOrchestrator m_orch = null;

	public CounterService(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param orch
	 */
	public CounterService(IOrchestrator orch){

	}

	public List GetCounterPlaceHolderList(){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public String GetCounterValue(String strName){
		return "";
	}

	/**
	 * 
	 * @param strName
	 */
	public String GetNextCounterValue(String strName){
		return "";
	}

	/**
	 * 
	 * @param strName
	 */
	public String ResetCounter(String strName){
		return "";
	}

}