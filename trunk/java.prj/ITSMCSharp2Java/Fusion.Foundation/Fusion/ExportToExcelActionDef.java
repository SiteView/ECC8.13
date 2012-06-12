package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:21
 */
public class ExportToExcelActionDef extends ActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:21
	 */
	private class Tags {

		private String Close = "Close";
		private String ExportToExcelActionDef = "ExportToExcelActionDef";
		private String ExportToExcelDetails = "ExportToExcelDetails";
		private String FilePath = "FilePath";
		private String Item = "Item";
		private String Location = "Location";
		private String LocationToValueList = "LocationToValueList";
		private String Name = "Name";
		private String NameToValueList = "NameToValueList";
		private String OpenForEachRecord = "OpenForEachRecord";
		private String Print = "Print";
		private String Save = "Save";
		private String SaveAs = "SaveAs";
		private String SaveAsFilePath = "SaveAsFilePath";
		private String Value = "Value";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClose(){
			return Close;
		}

		public String getExportToExcelActionDef(){
			return ExportToExcelActionDef;
		}

		public String getExportToExcelDetails(){
			return ExportToExcelDetails;
		}

		public String getFilePath(){
			return FilePath;
		}

		public String getItem(){
			return Item;
		}

		public String getLocation(){
			return Location;
		}

		public String getLocationToValueList(){
			return LocationToValueList;
		}

		public String getName(){
			return Name;
		}

		public String getNameToValueList(){
			return NameToValueList;
		}

		public String getOpenForEachRecord(){
			return OpenForEachRecord;
		}

		public String getPrint(){
			return Print;
		}

		public String getSave(){
			return Save;
		}

		public String getSaveAs(){
			return SaveAs;
		}

		public String getSaveAsFilePath(){
			return SaveAsFilePath;
		}

		public String getValue(){
			return Value;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setClose(String newVal){
			Close = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setExportToExcelActionDef(String newVal){
			ExportToExcelActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setExportToExcelDetails(String newVal){
			ExportToExcelDetails = newVal;
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
		public void setItem(String newVal){
			Item = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLocation(String newVal){
			Location = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLocationToValueList(String newVal){
			LocationToValueList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setName(String newVal){
			Name = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setNameToValueList(String newVal){
			NameToValueList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setOpenForEachRecord(String newVal){
			OpenForEachRecord = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPrint(String newVal){
			Print = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSave(String newVal){
			Save = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSaveAs(String newVal){
			SaveAs = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSaveAsFilePath(String newVal){
			SaveAsFilePath = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValue(String newVal){
			Value = newVal;
		}

	}

	private boolean m_bClose = false;
	private boolean m_bOpenForEachRecord = false;
	private boolean m_bPrint = false;
	private boolean m_bSave = false;
	private boolean m_bSaveAs = false;
	private SortedList m_htLocationToValue = new SortedList();
	private SortedList m_htNameToValue = new SortedList();
	private String m_strFilePath = "";
	private String m_strSaveAsFilePath = "";

	public ExportToExcelActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
		return "";
	}

	/**
	 * 
	 * @param strInsert
	 * @param strExportValue
	 */
	public static String BuildExportValue(String strInsert, String strExportValue){
		return "";
	}

	/**
	 * 
	 * @param strSheet
	 * @param strCell
	 */
	public static String BuildLocation(String strSheet, String strCell){
		return "";
	}

	/**
	 * 
	 * @param strSheet
	 * @param strCell
	 */
	public static String BuildLocationDisplay(String strSheet, String strCell){
		return "";
	}

	private static String CellFormatRegEx(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public boolean Close(){
		return null;
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

	private static String ExportValueFormat(){
		return "";
	}

	private static String ExportValueFormatRegEx(){
		return "";
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

	private static String LocationDisplayFormat(){
		return "";
	}

	private static String LocationFormat(){
		return "";
	}

	private static String LocationFormatRegEx(){
		return "";
	}

	private static String LocationFormatWithTagsRegEx(){
		return "";
	}

	public Map LocationToValue(){
		return null;
	}

	public Map NameToValue(){
		return null;
	}

	public boolean OpenForEachRecord(){
		return null;
	}

	/**
	 * 
	 * @param strColumnAndRow
	 * @param strColumn
	 * @param nRow
	 */
	public static void ParseColumnAndRow(String strColumnAndRow, String strColumn, int nRow){

	}

	/**
	 * 
	 * @param strValue
	 * @param strInsert
	 * @param strExportValue
	 */
	public static void ParseExportValue(String strValue, String strInsert, String strExportValue){

	}

	/**
	 * 
	 * @param strSheetAndCell
	 * @param nSheet
	 * @param strCell
	 */
	public static void ParseLocation(String strSheetAndCell, int nSheet, String strCell){

	}

	/**
	 * 
	 * @param strSheetAndCell
	 * @param strSheet
	 * @param strCell
	 */
	public static void ParseLocation(String strSheetAndCell, String strSheet, String strCell){

	}

	public boolean Print(){
		return null;
	}

	public boolean Save(){
		return null;
	}

	public boolean SaveAs(){
		return null;
	}

	public String SaveAsFilePath(){
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

}