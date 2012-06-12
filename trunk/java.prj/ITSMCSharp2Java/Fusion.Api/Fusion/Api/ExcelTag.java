package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:06
 */
public class ExcelTag extends Tag {

	private String Location = "Location";
	private String m_strExposedBy;
	private String m_strFilePath;
	private IExcelWrapper m_XlWrapper;
	private String Name = "Name";

	public ExcelTag(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strExposedBy
	 * @param strFilePath
	 */
	public ExcelTag(String strExposedBy, String strFilePath){

	}

	/**
	 * 
	 * @param strExposedBy
	 * @param xlWrapper
	 * @param strFilePath
	 */
	public ExcelTag(String strExposedBy, IExcelWrapper xlWrapper, String strFilePath){

	}

	public DisplayInfo Category(){
		return null;
	}

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 * @param strItem
	 */
	public String GetItemDisplay(TagContext context, String strSubcategory, String strItem){
		return "";
	}

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 */
	public List GetItems(TagContext context, String strSubcategory){
		return null;
	}

	/**
	 * 
	 * @param strItem
	 */
	private Object GetLocationValue(String strItem){
		return null;
	}

	/**
	 * 
	 * @param context
	 */
	public List GetSubcategories(TagContext context){
		return null;
	}

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 */
	public boolean HasOptionalEdit(TagContext context, String strSubcategory){
		return null;
	}

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 */
	public boolean HasRequiredEdit(TagContext context, String strSubcategory){
		return null;
	}

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 * @param strItem
	 */
	public String ResolveItem(TagContext context, String strSubcategory, String strItem){
		return "";
	}

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 * @param strItem
	 * @param cultureInfo
	 */
	public String ResolveItem(TagContext context, String strSubcategory, String strItem, CultureInfo cultureInfo){
		return "";
	}

}