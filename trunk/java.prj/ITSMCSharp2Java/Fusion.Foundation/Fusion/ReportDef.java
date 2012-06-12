package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:47
 */
public class ReportDef extends ScopedDefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:47
	 */
	public enum ReportTypes {
		Local,
		Server
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:47
	 */
	private class Tags {

		private String ParameterList = "ParameterList";
		private String ReportDef = "ReportDef";
		private String ReportName = "ReportName";
		private String ReportType = "ReportType";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getParameterList(){
			return ParameterList;
		}

		public String getReportDef(){
			return ReportDef;
		}

		public String getReportName(){
			return ReportName;
		}

		public String getReportType(){
			return ReportType;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParameterList(String newVal){
			ParameterList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setReportDef(String newVal){
			ReportDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setReportName(String newVal){
			ReportName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setReportType(String newVal){
			ReportType = newVal;
		}

	}

	private ArrayList m_aParameterDefs = new ArrayList();
	private ReportTypes m_ReportType = ReportTypes.Local;
	private String m_strRptName = "";

	public ReportDef(){

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
	 */
	public void CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect){

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
	public IList GetParametersThatHaveTagsContainingTagCategory(String strTagCategoryName, boolean bIgnoreDefaultValues){
		return null;
	}

	public IList ParameterDefinitions(){
		return null;
	}

	public String ReportName(){
		return "";
	}

	public ReportTypes ReportType(){
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

}