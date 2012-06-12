package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:48
 */
public class CalendarSet extends PersistenceInfo {

	private CalendarInfo m_oMasterAppointment;
	private CalRecurrencePattern m_oRecurrencePattern = null;

	public CalendarSet(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param masterAppointment
	 */
	public CalendarSet(CalendarInfo masterAppointment){

	}

	public boolean IsRecurring(){
		return null;
	}

	public CalendarInfo MasterAppointment(){
		return null;
	}

	public CalRecurrencePattern RecurrencePattern(){
		return null;
	}

}