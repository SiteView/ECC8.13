package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:42
 */
public class HtmlFormItemDef extends DefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:42
	 */
	private class Tags {

		private String HtmlFormItemDef = "HtmlFormItemDef";
		private String ItemName = "ItemName";
		private String ItemStatus = "ItemStatus";
		private String ItemType = "ItemType";
		private String ItemValue = "ItemValue";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getHtmlFormItemDef(){
			return HtmlFormItemDef;
		}

		public String getItemName(){
			return ItemName;
		}

		public String getItemStatus(){
			return ItemStatus;
		}

		public String getItemType(){
			return ItemType;
		}

		public String getItemValue(){
			return ItemValue;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setHtmlFormItemDef(String newVal){
			HtmlFormItemDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setItemName(String newVal){
			ItemName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setItemStatus(String newVal){
			ItemStatus = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setItemType(String newVal){
			ItemType = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setItemValue(String newVal){
			ItemValue = newVal;
		}

	}

	private boolean m_bItemStatus = false;
	private String m_strItemName = "";
	private String m_strItemType = "";
	private String m_strItemValue = "";

	public HtmlFormItemDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
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
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	/**
	 * 
	 * @param serial
	 * @param defParent
	 */
	public static SerializableDef DeserializeCreate(DefSerializer serial, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strSubType
	 */
	public static IDefinition DeserializeCreateNewForEditing(String strSubType){
		return null;
	}

	public String ItemName(){
		return "";
	}

	public boolean ItemStatus(){
		return null;
	}

	public String ItemType(){
		return "";
	}

	public String ItemValue(){
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

}