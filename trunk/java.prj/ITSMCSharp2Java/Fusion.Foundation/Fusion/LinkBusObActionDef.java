package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:03
 */
public class LinkBusObActionDef extends CreateChildBusObActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:03
	 */
	private class Tags {

		private String LinkBusObActionDef = "LinkBusObActionDef";
		private String LinkBusObDetails = "LinkBusObDetails";
		private String LinkBusObSource = "LinkBusObSource";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getLinkBusObActionDef(){
			return LinkBusObActionDef;
		}

		public String getLinkBusObDetails(){
			return LinkBusObDetails;
		}

		public String getLinkBusObSource(){
			return LinkBusObSource;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLinkBusObActionDef(String newVal){
			LinkBusObActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLinkBusObDetails(String newVal){
			LinkBusObDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLinkBusObSource(String newVal){
			LinkBusObSource = newVal;
		}

	}

	private String m_strLinkRecordSource = "";

	public LinkBusObActionDef(){

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

	public IList GetExposedObjects(){
		return null;
	}

	public String LinkRecordSource(){
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

	public String SerializeSpecificPropertyRoot(){
		return "";
	}

}