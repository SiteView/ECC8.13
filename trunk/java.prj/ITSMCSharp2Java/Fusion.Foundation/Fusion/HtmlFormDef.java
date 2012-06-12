package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:40
 */
public class HtmlFormDef extends DefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:40
	 */
	public enum FormItemTypes {
		Text,
		Password,
		SelectOne,
		TextArea,
		Radio,
		CheckBox
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:40
	 */
	private class Tags {

		private String FormItemList = "FormItemList";
		private String FormName = "FormName";
		private String FormOrder = "FormOrder";
		private String HtmlFormDef = "HtmlFormDef";
		private String IndexByFormName = "IndexByFormName";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getFormItemList(){
			return FormItemList;
		}

		public String getFormName(){
			return FormName;
		}

		public String getFormOrder(){
			return FormOrder;
		}

		public String getHtmlFormDef(){
			return HtmlFormDef;
		}

		public String getIndexByFormName(){
			return IndexByFormName;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFormItemList(String newVal){
			FormItemList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFormName(String newVal){
			FormName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFormOrder(String newVal){
			FormOrder = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setHtmlFormDef(String newVal){
			HtmlFormDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setIndexByFormName(String newVal){
			IndexByFormName = newVal;
		}

	}

	private ArrayList m_aFormItemDefs = new ArrayList();
	private static String m_astrFormItemStatusTypes[] = new string[] { "radio", "checkbox" };
	private static String m_astrFormItemValueTypes[] = new string[] { "text", "password", "select-one", "textarea" };
	private boolean m_bIndexByFormName = true;
	private int m_nFormOrder = -1;
	private String m_strFormName = "";

	public HtmlFormDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strName
	 * @param strType
	 * @param strValue
	 * @param bStatus
	 */
	public boolean AddFormItem(String strName, String strType, String strValue, boolean bStatus){
		return null;
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

	/**
	 * 
	 * @param eType
	 */
	public static String FormItemTypeToString(FormItemTypes eType){
		return "";
	}

	public String FormName(){
		return "";
	}

	public int FormOrder(){
		return 0;
	}

	/**
	 * 
	 * @param strName
	 * @param strType
	 * @param strValue
	 * @param bStatus
	 */
	public boolean GetFormItem(String strName, String strType, String strValue, boolean bStatus){
		return null;
	}

	public boolean IndexByFormName(){
		return null;
	}

	/**
	 * 
	 * @param defItem
	 */
	public static boolean IsFormItemOfStatusType(HtmlFormItemDef defItem){
		return null;
	}

	/**
	 * 
	 * @param strItemType
	 */
	public static boolean IsFormItemOfStatusType(String strItemType){
		return null;
	}

	/**
	 * 
	 * @param defItem
	 */
	public static boolean IsFormItemOfValueType(HtmlFormItemDef defItem){
		return null;
	}

	/**
	 * 
	 * @param strItemType
	 */
	public static boolean IsFormItemOfValueType(String strItemType){
		return null;
	}

	public IList ItemDefinitionObjects(){
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

	/**
	 * 
	 * @param strName
	 * @param strType
	 * @param strValue
	 * @param bStatus
	 */
	public boolean SetFormItem(String strName, String strType, String strValue, boolean bStatus){
		return null;
	}

	public String ToString(){
		return "";
	}

}