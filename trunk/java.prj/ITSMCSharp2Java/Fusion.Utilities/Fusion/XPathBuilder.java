package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:45
 */
public class XPathBuilder {

	private Boolean m_bResolveFromRoot = false;
	private String m_strPredicateExpr;
	private String m_strXPath;



	public void finalize() throws Throwable {

	}

	public XPathBuilder(){

	}

	/**
	 * 
	 * @param strNodeName
	 */
	public void AddAncestor(String strNodeName){

	}

	/**
	 * 
	 * @param strNodeName
	 */
	public void AddParent(String strNodeName){

	}

	/**
	 * 
	 * @param strAxis
	 * @param strNodeName
	 * @param strOperator
	 * @param strValue
	 */
	public void AddPredicate(String strAxis, String strNodeName, String strOperator, String strValue){

	}

	/**
	 * 
	 * @param strAxis
	 * @param strNodeName
	 * @param strOperator
	 * @param strValue
	 * @param strConnective
	 */
	public void AddPredicate(String strAxis, String strNodeName, String strOperator, String strValue, String strConnective){

	}

	/**
	 * 
	 * @param strNodeName
	 */
	public void AddSubject(String strNodeName){

	}

	/**
	 * 
	 * @param strAxis
	 * @param strNodeName
	 */
	public void AddSubject(String strAxis, String strNodeName){

	}

	public void Clear(){

	}

	public void ClearPredicate(){

	}

	public Boolean ResolveFromDocumentRoot(){
		return null;
	}

	public String XPath(){
		return "";
	}

}
