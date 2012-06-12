package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:47
 */
public class XmlContentAlignment {

	private string BottomCenter = "BOTTOMCENTER";
	private string BottomLeft = "BOTTOMLEFT";
	private string BottomRight = "BOTTOMRIGHT";
	private string MiddleCenter = "MIDDLECENTER";
	private string MiddleLeft = "MIDDLELEFT";
	private string MiddleRight = "MIDDLERIGHT";
	private string TopCenter = "TOPCENTER";
	private string TopLeft = "TOPLEFT";
	private string TopRight = "TOPRIGHT";

	public XmlContentAlignment(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param alignment
	 */
	public static string ContentAlignmentToXmlContentAlignment(ContentAlignment alignment){
		return "";
	}

	public string getBottomCenter(){
		return BottomCenter;
	}

	public string getBottomLeft(){
		return BottomLeft;
	}

	public string getBottomRight(){
		return BottomRight;
	}

	public string getMiddleCenter(){
		return MiddleCenter;
	}

	public string getMiddleLeft(){
		return MiddleLeft;
	}

	public string getMiddleRight(){
		return MiddleRight;
	}

	public string getTopCenter(){
		return TopCenter;
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
	public void setBottomCenter(string newVal){
		BottomCenter = newVal;
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
	public void setMiddleCenter(string newVal){
		MiddleCenter = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMiddleLeft(string newVal){
		MiddleLeft = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMiddleRight(string newVal){
		MiddleRight = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTopCenter(string newVal){
		TopCenter = newVal;
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
	 * @param strXmlContentAlignment
	 */
	public static ContentAlignment XmlContentAlignmentToContentAlignment(string strXmlContentAlignment){
		return null;
	}

}