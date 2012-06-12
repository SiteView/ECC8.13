package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:49
 */
public class UserSessionManagement {

	private int m_intExpiredSessionScavengeInterval = 30;
	private int m_intSessionExpiration = 120;

	public UserSessionManagement(){

	}

	public void finalize() throws Throwable {

	}

	public static UserSessionManagement CreateDefaultInstance(){
		return null;
	}

	public int ExpiredSessionScavengeInterval(){
		return 0;
	}

	public int SessionExpiration(){
		return 0;
	}

}