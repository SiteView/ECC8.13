package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:30
 */
public class SystemPromptDef extends SystemFunctionDef implements IDefinition, ISystemPrompt, ISystemFunction {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:30
	 */
	public class ParameterName extends ParameterName {

		private String Caption = "Caption";
		private String DefaultValue = "DefaultValue";
		private String Message = "Message";
		private String PromptRefId = "PromptRefId";
		private String PromptRefName = "PromptRefName";
		private String PromptRefType = "PromptRefType";

		public ParameterName(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		public String getCaption(){
			return Caption;
		}

		public String getDefaultValue(){
			return DefaultValue;
		}

		public String getMessage(){
			return Message;
		}

		public String getPromptRefId(){
			return PromptRefId;
		}

		public String getPromptRefName(){
			return PromptRefName;
		}

		public String getPromptRefType(){
			return PromptRefType;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCaption(String newVal){
			Caption = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDefaultValue(String newVal){
			DefaultValue = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMessage(String newVal){
			Message = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPromptRefId(String newVal){
			PromptRefId = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPromptRefName(String newVal){
			PromptRefName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPromptRefType(String newVal){
			PromptRefType = newVal;
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:31
	 */
	private class Tags {

		private String SystemPrompt = "SystemPrompt";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getSystemPrompt(){
			return SystemPrompt;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSystemPrompt(String newVal){
			SystemPrompt = newVal;
		}

	}

	private String SystemPromptDefName = "SystemPromptDef";
	private String SystemPromptExtentionPurpose = "SystemPromptExtension";

	public SystemPromptDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strName
	 * @param value
	 */
	public void AddParameter(String strName, Object value){

	}

	/**
	 * 
	 * @param dictParameters
	 */
	public void AddParameter(IDictionary dictParameters){

	}

	public String Alias(){
		return "";
	}

	public Map Annotations(){
		return null;
	}

	public void ApplyEdits(){

	}

	public void AssignIdIfRequired(){

	}

	public String AssociatedImage(){
		return "";
	}

	public boolean CanEdit(){
		return null;
	}

	public String Caption(){
		return "";
	}

	public String Category(){
		return "";
	}

	public String CategoryAsString(){
		return "";
	}

	/**
	 * 
	 * @param Name
	 */
	public void ClearCargo(String Name){

	}

	public IDefinition Clone(){
		return null;
	}

	public IDefinition CloneForCopy(){
		return null;
	}

	public IDefinition CloneForEdit(){
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
	 */
	public void CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect){

	}

	public SystemFunctionValueType DataType(){
		return null;
	}

	public Object DefaultValue(){
		return null;
	}

	public String DefinitionType(){
		return "";
	}

	public String Description(){
		return "";
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public String Flags(){
		return "";
	}

	public String Folder(){
		return "";
	}

	/**
	 * 
	 * @param strXml
	 */
	public void FromXml(String strXml){

	}

	/**
	 * 
	 * @param Name
	 */
	public Object GetCargo(String Name){
		return null;
	}

	public String getSystemPromptDefName(){
		return SystemPromptDefName;
	}

	public String getSystemPromptExtentionPurpose(){
		return SystemPromptExtentionPurpose;
	}

	private String Id(){
		return "";
	}

	public String InstanceClassName(){
		return "";
	}

	private boolean IsDefDirty(){
		return null;
	}

	public String LinkedTo(){
		return "";
	}

	public String Message(){
		return "";
	}

	public String Name(){
		return "";
	}

	public Map NamedParameters(){
		return null;
	}

	public String OriginalName(){
		return "";
	}

	public Fusion.Xml.Scope OriginalScope(){
		return null;
	}

	public String OriginalScopeOwner(){
		return "";
	}

	public String Perspective(){
		return "";
	}

	public String PromptRefId(){
		return "";
	}

	public String PromptRefName(){
		return "";
	}

	public String PromptRefType(){
		return "";
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 */
	public void ReconcileScope(Fusion.Xml.Scope scopeType, String strScopeOwner){

	}

	/**
	 * 
	 * @param strName
	 */
	public void RemoveParameter(String strName){

	}

	public Fusion.Xml.Scope Scope(){
		return null;
	}

	public String ScopeOwner(){
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

	/**
	 * 
	 * @param Name
	 * @param Cargo
	 */
	public void SetCargo(String Name, Object Cargo){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSystemPromptDefName(String newVal){
		SystemPromptDefName = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSystemPromptExtentionPurpose(String newVal){
		SystemPromptExtentionPurpose = newVal;
	}

	public String StorageName(){
		return "";
	}

	public String StorageSource(){
		return "";
	}

	public boolean Stored(){
		return null;
	}

	public String ToXml(){
		return "";
	}

	/**
	 * 
	 * @param funct
	 */
	public void Update(ISystemFunction funct){

	}

	/**
	 * 
	 * @param strName
	 * @param value
	 */
	public void UpdateParameter(String strName, Object value){

	}

	public Object Value(){
		return null;
	}

	private int Version(){
		return 0;
	}

}