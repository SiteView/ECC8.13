package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:44
 */
public interface IAuthenticationService {

	public Map AuthorizationProviders();

	/**
	 * 
	 * @param strUserType
	 * @param strLoginId
	 * @param strOldPassword
	 * @param strNewPassword
	 */
	public void ChangePassword(String strUserType, String strLoginId, String strOldPassword, String strNewPassword);

	/**
	 * 
	 * @param strUserType
	 * @param strLoginId
	 */
	public User CreateUser(String strUserType, String strLoginId);

	/**
	 * 
	 * @param strUserType
	 * @param authSource
	 */
	public IUserInfo CreateUserInfo(String strUserType, AuthenticationSource authSource);

	public String CurrentAuthenticationId();

	public AuthenticationSource CurrentAuthenticationSource();

	public String CurrentBusUnitDefId();

	public string[] CurrentLicenseList();

	public String CurrentLoginId();

	public String CurrentSecurityGroup();

	public String CurrentSecurityGroupId();

	public String CurrentUserBusUnit();

	public String CurrentUserEmailAddress();

	public String CurrentUserName();

	public String CurrentUserRecId();

	public String CurrentUserStatus();

	public String CurrentUserTeam();

	public String CurrentUserType();

	public String DefaultUserName();

	public String DefaultUserRecId();

	public String DefaultUserTeam();

	public String DefaultUserType();

	/**
	 * 
	 * @param user
	 * @param bDelete
	 */
	public void DeleteUser(User user, boolean bDelete);

	public List GetAuthenticationProviderNames();

	public List GetAuthenticationProviders();

	public BusUnitInfo[] GetBusUnitList();

	/**
	 * 
	 * @param strGroupId
	 */
	public DataSet GetLoginIdsByGroupId(String strGroupId);

	/**
	 * 
	 * @param strUserType
	 * @param strGroupId
	 */
	public string[] GetLoginIdsByGroupId(String strUserType, String strGroupId);

	/**
	 * 
	 * @param strUserType
	 */
	public string[] GetLoginIdsByUserType(String strUserType);

	/**
	 * 
	 * @param strUserType
	 * @param strLoginId
	 */
	public User GetUser(String strUserType, String strLoginId);

	/**
	 * 
	 * @param strLoginId
	 */
	public String GetUserStatusId(String strLoginId);

	/**
	 * 
	 * @param strUserType
	 */
	public List GetUserStatusList(String strUserType);

	/**
	 * 
	 * @param user
	 */
	public User SaveUser(User user);

	/**
	 * 
	 * @param busOb
	 * @param loginId
	 */
	public void SetCurrentUserNameOnBusOb(Object busOb, String loginId);

	/**
	 * 
	 * @param authProvider
	 */
	public void SetOrchestrator(IAuthorizationProvider authProvider);

	/**
	 * 
	 * @param sessionData
	 */
	public void SetUserSessionData(SessionData sessionData);

	/**
	 * 
	 * @param strSessionId
	 * @param sessionData
	 */
	public void SetUserSessionData(String strSessionId, SessionData sessionData);

	/**
	 * 
	 * @param strStatusId
	 */
	public void SetUserStatus(String strStatusId);

	/**
	 * 
	 * @param strSessionId
	 * @param strStatusId
	 */
	public void SetUserStatus(String strSessionId, String strStatusId);

	/**
	 * 
	 * @param dtmExpiration
	 */
	public IUserInfo[] SynchronizeSessions(DateTime dtmExpiration);

}