package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:46
 */
public class HoursOfOperationDef extends DefinitionObject {

	public HoursOfOperationDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public HoursOfOperationDef(Object fusionObject){

	}

	/**
	 * 
	 * @param HOPExemtionDef
	 */
	public void AddExemption(Fusion.Api.HoursOfOperationExemptionDef HOPExemtionDef){

	}

	public static String ClassName(){
		return "";
	}

	public Fusion.Api.HoursOfOperationExemptionDef CreateExemption(){
		return null;
	}

	public int DailyChoice(){
		return 0;
	}

	public String DailyEveryNthDay(){
		return "";
	}

	/**
	 * 
	 * @param strId
	 */
	public void DeleteExemption(String strId){

	}

	public int EndChoice(){
		return 0;
	}

	public String EndDate(){
		return "";
	}

	public String EndTime(){
		return "";
	}

	public int ExemptionCount(){
		return 0;
	}

	public boolean Friday(){
		return null;
	}

	/**
	 * 
	 * @param HOPExemptionId
	 */
	public Fusion.Api.HoursOfOperationExemptionDef GetHOPExemptionById(String HOPExemptionId){
		return null;
	}

	/**
	 * 
	 * @param HOPExemptionName
	 */
	public Fusion.Api.HoursOfOperationExemptionDef GetHOPExemptionByName(String HOPExemptionName){
		return null;
	}

	public String HOPName(){
		return "";
	}

	public List HoursOfOperationExemptionDefs(){
		return null;
	}

	public String MaxOccurrences(){
		return "";
	}

	public boolean Monday(){
		return null;
	}

	public int MonthlyChoice(){
		return 0;
	}

	public String MonthlyDay(){
		return "";
	}

	public int MonthlyDayOccurrence(){
		return 0;
	}

	public int MonthlyDayOfWeek(){
		return 0;
	}

	public String MonthlyEveryNthMonth(){
		return "";
	}

	public int MonthlyNthOccurrence(){
		return 0;
	}

	public int MonthlyWeekDayType(){
		return 0;
	}

	public int RecurrenceChoice(){
		return 0;
	}

	public boolean Saturday(){
		return null;
	}

	public String StartDate(){
		return "";
	}

	public String StartTime(){
		return "";
	}

	public int Status(){
		return 0;
	}

	public boolean Sunday(){
		return null;
	}

	public boolean Thursday(){
		return null;
	}

	public int TimeZoneIndex(){
		return 0;
	}

	public String TimeZoneName(){
		return "";
	}

	public boolean Tuesday(){
		return null;
	}

	/**
	 * 
	 * @param HOPNewExemptionDef
	 */
	public void UpdateExemption(Fusion.Api.HoursOfOperationExemptionDef HOPNewExemptionDef){

	}

	public boolean UseTimeZone(){
		return null;
	}

	public boolean Wednesday(){
		return null;
	}

	public String WeeklyEveryNthWeek(){
		return "";
	}

	private Fusion.BusinessLogic.HoursOfOperationDef WhoAmI(){
		return null;
	}

	public int YearlyChoice(){
		return 0;
	}

	public String YearlyDay(){
		return "";
	}

	public int YearlyDayMonth(){
		return 0;
	}

	public int YearlyDayOccurrence(){
		return 0;
	}

	public int YearlyDayOfWeek(){
		return 0;
	}

	public int YearlyDayOfWeekMonth(){
		return 0;
	}

	public String YearlyEveryNthYear(){
		return "";
	}

	public int YearlyNthOccurrence(){
		return 0;
	}

	public int YearlyWeekDayMonth(){
		return 0;
	}

	public int YearlyWeekDayType(){
		return 0;
	}

}