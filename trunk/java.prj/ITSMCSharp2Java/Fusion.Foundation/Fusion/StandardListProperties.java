package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:21
 */
public class StandardListProperties {

	private String Perspective = "Perspective";

	public StandardListProperties(){

	}

	public void finalize() throws Throwable {

	}

	public String getPerspective(){
		return Perspective;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPerspective(String newVal){
		Perspective = newVal;
	}

}