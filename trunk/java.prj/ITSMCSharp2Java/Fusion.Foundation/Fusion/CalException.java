package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:48
 */
public class CalException {

	private boolean m_bDeleted;
	private CalendarInfo m_oModifiedAppt;
	private DateTime m_originalStartDate;

	public CalException(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param deletedDate
	 */
	public CalException(DateTime deletedDate){

	}

	/**
	 * 
	 * @param modifiedDate
	 * @param modifiedAppt
	 */
	public CalException(DateTime modifiedDate, CalendarInfo modifiedAppt){

	}

	public boolean IsDeleted(){
		return null;
	}

	public CalendarInfo ModifiedAppt(){
		return null;
	}

	public DateTime OriginalStartDate(){
		return null;
	}

}