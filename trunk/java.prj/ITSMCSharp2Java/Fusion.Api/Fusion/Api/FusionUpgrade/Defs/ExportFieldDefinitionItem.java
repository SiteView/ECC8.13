package Fusion.Api.FusionUpgrade.Defs;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:44:16
 */
public class ExportFieldDefinitionItem extends ExportDefinitionItemDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:44:16
	 */
	private class Tags {

		private String ClassName = "ExportFieldDefintionItem";
		private String FieldName = "FieldName";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClassName(){
			return ClassName;
		}

		public String getFieldName(){
			return FieldName;
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
		public void setFieldName(String newVal){
			FieldName = newVal;
		}

	}

	private String m_strQualifiedFieldName;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public ExportFieldDefinitionItem(){

	}

	/**
	 * 
	 * @param boDef
	 * @param defField
	 */
	public ExportFieldDefinitionItem(Fusion.Api.BusinessObjectDef boDef, Fusion.Api.FieldDef defField){

	}

	/**
	 * 
	 * @param ph
	 * @param strFieldName
	 */
	public ExportFieldDefinitionItem(PlaceHolder ph, String strFieldName){

	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public Fusion.BusinessLogic.FieldDef FieldDefintion(){
		return null;
	}

	public String InstanceClassName(){
		return "";
	}

	public String QualifiedFieldName(){
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