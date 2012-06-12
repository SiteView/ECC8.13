package Fusion;

import java.math.BigDecimal;

import Fusion.control.ICryptoTransform;
import Fusion.control.XmlDocument;


/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:05
 */
public final class AuthorizationKey {

	private Boolean m_bEditMaster;
	private Boolean m_bEditXml;
	private BigDecimal m_permissionLevel;
	private String m_strUserId;
	private String strKey;



	public void finalize() throws Throwable {

	}

	public AuthorizationKey(){

	}

	/**
	 * 
	 * @param strFileName
	 * @param strFileKey
	 * @param strPassphrase
	 */
	public AuthorizationKey(String strFileName, String strFileKey, String strPassphrase){

	}

	public Boolean CanEditMaster(){
		return null;
	}

	public Boolean CanEditXml(){
		return null;
	}

	/**
	 * 
	 * @param strRights
	 * @param transform
	 */
	private String DecryptRights(String strRights, ICryptoTransform transform){
		return "";
	}

	/**
	 * 
	 * @param strPhrase
	 */
	private byte[] GetKeyForPhrase(String strPhrase){
		return null;
	}

	/**
	 * 
	 * @param passphrase
	 */
	private String HashString(String passphrase){
		return "";
	}

	public BigDecimal PermissionLevel(){
		return null;
	}

	/**
	 * 
	 * @param xd
	 * @param strPassphrase
	 */
	private void SetVars(XmlDocument xd, String strPassphrase){

	}

	public String UserId(){
		return "";
	}

	/**
	 * 
	 * @param strPathName
	 * @param strCryptPhrase
	 * @param strPassphrase
	 */
	private void VerifyRights(String strPathName, String strCryptPhrase, String strPassphrase){

	}

}
