package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:26
 */
public class SystemFunctionDef extends ScopedDefinitionObject implements IDefinition, ISystemFunction {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:26
	 */
	public class ParameterName {

		private String DataType = "DataType";

		public ParameterName(){

		}

		public void finalize() throws Throwable {

		}

		public String getDataType(){
			return DataType;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDataType(String newVal){
			DataType = newVal;
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:26
	 */
	private class Tags {

		private String Category = "Category";
		private String Name = "Name";
		private String Parameter = "Parameter";
		private String ParameterList = "ParameterList";
		private String SystemFunction = "SystemFunction";
		private String Value = "Value";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getCategory(){
			return Category;
		}

		public String getName(){
			return Name;
		}

		public String getParameter(){
			return Parameter;
		}

		public String getParameterList(){
			return ParameterList;
		}

		public String getSystemFunction(){
			return SystemFunction;
		}

		public String getValue(){
			return Value;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCategory(String newVal){
			Category = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setName(String newVal){
			Name = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParameter(String newVal){
			Parameter = newVal;
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
		public void setSystemFunction(String newVal){
			SystemFunction = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValue(String newVal){
			Value = newVal;
		}

	}

	private static CaseInsensitiveComparer comparer = new CaseInsensitiveComparer();
	private static CaseInsensitiveHashCodeProvider hashProvider = new CaseInsensitiveHashCodeProvider();
	private Hashtable m_dictParameters;
	private String SystemFunctionDefName = "SystemFunctionDef";
	private String SystemFunctionExtentionPurpose = "SystemFunctionExtension";



	public void finalize() throws Throwable {
		super.finalize();
	}

	public SystemFunctionDef(){

	}

	/**
	 * 
	 * @param strName
	 * @param dataType
	 */
	public SystemFunctionDef(String strName, SystemFunctionValueType dataType){

	}

	/**
	 * 
	 * @param dictParameters
	 */
	public void AddParameter(IDictionary dictParameters){

	}

	/**
	 * 
	 * @param strName
	 * @param value
	 */
	public void AddParameter(String strName, Object value){

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

	public String Category(){
		return "";
	}

	public String CategoryAsString(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param Name
	 */
	public void ClearCargo(String Name){

	}

	public void ClearParameters(){

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

	/**
	 * 
	 * @param strName
	 * @param type
	 */
	public static SystemFunctionDef Create(String strName, SystemFunctionValueType type){
		return null;
	}

	/**
	 * 
	 * @param xePrompt
	 */
	public static ISystemFunction CreateFromXml(XmlElement xePrompt){
		return null;
	}

	public SystemFunctionValueType DataType(){
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
	 * @param strCategory
	 */
	public static ISystemFunction DeserializeCreateNewForEditing(String strCategory){
		return null;
	}

	public String Flags(){
		return "";
	}

	public String Folder(){
		return "";
	}

	/**
	 * 
	 * @param text1
	 */
	private void FromXml(String text1){

	}

	/**
	 * 
	 * @param Name
	 */
	public Object GetCargo(String Name){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Object GetParameter(String strName){
		return null;
	}

	public String getSystemFunctionDefName(){
		return SystemFunctionDefName;
	}

	public String getSystemFunctionExtentionPurpose(){
		return SystemFunctionExtentionPurpose;
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
	public void setSystemFunctionDefName(String newVal){
		SystemFunctionDefName = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSystemFunctionExtentionPurpose(String newVal){
		SystemFunctionExtentionPurpose = newVal;
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
	 * @param function
	 */
	public void Update(ISystemFunction function){

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