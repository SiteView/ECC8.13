package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:49
 */
public interface ICounterService {

	public List GetCounterPlaceHolderList();

	/**
	 * 
	 * @param strName
	 */
	public String GetCounterValue(String strName);

	/**
	 * 
	 * @param strName
	 */
	public String GetNextCounterValue(String strName);

	/**
	 * 
	 * @param strName
	 */
	public String ResetCounter(String strName);

}