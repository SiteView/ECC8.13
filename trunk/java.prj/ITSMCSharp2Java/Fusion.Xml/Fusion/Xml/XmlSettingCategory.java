package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:57
 */
public class XmlSettingCategory {

	private string Dialog = "Dialog";
	private string ExtendedGroup = "ExtendedGroup";
	private string Grid = "Grid";
	private string Group = "Group";
	private string Mfu = "Mfu";
	private string Mru = "Mru";
	private string None = "None";
	private string QueryPrompt = "QueryPrompt";
	private string ScopedGroup = "ScopedGroup";
	private string Single = "Single";
	private string Tab = "Tab";

	public XmlSettingCategory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param sc
	 */
	public static string CategoryToXmlCategory(SettingCategory sc){
		return "";
	}

	public string getDialog(){
		return Dialog;
	}

	public string getExtendedGroup(){
		return ExtendedGroup;
	}

	public string getGrid(){
		return Grid;
	}

	public string getGroup(){
		return Group;
	}

	public string getMfu(){
		return Mfu;
	}

	public string getMru(){
		return Mru;
	}

	public string getNone(){
		return None;
	}

	public string getQueryPrompt(){
		return QueryPrompt;
	}

	public string getScopedGroup(){
		return ScopedGroup;
	}

	public string getSingle(){
		return Single;
	}

	public string getTab(){
		return Tab;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDialog(string newVal){
		Dialog = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setExtendedGroup(string newVal){
		ExtendedGroup = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGrid(string newVal){
		Grid = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGroup(string newVal){
		Group = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMfu(string newVal){
		Mfu = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMru(string newVal){
		Mru = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNone(string newVal){
		None = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setQueryPrompt(string newVal){
		QueryPrompt = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setScopedGroup(string newVal){
		ScopedGroup = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSingle(string newVal){
		Single = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTab(string newVal){
		Tab = newVal;
	}

	/**
	 * 
	 * @param strXmlCategory
	 */
	public static SettingCategory XmlCategoryToCategory(string strXmlCategory){
		return null;
	}

}