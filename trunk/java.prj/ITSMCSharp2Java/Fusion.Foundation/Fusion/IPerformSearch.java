package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:53
 */
public interface IPerformSearch {

	/**
	 * 
	 * @param query
	 * @param bSkipList
	 * @param nResultCount
	 * @param bDontPrompt
	 * @param strPromptTitle
	 * @param strSettingsID
	 */
	public void DoSearch(FusionQuery query, boolean bSkipList, int nResultCount, boolean bDontPrompt, String strPromptTitle, String strSettingsID);

}