package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:51
 */
public class XmlDefListControllerCategory {

	private string AutoTask = "AUTOTASK";
	private string BusinessProcess = "BUSINESSPROCESS";
	private string Dashboard = "DASHBOARD";
	private string DashboardPart = "DASHBOARDPART";
	private string None = "NONE";
	private string ObjectTreeView = "OBJECTTREEVIEW";
	private string ObjectVersionView = "OBJECTVERSIONVIEW";
	private string Report = "REPORT";
	private string Search = "SEARCH";
	private string Trigger = "TRIGGER";

	public XmlDefListControllerCategory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param defListController
	 */
	public static string GetTypeName(DefListController defListController){
		return "";
	}

	/**
	 * 
	 * @param strXmlCategory
	 */
	public static DefListController ToCategory(string strXmlCategory){
		return null;
	}

	/**
	 * 
	 * @param defListController
	 */
	public static string ToString(DefListController defListController){
		return "";
	}

}