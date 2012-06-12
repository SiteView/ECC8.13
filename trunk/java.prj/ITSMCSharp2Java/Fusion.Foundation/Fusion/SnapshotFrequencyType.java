package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:19
 */
public class SnapshotFrequencyType {

	private int Daily = 4;
	private int Monthly = 10;
	private int MonthlyRelativeToFrequencyInterval = 20;
	private int Once = 1;
	private int UseDatabaseDefault = -1;
	private int Weekly = 8;
	private int WhenSqlServerAgentStarts = 40;

	public SnapshotFrequencyType(){

	}

	public void finalize() throws Throwable {

	}

	public int getDaily(){
		return Daily;
	}

	public int getMonthly(){
		return Monthly;
	}

	public int getMonthlyRelativeToFrequencyInterval(){
		return MonthlyRelativeToFrequencyInterval;
	}

	public int getOnce(){
		return Once;
	}

	public int getUseDatabaseDefault(){
		return UseDatabaseDefault;
	}

	public int getWeekly(){
		return Weekly;
	}

	public int getWhenSqlServerAgentStarts(){
		return WhenSqlServerAgentStarts;
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
	public void setMonthlyRelativeToFrequencyInterval(int newVal){
		MonthlyRelativeToFrequencyInterval = newVal;
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

	/**
	 * 
	 * @param newVal
	 */
	public void setWhenSqlServerAgentStarts(int newVal){
		WhenSqlServerAgentStarts = newVal;
	}

}