package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:25
 */
public class FileBasedConnectionDefMgr extends ConnectionDefManager {

	private String AppConfigLocation = "CIQAppDir";
	private String ConnectionFileName = "Connections.ciq";
	private boolean m_bCommonConnectionsDirty = false;
	private boolean m_bCommonConnectionsLoaded = false;
	private boolean m_bPersonalConnectionsDirty = false;
	private boolean m_bPersonalConnectionsLoaded = false;
	private ArrayList m_listCommonConnections = null;
	private ArrayList m_listPersonalConnections = null;
	private String m_strCommonDirectory = "";
	private String m_strPersonalDirectory = "";

	public FileBasedConnectionDefMgr(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param connDef
	 */
	public void AddConnectionDef(ConnectionDef connDef){

	}

	/**
	 * 
	 * @param grp
	 */
	public boolean AreConnectionsLoadedForGroup(ConnectionDefGroup grp){
		return null;
	}

	private String CommonDataDirectory(){
		return "";
	}

	/**
	 * 
	 * @param grp
	 */
	public List ConnectionsForGroup(ConnectionDefGroup grp){
		return null;
	}

	/**
	 * 
	 * @param type
	 * @param grp
	 */
	public ConnectionDef CreateNewConnectionDef(ConnectionDefType type, ConnectionDefGroup grp){
		return null;
	}

	private DbConnectionDef CreateSpecialDbConnection(){
		return null;
	}

	private ServerConnectionDef CreateSpecialServerConnection(){
		return null;
	}

	/**
	 * 
	 * @param connDef
	 */
	public void DeleteConnectionDef(ConnectionDef connDef){

	}

	/**
	 * 
	 * @param strConnectionName
	 */
	public ConnectionDef GetConnectionDef(String strConnectionName){
		return null;
	}

	public String getConnectionFileName(){
		return ConnectionFileName;
	}

	private void LoadCommonConnections(){

	}

	/**
	 * 
	 * @param grp
	 */
	public void LoadConnectionsForGroup(ConnectionDefGroup grp){

	}

	/**
	 * 
	 * @param grp
	 */
	public void LoadConnectionsForGroupIfNeeded(ConnectionDefGroup grp){

	}

	private void LoadPersonalConnections(){

	}

	private String PersonalDataDirectory(){
		return "";
	}

	/**
	 * 
	 * @param strDirectory
	 */
	private XmlDocument ReadFromDirectory(String strDirectory){
		return null;
	}

	private XmlDocument ReadFromIsolatedStorage(){
		return null;
	}

	/**
	 * 
	 * @param grp
	 */
	public void ReloadConnectionsForGroup(ConnectionDefGroup grp){

	}

	private void SaveCommonConnectionDefs(){

	}

	public void SaveConnectionDefs(){

	}

	private void SavePersonalConnectionDefs(){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setConnectionFileName(String newVal){
		ConnectionFileName = newVal;
	}

	/**
	 * 
	 * @param grp
	 */
	public boolean SupportsConnectionsForGroup(ConnectionDefGroup grp){
		return null;
	}

	/**
	 * 
	 * @param connDef
	 */
	public void UpdateConnectionDef(ConnectionDef connDef){

	}

	/**
	 * 
	 * @param strDirectory
	 * @param xmlConnectionInfo
	 */
	private boolean WriteToDirectory(String strDirectory, XmlDocument xmlConnectionInfo){
		return null;
	}

	/**
	 * 
	 * @param xmlConnectionInfo
	 */
	private boolean WriteToIsolatedStorage(XmlDocument xmlConnectionInfo){
		return null;
	}

	/**
	 * 
	 * @param xmlConnectionInfo
	 * @param strDirectory
	 */
	private boolean WriteToIsolatedStorage(XmlDocument xmlConnectionInfo, String strDirectory){
		return null;
	}

}