package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:53
 */
public class RptParameterDef extends DefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:53
	 */
	public enum ParameterKinds {
		Discrete,
		Range,
		DiscreteOrRange
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:53
	 */
	private class Tags {

		private String RptParameterDef = "RptParameterDef";
		private String ValueList = "ValueList";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getRptParameterDef(){
			return RptParameterDef;
		}

		public String getValueList(){
			return ValueList;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRptParameterDef(String newVal){
			RptParameterDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValueList(String newVal){
			ValueList = newVal;
		}

	}

	private ArrayList m_aValueDefs = new ArrayList();
	private boolean m_bAllowMultVals;
	private ReportDef m_defParent;
	private ParameterKinds m_Kind = ParameterKinds.Discrete;

	public RptParameterDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public boolean AllowMultipleValues(){
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
	 * @param strTagCategoryName
	 * @param bIgnoreDefaultValues
	 */
	public boolean HasTagsContainingTagCategory(String strTagCategoryName, boolean bIgnoreDefaultValues){
		return null;
	}

	public ParameterKinds ParameterKind(){
		return null;
	}

	public ReportDef Parent(){
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

	public IList ValueDefinitions(){
		return null;
	}

}