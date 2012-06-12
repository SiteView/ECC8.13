package Fusion;
import Fusion.Foundation.CompareInfo;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:10
 */
public class DefRights extends SerializableDef implements IAggregate {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:10
	 */
	private class Tags {

		private String AllowAddAnnotations = "AllowAddAnnotations";
		private String AllowChangeAliasName = "AllowChangeAliasName";
		private String AllowChangeDatabaseProperties = "AllowChangeDatabaseProperties";
		private String AllowChangeName = "AllowChangeName";
		private String AllowChanges = "AllowChanges";
		private String AllowChangeStorageName = "AllowChangeStorageName";
		private String AllowRemoval = "AllowRemoval";
		private String AllowRemoveAnnotations = "AllowRemoveAnnotations";
		private String CustomizationLevel = "Level";
		private String EditorRights = "EditorRights";
		private String Value = "Value";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAllowAddAnnotations(){
			return AllowAddAnnotations;
		}

		public String getAllowChangeAliasName(){
			return AllowChangeAliasName;
		}

		public String getAllowChangeDatabaseProperties(){
			return AllowChangeDatabaseProperties;
		}

		public String getAllowChangeName(){
			return AllowChangeName;
		}

		public String getAllowChanges(){
			return AllowChanges;
		}

		public String getAllowChangeStorageName(){
			return AllowChangeStorageName;
		}

		public String getAllowRemoval(){
			return AllowRemoval;
		}

		public String getAllowRemoveAnnotations(){
			return AllowRemoveAnnotations;
		}

		public String getCustomizationLevel(){
			return CustomizationLevel;
		}

		public String getEditorRights(){
			return EditorRights;
		}

		public String getValue(){
			return Value;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAllowAddAnnotations(String newVal){
			AllowAddAnnotations = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAllowChangeAliasName(String newVal){
			AllowChangeAliasName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAllowChangeDatabaseProperties(String newVal){
			AllowChangeDatabaseProperties = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAllowChangeName(String newVal){
			AllowChangeName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAllowChanges(String newVal){
			AllowChanges = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAllowChangeStorageName(String newVal){
			AllowChangeStorageName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAllowRemoval(String newVal){
			AllowRemoval = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAllowRemoveAnnotations(String newVal){
			AllowRemoveAnnotations = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCustomizationLevel(String newVal){
			CustomizationLevel = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setEditorRights(String newVal){
			EditorRights = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValue(String newVal){
			Value = newVal;
		}

	}

	private AggregateBase m_aggregate = null;
	private boolean m_bAllowAddAnnotations = true;
	private boolean m_bAllowChangeAliasName = true;
	private boolean m_bAllowChangeDatabaseProperties = true;
	private boolean m_bAllowChangeName = true;
	private boolean m_bAllowChanges = true;
	private boolean m_bAllowChangeStorageName = true;
	private boolean m_bAllowRemoval = true;
	private boolean m_bAllowRemoveAnnotations = true;
	private boolean m_bSerialize = false;
	private Fusion.Xml.CustomizationLevel m_CustomizationLevel = Fusion.Xml.CustomizationLevel.NotSet;
	private SerializableDef m_ParentDef = null;

	public DefRights(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param parentDef
	 */
	public DefRights(SerializableDef parentDef){

	}

	public AggregateBase Aggregate(){
		return null;
	}

	public String AggregateClassName(){
		return "";
	}

	public boolean AllowAddAnnotations(){
		return null;
	}

	public boolean AllowChangeAliasName(){
		return null;
	}

	public boolean AllowChangeDatabaseProperties(){
		return null;
	}

	public boolean AllowChangeName(){
		return null;
	}

	public boolean AllowChanges(){
		return null;
	}

	public boolean AllowChangeStorageName(){
		return null;
	}

	public boolean AllowPermissionsToBeSet(){
		return null;
	}

	public boolean AllowRemoval(){
		return null;
	}

	public boolean AllowRemoveAnnotations(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param defOwner
	 */
	public DefRights Clone(SerializableDef defOwner){
		return null;
	}

	/**
	 * 
	 * @param defToCompare
	 * @param ciParent
	 */
	public void CompareContents(SerializableDef defToCompare, CompareInfo ciParent){

	}

	protected void ConfirmEditCondition(){

	}

	private void ConfirmParentEditMode(){

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
	 * @param factory
	 */
	public AggregateBase CreateAggregate(IAggregateFactory factory){
		return null;
	}

	public Fusion.Xml.CustomizationLevel CustomizationLevel(){
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

	private Fusion.Xml.CustomizationLevel GetCurrentCustomizationLevel(){
		return null;
	}

	public SerializableDef ParentDef(){
		return null;
	}

	protected void ResetRights(){

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

	/**
	 * 
	 * @param bDefDirty
	 */
	public void SetDefDirty(boolean bDefDirty){

	}

	private void ValidateCustomizationLevel(){

	}

}