package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:33
 */
public class PresentationConstants {

	private String BriefExtension = ".Brief";

	public PresentationConstants(){

	}

	public void finalize() throws Throwable {

	}

	public String getBriefExtension(){
		return BriefExtension;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBriefExtension(String newVal){
		BriefExtension = newVal;
	}

}