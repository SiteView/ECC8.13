package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:50
 */
public class CalRecurrencePattern extends PersistenceInfo {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:50
	 */
	public enum InstanceEnum {
		First,
		Second,
		Third,
		Fourth,
		Last
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:50
	 */
	public enum RecurrenceTypeEnum {
		RecursDaily,
		RecursMonthly,
		RecursMonthNth,
		RecursWeekly,
		RecursYearly,
		RecursYearNth
	}

	private ArrayList m_arrExceptions = new ArrayList();
	private boolean m_bNoEndDate;
	private InstanceEnum m_eInstance;
	private RecurrenceTypeEnum m_eRecurrenceType;
	private int m_nDayOfMonth;
	private int m_nInterval;
	private int m_nMonthOfYear;
	private int m_nOccurrences;
	private DayFlags m_oDayOfWeekMask;
	private DateTime m_oPatternEndDate;
	private DateTime m_oPatternStartDate;

	public CalRecurrencePattern(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param recurrenceType
	 */
	public CalRecurrencePattern(RecurrenceTypeEnum recurrenceType){

	}

	public String AnnotationGroup(){
		return "";
	}

	/**
	 * 
	 * @param validTypes
	 */
	private void CheckRecurrenceValidity(RecurrenceTypeEnum[] validTypes){

	}

	public int DayOfMonth(){
		return 0;
	}

	public DayFlags DayOfWeekMask(){
		return null;
	}

	public InstanceEnum Instance(){
		return null;
	}

	public int Interval(){
		return 0;
	}

	public boolean IsValid(){
		return null;
	}

	public int MonthOfYear(){
		return 0;
	}

	public boolean NoEndDate(){
		return null;
	}

	public int Occurrences(){
		return 0;
	}

	public DateTime PatternEndDateTime(){
		return null;
	}

	public DateTime PatternStartDateTime(){
		return null;
	}

	public ArrayList RecurrenceExceptions(){
		return null;
	}

	public RecurrenceTypeEnum RecurrenceType(){
		return null;
	}

}