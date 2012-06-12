package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:36
 */
public class SimpleQueryResolver {

	private IOrchestrator m_orch = null;

	public SimpleQueryResolver(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param orch
	 */
	public SimpleQueryResolver(IOrchestrator orch){

	}

	/**
	 * 
	 * @param phQueryGroup
	 */
	public List GetQueryGroupAsBusObList(PlaceHolder phQueryGroup){
		return null;
	}

	/**
	 * 
	 * @param defQueryGroup
	 */
	public List GetQueryGroupAsBusObList(QueryGroupDef defQueryGroup){
		return null;
	}

	/**
	 * 
	 * @param queryGroupName
	 * @param scopeType
	 * @param scopeOwner
	 * @param linkedTo
	 */
	public List GetQueryGroupAsBusObList(String queryGroupName, Scope scopeType, String scopeOwner, String linkedTo){
		return null;
	}

	/**
	 * 
	 * @param phQueryGroup
	 */
	public IBusObKeyList GetQueryGroupAsKeyList(PlaceHolder phQueryGroup){
		return null;
	}

	/**
	 * 
	 * @param defQueryGroup
	 */
	public IBusObKeyList GetQueryGroupAsKeyList(QueryGroupDef defQueryGroup){
		return null;
	}

	/**
	 * 
	 * @param queryGroupName
	 * @param scopeType
	 * @param scopeOwner
	 * @param linkedTo
	 */
	public IBusObKeyList GetQueryGroupAsKeyList(String queryGroupName, Scope scopeType, String scopeOwner, String linkedTo){
		return null;
	}

	/**
	 * 
	 * @param queries
	 */
	public List ResolveQueries(List queries){
		return null;
	}

	/**
	 * 
	 * @param query
	 */
	public IQueryResult ResolveQuery(FusionQuery query){
		return null;
	}

	/**
	 * 
	 * @param query
	 */
	public DataTable ResolveQueryToBusObDataTable(FusionQuery query){
		return null;
	}

	/**
	 * 
	 * @param query
	 * @param result
	 */
	public DataTable ResolveQueryToBusObDataTable(FusionQuery query, DataSetResult result){
		return null;
	}

	/**
	 * 
	 * @param query
	 */
	public List ResolveQueryToBusObList(FusionQuery query){
		return null;
	}

	/**
	 * 
	 * @param query
	 * @param startTransaction
	 */
	public List ResolveQueryToBusObList(FusionQuery query, boolean startTransaction){
		return null;
	}

	/**
	 * 
	 * @param query
	 * @param result
	 */
	public List ResolveQueryToBusObList(FusionQuery query, DataSetResult result){
		return null;
	}

	/**
	 * 
	 * @param query
	 * @param startTransaction
	 * @param result
	 */
	public List ResolveQueryToBusObList(FusionQuery query, boolean startTransaction, DataSetResult result){
		return null;
	}

	/**
	 * 
	 * @param query
	 */
	public IBusObKeyList ResolveQueryToKeyList(FusionQuery query){
		return null;
	}

	/**
	 * 
	 * @param query
	 * @param ownerBusObId
	 * @param relationshipName
	 */
	public DataTable ResolveRollUpQueryToDataTable(FusionQuery query, String ownerBusObId, String relationshipName){
		return null;
	}

	/**
	 * 
	 * @param query
	 * @param relationshipName
	 */
	public List ResolveRollUpQueryToDataTables(FusionQuery query, String relationshipName){
		return null;
	}

}