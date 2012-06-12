package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:38:28
 */
public class XmlTimeUnit {

	private string Hours = "Hours";
	private string Minutes = "Minutes";
	private string None = "None";
	private string Seconds = "Seconds";

	public XmlTimeUnit(){

	}

	public void finalize() throws Throwable {

	}

	public string getHours(){
		return Hours;
	}

	public string getMinutes(){
		return Minutes;
	}

	public string getNone(){
		return None;
	}

	public string getSeconds(){
		return Seconds;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setHours(string newVal){
		Hours = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMinutes(string newVal){
		Minutes = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNone(string newVal){
		None = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSeconds(string newVal){
		Seconds = newVal;
	}

	/**
	 * 
	 * @param strCategory
	 */
	public static TimeUnit ToCategory(string strCategory){
		return null;
	}

	/**
	 * 
	 * @param timeUnit
	 */
	public static string ToString(TimeUnit timeUnit){
		return "";
	}

}