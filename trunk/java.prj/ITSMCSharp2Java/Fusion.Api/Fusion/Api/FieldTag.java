package Fusion.Api;

import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:44:30
 */
public class FieldTag extends Tag {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:44:30
	 */
	private class DefinitionComparer extends IComparer {

		public DefinitionComparer(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		/**
		 * 
		 * @param x
		 * @param y
		 */
		public int Compare(Object x, Object y){
			return 0;
		}

	}

	public FieldTag(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param context
	 * @param strBusObName
	 * @param strBusObAlias
	 * @param defRel
	 * @param bIsDupe
	 * @param alDisplayInfo
	 */
	private void AddBusObToList(TagContext context, String strBusObName, String strBusObAlias, RelationshipDef defRel, boolean bIsDupe, ArrayList alDisplayInfo){

	}

	/**
	 * 
	 * @param defFld
	 * @param strItemText
	 * @param strSubcategory
	 * @param aItems
	 */
	private void AddItemToFieldList(FieldDef defFld, String strItemText, String strSubcategory, IList aItems){

	}

	/**
	 * 
	 * @param defFld
	 * @param strSubcategory
	 * @param aItems
	 */
	private void AddSubFieldsForLinkField(FieldDef defFld, String strSubcategory, IList aItems){

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
	 * @param strBusOb
	 * @param strField
	 */
	private DataTable GetDataTableFromBusObFieldName(TagContext context, String strBusOb, String strField){
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
	private IList GetListOfAllBusObs(TagContext context){
		return null;
	}

	/**
	 * 
	 * @param context
	 */
	private IList GetListOfCurrentBusObAndRelatedBusObs(TagContext context){
		return null;
	}

	/**
	 * 
	 * @param context
	 */
	private IList GetListOfRelatedBusObs(TagContext context){
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
	 * @param query
	 */
	private DataTable PerformFusionQuery(TagContext context, FusionQuery query){
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
	public List ResolveItemToCollection(TagContext context, String strSubcategory, String strItem){
		return null;
	}

}