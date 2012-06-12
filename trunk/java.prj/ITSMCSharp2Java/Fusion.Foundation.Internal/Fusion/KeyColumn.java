package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-四月-2010 10:50:25
 */
public class KeyColumn extends SerializableDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 21-四月-2010 10:50:25
	 */
	private class Tags {

		private String Column = "Column";
		private String MapTo = "MapTo";
		private String Name = "Name";
		private String Number = "Number";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getColumn(){
			return Column;
		}

		public String getMapTo(){
			return MapTo;
		}

		public String getName(){
			return Name;
		}

		public String getNumber(){
			return Number;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setColumn(String newVal){
			Column = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMapTo(String newVal){
			MapTo = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setName(String newVal){
			Name = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setNumber(String newVal){
			Number = newVal;
		}

	}

	private int m_nColumnNumber = 0;
	private String m_strColumnName = "";
	private String m_strForeignKeyMapToColumn = "";



	public void finalize() throws Throwable {
		super.finalize();
	}

	public KeyColumn(){

	}

	public static String ClassName(){
		return "";
	}

	public KeyColumn Clone(){
		return null;
	}

	public String ColumnName(){
		return "";
	}

	public int ColumnNumber(){
		return 0;
	}

	/**
	 * 
	 * @param col
	 */
	public boolean Compare(KeyColumn col){
		return null;
	}

	/**
	 * 
	 * @param col
	 */
	protected void CopyContents(KeyColumn col){

	}

	public static KeyColumn Create(){
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
	public static SerializableDef DeserializeCreate(DefSerializer serial, SerializableDef defParent){
		return null;
	}

	public String ForeignKeyMapToColumnName(){
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