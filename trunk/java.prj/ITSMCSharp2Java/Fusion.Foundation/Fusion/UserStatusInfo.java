package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:49
 */
public class UserStatusInfo implements IUserStatusInfo {

	private String m_strLoginId;
	private String m_strSessionId;
	private String m_strStatusId;



	public void finalize() throws Throwable {

	}

	public UserStatusInfo(){

	}

	/**
	 * 
	 * @param strLoginId
	 * @param strStatusId
	 * @param strSessionId
	 */
	public UserStatusInfo(String strLoginId, String strStatusId, String strSessionId){

	}

	public String LoginId(){
		return "";
	}

	public String SessionId(){
		return "";
	}

	public String StatusId(){
		return "";
	}

}