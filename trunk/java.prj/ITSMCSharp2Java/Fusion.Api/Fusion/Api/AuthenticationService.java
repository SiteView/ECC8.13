package Fusion.Api;

import java.util.List;
import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:27
 */
public class AuthenticationService extends IAuthenticationService {

	private String ACCESSUSERS = "AccessUsers";
	private String INTERNAL_MODULESECURITY = "Fusion.Security.System";
	private IOrchestrator m_Orch = null;

	public AuthenticationService(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param orch
	 */
	public AuthenticationService(IOrchestrator orch){

	}

	public Map AuthorizationProviders(){
		return null;
	}

	/**
	 * 
	 * @param strUserType
	 * @param strLoginId
	 * @param strOldPassword
	 * @param strNewPassword
	 */
	public void ChangePassword(String strUserType, String strLoginId, String strOldPassword, String strNewPassword){

	}

	/**
	 * 
	 * @param strUserType
	 * @param strLoginId
	 */
	public User CreateUser(String strUserType, String strLoginId){
		return null;
	}

	/**
	 * 
	 * @param strUserType
	 * @param authSource
	 */
	public IUserInfo CreateUserInfo(String strUserType, AuthenticationSource authSource){
		return null;
	}

	public String CurrentAuthenticationId(){
		return "";
	}

	public AuthenticationSource CurrentAuthenticationSource(){
		return null;
	}

	public String CurrentBusUnitDefId(){
		return "";
	}

	public String[] CurrentLicenseList(){
		return "";
	}

	public String CurrentLoginId(){
		return "";
	}

	public String CurrentSecurityGroup(){
		return "";
	}

	public String CurrentSecurityGroupId(){
		return "";
	}

	public String CurrentUserBusUnit(){
		return "";
	}

	public String CurrentUserEmailAddress(){
		return "";
	}

	public String CurrentUserName(){
		return "";
	}

	public String CurrentUserRecId(){
		return "";
	}

	public String CurrentUserStatus(){
		return "";
	}

	public String CurrentUserTeam(){
		return "";
	}

	public String CurrentUserType(){
		return "";
	}

	public String DefaultUserName(){
		return "";
	}

	public String DefaultUserRecId(){
		return "";
	}

	public String DefaultUserTeam(){
		return "";
	}

	public String DefaultUserType(){
		return "";
	}

	/**
	 * 
	 * @param user
	 * @param bDelete
	 */
	public void DeleteUser(User user, boolean bDelete){

	}

	public List GetAuthenticationProviderNames(){
		return null;
	}

	public List GetAuthenticationProviders(){
		return null;
	}

	public BusUnitInfo[] GetBusUnitList(){
		return null;
	}

	/**
	 * 
	 * @param strGroupId
	 */
	public DataSet GetLoginIdsByGroupId(String strGroupId){
		return null;
	}

	/**
	 * 
	 * @param strUserType
	 * @param strGroupId
	 */
	public String[] GetLoginIdsByGroupId(String strUserType, String strGroupId){
		return null;
	}

	/**
	 * 
	 * @param strUserType
	 */
	public String[] GetLoginIdsByUserType(String strUserType){
		return null;
	}

	/**
	 * 
	 * @param strUserType
	 * @param strLoginId
	 */
	public User GetUser(String strUserType, String strLoginId){
		return null;
	}

	/**
	 * 
	 * @param strLoginId
	 */
	public String GetUserStatusId(String strLoginId){
		return "";
	}

	/**
	 * 
	 * @param strUserType
	 */
	public List GetUserStatusList(String strUserType){
		return null;
	}

	/**
	 * 
	 * @param user
	 */
	public User SaveUser(User user){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 * @param loginId
	 */
	public void SetCurrentUserNameOnBusOb(Object busOb, String loginId){

	}

	/**
	 * 
	 * @param provider
	 */
	public void SetOrchestrator(IAuthorizationProvider provider){

	}

	/**
	 * 
	 * @param sessionData
	 */
	public void SetUserSessionData(SessionData sessionData){

	}

	/**
	 * 
	 * @param strSessionId
	 * @param sessionData
	 */
	public void SetUserSessionData(String strSessionId, SessionData sessionData){

	}

	/**
	 * 
	 * @param strStatusId
	 */
	public void SetUserStatus(String strStatusId){

	}

	/**
	 * 
	 * @param strSessionId
	 * @param strStatusId
	 */
	public void SetUserStatus(String strSessionId, String strStatusId){

	}

	/**
	 * 
	 * @param dtm
	 */
	public IUserInfo[] SynchronizeSessions(DateTime dtm){
		return null;
	}

}