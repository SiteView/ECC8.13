package Fusion.Api.FusionUpgrade.Defs;

import java.util.ArrayList;
import java.util.Hashtable;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:44:11
 */
public class ExportDef extends ExportItemDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:44:11
	 */
	private class Tags {

		private String ClassName = "ExportDef";
		private String Description = "Description";
		private String ExportPackageItems = "ExportPackageItems";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClassName(){
			return ClassName;
		}

		public String getDescription(){
			return Description;
		}

		public String getExportPackageItems(){
			return ExportPackageItems;
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
		public void setDescription(String newVal){
			Description = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setExportPackageItems(String newVal){
			ExportPackageItems = newVal;
		}

	}

	private ArrayList m_alPackages = new ArrayList();
	private String m_strDescription = "";

	public ExportDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strName
	 * @param strDescription
	 */
	public ExportDef(String strName, String strDescription){

	}

	/**
	 * 
	 * @param eiDef
	 */
	public void AddDefinitionItem(ExportDefinitionItemDef eiDef){

	}

	/**
	 * 
	 * @param eiDef
	 */
	public void AddPackageExportItem(ExportPackageItemDef eiDef){

	}

	public static String ClassName(){
		return "";
	}

	public void ClearDefinitionItems(){

	}

	public void ClearPackageItems(){

	}

	public ArrayList DataItems(){
		return null;
	}

	public ArrayList DefinitionItems(){
		return null;
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
	 * @param strID
	 */
	public ExportItemDef FindAllExportItem(String strID){
		return null;
	}

	/**
	 * 
	 * @param ph
	 */
	public ExportItemDef FindExportItem(PlaceHolder ph){
		return null;
	}

	/**
	 * 
	 * @param strID
	 */
	public ExportItemDef FindExportItem(String strID){
		return null;
	}

	/**
	 * 
	 * @param strPerspective
	 * @param strID
	 * @param strCategory
	 * @param strScope
	 * @param strScopeOwner
	 */
	private ExportItemDef FindExportItem(String strPerspective, String strID, String strCategory, String strScope, String strScopeOwner){
		return null;
	}

	/**
	 * 
	 * @param strPackageName
	 */
	public ExportPackageItemDef GetPackage(String strPackageName){
		return null;
	}

	public Hashtable GetPackages(){
		return null;
	}

	/**
	 * 
	 * @param ph
	 */
	public boolean HolderExists(PlaceHolder ph){
		return false;
	}

	public String InstanceClassName(){
		return "";
	}

	public ArrayList PackageItems(){
		return null;
	}

	/**
	 * 
	 * @param eiDef
	 */
	public void RemoveDefinitionItem(ExportDefinitionItemDef eiDef){

	}

	/**
	 * 
	 * @param eiDef
	 */
	public void RemovePackageExportItem(ExportPackageItemDef eiDef){

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