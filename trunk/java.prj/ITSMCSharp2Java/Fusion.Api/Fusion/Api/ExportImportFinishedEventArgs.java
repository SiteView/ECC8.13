package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:17
 */
public class ExportImportFinishedEventArgs extends FusionAggregate {

	public ExportImportFinishedEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ExportImportFinishedEventArgs(Object fusionObject){

	}

	public MessageInfoList ErrorList(){
		return null;
	}

	public boolean Successful(){
		return null;
	}

	private Fusion.BusinessLogic.ExportImportFinishedEventArgs WhoAmI(){
		return null;
	}

}