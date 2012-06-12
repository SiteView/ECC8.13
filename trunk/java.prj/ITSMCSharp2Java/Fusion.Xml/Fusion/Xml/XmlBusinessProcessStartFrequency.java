package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:45
 */
public class XmlBusinessProcessStartFrequency {

	private string BeginMonth = "BEGINMONTH";
	private string Day = "DAY";
	private string EndMonth = "ENDMONTH";
	private string Month = "MONTH";
	private string Quarter = "QUARTER";
	private string Week = "WEEK";
	private string Year = "YEAR";

	public XmlBusinessProcessStartFrequency(){

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

	public string getQuarter(){
		return Quarter;
	}

	public string getWeek(){
		return Week;
	}

	public string getYear(){
		return Year;
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
	public void setQuarter(string newVal){
		Quarter = newVal;
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
	 * @param startFrequency
	 */
	public static string StartFrequencyToString(BusinessProcessStartFrequency startFrequency){
		return "";
	}

	/**
	 * 
	 * @param strStartFrequency
	 */
	public static BusinessProcessStartFrequency StringToStartFrequency(string strStartFrequency){
		return null;
	}

}