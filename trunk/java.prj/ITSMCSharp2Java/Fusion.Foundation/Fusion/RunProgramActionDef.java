package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:59
 */
public class RunProgramActionDef extends ActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:59
	 */
	private class Tags {

		private String Arguments = "Arguments";
		private String FilePath = "FilePath";
		private String OutputFile = "OutputFile";
		private String PauseAfterLaunch = "PauseAfterLaunch";
		private String PauseSeconds = "PauseSeconds";
		private String RunProgramActionDef = "RunProgramActionDef";
		private String RunProgramDetails = "RunProgramDetails";
		private String ShowOutputMsgBox = "ShowOutputMsgBox";
		private String WaitForExit = "WaitForExit";
		private String WriteOutputFile = "WriteOutputFile";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getArguments(){
			return Arguments;
		}

		public String getFilePath(){
			return FilePath;
		}

		public String getOutputFile(){
			return OutputFile;
		}

		public String getPauseAfterLaunch(){
			return PauseAfterLaunch;
		}

		public String getPauseSeconds(){
			return PauseSeconds;
		}

		public String getRunProgramActionDef(){
			return RunProgramActionDef;
		}

		public String getRunProgramDetails(){
			return RunProgramDetails;
		}

		public String getShowOutputMsgBox(){
			return ShowOutputMsgBox;
		}

		public String getWaitForExit(){
			return WaitForExit;
		}

		public String getWriteOutputFile(){
			return WriteOutputFile;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setArguments(String newVal){
			Arguments = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFilePath(String newVal){
			FilePath = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setOutputFile(String newVal){
			OutputFile = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPauseAfterLaunch(String newVal){
			PauseAfterLaunch = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPauseSeconds(String newVal){
			PauseSeconds = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRunProgramActionDef(String newVal){
			RunProgramActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRunProgramDetails(String newVal){
			RunProgramDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setShowOutputMsgBox(String newVal){
			ShowOutputMsgBox = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setWaitForExit(String newVal){
			WaitForExit = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setWriteOutputFile(String newVal){
			WriteOutputFile = newVal;
		}

	}

	private boolean m_bPauseAfterLaunch = false;
	private boolean m_bShowOutputMsgBox = false;
	private boolean m_bWaitForExit = false;
	private boolean m_bWriteOutputFile = false;
	private int m_nPauseSeconds = 0;
	private String m_strArgs = "";
	private String m_strFilePath = "";
	private String m_strOutputFile = "";

	public RunProgramActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
		return "";
	}

	public String Arguments(){
		return "";
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
	 * @param correction
	 * @param bJustCollect
	 * @param strAssociatedBusOb
	 */
	public boolean CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect, String strAssociatedBusOb){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public String FilePath(){
		return "";
	}

	/**
	 * 
	 * @param list
	 */
	public void GatherPromptDefs(IList list){

	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public boolean HasTagsContainingTagCategory(String strTagCategoryName){
		return null;
	}

	public String OutputFile(){
		return "";
	}

	public boolean PauseAfterLaunch(){
		return null;
	}

	public int PauseSeconds(){
		return 0;
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

	public boolean ShowOutputInMsgBox(){
		return null;
	}

	public boolean WaitForExit(){
		return null;
	}

	public boolean WriteOutputToFile(){
		return null;
	}

}