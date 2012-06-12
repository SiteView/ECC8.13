package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:49
 */
public class CallWSActionDef extends ActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:49
	 */
	private class Tags {

		private String Assembly = "Assembly";
		private String CallWSActionDef = "CallWSActionDef";
		private String CallWSDetails = "CallWSDetails";
		private String HasReturnValue = "HasReturnValue";
		private String Method = "Method";
		private String ParamType = "ParamType";
		private String ParamTypeList = "ParamTypeList";
		private String ParamVal = "ParamVal";
		private String ParamValList = "ParamValList";
		private String Type = "Type";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAssembly(){
			return Assembly;
		}

		public String getCallWSActionDef(){
			return CallWSActionDef;
		}

		public String getCallWSDetails(){
			return CallWSDetails;
		}

		public String getHasReturnValue(){
			return HasReturnValue;
		}

		public String getMethod(){
			return Method;
		}

		public String getParamType(){
			return ParamType;
		}

		public String getParamTypeList(){
			return ParamTypeList;
		}

		public String getParamVal(){
			return ParamVal;
		}

		public String getParamValList(){
			return ParamValList;
		}

		public String getType(){
			return Type;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAssembly(String newVal){
			Assembly = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCallWSActionDef(String newVal){
			CallWSActionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCallWSDetails(String newVal){
			CallWSDetails = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setHasReturnValue(String newVal){
			HasReturnValue = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMethod(String newVal){
			Method = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParamType(String newVal){
			ParamType = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParamTypeList(String newVal){
			ParamTypeList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParamVal(String newVal){
			ParamVal = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setParamValList(String newVal){
			ParamValList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setType(String newVal){
			Type = newVal;
		}

	}

	private ArrayList m_aParamTypes = new ArrayList();
	private ArrayList m_aParamVals = new ArrayList();
	private boolean m_bHasReturnValue = false;
	private String m_strAssembly = "";
	private String m_strMethod = "";
	private String m_strType = "";

	public CallWSActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
		return "";
	}

	public String AssemblyPath(){
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

	/**
	 * 
	 * @param list
	 */
	public void GatherPromptDefs(IList list){

	}

	public Type[] GetMethodSignature(){
		return null;
	}

	public boolean HasReturnValue(){
		return null;
	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public boolean HasTagsContainingTagCategory(String strTagCategoryName){
		return null;
	}

	public String MethodName(){
		return "";
	}

	public IList ParamTypes(){
		return null;
	}

	public IList ParamVals(){
		return null;
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

	public String TypeName(){
		return "";
	}

}