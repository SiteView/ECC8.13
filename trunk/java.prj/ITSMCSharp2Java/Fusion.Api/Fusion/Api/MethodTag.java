package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:03
 */
public class MethodTag extends Tag {

	private Object m_oReturnValue;
	private String m_strExposedBy;
	private String ReturnValue = "ReturnValue";

	public MethodTag(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strExposedBy
	 */
	public MethodTag(String strExposedBy){

	}

	/**
	 * 
	 * @param strExposedBy
	 * @param oReturnValue
	 */
	public MethodTag(String strExposedBy, Object oReturnValue){

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
		return false;
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