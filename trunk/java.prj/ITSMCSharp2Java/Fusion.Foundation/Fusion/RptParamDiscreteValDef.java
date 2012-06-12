package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:52
 */
public class RptParamDiscreteValDef extends RptParamValueDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:52
	 */
	private class Tags {

		private String DiscreteValDetails = "DiscreteValDetails";
		private String RptParamDiscreteValDef = "RptParamDiscreteValDef";
		private String Value = "Value";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getDiscreteValDetails(){
			return DiscreteValDetails;
		}

		public String getRptParamDiscreteValDef(){
			return RptParamDiscreteValDef;
		}

		public String getValue(){
			return Value;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDiscreteValDetails(String newVal){
			DiscreteValDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRptParamDiscreteValDef(String newVal){
			RptParamDiscreteValDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValue(String newVal){
			Value = newVal;
		}

	}

	private String m_strValue = "";

	public RptParamDiscreteValDef(){

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

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public boolean HasTagsContainingTagCategory(String strTagCategoryName){
		return null;
	}

	public String ParameterValue(){
		return "";
	}

	protected RptParamValueDef.ValueTypes RptParamValueType(){
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

}