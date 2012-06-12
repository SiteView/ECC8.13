package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:53
 */
public interface IPromptSettings {

	/**
	 * 
	 * @param strQueryPromptId
	 */
	public void ClearQueryPromptSettings(String strQueryPromptId);

	/**
	 * 
	 * @param strQueryPromptId
	 * @param strQueryPromptName
	 */
	public boolean Contains(String strQueryPromptId, String strQueryPromptName);

	/**
	 * 
	 * @param strQueryPromptId
	 * @param bDeleteChilds
	 */
	public void DeleteQueryPromptSetting(String strQueryPromptId, boolean bDeleteChilds);

	/**
	 * 
	 * @param strQueryPromptId
	 */
	public void FlushQueryPromptSetting(String strQueryPromptId);

	/**
	 * 
	 * @param strQueryPromptId
	 */
	public List GetQueryPromptSettings(String strQueryPromptId);

	/**
	 * 
	 * @param strQueryPromptId
	 * @param QueryPrompts
	 */
	public void SetQueryPromptSettings(String strQueryPromptId, List QueryPrompts);

}