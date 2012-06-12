package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:42
 */
public class UpdatePackage {

	private int InitialSize = 10;
	private BusinessObjectShell m_businessObjectDeletes[];
	private BusinessObjectUpdate m_businessObjectInserts[];
	private BusinessObjectLink m_businessObjectLinkDeletes[];
	private BusinessObjectLink m_businessObjectLinkInserts[];
	private BusinessObjectUpdate m_businessObjectUpdates[];
	private ArrayList m_cachedBusObTypes = null;
	private int m_deletesSize = 0;
	private static ArrayList m_emptyEventItems = new ArrayList(0);
	private int m_insertSize = 0;
	private int m_linksSize = 0;
	private ArrayList m_listEventItems;
	private int m_removedLinksSize = 0;
	private int m_updatesSize = 0;

	public UpdatePackage(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param delete
	 */
	public void AddBusinessObjectDelete(BusinessObjectShell delete){

	}

	/**
	 * 
	 * @param insert
	 */
	public void AddBusinessObjectInsert(BusinessObjectUpdate insert){

	}

	/**
	 * 
	 * @param link
	 */
	public void AddBusinessObjectLinkDelete(BusinessObjectLink link){

	}

	/**
	 * 
	 * @param link
	 */
	public void AddBusinessObjectLinkInsert(BusinessObjectLink link){

	}

	/**
	 * 
	 * @param update
	 */
	public void AddBusinessObjectUpdate(BusinessObjectUpdate update){

	}

	/**
	 * 
	 * @param strBusObName
	 */
	public void AddCachedBusObType(string strBusObName){

	}

	/**
	 * 
	 * @param eventItem
	 */
	public void AddEventItem(EventItem eventItem){

	}

	public BusinessObjectShell[] BusinessObjectDeletes(){
		return null;
	}

	public BusinessObjectUpdate[] BusinessObjectInserts(){
		return null;
	}

	public BusinessObjectLink[] BusinessObjectLinkDeletes(){
		return null;
	}

	public BusinessObjectLink[] BusinessObjectLinkInserts(){
		return null;
	}

	public BusinessObjectUpdate[] BusinessObjectUpdates(){
		return null;
	}

	public string[] CachedBusObTypes(){
		return "";
	}

	public void ClearEventItems(){

	}

	public ICollection EventItems(){
		return null;
	}

	/**
	 * 
	 * @param strBusObName
	 */
	public bool HasCachedBusObType(string strBusObName){
		return null;
	}

	/**
	 * 
	 * @param eventItem
	 */
	public void RemoveEventItem(EventItem eventItem){

	}

}