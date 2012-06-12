package Fusion.Api;

import java.math.BigDecimal;
import java.util.Date;


/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:34
 */
public class SettingsService extends ISettings {

	private ISettings m_iSettingsService = null;

	public SettingsService(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param iSettingsService
	 */
	public SettingsService(ISettings iSettingsService){

	}

	public void ClearSettingsCache(){

	}

	/**
	 * 
	 * @param strSettingId
	 */
	public void Delete(String strSettingId){

	}

	/**
	 * 
	 * @param scope
	 * @param strScopeOwner
	 */
	public void Delete(Scope scope, String strScopeOwner){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public void Delete(String strSettingId, Scope scope, String strScopeOwner){

	}

	public IDisplaySettings DisplaySettings(){
		return null;
	}

	public void Flush(){

	}

	/**
	 * 
	 * @param strSettingId
	 */
	public void Flush(String strSettingId){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public void Flush(String strSettingId, Scope scope, String strScopeOwner){

	}

	public void FlushAllGlobalSettings(){

	}

	public int GetCurrentSystemVersion(){
		return 0;
	}

	/**
	 * 
	 * @param strSettingId
	 */
	public boolean GetSettingAsboolean(String strSettingId){
		return false;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param bDefault
	 */
	public boolean GetSettingAsboolean(String strSettingId, boolean bDefault){
		return false;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public boolean GetSettingAsbooleanForScope(String strSettingId, Scope scope, String strScopeOwner){
		return false;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param bDefault
	 */
	public boolean GetSettingAsbooleanForScope(String strSettingId, Scope scope, String strScopeOwner, boolean bDefault){
		return false;
	}

	/**
	 * 
	 * @param strSettingId
	 */
	public Date GetSettingAsDateTime(String strSettingId){
		return null;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param dtDefault
	 */
	public Date GetSettingAsDateTime(String strSettingId, Date dtDefault){
		return null;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public Date GetSettingAsDateTimeForScope(String strSettingId, Scope scope, String strScopeOwner){
		return null;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param dtDefault
	 */
	public Date GetSettingAsDateTimeForScope(String strSettingId, Scope scope, String strScopeOwner, Date dtDefault){
		return null;
	}

	/**
	 * 
	 * @param strSettingId
	 */
	public BigDecimal GetSettingAsDecimal(String strSettingId){
		return null;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param dDefault
	 */
	public BigDecimal GetSettingAsDecimal(String strSettingId, BigDecimal dDefault){
		return null;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public BigDecimal GetSettingAsDecimalForScope(String strSettingId, Scope scope, String strScopeOwner){
		return null;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param dDefault
	 */
	public BigDecimal GetSettingAsDecimalForScope(String strSettingId, Scope scope, String strScopeOwner, BigDecimal dDefault){
		return null;
	}

	/**
	 * 
	 * @param strSettingId
	 */
	public int GetSettingAsInt(String strSettingId){
		return 0;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param nDefault
	 */
	public int GetSettingAsInt(String strSettingId, int nDefault){
		return 0;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public int GetSettingAsIntForScope(String strSettingId, Scope scope, String strScopeOwner){
		return 0;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param nDefault
	 */
	public int GetSettingAsIntForScope(String strSettingId, Scope scope, String strScopeOwner, int nDefault){
		return 0;
	}

	/**
	 * 
	 * @param strSettingId
	 */
	public String GetSettingAsString(String strSettingId){
		return "";
	}

	/**
	 * 
	 * @param strSettingId
	 * @param strDefault
	 */
	public String GetSettingAsString(String strSettingId, String strDefault){
		return "";
	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public String GetSettingAsStringForScope(String strSettingId, Scope scope, String strScopeOwner){
		return "";
	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param strDefault
	 */
	public String GetSettingAsStringForScope(String strSettingId, Scope scope, String strScopeOwner, String strDefault){
		return "";
	}

	/**
	 * 
	 * @param strSettingId
	 */
	public String[] GetSettingNames(String strSettingId){
		return null;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public String[] GetSettingNamesForScope(String strSettingId, Scope scope, String strScopeOwner){
		return "";
	}

	/**
	 * 
	 * @param strSettingId
	 */
	public ISettings GetSettings(String strSettingId){
		return null;
	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public ISettings GetSettingsForScope(String strSettingId, Scope scope, String strScopeOwner){
		return null;
	}

	public boolean LoadGlobalSettings(){
		return false;
	}

	/**
	 * 
	 * @param strSettingId
	 */
	public void LoadSettingForAllScopes(String strSettingId){

	}

	public boolean LoadUserSettings(){
		return false;
	}

	public IMfu Mfu(){
		return null;
	}

	public IMru Mru(){
		return null;
	}

	/**
	 * 
	 * @param args
	 */
	protected void OnSettingChanged(SettingChangedEventArgs args){

	}

	public IPromptSettings PromptSettings(){
		return null;
	}

	/**
	 * 
	 * @param strSettingId
	 */
	public void Reset(String strSettingId){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public void Reset(String strSettingId, Scope scope, String strScopeOwner){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param bValue
	 */
	public void SetSetting(String strSettingId, boolean bValue){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param dtValue
	 */
	public void SetSetting(String strSettingId, Date dtValue){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param dValue
	 */
	public void SetSetting(String strSettingId, BigDecimal dValue){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param nValue
	 */
	public void SetSetting(String strSettingId, int nValue){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param strValue
	 */
	public void SetSetting(String strSettingId, String strValue){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param bValue
	 */
	public void SetSettingForScope(String strSettingId, Scope scope, String strScopeOwner, boolean bValue){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param dtValue
	 */
	public void SetSettingForScope(String strSettingId, Scope scope, String strScopeOwner, Date dtValue){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param dValue
	 */
	public void SetSettingForScope(String strSettingId, Scope scope, String strScopeOwner, BigDecimal dValue){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param nValue
	 */
	public void SetSettingForScope(String strSettingId, Scope scope, String strScopeOwner, int nValue){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param strValue
	 */
	public void SetSettingForScope(String strSettingId, Scope scope, String strScopeOwner, String strValue){

	}

	public SettingChangedHandler SettingChanged(){
		return null;
	}

}