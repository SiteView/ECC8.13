package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:44
 */
public interface IAuthorizationProvider {

	/**
	 * 
	 * @param node
	 */
	public boolean Deserialize(XmlNode node);

	public boolean EditSettings();

	/**
	 * 
	 * @param ab
	 */
	public IUserInfo GetUserInfo(IAuthenticationBundle ab);

	/**
	 * 
	 * @param sUserType
	 * @param sAuthenticationID
	 * @param sAuthenticationSource
	 */
	public IUserInfo GetUserInfo(String sUserType, String sAuthenticationID, String sAuthenticationSource);

	public boolean HasSettings();

	public String Name();

}