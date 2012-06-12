package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:02
 */
public abstract class DbConnectionDef extends ConnectionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:02
	 */
	private class Tags {

		private String AdditionalDbSettings = "AdditionalDbSettings";
		private String Available = "Available";
		private String Connection = "Connection";
		private String ConnectionList = "ConnectionList";
		private String Connections = "Connections";
		private String Database = "Database";
		private String DbConnection = "DbConnection";
		private String DbSetting = "DbSetting";
		private String Encrypted = "Encrypted";
		private String Fade = "Fade";
		private String FusionPooling = "FusionPooling";
		private String Hold = "Hold";
		private String Location = "Location";
		private String Login = "Login";
		private String LoginConnection = "CONNECTION";
		private String LoginIntegrated = "INTEGRATED";
		private String Max = "Max";
		private String Method = "Method";
		private String Min = "Min";
		private String Name = "Name";
		private String Owner = "Owner";
		private String Pooling = "Pooling";
		private String Provider = "Provider";
		private String Timeout = "Timeout";
		private String Type = "Type";
		private String Value = "Value";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAdditionalDbSettings(){
			return AdditionalDbSettings;
		}

		public String getAvailable(){
			return Available;
		}

		public String getConnection(){
			return Connection;
		}

		public String getConnectionList(){
			return ConnectionList;
		}

		public String getConnections(){
			return Connections;
		}

		public String getDatabase(){
			return Database;
		}

		public String getDbConnection(){
			return DbConnection;
		}

		public String getDbSetting(){
			return DbSetting;
		}

		public String getEncrypted(){
			return Encrypted;
		}

		public String getFade(){
			return Fade;
		}

		public String getFusionPooling(){
			return FusionPooling;
		}

		public String getHold(){
			return Hold;
		}

		public String getLocation(){
			return Location;
		}

		public String getLogin(){
			return Login;
		}

		public String getLoginConnection(){
			return LoginConnection;
		}

		public String getLoginIntegrated(){
			return LoginIntegrated;
		}

		public String getMax(){
			return Max;
		}

		public String getMethod(){
			return Method;
		}

		public String getMin(){
			return Min;
		}

		public String getName(){
			return Name;
		}

		public String getOwner(){
			return Owner;
		}

		public String getPooling(){
			return Pooling;
		}

		public String getProvider(){
			return Provider;
		}

		public String getTimeout(){
			return Timeout;
		}

		public String getType(){
			return Type;
		}

		public String getValue(){
			return Value;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAdditionalDbSettings(String newVal){
			AdditionalDbSettings = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAvailable(String newVal){
			Available = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setConnection(String newVal){
			Connection = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setConnectionList(String newVal){
			ConnectionList = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setConnections(String newVal){
			Connections = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDatabase(String newVal){
			Database = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDbConnection(String newVal){
			DbConnection = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDbSetting(String newVal){
			DbSetting = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setEncrypted(String newVal){
			Encrypted = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFade(String newVal){
			Fade = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFusionPooling(String newVal){
			FusionPooling = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setHold(String newVal){
			Hold = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLocation(String newVal){
			Location = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLogin(String newVal){
			Login = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLoginConnection(String newVal){
			LoginConnection = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLoginIntegrated(String newVal){
			LoginIntegrated = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMax(String newVal){
			Max = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMethod(String newVal){
			Method = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMin(String newVal){
			Min = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setName(String newVal){
			Name = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setOwner(String newVal){
			Owner = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPooling(String newVal){
			Pooling = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setProvider(String newVal){
			Provider = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTimeout(String newVal){
			Timeout = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setType(String newVal){
			Type = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValue(String newVal){
			Value = newVal;
		}

	}

	private String Admin = "ADMIN";
	private int AdminConnection = 1;
	private String Db2IndexTablespace = "Db2IndexTablespace";
	private String Db2LobTablespace = "Db2LobTablespace";
	private String Db2TableTablespace = "Db2TableTablespace";
	private DbLoginMethod m_aLoginMethod[] = new DbLoginMethod[2];
	private String m_astrAdditionalParms[] = new string[2];
	private String m_astrConnection[] = new string[2];
	private String m_astrPassword[] = new string[2];
	private String m_astrUserId[] = new string[2];
	private boolean m_bPasswordsEncrypted = true;
	protected boolean m_bUseFusionPooling = false;
	private DatabaseEngine m_dbEngine;
	private Hashtable m_htAdditionalDbSettings = null;
	protected int m_nConnTimeout = 0;
	protected int m_nFadeTimeout = 0;
	protected int m_nHoldConnections = 0;
	protected int m_nMaxConnections = 0;
	protected int m_nMinConnections = 0;
	private DataProviders m_provider;
	private String m_strDataSource = "";
	private String m_strOwnerName = "";
	private String m_strProviderName = "";
	private String m_strServer = "";
	private int NUM_CONNECTION_TYPES = 2;
	private String User = "USER";
	private int UserConnection = 0;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public DbConnectionDef(){

	}

	public Hashtable AdditionalDbSettings(){
		return null;
	}

	/**
	 * 
	 * @param nConnectionType
	 */
	public String BuildConnectionString(int nConnectionType){
		return "";
	}

	/**
	 * 
	 * @param strProviderName
	 * @param strServer
	 * @param strDataSource
	 * @param methodLogin
	 * @param strUserId
	 * @param strPassword
	 * @param strAdditionalParms
	 */
	private String BuildConnectionString(String strProviderName, String strServer, String strDataSource, DbLoginMethod methodLogin, String strUserId, String strPassword, String strAdditionalParms){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public int ConnectionTimeout(){
		return 0;
	}

	/**
	 * 
	 * @param nConnectionType
	 */
	public static String ConnectionTypeToString(int nConnectionType){
		return "";
	}

	/**
	 * 
	 * @param defConn
	 */
	public void CopyContents(ConnectionDef defConn){

	}

	public String DataSource(){
		return "";
	}

	public DatabaseEngine DbEngine(){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public int FadeTimeout(){
		return 0;
	}

	/**
	 * 
	 * @param strName
	 */
	public String GetAdditionalDbSetting(String strName){
		return "";
	}

	/**
	 * 
	 * @param nConnectionType
	 */
	public String GetAdditionalParms(int nConnectionType){
		return "";
	}

	public String getAdmin(){
		return Admin;
	}

	public int getAdminConnection(){
		return AdminConnection;
	}

	/**
	 * 
	 * @param nConnectionType
	 */
	public String GetConnectionString(int nConnectionType){
		return "";
	}

	public String getDb2IndexTablespace(){
		return Db2IndexTablespace;
	}

	public String getDb2LobTablespace(){
		return Db2LobTablespace;
	}

	public String getDb2TableTablespace(){
		return Db2TableTablespace;
	}

	/**
	 * 
	 * @param nConnectionType
	 */
	public DbLoginMethod GetLoginMethod(int nConnectionType){
		return null;
	}

	/**
	 * 
	 * @param nConnectionType
	 */
	public String GetPassword(int nConnectionType){
		return "";
	}

	public String getUser(){
		return User;
	}

	public int getUserConnection(){
		return UserConnection;
	}

	/**
	 * 
	 * @param nConnectionType
	 */
	public String GetUserId(int nConnectionType){
		return "";
	}

	public int HoldConnections(){
		return 0;
	}

	public void LoadDataFromConnectionStrings(){

	}

	public abstract String Location();

	/**
	 * 
	 * @param typeLogin
	 */
	public static String LoginMethodToString(DbLoginMethod typeLogin){
		return "";
	}

	public int MaxConnections(){
		return 0;
	}

	public int MinConnections(){
		return 0;
	}

	public String OwnerName(){
		return "";
	}

	/**
	 * 
	 * @param conn
	 * @param strConn
	 * @param strProviderName
	 * @param strServer
	 * @param strDataSource
	 * @param methodLogin
	 * @param strUserId
	 * @param strPassword
	 * @param strAddParms
	 */
	private void ParseConnectionString(ConnectionStrings conn, String strConn, String strProviderName, String strServer, String strDataSource, DbLoginMethod methodLogin, String strUserId, String strPassword, String strAddParms){

	}

	public boolean PasswordsEncrypted(){
		return null;
	}

	public DataProviders Provider(){
		return null;
	}

	public String ProviderName(){
		return "";
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

	public String SerializeSpecificPropertyRoot(){
		return "";
	}

	public String ServerName(){
		return "";
	}

	/**
	 * 
	 * @param strName
	 * @param strValue
	 */
	public void SetAdditionalDbSetting(String strName, String strValue){

	}

	/**
	 * 
	 * @param nConnectionType
	 * @param strAddParms
	 */
	public void SetAdditionalParms(int nConnectionType, String strAddParms){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAdmin(String newVal){
		Admin = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAdminConnection(int newVal){
		AdminConnection = newVal;
	}

	protected abstract void SetConnectionPoolDefaults();

	/**
	 * 
	 * @param nConnectionType
	 * @param strConnection
	 */
	public void SetConnectionString(int nConnectionType, String strConnection){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDb2IndexTablespace(String newVal){
		Db2IndexTablespace = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDb2LobTablespace(String newVal){
		Db2LobTablespace = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDb2TableTablespace(String newVal){
		Db2TableTablespace = newVal;
	}

	/**
	 * 
	 * @param nConnectionType
	 * @param method
	 */
	public void SetLoginMethod(int nConnectionType, DbLoginMethod method){

	}

	/**
	 * 
	 * @param nConnectionType
	 * @param strPassword
	 */
	public void SetPassword(int nConnectionType, String strPassword){

	}

	/**
	 * 
	 * @param bUseFusionPooling
	 * @param nMinConnections
	 * @param nMaxConnections
	 * @param nHoldConnections
	 * @param nFadeTimeout
	 * @param nConnectionTimeout
	 */
	public void SetPoolingOptions(boolean bUseFusionPooling, int nMinConnections, int nMaxConnections, int nHoldConnections, int nFadeTimeout, int nConnectionTimeout){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUser(String newVal){
		User = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUserConnection(int newVal){
		UserConnection = newVal;
	}

	/**
	 * 
	 * @param nConnectionType
	 * @param strUserId
	 */
	public void SetUserId(int nConnectionType, String strUserId){

	}

	/**
	 * 
	 * @param strConnectionType
	 */
	public static int StringToConnectionType(String strConnectionType){
		return 0;
	}

	/**
	 * 
	 * @param strLoginMethod
	 */
	public static DbLoginMethod StringToLoginMethod(String strLoginMethod){
		return null;
	}

	public boolean UseFusionPooling(){
		return null;
	}

}