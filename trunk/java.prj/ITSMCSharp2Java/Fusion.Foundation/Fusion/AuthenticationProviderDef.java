package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:42
 */
public class AuthenticationProviderDef extends DefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:42
	 */
	private class Tags {

		private String Category = "Category";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getCategory(){
			return Category;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCategory(String newVal){
			Category = newVal;
		}

	}

	private String m_sCategory = null;

	public AuthenticationProviderDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param sCategory
	 */
	public AuthenticationProviderDef(String sCategory){

	}

	public String Category(){
		return "";
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
	 * @param serial
	 */
	public DefSerializer Serialize(DefSerializer serial){
		return null;
	}

	public String SerializeGeneralPropertyRoot(){
		return "";
	}

	public String SerializeSpecificPropertyRoot(){
		return "";
	}

	public String ToXml(){
		return "";
	}

}