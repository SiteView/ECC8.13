package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:02
 */
public abstract class MetaObject extends FusionAggregate {

	public MetaObject(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public MetaObject(Object fusionObject){

	}

	public String Alias(){
		return "";
	}

	public String Description(){
		return "";
	}

	public String Id(){
		return "";
	}

	public String Name(){
		return "";
	}

	private Fusion.BusinessLogic.MetaObject WhoAmI(){
		return null;
	}

}