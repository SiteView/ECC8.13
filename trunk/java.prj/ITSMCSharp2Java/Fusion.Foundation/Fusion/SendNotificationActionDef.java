package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:11
 */
public class SendNotificationActionDef extends ActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:11
	 */
	private class Tags {

		private String Body = "Body";
		private String Cc = "Cc";
		private String FromAddress = "FromAddress";
		private String RunProgramDetails = "SendNotificationDetails";
		private String SendImmediately = "SendImmediately";
		private String SendNotificationActionDef = "SendNotificationActionDef";
		private String SendRtf = "SendRtf";
		private String Subject = "Subject";
		private String To = "To";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getBody(){
			return Body;
		}

		public String getCc(){
			return Cc;
		}

		public String getFromAddress(){
			return FromAddress;
		}

		public String getRunProgramDetails(){
			return RunProgramDetails;
		}

		public String getSendImmediately(){
			return SendImmediately;
		}

		public String getSendNotificationActionDef(){
			return SendNotificationActionDef;
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
		public void setFromAddress(String newVal){
			FromAddress = newVal;
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
		public void setSendImmediately(String newVal){
			SendImmediately = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSendNotificationActionDef(String newVal){
			SendNotificationActionDef = newVal;
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

	private boolean m_bSendImmediately = true;
	private boolean m_bSendRtf = false;
	private String m_strBody = "";
	private String m_strCc = "";
	private String m_strFromAddress = "";
	private String m_strSubject = "";
	private String m_strTo = "";

	public SendNotificationActionDef(){

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

	public String Cc(){
		return "";
	}

	public static String ClassName(){
		return "";
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

	public String FromAddress(){
		return "";
	}

	/**
	 * 
	 * @param list
	 */
	public void GatherPromptDefs(IList list){

	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public boolean HasTagsContainingTagCategory(String strTagCategoryName){
		return null;
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

	public String Subject(){
		return "";
	}

	public String To(){
		return "";
	}

}