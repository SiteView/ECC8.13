package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:14
 */
public class Notification {

	private ArrayList m_alSourceObjects;
	private String m_strCategory;
	private String m_strDetails;
	private String m_strSource;
	private String m_strTarget;

	public Notification(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param notifOld
	 */
	public Notification(Notification notifOld){

	}

	/**
	 * 
	 * @param notifOld
	 * @param moNew
	 */
	public Notification(Notification notifOld, Object moNew){

	}

	/**
	 * 
	 * @param strCategory
	 * @param strTarget
	 * @param strSource
	 * @param strDetails
	 */
	public Notification(String strCategory, String strTarget, String strSource, String strDetails){

	}

	/**
	 * 
	 * @param strCategory
	 * @param strTarget
	 * @param strSource
	 * @param strDetails
	 * @param moNew
	 */
	public Notification(String strCategory, String strTarget, String strSource, String strDetails, Object moNew){

	}

	/**
	 * 
	 * @param moNew
	 */
	public void AddSourceObject(Object moNew){

	}

	public String Category(){
		return "";
	}

	public String Details(){
		return "";
	}

	public Object FirstSourceObject(){
		return null;
	}

	public String Source(){
		return "";
	}

	public List SourceObjects(){
		return null;
	}

	public String Target(){
		return "";
	}

}