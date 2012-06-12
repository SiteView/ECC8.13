package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:54
 */
public class ContextPackageDef extends ScopedDefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:54
	 */
	private class Tags {

		private String ClassName = "ContextPackageDef";
		private String ContextPackageDef = "ContextPackageDef";
		private String Purpose = "Purpose";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClassName(){
			return ClassName;
		}

		public String getContextPackageDef(){
			return ContextPackageDef;
		}

		public String getPurpose(){
			return Purpose;
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
		public void setContextPackageDef(String newVal){
			ContextPackageDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPurpose(String newVal){
			Purpose = newVal;
		}

	}

	private String m_strPurpose = "";

	public ContextPackageDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
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
	 * @param strCategory
	 */
	public static ContextPackageDef Create(String strCategory){
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
	public static ContextPackageDef DeserializeCreate(DefSerializer serial, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strPurpose
	 */
	public boolean IsForPurpose(String strPurpose){
		return null;
	}

	public String Purpose(){
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