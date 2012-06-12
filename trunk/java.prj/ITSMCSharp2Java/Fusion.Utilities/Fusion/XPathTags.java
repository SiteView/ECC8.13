package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:45
 */
public class XPathTags {

	private String XPathAncestor = "ancestor::";
	private String XPathAttribute = "@";
	private String XPathChild = "child::";
	private String XPathDescendant = "descendant::";

	public XPathTags(){

	}

	public void finalize() throws Throwable {

	}

	public String getXPathAncestor(){
		return XPathAncestor;
	}

	public String getXPathAttribute(){
		return XPathAttribute;
	}

	public String getXPathChild(){
		return XPathChild;
	}

	public String getXPathDescendant(){
		return XPathDescendant;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setXPathAncestor(String newVal){
		XPathAncestor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setXPathAttribute(String newVal){
		XPathAttribute = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setXPathChild(String newVal){
		XPathChild = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setXPathDescendant(String newVal){
		XPathDescendant = newVal;
	}

}
