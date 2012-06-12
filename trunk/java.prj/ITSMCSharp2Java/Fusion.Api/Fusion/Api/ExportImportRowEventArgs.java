package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:18
 */
public class ExportImportRowEventArgs extends FusionAggregate {

	public ExportImportRowEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ExportImportRowEventArgs(Object fusionObject){

	}

	public int CurrentRow(){
		return 0;
	}

	public int TotalRows(){
		return 0;
	}

	private Fusion.BusinessLogic.ExportImportRowEventArgs WhoAmI(){
		return null;
	}

}