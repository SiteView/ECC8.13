package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:55
 */
public class ContextPackageListDef extends ContextPackageDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:55
	 */
	private class Tags {

		private String ClassName = "ContextPackageListDef";
		private String ContextPackageListDef = "ContextPackageListDef";
		private String FieldAnnotation = "FieldAnnotation";
		private String FieldCategory = "FieldCategory";
		private String FieldName = "FieldName";
		private String Relationship = "Relationship";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClassName(){
			return ClassName;
		}

		public String getContextPackageListDef(){
			return ContextPackageListDef;
		}

		public String getFieldAnnotation(){
			return FieldAnnotation;
		}

		public String getFieldCategory(){
			return FieldCategory;
		}

		public String getFieldName(){
			return FieldName;
		}

		public String getRelationship(){
			return Relationship;
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
		public void setContextPackageListDef(String newVal){
			ContextPackageListDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFieldAnnotation(String newVal){
			FieldAnnotation = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFieldCategory(String newVal){
			FieldCategory = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFieldName(String newVal){
			FieldName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRelationship(String newVal){
			Relationship = newVal;
		}

	}

	private ArrayList m_aContextPackages = new ArrayList();
	private Fusion.FieldCategory m_fldCategory = 0;
	private String m_strFieldAnnotation = "";
	private String m_strFieldCategory = "";
	private String m_strFieldName = "";
	private String m_strRelationship = "";

	public ContextPackageListDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param alResult
	 * @param strPurpose
	 * @param strAssociatedWith
	 */
	public void AddContextPackagesToList(ArrayList alResult, String strPurpose, String strAssociatedWith){

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
	public void AddFieldContextPackagesToList(ArrayList alResult, String strPurpose, String strAssociatedWith, String strRelationship, String strField, List collAnnotations, Fusion.FieldCategory fldCat){

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

	public static String ClassName(){
		return "";
	}

	protected List ContextPackages(){
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
	 * @param strCategory
	 */
	public static ContextPackageListDef Create(String strCategory){
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

	public String FieldAnnotation(){
		return "";
	}

	public String FieldCategory(){
		return "";
	}

	public String FieldName(){
		return "";
	}

	/**
	 * 
	 * @param strCategory
	 */
	public boolean IsCategory(String strCategory){
		return null;
	}

	public boolean IsCoreList(){
		return null;
	}

	public boolean IsFieldBehaviorList(){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param collAnnotations
	 * @param fldCat
	 */
	public boolean IsForField(String strField, List collAnnotations, Fusion.FieldCategory fldCat){
		return null;
	}

	public boolean IsRelationshipSpecificList(){
		return null;
	}

	public String Relationship(){
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

}