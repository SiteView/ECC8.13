package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:48
 */
public interface IExposedTag {

	public DisplayInfo Category();

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 * @param strItem
	 */
	public String GetItemDisplay(Object context, String strSubcategory, String strItem);

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 */
	public List GetItems(Object context, String strSubcategory);

	/**
	 * 
	 * @param context
	 */
	public List GetSubcategories(Object context);

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 */
	public String GetSubcategoryDisplay(Object context, String strSubcategory);

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 */
	public boolean HasOptionalEdit(Object context, String strSubcategory);

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 */
	public boolean HasRequiredEdit(Object context, String strSubcategory);

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 * @param strItem
	 */
	public String ResolveItem(Object context, String strSubcategory, String strItem);

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 * @param strItem
	 * @param Ã±ultureInfo
	 */
	public String ResolveItem(Object context, String strSubcategory, String strItem, CultureInfo Ã±ultureInfo);

}