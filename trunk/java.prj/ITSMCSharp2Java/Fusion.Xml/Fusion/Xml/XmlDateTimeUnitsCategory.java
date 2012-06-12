package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:50
 */
public class XmlDateTimeUnitsCategory {

	private string defDateTime = "DATETIME";
	private string defDays = "DAYS";
	private string defHours = "HOURS";
	private string defMilliseconds = "MILLISECONDS";
	private string defMinutes = "MINUTES";
	private string defNone = "NONE";
	private string defSeconds = "SECONDS";
	private string defTimeSpan = "TIMESPAN";
	private string defWeeks = "WEEKS";
	private string defYears = "YEARS";

	public XmlDateTimeUnitsCategory(){

	}

	public void finalize() throws Throwable {

	}

	public string getdefDateTime(){
		return defDateTime;
	}

	public string getdefDays(){
		return defDays;
	}

	public string getdefHours(){
		return defHours;
	}

	public string getdefMilliseconds(){
		return defMilliseconds;
	}

	public string getdefMinutes(){
		return defMinutes;
	}

	public string getdefNone(){
		return defNone;
	}

	public string getdefSeconds(){
		return defSeconds;
	}

	public string getdefTimeSpan(){
		return defTimeSpan;
	}

	public string getdefWeeks(){
		return defWeeks;
	}

	public string getdefYears(){
		return defYears;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefDateTime(string newVal){
		defDateTime = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefDays(string newVal){
		defDays = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefHours(string newVal){
		defHours = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefMilliseconds(string newVal){
		defMilliseconds = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefMinutes(string newVal){
		defMinutes = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefNone(string newVal){
		defNone = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefSeconds(string newVal){
		defSeconds = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefTimeSpan(string newVal){
		defTimeSpan = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefWeeks(string newVal){
		defWeeks = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefYears(string newVal){
		defYears = newVal;
	}

	/**
	 * 
	 * @param strCategory
	 */
	public static DateTimeUnits ToCategory(string strCategory){
		return null;
	}

	/**
	 * 
	 * @param unitsValue
	 */
	public static string ToString(DateTimeUnits unitsValue){
		return "";
	}

}