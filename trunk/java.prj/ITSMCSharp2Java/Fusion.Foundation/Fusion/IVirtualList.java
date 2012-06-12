package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:00
 */
public interface IVirtualList extends IListICollection, IEnumerable {

	/**
	 * 
	 * @param aFields
	 */
	public void AddGroupBy(string[] aFields);

	/**
	 * 
	 * @param bAscending
	 * @param aFields
	 */
	public void AddOrderBy(boolean bAscending, string[] aFields);

	public CellDataRequestedHandler CellDataRequested();

	public void ClearFilter();

	public int DesiredPageSize();

	/**
	 * 
	 * @param iRow
	 * @param sColumn
	 */
	public Object GetCellData(int iRow, String sColumn);

	/**
	 * 
	 * @param iFunction
	 * @param iStart
	 */
	public Object GetFunction(int iFunction, int iStart);

	/**
	 * 
	 * @param iRow
	 */
	public DataRow GetRowData(int iRow);

	/**
	 * 
	 * @param sField
	 */
	public int HasGroupBy(String sField);

	public boolean IgnoreRequest();

	public IQueryResult MoveToFirstPage();

	public IQueryResult MoveToNextPage();

	/**
	 * 
	 * @param iPage
	 */
	public IQueryResult MoveToPage(int iPage);

	public IQueryResult MoveToPrevPage();

	public int PagesCount();

	public int PageSize();

	public FusionQuery Query();

	/**
	 * 
	 * @param ind
	 */
	public int RecordPage(int ind);

	/**
	 * 
	 * @param aFields
	 */
	public void RemoveGroupBy(string[] aFields);

	/**
	 * 
	 * @param aFields
	 */
	public void RemoveOrderBy(string[] aFields);

	public void Reset();

	/**
	 * 
	 * @param el
	 */
	public DataTable ResolveFunctions(XmlElement[] el);

	/**
	 * 
	 * @param el
	 */
	public void SetFilter(XmlElement el);

	public void SoftReset();

}