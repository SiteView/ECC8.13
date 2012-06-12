package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:59
 */
public class LoadSystemVersionEventArgs extends FusionAggregate {

	public LoadSystemVersionEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public LoadSystemVersionEventArgs(Object fusionObject){

	}

	public int SystemVersion(){
		return 0;
	}

	private Fusion.BusinessLogic.LoadSystemVersionEventArgs WhoAmI(){
		return null;
	}

}