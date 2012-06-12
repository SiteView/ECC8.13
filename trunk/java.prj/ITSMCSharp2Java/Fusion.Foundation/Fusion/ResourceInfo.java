package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:48
 */
public class ResourceInfo {

	private static String FILESEPARATOR = ".";
	private boolean m_bPhysicalResource = true;
	private Fusion.ModuleInfo m_ModuleInfo = null;
	private String m_strAdrId = "";
	private String m_strCategory = "";
	private String m_strFileName = "";
	private String m_strManifestResourceName = "";
	private String NOCATEGORY = "__NOCAT__";
	private static String SEPARATOR = "-";

	public ResourceInfo(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param mi
	 * @param strManifestResourceName
	 */
	public ResourceInfo(Fusion.ModuleInfo mi, String strManifestResourceName){

	}

	public String AdrId(){
		return "";
	}

	public String Category(){
		return "";
	}

	public String CategoryKeyName(){
		return "";
	}

	public String GetBaseName(){
		return "";
	}

	private String GetCategory(){
		return "";
	}

	public String GetExtension(){
		return "";
	}

	public String GetFileName(){
		return "";
	}

	/**
	 * 
	 * @param nPosition
	 */
	public String GetFileNameSubString(int nPosition){
		return "";
	}

	public String getFILESEPARATOR(){
		return FILESEPARATOR;
	}

	/**
	 * 
	 * @param strString
	 * @param strSeparator
	 * @param nSeparator
	 */
	private int GetLastSeparatorPosition(String strString, String strSeparator, int nSeparator){
		return 0;
	}

	public String getSEPARATOR(){
		return SEPARATOR;
	}

	public boolean IsImage(){
		return null;
	}

	public String ManifestResourceName(){
		return "";
	}

	public Fusion.ModuleInfo ModuleInfo(){
		return null;
	}

	public boolean NoCategory(){
		return null;
	}

	public boolean PhysicalResource(){
		return null;
	}

	public String PrimaryName(){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFILESEPARATOR(String newVal){
		FILESEPARATOR = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSEPARATOR(String newVal){
		SEPARATOR = newVal;
	}

}