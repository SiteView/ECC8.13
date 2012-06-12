package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:24
 */
public class SysExtensionDef extends ScopedDefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:24
	 */
	private class Tags {

		private String AssociatedWith = "AssociatedWith";
		private String ClassName = "SysExtensionDef";
		private String SysExtensionDef = "SysExtensionDef";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAssociatedWith(){
			return AssociatedWith;
		}

		public String getClassName(){
			return ClassName;
		}

		public String getSysExtensionDef(){
			return SysExtensionDef;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAssociatedWith(String newVal){
			AssociatedWith = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setClassName(String newVal){
			ClassName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSysExtensionDef(String newVal){
			SysExtensionDef = newVal;
		}

	}

	private ContextPackageListDef m_ContextPackages = null;
	private String m_strAssociatedWith = "";

	public SysExtensionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param alResult
	 * @param strCategory
	 * @param strPurpose
	 * @param strAssociatedWith
	 */
	public void AddContextPackagesToList(ArrayList alResult, String strCategory, String strPurpose, String strAssociatedWith){

	}

	/**
	 * 
	 * @param alResult
	 * @param strPurpose
	 * @param strAssociatedWith
	 * @param strRelationship
	 * @param strField
	 * @param collAnnotations
	 * @param fldCat
	 */
	public void AddFieldContextPackagesToList(ArrayList alResult, String strPurpose, String strAssociatedWith, String strRelationship, String strField, List collAnnotations, FieldCategory fldCat){

	}

	/**
	 * 
	 * @param alResult
	 * @param strPurpose
	 * @param strAssociatedWith
	 * @param strRelationship
	 */
	public void AddRelatedContextPackagesToList(ArrayList alResult, String strPurpose, String strAssociatedWith, String strRelationship){

	}

	public String AssociatedWith(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public ContextPackageListDef ContextPackages(){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param defOwner
	 */
	protected void CopyContents(SerializableDef def, SerializableDef defOwner){

	}

	public static SysExtensionDef Create(){
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
	 * @param strAssociatedWith
	 */
	public boolean IsAssociatedWith(String strAssociatedWith){
		return null;
	}

	public boolean IsBusObTarget(){
		return null;
	}

	/**
	 * 
	 * @param strCategory
	 */
	public boolean IsCategory(String strCategory){
		return null;
	}

	public boolean IsCore(){
		return null;
	}

	public boolean IsRelatedBusOb(){
		return null;
	}

	public boolean IsTarget(){
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