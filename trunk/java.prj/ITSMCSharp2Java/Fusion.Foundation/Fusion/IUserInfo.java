package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:59
 */
public interface IUserInfo {

	public String AuthenticationId();

	public Fusion.AuthenticationSource AuthenticationSource();

	public String BusUnitDefId();

	public DateTime LastAccess();

	public String LoginId();

	public String Password();

	public boolean PasswordRequired();

	public String SessionToken();

	public String StatusId();

	public boolean TrackPresence();

}