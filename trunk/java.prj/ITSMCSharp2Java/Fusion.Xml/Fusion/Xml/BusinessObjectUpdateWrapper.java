package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-四月-2010 11:37:25
 */
public class BusinessObjectUpdateWrapper {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 22-四月-2010 11:37:25
	 */
	public enum Action {
		NotSet,
		Add,
		Edit,
		Delete,
		Skip,
		AddLink,
		RemoveLink
	}

	private ICollection m_icollFields = null;
	private XmlElement m_xeBO = null;

	public BusinessObjectUpdateWrapper(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param elBO
	 */
	public BusinessObjectUpdateWrapper(XmlElement elBO){

	}

	public Action ActionType(){
		return null;
	}

	public string BusObId(){
		return "";
	}

	public string BusObName(){
		return "";
	}

	public ICollection Fields(){
		return null;
	}

	/**
	 * 
	 * @param strLinkToName
	 * @param strLinkToId
	 * @param strReason
	 * @param strRelationshipName
	 */
	public void GetLinkToInformation(string strLinkToName, string strLinkToId, string strReason, string strRelationshipName){

	}

	public string Version(){
		return "";
	}

}