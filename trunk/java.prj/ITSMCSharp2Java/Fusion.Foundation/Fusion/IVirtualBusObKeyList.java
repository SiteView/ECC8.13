package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:00
 */
public interface IVirtualBusObKeyList extends IVirtualKeyList, IDisposable {

	/**
	 * 
	 * @param dictFieldToValue
	 */
	public void AddRowOfData(IDictionary dictFieldToValue);

	public List BusObListForCurrentPage();

	public void CacheToDisk();

	/**
	 * 
	 * @param query
	 */
	public void ChangeSearchCriteria(FusionQuery query);

	public IVirtualBusObKeyList Clone();

	public int CurrentListCount();

	public int CurrentPage();

	/**
	 * 
	 * @param nRow
	 */
	public DataRow DataForRow(int nRow);

	/**
	 * 
	 * @param nRow
	 * @param strQualifiedColumnName
	 */
	public Object DataForRowItem(int nRow, String strQualifiedColumnName);

	/**
	 * 
	 * @param nStart
	 * @param nEnd
	 */
	public DataRow[] DataForRows(int nStart, int nEnd);

	public DataRow[] DataRowsForCurrentPage();

	public String DiskFileName();

	public void FirstPage();

	/**
	 * 
	 * @param nRow
	 */
	public IVirtualBusObKey GetKey(int nRow);

	/**
	 * 
	 * @param strId
	 * @param nPositionInKeyList
	 */
	public IVirtualBusObKey GetKeyById(String strId, int nPositionInKeyList);

	/**
	 * 
	 * @param nStart
	 * @param nEnd
	 */
	public List GetKeys(int nStart, int nEnd);

	public boolean NextPage();

	/**
	 * 
	 * @param nStart
	 * @param nEnd
	 */
	public void PreLoadDataForRows(int nStart, int nEnd);

	public void ReadFromDisk();

	public void RemoveAssociatedDiskCache();

	/**
	 * 
	 * @param nRows
	 */
	public boolean Skip(int nRows);

	/**
	 * 
	 * @param query
	 */
	public void SortKeysDifferently(FusionQuery query);

	public FusionQuery SpecialQueryForCount();

	/**
	 * 
	 * @param nStartPos
	 * @param nCount
	 */
	public List SubsetOfKeyList(int nStartPos, int nCount);

	public int TotalPages();

	/**
	 * 
	 * @param strColumnName
	 */
	public String TranslateColumnName(String strColumnName);

	/**
	 * 
	 * @param strId
	 * @param dictFieldToValue
	 */
	public void UpdateRowOfData(String strId, Map dictFieldToValue);

}