package Fusion;

import Fusion.control.ILogger;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:33
 */
public class PerformanceWatch {

	private String COMPILATION_SYMBOL = "PERFORMANCETEST";
	private String LOG_SOURCE = "FrontRange Performace Tool";
	private ILogger m_Logger = null;
	private static PerformanceWatch m_PerformanceWatch = null;
	private RWHashtable m_Watches = new RWHashtable();



	public void finalize() throws Throwable {

	}

	public PerformanceWatch(){

	}

	private void Initialize(){

	}

	/**
	 * 
	 * @param strKey
	 * @param strMessage
	 */
	public void LogElapsedTime(String strKey, String strMessage){

	}

	/**
	 * 
	 * @param strKey
	 * @param strMessage
	 */
	private void LogElapsedTimeToEventLog(String strKey, String strMessage){

	}

	/**
	 * 
	 * @param strKey
	 */
	public void Reset(String strKey){

	}

	/**
	 * 
	 * @param strKey
	 */
	public void Start(String strKey){

	}

	/**
	 * 
	 * @param strKey
	 */
	public void Stop(String strKey){

	}

	/**
	 * 
	 * @param strKey
	 * @param strMessage
	 */
	public void StopAndLog(String strKey, String strMessage){

	}

	/**
	 * 
	 * @param strKey
	 */
	private void StopWatch(String strKey){

	}

	public static PerformanceWatch Watch(){
		return null;
	}

}