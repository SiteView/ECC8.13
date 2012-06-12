package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:53
 */
public class XmlKBAccessRight {

	private char Add = 'A';
	private char Edit = 'E';
	private char Modify = 'M';
	private char Search = 'S';

	public XmlKBAccessRight(){

	}

	public void finalize() throws Throwable {

	}

	public char getAdd(){
		return Add;
	}

	public char getEdit(){
		return Edit;
	}

	public char getModify(){
		return Modify;
	}

	public char getSearch(){
		return Search;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAdd(char newVal){
		Add = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEdit(char newVal){
		Edit = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setModify(char newVal){
		Modify = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSearch(char newVal){
		Search = newVal;
	}

	/**
	 * 
	 * @param strXmlRights
	 */
	public static KBAccessRight ToRight(string strXmlRights){
		return null;
	}

	/**
	 * 
	 * @param rightFlags
	 */
	public static string ToStringRight(KBAccessRight rightFlags){
		return "";
	}

}