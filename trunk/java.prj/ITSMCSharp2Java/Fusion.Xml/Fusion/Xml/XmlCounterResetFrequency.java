package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:49
 */
public class XmlCounterResetFrequency {

	private string BeginMonth = "BEGINMONTH";
	private string Day = "DAY";
	private string EndMonth = "ENDMONTH";
	private string Month = "MONTH";
	private string Never = "NEVER";
	private string Quarter = "QUARTER";
	private string ResetValue = "RESETVALUE";
	private string Week = "WEEK";
	private string Year = "YEAR";

	public XmlCounterResetFrequency(){

	}

	public void finalize() throws Throwable {

	}

	public string getBeginMonth(){
		return BeginMonth;
	}

	public string getDay(){
		return Day;
	}

	public string getEndMonth(){
		return EndMonth;
	}

	public string getMonth(){
		return Month;
	}

	public string getNever(){
		return Never;
	}

	public string getQuarter(){
		return Quarter;
	}

	public string getResetValue(){
		return ResetValue;
	}

	public string getWeek(){
		return Week;
	}

	public string getYear(){
		return Year;
	}

	/**
	 * 
	 * @param resetFrequency
	 */
	public static string ResetFrequencyToString(CounterResetFrequency resetFrequency){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBeginMonth(string newVal){
		BeginMonth = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDay(string newVal){
		Day = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEndMonth(string newVal){
		EndMonth = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMonth(string newVal){
		Month = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNever(string newVal){
		Never = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setQuarter(string newVal){
		Quarter = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setResetValue(string newVal){
		ResetValue = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setWeek(string newVal){
		Week = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setYear(string newVal){
		Year = newVal;
	}

	/**
	 * 
	 * @param strResetFrequency
	 */
	public static CounterResetFrequency StringToResetFrequency(string strResetFrequency){
		return null;
	}

}