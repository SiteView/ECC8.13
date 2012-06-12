package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-����-2010 14:35:05
 */
public class SendCalendarActionDef extends ActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-����-2010 14:35:05
	 */
	private class Tags {

		private String Body = "Body";
		private String Category = "Category";
		private String ContentType = "ContentType";
		private String EndDateTime = "EndDateTime";
		private String FolderType = "FolderType";
		private String LinkRelName = "LinkRelName";
		private String LinkType = "LinkType";
		private String PublicFolder = "PublicFolder";
		private String RunProgramDetails = "SendCalendarDetails";
		private String SendCalendarActionDef = "SendCalendarActionDef";
		private String SendImmediately = "SendImmediately";
		private String SendRtf = "SendRtf";
		private String StartDateTime = "StartDateTime";
		private String Subject = "Subject";
		private String To = "To";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getBody(){
			return Body;
		}

		public String getCategory(){
			return Category;
		}

		public String getContentType(){
			return ContentType;
		}

		public String getEndDateTime(){
			return EndDateTime;
		}

		public String getFolderType(){
			return FolderType;
		}

		public String getLinkRelName(){
			return LinkRelName;
		}

		public String getLinkType(){
			return LinkType;
		}

		public String getPublicFolder(){
			return PublicFolder;
		}

		public String getRunProgramDetails(){
			return RunProgramDetails;
		}

		public String getSendCalendarActionDef(){
			return SendCalendarActionDef;
		}

		public String getSendImmediately(){
			return SendImmediately;
		}

		public String getSendRtf(){
			return SendRtf;
		}

		public String getStartDateTime(){
			return StartDateTime;
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
		public void setBody(String newVal){
			Body = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCategory(String newVal){
			Category = newVal;
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
		public void setEndDateTime(String newVal){
			EndDateTime = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFolderType(String newVal){
			FolderType = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLinkRelName(String newVal){
			LinkRelName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLinkType(String newVal){
			LinkType = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPublicFolder(String newVal){
			PublicFolder = newVal;
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
		public void setSendCalendarActionDef(String newVal){
			SendCalendarActionDef = newVal;
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
		public void setStartDateTime(String newVal){
			StartDateTime = newVal;
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

	private int CONTENTTYPE_HTML = 2;
	private int CONTENTTYPE_PLAIN = 0;
	private int CONTENTTYPE_RTF = 1;
	private int FOLDERTYPE_PUBLIC = 1;
	private int FOLDERTYPE_RECIPIENT = 0;
	private int LINKTYPE_CHILD = 2;
	private int LINKTYPE_MASTER = 1;
	private int LINKTYPE_NONE = 0;
	private boolean m_bSendImmediately = true;
	private boolean m_bSendRtf = false;
	private int m_iContentType = 0;
	private int m_iFolderType = 1;
	private int m_iLinkType = 0;
	private String m_strBody = "";
	private String m_strCategory = "";
	private String m_strEndDateTime = "";
	private String m_strFrom = "";
	private String m_strLinkRelName = "";
	private String m_strPublicFolder = "";
	private String m_strStartDateTime = "";
	private String m_strSubject = "";
	private String m_strTo = "";

	public SendCalendarActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
		return "";
	}

	public String Body(){
		return "";
	}

	public String Category(){
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

	public String EndDateTime(){
		return "";
	}

	public int FolderType(){
		return 0;
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

	public int getCONTENTTYPE_HTML(){
		return CONTENTTYPE_HTML;
	}

	public int getCONTENTTYPE_PLAIN(){
		return CONTENTTYPE_PLAIN;
	}

	public int getCONTENTTYPE_RTF(){
		return CONTENTTYPE_RTF;
	}

	public int getFOLDERTYPE_PUBLIC(){
		return FOLDERTYPE_PUBLIC;
	}

	public int getFOLDERTYPE_RECIPIENT(){
		return FOLDERTYPE_RECIPIENT;
	}

	public int getLINKTYPE_CHILD(){
		return LINKTYPE_CHILD;
	}

	public int getLINKTYPE_MASTER(){
		return LINKTYPE_MASTER;
	}

	public int getLINKTYPE_NONE(){
		return LINKTYPE_NONE;
	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public boolean HasTagsContainingTagCategory(String strTagCategoryName){
		return null;
	}

	public String LinkRelName(){
		return "";
	}

	public int LinkType(){
		return 0;
	}

	public String PublicFolder(){
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

	/**
	 * 
	 * @param newVal
	 */
	public void setFOLDERTYPE_PUBLIC(int newVal){
		FOLDERTYPE_PUBLIC = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFOLDERTYPE_RECIPIENT(int newVal){
		FOLDERTYPE_RECIPIENT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLINKTYPE_CHILD(int newVal){
		LINKTYPE_CHILD = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLINKTYPE_MASTER(int newVal){
		LINKTYPE_MASTER = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLINKTYPE_NONE(int newVal){
		LINKTYPE_NONE = newVal;
	}

	public String StartDateTime(){
		return "";
	}

	public String Subject(){
		return "";
	}

	public String To(){
		return "";
	}

}