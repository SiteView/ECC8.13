package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-四月-2010 10:50:23
 */
public class IndexColumn extends SerializableDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 21-四月-2010 10:50:23
	 */
	private class Tags {

		private String Ascending = "ASC";
		private String Column = "Column";
		private String Descending = "DESC";
		private String Name = "Name";
		private String Number = "Number";
		private String Order = "Order";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAscending(){
			return Ascending;
		}

		public String getColumn(){
			return Column;
		}

		public String getDescending(){
			return Descending;
		}

		public String getName(){
			return Name;
		}

		public String getNumber(){
			return Number;
		}

		public String getOrder(){
			return Order;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAscending(String newVal){
			Ascending = newVal;
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
		public void setDescending(String newVal){
			Descending = newVal;
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

		/**
		 * 
		 * @param newVal
		 */
		public void setOrder(String newVal){
			Order = newVal;
		}

	}

	private boolean m_bAscending = true;
	private int m_nColumnNumber = 0;
	private String m_strColumnName = "";



	public void finalize() throws Throwable {
		super.finalize();
	}

	public IndexColumn(){

	}

	public boolean Ascending(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public IndexColumn Clone(){
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
	public boolean Compare(IndexColumn col){
		return null;
	}

	/**
	 * 
	 * @param col
	 */
	protected void CopyContents(IndexColumn col){

	}

	public static IndexColumn Create(){
		return null;
	}

	public boolean Descending(){
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