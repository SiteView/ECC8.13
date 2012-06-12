package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:16
 */
public class ServerConnectionDef extends ConnectionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:16
	 */
	private class Tags {

		private String BypassOnLocal = "BypassOnLocal";
		private String CallBack = "CallBack";
		private String CompressionLevel = "CompressionLevel";
		private String Description = "Description";
		private String Port = "Port";
		private String ProxyServerAddress = "ProxyServerAddress";
		private String ProxyServerDomain = "ProxyServerDomain";
		private String ProxyServerPassword = "ProxyServerPassword";
		private String ProxyServerPort = "ProxyServerPort";
		private String ProxyServerUsername = "ProxyServerUsername";
		private String ServerConnection = "ServerConnection";
		private String SpecifyCredentials = "SpecifyCredentials";
		private String URI = "URI";
		private String UseProxyServer = "UseProxyServer";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getBypassOnLocal(){
			return BypassOnLocal;
		}

		public String getCallBack(){
			return CallBack;
		}

		public String getCompressionLevel(){
			return CompressionLevel;
		}

		public String getDescription(){
			return Description;
		}

		public String getPort(){
			return Port;
		}

		public String getProxyServerAddress(){
			return ProxyServerAddress;
		}

		public String getProxyServerDomain(){
			return ProxyServerDomain;
		}

		public String getProxyServerPassword(){
			return ProxyServerPassword;
		}

		public String getProxyServerPort(){
			return ProxyServerPort;
		}

		public String getProxyServerUsername(){
			return ProxyServerUsername;
		}

		public String getServerConnection(){
			return ServerConnection;
		}

		public String getSpecifyCredentials(){
			return SpecifyCredentials;
		}

		public String getURI(){
			return URI;
		}

		public String getUseProxyServer(){
			return UseProxyServer;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBypassOnLocal(String newVal){
			BypassOnLocal = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCallBack(String newVal){
			CallBack = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCompressionLevel(String newVal){
			CompressionLevel = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDescription(String newVal){
			Description = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPort(String newVal){
			Port = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setProxyServerAddress(String newVal){
			ProxyServerAddress = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setProxyServerDomain(String newVal){
			ProxyServerDomain = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setProxyServerPassword(String newVal){
			ProxyServerPassword = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setProxyServerPort(String newVal){
			ProxyServerPort = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setProxyServerUsername(String newVal){
			ProxyServerUsername = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setServerConnection(String newVal){
			ServerConnection = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSpecifyCredentials(String newVal){
			SpecifyCredentials = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setURI(String newVal){
			URI = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setUseProxyServer(String newVal){
			UseProxyServer = newVal;
		}

	}

	private CompressionLevel m_compressionLevel = CompressionLevel.BestCompression;
	private int m_nCallBackPort = 0;
	private ProxyServerInfo m_proxyInfo = new ProxyServerInfo();
	private String m_strUri = "";

	public ServerConnectionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public int CallBackPort(){
		return 0;
	}

	public static String ClassName(){
		return "";
	}

	public IDefinition Clone(){
		return null;
	}

	public CompressionLevel ConnectionCompressionLevel(){
		return null;
	}

	public ConnectionDefType ConnectionType(){
		return null;
	}

	/**
	 * 
	 * @param defConn
	 */
	public void CopyContents(ConnectionDef defConn){

	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	/**
	 * 
	 * @param serial
	 * @param defParent
	 */
	public static SerializableDef DeserializeCreate(DefSerializer serial, SerializableDef defParent){
		return null;
	}

	public ProxyServerInfo ProxyInfo(){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public DefSerializer Serialize(DefSerializer serial){
		return null;
	}

	public String SerializeClassName(){
		return "";
	}

	public String Uri(){
		return "";
	}

}