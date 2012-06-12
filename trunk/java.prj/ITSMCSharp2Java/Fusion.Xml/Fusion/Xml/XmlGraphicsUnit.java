package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:53
 */
public class XmlGraphicsUnit {

	private string Display = "DISPLAY";
	private string Document = "DOCUMENT";
	private string Inch = "INCH";
	private string Millimeter = "MILLIMETER";
	private string Pixel = "PIXEL";
	private string Point = "POINT";
	private string World = "WORLD";

	public XmlGraphicsUnit(){

	}

	public void finalize() throws Throwable {

	}

	public string getDisplay(){
		return Display;
	}

	public string getDocument(){
		return Document;
	}

	public string getInch(){
		return Inch;
	}

	public string getMillimeter(){
		return Millimeter;
	}

	public string getPixel(){
		return Pixel;
	}

	public string getPoint(){
		return Point;
	}

	public string getWorld(){
		return World;
	}

	/**
	 * 
	 * @param gu
	 */
	public static string GraphicsUnitToXmlGraphicsUnit(GraphicsUnit gu){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDisplay(string newVal){
		Display = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDocument(string newVal){
		Document = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setInch(string newVal){
		Inch = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMillimeter(string newVal){
		Millimeter = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPixel(string newVal){
		Pixel = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPoint(string newVal){
		Point = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setWorld(string newVal){
		World = newVal;
	}

	/**
	 * 
	 * @param strXmlGraphicsUnit
	 */
	public static GraphicsUnit XmlGraphicsUnitToGraphicsUnit(string strXmlGraphicsUnit){
		return null;
	}

}