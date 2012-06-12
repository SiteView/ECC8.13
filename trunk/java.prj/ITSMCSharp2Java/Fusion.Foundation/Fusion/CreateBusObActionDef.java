package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:55
 */
public class CreateBusObActionDef extends CreateUpdateBusObActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:55
	 */
	private class Tags {

		private String CreateBusObActionDef = "CreateBusObActionDef";
		private String CreateBusObDetails = "CreateBusObDetails";
		private String IsParent = "IsParent";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getCreateBusObActionDef(){
			return CreateBusObActionDef;
		}

		public String getCreateBusObDetails(){
			return CreateBusObDetails;
		}

		public String getIsParent(){
			return IsParent;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCreateBusObActionDef(String newVal){
			CreateBusObActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCreateBusObDetails(String newVal){
			CreateBusObDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setIsParent(String newVal){
			IsParent = newVal;
		}

	}

	private boolean m_bIsParent = false;

	public CreateBusObActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
		return "";
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
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public IList GetExposedObjects(){
		return null;
	}

	public boolean IsParent(){
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

	public String SerializeSpecificPropertyRoot(){
		return "";
	}

}