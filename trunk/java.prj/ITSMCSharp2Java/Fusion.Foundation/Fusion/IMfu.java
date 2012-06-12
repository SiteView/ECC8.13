package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:49
 */
public interface IMfu {

	/**
	 * 
	 * @param strMfuId
	 * @param strItem
	 */
	public void AddItem(String strMfuId, String strItem);

	/**
	 * 
	 * @param strMfuId
	 */
	public void ClearItems(String strMfuId);

	/**
	 * 
	 * @param strMfuId
	 * @param bDeleteChilds
	 */
	public void Delete(String strMfuId, boolean bDeleteChilds);

	/**
	 * 
	 * @param strMfuId
	 */
	public void Flush(String strMfuId);

	/**
	 * 
	 * @param strMfuId
	 */
	public List GetItems(String strMfuId);

	/**
	 * 
	 * @param strMfuId
	 */
	public int GetMaximumItemCount(String strMfuId);

	/**
	 * 
	 * @param strMfuId
	 */
	public boolean IsPersistent(String strMfuId);

	/**
	 * 
	 * @param strMfuId
	 * @param strValue
	 */
	public void RemoveItem(String strMfuId, String strValue);

	/**
	 * 
	 * @param strMfuId
	 * @param nCount
	 */
	public void SetMaximumItemCount(String strMfuId, int nCount);

	/**
	 * 
	 * @param strMfuId
	 * @param bPersistent
	 */
	public void SetPersistent(String strMfuId, boolean bPersistent);

}