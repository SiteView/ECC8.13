package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:19
 */
public class ActionDirectoryEntry {

	private boolean m_bHidden;
	private String m_strActionItem;
	private String m_strCategory;
	private String m_strDefType;
	private String m_strDescription;
	private String m_strEditType;
	private String m_strExecType;
	private String m_strIcon;

	public ActionDirectoryEntry(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strActionItem
	 * @param strCategory
	 * @param strDescription
	 * @param strIcon
	 * @param strDefinitionType
	 * @param strEditorType
	 * @param strExecutorType
	 * @param bHidden
	 */
	public ActionDirectoryEntry(String strActionItem, String strCategory, String strDescription, String strIcon, String strDefinitionType, String strEditorType, String strExecutorType, boolean bHidden){

	}

	public String ActionItem(){
		return "";
	}

	public String Category(){
		return "";
	}

	public String DefinitionTypeName(){
		return "";
	}

	public String Description(){
		return "";
	}

	public String EditorTypeName(){
		return "";
	}

	public String ExecutorTypeName(){
		return "";
	}

	public boolean Hidden(){
		return false;
	}

	public String IconName(){
		return "";
	}

}

