package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:23
 */
public class BPInvokerMessage {

	private Fusion.Xml.BusinessObjectUpdateWrapper.Action m_action;
	private string m_sBusObName;
	private string m_sId;



	public void finalize() throws Throwable {

	}

	public BPInvokerMessage(){

	}

	/**
	 * 
	 * @param sId
	 * @param sBusObName
	 * @param action
	 */
	public BPInvokerMessage(string sId, string sBusObName, Fusion.Xml.BusinessObjectUpdateWrapper.Action action){

	}

	public Fusion.Xml.BusinessObjectUpdateWrapper.Action Action(){
		return null;
	}

	public string BusObName(){
		return "";
	}

	public string Id(){
		return "";
	}

}