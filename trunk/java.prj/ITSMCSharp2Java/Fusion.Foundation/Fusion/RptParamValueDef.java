package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:56
 */
public abstract class RptParamValueDef extends DefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:56
	 */
	private class Tags {

		private String RptParamValueDef = "RptParamValueDef";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getRptParamValueDef(){
			return RptParamValueDef;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRptParamValueDef(String newVal){
			RptParamValueDef = newVal;
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:56
	 */
	public enum ValueTypes {
		Default,
		Discrete,
		Range
	}

	private RptParameterDef m_defParent;

	public RptParamValueDef(){

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
	public abstract boolean CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect, String strAssociatedBusOb);

	/**
	 * 
	 * @param correction
	 * @param bJustCollect
	 * @param strAssociatedBusOb
	 * @param strValue
	 */
	protected static boolean CorrectNamedReferenceInTags(NamedReferenceCorrection correction, boolean bJustCollect, String strAssociatedBusOb, String strValue){
		return null;
	}

	/**
	 * 
	 * @param valType
	 */
	private static RptParamValueDef CreateFromCategory(ValueTypes valType){
		return null;
	}

	/**
	 * 
	 * @param strCat
	 */
	private static RptParamValueDef CreateFromCategory(String strCat){
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
	 * @param serial
	 * @param defParent
	 */
	public static SerializableDef DeserializeCreate(DefSerializer serial, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param valType
	 */
	public static IDefinition DeserializeCreateNewForEditing(ValueTypes valType){
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
	 * @param strTagCategoryName
	 */
	public abstract boolean HasTagsContainingTagCategory(String strTagCategoryName);

	/**
	 * 
	 * @param strValue
	 * @param strTagCategoryName
	 */
	protected static boolean HasTagsContainingTagCategory(String strValue, String strTagCategoryName){
		return null;
	}

	public RptParameterDef Parent(){
		return null;
	}

	protected abstract ValueTypes RptParamValueType();

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