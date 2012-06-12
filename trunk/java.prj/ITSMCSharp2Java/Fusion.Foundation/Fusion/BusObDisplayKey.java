package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:46
 */
public class BusObDisplayKey implements IBusObDisplayKey, IComparable {

	private String m_strAlias;
	private String m_strDisplayText;
	private String m_strId;
	private String m_strName;
	protected String SEPARATOR = "\t";
	protected int TOKENLEN = 4;
	protected int TOKENSTART = 0;



	public void finalize() throws Throwable {

	}

	public BusObDisplayKey(){

	}

	/**
	 * 
	 * @param strSerializedData
	 */
	public BusObDisplayKey(String strSerializedData){

	}

	/**
	 * 
	 * @param strId
	 * @param strName
	 * @param strAlias
	 * @param strDisplayText
	 */
	public BusObDisplayKey(String strId, String strName, String strAlias, String strDisplayText){

	}

	public String Alias(){
		return "";
	}

	/**
	 * 
	 * @param obj
	 */
	public int CompareTo(Object obj){
		return 0;
	}

	public IBusObDisplayKey Copy(){
		return null;
	}

	public String DisplayText(){
		return "";
	}

	public String Id(){
		return "";
	}

	/**
	 * 
	 * @param s
	 */
	protected boolean IsEmpty(String s){
		return false;
	}

	public String Name(){
		return "";
	}

	public String Serialize(){
		return "";
	}

	public String ToString(){
		return "";
	}

}