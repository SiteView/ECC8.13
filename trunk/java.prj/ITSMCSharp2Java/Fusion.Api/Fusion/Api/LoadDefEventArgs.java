package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:59
 */
public class LoadDefEventArgs extends FusionAggregate {

	public LoadDefEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public LoadDefEventArgs(Object fusionObject){

	}

	public String DefinitionName(){
		return "";
	}

	public int DefinitionNumber(){
		return 0;
	}

	public boolean SystemDefinition(){
		return false;
	}

	public int TotalNumberOfDefinitions(){
		return 0;
	}

	private Fusion.BusinessLogic.LoadDefEventArgs WhoAmI(){
		return null;
	}

}