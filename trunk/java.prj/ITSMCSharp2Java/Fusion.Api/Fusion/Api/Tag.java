package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:48
 */
public abstract class Tag extends IExposedTag {



	public void finalize() throws Throwable {
		super.finalize();
	}

	protected Tag(){

	}

	public abstract DisplayInfo Category();

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
	 * @param strItem
	 */
	public String GetItemDisplay(Object context, String strSubcategory, String strItem){
		return "";
	}

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 */
	public abstract List GetItems(TagContext context, String strSubcategory);

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 */
	public List GetItems(Object context, String strSubcategory){
		return null;
	}

	/**
	 * 
	 * @param context
	 */
	public abstract List GetSubcategories(TagContext context);

	/**
	 * 
	 * @param context
	 */
	public List GetSubcategories(Object context){
		return null;
	}

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 */
	public String GetSubcategoryDisplay(TagContext context, String strSubcategory){
		return "";
	}

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 */
	public String GetSubcategoryDisplay(Object context, String strSubcategory){
		return "";
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
	public boolean HasOptionalEdit(Object context, String strSubcategory){
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
	 */
	public boolean HasRequiredEdit(Object context, String strSubcategory){
		return null;
	}

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 * @param strItem
	 */
	public abstract String ResolveItem(TagContext context, String strSubcategory, String strItem);

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 * @param strItem
	 */
	public String ResolveItem(Object context, String strSubcategory, String strItem){
		return "";
	}

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 * @param strItem
	 * @param Ã±ultureInfo
	 */
	public abstract String ResolveItem(TagContext context, String strSubcategory, String strItem, CultureInfo Ã±ultureInfo);

	/**
	 * 
	 * @param context
	 * @param strSubcategory
	 * @param strItem
	 * @param Ã±ultureInfo
	 */
	public String ResolveItem(Object context, String strSubcategory, String strItem, CultureInfo Ã±ultureInfo){
		return "";
	}

}