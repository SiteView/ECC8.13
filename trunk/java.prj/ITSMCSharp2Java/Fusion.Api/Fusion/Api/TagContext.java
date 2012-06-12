package Fusion.Api;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.Map;

import com.sun.org.apache.xerces.internal.impl.xpath.regex.Match;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:45:52
 */
public class TagContext {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:45:52
	 */
	public enum ResolvedType {
		Unicode,
		RTF
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:45:52
	 */
	private class TagItemProperties {

		private String m_strCategory;
		private String m_strItem;
		private String m_strSubcategory;

		public TagItemProperties(){

		}

		public void finalize() throws Throwable {

		}

		/**
		 * 
		 * @param strCategory
		 * @param strSubcategory
		 * @param strItem
		 */
		public TagItemProperties(String strCategory, String strSubcategory, String strItem){

		}

		public String Category(){
			return "";
		}

		public String Item(){
			return "";
		}

		public String Subcategory(){
			return "";
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:45:52
	 */
	private class Tags {

		private String From = "From";
		private String Subcategory = "Subcategory";
		private String Value = "Value";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getFrom(){
			return From;
		}

		public String getSubcategory(){
			return Subcategory;
		}

		public String getValue(){
			return Value;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFrom(String newVal){
			From = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSubcategory(String newVal){
			Subcategory = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValue(String newVal){
			Value = newVal;
		}

	}

	private ArrayList m_aBusObs;
	private boolean m_bAtLeastOneSuccess;
	private boolean m_bUseAllBusObs;
	private boolean m_bUseLinkFields;
	private BusinessObject m_busObActive;
	private BusinessObject m_busObCurrent;
	private CultureInfo m_CultureInfo;
	private BusinessObjectDef m_defBusObCurrent;
	private IFusionApi m_FusionApi;
	private Hashtable m_htResolvedSystemPrompts;
	private Hashtable m_htTagCategoryNameToAdditionalExposedTag;
	private Hashtable m_htTagCategoryNameToExposedTag;
	private IUIInteraction m_Interaction;
	private Fusion.Api.DefinitionLibrary m_Library;
	private int m_nCurrBusOb;
	private ResolvedType m_ResolvedType;
	private TagResolveResult m_ResolveResult;
	private IVirtualKeyList m_virtualKeyList;

	public TagContext(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param fusionApi
	 * @param busOb
	 * @param interaction
	 */
	public TagContext(IFusionApi fusionApi, BusinessObject busOb, IUIInteraction interaction){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param library
	 * @param defBusOb
	 */
	public TagContext(IFusionApi fusionApi, Fusion.Api.DefinitionLibrary library, BusinessObjectDef defBusOb){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param collBusObs
	 * @param interaction
	 */
	public TagContext(IFusionApi fusionApi, List collBusObs, IUIInteraction interaction){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param busOb
	 * @param interaction
	 * @param cultureInfo
	 */
	public TagContext(IFusionApi fusionApi, BusinessObject busOb, IUIInteraction interaction, CultureInfo cultureInfo){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param busOb
	 * @param resolvedPrompts
	 * @param interaction
	 */
	public TagContext(IFusionApi fusionApi, BusinessObject busOb, Map resolvedPrompts, IUIInteraction interaction){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param library
	 * @param defBusOb
	 * @param cultureInfo
	 */
	public TagContext(IFusionApi fusionApi, Fusion.Api.DefinitionLibrary library, BusinessObjectDef defBusOb, CultureInfo cultureInfo){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param virtualKeyList
	 * @param busOb
	 * @param interaction
	 */
	public TagContext(IFusionApi fusionApi, IVirtualKeyList virtualKeyList, BusinessObject busOb, IUIInteraction interaction){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param collBusObs
	 * @param interaction
	 * @param cultureInfo
	 */
	public TagContext(IFusionApi fusionApi, List collBusObs, IUIInteraction interaction, CultureInfo cultureInfo){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param busOb
	 * @param resolvedPrompts
	 * @param interaction
	 * @param cultureInfo
	 */
	public TagContext(IFusionApi fusionApi, BusinessObject busOb, Map resolvedPrompts, IUIInteraction interaction, CultureInfo cultureInfo){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param virtualKeyList
	 * @param busOb
	 * @param interaction
	 * @param cultureInfo
	 */
	public TagContext(IFusionApi fusionApi, IVirtualKeyList virtualKeyList, BusinessObject busOb, IUIInteraction interaction, CultureInfo cultureInfo){

	}

	/**
	 * 
	 * @param expTag
	 */
	public void AddRunTimeExposedTag(IExposedTag expTag){

	}

	public IFusionApi Api(){
		return null;
	}

	/**
	 * 
	 * @param strCategoryDisplay
	 * @param strSubcategoryDisplay
	 * @param strItemDisplay
	 */
	public static String BuildXmlTagDisplayFromDisplayText(String strCategoryDisplay, String strSubcategoryDisplay, String strItemDisplay){
		return "";
	}

	/**
	 * 
	 * @param strCategory
	 * @param strSubcategory
	 * @param strItem
	 */
	public String BuildXmlTagDisplayFromNonDisplayText(String strCategory, String strSubcategory, String strItem){
		return "";
	}

	public ArrayList BusObList(){
		return null;
	}

	public int BusObListCount(){
		return 0;
	}

	public boolean BusObListMode(){
		return false;
	}

	public BusinessObject CurrentBusOb(){
		return null;
	}

	public BusinessObjectDef CurrentBusObDef(){
		return null;
	}

	public CultureInfo CurrentCulture(){
		return null;
	}

	public Fusion.Api.DefinitionLibrary DefinitionLibrary(){
		return null;
	}

	protected List GetAdditionalExposedTags(){
		return null;
	}

	private void GetCoreExposedTags(){

	}

	private BusinessObject GetCurrentBusObFromKeyList(){
		return null;
	}

	private BusinessObject GetCurrentBusObFromList(){
		return null;
	}

	/**
	 * 
	 * @param strCategory
	 */
	public IExposedTag GetExposedTag(String strCategory){
		return null;
	}

	public List GetTagCategories(){
		return null;
	}

	/**
	 * 
	 * @param strCategory
	 */
	public String GetTagCategoryDisplayFromNonDisplayText(String strCategory){
		return "";
	}

	/**
	 * 
	 * @param strCategory
	 * @param strSubcategory
	 * @param strItem
	 */
	public String GetTagItemDisplayFromNonDisplayText(String strCategory, String strSubcategory, String strItem){
		return "";
	}

	/**
	 * 
	 * @param strCategory
	 * @param strSubcategory
	 */
	public List GetTagItems(String strCategory, String strSubcategory){
		return null;
	}

	/**
	 * 
	 * @param strCategory
	 */
	public List GetTagSubcategories(String strCategory){
		return null;
	}

	/**
	 * 
	 * @param strCategory
	 * @param strSubcategory
	 */
	public String GetTagSubcategoryDisplayFromNonDisplayText(String strCategory, String strSubcategory){
		return "";
	}

	public IUIInteraction InteractionHandler(){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 */
	public boolean IsActiveBusOb(BusinessObject busOb){
		return false;
	}

	public int KeyListCount(){
		return 0;
	}

	public boolean KeyListMode(){
		return false;
	}

	public void LoadAdditionalDesignTimeExposedTags(){

	}

	public boolean MoveFirstInBusObList(){
		return false;
	}

	public boolean MoveFirstInKeyList(){
		return false;
	}

	public boolean MoveLastInBusObList(){
		return false;
	}

	public boolean MoveLastInKeyList(){
		return false;
	}

	public boolean MoveNextInBusObList(){
		return false;
	}

	public boolean MoveNextInKeyList(){
		return false;
	}

	public boolean MovePreviousInBusObList(){
		return false;
	}

	public boolean MovePreviousInKeyList(){
		return false;
	}

	public Map ResolvedSystemPrompts(){
		return null;
	}

	/**
	 * 
	 * @param strCategory
	 * @param strSubcategory
	 * @param strItem
	 */
	private String ResolveItem(String strCategory, String strSubcategory, String strItem){
		return "";
	}

	/**
	 * 
	 * @param match
	 */
	private String ResolveMatchEvaluator(Match match){
		return "";
	}

	/**
	 * 
	 * @param strTags
	 */
	public TagResolveResult ResolveTags(String strTags){
		return null;
	}

	/**
	 * 
	 * @param strTags
	 * @param ResultType
	 */
	public TagResolveResult ResolveTags(String strTags, ResolvedType ResultType){
		return null;
	}

	/**
	 * 
	 * @param strTags
	 */
	private TagResolveResult ResolveTagsInString(String strTags){
		return null;
	}

	public static String TagWithoutSubcategoryDisplayFormat(){
		return "";
	}

	public static String TagWithSubcategoryDisplayFormat(){
		return "";
	}

	public boolean UseAllBusinessObjects(){
		return false;
	}

	public boolean UseLinkFields(){
		return false;
	}

}