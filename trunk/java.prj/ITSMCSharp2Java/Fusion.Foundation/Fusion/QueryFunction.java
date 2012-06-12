package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:38
 */
public class QueryFunction {

	private XmlDocument m_xdQueries = null;
	private int NotSpecified = -1;

	public QueryFunction(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param xd
	 */
	public QueryFunction(XmlDocument xd){

	}

	/**
	 * 
	 * @param xeSubFunction
	 * @param nNumDays
	 */
	public XmlElement AddDays(XmlElement xeSubFunction, int nNumDays){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 * @param nNumDays
	 */
	public XmlElement AddDays(ValueSources eValueType, String strValue, int nNumDays){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 * @param nNumHours
	 */
	public XmlElement AddHours(XmlElement xeSubFunction, int nNumHours){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 * @param nNumHours
	 */
	public XmlElement AddHours(ValueSources eValueType, String strValue, int nNumHours){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 * @param nNumMinutes
	 */
	public XmlElement AddMinutes(XmlElement xeSubFunction, int nNumMinutes){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 * @param nNumMinutes
	 */
	public XmlElement AddMinutes(ValueSources eValueType, String strValue, int nNumMinutes){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 * @param nNumMonths
	 */
	public XmlElement AddMonths(XmlElement xeSubFunction, int nNumMonths){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 * @param nNumMonths
	 */
	public XmlElement AddMonths(ValueSources eValueType, String strValue, int nNumMonths){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 * @param nNumQuarters
	 */
	public XmlElement AddQuarters(XmlElement xeSubFunction, int nNumQuarters){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 * @param nNumQuarters
	 */
	public XmlElement AddQuarters(ValueSources eValueType, String strValue, int nNumQuarters){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 * @param nNumSeconds
	 */
	public XmlElement AddSeconds(XmlElement xeSubFunction, int nNumSeconds){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 * @param nNumSeconds
	 */
	public XmlElement AddSeconds(ValueSources eValueType, String strValue, int nNumSeconds){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 * @param nNumYears
	 */
	public XmlElement AddYears(XmlElement xeSubFunction, int nNumYears){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 * @param nNumYears
	 */
	public XmlElement AddYears(ValueSources eValueType, String strValue, int nNumYears){
		return null;
	}

	/**
	 * 
	 * @param strFieldName
	 */
	public XmlElement AverageAllValues(String strFieldName){
		return null;
	}

	/**
	 * 
	 * @param strFieldName
	 */
	public XmlElement AverageDistinctValues(String strFieldName){
		return null;
	}

	/**
	 * 
	 * @param strFunctionName
	 * @param nNumber
	 * @param xeSubFunction
	 */
	private XmlElement BuildFunctionToIncrementDateTime(String strFunctionName, int nNumber, XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param strFunctionName
	 * @param nNumber
	 * @param eValueType
	 * @param strValue
	 */
	private XmlElement BuildFunctionToIncrementDateTime(String strFunctionName, int nNumber, ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strFunctionName
	 * @param eValueType1
	 * @param strValue1
	 * @param eValueType2
	 * @param strValue2
	 */
	private XmlElement BuildFunctionWithStartEndDateTimes(String strFunctionName, ValueSources eValueType1, String strValue1, ValueSources eValueType2, String strValue2){
		return null;
	}

	public XmlElement CountOfAllValues(){
		return null;
	}

	/**
	 * 
	 * @param strFieldName
	 */
	public XmlElement CountOfAllValues(String strFieldName){
		return null;
	}

	/**
	 * 
	 * @param strFieldName
	 */
	public XmlElement CountOfDistinctValues(String strFieldName){
		return null;
	}

	/**
	 * 
	 * @param strFunctionName
	 * @param xeSubFunction
	 */
	public XmlElement CreateFunctionWithSubfunction(String strFunctionName, XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param strFunctionName
	 * @param eValueType
	 * @param strValue
	 */
	private XmlElement CreateFunctionWithValueField(String strFunctionName, ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement GetDayOfMonth(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement GetDayOfMonth(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement GetDayOfWeek(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement GetDayOfWeek(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement GetDayOfYear(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement GetDayOfYear(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeFunction
	 */
	public QueryFunctions GetFunctionType(XmlElement xeFunction){
		return null;
	}

	/**
	 * 
	 * @param xeFunction
	 * @param eValueType
	 * @param strValue
	 */
	public void GetFunctionValue(XmlElement xeFunction, ValueSources eValueType, String strValue){

	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement GetHour(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement GetHour(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement GetMinutes(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement GetMinutes(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement GetMonth(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement GetMonth(ValueSources eValueType, String strValue){
		return null;
	}

	public int getNotSpecified(){
		return NotSpecified;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement GetQuarter(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement GetQuarter(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param eQueryFunction
	 */
	public QueryFunctionInputTypes GetQueryFunctionInputTypes(QueryFunctions eQueryFunction){
		return null;
	}

	/**
	 * 
	 * @param eQueryFunction
	 */
	public QueryFunctionReturnType GetQueryFunctionReturnType(QueryFunctions eQueryFunction){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement GetSeconds(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement GetSeconds(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeFunction
	 * @param eStartValueType
	 * @param strStartDateTimeValue
	 * @param eEndValueType
	 * @param strEndDateTimeValue
	 */
	private void GetStartEndDateTimeValues(XmlElement xeFunction, ValueSources eStartValueType, String strStartDateTimeValue, ValueSources eEndValueType, String strEndDateTimeValue){

	}

	/**
	 * 
	 * @param xeFunction
	 */
	public XmlElement GetSubfunctionOrValue(XmlElement xeFunction){
		return null;
	}

	/**
	 * 
	 * @param xeValue
	 * @param eValueType
	 * @param strValue
	 */
	private void GetValueTagData(XmlElement xeValue, ValueSources eValueType, String strValue){

	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement GetWeekOfYear(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement GetWeekOfYear(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement GetYear(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement GetYear(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param eQueryFunction
	 */
	public boolean IsAggregateFunction(QueryFunctions eQueryFunction){
		return null;
	}

	/**
	 * 
	 * @param strFunction
	 */
	public boolean IsAggregateFunction(String strFunction){
		return null;
	}

	/**
	 * 
	 * @param xeFunction
	 */
	public boolean IsAggregateFunction(XmlElement xeFunction){
		return null;
	}

	/**
	 * 
	 * @param eQueryFunction
	 */
	public boolean IsQueryFunctionAllowedInSelectClause(QueryFunctions eQueryFunction){
		return null;
	}

	/**
	 * 
	 * @param strQueryFunction
	 */
	public boolean IsQueryFunctionAllowedInSelectClause(String strQueryFunction){
		return null;
	}

	/**
	 * 
	 * @param xeFunction
	 */
	public boolean IsQueryFunctionAllowedInSelectClause(XmlElement xeFunction){
		return null;
	}

	/**
	 * 
	 * @param eQueryFunction
	 */
	public boolean IsQueryFunctionAllowedInWhereClause(QueryFunctions eQueryFunction){
		return null;
	}

	/**
	 * 
	 * @param strQueryFunction
	 */
	public boolean IsQueryFunctionAllowedInWhereClause(String strQueryFunction){
		return null;
	}

	/**
	 * 
	 * @param xeFunction
	 */
	public boolean IsQueryFunctionAllowedInWhereClause(XmlElement xeFunction){
		return null;
	}

	/**
	 * 
	 * @param xeFunctionOrValue
	 */
	public boolean IsValue(XmlElement xeFunctionOrValue){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 * @param nNumChars
	 */
	public XmlElement Left(XmlElement xeSubFunction, int nNumChars){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 * @param nNumChars
	 */
	public XmlElement Left(ValueSources eValueType, String strValue, int nNumChars){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement Lowercase(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement Lowercase(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strFieldName
	 */
	public XmlElement MaxValue(String strFieldName){
		return null;
	}

	/**
	 * 
	 * @param strFieldName
	 */
	public XmlElement MinValue(String strFieldName){
		return null;
	}

	/**
	 * 
	 * @param eStartValueType
	 * @param strStartValue
	 * @param eEndValueType
	 * @param strEndValue
	 */
	public XmlElement NumberOfDaysBetween(ValueSources eStartValueType, String strStartValue, ValueSources eEndValueType, String strEndValue){
		return null;
	}

	/**
	 * 
	 * @param eStartValueType
	 * @param strStartValue
	 * @param eEndValueType
	 * @param strEndValue
	 */
	public XmlElement NumberOfHoursBetween(ValueSources eStartValueType, String strStartValue, ValueSources eEndValueType, String strEndValue){
		return null;
	}

	/**
	 * 
	 * @param eStartValueType
	 * @param strStartValue
	 * @param eEndValueType
	 * @param strEndValue
	 */
	public XmlElement NumberOfMinutesBetween(ValueSources eStartValueType, String strStartValue, ValueSources eEndValueType, String strEndValue){
		return null;
	}

	/**
	 * 
	 * @param eStartValueType
	 * @param strStartValue
	 * @param eEndValueType
	 * @param strEndValue
	 */
	public XmlElement NumberOfMonthsBetween(ValueSources eStartValueType, String strStartValue, ValueSources eEndValueType, String strEndValue){
		return null;
	}

	/**
	 * 
	 * @param eStartValueType
	 * @param strStartValue
	 * @param eEndValueType
	 * @param strEndValue
	 */
	public XmlElement NumberOfQuartersBetween(ValueSources eStartValueType, String strStartValue, ValueSources eEndValueType, String strEndValue){
		return null;
	}

	/**
	 * 
	 * @param eStartValueType
	 * @param strStartValue
	 * @param eEndValueType
	 * @param strEndValue
	 */
	public XmlElement NumberOfSecondsBetween(ValueSources eStartValueType, String strStartValue, ValueSources eEndValueType, String strEndValue){
		return null;
	}

	/**
	 * 
	 * @param eStartValueType
	 * @param strStartValue
	 * @param eEndValueType
	 * @param strEndValue
	 */
	public XmlElement NumberOfWeeksBetween(ValueSources eStartValueType, String strStartValue, ValueSources eEndValueType, String strEndValue){
		return null;
	}

	/**
	 * 
	 * @param eStartValueType
	 * @param strStartValue
	 * @param eEndValueType
	 * @param strEndValue
	 */
	public XmlElement NumberOfYearsBetween(ValueSources eStartValueType, String strStartValue, ValueSources eEndValueType, String strEndValue){
		return null;
	}

	/**
	 * 
	 * @param eQueryFunction
	 */
	public static String QueryFunctionToString(QueryFunctions eQueryFunction){
		return "";
	}

	/**
	 * 
	 * @param xeSubFunction
	 * @param nNumChars
	 */
	public XmlElement Right(XmlElement xeSubFunction, int nNumChars){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 * @param nNumChars
	 */
	public XmlElement Right(ValueSources eValueType, String strValue, int nNumChars){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 * @param nDecimalPlaces
	 */
	public XmlElement Round(ValueSources eValueType, String strValue, int nDecimalPlaces){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement SearchByDateOnly(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement SearchByDateOnly(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement SearchByTimeOnly(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement SearchByTimeOnly(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNotSpecified(int newVal){
		NotSpecified = newVal;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement SingleValue(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strQueryFunction
	 */
	public static QueryFunctions StringToQueryFunction(String strQueryFunction){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 * @param nStartPosition
	 * @param nNumChars
	 */
	public XmlElement Substring(XmlElement xeSubFunction, int nStartPosition, int nNumChars){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 * @param nStartPosition
	 * @param nNumChars
	 */
	public XmlElement Substring(ValueSources eValueType, String strValue, int nStartPosition, int nNumChars){
		return null;
	}

	/**
	 * 
	 * @param strFieldName
	 */
	public XmlElement SumOfAllValues(String strFieldName){
		return null;
	}

	/**
	 * 
	 * @param strFieldName
	 */
	public XmlElement SumOfDistinctValues(String strFieldName){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement TrimLeftSpaces(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement TrimLeftSpaces(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement TrimRightSpaces(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement TrimRightSpaces(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement TrimSpaces(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement TrimSpaces(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeSubFunction
	 */
	public XmlElement Uppercase(XmlElement xeSubFunction){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 * @param strValue
	 */
	public XmlElement Uppercase(ValueSources eValueType, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeFunction
	 * @param nNumDays
	 */
	public void ValuesForAddDays(XmlElement xeFunction, int nNumDays){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param nNumHours
	 */
	public void ValuesForAddHours(XmlElement xeFunction, int nNumHours){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param nNumMinutes
	 */
	public void ValuesForAddMinutes(XmlElement xeFunction, int nNumMinutes){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param nNumMonths
	 */
	public void ValuesForAddMonths(XmlElement xeFunction, int nNumMonths){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param nNumQuarters
	 */
	public void ValuesForAddQuarters(XmlElement xeFunction, int nNumQuarters){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param nNumSeconds
	 */
	public void ValuesForAddSeconds(XmlElement xeFunction, int nNumSeconds){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param nNumYears
	 */
	public void ValuesForAddYears(XmlElement xeFunction, int nNumYears){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param nNumChars
	 */
	public void ValuesForLeft(XmlElement xeFunction, int nNumChars){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param eStartValueType
	 * @param strStartDateTimeValue
	 * @param eEndValueType
	 * @param strEndDateTimeValue
	 */
	public void ValuesForNumberOfDaysBetween(XmlElement xeFunction, ValueSources eStartValueType, String strStartDateTimeValue, ValueSources eEndValueType, String strEndDateTimeValue){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param eStartValueType
	 * @param strStartDateTimeValue
	 * @param eEndValueType
	 * @param strEndDateTimeValue
	 */
	public void ValuesForNumberOfHoursBetween(XmlElement xeFunction, ValueSources eStartValueType, String strStartDateTimeValue, ValueSources eEndValueType, String strEndDateTimeValue){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param eStartValueType
	 * @param strStartDateTimeValue
	 * @param eEndValueType
	 * @param strEndDateTimeValue
	 */
	public void ValuesForNumberOfMinutesBetween(XmlElement xeFunction, ValueSources eStartValueType, String strStartDateTimeValue, ValueSources eEndValueType, String strEndDateTimeValue){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param eStartValueType
	 * @param strStartDateTimeValue
	 * @param eEndValueType
	 * @param strEndDateTimeValue
	 */
	public void ValuesForNumberOfMonthsBetween(XmlElement xeFunction, ValueSources eStartValueType, String strStartDateTimeValue, ValueSources eEndValueType, String strEndDateTimeValue){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param eStartValueType
	 * @param strStartDateTimeValue
	 * @param eEndValueType
	 * @param strEndDateTimeValue
	 */
	public void ValuesForNumberOfQuartersBetween(XmlElement xeFunction, ValueSources eStartValueType, String strStartDateTimeValue, ValueSources eEndValueType, String strEndDateTimeValue){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param eStartValueType
	 * @param strStartDateTimeValue
	 * @param eEndValueType
	 * @param strEndDateTimeValue
	 */
	public void ValuesForNumberOfSecondsBetween(XmlElement xeFunction, ValueSources eStartValueType, String strStartDateTimeValue, ValueSources eEndValueType, String strEndDateTimeValue){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param eStartValueType
	 * @param strStartDateTimeValue
	 * @param eEndValueType
	 * @param strEndDateTimeValue
	 */
	public void ValuesForNumberOfWeeksBetween(XmlElement xeFunction, ValueSources eStartValueType, String strStartDateTimeValue, ValueSources eEndValueType, String strEndDateTimeValue){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param eStartValueType
	 * @param strStartDateTimeValue
	 * @param eEndValueType
	 * @param strEndDateTimeValue
	 */
	public void ValuesForNumberOfYearsBetween(XmlElement xeFunction, ValueSources eStartValueType, String strStartDateTimeValue, ValueSources eEndValueType, String strEndDateTimeValue){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param nNumChars
	 */
	public void ValuesForRight(XmlElement xeFunction, int nNumChars){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param nDecimalPlaces
	 */
	public void ValuesForRound(XmlElement xeFunction, int nDecimalPlaces){

	}

	/**
	 * 
	 * @param xeFunction
	 * @param nStartPosition
	 * @param nNumChars
	 */
	public void ValuesForSubstring(XmlElement xeFunction, int nStartPosition, int nNumChars){

	}

}