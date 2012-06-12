package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:50
 */
public interface IFusionApi {

	public IAlertNotificationService AlertNotificationService();

	public IAdr ApplicationDefinitionRepository();

	/**
	 * 
	 * @param strToken
	 */
	public boolean Attach(String strToken);

	public boolean Attached();

	public Fusion.Api.AttachmentService AttachmentService();

	public IAuthenticationService AuthenticationService();

	public IDefinitions BusObDefinitions();

	public IBusObEventPublisher BusObEventPublisher();

	public IBusinessObjectService BusObService();

	public ILinkObjects CalendarClientService();

	/**
	 * 
	 * @param strConnectionName
	 */
	public boolean CheckConnectionName(String strConnectionName);

	public boolean ConfirmTwoTierMode();

	/**
	 * 
	 * @param connectionName
	 */
	public void Connect(String connectionName);

	/**
	 * 
	 * @param connectionName
	 * @param credentials
	 */
	public void Connect(String connectionName, ICredentials credentials);

	public EventHandler ConnectChanged();

	public boolean Connected();

	public String ConnectionName();

	public ICounterService CounterService();

	/**
	 * 
	 * @param connectionName
	 * @param useUnicode
	 * @param bForceCreation
	 */
	public void CreateAndConnect(String connectionName, boolean useUnicode, boolean bForceCreation);

	public IDataStoreService DataStoreService();

	public String Detach();

	/**
	 * 
	 * @param bPreserveSessionId
	 */
	public String Detach(boolean bPreserveSessionId);

	public void Disconnect();

	public Fusion.Api.ExportImportManager ExportImportManager();

	public IAuthenticationBundle GetAuthenticationBundle();

	public List GetUserTypes();

	public Fusion.Api.InteractionHandler InteractionHandler();

	public Fusion.Api.LicenseService LicenseService();

	public Fusion.Api.LicenseType LicenseType();

	public DefinitionLibrary LiveDefinitionLibrary();

	public boolean LoggedIn();

	/**
	 * 
	 * @param authentication
	 */
	public boolean Login(IAuthenticationBundle authentication);

	public void Logout();

	/**
	 * 
	 * @param modifiedUsername
	 */
	public void LogoutWeb(String modifiedUsername);

	public ILinkObjects MailClientService();

	public Fusion.Api.MailService MailService();

	public IMessageService MessageService();

	public IModuleManager ModuleManager();

	public INotifier Notifier();

	public IPresentation Presentation();

	public Fusion.ReportLibrary ReportLibrary();

	/**
	 * 
	 * @param defLib
	 */
	public void ReregisterAllExternalConnections(DefinitionLibrary defLib);

	public IResources Resources();

	public Fusion.Api.RoleManager RoleManager();

	public ISecurity SecurityService();

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
	public void SetLicenseType(Fusion.Api.LicenseType licenseType);

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
	public void SetLicenseTypeInternal(Fusion.Api.LicenseType licenseType);

	public ISettings SettingsService();

	public Fusion.Api.StatisticsService StatisticsService();

	public Fusion.Api.SystemExtensions SystemExtensions();

	public ISystemFunctions SystemFunctions();

	public ISystemInfo SystemInformation();

	public ITokenService TokenService();

	/**
	 * 
	 * @param o
	 */
	public Object TranslateInternalObject(Object o);

	public Fusion.Api.ValueResolverService ValueResolverService();

}