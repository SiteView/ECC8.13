package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:56
 */
public class CreateChildBusObActionDef extends CreateUpdateBusObActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:56
	 */
	private class Tags {

		private String ChangeDisplayOption = "ChangeDisplayOption";
		private String CreateChildBusObActionDef = "CreateChildBusObActionDef";
		private String CreateChildBusObDetails = "CreateChildBusObDetails";
		private String LinkFieldName = "LinkFieldName";
		private String ParentBusObName = "ParentBusObName";
		private String ParentBusObSource = "ParentBusObSource";
		private String RelationshipName = "RelationshipName";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getChangeDisplayOption(){
			return ChangeDisplayOption;
		}

		public String getCreateChildBusObActionDef(){
			return CreateChildBusObActionDef;
		}

		public String getCreateChildBusObDetails(){
			return CreateChildBusObDetails;
		}

		public String getLinkFieldName(){
			return LinkFieldName;
		}

		public String getParentBusObName(){
			return ParentBusObName;
		}

		public String getParentBusObSource(){
			return ParentBusObSource;
		}

		public String getRelationshipName(){
			return RelationshipName;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setChangeDisplayOption(String newVal){
			ChangeDisplayOption = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCreateChildBusObActionDef(String newVal){
			CreateChildBusObActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCreateChildBusObDetails(String newVal){
			CreateChildBusObDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLinkFieldName(String newVal){
			LinkFieldName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParentBusObName(String newVal){
			ParentBusObName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParentBusObSource(String newVal){
			ParentBusObSource = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRelationshipName(String newVal){
			RelationshipName = newVal;
		}

	}

	private String m_strChangeDisplayOption = "";
	private String m_strLinkFieldName = "";
	private String m_strParentBusObName = "";
	private String m_strParentBusObSource = "";
	private String m_strRelationshipName = "";

	public CreateChildBusObActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
		return "";
	}

	public String ChangeDisplayOption(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public boolean ConsumesContextBusinessObject(){
		return null;
	}

	/**
	 * 
	 * @param expOb
	 */
	public boolean ConsumesExposedObject(ExposedObject expOb){
		return null;
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

	public IList GetExposedObjects(){
		return null;
	}

	public String LinkFieldName(){
		return "";
	}

	public String ParentBusinessObjectName(){
		return "";
	}

	public String ParentBusinessObjectSource(){
		return "";
	}

	public String RelationshipName(){
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

	public String SerializeSpecificPropertyRoot(){
		return "";
	}

}