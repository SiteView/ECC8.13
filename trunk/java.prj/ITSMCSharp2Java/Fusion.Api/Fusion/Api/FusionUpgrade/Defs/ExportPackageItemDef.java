package Fusion.Api.FusionUpgrade.Defs;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:44:22
 */
public class ExportPackageItemDef extends SerializableDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:44:22
	 */
	private class Tags {

		private String ClassName = "ExportPackageItemDef";
		private String ExportItemID = "ExportItemID";
		private String ExportItemIDList = "ExportItemIDList";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClassName(){
			return ClassName;
		}

		public String getExportItemID(){
			return ExportItemID;
		}

		public String getExportItemIDList(){
			return ExportItemIDList;
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
		public void setExportItemID(String newVal){
			ExportItemID = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setExportItemIDList(String newVal){
			ExportItemIDList = newVal;
		}

	}

	private List<String> m_scExportItemRecIDs = new ArrayList<String>();
	private String m_strDescription = "";

	public ExportPackageItemDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strName
	 * @param strDescription
	 */
	public ExportPackageItemDef(String strName, String strDescription){

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

	public void ClearItems(){

	}

	public String Description(){
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

	public List<String> ExportItemRecIDs(){
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

}