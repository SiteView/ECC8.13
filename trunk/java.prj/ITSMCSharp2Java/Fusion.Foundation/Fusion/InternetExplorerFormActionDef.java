package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:52
 */
public class InternetExplorerFormActionDef extends ActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:52
	 */
	private class Tags {

		private String FormAddress = "FormAddress";
		private String HtmlFormDef = "HtmlFormDef";
		private String InternetExplorerFormActionDef = "InternetExplorerFormActionDef";
		private String InternetExplorerFormDetails = "InternetExplorerFormDetails";
		private String Submit = "Submit";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getFormAddress(){
			return FormAddress;
		}

		public String getHtmlFormDef(){
			return HtmlFormDef;
		}

		public String getInternetExplorerFormActionDef(){
			return InternetExplorerFormActionDef;
		}

		public String getInternetExplorerFormDetails(){
			return InternetExplorerFormDetails;
		}

		public String getSubmit(){
			return Submit;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFormAddress(String newVal){
			FormAddress = newVal;
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
		public void setInternetExplorerFormActionDef(String newVal){
			InternetExplorerFormActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setInternetExplorerFormDetails(String newVal){
			InternetExplorerFormDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSubmit(String newVal){
			Submit = newVal;
		}

	}

	private boolean m_bSubmit = false;
	private HtmlFormDef m_defHtmlForm;
	private String m_strFormAddress = "";

	public InternetExplorerFormActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
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

	public String FormAddress(){
		return "";
	}

	/**
	 * 
	 * @param list
	 */
	public void GatherPromptDefs(IList list){

	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public boolean HasTagsContainingTagCategory(String strTagCategoryName){
		return null;
	}

	public HtmlFormDef HtmlFormDefinitionObject(){
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

	public boolean Submit(){
		return null;
	}

}