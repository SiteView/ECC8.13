package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:56
 */
public interface ISettings {

	public void ClearSettingsCache();

	/**
	 * 
	 * @param strSettingId
	 */
	public void Delete(String strSettingId);

	/**
	 * 
	 * @param scope
	 * @param strScopeOwner
	 */
	public void Delete(Scope scope, String strScopeOwner);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public void Delete(String strSettingId, Scope scope, String strScopeOwner);

	public IDisplaySettings DisplaySettings();

	public void Flush();

	/**
	 * 
	 * @param strSettingId
	 */
	public void Flush(String strSettingId);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public void Flush(String strSettingId, Scope scope, String strScopeOwner);

	public void FlushAllGlobalSettings();

	public int GetCurrentSystemVersion();

	/**
	 * 
	 * @param strSettingId
	 */
	public boolean GetSettingAsBool(String strSettingId);

	/**
	 * 
	 * @param strSettingId
	 * @param bDefault
	 */
	public boolean GetSettingAsBool(String strSettingId, boolean bDefault);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public boolean GetSettingAsBoolForScope(String strSettingId, Scope scope, String strScopeOwner);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param bDefault
	 */
	public boolean GetSettingAsBoolForScope(String strSettingId, Scope scope, String strScopeOwner, boolean bDefault);

	/**
	 * 
	 * @param strSettingId
	 */
	public DateTime GetSettingAsDateTime(String strSettingId);

	/**
	 * 
	 * @param strSettingId
	 * @param dtDefault
	 */
	public DateTime GetSettingAsDateTime(String strSettingId, DateTime dtDefault);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public DateTime GetSettingAsDateTimeForScope(String strSettingId, Scope scope, String strScopeOwner);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param dtDefault
	 */
	public DateTime GetSettingAsDateTimeForScope(String strSettingId, Scope scope, String strScopeOwner, DateTime dtDefault);

	/**
	 * 
	 * @param strSettingId
	 */
	public decimal GetSettingAsDecimal(String strSettingId);

	/**
	 * 
	 * @param strSettingId
	 * @param dDefault
	 */
	public decimal GetSettingAsDecimal(String strSettingId, decimal dDefault);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public decimal GetSettingAsDecimalForScope(String strSettingId, Scope scope, String strScopeOwner);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param dDefault
	 */
	public decimal GetSettingAsDecimalForScope(String strSettingId, Scope scope, String strScopeOwner, decimal dDefault);

	/**
	 * 
	 * @param strSettingId
	 */
	public int GetSettingAsInt(String strSettingId);

	/**
	 * 
	 * @param strSettingId
	 * @param nDefault
	 */
	public int GetSettingAsInt(String strSettingId, int nDefault);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public int GetSettingAsIntForScope(String strSettingId, Scope scope, String strScopeOwner);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param nDefault
	 */
	public int GetSettingAsIntForScope(String strSettingId, Scope scope, String strScopeOwner, int nDefault);

	/**
	 * 
	 * @param strSettingId
	 */
	public String GetSettingAsString(String strSettingId);

	/**
	 * 
	 * @param strSettingId
	 * @param strDefault
	 */
	public String GetSettingAsString(String strSettingId, String strDefault);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public String GetSettingAsStringForScope(String strSettingId, Scope scope, String strScopeOwner);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param strDefault
	 */
	public String GetSettingAsStringForScope(String strSettingId, Scope scope, String strScopeOwner, String strDefault);

	/**
	 * 
	 * @param strSettingId
	 */
	public string[] GetSettingNames(String strSettingId);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public string[] GetSettingNamesForScope(String strSettingId, Scope scope, String strScopeOwner);

	/**
	 * 
	 * @param strSettingId
	 */
	public ISettings GetSettings(String strSettingId);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public ISettings GetSettingsForScope(String strSettingId, Scope scope, String strScopeOwner);

	public boolean LoadGlobalSettings();

	/**
	 * 
	 * @param strSettingId
	 */
	public void LoadSettingForAllScopes(String strSettingId);

	public boolean LoadUserSettings();

	public IMfu Mfu();

	public IMru Mru();

	public IPromptSettings PromptSettings();

	/**
	 * 
	 * @param strSettingId
	 */
	public void Reset(String strSettingId);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 */
	public void Reset(String strSettingId, Scope scope, String strScopeOwner);

	/**
	 * 
	 * @param strSettingId
	 * @param bValue
	 */
	public void SetSetting(String strSettingId, boolean bValue);

	/**
	 * 
	 * @param strSettingId
	 * @param dtValue
	 */
	public void SetSetting(String strSettingId, DateTime dtValue);

	/**
	 * 
	 * @param strSettingId
	 * @param dValue
	 */
	public void SetSetting(String strSettingId, decimal dValue);

	/**
	 * 
	 * @param strSettingId
	 * @param nValue
	 */
	public void SetSetting(String strSettingId, int nValue);

	/**
	 * 
	 * @param strSettingId
	 * @param strValue
	 */
	public void SetSetting(String strSettingId, String strValue);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param bValue
	 */
	public void SetSettingForScope(String strSettingId, Scope scope, String strScopeOwner, boolean bValue);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param dtValue
	 */
	public void SetSettingForScope(String strSettingId, Scope scope, String strScopeOwner, DateTime dtValue);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param dValue
	 */
	public void SetSettingForScope(String strSettingId, Scope scope, String strScopeOwner, decimal dValue);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param nValue
	 */
	public void SetSettingForScope(String strSettingId, Scope scope, String strScopeOwner, int nValue);

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param strValue
	 */
	public void SetSettingForScope(String strSettingId, Scope scope, String strScopeOwner, String strValue);

}