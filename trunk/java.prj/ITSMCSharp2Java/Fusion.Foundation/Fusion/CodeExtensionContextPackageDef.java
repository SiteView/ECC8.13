package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:51
 */
public class CodeExtensionContextPackageDef extends ContextPackageDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:51
	 */
	private class Tags {

		private String ClassName = "CodeExtensionContextPackageDef";
		private String CodeExtensionContextPackageDef = "CodeExtensionContextPackageDef";
		private String FactoryAssembly = "FactoryAssembly";
		private String FactoryClass = "FactoryClass";
		private String FactoryMethod = "FactoryMethod";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClassName(){
			return ClassName;
		}

		public String getCodeExtensionContextPackageDef(){
			return CodeExtensionContextPackageDef;
		}

		public String getFactoryAssembly(){
			return FactoryAssembly;
		}

		public String getFactoryClass(){
			return FactoryClass;
		}

		public String getFactoryMethod(){
			return FactoryMethod;
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
		public void setCodeExtensionContextPackageDef(String newVal){
			CodeExtensionContextPackageDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFactoryAssembly(String newVal){
			FactoryAssembly = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFactoryClass(String newVal){
			FactoryClass = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFactoryMethod(String newVal){
			FactoryMethod = newVal;
		}

	}

	private String m_strFactoryAssembly = "";
	private String m_strFactoryClass = "";
	private String m_strFactoryMethod = "";

	public CodeExtensionContextPackageDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public static String ClassName(){
		return "";
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
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public String FactoryAssembly(){
		return "";
	}

	public String FactoryClass(){
		return "";
	}

	public String FactoryMethod(){
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

}