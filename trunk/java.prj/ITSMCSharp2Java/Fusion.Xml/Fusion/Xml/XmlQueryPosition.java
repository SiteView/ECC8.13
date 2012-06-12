package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:54
 */
public class XmlQueryPosition {

	private string First = "First";
	private string Last = "Last";
	private string Next = "Next";
	private string Previous = "Previous";

	public XmlQueryPosition(){

	}

	public void finalize() throws Throwable {

	}

	public string getFirst(){
		return First;
	}

	public string getLast(){
		return Last;
	}

	public string getNext(){
		return Next;
	}

	public string getPrevious(){
		return Previous;
	}

	/**
	 * 
	 * @param pos
	 */
	public static string QueryPositionToXml(QueryPosition pos){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFirst(string newVal){
		First = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLast(string newVal){
		Last = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNext(string newVal){
		Next = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPrevious(string newVal){
		Previous = newVal;
	}

	/**
	 * 
	 * @param strXml
	 */
	public static QueryPosition XmlToQueryPosition(string strXml){
		return null;
	}

}