package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:42
 */
public class UpdateWrapper extends XmlWrapper {

	private ICollection m_icollBusinessObjects = null;
	private ArrayList m_listEventItems = new ArrayList();

	public UpdateWrapper(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strName
	 * @param strID
	 */
	public void AddBOAdd(string strName, string strID){

	}

	/**
	 * 
	 * @param strName
	 * @param strID
	 */
	public void AddBODelete(string strName, string strID){

	}

	/**
	 * 
	 * @param strName
	 * @param strID
	 */
	public void AddBOEdit(string strName, string strID){

	}

	/**
	 * 
	 * @param strLinkFromName
	 * @param strLinkFromId
	 * @param strLinkToName
	 * @param strLinkToId
	 * @param strReason
	 * @param strRelationshipName
	 */
	public void AddBOLinkAdd(string strLinkFromName, string strLinkFromId, string strLinkToName, string strLinkToId, string strReason, string strRelationshipName){

	}

	/**
	 * 
	 * @param strLinkFromName
	 * @param strLinkFromId
	 * @param strLinkToName
	 * @param strLinkToId
	 * @param strReason
	 * @param strRelationshipName
	 */
	public void AddBOLinkRemove(string strLinkFromName, string strLinkFromId, string strLinkToName, string strLinkToId, string strReason, string strRelationshipName){

	}

	/**
	 * 
	 * @param item
	 */
	public void AddEventItem(EventItem item){

	}

	public ICollection BusinessObjects(){
		return null;
	}

	public void ClearEventItems(){

	}

	public ICollection EventItems(){
		return null;
	}

	/**
	 * 
	 * @param item
	 */
	public void RemoveEventItem(EventItem item){

	}

	/**
	 * 
	 * @param version
	 */
	public void SetVersion(object version){

	}

}