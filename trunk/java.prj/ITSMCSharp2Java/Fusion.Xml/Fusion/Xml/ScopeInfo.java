package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:39
 */
public class ScopeInfo {

	private bool m_bFound = false;
	private Fusion.Xml.Scope m_scopeType = Fusion.Xml.Scope.Global;
	private string m_strScopeOwner = "GLOBAL";

	public ScopeInfo(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 */
	public ScopeInfo(Fusion.Xml.Scope scopeType, string strScopeOwner){

	}

	public bool Found(){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 */
	public bool IsScope(Fusion.Xml.Scope scopeType, string strScopeOwner){
		return null;
	}

	public Fusion.Xml.Scope Scope(){
		return null;
	}

	public string ScopeAsString(){
		return "";
	}

	public string ScopeOwner(){
		return "";
	}

}