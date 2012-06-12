package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:45
 */
public class BusObBusUnitDef extends BusinessUnitDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:45
	 */
	private class Tags {

		private String BusinessObjectDef = "BusinessObjectDef";
		private String BusinessObjectDetails = "BusinessObjectDetails";
		private String BusinessUnitDef = "BusinessUnitDef";
		private String DisplayFieldName = "DisplayFieldName";
		private String Field = "Field";
		private String ID = "ID";
		private String RelationshipDef = "RelationshipDef";
		private String ValueFieldName = "ValueFieldName";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getBusinessObjectDef(){
			return BusinessObjectDef;
		}

		public String getBusinessObjectDetails(){
			return BusinessObjectDetails;
		}

		public String getBusinessUnitDef(){
			return BusinessUnitDef;
		}

		public String getDisplayFieldName(){
			return DisplayFieldName;
		}

		public String getField(){
			return Field;
		}

		public String getID(){
			return ID;
		}

		public String getRelationshipDef(){
			return RelationshipDef;
		}

		public String getValueFieldName(){
			return ValueFieldName;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBusinessObjectDef(String newVal){
			BusinessObjectDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBusinessObjectDetails(String newVal){
			BusinessObjectDetails = newVal;
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
		public void setDisplayFieldName(String newVal){
			DisplayFieldName = newVal;
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
		public void setID(String newVal){
			ID = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRelationshipDef(String newVal){
			RelationshipDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValueFieldName(String newVal){
			ValueFieldName = newVal;
		}

	}

	private String m_strBusObDefId = "";
	private String m_strDisplayFieldId = "";
	private String m_strRelDefId = "";
	private String m_strValueFieldId = "";

	public BusObBusUnitDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String BusObDefId(){
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
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public String DisplayFieldId(){
		return "";
	}

	public String RelationshipDefId(){
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

	public String SerializeSpecificPropertyRoot(){
		return "";
	}

	public String ValueFieldId(){
		return "";
	}

}