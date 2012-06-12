package Fusion;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:55
 */
public class WordMailMergeActionDef extends ActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:55
	 */
	private class Tags {

		private String Close = "Close";
		private String Field = "Field";
		private String FieldToValueList = "FieldToValueList";
		private String Item = "Item";
		private String MainDocFilePath = "MainDocFilePath";
		private String MergeDocFilePath = "MergeDocFilePath";
		private String Print = "Print";
		private String Save = "Save";
		private String Value = "Value";
		private String WordMailMergeActionDef = "WordMailMergeActionDef";
		private String WordMailMergeDetails = "WordMailMergeDetails";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClose(){
			return Close;
		}

		public String getField(){
			return Field;
		}

		public String getFieldToValueList(){
			return FieldToValueList;
		}

		public String getItem(){
			return Item;
		}

		public String getMainDocFilePath(){
			return MainDocFilePath;
		}

		public String getMergeDocFilePath(){
			return MergeDocFilePath;
		}

		public String getPrint(){
			return Print;
		}

		public String getSave(){
			return Save;
		}

		public String getValue(){
			return Value;
		}

		public String getWordMailMergeActionDef(){
			return WordMailMergeActionDef;
		}

		public String getWordMailMergeDetails(){
			return WordMailMergeDetails;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setClose(String newVal){
			Close = newVal;
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
		public void setFieldToValueList(String newVal){
			FieldToValueList = newVal;
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
		public void setMainDocFilePath(String newVal){
			MainDocFilePath = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMergeDocFilePath(String newVal){
			MergeDocFilePath = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPrint(String newVal){
			Print = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSave(String newVal){
			Save = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValue(String newVal){
			Value = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setWordMailMergeActionDef(String newVal){
			WordMailMergeActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setWordMailMergeDetails(String newVal){
			WordMailMergeDetails = newVal;
		}

	}

	private boolean m_bClose = false;
	private boolean m_bPrint = false;
	private boolean m_bSave = false;
	private List m_htMergeFieldToValue = new LinkedList();
	private String m_strMainDocFilePath = "";
	private String m_strMergeDocFilePath = "";

	public WordMailMergeActionDef(){

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

	public boolean Close(){
		return false;
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
	 * @param correction
	 * @param bJustCollect
	 * @param strAssociatedBusOb
	 */
	public boolean CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect, String strAssociatedBusOb){
		return false;
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	/**
	 * 
	 * @param list
	 */
	public void GatherPromptDefs(List list){

	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public boolean HasTagsContainingTagCategory(String strTagCategoryName){
		return false;
	}

	public String MainDocFilePath(){
		return "";
	}

	public String MergeDocFilePath(){
		return "";
	}

	public Map MergeFieldToValue(){
		return null;
	}

	public boolean Print(){
		return false;
	}

	public boolean Save(){
		return false;
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