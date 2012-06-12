package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:43
 */
public interface IAuthenticationBundle {

	public String ApplicationTypeName();

	public boolean AttemptExternalAuthentication();

	public String AuthenticationId();

	public Fusion.AuthenticationSource AuthenticationSource();

	public Fusion.AuthorizationSource AuthorizationSource();

	public String EncryptedPassword();

	public String Password();

	public String PreservedSessionId();

	public String UserType();

}