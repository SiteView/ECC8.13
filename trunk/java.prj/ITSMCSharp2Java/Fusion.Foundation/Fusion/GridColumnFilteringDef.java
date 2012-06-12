package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:37
 */
public class GridColumnFilteringDef extends SerializableDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:37
	 */
	private class Tags {

		private String ClassName = "GridColumnFilteringDef";
		private String Compare = "Compare";
		private String ConditionLogical = "ConditionLogical";
		private String GridColumnFiltering = "GridColumnFiltering";
		private String Operator = "Operator";
		private String Type = "Type";
		private String Value = "Value";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClassName(){
			return ClassName;
		}

		public String getCompare(){
			return Compare;
		}

		public String getConditionLogical(){
			return ConditionLogical;
		}

		public String getGridColumnFiltering(){
			return GridColumnFiltering;
		}

		public String getOperator(){
			return Operator;
		}

		public String getType(){
			return Type;
		}

		public String getValue(){
			return Value;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setClassName(String newVal){
			ClassName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCompare(String newVal){
			Compare = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setConditionLogical(String newVal){
			ConditionLogical = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setGridColumnFiltering(String newVal){
			GridColumnFiltering = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setOperator(String newVal){
			Operator = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setType(String newVal){
			Type = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValue(String newVal){
			Value = newVal;
		}

	}

	private String m_strCompareOperator = "";
	private String m_strCompareValue = "";
	private String m_strConditionLogOperator = "";
	private String m_strValueType = "";

	public GridColumnFilteringDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public static String ClassName(){
		return "";
	}

	public GridColumnFilteringDef Clone(){
		return null;
	}

	public String CompareOperator(){
		return "";
	}

	public String CompareValue(){
		return "";
	}

	public String ConditionLogicalOperator(){
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

	public String ValueType(){
		return "";
	}

}