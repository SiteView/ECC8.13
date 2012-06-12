package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:57
 */
public class RunForChildrenBusObsActionDef extends ActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:57
	 */
	public enum Children {
		All,
		First,
		Last,
		Active,
		LinkField
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:57
	 */
	private class Tags {

		private String ActionList = "ActionList";
		private String ChildBusObName = "ChildBusObName";
		private String Children = "Children";
		private String FusionQueryOrderByList = "FusionQueryOrderByList";
		private String LinkFieldName = "LinkFieldName";
		private String OrderByList = "OrderByList";
		private String ParentBusObName = "ParentBusObName";
		private String ParentBusObSource = "ParentBusObSource";
		private String RelationshipName = "RelationshipName";
		private String RunForChildrenBusObsActionDef = "RunForChildrenBusObsActionDef";
		private String RunForChildrenBusObsDetails = "RunForChildrenBusObsDetails";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getActionList(){
			return ActionList;
		}

		public String getChildBusObName(){
			return ChildBusObName;
		}

		public String getChildren(){
			return Children;
		}

		public String getFusionQueryOrderByList(){
			return FusionQueryOrderByList;
		}

		public String getLinkFieldName(){
			return LinkFieldName;
		}

		public String getOrderByList(){
			return OrderByList;
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

		public String getRunForChildrenBusObsActionDef(){
			return RunForChildrenBusObsActionDef;
		}

		public String getRunForChildrenBusObsDetails(){
			return RunForChildrenBusObsDetails;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setActionList(String newVal){
			ActionList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setChildBusObName(String newVal){
			ChildBusObName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setChildren(String newVal){
			Children = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFusionQueryOrderByList(String newVal){
			FusionQueryOrderByList = newVal;
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
		public void setOrderByList(String newVal){
			OrderByList = newVal;
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

		/**
		 * 
		 * @param newVal
		 */
		public void setRunForChildrenBusObsActionDef(String newVal){
			RunForChildrenBusObsActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRunForChildrenBusObsDetails(String newVal){
			RunForChildrenBusObsDetails = newVal;
		}

	}

	private ArrayList m_aActionDefs = new ArrayList();
	private ArrayList m_alChildOrderByList = new ArrayList();
	private String m_strChildBusObName = "";
	private String m_strLinkFieldName = "";
	private String m_strParentBusObName = "";
	private String m_strParentBusObSource = "";
	private String m_strRelationshipName = "";
	private Children m_WhichChildren = Children.All;

	public RunForChildrenBusObsActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public IList ActionDefinitionObjects(){
		return null;
	}

	public String ActionItem(){
		return "";
	}

	public String ChildBusinessObjectName(){
		return "";
	}

	public IList ChildOrderByList(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public boolean ConsumesContextBusinessObject(){
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

	/**
	 * 
	 * @param list
	 */
	public void GatherPromptDefs(IList list){

	}

	/**
	 * 
	 * @param sID
	 */
	public ActionDef GetActionDefByID(String sID){
		return null;
	}

	public IList GetActionsThatConsumeTheContextBusinessObject(){
		return null;
	}

	/**
	 * 
	 * @param expOb
	 */
	public IList GetActionsThatConsumeTheExposedObject(ExposedObject expOb){
		return null;
	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public IList GetActionsThatHaveTagsContainingTagCategory(String strTagCategoryName){
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
	 * @param strName
	 * @param strId
	 */
	public boolean IsActionNameUnique(String strName, String strId){
		return null;
	}

	public String LinkFieldName(){
		return "";
	}

	/**
	 * 
	 * @param sXml
	 */
	private void OrderByListFromXml(String sXml){

	}

	private String OrderByListToXml(){
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

	public Children WhichChildren(){
		return null;
	}

}