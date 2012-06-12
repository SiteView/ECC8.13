package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:17
 */
public class SimpleContextPackageDef extends ContextPackageDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:18
	 */
	private class Tags {

		private String ClassName = "SimpleContextPackageDef";
		private String DefName = "DefName";
		private String DefScope = "DefScope";
		private String DefScopeOwner = "DefScopeOwner";
		private String FormMode = "FormMode";
		private String GridMode = "GridMode";
		private String MirrorMenu = "MirrorMenu";
		private String SimpleContextPackageDef = "SimpleContextPackageDef";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClassName(){
			return ClassName;
		}

		public String getDefName(){
			return DefName;
		}

		public String getDefScope(){
			return DefScope;
		}

		public String getDefScopeOwner(){
			return DefScopeOwner;
		}

		public String getFormMode(){
			return FormMode;
		}

		public String getGridMode(){
			return GridMode;
		}

		public String getMirrorMenu(){
			return MirrorMenu;
		}

		public String getSimpleContextPackageDef(){
			return SimpleContextPackageDef;
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
		public void setDefName(String newVal){
			DefName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDefScope(String newVal){
			DefScope = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDefScopeOwner(String newVal){
			DefScopeOwner = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFormMode(String newVal){
			FormMode = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setGridMode(String newVal){
			GridMode = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMirrorMenu(String newVal){
			MirrorMenu = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSimpleContextPackageDef(String newVal){
			SimpleContextPackageDef = newVal;
		}

	}

	private boolean m_bFormMode = false;
	private boolean m_bGridMode = false;
	private boolean m_bMirrorMenu = false;
	private Scope m_DefScope = Scope.Internal;
	private String m_strDefName = "";
	private String m_strDefScopeOwner = "INTERNAL";

	public SimpleContextPackageDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param alResult
	 * @param strCategory
	 * @param strPurpose
	 * @param strRelationship
	 * @param strField
	 * @param collAnnotations
	 * @param fldCat
	 */
	public void AddContextPackagesToList(ArrayList alResult, String strCategory, String strPurpose, String strRelationship, String strField, List collAnnotations, FieldCategory fldCat){

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

	public String DefName(){
		return "";
	}

	public Scope DefScope(){
		return null;
	}

	public String DefScopeOwner(){
		return "";
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public boolean FormMode(){
		return null;
	}

	public boolean GridMode(){
		return null;
	}

	public boolean MirrorMenu(){
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

}