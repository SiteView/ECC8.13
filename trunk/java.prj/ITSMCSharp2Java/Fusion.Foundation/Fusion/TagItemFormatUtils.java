package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:37
 */
public class TagItemFormatUtils extends IComparer {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:37
	 */
	private class XmlTags {

		private String Format = "Format";
		private String FormatApplyOrder = "ApplyOrder";
		private String FormatArguments = "Args";
		private String FormatItem = "Type";
		private String Item = "Item";

		public XmlTags(){

		}

		public void finalize() throws Throwable {

		}

		public String getFormat(){
			return Format;
		}

		public String getFormatApplyOrder(){
			return FormatApplyOrder;
		}

		public String getFormatArguments(){
			return FormatArguments;
		}

		public String getFormatItem(){
			return FormatItem;
		}

		public String getItem(){
			return Item;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFormat(String newVal){
			Format = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFormatApplyOrder(String newVal){
			FormatApplyOrder = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFormatArguments(String newVal){
			FormatArguments = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFormatItem(String newVal){
			FormatItem = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setItem(String newVal){
			Item = newVal;
		}

	}

	public TagItemFormatUtils(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strItem
	 * @param format
	 */
	public static String AddFormatToItem(String strItem, TagFormat format){
		return "";
	}

	/**
	 * 
	 * @param val
	 * @param iFormatter
	 * @param alFormats
	 */
	private static FusionValue ApplyFormats(FusionValue val, ITagFormatter iFormatter, ArrayList alFormats){
		return null;
	}

	/**
	 * 
	 * @param strCoreItem
	 */
	public static String BuildItem(String strCoreItem){
		return "";
	}

	/**
	 * 
	 * @param strCoreItem
	 * @param format
	 */
	public static String BuildItem(String strCoreItem, TagFormat format){
		return "";
	}

	/**
	 * 
	 * @param strCoreItem
	 * @param collFormats
	 */
	public static String BuildItem(String strCoreItem, List collFormats){
		return "";
	}

	/**
	 * 
	 * @param x
	 * @param y
	 */
	public int Compare(Object x, Object y){
		return 0;
	}

	/**
	 * 
	 * @param val
	 * @param format
	 */
	public static FusionValue FormatItem(FusionValue val, TagFormat format){
		return null;
	}

	/**
	 * 
	 * @param val
	 * @param collFormats
	 */
	public static FusionValue FormatItem(FusionValue val, List collFormats){
		return null;
	}

	/**
	 * 
	 * @param strItem
	 */
	public static String GetCoreItem(String strItem){
		return "";
	}

	/**
	 * 
	 * @param format
	 */
	private static XmlElement GetFormatElement(TagFormat format){
		return null;
	}

	/**
	 * 
	 * @param xeFormat
	 */
	private static TagFormat GetTagFormat(XmlElement xeFormat){
		return null;
	}

	/**
	 * 
	 * @param strItem
	 * @param strCoreItem
	 * @param collFormats
	 */
	public static void ParseItem(String strItem, String strCoreItem, List collFormats){

	}

	/**
	 * 
	 * @param strItem
	 * @param strFormatItem
	 */
	public static String RemoveFormatFromItem(String strItem, String strFormatItem){
		return "";
	}

	/**
	 * 
	 * @param strItem
	 * @param strCoreItem
	 */
	public static String UpdateCoreItem(String strItem, String strCoreItem){
		return "";
	}

}