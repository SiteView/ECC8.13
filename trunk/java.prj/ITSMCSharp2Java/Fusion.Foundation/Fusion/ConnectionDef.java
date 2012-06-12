package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:53
 */
public abstract class ConnectionDef extends DefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:53
	 */
	private class Tags {

		private String CacheLevel = "Level";
		private String DefinitionCache = "DefinitionCache";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getCacheLevel(){
			return CacheLevel;
		}

		public String getDefinitionCache(){
			return DefinitionCache;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCacheLevel(String newVal){
			CacheLevel = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDefinitionCache(String newVal){
			DefinitionCache = newVal;
		}

	}

	private String DbConnectionDef = "DbConnectionDef";
	protected String DbExternalTable = "ExternalTable";
	protected String DbInternal = "Internal";
	protected String DbLocation = "Location";
	private DefinitionCacheLevel m_cacheLevel = DefinitionCacheLevel.PerspectiveOnly;
	private String ServerConnectionDef = "ServerConnectionDef";

	public ConnectionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public static String ClassName(){
		return "";
	}

	public IDefinition CloneForEdit(){
		return null;
	}

	public ConnectionDefGroup ConnectionGroup(){
		return null;
	}

	public abstract ConnectionDefType ConnectionType();

	/**
	 * 
	 * @param defConn
	 */
	public void CopyContents(ConnectionDef defConn){

	}

	/**
	 * 
	 * @param type
	 */
	public static ConnectionDef Create(ConnectionDefType type){
		return null;
	}

	/**
	 * 
	 * @param xeConnectionDef
	 */
	public static ConnectionDef Create(XmlElement xeConnectionDef){
		return null;
	}

	public boolean DatabaseConnection(){
		return null;
	}

	public DefinitionCacheLevel DefinitionCache(){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public String DisplayName(){
		return "";
	}

	public boolean ExternalDatabaseConnection(){
		return null;
	}

	public boolean InternalDatabaseConnection(){
		return null;
	}

	/**
	 * 
	 * @param strConnectionName
	 */
	public static String ParseDisplayName(String strConnectionName){
		return "";
	}

	/**
	 * 
	 * @param connGroup
	 * @param strName
	 */
	public void ParseName(ConnectionDefGroup connGroup, String strName){

	}

	/**
	 * 
	 * @param strConnectionName
	 * @param connGroup
	 * @param strName
	 */
	public static void ParseName(String strConnectionName, ConnectionDefGroup connGroup, String strName){

	}

	/**
	 * 
	 * @param serial
	 */
	public DefSerializer Serialize(DefSerializer serial){
		return null;
	}

	public boolean ServerConnection(){
		return null;
	}

	/**
	 * 
	 * @param connGroup
	 * @param strName
	 */
	public String SetName(ConnectionDefGroup connGroup, String strName){
		return "";
	}

	public String ToString(){
		return "";
	}

}