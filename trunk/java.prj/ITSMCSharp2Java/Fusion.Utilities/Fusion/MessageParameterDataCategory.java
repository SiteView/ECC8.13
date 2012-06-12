package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:31
 */
public class MessageParameterDataCategory {

	private String Date = "Date";
	private String DateTime = "DateTime";
	private String Logical = "Logical";
	private String Number = "Number";
	private String ResourceId = "ResourceId";
	private String Text = "Text";
	private String Time = "Time";

	public MessageParameterDataCategory(){

	}

	public void finalize() throws Throwable {

	}

	public String getDate(){
		return Date;
	}

	public String getDateTime(){
		return DateTime;
	}

	public String getLogical(){
		return Logical;
	}

	public String getNumber(){
		return Number;
	}

	/**
	 * 
	 * @param strDataCategory
	 */
	public static ParameterDataCategory GetParameterDataCategory(String strDataCategory){
		return null;
	}

	public String getResourceId(){
		return ResourceId;
	}

	public String getText(){
		return Text;
	}

	public String getTime(){
		return Time;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDate(String newVal){
		Date = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDateTime(String newVal){
		DateTime = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLogical(String newVal){
		Logical = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNumber(String newVal){
		Number = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setResourceId(String newVal){
		ResourceId = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setText(String newVal){
		Text = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTime(String newVal){
		Time = newVal;
	}

}
