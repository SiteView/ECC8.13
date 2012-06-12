package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:12
 */
public class ModuleNames {

	private String BrandingModule = "Branding";
	private String BrandingSetting = "Fusion.SystemStartUp.BrandingModule";
	private String FusionDefault = "Fusion";
	private String ModuleInfoFile = "ModuleInfo.xml";
	private String RegisteredDllSetting = "Fusion.SystemStartUp.RegisteredDlls";

	public ModuleNames(){

	}

	public void finalize() throws Throwable {

	}

	public String getBrandingModule(){
		return BrandingModule;
	}

	public String getBrandingSetting(){
		return BrandingSetting;
	}

	public String getFusionDefault(){
		return FusionDefault;
	}

	public String getModuleInfoFile(){
		return ModuleInfoFile;
	}

	public String getRegisteredDllSetting(){
		return RegisteredDllSetting;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBrandingModule(String newVal){
		BrandingModule = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBrandingSetting(String newVal){
		BrandingSetting = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFusionDefault(String newVal){
		FusionDefault = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setModuleInfoFile(String newVal){
		ModuleInfoFile = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRegisteredDllSetting(String newVal){
		RegisteredDllSetting = newVal;
	}

}