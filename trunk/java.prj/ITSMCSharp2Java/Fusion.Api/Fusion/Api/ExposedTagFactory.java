package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:24
 */
public class ExposedTagFactory {

	public ExposedTagFactory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param def
	 */
	public static IExposedTag GetExposedTag(ActionDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	private static IExposedTag GetExposedTag(CallMethodActionDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	private static IExposedTag GetExposedTag(CallWSActionDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	private static IExposedTag GetExposedTag(ExportToExcelActionDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	private static IExposedTag GetExposedTag(SendMessageActionDef def){
		return null;
	}

}