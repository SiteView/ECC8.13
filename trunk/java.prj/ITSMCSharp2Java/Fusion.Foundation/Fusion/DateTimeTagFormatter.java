package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:01
 */
public class DateTimeTagFormatter implements ITagFormatter {

	private String CustomDatePatternArgument = "CustomDate";
	private String CustomTimePatternArgument = "CustomTime";
	private String DateFormatArgument = "DateFormat";
	private String TimeFormatArgument = "TimeFormat";

	public DateTimeTagFormatter(){

	}

	public void finalize() throws Throwable {

	}

	public boolean ApplyLast(){
		return null;
	}

	/**
	 * 
	 * @param val
	 * @param format
	 */
	public FusionValue Format(FusionValue val, TagFormat format){
		return null;
	}

	public String getCustomDatePatternArgument(){
		return CustomDatePatternArgument;
	}

	public String getCustomTimePatternArgument(){
		return CustomTimePatternArgument;
	}

	public String getDateFormatArgument(){
		return DateFormatArgument;
	}

	public String getTimeFormatArgument(){
		return TimeFormatArgument;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCustomDatePatternArgument(String newVal){
		CustomDatePatternArgument = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCustomTimePatternArgument(String newVal){
		CustomTimePatternArgument = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDateFormatArgument(String newVal){
		DateFormatArgument = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTimeFormatArgument(String newVal){
		TimeFormatArgument = newVal;
	}

}