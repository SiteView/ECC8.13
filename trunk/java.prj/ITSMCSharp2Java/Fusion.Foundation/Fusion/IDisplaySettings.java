package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:47
 */
public interface IDisplaySettings {

	/**
	 * 
	 * @param strGridId
	 */
	public void ClearGridSettings(String strGridId);

	/**
	 * 
	 * @param strDialogId
	 */
	public void ClearSuppressMessage(String strDialogId);

	/**
	 * 
	 * @param strTabId
	 */
	public void ClearTabSettings(String strTabId);

	/**
	 * 
	 * @param strDialogId
	 * @param bDeleteChilds
	 */
	public void DeleteDialogSetting(String strDialogId, boolean bDeleteChilds);

	/**
	 * 
	 * @param strGridId
	 * @param bDeleteChilds
	 */
	public void DeleteGridSetting(String strGridId, boolean bDeleteChilds);

	/**
	 * 
	 * @param strTabId
	 * @param bDeleteChilds
	 */
	public void DeleteTabSetting(String strTabId, boolean bDeleteChilds);

	/**
	 * 
	 * @param strDialogId
	 */
	public void FlushDialogSetting(String strDialogId);

	/**
	 * 
	 * @param strGridId
	 */
	public void FlushGridSetting(String strGridId);

	/**
	 * 
	 * @param strTabId
	 */
	public void FlushTabSetting(String strTabId);

	/**
	 * 
	 * @param strDialogId
	 */
	public String GetAutomaticAction(String strDialogId);

	/**
	 * 
	 * @param strDialogId
	 * @param state
	 * @param location
	 * @param size
	 */
	public void GetDialogPositionInfo(String strDialogId, FormWindowState state, Point location, Size size);

	/**
	 * 
	 * @param strGridId
	 */
	public String GetGridActiveRowRecID(String strGridId);

	/**
	 * 
	 * @param strGridId
	 */
	public ArrayList GetGridGroupBranchStatus(String strGridId);

	/**
	 * 
	 * @param strGridId
	 */
	public boolean GetGridOnlyStoreExpand(String strGridId);

	/**
	 * 
	 * @param strGridId
	 */
	public List GetGridSettings(String strGridId);

	/**
	 * 
	 * @param strGridId
	 */
	public List GetGridSettingsColumnNames(String strGridId);

	/**
	 * 
	 * @param strGridId
	 */
	public string[] GetGridSortOrder(String strGridId);

	/**
	 * 
	 * @param strTabId
	 */
	public int GetSelectedTabIndex(String strTabId);

	/**
	 * 
	 * @param strDialogId
	 */
	public boolean IsMessageSuppressed(String strDialogId);

	/**
	 * 
	 * @param strDialogId
	 * @param state
	 * @param location
	 * @param size
	 */
	public void SetDialogPositionInfo(String strDialogId, FormWindowState state, Point location, Size size);

	/**
	 * 
	 * @param strGridId
	 * @param activeRowID
	 */
	public void SetGridActiveRowRecID(String strGridId, String activeRowID);

	/**
	 * 
	 * @param strGridId
	 * @param branchStatus
	 */
	public void SetGridGroupBranchStatus(String strGridId, ArrayList branchStatus);

	/**
	 * 
	 * @param strGridId
	 * @param columns
	 */
	public void SetGridSettings(String strGridId, List columns);

	/**
	 * 
	 * @param strGridId
	 * @param orders
	 */
	public void SetGridSortOrder(String strGridId, string[] orders);

	/**
	 * 
	 * @param strTabId
	 * @param selectedTabIndex
	 */
	public void SetSelectedTabIndex(String strTabId, int selectedTabIndex);

	/**
	 * 
	 * @param strDialogId
	 * @param strAutomaticAction
	 */
	public void SuppressMessage(String strDialogId, String strAutomaticAction);

}