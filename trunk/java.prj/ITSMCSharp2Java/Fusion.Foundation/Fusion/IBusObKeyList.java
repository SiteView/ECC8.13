package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:45
 */
public interface IBusObKeyList extends IListICollection, IEnumerable {

	public IBusObKey Current();

	public int CurrentPos();

	public boolean First();

	public boolean HasItems();

	/**
	 * 
	 * @param iPos
	 */
	public boolean Jump(int iPos);

	public boolean Last();

	public boolean Next();

	public boolean Previous();

	/**
	 * 
	 * @param nIndex
	 * @param nCount
	 */
	public List SubsetOfKeyList(int nIndex, int nCount);

}