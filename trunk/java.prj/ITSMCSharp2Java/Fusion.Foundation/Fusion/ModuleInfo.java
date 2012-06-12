package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:11
 */
public class ModuleInfo {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:11
	 */
	private class Tags {

		private String Critical = "Critical";
		private String MethodName = "MethodName";
		private String Module = "Module";
		private String Name = "Name";
		private String Snapin = "Snapin";
		private String TypeName = "TypeName";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getCritical(){
			return Critical;
		}

		public String getMethodName(){
			return MethodName;
		}

		public String getModule(){
			return Module;
		}

		public String getName(){
			return Name;
		}

		public String getSnapin(){
			return Snapin;
		}

		public String getTypeName(){
			return TypeName;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCritical(String newVal){
			Critical = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMethodName(String newVal){
			MethodName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setModule(String newVal){
			Module = newVal;
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
		public void setSnapin(String newVal){
			Snapin = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTypeName(String newVal){
			TypeName = newVal;
		}

	}

	private static CaseInsensitiveComparer comparer = new CaseInsensitiveComparer();
	private static CaseInsensitiveHashCodeProvider hashProvider = new CaseInsensitiveHashCodeProvider();
	private System.Reflection.Assembly m_Assembly;
	private boolean m_bCritical;
	private boolean m_bFirstTimeForParent;
	private boolean m_bLoaded;
	private Hashtable m_htUncategorizedResources;
	private System.Reflection.Assembly m_ParentSatelliteAssembly;
	private Hashtable m_Resources;
	private System.Reflection.Assembly m_SatelliteAssembly;
	private String m_strAssemblyName;
	private String m_strError;
	private String m_strMethodName;
	private String m_strName;
	private String m_strTypeName;
	private String MODULEINFOFILE = "ModuleInfo.xml";

	public ModuleInfo(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param xe
	 */
	public ModuleInfo(XmlElement xe){

	}

	/**
	 * 
	 * @param strName
	 * @param strAssemblyName
	 * @param assembly
	 * @param bCritical
	 */
	public ModuleInfo(String strName, String strAssemblyName, System.Reflection.Assembly assembly, boolean bCritical){

	}

	public System.Reflection.Assembly Assembly(){
		return null;
	}

	public String AssemblyName(){
		return "";
	}

	public String Error(){
		return "";
	}

	/**
	 * 
	 * @param strResourceName
	 */
	public String GetCorrectCasingForResource(String strResourceName){
		return "";
	}

	/**
	 * 
	 * @param strDefName
	 */
	public String GetManifestResourceNameFromDefName(String strDefName){
		return "";
	}

	/**
	 * 
	 * @param xmlDoc
	 */
	public XmlElement GetModuleInfoSetting(XmlDocument xmlDoc){
		return null;
	}

	/**
	 * 
	 * @param al
	 */
	public static XmlElement GetModuleInfoXml(System.Reflection.Assembly al){
		return null;
	}

	public IModule GetModuleSnapin(){
		return null;
	}

	/**
	 * 
	 * @param strManifestResourceName
	 */
	private ResourceInfo GetResourceInfo(String strManifestResourceName){
		return null;
	}

	/**
	 * 
	 * @param strCategory
	 * @param strPrimaryTag
	 */
	public ResourceInfo GetResourceInfo(String strCategory, String strPrimaryTag){
		return null;
	}

	/**
	 * 
	 * @param strCategory
	 * @param strSubCategory
	 * @param strPrimaryTag
	 */
	public ResourceInfo GetResourceInfo(String strCategory, String strSubCategory, String strPrimaryTag){
		return null;
	}

	/**
	 * 
	 * @param strKey
	 */
	private List GetResourceInfoCollection(String strKey){
		return null;
	}

	public List GetResourceInfoList(){
		return null;
	}

	/**
	 * 
	 * @param strCategory
	 */
	public List GetResourceInfoList(String strCategory){
		return null;
	}

	/**
	 * 
	 * @param strCategory
	 * @param strSubCategory
	 */
	public List GetResourceInfoList(String strCategory, String strSubCategory){
		return null;
	}

	public boolean IsCritical(){
		return null;
	}

	public boolean IsLoaded(){
		return null;
	}

	public String KeyName(){
		return "";
	}

	private void LoadAssembly(){

	}

	private void LoadParentSatelliteAssembly(){

	}

	public void LoadResourceInfo(){

	}

	private void LoadSatelliteAssembly(){

	}

	private void LoadSnapinInfo(){

	}

	public String Name(){
		return "";
	}

	public System.Reflection.Assembly ParentSatelliteAssembly(){
		return null;
	}

	public System.Reflection.Assembly SatelliteAssembly(){
		return null;
	}

	public String SimpleAssemblyName(){
		return "";
	}

}