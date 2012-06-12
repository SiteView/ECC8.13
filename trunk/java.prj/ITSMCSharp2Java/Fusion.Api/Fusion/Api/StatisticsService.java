package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:39
 */
public class StatisticsService extends FusionAggregate {

	public StatisticsService(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public StatisticsService(Object fusionObject){

	}

	/**
	 * 
	 * @param strDefinitionId
	 * @param strRequestId
	 */
	public void ClearCachedStatistics(String strDefinitionId, String strRequestId){

	}

	public void ExpireLoggedStatistics(){

	}

	/**
	 * 
	 * @param request
	 */
	public IQueryResult GetStatistics(StatisticRequest request){
		return null;
	}

	/**
	 * 
	 * @param request
	 */
	public void RegisterStatisticRequest(StatisticRequest request){

	}

	/**
	 * 
	 * @param strDefinitionId
	 * @param strRequestId
	 * @param bDeleteLoggedData
	 */
	public void UnregisterStatisticRequest(String strDefinitionId, String strRequestId, boolean bDeleteLoggedData){

	}

	/**
	 * 
	 * @param request
	 * @param bDeleteLoggedData
	 * @param bResetNextScheduledDateTime
	 */
	public void UpdateRegisteredStatisticRequest(StatisticRequest request, boolean bDeleteLoggedData, boolean bResetNextScheduledDateTime){

	}

	private Fusion.BusinessLogic.StatisticsService WhoAmI(){
		return null;
	}

}