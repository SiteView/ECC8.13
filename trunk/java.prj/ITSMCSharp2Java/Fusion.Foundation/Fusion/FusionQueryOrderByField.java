package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:34
 */
public class FusionQueryOrderByField {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:34
	 */
	public class Tags {

		private String EndRow = "EndRow";
		private String Field = "Field";
		private String OrderByField = "OrderByField";
		private String OrderByList = "OrderByList";
		private String SortOrder = "SortOrder";
		private String StartRow = "StartRow";
		private String valAscending = "ASC";
		private String valDbNull = "(DbNull)";
		private String valDescending = "DESC";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getEndRow(){
			return EndRow;
		}

		public String getField(){
			return Field;
		}

		public String getOrderByField(){
			return OrderByField;
		}

		public String getOrderByList(){
			return OrderByList;
		}

		public String getSortOrder(){
			return SortOrder;
		}

		public String getStartRow(){
			return StartRow;
		}

		public String getvalAscending(){
			return valAscending;
		}

		public String getvalDbNull(){
			return valDbNull;
		}

		public String getvalDescending(){
			return valDescending;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setEndRow(String newVal){
			EndRow = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setField(String newVal){
			Field = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setOrderByField(String newVal){
			OrderByField = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setOrderByList(String newVal){
			OrderByList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSortOrder(String newVal){
			SortOrder = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setStartRow(String newVal){
			StartRow = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setvalAscending(String newVal){
			valAscending = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setvalDbNull(String newVal){
			valDbNull = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setvalDescending(String newVal){
			valDescending = newVal;
		}

	}

	private boolean m_bAscending;
	private Object m_oEndValue;
	private Object m_oStartValue;
	private String m_strName;



	public void finalize() throws Throwable {

	}

	public FusionQueryOrderByField(){

	}

	/**
	 * 
	 * @param strFieldName
	 * @param bAscending
	 */
	public FusionQueryOrderByField(String strFieldName, boolean bAscending){

	}

	/**
	 * 
	 * @param strFieldName
	 * @param bAscending
	 * @param oStartValue
	 * @param oEndValue
	 */
	public FusionQueryOrderByField(String strFieldName, boolean bAscending, Object oStartValue, Object oEndValue){

	}

	public boolean Ascending(){
		return null;
	}

	public FusionQueryOrderByField Clone(){
		return null;
	}

	/**
	 * 
	 * @param fldOrderBy
	 */
	public void CopyContents(FusionQueryOrderByField fldOrderBy){

	}

	public Object EndValue(){
		return null;
	}

	/**
	 * 
	 * @param xeOrderByFld
	 */
	public void FromXml(XmlElement xeOrderByFld){

	}

	public String Name(){
		return "";
	}

	public Object StartValue(){
		return null;
	}

	/**
	 * 
	 * @param writerXml
	 */
	public void ToXml(XmlTextWriter writerXml){

	}

}