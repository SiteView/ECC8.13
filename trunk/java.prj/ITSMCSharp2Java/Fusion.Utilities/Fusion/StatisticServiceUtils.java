package Fusion;

import Fusion.control.DateTime;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:38
 */
public class StatisticServiceUtils {

	private String DefinitionIdColumn = "DefinitionID";
	private String FusionQueryColumn = "FusionQuery";
	private String InProcessColumn = "InProcess";
	private String ItemNameColumn = "ItemName";
	private String ItemRowColumn = "ItemRow";
	private String ItemValueColumn = "ItemValue";
	private String LogExpirationTimeSpanColumn = "LogExpirationTimeSpan";
	private String NextScheduledDateTimeColumn = "NextScheduledDateTime";
	private String RequestEnabledColumn = "RequestEnabled";
	private String RequestEndDateTimeColumn = "RequestEndDateTime";
	private String RequestIdColumn = "RequestID";
	private String RequestNameColumn = "RequestName";
	private String RequestStartDateTimeColumn = "RequestStartDateTime";
	private String SchedulingCategoryColumn = "SchedulingCategory";
	private String SchedulingValueColumn = "SchedulingValue";
	private String StatisticDateTimeColumn = "StatisticDateTime";
	private String StatisticRequestsTable = "StatisticRequests";
	private String StatisticResultsTable = "StatisticResults";

	public StatisticServiceUtils(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param statisticScheduling
	 * @param strSchedulingValue
	 * @param dtCurrentScheduledDateTime
	 */
	public static DateTime CalculateNextScheduledDateTime(StatisticScheduling statisticScheduling, String strSchedulingValue, DateTime dtCurrentScheduledDateTime){
		return null;
	}

	/**
	 * 
	 * @param statisticScheduling
	 * @param strSchedulingValue
	 * @param dtCurrentScheduledDateTime
	 * @param dtCurrentDateTime
	 */
	public static DateTime CalculateNextScheduledDateTime(StatisticScheduling statisticScheduling, String strSchedulingValue, DateTime dtCurrentScheduledDateTime, DateTime dtCurrentDateTime){
		return null;
	}

	/**
	 * 
	 * @param statisticScheduling
	 * @param strSchedulingValue
	 * @param dtCurrentScheduledDateTime
	 */
	public static DateTime CalculatePreviousScheduledDateTime(StatisticScheduling statisticScheduling, String strSchedulingValue, DateTime dtCurrentScheduledDateTime){
		return null;
	}

	/**
	 * 
	 * @param nNumberOfBackStatistics
	 * @param dtEndDateTime
	 * @param statisticScheduling
	 * @param strSchedulingValue
	 */
	public static DateTime CalculateStartDateTimeForBackStatistics(int nNumberOfBackStatistics, DateTime dtEndDateTime, StatisticScheduling statisticScheduling, String strSchedulingValue){
		return null;
	}

	public String getDefinitionIdColumn(){
		return DefinitionIdColumn;
	}

	public String getFusionQueryColumn(){
		return FusionQueryColumn;
	}

	public String getInProcessColumn(){
		return InProcessColumn;
	}

	public String getItemNameColumn(){
		return ItemNameColumn;
	}

	public String getItemRowColumn(){
		return ItemRowColumn;
	}

	public String getItemValueColumn(){
		return ItemValueColumn;
	}

	public String getLogExpirationTimeSpanColumn(){
		return LogExpirationTimeSpanColumn;
	}

	public String getNextScheduledDateTimeColumn(){
		return NextScheduledDateTimeColumn;
	}

	public String getRequestEnabledColumn(){
		return RequestEnabledColumn;
	}

	public String getRequestEndDateTimeColumn(){
		return RequestEndDateTimeColumn;
	}

	public String getRequestIdColumn(){
		return RequestIdColumn;
	}

	public String getRequestNameColumn(){
		return RequestNameColumn;
	}

	public String getRequestStartDateTimeColumn(){
		return RequestStartDateTimeColumn;
	}

	public String getSchedulingCategoryColumn(){
		return SchedulingCategoryColumn;
	}

	public String getSchedulingValueColumn(){
		return SchedulingValueColumn;
	}

	public String getStatisticDateTimeColumn(){
		return StatisticDateTimeColumn;
	}

	public String getStatisticRequestsTable(){
		return StatisticRequestsTable;
	}

	public String getStatisticResultsTable(){
		return StatisticResultsTable;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDefinitionIdColumn(String newVal){
		DefinitionIdColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFusionQueryColumn(String newVal){
		FusionQueryColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setInProcessColumn(String newVal){
		InProcessColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setItemNameColumn(String newVal){
		ItemNameColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setItemRowColumn(String newVal){
		ItemRowColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setItemValueColumn(String newVal){
		ItemValueColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLogExpirationTimeSpanColumn(String newVal){
		LogExpirationTimeSpanColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNextScheduledDateTimeColumn(String newVal){
		NextScheduledDateTimeColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRequestEnabledColumn(String newVal){
		RequestEnabledColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRequestEndDateTimeColumn(String newVal){
		RequestEndDateTimeColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRequestIdColumn(String newVal){
		RequestIdColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRequestNameColumn(String newVal){
		RequestNameColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRequestStartDateTimeColumn(String newVal){
		RequestStartDateTimeColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSchedulingCategoryColumn(String newVal){
		SchedulingCategoryColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSchedulingValueColumn(String newVal){
		SchedulingValueColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setStatisticDateTimeColumn(String newVal){
		StatisticDateTimeColumn = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setStatisticRequestsTable(String newVal){
		StatisticRequestsTable = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setStatisticResultsTable(String newVal){
		StatisticResultsTable = newVal;
	}

	/**
	 * 
	 * @param strStatisticScheduling
	 */
	public static StatisticScheduling ToStatisticSchedulingCategory(String strStatisticScheduling){
		return null;
	}

}