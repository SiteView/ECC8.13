package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:16
 */
public class DisplayInfo extends IComparable {

	private String m_strLocalizedName;
	private String m_strName;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public DisplayInfo(){

	}

	/**
	 * 
	 * @param strName
	 * @param strLocalizedName
	 */
	public DisplayInfo(String strName, String strLocalizedName){

	}

	/**
	 * 
	 * @param obj
	 */
	public int CompareTo(Object obj){
		return 0;
	}

	public String LocalizedName(){
		return "";
	}

	public String Name(){
		return "";
	}

	public String ToString(){
		return "";
	}

}