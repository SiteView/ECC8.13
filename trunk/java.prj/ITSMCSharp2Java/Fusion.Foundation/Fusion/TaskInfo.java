package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:39
 */
public class TaskInfo extends DataTransport {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:39
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

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:40
	 */
	public enum StatusEnum {
		NotStarted,
		InProgress,
		Completed,
		WaitingOnSomeoneElse,
		Deferred
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:40
	 */
	public enum TaskInfoStateEnum {
		New,
		Modified,
		Deleted
	}

	private boolean m_bIsPublicFolder = true;
	private boolean m_bReminder = false;
	private DateTime m_dueDateTime;
	private TaskInfoStateEnum m_enumTaskInfoState = TaskInfoStateEnum.New;
	private int m_nPercent = 0;
	private int m_nReminderMinutesBeforeStart = 0;
	private DateTime m_startDateTime;
	private StatusEnum m_Status = StatusEnum.NotStarted;
	private String m_strCategory = "";
	private String m_strDescription = "";
	private String m_strOwner = "";
	private String m_strPublicFolder = "";
	private String m_strRecipientName = "";



	public void finalize() throws Throwable {
		super.finalize();
	}

	public TaskInfo(){

	}

	public String AnnotationGroup(){
		return "";
	}

	public String Category(){
		return "";
	}

	public String Description(){
		return "";
	}

	public DateTime DueDateTime(){
		return null;
	}

	public boolean IsPublicFolder(){
		return null;
	}

	public LinkToBusOb LinkedTo(){
		return null;
	}

	public String Owner(){
		return "";
	}

	public int Percent(){
		return 0;
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

	public StatusEnum Status(){
		return null;
	}

	public TaskInfoStateEnum TaskInfoState(){
		return null;
	}

	public ProblemReport Validate(){
		return null;
	}

}