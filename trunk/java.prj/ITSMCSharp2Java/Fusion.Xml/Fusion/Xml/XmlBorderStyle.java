package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:44
 */
public class XmlBorderStyle {

	private string Fixed3D = "FIXED3D";
	private string FixedSingle = "FIXEDSINGLE";
	private string None = "NONE";

	public XmlBorderStyle(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param style
	 */
	public static string BorderStyleToXmlBorderStyle(BorderStyle style){
		return "";
	}

	public string getFixed3D(){
		return Fixed3D;
	}

	public string getFixedSingle(){
		return FixedSingle;
	}

	public string getNone(){
		return None;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFixed3D(string newVal){
		Fixed3D = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFixedSingle(string newVal){
		FixedSingle = newVal;
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
	 * @param strXmlBorderStyle
	 */
	public static BorderStyle XmlBorderStyleToBorderStyle(string strXmlBorderStyle){
		return null;
	}

}