package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:00
 */
public class DateTimeAdjustFunction extends SystemFunctionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:01
	 */
	public class ParameterName extends ParameterName {

		private String BusObName = "BusObName";
		private String FieldName = "FieldName";
		private String Increment = "Increment";
		private String Units = "Units";

		public ParameterName(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		public String getBusObName(){
			return BusObName;
		}

		public String getFieldName(){
			return FieldName;
		}

		public String getIncrement(){
			return Increment;
		}

		public String getUnits(){
			return Units;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBusObName(String newVal){
			BusObName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFieldName(String newVal){
			FieldName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setIncrement(String newVal){
			Increment = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setUnits(String newVal){
			Units = newVal;
		}

	}

	private String DateTimeAdjustFunctionName = "DateTimeAdjustFunction";

	public DateTimeAdjustFunction(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String BusObName(){
		return "";
	}

	public String Category(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public String FieldName(){
		return "";
	}

	public String getDateTimeAdjustFunctionName(){
		return DateTimeAdjustFunctionName;
	}

	public decimal Increment(){
		return 0;
	}

	public static String PromptDisplayName(){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDateTimeAdjustFunctionName(String newVal){
		DateTimeAdjustFunctionName = newVal;
	}

	public TimeSpanUnit Units(){
		return null;
	}

}