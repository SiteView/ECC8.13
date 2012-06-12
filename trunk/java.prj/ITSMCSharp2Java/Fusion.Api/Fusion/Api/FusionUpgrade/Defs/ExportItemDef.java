package Fusion.Api.FusionUpgrade.Defs;
import java.util.ArrayList;

import Fusion.Api.IFusionApi;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:44:20
 */
public class ExportItemDef extends SerializableDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:44:20
	 */
	private class Tags {

		private String Category = "Category";
		private String ClassName = "ExportItemDef";
		private String ExportItemList = "ExportItemList";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getCategory(){
			return Category;
		}

		public String getClassName(){
			return ClassName;
		}

		public String getExportItemList(){
			return ExportItemList;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCategory(String newVal){
			Category = newVal;
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
		public void setExportItemList(String newVal){
			ExportItemList = newVal;
		}

	}

	private ArrayList m_alExportItemDefs = new ArrayList();
	private static IFusionApi m_api;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public ExportItemDef(){

	}

	/**
	 * 
	 * @param eiDef
	 */
	public void AddExportItem(ExportItemDef eiDef){

	}

	public static String ClassName(){
		return "";
	}

	public void ClearDataItems(){

	}

	public void ClearItems(){

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

	public ArrayList ExportItems(){
		return null;
	}

	public IFusionApi getapi(){
		return m_api;
	}

	protected ArrayList GetExportDataItems(){
		return null;
	}

	protected ArrayList GetExportDefintionItems(){
		return null;
	}

	public String InstanceClassName(){
		return "";
	}

	/**
	 * 
	 * @param eiDef
	 */
	public void RemoveExportItem(ExportItemDef eiDef){

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

	/**
	 * 
	 * @param newVal
	 */
	public void setapi(IFusionApi newVal){
		m_api = newVal;
	}

}