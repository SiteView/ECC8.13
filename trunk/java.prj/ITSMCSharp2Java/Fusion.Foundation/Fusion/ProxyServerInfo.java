package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:35
 */
public class ProxyServerInfo {

	private boolean m_bBypassOnLocal = false;
	private boolean m_bSpecifyCredentials = false;
	private boolean m_bUseProxyServer = false;
	private int m_intPort = 0;
	private String m_strAddress = "";
	private String m_strDomain = "";
	private String m_strPassword = "";
	private String m_strUsername = "";

	public ProxyServerInfo(){

	}

	public void finalize() throws Throwable {

	}

	public String Address(){
		return "";
	}

	public boolean BypassOnLocal(){
		return null;
	}

	public ProxyServerInfo Clone(){
		return null;
	}

	public String Domain(){
		return "";
	}

	public String Password(){
		return "";
	}

	public int Port(){
		return 0;
	}

	public boolean SpecifyCredentials(){
		return null;
	}

	public boolean UseProxyServer(){
		return null;
	}

	public String Username(){
		return "";
	}

}