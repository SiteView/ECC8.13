package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:57
 */
public class CrystalSettingsManager {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:58
	 */
	private class Tags {

		private String elmAdd = "add";
		private String elmConfiguration = "configuration";
		private String elmCrystalDecisions = "crystalDecisions";
		private String elmCustomServerFileReportService = "customServerFileReportService";
		private String elmFrontRangeSolutions = "frontRangeSolutions";
		private String elmKey = "key";
		private String elmServerFileReportManager = "serverFileReportManager";
		private String elmValue = "value";
		private String valRootDir = "rootDirectory";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getelmAdd(){
			return elmAdd;
		}

		public String getelmConfiguration(){
			return elmConfiguration;
		}

		public String getelmCrystalDecisions(){
			return elmCrystalDecisions;
		}

		public String getelmCustomServerFileReportService(){
			return elmCustomServerFileReportService;
		}

		public String getelmFrontRangeSolutions(){
			return elmFrontRangeSolutions;
		}

		public String getelmKey(){
			return elmKey;
		}

		public String getelmServerFileReportManager(){
			return elmServerFileReportManager;
		}

		public String getelmValue(){
			return elmValue;
		}

		public String getvalRootDir(){
			return valRootDir;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setelmAdd(String newVal){
			elmAdd = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setelmConfiguration(String newVal){
			elmConfiguration = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setelmCrystalDecisions(String newVal){
			elmCrystalDecisions = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setelmCustomServerFileReportService(String newVal){
			elmCustomServerFileReportService = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setelmFrontRangeSolutions(String newVal){
			elmFrontRangeSolutions = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setelmKey(String newVal){
			elmKey = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setelmServerFileReportManager(String newVal){
			elmServerFileReportManager = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setelmValue(String newVal){
			elmValue = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setvalRootDir(String newVal){
			valRootDir = newVal;
		}

	}

	private boolean m_bFieldsChanged = false;
	private boolean m_bReadWriteLoginInfo = true;
	private boolean m_bReadWriteServerInfo = true;
	private boolean m_bUseRas = false;
	private String m_strDatabase = "";
	private String m_strDatabaseId = "Database";
	private String m_strDataSource = "";
	private String m_strDataSourceId = "DataSource";
	private String m_strFolder = "";
	private String m_strFolderId = "Folder";
	private String m_strLoginInfoId = "Login";
	private String m_strName = "";
	private String m_strNameId = "Name";
	private String m_strPassword = "";
	private String m_strPasswordId = "Password";
	private String m_strReportSettingsId = "Fusion.Report";
	private String m_strServerInfoId = "Server";
	private String m_strUser = "";
	private String m_strUseRasId = "UseRas";
	private String m_strUserId = "User";
	private String m_strWebServiceURL = "";
	private String m_strWebServiceURLId = "WebServiceURL";
	private ISettings m_svc = null;
	private String WEBCONFIG_LOCATION = "ServiceManagementCrystalReportViewers";

	public CrystalSettingsManager(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param svc
	 */
	public CrystalSettingsManager(ISettings svc){

	}

	/**
	 * 
	 * @param xdSettings
	 * @param xeSettings
	 * @param strKey
	 * @param strValue
	 */
	private void AddSetting(XmlDocument xdSettings, XmlElement xeSettings, String strKey, String strValue){

	}

	public String Database(){
		return "";
	}

	public String DataSource(){
		return "";
	}

	public String Folder(){
		return "";
	}

	private String GetCrystalFileLocation(){
		return "";
	}

	/**
	 * 
	 * @param xdSettings
	 */
	private XmlElement GetCrystalSettingsNode(XmlDocument xdSettings){
		return null;
	}

	/**
	 * 
	 * @param xdSettings
	 */
	private XmlElement GetFrsSettingsNode(XmlDocument xdSettings){
		return null;
	}

	/**
	 * 
	 * @param xdSettings
	 */
	private void GetSettings(XmlDocument xdSettings){

	}

	public String Password(){
		return "";
	}

	public void ReadSettings(){

	}

	private void ReadSettingsFile(){

	}

	public boolean ReadWriteLoginInfo(){
		return null;
	}

	public boolean ReadWriteServerInfo(){
		return null;
	}

	public void SaveSettings(){

	}

	public String Server(){
		return "";
	}

	/**
	 * 
	 * @param xdSettings
	 */
	private void SetSettings(XmlDocument xdSettings){

	}

	public String User(){
		return "";
	}

	public boolean UseRas(){
		return null;
	}

	public String WebServiceURL(){
		return "";
	}

	private void WriteSettingsFile(){

	}

}