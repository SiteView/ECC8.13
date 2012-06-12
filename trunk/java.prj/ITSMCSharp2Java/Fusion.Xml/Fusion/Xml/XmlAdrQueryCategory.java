package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:43
 */
public class XmlAdrQueryCategory {

	private string Delete = "DELETE";
	private string DupeCheck = "DUPECHECK";
	private string ItemList = "ITEMLIST";
	private string PlaceholderList = "PLACEHOLDERLIST";
	private string SpecifiedItems = "SPECIFIEDITEMS";
	private string Update = "UPDATE";

	public XmlAdrQueryCategory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param cat
	 */
	public static string CategoryToXmlCategory(AdrQueryCategory cat){
		return "";
	}

	public string getDelete(){
		return Delete;
	}

	public string getDupeCheck(){
		return DupeCheck;
	}

	public string getItemList(){
		return ItemList;
	}

	public string getPlaceholderList(){
		return PlaceholderList;
	}

	public string getSpecifiedItems(){
		return SpecifiedItems;
	}

	public string getUpdate(){
		return Update;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDelete(string newVal){
		Delete = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDupeCheck(string newVal){
		DupeCheck = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setItemList(string newVal){
		ItemList = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPlaceholderList(string newVal){
		PlaceholderList = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSpecifiedItems(string newVal){
		SpecifiedItems = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUpdate(string newVal){
		Update = newVal;
	}

	/**
	 * 
	 * @param strXmlCategory
	 */
	public static AdrQueryCategory XmlCategoryToCategory(string strXmlCategory){
		return null;
	}

}