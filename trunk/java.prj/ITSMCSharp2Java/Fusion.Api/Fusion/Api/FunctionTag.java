package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:34
 */
public class FunctionTag extends Tag {

	public FunctionTag(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public DisplayInfo Category(){
		return null;
	}

	public static String CategoryName(){
		return "";
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
	 * @param strFunc
	 * @param collFormats
	 */
	public static SystemFunctionValueType GetValueType(TagContext context, String strSubcategory, String strFunc, List collFormats){
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

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 * @param strItem
	 */
	public FusionValue ResolveItemToFusionValue(TagContext context, String strSubcategory, String strItem){
		return null;
	}

}