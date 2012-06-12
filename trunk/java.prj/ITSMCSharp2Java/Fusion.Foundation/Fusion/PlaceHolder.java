package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:32
 */
public class PlaceHolder extends INameId {

	private Fusion.Xml.Scope m_Scope;
	private String m_strAlias;
	private String m_strAssociatedImage;
	private String m_strCategory;
	private String m_strDefClassName;
	private String m_strDesc;
	private String m_strFlags;
	private String m_strFolder;
	private String m_strId;
	private String m_strLinkedTo;
	private String m_strName;
	private String m_strPerspective;
	private String m_strScopeOwner;

	public PlaceHolder(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param def
	 */
	public PlaceHolder(IDefinition def){

	}

	/**
	 * 
	 * @param xeItem
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 */
	public PlaceHolder(XmlElement xeItem, Fusion.Xml.Scope scopeType, String strScopeOwner, String strDefClassName){

	}

	/**
	 * 
	 * @param scopeValue
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strId
	 * @param strName
	 * @param strDefClassName
	 * @param strCategory
	 * @param strAlias
	 * @param strDesc
	 * @param strFolder
	 * @param strPerspective
	 * @param strFlags
	 * @param strAssociatedImage
	 */
	public PlaceHolder(Fusion.Xml.Scope scopeValue, String strScopeOwner, String strLinkedTo, String strId, String strName, String strDefClassName, String strCategory, String strAlias, String strDesc, String strFolder, String strPerspective, String strFlags, String strAssociatedImage){

	}

	public String Alias(){
		return "";
	}

	public String AssociatedImage(){
		return "";
	}

	public String Category(){
		return "";
	}

	public String DefClassName(){
		return "";
	}

	public String Description(){
		return "";
	}

	public String Folder(){
		return "";
	}

	/**
	 * 
	 * @param strFlag
	 */
	public boolean HasFlag(String strFlag){
		return null;
	}

	public String Id(){
		return "";
	}

	public String IdKey(){
		return "";
	}

	public String LinkedTo(){
		return "";
	}

	public String Name(){
		return "";
	}

	public String NameKey(){
		return "";
	}

	public String Perspective(){
		return "";
	}

	public Fusion.Xml.Scope Scope(){
		return null;
	}

	public String ScopeOwner(){
		return "";
	}

	/**
	 * 
	 * @param strFlags
	 */
	protected void SetFlags(String strFlags){

	}

	public String ToString(){
		return "";
	}

}