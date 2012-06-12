package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:20
 */
public class StampLabelActionDef extends ActionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:21
	 */
	private class Tags {

		private String ChildDepth = "ChildDepth";
		private String Expression = "Expression";
		private String StampChildren = "StampChildren";
		private String StampLabelActionDef = "StampLabelActionDef";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getChildDepth(){
			return ChildDepth;
		}

		public String getExpression(){
			return Expression;
		}

		public String getStampChildren(){
			return StampChildren;
		}

		public String getStampLabelActionDef(){
			return StampLabelActionDef;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setChildDepth(String newVal){
			ChildDepth = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setExpression(String newVal){
			Expression = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setStampChildren(String newVal){
			StampChildren = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setStampLabelActionDef(String newVal){
			StampLabelActionDef = newVal;
		}

	}

	private boolean m_bStampChildren = false;
	private int m_iChildDepth = 0;
	private String m_strExpression = "";

	public StampLabelActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
		return "";
	}

	public int ChildDepth(){
		return 0;
	}

	public static String ClassName(){
		return "";
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

	public String Expression(){
		return "";
	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public boolean HasTagsContainingTagCategory(String strTagCategoryName){
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

	public boolean StampChildren(){
		return null;
	}

}