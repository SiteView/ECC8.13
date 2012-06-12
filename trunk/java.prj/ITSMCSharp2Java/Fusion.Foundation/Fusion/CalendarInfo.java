package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:47
 */
public class CalendarInfo extends DataTransport {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:47
	 */
	public enum CalendarInfoStateEnum {
		New,
		Modified,
		Deleted
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:48
	 */
	public enum MeetingAction {
		Accept,
		Decline,
		Tentative
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:48
	 */
	public class ProblemReport {

		private boolean IsValid;
		private ArrayList ProblemFields;

		public ProblemReport(){

		}

		public void finalize() throws Throwable {

		}

		public boolean getIsValid(){
			return IsValid;
		}

		public ArrayList getProblemFields(){
			return ProblemFields;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setIsValid(boolean newVal){
			IsValid = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setProblemFields(ArrayList newVal){
			ProblemFields = newVal;
		}

	}

	private boolean m_bIsAllDayEvent = false;
	private boolean m_bIsMeeting = false;
	private boolean m_bIsPublicFolder = true;
	private boolean m_bReminder = false;
	private DateTime m_endDateTime;
	private CalendarInfoStateEnum m_enumCalendarInfoState = CalendarInfoStateEnum.New;
	private MeetingAction m_meetingAction = MeetingAction.Tentative;
	private int m_nDuration = 0;
	private int m_nReminderMinutesBeforeStart = 0;
	private DateTime m_startDateTime;
	private String m_strCategory = "";
	private String m_strDescription = "";
	private String m_strMeetingLocation = "";
	private String m_strPublicFolder = "";
	private String m_strRecipientName = "";



	public void finalize() throws Throwable {
		super.finalize();
	}

	public CalendarInfo(){

	}

	public MeetingAction Action(){
		return null;
	}

	public String AnnotationGroup(){
		return "";
	}

	public CalendarInfoStateEnum CalendarInfoState(){
		return null;
	}

	public String Category(){
		return "";
	}

	public String Description(){
		return "";
	}

	public int Duration(){
		return 0;
	}

	public DateTime EndDateTime(){
		return null;
	}

	public boolean IsAllDayEvent(){
		return null;
	}

	public boolean IsMeeting(){
		return null;
	}

	public boolean IsPublicFolder(){
		return null;
	}

	public LinkToBusOb LinkedTo(){
		return null;
	}

	public String MeetingLocation(){
		return "";
	}

	public String PublicFolder(){
		return "";
	}

	public String RecipientName(){
		return "";
	}

	public boolean Reminder(){
		return null;
	}

	public int ReminderMinutesBeforeStart(){
		return 0;
	}

	public DateTime StartDateTime(){
		return null;
	}

	public ProblemReport Validate(){
		return null;
	}

}