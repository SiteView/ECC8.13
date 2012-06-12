package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:31
 */
public class FilenameTag extends Tag {

	private String Filename = "Filename";
	private String FilenameWithPath = "FilenameWithPath";
	private String TempFilename = "TempFilename";
	private String TempFilenameWithPath = "TempFilenameWithPath";

	public FilenameTag(){

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