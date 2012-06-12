package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:46
 */
public class TableChangeEventArgs extends FusionAggregate {

	public TableChangeEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public TableChangeEventArgs(Object fusionObject){

	}

	public TableChangeEventType ChangeType(){
		return null;
	}

	public boolean SystemTable(){
		return null;
	}

	public String TableName(){
		return "";
	}

	public int TableNumber(){
		return 0;
	}

	public int TotalNumberOfTables(){
		return 0;
	}

	private Fusion.BusinessLogic.TableChangeEventArgs WhoAmI(){
		return null;
	}

}