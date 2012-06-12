package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-四月-2010 11:37:30
 */
public class EventItem {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 22-四月-2010 11:37:30
	 */
	public class EventFieldInfo {

		private object m_newValue = null;
		private object m_oldValue = null;
		private string m_strField = string.Empty;
		private string m_strValueType = null;

		public EventFieldInfo(){

		}

		public void finalize() throws Throwable {

		}

		/**
		 * 
		 * @param sField
		 * @param oldValue
		 * @param newValue
		 */
		public EventFieldInfo(string sField, object oldValue, object newValue){

		}

		public string Field(){
			return "";
		}

		public object NewValue(){
			return null;
		}

		public object OldValue(){
			return null;
		}

		/**
		 * 
		 * @param val
		 */
		private void SetType(object val){

		}

		public string ValueType(){
			return "";
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 22-四月-2010 11:37:30
	 */
	public enum EventSource {
		RecordAdd,
		RecordUpdate,
		RecordDelete,
		FieldUpdate,
		Unknown
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 22-四月-2010 11:37:30
	 */
	public enum Queue {
		Public,
		Private
	}

	private ArrayList m_aFieldInfos;
	private bool m_bAuditingEvent;
	private bool m_bEncrypted;
	private EventSource m_eventSource;
	private Hashtable m_htBusinessRules;
	private object m_oBusOb;
	private Queue m_queueAccess;
	private string m_strBusObId;
	private string m_strBusObName;
	private string m_strEventDefId;
	private string m_strEventDefName;
	private string m_strId;
	private string m_strOwnerId;
	private string m_strOwnerName;
	private DateTime m_timeStamp;



	public void finalize() throws Throwable {

	}

	public EventItem(){

	}

	/**
	 * 
	 * @param strEventId
	 * @param strEventName
	 */
	public EventItem(string strEventId, string strEventName){

	}

	public Hashtable AssociatedBusinessRules(){
		return null;
	}

	public bool AuditingEvent(){
		return null;
	}

	public object BusinessObject(){
		return null;
	}

	public string BusObId(){
		return "";
	}

	public string BusObName(){
		return "";
	}

	public bool Encrypted(){
		return null;
	}

	public string EventDefId(){
		return "";
	}

	public string EventDefName(){
		return "";
	}

	public ArrayList FieldInfos(){
		return null;
	}

	public int FieldInfosCount(){
		return 0;
	}

	public string Id(){
		return "";
	}

	public string OwnerId(){
		return "";
	}

	public string OwnerName(){
		return "";
	}

	public Queue QueueAccess(){
		return null;
	}

	public EventSource Source(){
		return null;
	}

	public DateTime TimeStamp(){
		return null;
	}

}