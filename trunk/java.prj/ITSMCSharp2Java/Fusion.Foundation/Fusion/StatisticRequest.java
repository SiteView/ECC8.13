package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:21
 */
public class StatisticRequest {

	private StatisticScheduling m_BackStatisticScheduling;
	private boolean m_bBackStatisticsRequired;
	private boolean m_bEnableBackStatistics;
	private boolean m_bForceRecalculation;
	private DateTime m_dtBackStatisticsEndDateTime;
	private DateTime m_dtBackStatisticsStartDateTime;
	private DateTime m_dtExpectedDateTime;
	private Fusion.FusionQuery m_FusionQuery;
	private int m_nLogExpirationTotalDays;
	private int m_nNumOfBackStatistics;
	private String m_strBackStatisticSchedulingValue;
	private String m_strDefinitionId;
	private String m_strId;
	private String m_strName;
	private TimeSpan m_tsStatisticDateTimeOffset;



	public void finalize() throws Throwable {

	}

	public StatisticRequest(){

	}

	/**
	 * 
	 * @param strDefinitionId
	 * @param strRequestId
	 */
	public StatisticRequest(String strDefinitionId, String strRequestId){

	}

	public StatisticScheduling BackStatisticScheduling(){
		return null;
	}

	public String BackStatisticSchedulingValue(){
		return "";
	}

	public DateTime BackStatisticsEndDateTime(){
		return null;
	}

	public boolean BackStatisticsRequired(){
		return null;
	}

	public DateTime BackStatisticsStartDateTime(){
		return null;
	}

	public StatisticRequest Clone(){
		return null;
	}

	/**
	 * 
	 * @param request
	 */
	public void CopyContents(StatisticRequest request){

	}

	public String DefinitionId(){
		return "";
	}

	public boolean EnableBackStatistics(){
		return null;
	}

	public DateTime ExpectedDateTime(){
		return null;
	}

	public boolean ForceRecalculation(){
		return null;
	}

	public Fusion.FusionQuery FusionQuery(){
		return null;
	}

	public String Id(){
		return "";
	}

	public int LogExpirationTotalDays(){
		return 0;
	}

	public String Name(){
		return "";
	}

	public int NumOfBackStatistics(){
		return 0;
	}

	public TimeSpan StatisticDateTimeOffset(){
		return null;
	}

}