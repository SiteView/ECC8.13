package Fusion;

import java.io.Serializable;
import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:39
 */
public class GridColumnSetting extends SerializableDef implements Serializable {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:39
	 */
	private class Tags {

		private String Aggregation = "Aggregation";
		private String Alias = "Alias";
		private String Average = "Average";
		private String ClassName = "GridColumnSetting";
		private String ColumnSetting = "ColumnSetting";
		private String ComparisonValue = "ComparisonValue";
		private String ConditionCount = "ConditionCount";
		private String Count = "Count";
		private String Filtering = "Filtering";
		private String GridColumnFilteringList = "GridColumnFilteringList";
		private String GroupIndex = "GroupIndex";
		private String Index = "Index";
		private String Maximum = "Maximum";
		private String Minimum = "Minimum";
		private String SortOption = "SortOption";
		private String Sum = "Sum";
		private String Tag = "Tag";
		private String Width = "Width";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAggregation(){
			return Aggregation;
		}

		public String getAlias(){
			return Alias;
		}

		public String getAverage(){
			return Average;
		}

		public String getClassName(){
			return ClassName;
		}

		public String getColumnSetting(){
			return ColumnSetting;
		}

		public String getComparisonValue(){
			return ComparisonValue;
		}

		public String getConditionCount(){
			return ConditionCount;
		}

		public String getCount(){
			return Count;
		}

		public String getFiltering(){
			return Filtering;
		}

		public String getGridColumnFilteringList(){
			return GridColumnFilteringList;
		}

		public String getGroupIndex(){
			return GroupIndex;
		}

		public String getIndex(){
			return Index;
		}

		public String getMaximum(){
			return Maximum;
		}

		public String getMinimum(){
			return Minimum;
		}

		public String getSortOption(){
			return SortOption;
		}

		public String getSum(){
			return Sum;
		}

		public String getTag(){
			return Tag;
		}

		public String getWidth(){
			return Width;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAggregation(String newVal){
			Aggregation = newVal;
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
		public void setAverage(String newVal){
			Average = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setClassName(String newVal){
			ClassName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setColumnSetting(String newVal){
			ColumnSetting = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setComparisonValue(String newVal){
			ComparisonValue = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setConditionCount(String newVal){
			ConditionCount = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCount(String newVal){
			Count = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFiltering(String newVal){
			Filtering = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setGridColumnFilteringList(String newVal){
			GridColumnFilteringList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setGroupIndex(String newVal){
			GroupIndex = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setIndex(String newVal){
			Index = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMaximum(String newVal){
			Maximum = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMinimum(String newVal){
			Minimum = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSortOption(String newVal){
			SortOption = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSum(String newVal){
			Sum = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTag(String newVal){
			Tag = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setWidth(String newVal){
			Width = newVal;
		}

	}

	private int ASCENDING = 1;
	private int DESCENDING = 2;
	private ArrayList m_alGridColumnFilteringDefs;
	private boolean m_bAvg;
	private boolean m_bCnt;
	private boolean m_bMax;
	private boolean m_bMin;
	private boolean m_bSum;
	private int m_nConditionCount;
	private int m_nGroupIndex;
	private int m_nIndex;
	private int m_nSortOption;
	private int m_nWidth;
	private String m_strComparisonValue;
	private String m_strDisplayName;
	private String m_strTag;
	private int NONE = 0;
	private int NOTGROUPBYCOLUMN = 0;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public GridColumnSetting(){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public GridColumnSetting(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param gridColumnFilteringDef
	 */
	public void AddGridColumnFilteringDef(GridColumnFilteringDef gridColumnFilteringDef){

	}

	public boolean Average(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public void ClearGridColumnFilteringDefs(){

	}

	public GridColumnSetting Clone(){
		return null;
	}

	public String ComparisonValue(){
		return "";
	}

	public int ConditionCount(){
		return 0;
	}

	/**
	 * 
	 * @param def
	 * @param defOwner
	 */
	protected void CopyContents(SerializableDef def, SerializableDef defOwner){

	}

	public boolean Count(){
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

	public String DisplayName(){
		return "";
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

	public GridColumnFilteringDef[] GridColumnFilteringConditions(){
		return null;
	}

	public int GroupIndex(){
		return 0;
	}

	public int Index(){
		return 0;
	}

	public boolean Maximum(){
		return null;
	}

	public boolean Minimum(){
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

	public int SortOption(){
		return 0;
	}

	public boolean Sum(){
		return null;
	}

	public String Tag(){
		return "";
	}

	public int Width(){
		return 0;
	}

}