package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:57
 */
public interface ISqlServerReplicationDef {

	/**
	 * 
	 * @param strArticleName
	 * @param strFilterName
	 * @param strJoinArticleName
	 * @param strJoinFilterClause
	 * @param bJoinOnUniqueKey
	 * @param bForceInvalidateSnapshot
	 * @param bForceReinitSubscription
	 */
	public ISqlServerFilterCriteria AddJoinArticleFilter(String strArticleName, String strFilterName, String strJoinArticleName, String strJoinFilterClause, boolean bJoinOnUniqueKey, boolean bForceInvalidateSnapshot, boolean bForceReinitSubscription);

	/**
	 * 
	 * @param strLoginId
	 */
	public void AddPublicationAccessLoginId(String strLoginId);

	public boolean AddPublicationInfoToActiveDirectory();

	/**
	 * 
	 * @param strSubscriberServerName
	 * @param strSubscriberDescription
	 * @param nSubscriberSecurityMode
	 * @param strSubscriberLoginForPublisher
	 * @param strSubscriberPwdForPublisher
	 * @param nSubscriberFrequencyType
	 * @param nSubscriberFrequencyInterval
	 * @param nSubscriberFrequencyRelativeInterval
	 * @param nSubscriberFrequencyRecurrenceFactor
	 * @param nSubscriberFrequencySubday
	 * @param nSubscriberFrequencySubdayInterval
	 * @param dtSubscriberActiveStartDateTime
	 * @param dtSubscriberActiveEndDateTime
	 */
	public ISqlServerSubscriberInfo AddSubscriber(String strSubscriberServerName, String strSubscriberDescription, int nSubscriberSecurityMode, String strSubscriberLoginForPublisher, String strSubscriberPwdForPublisher, int nSubscriberFrequencyType, int nSubscriberFrequencyInterval, int nSubscriberFrequencyRelativeInterval, int nSubscriberFrequencyRecurrenceFactor, int nSubscriberFrequencySubday, int nSubscriberFrequencySubdayInterval, DateTime dtSubscriberActiveStartDateTime, DateTime dtSubscriberActiveEndDateTime);

	/**
	 * 
	 * @param strArticleName
	 * @param strSubsetFilterClause
	 */
	public void AddSubsetArticleFilter(String strArticleName, String strSubsetFilterClause);

	public boolean AllowAlternatePublisherSynchronizationPartner();

	public boolean AllowAnonymousSubscriptions();

	public boolean AllowPullSubscriptions();

	public boolean AllowPushSubscriptions();

	public boolean AllowSubscriptionCopy();

	public String AlternateSnapshotFolder();

	public boolean ArticleAllowInteractiveResolver();

	public boolean ArticleAutoIdentityRange();

	public int ArticleCheckPermissions();

	public String ArticleCreationScript();

	public String ArticleDestinationOwner();

	public boolean ArticleFastMulticolUpdateProc();

	public boolean ArticleForceInvalidateSnapshot();

	public String ArticlePreCreationCmd();

	public int ArticlePubIdentityRange();

	public String ArticleResolver();

	public String ArticleResolverInfo();

	public int ArticleSchemaOption();

	public String ArticleSourceOwner();

	public String ArticleStatus();

	public int ArticleSubIdentityRange();

	public int ArticleThreshold();

	public boolean ArticleVerifyResolverSignature();

	public boolean CompressSnapshot();

	public int ConflictRetentionDays();

	public boolean ConflictsStoredOnPublisherOnly();

	public String DistributionDb();

	public String DistributionDbDataFile();

	public int DistributionDbDataFileSize();

	public String DistributionDbDataFolder();

	public int DistributionDbSecurityMode();

	public String DistributorAdminPassword();

	public int DistributorCreateMode();

	public String DistributorDbLogin();

	public String DistributorDbPassword();

	public String DistributorFtpServiceAddress();

	public String DistributorFtpServiceLogin();

	public String DistributorFtpServicePassword();

	public int DistributorFtpServicePort();

	public String DistributorFtpServiceSubdirectory();

	public int DistributorHeartbeatInterval();

	public int DistributorHistoryRetention();

	public String DistributorLogFile();

	public int DistributorLogFileSize();

	public String DistributorLogFolder();

	public int DistributorMaxRetention();

	public int DistributorMinRetention();

	public String DistributorServerName();

	public List JoinArticleFilters();

	public boolean KeepPartitionChanges();

	public int MaxConcurrentDynamicSnapshots();

	public int MaxConcurrentMergeProcesses();

	public String PostSnapshotScript();

	public String PreSnapshotScript();

	public List PublicationAccessLoginIds();

	public String PublicationDescription();

	public boolean PublicationEnabledForInternet();

	public String PublicationName();

	public int PublicationRetention();

	public String PublisherDbLogin();

	public String PublisherDbPassword();

	public boolean PublisherEncryptedPassword();

	public int PublisherSecurityMode();

	public String PublisherServerName();

	public String PublisherTrusted();

	public String PublisherWorkingDirectory();

	public DateTime PubSnapshotActiveEndDateTime();

	public DateTime PubSnapshotActiveStartDateTime();

	public int PubSnapshotFrequencyInterval();

	public int PubSnapshotFrequencyRecurrenceFactor();

	public int PubSnapshotFrequencyRelativeInterval();

	public int PubSnapshotFrequencySubday();

	public int PubSnapshotFrequencySubdayInterval();

	public int PubSnapshotFrequencyType();

	public String ReplicationDatabase();

	public boolean SnapshotFilesInDefaultFolder();

	public List Subscribers();

	public String SubscriberSyncMode();

	public Map SubsetFilters();

	public boolean TableArticleColumnTracking();

	public boolean UseDynamicFilters();

	public String ValidateSubscriberInfoFunctions();

}