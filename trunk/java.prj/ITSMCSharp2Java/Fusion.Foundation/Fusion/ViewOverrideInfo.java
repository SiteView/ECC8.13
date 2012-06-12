package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:53
 */
public class ViewOverrideInfo implements IViewOverrideInfo {

	private Fusion.Xml.ViewBehavior m_Behavior;
	private String m_strDefId;
	private String m_strDefName;
	private String m_strDefType;
	private String m_strLinkDefId;
	private String m_strLinkDefName;
	private String m_strPerspective;



	public void finalize() throws Throwable {

	}

	protected ViewOverrideInfo(){

	}

	/**
	 * 
	 * @param strPerspective
	 * @param strDefName
	 * @param strDefId
	 * @param strDefType
	 * @param eViewBehavior
	 * @param strLinkDefPerspective
	 * @param strLinkDefName
	 * @param strLinkDefId
	 */
	public ViewOverrideInfo(String strPerspective, String strDefName, String strDefId, String strDefType, Fusion.Xml.ViewBehavior eViewBehavior, String strLinkDefPerspective, String strLinkDefName, String strLinkDefId){

	}

	public IViewOverrideInfo Clone(){
		return null;
	}

	/**
	 * 
	 * @param voi
	 */
	protected void CopyContents(ViewOverrideInfo voi){

	}

	public String DefId(){
		return "";
	}

	public String DefName(){
		return "";
	}

	public String DefType(){
		return "";
	}

	public String LinkDefId(){
		return "";
	}

	public String LinkDefName(){
		return "";
	}

	public String Perspective(){
		return "";
	}

	public Fusion.Xml.ViewBehavior ViewBehavior(){
		return null;
	}

}