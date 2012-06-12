package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:53
 */
public abstract class ConnectionDefManager implements IConnectionDefManager {

	private String ConnectionDefaultsRegKey = "Connection";
	private String DefaultDatabaseRegValue = "Default";
	private String FusionDefaultConnection = "FusionConnection";
	private static boolean ServerConnectionMode = false;

	public ConnectionDefManager(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param connDef
	 */
	public abstract void AddConnectionDef(ConnectionDef connDef);

	/**
	 * 
	 * @param grp
	 */
	public abstract boolean AreConnectionsLoadedForGroup(ConnectionDefGroup grp);

	/**
	 * 
	 * @param connGroup
	 * @param collConnections
	 */
	protected XmlDocument BuildXml(ConnectionDefGroup connGroup, List collConnections){
		return null;
	}

	/**
	 * 
	 * @param grp
	 */
	public abstract List ConnectionsForGroup(ConnectionDefGroup grp);

	/**
	 * 
	 * @param type
	 * @param grp
	 */
	public ConnectionDef CreateNewConnectionDef(ConnectionDefType type, ConnectionDefGroup grp){
		return null;
	}

	/**
	 * 
	 * @param connDef
	 */
	public abstract void DeleteConnectionDef(ConnectionDef connDef);

	/**
	 * 
	 * @param connDef
	 * @param alConnections
	 */
	protected boolean DeleteConnectionDef(ConnectionDef connDef, ArrayList alConnections){
		return null;
	}

	/**
	 * 
	 * @param strConnectionName
	 */
	public abstract ConnectionDef GetConnectionDef(String strConnectionName);

	public ConnectionDef GetDefaultDatabase(){
		return null;
	}

	public String GetDefaultDatabaseName(){
		return "";
	}

	public boolean getServerConnectionMode(){
		return ServerConnectionMode;
	}

	/**
	 * 
	 * @param connDef
	 */
	public static boolean IsConnectionNameValid(ConnectionDef connDef){
		return null;
	}

	/**
	 * 
	 * @param xmlConnectionInfo
	 */
	protected List LoadConnectionDefs(XmlDocument xmlConnectionInfo){
		return null;
	}

	/**
	 * 
	 * @param grp
	 */
	public abstract void LoadConnectionsForGroup(ConnectionDefGroup grp);

	/**
	 * 
	 * @param grp
	 */
	public abstract void LoadConnectionsForGroupIfNeeded(ConnectionDefGroup grp);

	/**
	 * 
	 * @param collConnections
	 * @param strConnectionName
	 * @param bWithoutGroup
	 */
	protected ConnectionDef LookupConnection(List collConnections, String strConnectionName, boolean bWithoutGroup){
		return null;
	}

	/**
	 * 
	 * @param grp
	 */
	public abstract void ReloadConnectionsForGroup(ConnectionDefGroup grp);

	public abstract void SaveConnectionDefs();

	/**
	 * 
	 * @param strDefault
	 */
	public void SetDefaultDatabase(String strDefault){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setServerConnectionMode(boolean newVal){
		ServerConnectionMode = newVal;
	}

	/**
	 * 
	 * @param grp
	 */
	public abstract boolean SupportsConnectionsForGroup(ConnectionDefGroup grp);

	/**
	 * 
	 * @param grp
	 */
	protected void ThrowGroupNotSupportedException(ConnectionDefGroup grp){

	}

	/**
	 * 
	 * @param connDef
	 */
	public abstract void UpdateConnectionDef(ConnectionDef connDef);

	/**
	 * 
	 * @param connDef
	 * @param alConnections
	 */
	protected boolean UpdateConnectionDef(ConnectionDef connDef, ArrayList alConnections){
		return null;
	}

}