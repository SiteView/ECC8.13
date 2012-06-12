package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:43
 */
public class AutoTaskDef extends ScopedDefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:43
	 */
	private class Tags {

		private String ActionList = "ActionList";
		private String AutoTaskDef = "AutoTaskDef";
		private String CanRunForGroup = "CanRunForGroup";
		private String PostActionList = "PostActionList";
		private String PreActionList = "PreActionList";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getActionList(){
			return ActionList;
		}

		public String getAutoTaskDef(){
			return AutoTaskDef;
		}

		public String getCanRunForGroup(){
			return CanRunForGroup;
		}

		public String getPostActionList(){
			return PostActionList;
		}

		public String getPreActionList(){
			return PreActionList;
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
		public void setAutoTaskDef(String newVal){
			AutoTaskDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCanRunForGroup(String newVal){
			CanRunForGroup = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPostActionList(String newVal){
			PostActionList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPreActionList(String newVal){
			PreActionList = newVal;
		}

	}

	private ArrayList m_aActionDefs = new ArrayList();
	private ArrayList m_aPostActionDefs = new ArrayList();
	private ArrayList m_aPreActionDefs = new ArrayList();
	private boolean m_bCanRunForGroup = true;

	public AutoTaskDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public IList ActionDefinitionObjects(){
		return null;
	}

	public String AggregateClassName(){
		return "";
	}

	public boolean CanRunForGroup(){
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
	 */
	public void CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect){

	}

	/**
	 * 
	 * @param correction
	 * @param bJustCollect
	 * @param aActionDefs
	 */
	private boolean CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect, IList aActionDefs){
		return null;
	}

	protected boolean DefinitionSupportsPerspective(){
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

	public String Flags(){
		return "";
	}

	public IList GatherPromptDefs(){
		return null;
	}

	/**
	 * 
	 * @param aPrompts
	 * @param aActionDefs
	 */
	private void GatherPromptDefs(IList aPrompts, IList aActionDefs){

	}

	/**
	 * 
	 * @param sID
	 */
	public ActionDef GetActionDefinitionByID(String sID){
		return null;
	}

	public IList GetActionsThatConsumeTheContextBusinessObject(){
		return null;
	}

	/**
	 * 
	 * @param aActionNames
	 * @param aActionDefs
	 */
	private void GetActionsThatConsumeTheContextBusinessObject(IList aActionNames, IList aActionDefs){

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
	 * @param expOb
	 * @param aActionNames
	 * @param aActionDefs
	 */
	private void GetActionsThatConsumeTheExposedObject(ExposedObject expOb, IList aActionNames, IList aActionDefs){

	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public IList GetActionsThatHaveTagsContainingTagCategory(String strTagCategoryName){
		return null;
	}

	/**
	 * 
	 * @param strTagCategoryName
	 * @param aActionNames
	 * @param aActionDefs
	 */
	private void GetActionsThatHaveTagsContainingTagCategory(String strTagCategoryName, IList aActionNames, IList aActionDefs){

	}

	public IList GetExposedObjects(){
		return null;
	}

	/**
	 * 
	 * @param aExpObs
	 * @param aActionDefs
	 */
	private boolean GetExposedObjects(IList aExpObs, IList aActionDefs){
		return null;
	}

	/**
	 * 
	 * @param sID
	 */
	public ActionDef GetPostActionDefinitionByID(String sID){
		return null;
	}

	/**
	 * 
	 * @param sID
	 */
	public ActionDef GetPreActionDefinitionByID(String sID){
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

	/**
	 * 
	 * @param strName
	 * @param strId
	 * @param aActionDefs
	 */
	private boolean IsActionNameUnique(String strName, String strId, IList aActionDefs){
		return null;
	}

	public IList PostActionDefinitionObjects(){
		return null;
	}

	public IList PreActionDefinitionObjects(){
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