package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:54
 */
public interface ISystemInfo {

	public String ConnectionDisplayName();

	public String ConnectionName();

	public String CurrentLoginId();

	public String CurrentUserName();

	public String LicenseName();

	public String SerialNumber();

	public String Version();

	public String VerticalName();

	public String VerticalVersion();

}