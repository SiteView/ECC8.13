package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:06
 */
public class LinkStatus {

	private EmailAddress m_address;
	private IBusObDisplayKey m_busObKey;
	private List m_collBusObKeys;
	private LinkResults m_linkResults;

	public LinkStatus(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param address
	 * @param collKeys
	 */
	public LinkStatus(EmailAddress address, List collKeys){

	}

	/**
	 * 
	 * @param results
	 * @param address
	 */
	public LinkStatus(LinkResults results, EmailAddress address){

	}

	/**
	 * 
	 * @param results
	 * @param key
	 */
	public LinkStatus(LinkResults results, IBusObDisplayKey key){

	}

	public EmailAddress Address(){
		return null;
	}

	public IBusObDisplayKey Key(){
		return null;
	}

	public List MatchingBusObKeys(){
		return null;
	}

	public LinkResults Results(){
		return null;
	}

}