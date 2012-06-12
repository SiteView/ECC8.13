package Fusion.Api;

import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:37
 */
public class SqlServerReplicationDef extends ReplicationDef implements ISqlServerReplicationDef {

	public SqlServerReplicationDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public SqlServerReplicationDef(Object fusionObject){

	}

	/**
	 * 
	 * @param articleName
	 * @param filterName
	 * @param joinArticleName
	 * @param joinFilterClause
	 * @param joinOnUniqueKey
	 * @param forceInvalidateSnapshot
	 * @param forceReinitSubscription
	 */
	public ISqlServerFilterCriteria AddJoinArticleFilter(String articleName, String filterName, String joinArticleName, String joinFilterClause, boolean joinOnUniqueKey, boolean forceInvalidateSnapshot, boolean forceReinitSubscription){
		return null;
	}

	/**
	 * 
	 * @param loginId
	 */
	public void AddPublicationAccessLoginId(String loginId){

	}

	public boolean AddPublicationInfoToActiveDirectory(){
		return null;
	}

	/**
	 * 
	 * @param subscriberServerName
	 * @param subscriberDescription
	 * @param subscriberSecurityMode
	 * @param subscriberLoginForPublisher
	 * @param subscriberPwdForPublisher
	 * @param subscriberFrequencyType
	 * @param subscriberFrequencyInterval
	 * @param subscriberFrequencyRelativeInterval
	 * @param subscriberFrequencyRecurrenceFactor
	 * @param subscriberFrequencySubday
	 * @param subscriberFrequencySubdayInterval
	 * @param subscriberActiveStartDateTime
	 * @param subscriberActiveEndDateTime
	 */
	public ISqlServerSubscriberInfo AddSubscriber(String subscriberServerName, String subscriberDescription, int subscriberSecurityMode, String subscriberLoginForPublisher, String subscriberPwdForPublisher, int subscriberFrequencyType, int subscriberFrequencyInterval, int subscriberFrequencyRelativeInterval, int subscriberFrequencyRecurrenceFactor, int subscriberFrequencySubday, int subscriberFrequencySubdayInterval, Date subscriberActiveStartDateTime, Date subscriberActiveEndDateTime){
		return null;
	}

	/**
	 * 
	 * @param strArticleName
	 * @param strSubsetFilterClause
	 */
	public void AddSubsetArticleFilter(String strArticleName, String strSubsetFilterClause){

	}

	public boolean AllowAlternatePublisherSynchronizationPartner(){
		return null;
	}

	public boolean AllowAnonymousSubscriptions(){
		return null;
	}

	public boolean AllowPullSubscriptions(){
		return null;
	}

	public boolean AllowPushSubscriptions(){
		return null;
	}

	public boolean AllowSubscriptionCopy(){
		return null;
	}

	public String AlternateSnapshotFolder(){
		return "";
	}

	public boolean ArticleAllowInteractiveResolver(){
		return null;
	}

	public boolean ArticleAutoIdentityRange(){
		return null;
	}

	public int ArticleCheckPermissions(){
		return 0;
	}

	public String ArticleCreationScript(){
		return "";
	}

	public String ArticleDestinationOwner(){
		return "";
	}

	public boolean ArticleFastMulticolUpdateProc(){
		return null;
	}

	public boolean ArticleForceInvalidateSnapshot(){
		return null;
	}

	public String ArticlePreCreationCmd(){
		return "";
	}

	public int ArticlePubIdentityRange(){
		return 0;
	}

	public String ArticleResolver(){
		return "";
	}

	public String ArticleResolverInfo(){
		return "";
	}

	public int ArticleSchemaOption(){
		return 0;
	}

	public String ArticleSourceOwner(){
		return "";
	}

	public String ArticleStatus(){
		return "";
	}

	public int ArticleSubIdentityRange(){
		return 0;
	}

	public int ArticleThreshold(){
		return 0;
	}

	public boolean ArticleVerifyResolverSignature(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public boolean CompressSnapshot(){
		return null;
	}

	public int ConflictRetentionDays(){
		return 0;
	}

	public boolean ConflictsStoredOnPublisherOnly(){
		return null;
	}

	public String DistributionDb(){
		return "";
	}

	public String DistributionDbDataFile(){
		return "";
	}

	public int DistributionDbDataFileSize(){
		return 0;
	}

	public String DistributionDbDataFolder(){
		return "";
	}

	public int DistributionDbSecurityMode(){
		return 0;
	}

	public String DistributorAdminPassword(){
		return "";
	}

	public int DistributorCreateMode(){
		return 0;
	}

	public String DistributorDbLogin(){
		return "";
	}

	public String DistributorDbPassword(){
		return "";
	}

	public String DistributorFtpServiceAddress(){
		return "";
	}

	public String DistributorFtpServiceLogin(){
		return "";
	}

	public String DistributorFtpServicePassword(){
		return "";
	}

	public int DistributorFtpServicePort(){
		return 0;
	}

	public String DistributorFtpServiceSubdirectory(){
		return "";
	}

	public int DistributorHeartbeatInterval(){
		return 0;
	}

	public int DistributorHistoryRetention(){
		return 0;
	}

	public String DistributorLogFile(){
		return "";
	}

	public int DistributorLogFileSize(){
		return 0;
	}

	public String DistributorLogFolder(){
		return "";
	}

	public int DistributorMaxRetention(){
		return 0;
	}

	public int DistributorMinRetention(){
		return 0;
	}

	public String DistributorServerName(){
		return "";
	}

	/**
	 * 
	 * @param filter
	 */
	private ISqlServerFilterCriteria GetAggregate(ISqlServerFilterCriteria filter){
		return null;
	}

	/**
	 * 
	 * @param info
	 */
	private ISqlServerSubscriberInfo GetAggregate(ISqlServerSubscriberInfo info){
		return null;
	}

	public List JoinArticleFilters(){
		return null;
	}

	public boolean KeepPartitionChanges(){
		return null;
	}

	public int MaxConcurrentDynamicSnapshots(){
		return 0;
	}

	public int MaxConcurrentMergeProcesses(){
		return 0;
	}

	public String PostSnapshotScript(){
		return "";
	}

	public String PreSnapshotScript(){
		return "";
	}

	public List PublicationAccessLoginIds(){
		return null;
	}

	public String PublicationDescription(){
		return "";
	}

	public boolean PublicationEnabledForInternet(){
		return null;
	}

	public int PublicationRetention(){
		return 0;
	}

	public String PublisherDbLogin(){
		return "";
	}

	public String PublisherDbPassword(){
		return "";
	}

	public boolean PublisherEncryptedPassword(){
		return null;
	}

	public int PublisherSecurityMode(){
		return 0;
	}

	public String PublisherServerName(){
		return "";
	}

	public String PublisherTrusted(){
		return "";
	}

	public String PublisherWorkingDirectory(){
		return "";
	}

	public Date PubSnapshotActiveEndDateTime(){
		return null;
	}

	public Date PubSnapshotActiveStartDateTime(){
		return null;
	}

	public int PubSnapshotFrequencyInterval(){
		return 0;
	}

	public int PubSnapshotFrequencyRecurrenceFactor(){
		return 0;
	}

	public int PubSnapshotFrequencyRelativeInterval(){
		return 0;
	}

	public int PubSnapshotFrequencySubday(){
		return 0;
	}

	public int PubSnapshotFrequencySubdayInterval(){
		return 0;
	}

	public int PubSnapshotFrequencyType(){
		return 0;
	}

	public String ReplicationDatabase(){
		return "";
	}

	public boolean SnapshotFilesInDefaultFolder(){
		return null;
	}

	public List Subscribers(){
		return null;
	}

	public String SubscriberSyncMode(){
		return "";
	}

	public Map SubsetFilters(){
		return null;
	}

	public boolean TableArticleColumnTracking(){
		return null;
	}

	public boolean UseDynamicFilters(){
		return null;
	}

	public String ValidateSubscriberInfoFunctions(){
		return "";
	}

	private Fusion.BusinessLogic.SqlServerReplicationDef WhoAmI(){
		return null;
	}

}