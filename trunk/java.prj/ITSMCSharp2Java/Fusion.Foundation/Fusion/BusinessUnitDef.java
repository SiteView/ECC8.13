package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:44
 */
public class BusinessUnitDef extends DefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:44
	 */
	private class Tags {

		private String BusinessUnitDef = "BusinessUnitDef";
		private String Icon = "Icon";
		private String SelectText = "SelectText";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getBusinessUnitDef(){
			return BusinessUnitDef;
		}

		public String getIcon(){
			return Icon;
		}

		public String getSelectText(){
			return SelectText;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBusinessUnitDef(String newVal){
			BusinessUnitDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setIcon(String newVal){
			Icon = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSelectText(String newVal){
			SelectText = newVal;
		}

	}

	private BusUnitCategory m_BusUnitCategory = BusUnitCategory.None;
	private String m_strIcon = "";
	private String m_strSelectText = "";

	public BusinessUnitDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public BusUnitCategory Category(){
		return null;
	}

	public String CategoryAsString(){
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
	 * @param bc
	 */
	public static BusinessUnitDef Create(BusUnitCategory bc){
		return null;
	}

	public String DefinitionType(){
		return "";
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

	public String Icon(){
		return "";
	}

	public String SelectText(){
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

	public String ToString(){
		return "";
	}

}