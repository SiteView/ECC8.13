package Fusion;
import java.util.Hashtable;
import java.util.List;
import java.util.Map;

import Fusion.Foundation.CompareInfo;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:06
 */
public abstract class DefinitionObject extends SerializableDef implements IDefinition, IAggregate {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:06
	 */
	protected enum SerializeExcludeFlags {
		Alias,
		All,
		Desc,
		None,
		StorageInfo,
		Stored,
		System
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:06
	 */
	private class Tags {

		private String Alias = "Alias";
		private String Annotation = "Annotation";
		private String AnnotationList = "AnnotationList";
		private String Category = "Category";
		private String Content = "Content";
		private String Description = "Description";
		private String EditorRights = "EditorRights";
		private String Folder = "Folder";
		private String LinkedTo = "LinkedTo";
		private String Name = "Name";
		private String Package = "Package";
		private String Perspective = "Perspective";
		private String Scope = "Scope";
		private String ScopeOwner = "ScopeOwner";
		private String StorageName = "StorageName";
		private String StorageSource = "StorageSource";
		private String Stored = "Stored";
		private String System = "System";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAlias(){
			return Alias;
		}

		public String getAnnotation(){
			return Annotation;
		}

		public String getAnnotationList(){
			return AnnotationList;
		}

		public String getCategory(){
			return Category;
		}

		public String getContent(){
			return Content;
		}

		public String getDescription(){
			return Description;
		}

		public String getEditorRights(){
			return EditorRights;
		}

		public String getFolder(){
			return Folder;
		}

		public String getLinkedTo(){
			return LinkedTo;
		}

		public String getName(){
			return Name;
		}

		public String getPackage(){
			return Package;
		}

		public String getPerspective(){
			return Perspective;
		}

		public String getScope(){
			return Scope;
		}

		public String getScopeOwner(){
			return ScopeOwner;
		}

		public String getStorageName(){
			return StorageName;
		}

		public String getStorageSource(){
			return StorageSource;
		}

		public String getStored(){
			return Stored;
		}

		public String getSystem(){
			return System;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAlias(String newVal){
			Alias = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAnnotation(String newVal){
			Annotation = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAnnotationList(String newVal){
			AnnotationList = newVal;
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
		public void setContent(String newVal){
			Content = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDescription(String newVal){
			Description = newVal;
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
		public void setFolder(String newVal){
			Folder = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLinkedTo(String newVal){
			LinkedTo = newVal;
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
		public void setPackage(String newVal){
			Package = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPerspective(String newVal){
			Perspective = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setScope(String newVal){
			Scope = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setScopeOwner(String newVal){
			ScopeOwner = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setStorageName(String newVal){
			StorageName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setStorageSource(String newVal){
			StorageSource = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setStored(String newVal){
			Stored = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSystem(String newVal){
			System = newVal;
		}

	}

	private static CaseInsensitiveComparer comparer = new CaseInsensitiveComparer();
	private static CaseInsensitiveHashCodeProvider hashProvider = new CaseInsensitiveHashCodeProvider();
	private AggregateBase m_aggregate = null;
	private boolean m_bStored = false;
	private Fusion.DefRights m_DefRights = null;
	private static final Hashtable m_empty = new Hashtable();
	private Hashtable m_htAnnotations = new Hashtable(hashProvider, comparer);
	private Hashtable m_htCargo = new Hashtable(hashProvider, comparer);
	private String m_OriginalName = "";
	private Fusion.Xml.Scope m_OriginalScope = Fusion.Xml.Scope.Global;
	private String m_OriginalstrScopeOwner = "GLOBAL";
	private System.Resources.ResourceManager m_ResourceManager = null;
	private Fusion.Xml.Scope m_Scope = Fusion.Xml.Scope.Global;
	private SerializeExcludeFlags m_SerializeExcludeFlags = 0;
	private String m_strAlias = "";
	private String m_strDesc = "";
	private String m_strExtensionPackage = "";
	private String m_strFolder = "";
	private String m_strLinkedTo = "";
	private String m_strPerspective = "(Base)";
	private String m_strScopeOwner = "GLOBAL";
	private String m_strStorageName = "";
	private String m_strStorageSource = "Internal";
	private String m_strXmlCategory = "STANDARD";
	private String standard = "STANDARD";

	public DefinitionObject(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strName
	 * @param strValue
	 */
	public void AddAnnotation(String strName, String strValue){

	}

	public AggregateBase Aggregate(){
		return null;
	}

	public String AggregateClassName(){
		return "";
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

	public boolean CanChangeDatabaseProperties(){
		return false;
	}

	public boolean CanEdit(){
		return false;
	}

	public String CategoryAsString(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param strName
	 */
	public void ClearCargo(String strName){

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
	 * @param defOb
	 */
	private List<String> CompareAnnotations(DefinitionObject defOb){
		return null;
	}

	/**
	 * 
	 * @param defToCompare
	 * @param ciParent
	 */
	public void CompareContents(SerializableDef defToCompare, CompareInfo ciParent){

	}

	protected boolean ConstructorTakesArgument(){
		return false;
	}

	/**
	 * 
	 * @param htAnn
	 */
	protected Hashtable CopyAnnotations(Hashtable htAnn){
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
	 * @param factory
	 */
	public AggregateBase CreateAggregate(IAggregateFactory factory){
		return null;
	}

	protected IDefinition CreateCloneObject(){
		return null;
	}

	protected Fusion.DefRights CreateDefRights(){
		return null;
	}

	public String DataStore(){
		return "";
	}

	protected boolean DefinitionSupportsPerspective(){
		return false;
	}

	protected boolean DefinitionSupportsScope(){
		return false;
	}

	public String DefinitionType(){
		return "";
	}

	public Fusion.DefRights DefRights(){
		return null;
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
	 * @param typeItem
	 */
	protected void DeserializeDefRights(DefSerializer serial, Type typeItem){

	}

	/**
	 * 
	 * @param sef
	 */
	protected void ExcludeSerializeItem(SerializeExcludeFlags sef){

	}

	public String Flags(){
		return "";
	}

	public String Folder(){
		return "";
	}

	/**
	 * 
	 * @param strName
	 */
	public String GetAnnotationValue(String strName){
		return "";
	}

	/**
	 * 
	 * @param strName
	 * @param nDefaultValue
	 */
	public int GetAnnotationValueAsInt(String strName, int nDefaultValue){
		return 0;
	}

	/**
	 * 
	 * @param strName
	 */
	public Object GetCargo(String strName){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public String GetCargoAsString(String strName){
		return "";
	}

	/**
	 * 
	 * @param strName
	 */
	public boolean HasAnnotation(String strName){
		return false;
	}

	private String Id(){
		return "";
	}

	/**
	 * 
	 * @param sef
	 */
	protected void IncludeSerializeItem(SerializeExcludeFlags sef){

	}

	public String InstanceClassName(){
		return "";
	}

	public boolean IsDefDirty(){
		return false;
	}

	/**
	 * 
	 * @param strID
	 */
	public boolean IsMatchingId(String strID){
		return false;
	}

	public String LinkedTo(){
		return "";
	}

	public String Name(){
		return "";
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

	public String Package(){
		return "";
	}

	public String Perspective(){
		return "";
	}

	/**
	 * 
	 * @param element
	 */
	protected Hashtable ReadAnnotations(XmlElement element){
		return null;
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
	 * @param strXml
	 */
	public void RedefineFromXml(String strXml){

	}

	/**
	 * 
	 * @param strName
	 */
	public void RemoveAnnotation(String strName){

	}

	/**
	 * 
	 * @param def
	 */
	public boolean ReportConflicts(IDefinition def){
		return false;
	}

	protected boolean RequiresStorageTag(){
		return false;
	}

	public String ResourceAlias(){
		return "";
	}

	public String ResourceDescription(){
		return "";
	}

	protected System.Resources.ResourceManager ResourceManager(){
		return null;
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

	/**
	 * 
	 * @param serial
	 */
	protected void SerializeAnnotations(DefSerializer serial){

	}

	/**
	 * 
	 * @param serial
	 * @param typeItem
	 */
	protected void SerializeDefRights(DefSerializer serial, Type typeItem){

	}

	/**
	 * 
	 * @param strName
	 * @param oCargo
	 */
	public void SetCargo(String strName, Object oCargo){

	}

	/**
	 * 
	 * @param sef
	 */
	protected boolean ShouldExcludeItem(SerializeExcludeFlags sef){
		return false;
	}

	public String StorageName(){
		return "";
	}

	public String StorageSource(){
		return "";
	}

	public boolean Stored(){
		return false;
	}

	protected boolean StoredDefault(){
		return false;
	}

	public String ToXml(){
		return "";
	}

	protected boolean UseBaseDefRights(){
		return false;
	}

	protected boolean UseResources(){
		return false;
	}

	/**
	 * 
	 * @param parentDef
	 */
	protected boolean Validate(IDefinition parentDef){
		return false;
	}

	public int Version(){
		return 0;
	}

	public String Visualize(){
		return "";
	}

	public String XmlCategory(){
		return "";
	}

}