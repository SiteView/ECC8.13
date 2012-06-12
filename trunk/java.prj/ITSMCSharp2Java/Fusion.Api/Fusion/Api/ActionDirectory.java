package Fusion.Api;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:18
 */
public class ActionDirectory {

	private static ActionDirectory m_Dir;
	private List m_htActionItemToDirectoryEntry = new LinkedList();



	public void finalize() throws Throwable {

	}

	private ActionDirectory(){

	}

	public Map ActionItemToDirectoryEntry(){
		return null;
	}

	private void AddCoreEntries(){

	}

	/**
	 * 
	 * @param strType
	 */
	private Object CreateInstance(String strType){
		return null;
	}

	public static ActionDirectory Directory(){
		return null;
	}

	/**
	 * 
	 * @param strItem
	 */
	public ActionDef GetActionDef(String strItem){
		return null;
	}

	/**
	 * 
	 * @param strItem
	 */
	public IActionExecutor GetActionExecutor(String strItem){
		return null;
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
	private void RegisterFactory(String strActionItem, String strCategory, String strDescription, String strIcon, String strDefinitionType, String strEditorType, String strExecutorType, boolean bHidden){

	}

	/**
	 * 
	 * @param strActionItem
	 */
	public ActionDirectoryEntry get(String strActionItem){
		return null;
	}

}
