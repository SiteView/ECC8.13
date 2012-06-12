package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:56
 */
public class WriteFileActionDef extends ActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:56
	 */
	private class Tags {

		private String Append = "Append";
		private String Content = "Content";
		private String FilePath = "FilePath";
		private String WriteFileActionDef = "WriteFileActionDef";
		private String WriteFileDetails = "WriteFileDetails";
		private String WriteRtf = "WriteRtf";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAppend(){
			return Append;
		}

		public String getContent(){
			return Content;
		}

		public String getFilePath(){
			return FilePath;
		}

		public String getWriteFileActionDef(){
			return WriteFileActionDef;
		}

		public String getWriteFileDetails(){
			return WriteFileDetails;
		}

		public String getWriteRtf(){
			return WriteRtf;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAppend(String newVal){
			Append = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setContent(String newVal){
			Content = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFilePath(String newVal){
			FilePath = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setWriteFileActionDef(String newVal){
			WriteFileActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setWriteFileDetails(String newVal){
			WriteFileDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setWriteRtf(String newVal){
			WriteRtf = newVal;
		}

	}

	private boolean m_bAppend = false;
	private boolean m_bWriteRtf = true;
	private String m_strContent = "";
	private String m_strFilePath = "";

	public WriteFileActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
		return "";
	}

	public boolean Append(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public String Content(){
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

	public String FilePath(){
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

	public boolean WriteRtf(){
		return null;
	}

}