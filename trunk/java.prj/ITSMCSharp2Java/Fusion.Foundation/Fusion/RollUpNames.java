package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:51
 */
public class RollUpNames {

	private String ColumnBusObName = "BusObName";
	private String RollUpOwnerField = "OwnerDisplayName";

	public RollUpNames(){

	}

	public void finalize() throws Throwable {

	}

	public String getColumnBusObName(){
		return ColumnBusObName;
	}

	public String getRollUpOwnerField(){
		return RollUpOwnerField;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setColumnBusObName(String newVal){
		ColumnBusObName = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRollUpOwnerField(String newVal){
		RollUpOwnerField = newVal;
	}

}