package Fusion.HoursOfOperation.Controller;

import javax.sql.rowset.spi.XmlReader;
import javax.xml.bind.annotation.XmlSchema;

import Fusion.control.CollectionChangeEventArgs;
import Fusion.control.DataColumn;
import Fusion.control.DataRow;
import Fusion.control.DataRowAction;
import Fusion.control.DataRowBuilder;
import Fusion.control.DataRowChangeEventArgs;
import Fusion.control.DataSet;
import Fusion.control.DataTable;
import Fusion.control.EventArgs;
import Fusion.control.IEnumerable;
import Fusion.control.IEnumerator;
import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;
import Fusion.control.Type;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 11:18:13
 */
public class EditHOPFormData extends DataSet {

	public class HOPRowChangeEventHandler {

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:13
	 */
	public class HOPDataTable extends DataTable implements IEnumerable {

		private DataColumn columnDailyChoice;
		private DataColumn columnDailyEveryNthDay;
		private DataColumn columnEndChoice;
		private DataColumn columnEndDate;
		private DataColumn columnEndTime;
		private DataColumn columnFriday;
		private DataColumn columnMaxOccurrences;
		private DataColumn columnMonday;
		private DataColumn columnMonthlyChoice;
		private DataColumn columnMonthlyDay;
		private DataColumn columnMonthlyDayOccurrence;
		private DataColumn columnMonthlyDayOfWeek;
		private DataColumn columnMonthlyEveryNthMonth;
		private DataColumn columnMonthlyNthOccurrence;
		private DataColumn columnMonthlyWeekDayType;
		private DataColumn columnName;
		private DataColumn columnRecurrenceChoice;
		private DataColumn columnSaturday;
		private DataColumn columnStartDate;
		private DataColumn columnStartTime;
		private DataColumn columnStatus;
		private DataColumn columnSunday;
		private DataColumn columnThursday;
		private DataColumn columnTuesday;
		private DataColumn columnWednesday;
		private DataColumn columnWeeklyEveryNthWeek;
		private DataColumn columnYearlyChoice;
		private DataColumn columnYearlyDay;
		private DataColumn columnYearlyDayMonth;
		private DataColumn columnYearlyDayOccurrence;
		private DataColumn columnYearlyDayOfWeek;
		private DataColumn columnYearlyDayOfWeekMonth;
		private DataColumn columnYearlyEveryNthYear;
		private DataColumn columnYearlyNthOccurrence;
		private DataColumn columnYearlyWeekDayMonth;
		private DataColumn columnYearlyWeekDayType;



		public void finalize() throws Throwable {
			super.finalize();
		}

		public HOPDataTable(){

		}

		/**
		 * 
		 * @param table
		 */
		public HOPDataTable(DataTable table){

		}

		/**
		 * 
		 * @param row
		 */
		public void AddHOPRow(EditHOPFormData.HOPRow row){

		}

		/**
		 * 
		 * @param Name
		 * @param Status
		 * @param StartDate
		 * @param StartTime
		 * @param EndChoice
		 * @param MaxOccurrences
		 * @param EndDate
		 * @param EndTime
		 * @param RecurrenceChoice
		 * @param DailyChoice
		 * @param DailyEveryNthDay
		 * @param WeeklyEveryNthWeek
		 * @param Sunday
		 * @param Monday
		 * @param Tuesday
		 * @param Wednesday
		 * @param Thursday
		 * @param Friday
		 * @param Saturday
		 * @param MonthlyChoice
		 * @param MonthlyEveryNthMonth
		 * @param MonthlyDay
		 * @param MonthlyNthOccurrence
		 * @param MonthlyDayOfWeek
		 * @param MonthlyDayOccurrence
		 * @param MonthlyWeekDayType
		 * @param YearlyChoice
		 * @param YearlyEveryNthYear
		 * @param YearlyDayMonth
		 * @param YearlyDay
		 * @param YearlyDayOfWeekMonth
		 * @param YearlyNthOccurrence
		 * @param YearlyDayOfWeek
		 * @param YearlyDayOccurrence
		 * @param YearlyWeekDayMonth
		 * @param YearlyWeekDayType
		 */
		public EditHOPFormData.HOPRow AddHOPRow(String Name, int Status, String StartDate, String StartTime, int EndChoice, String MaxOccurrences, String EndDate, String EndTime, int RecurrenceChoice, int DailyChoice, String DailyEveryNthDay, String WeeklyEveryNthWeek, Boolean Sunday, Boolean Monday, Boolean Tuesday, Boolean Wednesday, Boolean Thursday, Boolean Friday, Boolean Saturday, int MonthlyChoice, String MonthlyEveryNthMonth, String MonthlyDay, int MonthlyNthOccurrence, int MonthlyDayOfWeek, int MonthlyDayOccurrence, int MonthlyWeekDayType, int YearlyChoice, String YearlyEveryNthYear, int YearlyDayMonth, String YearlyDay, int YearlyDayOfWeekMonth, int YearlyNthOccurrence, int YearlyDayOfWeek, int YearlyDayOccurrence, int YearlyWeekDayMonth, int YearlyWeekDayType){
			return null;
		}

		public DataTable Clone(){
			return null;
		}

		public int Count(){
			return 0;
		}

		protected DataTable CreateInstance(){
			return null;
		}

		public DataColumn DailyChoiceColumn(){
			return null;
		}

		public DataColumn DailyEveryNthDayColumn(){
			return null;
		}

		public DataColumn EndChoiceColumn(){
			return null;
		}

		public DataColumn EndDateColumn(){
			return null;
		}

		public DataColumn EndTimeColumn(){
			return null;
		}

		public DataColumn FridayColumn(){
			return null;
		}

		public IEnumerator GetEnumerator(){
			return null;
		}

		protected Type GetRowType(){
			return null;
		}

		public EditHOPFormData.HOPRowChangeEventHandler HOPRowChanged(){
			return null;
		}

		public EditHOPFormData.HOPRowChangeEventHandler HOPRowChanging(){
			return null;
		}

		public EditHOPFormData.HOPRowChangeEventHandler HOPRowDeleted(){
			return null;
		}

		public EditHOPFormData.HOPRowChangeEventHandler HOPRowDeleting(){
			return null;
		}

		private void InitClass(){

		}

		public void InitVars(){

		}

		public DataColumn MaxOccurrencesColumn(){
			return null;
		}

		public DataColumn MondayColumn(){
			return null;
		}

		public DataColumn MonthlyChoiceColumn(){
			return null;
		}

		public DataColumn MonthlyDayColumn(){
			return null;
		}

		public DataColumn MonthlyDayOccurrenceColumn(){
			return null;
		}

		public DataColumn MonthlyDayOfWeekColumn(){
			return null;
		}

		public DataColumn MonthlyEveryNthMonthColumn(){
			return null;
		}

		public DataColumn MonthlyNthOccurrenceColumn(){
			return null;
		}

		public DataColumn MonthlyWeekDayTypeColumn(){
			return null;
		}

		public DataColumn NameColumn(){
			return null;
		}

		public EditHOPFormData.HOPRow NewHOPRow(){
			return null;
		}

		/**
		 * 
		 * @param builder
		 */
		protected DataRow NewRowFromBuilder(DataRowBuilder builder){
			return null;
		}

		/**
		 * 
		 * @param e
		 */
		protected void OnRowChanged(DataRowChangeEventArgs e){

		}

		/**
		 * 
		 * @param e
		 */
		protected void OnRowChanging(DataRowChangeEventArgs e){

		}

		/**
		 * 
		 * @param e
		 */
		protected void OnRowDeleted(DataRowChangeEventArgs e){

		}

		/**
		 * 
		 * @param e
		 */
		protected void OnRowDeleting(DataRowChangeEventArgs e){

		}

		public DataColumn RecurrenceChoiceColumn(){
			return null;
		}

		/**
		 * 
		 * @param row
		 */
		public void RemoveHOPRow(EditHOPFormData.HOPRow row){

		}

		public DataColumn SaturdayColumn(){
			return null;
		}

		public DataColumn StartDateColumn(){
			return null;
		}

		public DataColumn StartTimeColumn(){
			return null;
		}

		public DataColumn StatusColumn(){
			return null;
		}

		public DataColumn SundayColumn(){
			return null;
		}

		/**
		 * 
		 * @param index
		 */
		public EditHOPFormData.HOPRow getThis(int index){
			return null;
		}

		public DataColumn ThursdayColumn(){
			return null;
		}

		public DataColumn TuesdayColumn(){
			return null;
		}

		public DataColumn WednesdayColumn(){
			return null;
		}

		public DataColumn WeeklyEveryNthWeekColumn(){
			return null;
		}

		public DataColumn YearlyChoiceColumn(){
			return null;
		}

		public DataColumn YearlyDayColumn(){
			return null;
		}

		public DataColumn YearlyDayMonthColumn(){
			return null;
		}

		public DataColumn YearlyDayOccurrenceColumn(){
			return null;
		}

		public DataColumn YearlyDayOfWeekColumn(){
			return null;
		}

		public DataColumn YearlyDayOfWeekMonthColumn(){
			return null;
		}

		public DataColumn YearlyEveryNthYearColumn(){
			return null;
		}

		public DataColumn YearlyNthOccurrenceColumn(){
			return null;
		}

		public DataColumn YearlyWeekDayMonthColumn(){
			return null;
		}

		public DataColumn YearlyWeekDayTypeColumn(){
			return null;
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:13
	 */
	public class HOPRow extends DataRow {

		private EditHOPFormData.HOPDataTable tableHOP;

		public HOPRow(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		/**
		 * 
		 * @param rb
		 */
		public HOPRow(DataRowBuilder rb){

		}

		public int DailyChoice(){
			return 0;
		}

		public String DailyEveryNthDay(){
			return "";
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

		public Boolean Friday(){
			return null;
		}

		public Boolean IsDailyChoiceNull(){
			return null;
		}

		public Boolean IsDailyEveryNthDayNull(){
			return null;
		}

		public Boolean IsEndChoiceNull(){
			return null;
		}

		public Boolean IsEndDateNull(){
			return null;
		}

		public Boolean IsEndTimeNull(){
			return null;
		}

		public Boolean IsFridayNull(){
			return null;
		}

		public Boolean IsMaxOccurrencesNull(){
			return null;
		}

		public Boolean IsMondayNull(){
			return null;
		}

		public Boolean IsMonthlyChoiceNull(){
			return null;
		}

		public Boolean IsMonthlyDayNull(){
			return null;
		}

		public Boolean IsMonthlyDayOccurrenceNull(){
			return null;
		}

		public Boolean IsMonthlyDayOfWeekNull(){
			return null;
		}

		public Boolean IsMonthlyEveryNthMonthNull(){
			return null;
		}

		public Boolean IsMonthlyNthOccurrenceNull(){
			return null;
		}

		public Boolean IsMonthlyWeekDayTypeNull(){
			return null;
		}

		public Boolean IsNameNull(){
			return null;
		}

		public Boolean IsRecurrenceChoiceNull(){
			return null;
		}

		public Boolean IsSaturdayNull(){
			return null;
		}

		public Boolean IsStartDateNull(){
			return null;
		}

		public Boolean IsStartTimeNull(){
			return null;
		}

		public Boolean IsStatusNull(){
			return null;
		}

		public Boolean IsSundayNull(){
			return null;
		}

		public Boolean IsThursdayNull(){
			return null;
		}

		public Boolean IsTuesdayNull(){
			return null;
		}

		public Boolean IsWednesdayNull(){
			return null;
		}

		public Boolean IsWeeklyEveryNthWeekNull(){
			return null;
		}

		public Boolean IsYearlyChoiceNull(){
			return null;
		}

		public Boolean IsYearlyDayMonthNull(){
			return null;
		}

		public Boolean IsYearlyDayNull(){
			return null;
		}

		public Boolean IsYearlyDayOccurrenceNull(){
			return null;
		}

		public Boolean IsYearlyDayOfWeekMonthNull(){
			return null;
		}

		public Boolean IsYearlyDayOfWeekNull(){
			return null;
		}

		public Boolean IsYearlyEveryNthYearNull(){
			return null;
		}

		public Boolean IsYearlyNthOccurrenceNull(){
			return null;
		}

		public Boolean IsYearlyWeekDayMonthNull(){
			return null;
		}

		public Boolean IsYearlyWeekDayTypeNull(){
			return null;
		}

		public String MaxOccurrences(){
			return "";
		}

		public Boolean Monday(){
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

		public String Name(){
			return "";
		}

		public int RecurrenceChoice(){
			return 0;
		}

		public Boolean Saturday(){
			return null;
		}

		public void SetDailyChoiceNull(){

		}

		public void SetDailyEveryNthDayNull(){

		}

		public void SetEndChoiceNull(){

		}

		public void SetEndDateNull(){

		}

		public void SetEndTimeNull(){

		}

		public void SetFridayNull(){

		}

		public void SetMaxOccurrencesNull(){

		}

		public void SetMondayNull(){

		}

		public void SetMonthlyChoiceNull(){

		}

		public void SetMonthlyDayNull(){

		}

		public void SetMonthlyDayOccurrenceNull(){

		}

		public void SetMonthlyDayOfWeekNull(){

		}

		public void SetMonthlyEveryNthMonthNull(){

		}

		public void SetMonthlyNthOccurrenceNull(){

		}

		public void SetMonthlyWeekDayTypeNull(){

		}

		public void SetNameNull(){

		}

		public void SetRecurrenceChoiceNull(){

		}

		public void SetSaturdayNull(){

		}

		public void SetStartDateNull(){

		}

		public void SetStartTimeNull(){

		}

		public void SetStatusNull(){

		}

		public void SetSundayNull(){

		}

		public void SetThursdayNull(){

		}

		public void SetTuesdayNull(){

		}

		public void SetWednesdayNull(){

		}

		public void SetWeeklyEveryNthWeekNull(){

		}

		public void SetYearlyChoiceNull(){

		}

		public void SetYearlyDayMonthNull(){

		}

		public void SetYearlyDayNull(){

		}

		public void SetYearlyDayOccurrenceNull(){

		}

		public void SetYearlyDayOfWeekMonthNull(){

		}

		public void SetYearlyDayOfWeekNull(){

		}

		public void SetYearlyEveryNthYearNull(){

		}

		public void SetYearlyNthOccurrenceNull(){

		}

		public void SetYearlyWeekDayMonthNull(){

		}

		public void SetYearlyWeekDayTypeNull(){

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

		public Boolean Sunday(){
			return null;
		}

		public Boolean Thursday(){
			return null;
		}

		public Boolean Tuesday(){
			return null;
		}

		public Boolean Wednesday(){
			return null;
		}

		public String WeeklyEveryNthWeek(){
			return "";
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

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:14
	 */
	public class HOPRowChangeEvent extends EventArgs {

		private DataRowAction eventAction;
		private EditHOPFormData.HOPRow eventRow;

		public HOPRowChangeEvent(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		/**
		 * 
		 * @param row
		 * @param action
		 */
		public HOPRowChangeEvent(EditHOPFormData.HOPRow row, DataRowAction action){

		}

		public DataRowAction Action(){
			return null;
		}

		public EditHOPFormData.HOPRow Row(){
			return null;
		}

	}

	private HOPDataTable tableHOP;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public EditHOPFormData(){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	protected EditHOPFormData(SerializationInfo info, StreamingContext context){

	}

	public DataSet Clone(){
		return null;
	}

	protected XmlSchema GetSchemaSerializable(){
		return null;
	}

	public HOPDataTable HOP(){
		return null;
	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	public void HOPRowChangeEventHandler(Object sender, EditHOPFormData.HOPRowChangeEvent e){

	}

	private void InitClass(){

	}

	public void InitVars(){

	}

	/**
	 * 
	 * @param reader
	 */
	protected void ReadXmlSerializable(XmlReader reader){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void SchemaChanged(Object sender, CollectionChangeEventArgs e){

	}

	private Boolean ShouldSerializeHOP(){
		return null;
	}

	protected Boolean ShouldSerializeRelations(){
		return null;
	}

	protected Boolean ShouldSerializeTables(){
		return null;
	}

}