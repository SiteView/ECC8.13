package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:07
 */
public class SendEmailActionDef extends ActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:07
	 */
	private class Tags {

		private String AttachDirName = "AttachDirName";
		private String AttachFilter = "AttachFilter";
		private String AttachRelName = "AttachRelName";
		private String AttachType = "AttachType";
		private String Bcc = "Bcc";
		private String Body = "Body";
		private String Cc = "Cc";
		private String ContentType = "ContentType";
		private String ReplyTo = "ReplyTo";
		private String RunProgramDetails = "SendEmailDetails";
		private String SendEmailActionDef = "SendEmailActionDef";
		private String SendImmediately = "SendImmediately";
		private String SendRtf = "SendRtf";
		private String Subject = "Subject";
		private String To = "To";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAttachDirName(){
			return AttachDirName;
		}

		public String getAttachFilter(){
			return AttachFilter;
		}

		public String getAttachRelName(){
			return AttachRelName;
		}

		public String getAttachType(){
			return AttachType;
		}

		public String getBcc(){
			return Bcc;
		}

		public String getBody(){
			return Body;
		}

		public String getCc(){
			return Cc;
		}

		public String getContentType(){
			return ContentType;
		}

		public String getReplyTo(){
			return ReplyTo;
		}

		public String getRunProgramDetails(){
			return RunProgramDetails;
		}

		public String getSendEmailActionDef(){
			return SendEmailActionDef;
		}

		public String getSendImmediately(){
			return SendImmediately;
		}

		public String getSendRtf(){
			return SendRtf;
		}

		public String getSubject(){
			return Subject;
		}

		public String getTo(){
			return To;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAttachDirName(String newVal){
			AttachDirName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAttachFilter(String newVal){
			AttachFilter = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAttachRelName(String newVal){
			AttachRelName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAttachType(String newVal){
			AttachType = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBcc(String newVal){
			Bcc = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBody(String newVal){
			Body = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCc(String newVal){
			Cc = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setContentType(String newVal){
			ContentType = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setReplyTo(String newVal){
			ReplyTo = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRunProgramDetails(String newVal){
			RunProgramDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSendEmailActionDef(String newVal){
			SendEmailActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSendImmediately(String newVal){
			SendImmediately = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSendRtf(String newVal){
			SendRtf = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSubject(String newVal){
			Subject = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTo(String newVal){
			To = newVal;
		}

	}

	private int ATTACHTYPE_FROMDIR = 2;
	private int ATTACHTYPE_FROMREL = 1;
	private int ATTACHTYPE_NONE = 0;
	private int CONTENTTYPE_HTML = 2;
	private int CONTENTTYPE_PLAIN = 0;
	private int CONTENTTYPE_RTF = 1;
	private boolean m_bSendImmediately = true;
	private boolean m_bSendRtf = true;
	private int m_iAttachType = 0;
	private int m_iContentType = 0;
	private String m_strAttachDirName = "";
	private String m_strAttachFilter = "*";
	private String m_strAttachRelName = "";
	private String m_strBcc = "";
	private String m_strBody = "";
	private String m_strCc = "";
	private String m_strFrom = "";
	private String m_strReplyTo = "";
	private String m_strSubject = "";
	private String m_strTo = "";

	public SendEmailActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
		return "";
	}

	public String AttachDirName(){
		return "";
	}

	public String AttachFilter(){
		return "";
	}

	public String AttachRelName(){
		return "";
	}

	public int AttachType(){
		return 0;
	}

	public String Bcc(){
		return "";
	}

	public String Body(){
		return "";
	}

	public String Cc(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public int ContentType(){
		return 0;
	}

	/**
	 * 
	 * @param def
	 * @param defOwner
	 */
	protected void CopyContents(SerializableDef def, SerializableDef defOwner){

	}

	/**
	 * 
	 * @param correction
	 * @param bJustCollect
	 * @param strAssociatedBusOb
	 */
	public boolean CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect, String strAssociatedBusOb){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public String From(){
		return "";
	}

	/**
	 * 
	 * @param list
	 */
	public void GatherPromptDefs(IList list){

	}

	public int getATTACHTYPE_FROMDIR(){
		return ATTACHTYPE_FROMDIR;
	}

	public int getATTACHTYPE_FROMREL(){
		return ATTACHTYPE_FROMREL;
	}

	public int getATTACHTYPE_NONE(){
		return ATTACHTYPE_NONE;
	}

	public int getCONTENTTYPE_HTML(){
		return CONTENTTYPE_HTML;
	}

	public int getCONTENTTYPE_PLAIN(){
		return CONTENTTYPE_PLAIN;
	}

	public int getCONTENTTYPE_RTF(){
		return CONTENTTYPE_RTF;
	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public boolean HasTagsContainingTagCategory(String strTagCategoryName){
		return null;
	}

	public String ReplyTo(){
		return "";
	}

	public boolean SendImmediately(){
		return null;
	}

	public boolean SendRtf(){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public DefSerializer Serialize(DefSerializer serial){
		return null;
	}

	public String SerializeClassName(){
		return "";
	}

	public String SerializeGeneralPropertyRoot(){
		return "";
	}

	public String SerializeSpecificPropertyRoot(){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setATTACHTYPE_FROMDIR(int newVal){
		ATTACHTYPE_FROMDIR = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setATTACHTYPE_FROMREL(int newVal){
		ATTACHTYPE_FROMREL = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setATTACHTYPE_NONE(int newVal){
		ATTACHTYPE_NONE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCONTENTTYPE_HTML(int newVal){
		CONTENTTYPE_HTML = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCONTENTTYPE_PLAIN(int newVal){
		CONTENTTYPE_PLAIN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCONTENTTYPE_RTF(int newVal){
		CONTENTTYPE_RTF = newVal;
	}

	public String Subject(){
		return "";
	}

	public String To(){
		return "";
	}

}