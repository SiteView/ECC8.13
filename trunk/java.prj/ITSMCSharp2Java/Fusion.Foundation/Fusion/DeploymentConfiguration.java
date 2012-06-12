package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:15
 */
public class DeploymentConfiguration {

	private boolean m_blnNoTouchDeploy;
	private Fusion.AutoConnectConfiguration m_cfgAutoConnect;
	private static DeploymentConfiguration m_cfgDeploymentConfigInstance;
	private Fusion.PreLoadConfiguration m_cfgPreLoad;
	private ServerConnectionDef m_srvConnDef;

	public DeploymentConfiguration(){

	}

	public void finalize() throws Throwable {

	}

	public Fusion.AutoConnectConfiguration AutoConnectConfiguration(){
		return null;
	}

	private void CreateDeployedServerDef(){

	}

	public ServerConnectionDef DeployedConnection(){
		return null;
	}

	private static void InitializeInstance(){

	}

	public static DeploymentConfiguration Instance(){
		return null;
	}

	public boolean NoTouchDeploy(){
		return null;
	}

	public Fusion.PreLoadConfiguration PreLoadConfiguration(){
		return null;
	}

}