package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:43
 */
public interface IAuthenticationProvider {

	/**
	 * 
	 * @param ab
	 */
	public boolean AreCredentialsValid(IAuthenticationBundle ab);

	public String AuthenticatedUsername();

	public AuthenticationProviderDef Def();

	public boolean EditSettings();

	public boolean HasSettings();

	public String Name();

	public boolean ProvidesAuthenticatedUsername();

}