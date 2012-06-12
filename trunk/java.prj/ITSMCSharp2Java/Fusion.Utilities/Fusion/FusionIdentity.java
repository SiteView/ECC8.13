package Fusion;

import Fusion.control.*;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:20
 */
public class FusionIdentity extends IIdentity {

	private Boolean m_bAuthenticated = false;
	private String m_strAuthenticationType = "";
	private String m_strName = "";

	public FusionIdentity(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param bAuthenticated
	 * @param strName
	 * @param strAuthType
	 */
	public FusionIdentity(Boolean bAuthenticated, String strName, String strAuthType){

	}

	public String AuthenticationType(){
		return "";
	}

	public Boolean IsAuthenticated(){
		return null;
	}

	public String Name(){
		return "";
	}

}