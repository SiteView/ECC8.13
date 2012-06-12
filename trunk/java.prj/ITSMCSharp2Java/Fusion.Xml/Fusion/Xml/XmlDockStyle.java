package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:51
 */
public class XmlDockStyle {

	private string Bottom = "BOTTOM";
	private string Fill = "FILL";
	private string Left = "LEFT";
	private string None = "NONE";
	private string Right = "RIGHT";
	private string Top = "TOP";

	public XmlDockStyle(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param style
	 */
	public static string DockStyleToXmlDockStyle(DockStyle style){
		return "";
	}

	public string getBottom(){
		return Bottom;
	}

	public string getFill(){
		return Fill;
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
	public void setFill(string newVal){
		Fill = newVal;
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
	 * @param strXmlDockStyle
	 */
	public static DockStyle XmlDockStyleToDockStyle(string strXmlDockStyle){
		return null;
	}

}