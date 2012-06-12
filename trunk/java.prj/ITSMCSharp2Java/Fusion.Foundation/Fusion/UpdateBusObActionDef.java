package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:44
 */
public class UpdateBusObActionDef extends CreateUpdateBusObActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:44
	 */
	private class Tags {

		private String BusObSource = "BusObSource";
		private String UpdateBusObActionDef = "UpdateBusObActionDef";
		private String UpdateBusObDetails = "UpdateBusObDetails";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getBusObSource(){
			return BusObSource;
		}

		public String getUpdateBusObActionDef(){
			return UpdateBusObActionDef;
		}

		public String getUpdateBusObDetails(){
			return UpdateBusObDetails;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBusObSource(String newVal){
			BusObSource = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setUpdateBusObActionDef(String newVal){
			UpdateBusObActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setUpdateBusObDetails(String newVal){
			UpdateBusObDetails = newVal;
		}

	}

	private String m_strBusObSource = "";

	public UpdateBusObActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
		return "";
	}

	public String BusinessObjectSource(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public boolean ConsumesContextBusinessObject(){
		return null;
	}

	/**
	 * 
	 * @param expOb
	 */
	public boolean ConsumesExposedObject(ExposedObject expOb){
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
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

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