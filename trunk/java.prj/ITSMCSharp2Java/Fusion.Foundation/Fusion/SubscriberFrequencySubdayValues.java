package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:23
 */
public class SubscriberFrequencySubdayValues {

	private int Hour = 8;
	private int Minute = 4;
	private int Once = 1;
	private int Second = 2;
	private int UseDatabaseDefault = -1;

	public SubscriberFrequencySubdayValues(){

	}

	public void finalize() throws Throwable {

	}

	public int getHour(){
		return Hour;
	}

	public int getMinute(){
		return Minute;
	}

	public int getOnce(){
		return Once;
	}

	public int getSecond(){
		return Second;
	}

	public int getUseDatabaseDefault(){
		return UseDatabaseDefault;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setHour(int newVal){
		Hour = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMinute(int newVal){
		Minute = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOnce(int newVal){
		Once = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSecond(int newVal){
		Second = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUseDatabaseDefault(int newVal){
		UseDatabaseDefault = newVal;
	}

}