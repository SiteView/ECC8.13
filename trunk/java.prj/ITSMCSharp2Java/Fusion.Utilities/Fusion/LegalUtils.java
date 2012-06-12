package Fusion;

import java.util.Hashtable;

import Fusion.control.ICollection;
import Fusion.control.Point;
import Fusion.control.Stream;
import Fusion.control.XmlElement;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 11:18:26
 */
public class LegalUtils {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:26
	 */
	private class Tags {

		private String AboutItems = "AboutItems";
		private String AdminIcon = "AdminIcon";
		private String AdminSplashScreen = "AdminSplashScreen";
		private String GeneralIcon = "GeneralIcon";
		private String GeneralSplashScreen = "GeneralSplashScreen";
		private String Horizontal = "Horizontal";
		private String Item = "Item";
		private String LegalProductName = "LegalProductName";
		private String License = "License";
		private String MainIcon = "MainIcon";
		private String MainSplashScreen = "MainSplashScreen";
		private String MainTitleBarText = "MainTitleBarText";
		private String MessageBoxCaption = "MessageBoxCaption";
		private String Name = "Name";
		private String OtherTitleBarText = "OtherTitleBarText";
		private String ProductName = "ProductName";
		private String SerialNumber = "SerialNumber";
		private String SplashScreenTextLocation = "SplashScreenTextLocation";
		private String Version = "Version";
		private String Vertical = "Vertical";
		private String VerticalName = "VerticalName";
		private String VerticalVersion = "VerticalVersion";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getAboutItems(){
			return AboutItems;
		}

		public String getAdminIcon(){
			return AdminIcon;
		}

		public String getAdminSplashScreen(){
			return AdminSplashScreen;
		}

		public String getGeneralIcon(){
			return GeneralIcon;
		}

		public String getGeneralSplashScreen(){
			return GeneralSplashScreen;
		}

		public String getHorizontal(){
			return Horizontal;
		}

		public String getItem(){
			return Item;
		}

		public String getLegalProductName(){
			return LegalProductName;
		}

		public String getLicense(){
			return License;
		}

		public String getMainIcon(){
			return MainIcon;
		}

		public String getMainSplashScreen(){
			return MainSplashScreen;
		}

		public String getMainTitleBarText(){
			return MainTitleBarText;
		}

		public String getMessageBoxCaption(){
			return MessageBoxCaption;
		}

		public String getName(){
			return Name;
		}

		public String getOtherTitleBarText(){
			return OtherTitleBarText;
		}

		public String getProductName(){
			return ProductName;
		}

		public String getSerialNumber(){
			return SerialNumber;
		}

		public String getSplashScreenTextLocation(){
			return SplashScreenTextLocation;
		}

		public String getVersion(){
			return Version;
		}

		public String getVertical(){
			return Vertical;
		}

		public String getVerticalName(){
			return VerticalName;
		}

		public String getVerticalVersion(){
			return VerticalVersion;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAboutItems(String newVal){
			AboutItems = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAdminIcon(String newVal){
			AdminIcon = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setAdminSplashScreen(String newVal){
			AdminSplashScreen = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setGeneralIcon(String newVal){
			GeneralIcon = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setGeneralSplashScreen(String newVal){
			GeneralSplashScreen = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setHorizontal(String newVal){
			Horizontal = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setItem(String newVal){
			Item = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLegalProductName(String newVal){
			LegalProductName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLicense(String newVal){
			License = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMainIcon(String newVal){
			MainIcon = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMainSplashScreen(String newVal){
			MainSplashScreen = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMainTitleBarText(String newVal){
			MainTitleBarText = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMessageBoxCaption(String newVal){
			MessageBoxCaption = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setName(String newVal){
			Name = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setOtherTitleBarText(String newVal){
			OtherTitleBarText = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setProductName(String newVal){
			ProductName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSerialNumber(String newVal){
			SerialNumber = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSplashScreenTextLocation(String newVal){
			SplashScreenTextLocation = newVal;
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
		public void setVertical(String newVal){
			Vertical = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setVerticalName(String newVal){
			VerticalName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setVerticalVersion(String newVal){
			VerticalVersion = newVal;
		}

	}

	private String ApplicationSuiteLegalName = "FrontRange Products";
	private String CompanyCopyright = "Copyright \\x00a9 2004. FrontRange Solutions USA Inc.";
	private String CompanyName = "FrontRange Solutions USA Inc.";
	private String CompanyTrademark = "";
	private String DefaultAdminIcon = "[IMAGE]Fusion#Images.Icons.Common.Admin.ico";
	private String DefaultAdminSplashScreen = "[IMAGE]Fusion#Images.Admin_Splash.jpg";
	private String DefaultIcon = "[IMAGE]Fusion#Images.Icons.Common.Application.ico";
	private String DefaultLicense = "Fusion.License.FrontRange Solutions EULA 9-04lckd.rtf";
	private String DefaultSplashScreen = "[IMAGE]Fusion#Images.Client_Splash.jpg";
	private String FusionProduct = "Fusion Architecture";
	private static Boolean m_bInitialized = false;
	private static Hashtable m_htAboutInfo = new Hashtable();
	private static Point m_pSplashScreenTextLocation = new Point(0x16, 0x55);
	private static String m_strAdminIcon = "";
	private static String m_strAdminSplashScreen = "";
	private static String m_strGeneralIcon = "";
	private static String m_strGeneralSplashScreen = "";
	private static String m_strLegalProductName = "";
	private static String m_strLicense = "";
	private static String m_strMainIcon = "";
	private static String m_strMainSplashScreen = "";
	private static String m_strMainTitleBarText = "";
	private static String m_strMessageBoxCaption = "";
	private static String m_strOtherTitleBarText = "";
	private static String m_strProductName = "";
	private static String m_strProductVersion = "1.0";
	private static String m_strSerialNumber = "";
	private static String m_strVerticalName = "";
	private static String m_strVerticalVersion = "";
	private String MaximumDataVersion = "1200";
	private String MessageBoxTitleBar = "FRS Application";
	private String MinimumDataVersion = "1000";
	private String OrionAcronym = "FRSApp";
	private String OrionAdministrator = "FRS Application Administrator";
	private String OrionAppVersion = "1.0";
	private String OrionLegalName = "FRS Application";
	private String OrionProduct = "FRS Application";
	private String OrionServerManager = "FRS Server Manager";
	private String OrionShortName = "FRS Application";

	public LegalUtils(){

	}

	public void finalize() throws Throwable {

	}

	public static ICollection AboutInfoNames(){
		return null;
	}

	public static String AdminIcon(){
		return "";
	}

	public static String AdminSplashScreen(){
		return "";
	}

	public static String GeneralIcon(){
		return "";
	}

	public static String GeneralSplashScreen(){
		return "";
	}

	/**
	 * 
	 * @param strName
	 */
	public static String GetAboutInfoValue(String strName){
		return "";
	}

	public String getApplicationSuiteLegalName(){
		return ApplicationSuiteLegalName;
	}

	public String getCompanyCopyright(){
		return CompanyCopyright;
	}

	public String getCompanyName(){
		return CompanyName;
	}

	public String getCompanyTrademark(){
		return CompanyTrademark;
	}

	public String getDefaultAdminIcon(){
		return DefaultAdminIcon;
	}

	public String getDefaultIcon(){
		return DefaultIcon;
	}

	public String getFusionProduct(){
		return FusionProduct;
	}

	public String getMaximumDataVersion(){
		return MaximumDataVersion;
	}

	public String getMinimumDataVersion(){
		return MinimumDataVersion;
	}

	public String getOrionAcronym(){
		return OrionAcronym;
	}

	public String getOrionAdministrator(){
		return OrionAdministrator;
	}

	public String getOrionAppVersion(){
		return OrionAppVersion;
	}

	public String getOrionLegalName(){
		return OrionLegalName;
	}

	public String getOrionProduct(){
		return OrionProduct;
	}

	public String getOrionServerManager(){
		return OrionServerManager;
	}

	public String getOrionShortName(){
		return OrionShortName;
	}

	/**
	 * 
	 * @param stream
	 */
	public static void Initialize(Stream stream){

	}

	public static String LegalProductName(){
		return "";
	}

	public static String License(){
		return "";
	}

	/**
	 * 
	 * @param xe
	 */
	private static void LoadFromXml(XmlElement xe){

	}

	public static String MainIcon(){
		return "";
	}

	public static String MainSplashScreen(){
		return "";
	}

	public static String MainTitleBarText(){
		return "";
	}

	public static String MessageBoxCaption(){
		return "";
	}

	public static String OtherTitleBarText(){
		return "";
	}

	public static String ProductName(){
		return "";
	}

	public static String ProductVersion(){
		return "";
	}

	public static String SerialNumber(){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setApplicationSuiteLegalName(String newVal){
		ApplicationSuiteLegalName = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCompanyCopyright(String newVal){
		CompanyCopyright = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCompanyName(String newVal){
		CompanyName = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCompanyTrademark(String newVal){
		CompanyTrademark = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDefaultAdminIcon(String newVal){
		DefaultAdminIcon = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDefaultIcon(String newVal){
		DefaultIcon = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFusionProduct(String newVal){
		FusionProduct = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaximumDataVersion(String newVal){
		MaximumDataVersion = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMinimumDataVersion(String newVal){
		MinimumDataVersion = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOrionAcronym(String newVal){
		OrionAcronym = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOrionAdministrator(String newVal){
		OrionAdministrator = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOrionAppVersion(String newVal){
		OrionAppVersion = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOrionLegalName(String newVal){
		OrionLegalName = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOrionProduct(String newVal){
		OrionProduct = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOrionServerManager(String newVal){
		OrionServerManager = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOrionShortName(String newVal){
		OrionShortName = newVal;
	}

	public static Point SplashScreenTextLocation(){
		return null;
	}

	public static String VerticalName(){
		return "";
	}

	public static String VerticalVersion(){
		return "";
	}

}