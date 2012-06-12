package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:54
 */
public class RptParamRangeValDef extends RptParamValueDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:54
	 */
	public enum RangeValueBoundTypes {
		NoBound,
		Inclusive,
		Exclusive
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:54
	 */
	private class Tags {

		private String FromValue = "FromValue";
		private String FromValueBoundType = "FromValueBoundType";
		private String RangeValDetails = "RangeValDetails";
		private String RptParamRangeValDef = "RptParamRangeValDef";
		private String ToValue = "ToValue";
		private String ToValueBoundType = "ToValueBoundType";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getFromValue(){
			return FromValue;
		}

		public String getFromValueBoundType(){
			return FromValueBoundType;
		}

		public String getRangeValDetails(){
			return RangeValDetails;
		}

		public String getRptParamRangeValDef(){
			return RptParamRangeValDef;
		}

		public String getToValue(){
			return ToValue;
		}

		public String getToValueBoundType(){
			return ToValueBoundType;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFromValue(String newVal){
			FromValue = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFromValueBoundType(String newVal){
			FromValueBoundType = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRangeValDetails(String newVal){
			RangeValDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRptParamRangeValDef(String newVal){
			RptParamRangeValDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setToValue(String newVal){
			ToValue = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setToValueBoundType(String newVal){
			ToValueBoundType = newVal;
		}

	}

	private RangeValueBoundTypes m_FromValueBoundType = RangeValueBoundTypes.Inclusive;
	private String m_strFromValue = "";
	private String m_strToValue = "";
	private RangeValueBoundTypes m_ToValueBoundType = RangeValueBoundTypes.Inclusive;

	public RptParamRangeValDef(){

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

	public String FromValue(){
		return "";
	}

	public RangeValueBoundTypes FromValueBoundType(){
		return null;
	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public boolean HasTagsContainingTagCategory(String strTagCategoryName){
		return null;
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

	public String ToValue(){
		return "";
	}

	public RangeValueBoundTypes ToValueBoundType(){
		return null;
	}

}