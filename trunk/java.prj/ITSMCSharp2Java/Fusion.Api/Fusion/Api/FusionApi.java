package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:37
 */
public final class FusionApi implements IFusionApi {

	private Fusion.Api.ApplicationDefinitionRepository m_adr = null;
	private static IAggregateFactory m_aggFactory = new Fusion.Api.AggregateFactory();
	private IAlertNotificationService m_AlertNotifService = null;
	private Fusion.Api.AttachmentService m_attachmentService = null;
	private IAuthenticationService m_authService = null;
	private boolean m_bConnected = false;
	private IDefinitions m_busObDefs = null;
	private IBusObEventPublisher m_busObEventPublisher;
	private IBusinessObjectService m_busObService = null;
	private ILinkObjects m_calendarClientService = null;
	private ICounterService m_counterService = null;
	private Fusion.Api.InteractionHandler m_InteractionHandler = null;
	private Fusion.Api.LicenseService m_licenseService;
	private Fusion.Api.LicenseType m_licenseType = Fusion.Api.LicenseType.Api;
	private Fusion.Api.DefinitionLibrary m_LiveDefinitionLibrary = null;
	private ILinkObjects m_mailClientService = null;
	private Fusion.Api.MailService m_mailService = null;
	private INotifier m_Notifier = null;
	private IOrchestrator m_orch = null;
	private IResources m_Resources = null;
	private Fusion.Api.RoleManager m_RoleManager = null;
	private ISecurity m_secService = null;
	private ISettings m_settingsService = null;
	private String m_strConnectionName = "";
	private Fusion.Api.StatisticsService m_svcStatistics = null;
	private Fusion.Api.SystemExtensions m_SystemExtensions = null;
	private ISystemFunctions m_systemFunctions = null;
	private ISystemInfo m_systemInfo = null;
	private ITokenService m_tokenService = null;
	private Fusion.Api.ValueResolverService m_valueResolverService = null;



	public void finalize() throws Throwable {

	}

	public FusionApi(){

	}

	public static IAggregateFactory AggregateFactory(){
		return null;
	}

	public IAlertNotificationService AlertNotificationService(){
		return null;
	}

	public IAdr ApplicationDefinitionRepository(){
		return null;
	}

	/**
	 * 
	 * @param strToken
	 */
	public boolean Attach(String strToken){
		return null;
	}

	public boolean Attached(){
		return null;
	}

	public Fusion.Api.AttachmentService AttachmentService(){
		return null;
	}

	public IAuthenticationService AuthenticationService(){
		return null;
	}

	public IDefinitions BusObDefinitions(){
		return null;
	}

	public IBusObEventPublisher BusObEventPublisher(){
		return null;
	}

	public IBusinessObjectService BusObService(){
		return null;
	}

	public ILinkObjects CalendarClientService(){
		return null;
	}

	/**
	 * 
	 * @param strConnectionName
	 */
	public boolean CheckConnectionName(String strConnectionName){
		return null;
	}

	public boolean ConfirmTwoTierMode(){
		return null;
	}

	/**
	 * 
	 * @param connectionName
	 */
	public void Connect(String connectionName){

	}

	/**
	 * 
	 * @param connectionName
	 * @param credentials
	 */
	public void Connect(String connectionName, ICredentials credentials){

	}

	public EventHandler ConnectChanged(){
		return null;
	}

	public boolean Connected(){
		return null;
	}

	public String ConnectionName(){
		return "";
	}

	public ICounterService CounterService(){
		return null;
	}

	/**
	 * 
	 * @param strConnectionName
	 * @param useUnicode
	 * @param bForceCreation
	 */
	public void CreateAndConnect(String strConnectionName, boolean useUnicode, boolean bForceCreation){

	}

	public static IFusionApi CreateInstance(){
		return null;
	}

	public IDataStoreService DataStoreService(){
		return null;
	}

	public String Detach(){
		return "";
	}

	/**
	 * 
	 * @param bPreserveSessionId
	 */
	public String Detach(boolean bPreserveSessionId){
		return "";
	}

	public void Disconnect(){

	}

	/**
	 * 
	 * @param orch
	 */
	public static void DoSystemTableUpgrade(DbOrchestrator orch){

	}

	public Fusion.Api.ExportImportManager ExportImportManager(){
		return null;
	}

	public IAuthenticationBundle GetAuthenticationBundle(){
		return null;
	}

	public List GetUserTypes(){
		return null;
	}

	private void InitServices(){

	}

	public Fusion.Api.InteractionHandler InteractionHandler(){
		return null;
	}

	/**
	 * 
	 * @param strConnectionName
	 * @param strAuthId
	 * @param strPassword
	 * @param strUserType
	 */
	public static boolean IsConnectionValid(String strConnectionName, String strAuthId, String strPassword, String strUserType){
		return null;
	}

	private boolean IsDataVersionCompatible(){
		return null;
	}

	public Fusion.Api.LicenseService LicenseService(){
		return null;
	}

	public Fusion.Api.LicenseType LicenseType(){
		return null;
	}

	public Fusion.Api.DefinitionLibrary LiveDefinitionLibrary(){
		return null;
	}

	public boolean LoggedIn(){
		return null;
	}

	/**
	 * 
	 * @param authentication
	 */
	public boolean Login(IAuthenticationBundle authentication){
		return null;
	}

	public void Logout(){

	}

	/**
	 * 
	 * @param modifiedUsername
	 */
	public void LogoutWeb(String modifiedUsername){

	}

	public ILinkObjects MailClientService(){
		return null;
	}

	public Fusion.Api.MailService MailService(){
		return null;
	}

	public IMessageService MessageService(){
		return null;
	}

	public IModuleManager ModuleManager(){
		return null;
	}

	public INotifier Notifier(){
		return null;
	}

	public IOrchestrator Orch(){
		return null;
	}

	public IPresentation Presentation(){
		return null;
	}

	public Fusion.ReportLibrary ReportLibrary(){
		return null;
	}

	/**
	 * 
	 * @param defLib
	 */
	public void ReregisterAllExternalConnections(Fusion.Api.DefinitionLibrary defLib){

	}

	public IResources Resources(){
		return null;
	}

	public Fusion.Api.RoleManager RoleManager(){
		return null;
	}

	public ISecurity SecurityService(){
		return null;
	}

	/**
	 * [StrongNameIdentityPermission(SecurityAction.LinkDemand,
	 * PublicKey="0024000004800000940000000602000000240000525341310004000001000100196CB
	 * A3664F0E9A38B0AC04F4222DC42FF6724480FE09C4DECA97A0F1EE91F36032A7C8A3E070E4E2F28F
	 * EF93F7FC667177DDB084FE928FB158898810FCD1D69F7445A4E729896F4B6ABA7372CF585FE73584
	 * 9CD4EE6159C3424979973024D4E11FDE5E38B41461A9370EA9DBD7AB52FAD2C419BB2D27B629C008
	 * F166B423FB6")]
	 * 
	 * @param licenseType
	 */
	public void SetLicenseType(Fusion.Api.LicenseType licenseType){

	}

	/**
	 * [StrongNameIdentityPermission(SecurityAction.LinkDemand,
	 * PublicKey="0024000004800000940000000602000000240000525341310004000001000100F1BAE
	 * 66E82CA55D1B447D951D7578E442932C932FB45F447CB9BFC7ABDB05FA47E4F76EE64A3761EE555E
	 * 0017B23AC2B53FAB15375062A632B99A177DFE2B94C514CB267E744596CF3EC201E5B2FA6B29F55A
	 * ECCC4761F6C51728F550DA0613E27F25508881292F427FE7C3CCC4F8DF208EA57EA85D3539E732B8
	 * D3B0F8B379F")]
	 * 
	 * @param licenseType
	 */
	public void SetLicenseTypeInternal(Fusion.Api.LicenseType licenseType){

	}

	public ISettings SettingsService(){
		return null;
	}

	public Fusion.Api.StatisticsService StatisticsService(){
		return null;
	}

	public Fusion.Api.SystemExtensions SystemExtensions(){
		return null;
	}

	public ISystemFunctions SystemFunctions(){
		return null;
	}

	public ISystemInfo SystemInformation(){
		return null;
	}

	/**
	 * 
	 * @param api
	 */
	public static void SystemTableUpgrade(IFusionApi api){

	}

	public ITokenService TokenService(){
		return null;
	}

	/**
	 * 
	 * @param o
	 */
	public Object TranslateInternalObject(Object o){
		return null;
	}

	public Fusion.Api.ValueResolverService ValueResolverService(){
		return null;
	}

}