package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:00
 */
public interface IVirtualKeyList extends IDisposable {

	public boolean AddAboveCurrentRow();

	/**
	 * 
	 * @param strId
	 * @param strName
	 */
	public int AddKey(String strId, String strName);

	public int Count();

	public IVirtualBusObKey Current();

	public int CurrentPosition();

	public void First();

	public boolean HasItems();

	/**
	 * 
	 * @param nPos
	 */
	public boolean Jump(int nPos);

	public void Last();

	public boolean Next();

	public boolean Previous();

	/**
	 * 
	 * @param strId
	 */
	public void RemoveCachedDataForRow(String strId);

	public void RemoveCurrentKey();

}