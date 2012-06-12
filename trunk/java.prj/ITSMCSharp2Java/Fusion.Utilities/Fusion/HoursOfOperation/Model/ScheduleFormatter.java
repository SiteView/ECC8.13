package Fusion.HoursOfOperation.Model;

import Fusion.control.Daily;
import Fusion.control.DayOfWeek;
import Fusion.control.IRecurrenceVisitor;
import Fusion.control.MonthlyDay;
import Fusion.control.MonthlyDayOfWeek;
import Fusion.control.MonthlyWeekDay;
import Fusion.control.RecurrenceBase;
import Fusion.control.Weekly;
import Fusion.control.YearlyDay;
import Fusion.control.YearlyDayOfWeek;
import Fusion.control.YearlyEasterRelated;
import Fusion.control.YearlyWeekDay;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:37
 */
public class ScheduleFormatter extends IRecurrenceVisitor {

	private RecurrenceBase mRecur;
	private String mSchedule;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public ScheduleFormatter(){

	}

	/**
	 * 
	 * @param recur
	 */
	public ScheduleFormatter(RecurrenceBase recur){

	}

	/**
	 * 
	 * @param value
	 */
	private String FormatNth(int value){
		return "";
	}

	/**
	 * 
	 * @param dayOfWeek
	 */
	public static String GetAbbreviatedDayName(DayOfWeek dayOfWeek){
		return "";
	}

	/**
	 * 
	 * @param dayOfWeek
	 */
	public static String GetDayName(DayOfWeek dayOfWeek){
		return "";
	}

	public String GetEndAfter(){
		return "";
	}

	/**
	 * 
	 * @param month
	 */
	public static String GetMonthName(int month){
		return "";
	}

	/**
	 * 
	 * @param value
	 */
	private String GetNthSuffix(int value){
		return "";
	}

	public String GetSchedule(){
		return "";
	}

	public String GetStartAfter(){
		return "";
	}

	/**
	 * 
	 * @param recur
	 */
	public void OnDaily(Daily recur){

	}

	/**
	 * 
	 * @param recur
	 */
	public void OnMonthlyDay(MonthlyDay recur){

	}

	/**
	 * 
	 * @param recur
	 */
	public void OnMonthlyDayOfWeek(MonthlyDayOfWeek recur){

	}

	/**
	 * 
	 * @param recur
	 */
	public void OnMonthlyWeekDay(MonthlyWeekDay recur){

	}

	/**
	 * 
	 * @param recur
	 */
	public void OnWeekly(Weekly recur){

	}

	/**
	 * 
	 * @param recur
	 */
	public void OnYearlyDay(YearlyDay recur){

	}

	/**
	 * 
	 * @param recur
	 */
	public void OnYearlyDayOfWeek(YearlyDayOfWeek recur){

	}

	/**
	 * 
	 * @param recur
	 */
	public void OnYearlyEasterRelated(YearlyEasterRelated recur){

	}

	/**
	 * 
	 * @param recur
	 */
	public void OnYearlyWeekDay(YearlyWeekDay recur){

	}

	public RecurrenceBase Recur(){
		return null;
	}

}