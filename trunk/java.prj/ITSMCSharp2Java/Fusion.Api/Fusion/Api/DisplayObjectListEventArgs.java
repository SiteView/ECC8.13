package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:02
 */
public class DisplayObjectListEventArgs extends EventArgs {

	private String AutoTaskList = "AutotasksList";
	private String BusinessProcessList = "BusinessProcessList";
	private String DashboardList = "DashboardList";
	private String DashboardPartList = "DashboardPartList";
	private Object m_objListType = null;
	private String ObjectBrowserList = "ObjectBrowserList";
	private String ReportList = "ReportList";
	private String SearchList = "SearchList";
	private String VersionList = "VersionList";

	public DisplayObjectListEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param objListType
	 */
	public DisplayObjectListEventArgs(Object objListType){

	}

	public String getAutoTaskList(){
		return AutoTaskList;
	}

	public String getBusinessProcessList(){
		return BusinessProcessList;
	}

	public String getDashboardList(){
		return DashboardList;
	}

	public String getDashboardPartList(){
		return DashboardPartList;
	}

	public String getObjectBrowserList(){
		return ObjectBrowserList;
	}

	public String getReportList(){
		return ReportList;
	}

	public String getSearchList(){
		return SearchList;
	}

	public String getVersionList(){
		return VersionList;
	}

	public Object ListType(){
		return null;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAutoTaskList(String newVal){
		AutoTaskList = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBusinessProcessList(String newVal){
		BusinessProcessList = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDashboardList(String newVal){
		DashboardList = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDashboardPartList(String newVal){
		DashboardPartList = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setObjectBrowserList(String newVal){
		ObjectBrowserList = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setReportList(String newVal){
		ReportList = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSearchList(String newVal){
		SearchList = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setVersionList(String newVal){
		VersionList = newVal;
	}

}