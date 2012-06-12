package Fusion.HoursOfOperation.Controller;
import Fusion.HoursOfOperation.Model.HOP;
import Fusion.control.Daily;
import Fusion.control.IRecurrenceVisitor;
import Fusion.control.MonthlyDay;
import Fusion.control.MonthlyDayOfWeek;
import Fusion.control.MonthlyWeekDay;
import Fusion.control.Weekly;
import Fusion.control.YearlyDay;
import Fusion.control.YearlyDayOfWeek;
import Fusion.control.YearlyEasterRelated;
import Fusion.control.YearlyWeekDay;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:15
 */
public class EditHOPLoader extends IRecurrenceVisitor {

	private HOP mHOP;
	private EditHOPFormData.HOPRow mHOPData;

	public EditHOPLoader(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public EditHOPFormData.HOPRow GetDefaultHOPData(){
		return null;
	}

	/**
	 * 
	 * @param hop
	 */
	public EditHOPFormData.HOPRow GetHOPData(HOP hop){
		return null;
	}

	private void LoadEndDetails(){

	}

	/**
	 * 
	 * @param recur
	 */
	private void OnDaily(Daily recur){

	}

	/**
	 * 
	 * @param recur
	 */
	private void OnMonthlyDay(MonthlyDay recur){

	}

	/**
	 * 
	 * @param recur
	 */
	private void OnMonthlyDayOfWeek(MonthlyDayOfWeek recur){

	}

	/**
	 * 
	 * @param recur
	 */
	private void OnMonthlyWeekDay(MonthlyWeekDay recur){

	}

	/**
	 * 
	 * @param recur
	 */
	private void OnWeekly(Weekly recur){

	}

	/**
	 * 
	 * @param recur
	 */
	private void OnYearlyDay(YearlyDay recur){

	}

	/**
	 * 
	 * @param recur
	 */
	private void OnYearlyDayOfWeek(YearlyDayOfWeek recur){

	}

	/**
	 * 
	 * @param recur
	 */
	private void OnYearlyEasterRelated(YearlyEasterRelated recur){

	}

	/**
	 * 
	 * @param recur
	 */
	private void OnYearlyWeekDay(YearlyWeekDay recur){

	}

}