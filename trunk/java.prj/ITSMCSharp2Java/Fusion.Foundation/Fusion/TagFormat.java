package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:34
 */
public class TagFormat {

	private Hashtable m_htArgNameToValue;
	private int m_nApplyOrder;
	private Object m_oCargo;
	private String m_strFormat;
	private String m_strFormatItem;



	public void finalize() throws Throwable {

	}

	public TagFormat(){

	}

	/**
	 * 
	 * @param strFormatItem
	 */
	public TagFormat(String strFormatItem){

	}

	/**
	 * 
	 * @param strFormatItem
	 * @param strFormat
	 */
	public TagFormat(String strFormatItem, String strFormat){

	}

	public int ApplyOrder(){
		return 0;
	}

	public Map ArgumentMap(){
		return null;
	}

	public Object Cargo(){
		return null;
	}

	public String Format(){
		return "";
	}

	public String FormatItem(){
		return "";
	}

}