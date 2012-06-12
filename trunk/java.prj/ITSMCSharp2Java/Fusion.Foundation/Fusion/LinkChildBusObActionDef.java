package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:04
 */
public class LinkChildBusObActionDef extends CreateChildBusObActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:04
	 */
	private class Tags {

		private String ChildRecId = "ChildRecId";
		private String LinkChildBusObActionDef = "LinkChildBusObActionDef";
		private String StaticLink = "StaticLink";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getChildRecId(){
			return ChildRecId;
		}

		public String getLinkChildBusObActionDef(){
			return LinkChildBusObActionDef;
		}

		public String getStaticLink(){
			return StaticLink;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setChildRecId(String newVal){
			ChildRecId = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLinkChildBusObActionDef(String newVal){
			LinkChildBusObActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setStaticLink(String newVal){
			StaticLink = newVal;
		}

	}

	private boolean m_bStaticLink = false;
	private String m_strChildRecId = "";

	public LinkChildBusObActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
		return "";
	}

	public String ChildRecId(){
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

	public boolean StaticLink(){
		return null;
	}

}