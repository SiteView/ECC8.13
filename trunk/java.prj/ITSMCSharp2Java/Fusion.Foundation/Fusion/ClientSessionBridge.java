package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:51
 */
public class ClientSessionBridge {

	private static ClientSessionBridge m_bridge = new ClientSessionBridge();
	private IReconnectBroker m_broker;



	public void finalize() throws Throwable {

	}

	private ClientSessionBridge(){

	}

	public static ClientSessionBridge Instance(){
		return null;
	}

	public boolean Reconnect(){
		return null;
	}

	/**
	 * 
	 * @param broker
	 */
	public void RegisterBroker(IReconnectBroker broker){

	}

}