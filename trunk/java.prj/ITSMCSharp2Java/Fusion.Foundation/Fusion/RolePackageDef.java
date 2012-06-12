package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:49
 */
public class RolePackageDef extends ScopedDefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:49
	 */
	private class Tags {

		private String ClassName = "RolePackageDef";
		private String RolePackageDef = "RolePackageDef";
		private String SubPackageList = "SubPackageList";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClassName(){
			return ClassName;
		}

		public String getRolePackageDef(){
			return RolePackageDef;
		}

		public String getSubPackageList(){
			return SubPackageList;
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
		public void setRolePackageDef(String newVal){
			RolePackageDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSubPackageList(String newVal){
			SubPackageList = newVal;
		}

	}

	private ArrayList m_alSubPackages = new ArrayList();

	public RolePackageDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param defFrom
	 * @param defOwner
	 */
	protected void CopyContents(SerializableDef defFrom, SerializableDef defOwner){

	}

	public static RolePackageDef Create(){
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
	public static RolePackageDef DeserializeCreate(DefSerializer serial, SerializableDef defParent){
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

	public List SubPackages(){
		return null;
	}

}