package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:46:08
 */
public class VirtualQueryResolver {

	private IOrchestrator m_orch = null;

	public VirtualQueryResolver(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param orch
	 */
	public VirtualQueryResolver(IOrchestrator orch){

	}

	/**
	 * 
	 * @param busObKeyList
	 */
	public List ResolveCurrentPageToBusObList(IVirtualBusObKeyList busObKeyList){
		return null;
	}

	/**
	 * 
	 * @param query
	 */
	public IVirtualBusObKeyList ResolveQueryToVirtualKeyList(FusionQuery query){
		return null;
	}

	/**
	 * 
	 * @param query
	 * @param queryCount
	 */
	public IVirtualBusObKeyList ResolveQueryToVirtualKeyList(FusionQuery query, FusionQuery queryCount){
		return null;
	}

	/**
	 * 
	 * @param query
	 * @param keysPerQuery
	 * @param maxResultsPerQuery
	 */
	public IVirtualBusObKeyList ResolveQueryToVirtualKeyList(FusionQuery query, int keysPerQuery, int maxResultsPerQuery){
		return null;
	}

	/**
	 * 
	 * @param query
	 * @param queryCount
	 * @param nKeysPerQuery
	 * @param nMaxResultsPerQuery
	 */
	public IVirtualBusObKeyList ResolveQueryToVirtualKeyList(FusionQuery query, FusionQuery queryCount, int nKeysPerQuery, int nMaxResultsPerQuery){
		return null;
	}

}