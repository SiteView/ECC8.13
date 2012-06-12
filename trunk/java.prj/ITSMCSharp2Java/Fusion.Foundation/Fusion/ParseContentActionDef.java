package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:30
 */
public class ParseContentActionDef extends CreateUpdateBusObActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:30
	 */
	private class Tags {

		private String AttObjRelName = "AttObjRelName";
		private String ColDelimiter = "ColDelimiter";
		private String ContainsHeader = "ContainsHeader";
		private String CSVFileName = "CSVFileName";
		private String Field = "Field";
		private String FieldCount = "FieldCount";
		private String IsParent = "IsParent";
		private String Item = "Item";
		private String LoadCSVFromObject = "LoadCSVFromObject";
		private String LogFileName = "LogFileName";
		private String LogMessage = "LogMessage";
		private String ParseContentActionDef = "ParseContentActionDef";
		private String ParseContentDetails = "ParseContentDetails";
		private String ParseMethod = "ParseMethod";
		private String PromptUser = "PromptUser";
		private String RowDelimiter = "RowDelimiter";
		private String SrcBusObj = "SourceBusinessObject";
		private String SrcFieldList = "SourceFieldList";
		private String TextQualifier = "TextQualifier";
		private String Value = "Value";

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

		public String getCSVFileName(){
			return CSVFileName;
		}

		public String getField(){
			return Field;
		}

		public String getFieldCount(){
			return FieldCount;
		}

		public String getIsParent(){
			return IsParent;
		}

		public String getItem(){
			return Item;
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

		public String getParseContentActionDef(){
			return ParseContentActionDef;
		}

		public String getParseContentDetails(){
			return ParseContentDetails;
		}

		public String getParseMethod(){
			return ParseMethod;
		}

		public String getPromptUser(){
			return PromptUser;
		}

		public String getRowDelimiter(){
			return RowDelimiter;
		}

		public String getSrcBusObj(){
			return SrcBusObj;
		}

		public String getSrcFieldList(){
			return SrcFieldList;
		}

		public String getTextQualifier(){
			return TextQualifier;
		}

		public String getValue(){
			return Value;
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
		public void setCSVFileName(String newVal){
			CSVFileName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setField(String newVal){
			Field = newVal;
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
		public void setItem(String newVal){
			Item = newVal;
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
		public void setParseContentActionDef(String newVal){
			ParseContentActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParseContentDetails(String newVal){
			ParseContentDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParseMethod(String newVal){
			ParseMethod = newVal;
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
		public void setSrcBusObj(String newVal){
			SrcBusObj = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSrcFieldList(String newVal){
			SrcFieldList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTextQualifier(String newVal){
			TextQualifier = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValue(String newVal){
			Value = newVal;
		}

	}

	private boolean m_bContainsHeader = false;
	private boolean m_bIsParent = false;
	private boolean m_bLoadCSVFromObject = false;
	private boolean m_bLogMessage = false;
	private boolean m_bPromptUser = true;
	private Hashtable m_htSrcFieldList = new Hashtable();
	private int m_iFieldCount = 1;
	private int m_iParseMethod = 1;
	private String m_strAttObjRelName = "";
	private String m_strColDelimiter = ",";
	private String m_strCSVFileName = "";
	private String m_strLogFileName = "";
	private String m_strRowDelimiter = "\r\n";
	private String m_strSrcBusObName = "";
	private String m_strTextQualifier = "\"";
	private int PARSEMETHOD_CUSTOM = 3;
	private int PARSEMETHOD_NAMEVALE = 1;
	private int PARSEMETHOD_XML = 2;

	public ParseContentActionDef(){

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

	public int getPARSEMETHOD_CUSTOM(){
		return PARSEMETHOD_CUSTOM;
	}

	public int getPARSEMETHOD_NAMEVALE(){
		return PARSEMETHOD_NAMEVALE;
	}

	public int getPARSEMETHOD_XML(){
		return PARSEMETHOD_XML;
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

	public int ParseMethod(){
		return 0;
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

	/**
	 * 
	 * @param newVal
	 */
	public void setPARSEMETHOD_CUSTOM(int newVal){
		PARSEMETHOD_CUSTOM = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPARSEMETHOD_NAMEVALE(int newVal){
		PARSEMETHOD_NAMEVALE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPARSEMETHOD_XML(int newVal){
		PARSEMETHOD_XML = newVal;
	}

	public String SrcBusinessObjectName(){
		return "";
	}

	public Hashtable SrcFieldList(){
		return null;
	}

	public String TextQualifier(){
		return "";
	}

}