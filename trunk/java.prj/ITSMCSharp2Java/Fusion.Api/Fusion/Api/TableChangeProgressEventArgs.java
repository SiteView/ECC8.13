package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:46
 */
public class TableChangeProgressEventArgs extends FusionAggregate {

	public TableChangeProgressEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public TableChangeProgressEventArgs(Object fusionObject){

	}

	public String ProgressMessage(){
		return "";
	}

	public String TableName(){
		return "";
	}

	private Fusion.BusinessLogic.TableChangeProgressEventArgs WhoAmI(){
		return null;
	}

}