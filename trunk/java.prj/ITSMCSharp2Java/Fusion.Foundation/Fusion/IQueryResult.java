package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:53
 */
public interface IQueryResult {

	public boolean AdditionalRows();

	/**
	 * 
	 * @param strOwnerBusObId
	 * @param strRelationshipName
	 * @param strRelatedBusObName
	 */
	public DataTable AddLinkedBusinessObjectDataTable(String strOwnerBusObId, String strRelationshipName, String strRelatedBusObName);

	/**
	 * 
	 * @param strBusObId
	 * @param strRelationshipName
	 */
	public DataTable AddRelationshipDataTable(String strBusObId, String strRelationshipName);

	public String BusinessObjectName();

	public DataTable BusObDataTable();

	public String BusObNameColumn();

	/**
	 * 
	 * @param strTableName
	 */
	public void DeleteDataTable(String strTableName);

	public int Found();

	/**
	 * 
	 * @param strId
	 */
	public DataRow GetBusObDataRow(String strId);

	/**
	 * 
	 * @param strOwnerBusObId
	 * @param strRelationshipName
	 * @param strRelatedBusObName
	 */
	public DataTable GetLinkedBusinessObjectTable(String strOwnerBusObId, String strRelationshipName, String strRelatedBusObName);

	/**
	 * 
	 * @param strOwnerBusObId
	 * @param strRelationshipName
	 * @param strRelatedBusObName
	 */
	public String GetLinkedBusinessObjectTableName(String strOwnerBusObId, String strRelationshipName, String strRelatedBusObName);

	/**
	 * 
	 * @param strOwnerBusObId
	 * @param strRelationshipName
	 */
	public DataTable GetRelationshipDataTable(String strOwnerBusObId, String strRelationshipName);

	/**
	 * 
	 * @param strBusObId
	 * @param strRelationshipName
	 */
	public IQueryResultInfo GetRelationshipQueryResultInfo(String strBusObId, String strRelationshipName);

	/**
	 * 
	 * @param strBusObId
	 * @param strRelationshipName
	 */
	public String GetRelationshipTableName(String strBusObId, String strRelationshipName);

	/**
	 * 
	 * @param strOwnerBusObId
	 * @param strRelationshipName
	 */
	public DataTable GetRollUpRelationshipDataTable(String strOwnerBusObId, String strRelationshipName);

	/**
	 * 
	 * @param strBusObId
	 * @param strRelationshipName
	 */
	public String GetRollUpRelationshipTableName(String strBusObId, String strRelationshipName);

	/**
	 * 
	 * @param strOwnerBusObId
	 * @param strRelationshipName
	 */
	public boolean HasDataForRelationship(String strOwnerBusObId, String strRelationshipName);

	/**
	 * 
	 * @param strOwnerBusObId
	 * @param strRelationshipName
	 */
	public boolean HasDataForRollUpRelationship(String strOwnerBusObId, String strRelationshipName);

	public IBusObKeyList MakeKeyListFromBusObDataTable();

	public List OrderByList();

	public IQueryResultInfo QueryResultInfo();

	public String RecIdColumn();

	public DataSetResult Result();

	public int Returned();

	public String RowPositionXml();

	/**
	 * 
	 * @param dt
	 */
	public void SetBusinessObjectTable(DataTable dt);

	/**
	 * 
	 * @param nPos
	 * @param oStartValue
	 * @param oEndValue
	 */
	public void SetLastOrderByValues(int nPos, Object oStartValue, Object oEndValue);

	/**
	 * 
	 * @param strBusObId
	 * @param strRelationshipName
	 * @param queryResultInfo
	 */
	public void SetRelationshipQueryResultInfo(String strBusObId, String strRelationshipName, IQueryResultInfo queryResultInfo);

}