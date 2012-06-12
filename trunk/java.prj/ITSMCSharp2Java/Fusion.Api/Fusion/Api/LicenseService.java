package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:56
 */
public class LicenseService {

	private String BasicAdminLicenseId = "01FF6B28393B41798C8B52465842372E";
	private String FusionApiLicenseId = "5340869BB88345a18D198254A6BAF8D4";
	private String IntegrationLayerLicenseId = "2884A5A059AA49c7948AE3D46A83EC00";
	private IFusionApi m_api;
	private ILicenseService m_licenseService;
	private IOrchestrator m_Orch = null;
	private String OutlookIntegrationLicenseId = "02C113FCE7A242a8AB1851CF9BF201F2";
	private String PlatformLicenseId = "3057913CD66847f5BF05A5369CBF181F";
	private String SelfServiceLicenseId = "CBA8FC8315CB4fc689D187664BEF749C";
	private String WebServicesLicenseId = "5AB4F3160AE240e3B97F34E9029B3AC0";

	public LicenseService(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param orch
	 * @param licenseService
	 * @param api
	 */
	public LicenseService(IOrchestrator orch, ILicenseService licenseService, IFusionApi api){

	}

	private String[] GetLicenseListForRole(){
		return "";
	}

	/**
	 * 
	 * @param strBusObName
	 * @param right
	 */
	public boolean HasBusObRight(String strBusObName, SecurityRight right){
		return false;
	}

	/**
	 * 
	 * @param licensesTaken
	 */
	private boolean HasFoundationLicense(String[] licensesTaken){
		return null;
	}

	/**
	 * 
	 * @param strDefId
	 * @param strDefName
	 * @param nLicenseCount
	 * @param nRowsInDB
	 */
	public boolean IsWithinLicenseCount(String strDefId, String strDefName, int nLicenseCount, int nRowsInDB){
		return false;
	}

	/**
	 * 
	 * @param strUsername
	 */
	public void Logout(String strUsername){

	}

	/**
	 * 
	 * @param strDefName
	 */
	public boolean NeedToCheckLicenseCount(String strDefName){
		return false;
	}

	public void TakeLicense(){

	}

	/**
	 * 
	 * @param strLicenseList
	 */
	public String[] TakeLicense(String[] strLicenseList){
		return "";
	}

	/**
	 * 
	 * @param strLicenseId
	 */
	public void TakeLicense(String strLicenseId){

	}

	/**
	 * 
	 * @param strLicenseId
	 * @param modifiedUsername
	 */
	public void TakeLicenseWeb(String strLicenseId, String modifiedUsername){

	}

	/**
	 * 
	 * @param strLicenseList
	 * @param modifiedUsername
	 */
	public void TakeLicenseWeb(String[] strLicenseList, String modifiedUsername){

	}

}