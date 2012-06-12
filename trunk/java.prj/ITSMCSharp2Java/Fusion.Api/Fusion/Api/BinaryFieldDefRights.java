package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:31
 */
public class BinaryFieldDefRights extends FieldDefRights {

	public BinaryFieldDefRights(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public BinaryFieldDefRights(Object fusionObject){

	}

	public boolean AllowChangeLength(){
		return false;
	}

	public static String ClassName(){
		return "";
	}

	public int Maximum(){
		return 0;
	}

	public int Minimum(){
		return 0;
	}

	private Fusion.BusinessLogic.BinaryFieldDefRights WhoAmI(){
		return null;
	}

}