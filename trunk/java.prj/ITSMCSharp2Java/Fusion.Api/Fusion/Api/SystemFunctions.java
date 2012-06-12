package Fusion.Api;

import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:45:42
 */
public class SystemFunctions extends ISystemFunctions {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:45:42
	 */
	public class Purpose {

		private String SystemFunctionExtension = "SystemFunctionExtension";
		private String SystemPromptEditorUiExtension = "SystemPromptEditorUiExtension";
		private String SystemPromptExtension = "SystemPromptExtension";
		private String SystemPromptUiExtension = "SystemPromptUiExtension";

		public Purpose(){

		}

		public void finalize() throws Throwable {

		}

		public String getSystemFunctionExtension(){
			return SystemFunctionExtension;
		}

		public String getSystemPromptEditorUiExtension(){
			return SystemPromptEditorUiExtension;
		}

		public String getSystemPromptExtension(){
			return SystemPromptExtension;
		}

		public String getSystemPromptUiExtension(){
			return SystemPromptUiExtension;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSystemFunctionExtension(String newVal){
			SystemFunctionExtension = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSystemPromptEditorUiExtension(String newVal){
			SystemPromptEditorUiExtension = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSystemPromptExtension(String newVal){
			SystemPromptExtension = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSystemPromptUiExtension(String newVal){
			SystemPromptUiExtension = newVal;
		}

	}

	private IOrchestrator m_orch = null;

	public SystemFunctions(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param orch
	 */
	public SystemFunctions(IOrchestrator orch){

	}

	/**
	 * 
	 * @param strName
	 * @param fApi
	 */
	public static ISystemFunction Create(String strName, IFusionApi fApi){
		return null;
	}

	public Date CurrentDate(){
		return null;
	}

	public Date CurrentDateTime(){
		return null;
	}

	public String CurrentLoginId(){
		return "";
	}

	public String CurrentSecurityGroup(){
		return "";
	}

	public String CurrentSecurityGroupId(){
		return "";
	}

	public String CurrentUserBusinessUnit(){
		return "";
	}

	public String CurrentUserEmailAddress(){
		return "";
	}

	public String CurrentUserName(){
		return "";
	}

	public String CurrentUserRecId(){
		return "";
	}

	public String CurrentUserTeam(){
		return "";
	}

	public String CurrentUserType(){
		return "";
	}

	public String DefaultUserName(){
		return "";
	}

	public String DefaultUserRecId(){
		return "";
	}

	public String DefaultUserTeam(){
		return "";
	}

	public String DefaultUserType(){
		return "";
	}

	public Date EndOfLastMonth(){
		return null;
	}

	public Date EndOfLastQuarter(){
		return null;
	}

	public Date EndOfLastWeek(){
		return null;
	}

	public Date EndOfLastYear(){
		return null;
	}

	public Date EndOfNextMonth(){
		return null;
	}

	public Date EndOfNextQuarter(){
		return null;
	}

	public Date EndOfNextWeek(){
		return null;
	}

	public Date EndOfNextYear(){
		return null;
	}

	public Date EndOfThisMonth(){
		return null;
	}

	public Date EndOfThisQuarter(){
		return null;
	}

	public Date EndOfThisWeek(){
		return null;
	}

	public Date EndOfThisYear(){
		return null;
	}

	/**
	 * 
	 * @param strFunction
	 */
	public ISystemFunction GetSystemFunction(String strFunction){
		return null;
	}

	/**
	 * 
	 * @param strFunction
	 * @param scope
	 */
	public ISystemFunction GetSystemFunction(String strFunction, Scope scope){
		return null;
	}

	/**
	 * 
	 * @param strFunction
	 */
	public SystemFunctionValueType GetSystemFunctionDataType(String strFunction){
		return null;
	}

	/**
	 * 
	 * @param strFunction
	 * @param scope
	 */
	public SystemFunctionValueType GetSystemFunctionDataType(String strFunction, Scope scope){
		return null;
	}

	/**
	 * 
	 * @param strFunction
	 */
	private ISystemFunction GetSystemFunctionExtension(String strFunction){
		return null;
	}

	private ArrayList GetSystemFunctionExtensions(){
		return null;
	}

	private ArrayList GetSystemPromptTypes(){
		return null;
	}

	/**
	 * 
	 * @param function
	 */
	public FusionValue GetSystemValue(FunctionCategory function){
		return null;
	}

	/**
	 * 
	 * @param strFunction
	 */
	public FusionValue GetSystemValue(String strFunction){
		return null;
	}

	public List ListOfSystemFunctionExtensions(){
		return null;
	}

	public List ListOfSystemFunctions(){
		return null;
	}

	public List ListOfSystemPromptTypes(){
		return null;
	}

	public Date StartOfLastMonth(){
		return null;
	}

	public Date StartOfLastQuarter(){
		return null;
	}

	public Date StartOfLastWeek(){
		return null;
	}

	public Date StartOfLastYear(){
		return null;
	}

	public Date StartOfNextMonth(){
		return null;
	}

	public Date StartOfNextQuarter(){
		return null;
	}

	public Date StartOfNextWeek(){
		return null;
	}

	public Date StartOfNextYear(){
		return null;
	}

	public Date StartOfThisMonth(){
		return null;
	}

	public Date StartOfThisQuarter(){
		return null;
	}

	public Date StartOfThisWeek(){
		return null;
	}

	public Date StartOfThisYear(){
		return null;
	}

	public Date Tomorrow(){
		return null;
	}

	public Date Yesterday(){
		return null;
	}

}