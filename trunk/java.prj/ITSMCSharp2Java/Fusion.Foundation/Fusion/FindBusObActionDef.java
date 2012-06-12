package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:27
 */
public class FindBusObActionDef extends CreateUpdateBusObActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:27
	 */
	private class Tags {

		private String CreateIfNotFound = "CreateIfNotFound";
		private String FindBusObActionDef = "FindBusObActionDef";
		private String FindBusObDetails = "FindBusObDetails";
		private String Query = "Query";
		private String TargetBusObName = "TargetBusObName";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getCreateIfNotFound(){
			return CreateIfNotFound;
		}

		public String getFindBusObActionDef(){
			return FindBusObActionDef;
		}

		public String getFindBusObDetails(){
			return FindBusObDetails;
		}

		public String getQuery(){
			return Query;
		}

		public String getTargetBusObName(){
			return TargetBusObName;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCreateIfNotFound(String newVal){
			CreateIfNotFound = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFindBusObActionDef(String newVal){
			FindBusObActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFindBusObDetails(String newVal){
			FindBusObDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setQuery(String newVal){
			Query = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTargetBusObName(String newVal){
			TargetBusObName = newVal;
		}

	}

	private boolean m_blnCreateIfNotFound = true;
	private Fusion.FusionQuery m_qryFusion;

	public FindBusObActionDef(){

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

	public boolean CreateIfNotFound(){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public Fusion.FusionQuery FusionQuery(){
		return null;
	}

	public IList GetExposedObjects(){
		return null;
	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public boolean HasTagsContainingTagCategory(String strTagCategoryName){
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