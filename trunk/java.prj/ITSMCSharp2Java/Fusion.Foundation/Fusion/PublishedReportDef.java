package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:36
 */
public class PublishedReportDef extends ScopedDefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:36
	 */
	private class Tags {

		private String Alias = "Alias";
		private String AliasToTableList = "AliasToTableList";
		private String Filename = "Filename";
		private String Item = "Item";
		private String PublishedReportDef = "PublishedReportDef";
		private String Table = "Table";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAlias(){
			return Alias;
		}

		public String getAliasToTableList(){
			return AliasToTableList;
		}

		public String getFilename(){
			return Filename;
		}

		public String getItem(){
			return Item;
		}

		public String getPublishedReportDef(){
			return PublishedReportDef;
		}

		public String getTable(){
			return Table;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAlias(String newVal){
			Alias = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAliasToTableList(String newVal){
			AliasToTableList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFilename(String newVal){
			Filename = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setItem(String newVal){
			Item = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPublishedReportDef(String newVal){
			PublishedReportDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTable(String newVal){
			Table = newVal;
		}

	}

	private Hashtable m_htAliasToTable = new Hashtable();
	private String m_strFilename = "";

	public PublishedReportDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public Map AliasToTable(){
		return null;
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
	 * @param defParent
	 */
	public static SerializableDef DeserializeCreate(DefSerializer serial, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strSubType
	 */
	public static IDefinition DeserializeCreateNewForEditing(String strSubType){
		return null;
	}

	public String Filename(){
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