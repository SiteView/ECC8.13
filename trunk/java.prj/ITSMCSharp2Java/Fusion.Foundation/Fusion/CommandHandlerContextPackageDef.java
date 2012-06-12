package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:52
 */
public class CommandHandlerContextPackageDef extends ContextPackageDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:52
	 */
	private class Tags {

		private String ClassName = "CommandHandlerContextPackageDef";
		private String CommandHandlerContextPackageDef = "CommandHandlerContextPackageDef";
		private String ContextIdentifier = "ContextIdentifier";
		private String ModuleName = "ModuleName";
		private String QualifiedClassName = "QualifiedClassName";
		private String Title = "Title";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClassName(){
			return ClassName;
		}

		public String getCommandHandlerContextPackageDef(){
			return CommandHandlerContextPackageDef;
		}

		public String getContextIdentifier(){
			return ContextIdentifier;
		}

		public String getModuleName(){
			return ModuleName;
		}

		public String getQualifiedClassName(){
			return QualifiedClassName;
		}

		public String getTitle(){
			return Title;
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
		public void setCommandHandlerContextPackageDef(String newVal){
			CommandHandlerContextPackageDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setContextIdentifier(String newVal){
			ContextIdentifier = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setModuleName(String newVal){
			ModuleName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setQualifiedClassName(String newVal){
			QualifiedClassName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTitle(String newVal){
			Title = newVal;
		}

	}

	private String m_strModuleName = "";
	private String m_strQualifiedClassName = "";

	public CommandHandlerContextPackageDef(){

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

	public String ModuleName(){
		return "";
	}

	public String QualifiedClassName(){
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