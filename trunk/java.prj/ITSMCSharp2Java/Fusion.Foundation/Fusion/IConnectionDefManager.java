package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:45
 */
public interface IConnectionDefManager {

	/**
	 * 
	 * @param connDef
	 */
	public void AddConnectionDef(ConnectionDef connDef);

	/**
	 * 
	 * @param grp
	 */
	public boolean AreConnectionsLoadedForGroup(ConnectionDefGroup grp);

	/**
	 * 
	 * @param grp
	 */
	public List ConnectionsForGroup(ConnectionDefGroup grp);

	/**
	 * 
	 * @param type
	 * @param grp
	 */
	public ConnectionDef CreateNewConnectionDef(ConnectionDefType type, ConnectionDefGroup grp);

	/**
	 * 
	 * @param connDef
	 */
	public void DeleteConnectionDef(ConnectionDef connDef);

	/**
	 * 
	 * @param strConnectionName
	 */
	public ConnectionDef GetConnectionDef(String strConnectionName);

	public ConnectionDef GetDefaultDatabase();

	public String GetDefaultDatabaseName();

	/**
	 * 
	 * @param grp
	 */
	public void LoadConnectionsForGroup(ConnectionDefGroup grp);

	/**
	 * 
	 * @param grp
	 */
	public void LoadConnectionsForGroupIfNeeded(ConnectionDefGroup grp);

	/**
	 * 
	 * @param grp
	 */
	public void ReloadConnectionsForGroup(ConnectionDefGroup grp);

	public void SaveConnectionDefs();

	/**
	 * 
	 * @param strDefault
	 */
	public void SetDefaultDatabase(String strDefault);

	/**
	 * 
	 * @param grp
	 */
	public boolean SupportsConnectionsForGroup(ConnectionDefGroup grp);

	/**
	 * 
	 * @param connDef
	 */
	public void UpdateConnectionDef(ConnectionDef connDef);

}