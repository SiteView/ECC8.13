package Fusion.HoursOfOperation.Model;

import Fusion.control.DateTime;
import Fusion.control.RecurrenceBase;
import Fusion.control.TimeSpan;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:22
 */
public class HOP {

	private DateTime mEndDate;
	private TimeSpan mEndTime;
	private String mName;
	private RecurrenceBase mRecur;
	private DateTime mStartDate;
	private TimeSpan mStartTime;
	private int mStatus;



	public void finalize() throws Throwable {

	}

	public HOP(){

	}

	/**
	 * 
	 * @param name
	 * @param recur
	 */
	public HOP(String name, RecurrenceBase recur){

	}

	public DateTime EndDate(){
		return null;
	}

	public TimeSpan EndTime(){
		return null;
	}

	public String Name(){
		return "";
	}

	public RecurrenceBase Recur(){
		return null;
	}

	public DateTime StartDate(){
		return null;
	}

	public TimeSpan StartTime(){
		return null;
	}

	public int Status(){
		return 0;
	}

}