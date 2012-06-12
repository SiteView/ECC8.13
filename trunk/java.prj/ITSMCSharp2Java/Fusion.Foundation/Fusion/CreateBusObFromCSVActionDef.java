package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:56
 */
public class CreateBusObFromCSVActionDef extends CreateUpdateBusObActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:56
	 */
	private class Tags {

		private String AttObjRelName = "AttObjRelName";
		private String ColDelimiter = "ColDelimiter";
		private String ContainsHeader = "ContainsHeader";
		private String CreateBusObFromCSVActionDef = "CreateBusObFromCSVActionDef";
		private String CreateBusObFromCSVDetails = "CreateBusObFromCSVDetails";
		private String CSVFileName = "CSVFileName";
		private String FieldCount = "FieldCount";
		private String IsParent = "IsParent";
		private String LoadCSVFromObject = "LoadCSVFromObject";
		private String LogFileName = "LogFileName";
		private String LogMessage = "LogMessage";
		private String PromptUser = "PromptUser";
		private String RowDelimiter = "RowDelimiter";
		private String TextQualifier = "TextQualifier";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAttObjRelName(){
			return AttObjRelName;
		}

		public String getColDelimiter(){
			return ColDelimiter;
		}

		public String getContainsHeader(){
			return ContainsHeader;
		}

		public String getCreateBusObFromCSVActionDef(){
			return CreateBusObFromCSVActionDef;
		}

		public String getCreateBusObFromCSVDetails(){
			return CreateBusObFromCSVDetails;
		}

		public String getCSVFileName(){
			return CSVFileName;
		}

		public String getFieldCount(){
			return FieldCount;
		}

		public String getIsParent(){
			return IsParent;
		}

		public String getLoadCSVFromObject(){
			return LoadCSVFromObject;
		}

		public String getLogFileName(){
			return LogFileName;
		}

		public String getLogMessage(){
			return LogMessage;
		}

		public String getPromptUser(){
			return PromptUser;
		}

		public String getRowDelimiter(){
			return RowDelimiter;
		}

		public String getTextQualifier(){
			return TextQualifier;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAttObjRelName(String newVal){
			AttObjRelName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setColDelimiter(String newVal){
			ColDelimiter = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setContainsHeader(String newVal){
			ContainsHeader = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCreateBusObFromCSVActionDef(String newVal){
			CreateBusObFromCSVActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCreateBusObFromCSVDetails(String newVal){
			CreateBusObFromCSVDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCSVFileName(String newVal){
			CSVFileName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFieldCount(String newVal){
			FieldCount = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setIsParent(String newVal){
			IsParent = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLoadCSVFromObject(String newVal){
			LoadCSVFromObject = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLogFileName(String newVal){
			LogFileName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLogMessage(String newVal){
			LogMessage = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPromptUser(String newVal){
			PromptUser = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRowDelimiter(String newVal){
			RowDelimiter = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTextQualifier(String newVal){
			TextQualifier = newVal;
		}

	}

	private boolean m_bContainsHeader = false;
	private boolean m_bIsParent = false;
	private boolean m_bLoadCSVFromObject = false;
	private boolean m_bLogMessage = false;
	private boolean m_bPromptUser = true;
	private int m_iFieldCount = 1;
	private String m_strAttObjRelName = "";
	private String m_strColDelimiter = ",";
	private String m_strCSVFileName = "";
	private String m_strLogFileName = "";
	private String m_strRowDelimiter = "\r\n";
	private String m_strTextQualifier = "\"";

	public CreateBusObFromCSVActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
		return "";
	}

	public String AttObjRelName(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public String ColDelimiter(){
		return "";
	}

	public boolean ContainsHeader(){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param defOwner
	 */
	protected void CopyContents(SerializableDef def, SerializableDef defOwner){

	}

	public String CSVFileName(){
		return "";
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public int FieldCount(){
		return 0;
	}

	public IList GetExposedObjects(){
		return null;
	}

	public boolean IsParent(){
		return null;
	}

	public boolean LoadCSVFromObject(){
		return null;
	}

	public String LogFileName(){
		return "";
	}

	public boolean LogMessage(){
		return null;
	}

	public boolean PromptUser(){
		return null;
	}

	public String RowDelimiter(){
		return "";
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

	public String TextQualifier(){
		return "";
	}

}