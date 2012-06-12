package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:08
 */
public class PagedQueryResolver {

	private IOrchestrator m_orch = null;

	public PagedQueryResolver(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param orch
	 */
	public PagedQueryResolver(IOrchestrator orch){

	}

	/**
	 * 
	 * @param query
	 * @param nRowsOfData
	 * @param pos
	 * @param strRowPositionXml
	 * @param astrFields
	 */
	public IQueryResult PagedFusionQueryForFields(FusionQuery query, int nRowsOfData, QueryPosition pos, String strRowPositionXml, String[] astrFields){
		return null;
	}

	/**
	 * 
	 * @param query
	 * @param nRowsOfData
	 * @param pos
	 * @param RowPosition
	 * @param rpi
	 * @param prevRes
	 */
	public IQueryResult PagedFusionQueryForFields(FusionQuery query, int nRowsOfData, QueryPosition pos, List RowPosition, FusionQuery.RelationshipPageInfo rpi, DataTable prevRes){
		return null;
	}

	/**
	 * 
	 * @param query
	 * @param nRowsOfData
	 * @param pos
	 * @param strRowPositionXml
	 */
	public IQueryResult PagedFusionQueryForKeys(FusionQuery query, int nRowsOfData, QueryPosition pos, String strRowPositionXml){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strQueryGroupName
	 * @param nRowsOfData
	 * @param pos
	 * @param strRowPositionXml
	 * @param astrFields
	 */
	public IQueryResult PagedQueryGroupForFields(Scope scopeType, String strScopeOwner, String strLinkedTo, String strQueryGroupName, int nRowsOfData, QueryPosition pos, String strRowPositionXml, String[] astrFields){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strQueryGroupName
	 * @param nRowsOfData
	 * @param pos
	 * @param strRowPositionXml
	 */
	public IQueryResult PagedQueryGroupForKeys(Scope scopeType, String strScopeOwner, String strLinkedTo, String strQueryGroupName, int nRowsOfData, QueryPosition pos, String strRowPositionXml){
		return null;
	}

	/**
	 * 
	 * @param query
	 * @param nRowsOfData
	 * @param pos
	 * @param strRowPositionXml
	 * @param resultQuery
	 */
	public List ResolvePagedFusionQueryToBusObList(FusionQuery query, int nRowsOfData, QueryPosition pos, String strRowPositionXml, IQueryResult resultQuery){
		return null;
	}

}