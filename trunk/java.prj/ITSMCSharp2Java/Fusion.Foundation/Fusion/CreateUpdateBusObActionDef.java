package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:57
 */
public abstract class CreateUpdateBusObActionDef extends ActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:57
	 */
	private class Tags {

		private String BusObName = "BusObName";
		private String DisplayLinkFields = "DisplayLinkFields";
		private String Edit = "Edit";
		private String EditInNewWindow = "EditInNewWindow";
		private String Field = "Field";
		private String FieldToValueList = "FieldToValueList";
		private String Item = "Item";
		private String Refresh = "Refresh";
		private String Save = "Save";
		private String Value = "Value";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getBusObName(){
			return BusObName;
		}

		public String getDisplayLinkFields(){
			return DisplayLinkFields;
		}

		public String getEdit(){
			return Edit;
		}

		public String getEditInNewWindow(){
			return EditInNewWindow;
		}

		public String getField(){
			return Field;
		}

		public String getFieldToValueList(){
			return FieldToValueList;
		}

		public String getItem(){
			return Item;
		}

		public String getRefresh(){
			return Refresh;
		}

		public String getSave(){
			return Save;
		}

		public String getValue(){
			return Value;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBusObName(String newVal){
			BusObName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDisplayLinkFields(String newVal){
			DisplayLinkFields = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setEdit(String newVal){
			Edit = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setEditInNewWindow(String newVal){
			EditInNewWindow = newVal;
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
		public void setFieldToValueList(String newVal){
			FieldToValueList = newVal;
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
		public void setRefresh(String newVal){
			Refresh = newVal;
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
		public void setValue(String newVal){
			Value = newVal;
		}

	}

	private boolean m_bDisplayLinkFields = false;
	private boolean m_bEdit = false;
	private boolean m_bNewWindow = true;
	private boolean m_bRefresh = false;
	private boolean m_bSave = false;
	private Hashtable m_htFieldToValue = new Hashtable();
	private String m_strBusObName = "";

	public CreateUpdateBusObActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strOverwrite
	 * @param strFieldValue
	 */
	public static String BuildFieldValue(String strOverwrite, String strFieldValue){
		return "";
	}

	public String BusinessObjectName(){
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

	public boolean DisplayLinkFields(){
		return null;
	}

	public boolean Edit(){
		return null;
	}

	public boolean EditInNewWindow(){
		return null;
	}

	public Map FieldToValue(){
		return null;
	}

	private static String FieldValueFormat(){
		return "";
	}

	private static String FieldValueFormatRegEx(){
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
	 * @param strValue
	 * @param strOverwrite
	 * @param strFieldValue
	 */
	public static void ParseFieldValue(String strValue, String strOverwrite, String strFieldValue){

	}

	public boolean Refresh(){
		return null;
	}

	public boolean Save(){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public DefSerializer Serialize(DefSerializer serial){
		return null;
	}

}