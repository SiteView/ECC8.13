package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:23
 */
public interface IDatabaseSpecifics {

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nNumDays
	 */
	public String AddDays(String strDateTimeColumn, int nNumDays);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nNumHours
	 */
	public String AddHours(String strDateTimeColumn, int nNumHours);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nNumMinutes
	 */
	public String AddMinutes(String strDateTimeColumn, int nNumMinutes);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nNumMonths
	 */
	public String AddMonths(String strDateTimeColumn, int nNumMonths);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nNumQuarters
	 */
	public String AddQuarters(String strDateTimeColumn, int nNumQuarters);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nNumSeconds
	 */
	public String AddSeconds(String strDateTimeColumn, int nNumSeconds);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nNumYears
	 */
	public String AddYears(String strDateTimeColumn, int nNumYears);

	/**
	 * 
	 * @param strColumnName
	 */
	public String AverageAllValues(String strColumnName);

	/**
	 * 
	 * @param strColumnName
	 */
	public String AverageDistinctValues(String strColumnName);

	/**
	 * 
	 * @param strTableToJoinWith
	 * @param strExpressions
	 */
	public String BuildJoinClause(String strTableToJoinWith, String strExpressions);

	/**
	 * 
	 * @param strTableToJoinWith
	 * @param strExpressions
	 */
	public String BuildLeftOuterJoinClause(String strTableToJoinWith, String strExpressions);

	/**
	 * 
	 * @param strTableToJoinWith
	 * @param strExpressions
	 */
	public String BuildRightOuterJoinClause(String strTableToJoinWith, String strExpressions);

	/**
	 * 
	 * @param strOwnerName
	 * @param strTableName
	 * @param bUseDistinct
	 * @param bUseTopQuery
	 * @param nTopItems
	 * @param strSelectColumns
	 * @param strWhereClause
	 * @param strOrderByClause
	 * @param strGroupByClause
	 */
	public String BuildSelectStatement(String strOwnerName, String strTableName, boolean bUseDistinct, boolean bUseTopQuery, int nTopItems, String strSelectColumns, String strWhereClause, String strOrderByClause, String strGroupByClause);

	public boolean CaseSensitive();

	/**
	 * 
	 * @param strColumnName
	 */
	public String CountOfAllValues(String strColumnName);

	/**
	 * 
	 * @param strColumnName
	 */
	public String CountOfDistinctValues(String strColumnName);

	public Fusion.DatabaseEngine DatabaseEngine();

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nHourDiff
	 */
	public String GetDayOfMonth(String strDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nHourDiff
	 */
	public String GetDayOfWeek(String strDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nHourDiff
	 */
	public String GetDayOfYear(String strDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param tableName
	 */
	public String GetDisableTriggerCommandForTable(String tableName);

	/**
	 * 
	 * @param tableName
	 */
	public String GetEnableTriggerCommandForTable(String tableName);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nHourDiff
	 */
	public String GetHour(String strDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param strDateTimeColumn
	 */
	public String GetMinutes(String strDateTimeColumn);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nHourDiff
	 */
	public String GetMonth(String strDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nHourDiff
	 */
	public String GetQuarter(String strDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param strDateTimeColumn
	 */
	public String GetSeconds(String strDateTimeColumn);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nHourDiff
	 */
	public String GetWeekOfYear(String strDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param nHourDiff
	 */
	public String GetYear(String strDateTimeColumn, int nHourDiff);

	public JoinLocation JoinClauseLocation();

	public boolean JoinRequiresColumnSelect();

	/**
	 * 
	 * @param strColumnName
	 * @param nNumOfChars
	 */
	public String Left(String strColumnName, int nNumOfChars);

	/**
	 * 
	 * @param strColumnName
	 */
	public String Lowercase(String strColumnName);

	public int MaxInClauseItems();

	public int MaxJoinTables();

	public int MaxSubQueryNesting();

	/**
	 * 
	 * @param strColumnName
	 */
	public String MaxValue(String strColumnName);

	/**
	 * 
	 * @param strColumnName
	 */
	public String MinValue(String strColumnName);

	/**
	 * 
	 * @param dtStartDateTime
	 * @param strEndDateTimeColumn
	 * @param nHourDiff
	 */
	public String NumberOfDaysBetween(DateTime dtStartDateTime, String strEndDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param dtEndDateTime
	 * @param nHourDiff
	 */
	public String NumberOfDaysBetween(String strStartDateTimeColumn, DateTime dtEndDateTime, int nHourDiff);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param strEndDateTimeColumn
	 * @param nHourDiff
	 */
	public String NumberOfDaysBetween(String strStartDateTimeColumn, String strEndDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param dtStartDateTime
	 * @param strEndDateTimeColumn
	 */
	public String NumberOfHoursBetween(DateTime dtStartDateTime, String strEndDateTimeColumn);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param dtEndDateTime
	 */
	public String NumberOfHoursBetween(String strStartDateTimeColumn, DateTime dtEndDateTime);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param strEndDateTimeColumn
	 */
	public String NumberOfHoursBetween(String strStartDateTimeColumn, String strEndDateTimeColumn);

	/**
	 * 
	 * @param dtStartDateTime
	 * @param strEndDateTimeColumn
	 */
	public String NumberOfMinutesBetween(DateTime dtStartDateTime, String strEndDateTimeColumn);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param dtEndDateTime
	 */
	public String NumberOfMinutesBetween(String strStartDateTimeColumn, DateTime dtEndDateTime);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param strEndDateTimeColumn
	 */
	public String NumberOfMinutesBetween(String strStartDateTimeColumn, String strEndDateTimeColumn);

	/**
	 * 
	 * @param dtStartDateTime
	 * @param strEndDateTimeColumn
	 * @param nHourDiff
	 */
	public String NumberOfMonthsBetween(DateTime dtStartDateTime, String strEndDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param dtEndDateTime
	 * @param nHourDiff
	 */
	public String NumberOfMonthsBetween(String strStartDateTimeColumn, DateTime dtEndDateTime, int nHourDiff);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param strEndDateTimeColumn
	 * @param nHourDiff
	 */
	public String NumberOfMonthsBetween(String strStartDateTimeColumn, String strEndDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param dtStartDateTime
	 * @param strEndDateTimeColumn
	 * @param nHourDiff
	 */
	public String NumberOfQuartersBetween(DateTime dtStartDateTime, String strEndDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param dtEndDateTime
	 * @param nHourDiff
	 */
	public String NumberOfQuartersBetween(String strStartDateTimeColumn, DateTime dtEndDateTime, int nHourDiff);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param strEndDateTimeColumn
	 * @param nHourDiff
	 */
	public String NumberOfQuartersBetween(String strStartDateTimeColumn, String strEndDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param dtStartDateTime
	 * @param strEndDateTimeColumn
	 */
	public String NumberOfSecondsBetween(DateTime dtStartDateTime, String strEndDateTimeColumn);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param dtEndDateTime
	 */
	public String NumberOfSecondsBetween(String strStartDateTimeColumn, DateTime dtEndDateTime);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param strEndDateTimeColumn
	 */
	public String NumberOfSecondsBetween(String strStartDateTimeColumn, String strEndDateTimeColumn);

	/**
	 * 
	 * @param dtStartDateTime
	 * @param strEndDateTimeColumn
	 * @param nHourDiff
	 */
	public String NumberOfWeeksBetween(DateTime dtStartDateTime, String strEndDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param dtEndDateTime
	 * @param nHourDiff
	 */
	public String NumberOfWeeksBetween(String strStartDateTimeColumn, DateTime dtEndDateTime, int nHourDiff);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param strEndDateTimeColumn
	 * @param nHourDiff
	 */
	public String NumberOfWeeksBetween(String strStartDateTimeColumn, String strEndDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param dtStartDateTime
	 * @param strEndDateTimeColumn
	 * @param nHourDiff
	 */
	public String NumberOfYearsBetween(DateTime dtStartDateTime, String strEndDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param dtEndDateTime
	 * @param nHourDiff
	 */
	public String NumberOfYearsBetween(String strStartDateTimeColumn, DateTime dtEndDateTime, int nHourDiff);

	/**
	 * 
	 * @param strStartDateTimeColumn
	 * @param strEndDateTimeColumn
	 * @param nHourDiff
	 */
	public String NumberOfYearsBetween(String strStartDateTimeColumn, String strEndDateTimeColumn, int nHourDiff);

	/**
	 * 
	 * @param strColumnName
	 * @param nNumOfChars
	 */
	public String Right(String strColumnName, int nNumOfChars);

	/**
	 * 
	 * @param strColumnName
	 * @param nDecimalPlaces
	 */
	public String Round(String strColumnName, int nDecimalPlaces);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param eOperator
	 * @param dtDateToSearchFor
	 */
	public String SearchByDateOnly(String strDateTimeColumn, Operators eOperator, DateTime dtDateToSearchFor);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param eOperator
	 * @param strDateTimeColumnToCompare
	 * @param nHourDiff
	 */
	public String SearchByDateOnly(String strDateTimeColumn, Operators eOperator, String strDateTimeColumnToCompare, int nHourDiff);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param eOperator
	 * @param n4DigitYear
	 * @param nMonth
	 * @param nDay
	 */
	public String SearchByDateOnly(String strDateTimeColumn, Operators eOperator, int n4DigitYear, int nMonth, int nDay);

	/**
	 * 
	 * @param strMemoColumn
	 * @param bUnicode
	 */
	public String SearchByMemo(String strMemoColumn, boolean bUnicode);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param eOperator
	 * @param dtTimeToSearchFor
	 */
	public String SearchByTimeOnly(String strDateTimeColumn, Operators eOperator, DateTime dtTimeToSearchFor);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param eOperator
	 * @param nHour
	 */
	public String SearchByTimeOnly(String strDateTimeColumn, Operators eOperator, int nHour);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param eOperator
	 * @param strDateTimeColumnToCompare
	 */
	public String SearchByTimeOnly(String strDateTimeColumn, Operators eOperator, String strDateTimeColumnToCompare);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param eOperator
	 * @param nHour
	 * @param nMinutes
	 */
	public String SearchByTimeOnly(String strDateTimeColumn, Operators eOperator, int nHour, int nMinutes);

	/**
	 * 
	 * @param strDateTimeColumn
	 * @param eOperator
	 * @param nHour
	 * @param nMinutes
	 * @param nSeconds
	 */
	public String SearchByTimeOnly(String strDateTimeColumn, Operators eOperator, int nHour, int nMinutes, int nSeconds);

	/**
	 * 
	 * @param bBetween
	 * @param strDateColumn
	 * @param dtStartDate
	 * @param dtEndDate
	 */
	public String SearchForDateBetween(boolean bBetween, String strDateColumn, DateTime dtStartDate, DateTime dtEndDate);

	/**
	 * 
	 * @param bBetween
	 * @param dtDateToCompare
	 * @param strStartDateColumn
	 * @param strEndDateColumn
	 * @param nHourDiff
	 */
	public String SearchForDateBetween(boolean bBetween, DateTime dtDateToCompare, String strStartDateColumn, String strEndDateColumn, int nHourDiff);

	/**
	 * 
	 * @param bBetween
	 * @param strDateColumn
	 * @param dtStartDate
	 * @param strEndDateColumn
	 * @param nHourDiff
	 */
	public String SearchForDateBetween(boolean bBetween, String strDateColumn, DateTime dtStartDate, String strEndDateColumn, int nHourDiff);

	/**
	 * 
	 * @param bBetween
	 * @param strDateColumn
	 * @param strStartDateColumn
	 * @param dtEndDate
	 * @param nHourDiff
	 */
	public String SearchForDateBetween(boolean bBetween, String strDateColumn, String strStartDateColumn, DateTime dtEndDate, int nHourDiff);

	/**
	 * 
	 * @param bBetween
	 * @param strDateColumn
	 * @param strStartDateColumn
	 * @param strEndDateColumn
	 * @param nHourDiff
	 */
	public String SearchForDateBetween(boolean bBetween, String strDateColumn, String strStartDateColumn, String strEndDateColumn, int nHourDiff);

	/**
	 * 
	 * @param bBetween
	 * @param dtTimeToCompare
	 * @param strStartTimeColumn
	 * @param strEndTimeColumn
	 */
	public String SearchForTimeBetween(boolean bBetween, DateTime dtTimeToCompare, String strStartTimeColumn, String strEndTimeColumn);

	/**
	 * 
	 * @param bBetween
	 * @param strTimeColumn
	 * @param dtStartTime
	 * @param dtEndTime
	 */
	public String SearchForTimeBetween(boolean bBetween, String strTimeColumn, DateTime dtStartTime, DateTime dtEndTime);

	/**
	 * 
	 * @param bBetween
	 * @param strTimeColumn
	 * @param dtStartTime
	 * @param strEndTimeColumn
	 */
	public String SearchForTimeBetween(boolean bBetween, String strTimeColumn, DateTime dtStartTime, String strEndTimeColumn);

	/**
	 * 
	 * @param bBetween
	 * @param strTimeColumn
	 * @param strStartTimeColumn
	 * @param dtEndTime
	 */
	public String SearchForTimeBetween(boolean bBetween, String strTimeColumn, String strStartTimeColumn, DateTime dtEndTime);

	/**
	 * 
	 * @param bBetween
	 * @param strTimeColumn
	 * @param strStartTimeColumn
	 * @param strEndTimeColumn
	 */
	public String SearchForTimeBetween(boolean bBetween, String strTimeColumn, String strStartTimeColumn, String strEndTimeColumn);

	public boolean StoreBooleanAsInt();

	/**
	 * 
	 * @param strColumnName
	 * @param nStartingPosition
	 * @param nLength
	 */
	public String Substring(String strColumnName, int nStartingPosition, int nLength);

	/**
	 * 
	 * @param strColumnName
	 */
	public String SumOfAllValues(String strColumnName);

	/**
	 * 
	 * @param strColumnName
	 */
	public String SumOfDistinctValues(String strColumnName);

	/**
	 * 
	 * @param engine
	 */
	public boolean SupportsExternalSource(Fusion.DatabaseEngine engine);

	/**
	 * 
	 * @param dbConnExternal
	 */
	public boolean SupportsExternalSource(Object dbConnExternal);

	public boolean SupportsTInDataTime();

	public boolean SupportsTop();

	/**
	 * 
	 * @param strColumnName
	 */
	public String TrimLeftSpaces(String strColumnName);

	/**
	 * 
	 * @param strColumnName
	 */
	public String TrimRightSpaces(String strColumnName);

	/**
	 * 
	 * @param strColumnName
	 */
	public String TrimSpaces(String strColumnName);

	/**
	 * 
	 * @param strColumnName
	 */
	public String Uppercase(String strColumnName);

}