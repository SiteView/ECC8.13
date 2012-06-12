package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:38:01
 */
public class XmlTabOrientation {

	private string BottomLeft = "BottomLeft";
	private string BottomRight = "BottomRight";
	private string LeftBottom = "LeftBottom";
	private string LeftTop = "LeftTop";
	private string RightBottom = "RightBottom";
	private string RightTop = "RightTop";
	private string TopLeft = "TopLeft";
	private string TopRight = "TopRight";

	public XmlTabOrientation(){

	}

	public void finalize() throws Throwable {

	}

	public string getBottomLeft(){
		return BottomLeft;
	}

	public string getBottomRight(){
		return BottomRight;
	}

	public string getLeftBottom(){
		return LeftBottom;
	}

	public string getLeftTop(){
		return LeftTop;
	}

	public string getRightBottom(){
		return RightBottom;
	}

	public string getRightTop(){
		return RightTop;
	}

	public string getTopLeft(){
		return TopLeft;
	}

	public string getTopRight(){
		return TopRight;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBottomLeft(string newVal){
		BottomLeft = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBottomRight(string newVal){
		BottomRight = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLeftBottom(string newVal){
		LeftBottom = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLeftTop(string newVal){
		LeftTop = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRightBottom(string newVal){
		RightBottom = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRightTop(string newVal){
		RightTop = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTopLeft(string newVal){
		TopLeft = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTopRight(string newVal){
		TopRight = newVal;
	}

	/**
	 * 
	 * @param source
	 */
	public static string TabOrientationToXmlTabOrientation(TabOrientation source){
		return "";
	}

	/**
	 * 
	 * @param strXmlTabOrientation
	 */
	public static TabOrientation XmlTabOrientationToTabOrientation(string strXmlTabOrientation){
		return null;
	}

}