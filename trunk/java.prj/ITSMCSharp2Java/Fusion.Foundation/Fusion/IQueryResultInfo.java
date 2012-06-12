package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:53
 */
public interface IQueryResultInfo {

	public boolean AdditionalRows();

	public String BusinessObjectName();

	public String BusObNameColumn();

	public int Found();

	public List OrderByList();

	public Fusion.PagingInfo PagingInfo();

	public String RecIdColumn();

	public DataSetResult Result();

	public boolean ResultFromLinkBasedRelationship();

	public int Returned();

	public String RowPositionXml();

	/**
	 * 
	 * @param nCount
	 */
	public void SetCountRetrieved(int nCount);

	/**
	 * 
	 * @param nTableItems
	 */
	public void SetEntireTableRetrieved(int nTableItems);

	/**
	 * 
	 * @param nPos
	 * @param oStartValue
	 * @param oEndValue
	 */
	public void SetLastOrderByValues(int nPos, Object oStartValue, Object oEndValue);

	/**
	 * 
	 * @param nPos
	 * @param oStartValue
	 * @param oEndValue
	 * @param bAscending
	 */
	public void SetLastOrderByValues(int nPos, Object oStartValue, Object oEndValue, boolean bAscending);

	public void SetNoDataFound();

	/**
	 * 
	 * @param nFound
	 * @param nRetrieved
	 */
	public void SetPartialDataRetrieved(int nFound, int nRetrieved);

	public QueryInfoToGet TypeOfDataHeld();

}