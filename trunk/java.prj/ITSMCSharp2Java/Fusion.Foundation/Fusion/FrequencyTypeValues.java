package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:28
 */
public class FrequencyTypeValues {

	private int Autostart = 0x40;
	private int Daily = 4;
	private int Monthly = 0x10;
	private int MonthlyRelative = 0x20;
	private int OnDemand = 2;
	private int OneTime = 1;
	private int Recurring = 0x7c;
	private int UseDatabaseDefault = -1;
	private int Weekly = 8;

	public FrequencyTypeValues(){

	}

	public void finalize() throws Throwable {

	}

	public int getAutostart(){
		return Autostart;
	}

	public int getDaily(){
		return Daily;
	}

	public int getMonthly(){
		return Monthly;
	}

	public int getMonthlyRelative(){
		return MonthlyRelative;
	}

	public int getOnDemand(){
		return OnDemand;
	}

	public int getOneTime(){
		return OneTime;
	}

	public int getRecurring(){
		return Recurring;
	}

	public int getUseDatabaseDefault(){
		return UseDatabaseDefault;
	}

	public int getWeekly(){
		return Weekly;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAutostart(int newVal){
		Autostart = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDaily(int newVal){
		Daily = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMonthly(int newVal){
		Monthly = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMonthlyRelative(int newVal){
		MonthlyRelative = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOnDemand(int newVal){
		OnDemand = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOneTime(int newVal){
		OneTime = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRecurring(int newVal){
		Recurring = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUseDatabaseDefault(int newVal){
		UseDatabaseDefault = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setWeekly(int newVal){
		Weekly = newVal;
	}

}