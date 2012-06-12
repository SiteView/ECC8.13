package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:52
 */
public class XmlFormattingDirection {

	private string Left = "Left";
	private string None = "None";
	private string Right = "Right";

	public XmlFormattingDirection(){

	}

	public void finalize() throws Throwable {

	}

	public string getLeft(){
		return Left;
	}

	public string getNone(){
		return None;
	}

	public string getRight(){
		return Right;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLeft(string newVal){
		Left = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNone(string newVal){
		None = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRight(string newVal){
		Right = newVal;
	}

	/**
	 * 
	 * @param strDirection
	 */
	public static FormattingDirection ToCategory(string strDirection){
		return null;
	}

	/**
	 * 
	 * @param direction
	 */
	public static string ToString(FormattingDirection direction){
		return "";
	}

}