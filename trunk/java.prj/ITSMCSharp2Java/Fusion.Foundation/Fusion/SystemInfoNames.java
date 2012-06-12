package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:28
 */
public class SystemInfoNames {

	private String LicensedName = "LicensedName";
	private String LicensedSerialNo = "LicensedSerialNo";
	private String Version = "Version";
	private String VerticalInfo = "VerticalInfo";

	public SystemInfoNames(){

	}

	public void finalize() throws Throwable {

	}

	public String getLicensedName(){
		return LicensedName;
	}

	public String getLicensedSerialNo(){
		return LicensedSerialNo;
	}

	public String getVersion(){
		return Version;
	}

	public String getVerticalInfo(){
		return VerticalInfo;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLicensedName(String newVal){
		LicensedName = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLicensedSerialNo(String newVal){
		LicensedSerialNo = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setVersion(String newVal){
		Version = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setVerticalInfo(String newVal){
		VerticalInfo = newVal;
	}

}