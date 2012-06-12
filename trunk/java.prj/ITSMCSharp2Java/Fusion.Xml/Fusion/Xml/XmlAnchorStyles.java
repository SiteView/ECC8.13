package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:43
 */
public class XmlAnchorStyles {

	private string Bottom = "BOTTOM";
	private string Left = "LEFT";
	private string None = "NONE";
	private string Right = "RIGHT";
	private string Top = "TOP";

	public XmlAnchorStyles(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param style
	 */
	public static string AnchorStylesToXmlAnchorStyles(AnchorStyles style){
		return "";
	}

	public string getBottom(){
		return Bottom;
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

	public string getTop(){
		return Top;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBottom(string newVal){
		Bottom = newVal;
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
	 * @param newVal
	 */
	public void setTop(string newVal){
		Top = newVal;
	}

	/**
	 * 
	 * @param strXmlAnchorStyles
	 */
	public static AnchorStyles XmlAnchorStylesToAnchorStyles(string strXmlAnchorStyles){
		return null;
	}

}