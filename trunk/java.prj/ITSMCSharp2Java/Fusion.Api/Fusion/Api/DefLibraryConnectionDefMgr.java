package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:01
 */
public class DefLibraryConnectionDefMgr extends FusionAggregate implements IConnectionDefManager {

	public DefLibraryConnectionDefMgr(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public DefLibraryConnectionDefMgr(Object fusionObject){

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

	/**
	 * 
	 * @param grp
	 */
	public List ConnectionsForGroup(ConnectionDefGroup grp){
		return null;
	}

	/**
	 * 
	 * @param defLib
	 */
	public static Fusion.Api.DefLibraryConnectionDefMgr CreateInstance(Fusion.Api.DefinitionLibrary defLib){
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

	public ConnectionDef GetDefaultDatabase(){
		return null;
	}

	public String GetDefaultDatabaseName(){
		return "";
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

	/**
	 * 
	 * @param grp
	 */
	public void ReloadConnectionsForGroup(ConnectionDefGroup grp){

	}

	public void SaveConnectionDefs(){

	}

	/**
	 * 
	 * @param strDefault
	 */
	public void SetDefaultDatabase(String strDefault){

	}

	/**
	 * 
	 * @param grp
	 */
	public boolean SupportsConnectionsForGroup(ConnectionDefGroup grp){
		return null;
	}

	public String ToString(){
		return "";
	}

	/**
	 * 
	 * @param connDef
	 */
	public void UpdateConnectionDef(ConnectionDef connDef){

	}

	private Fusion.BusinessLogic.DefLibraryConnectionDefMgr WhoAmI(){
		return null;
	}

}