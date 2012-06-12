package Fusion.Api.FusionUpgrade.Defs;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:44:13
 */
public class ExportDefinitionItemDef extends ExportItemDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:44:13
	 */
	private class Tags {

		private String ClassName = "ExportDefintionItem";
		private String Definition = "Definition";
		private String DefinitionType = "DefinitionType";
		private String ParetName = "ParetName";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClassName(){
			return ClassName;
		}

		public String getDefinition(){
			return Definition;
		}

		public String getDefinitionType(){
			return DefinitionType;
		}

		public String getParetName(){
			return ParetName;
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
		public void setDefinition(String newVal){
			Definition = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDefinitionType(String newVal){
			DefinitionType = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParetName(String newVal){
			ParetName = newVal;
		}

	}

	private IDefinition m_Def;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public ExportDefinitionItemDef(){

	}

	/**
	 * 
	 * @param def
	 */
	public ExportDefinitionItemDef(IDefinition def){

	}

	/**
	 * 
	 * @param ph
	 */
	public ExportDefinitionItemDef(PlaceHolder ph){

	}

	public static String ClassName(){
		return "";
	}

	public IDefinition Defintion(){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public String InstanceClassName(){
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