package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:38:29
 */
public class XmlViewBehavior {

	private string Base = "Base";
	private string Block = "Block";
	private string CustomVersion = "CustomVersion";
	private string LinkToAnotherDef = "LinkToAnotherDef";

	public XmlViewBehavior(){

	}

	public void finalize() throws Throwable {

	}

	public string getBase(){
		return Base;
	}

	public string getBlock(){
		return Block;
	}

	public string getCustomVersion(){
		return CustomVersion;
	}

	public string getLinkToAnotherDef(){
		return LinkToAnotherDef;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBase(string newVal){
		Base = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBlock(string newVal){
		Block = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCustomVersion(string newVal){
		CustomVersion = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLinkToAnotherDef(string newVal){
		LinkToAnotherDef = newVal;
	}

	/**
	 * 
	 * @param strViewBehavior
	 */
	public static ViewBehavior StringToViewBehavior(string strViewBehavior){
		return null;
	}

	/**
	 * 
	 * @param eViewBehavior
	 */
	public static string ViewBehaviorToString(ViewBehavior eViewBehavior){
		return "";
	}

}