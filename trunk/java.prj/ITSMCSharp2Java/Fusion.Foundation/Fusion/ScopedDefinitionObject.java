package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:00
 */
public abstract class ScopedDefinitionObject extends DefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:00
	 */
	private class Tags {

		private String ShowInNavigator = "ShowInNavigator";
		private String ShowOnMenu = "ShowOnMenu";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getShowInNavigator(){
			return ShowInNavigator;
		}

		public String getShowOnMenu(){
			return ShowOnMenu;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setShowInNavigator(String newVal){
			ShowInNavigator = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setShowOnMenu(String newVal){
			ShowOnMenu = newVal;
		}

	}

	private boolean m_bShowInNavigator = false;
	private boolean m_bShowOnMenu = false;

	public ScopedDefinitionObject(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param def
	 * @param defOwner
	 */
	protected void CopyContents(SerializableDef def, SerializableDef defOwner){

	}

	protected boolean DefinitionSupportsScope(){
		return false;
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public String Flags(){
		return "";
	}

	/**
	 * 
	 * @param serial
	 */
	public DefSerializer Serialize(DefSerializer serial){
		return null;
	}

	public boolean ShowInNavigator(){
		return false;
	}

	public boolean ShowOnMenu(){
		return false;
	}

}