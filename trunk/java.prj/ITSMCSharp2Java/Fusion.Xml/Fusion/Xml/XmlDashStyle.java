package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:50
 */
public class XmlDashStyle {

	private string Custom = "CUSTOM";
	private string Dash = "DASH";
	private string DashDot = "DASHDOT";
	private string DashDotDot = "DASHDOTDOT";
	private string Dot = "DOT";
	private string Solid = "SOLID";

	public XmlDashStyle(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param style
	 */
	public static string DashStyleToXmlDashStyle(DashStyle style){
		return "";
	}

	public string getCustom(){
		return Custom;
	}

	public string getDash(){
		return Dash;
	}

	public string getDashDot(){
		return DashDot;
	}

	public string getDashDotDot(){
		return DashDotDot;
	}

	public string getDot(){
		return Dot;
	}

	public string getSolid(){
		return Solid;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCustom(string newVal){
		Custom = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDash(string newVal){
		Dash = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDashDot(string newVal){
		DashDot = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDashDotDot(string newVal){
		DashDotDot = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDot(string newVal){
		Dot = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSolid(string newVal){
		Solid = newVal;
	}

	/**
	 * 
	 * @param strXmlDashStyle
	 */
	public static DashStyle XmlDashStyleToDashStyle(string strXmlDashStyle){
		return null;
	}

}