package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:50
 */
public interface IMru {

	/**
	 * 
	 * @param strMruId
	 * @param strItem
	 */
	public void AddItem(String strMruId, String strItem);

	/**
	 * 
	 * @param strMruId
	 */
	public void ClearItems(String strMruId);

	/**
	 * 
	 * @param strMruId
	 * @param bDeleteChilds
	 */
	public void Delete(String strMruId, boolean bDeleteChilds);

	/**
	 * 
	 * @param strMruId
	 */
	public void Flush(String strMruId);

	/**
	 * 
	 * @param strMruId
	 */
	public List GetItems(String strMruId);

	/**
	 * 
	 * @param strMruId
	 */
	public int GetMaximumItemCount(String strMruId);

	/**
	 * 
	 * @param strMruId
	 */
	public boolean IsPersistent(String strMruId);

	/**
	 * 
	 * @param strMruId
	 * @param strItem
	 */
	public void RemoveItem(String strMruId, String strItem);

	/**
	 * 
	 * @param strMruId
	 * @param nCount
	 */
	public void SetMaximumItemCount(String strMruId, int nCount);

	/**
	 * 
	 * @param strMruId
	 * @param bPersistent
	 */
	public void SetPersistent(String strMruId, boolean bPersistent);

}