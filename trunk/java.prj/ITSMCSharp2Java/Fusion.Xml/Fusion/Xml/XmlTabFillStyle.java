package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:38:00
 */
public class XmlTabFillStyle {

	private string LeftMergedWithCenter = "LeftMergedWithCenter";
	private string LeftRightOnly = "LeftRightOnly";
	private string None = "None";
	private string RightMergedWithCenter = "RightMergedWithCenter";

	public XmlTabFillStyle(){

	}

	public void finalize() throws Throwable {

	}

	public string getLeftMergedWithCenter(){
		return LeftMergedWithCenter;
	}

	public string getLeftRightOnly(){
		return LeftRightOnly;
	}

	public string getNone(){
		return None;
	}

	public string getRightMergedWithCenter(){
		return RightMergedWithCenter;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLeftMergedWithCenter(string newVal){
		LeftMergedWithCenter = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLeftRightOnly(string newVal){
		LeftRightOnly = newVal;
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
	public void setRightMergedWithCenter(string newVal){
		RightMergedWithCenter = newVal;
	}

	/**
	 * 
	 * @param source
	 */
	public static string TabFillStyleToXmlTabFillStyle(TabFillStyle source){
		return "";
	}

	/**
	 * 
	 * @param strXmlTabFillStyle
	 */
	public static TabFillStyle XmlTabFillStyleToTabFillStyle(string strXmlTabFillStyle){
		return null;
	}

}