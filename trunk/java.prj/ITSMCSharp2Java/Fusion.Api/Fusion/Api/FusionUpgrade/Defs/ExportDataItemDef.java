package Fusion.Api.FusionUpgrade.Defs;

import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:44:08
 */
public class ExportDataItemDef extends ExportItemDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:44:08
	 */
	private class Tags {

		private String BusinessObject = "BusinessObject";
		private String BusinessObjectList = "BusinessObjectList";
		private String ClassName = "ExportDataItemDef";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getBusinessObject(){
			return BusinessObject;
		}

		public String getBusinessObjectList(){
			return BusinessObjectList;
		}

		public String getClassName(){
			return ClassName;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBusinessObject(String newVal){
			BusinessObject = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBusinessObjectList(String newVal){
			BusinessObjectList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setClassName(String newVal){
			ClassName = newVal;
		}

	}

	private ArrayList m_alBusinessObjects = new ArrayList();
	private boolean m_bDataSerialized = false;
	private DataSet m_DataSet = new DataSet();

	public ExportDataItemDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param dt
	 */
	public void AddDataTable(DataTable dt){

	}

	public ArrayList BusinessObjectList(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public void ClearDataTables(){

	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public void DeSerializeDataItems(){

	}

	public DataSet ExportData(){
		return null;
	}

	public String InstanceClassName(){
		return "";
	}

	/**
	 * 
	 * @param dt
	 */
	public void RemoveDataTable(DataTable dt){

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