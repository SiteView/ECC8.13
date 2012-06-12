package Fusion;

import Fusion.control.DateTime;
import Fusion.control.TimeSpan;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:39
 */
public class StopWatch {

	private Boolean m_bStopped = false;
	private DateTime m_start = new DateTime();
	private DateTime m_stop = new DateTime();
	private static StopWatch sw1 = new StopWatch();
	private static StopWatch sw2 = new StopWatch();
	private static StopWatch sw3 = new StopWatch();



	public void finalize() throws Throwable {

	}

	public StopWatch(){

	}

	public TimeSpan ElapsedTime(){
		return null;
	}

	public StopWatch getsw1(){
		return sw1;
	}

	public StopWatch getsw2(){
		return sw2;
	}

	public StopWatch getsw3(){
		return sw3;
	}

	public void Reset(){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsw1(StopWatch newVal){
		sw1 = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsw2(StopWatch newVal){
		sw2 = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsw3(StopWatch newVal){
		sw3 = newVal;
	}

	public void Start(){

	}

	public DateTime StartTime(){
		return null;
	}

	public void Stop(){

	}

	public DateTime StopTime(){
		return null;
	}

	public double tms(){
		return 0;
	}

}