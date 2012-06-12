package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:44
 */
public class BookmarkActionDef extends ActionDef {

	public BookmarkActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String ActionItem(){
		return "";
	}

	/**
	 * 
	 * @param correction
	 * @param bJustCollect
	 * @param strAssociatedBusOb
	 */
	public boolean CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect, String strAssociatedBusOb){
		return false;
	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public boolean HasTagsContainingTagCategory(String strTagCategoryName){
		return false;
	}

}