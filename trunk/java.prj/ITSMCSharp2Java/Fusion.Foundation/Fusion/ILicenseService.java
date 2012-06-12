package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:49
 */
public interface ILicenseService {

	/**
	 * 
	 * @param strBusObName
	 * @param right
	 */
	public boolean HasBusObRight(String strBusObName, SecurityRight right);

	/**
	 * 
	 * @param strDefId
	 * @param strDefName
	 * @param nLicensedCount
	 * @param nRowsInDB
	 */
	public boolean IsWithinLicenseCount(String strDefId, String strDefName, int nLicensedCount, int nRowsInDB);

	/**
	 * 
	 * @param strUsername
	 */
	public void Logout(String strUsername);

	/**
	 * 
	 * @param strDefId
	 */
	public boolean NeedToCheckLicenseCount(String strDefId);

	/**
	 * 
	 * @param strLicenseList
	 * @param strUsername
	 */
	public string[] TakeLicense(string[] strLicenseList, String strUsername);

	/**
	 * 
	 * @param strLicenseId
	 * @param strUsername
	 */
	public void TakeLicense(String strLicenseId, String strUsername);

}