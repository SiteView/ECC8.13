package Fusion.Foundation;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 15:22:43
 */
public class CompareDefinitionsHelper {

	private static CaseInsensitiveComparer comparer = new CaseInsensitiveComparer();
	private static CaseInsensitiveHashCodeProvider hashProvider = new CaseInsensitiveHashCodeProvider();
	private boolean m_bDeepCompare = false;
	private static CompareDefinitionsHelper m_CompareHelper = null;
	private Hashtable m_htObj_CompareAttributes = new Hashtable();
	private Hashtable m_htType_DisplayProperetyInfo = new Hashtable();
	private Hashtable m_htType_ProperetyInfoForKey = new Hashtable();
	private Hashtable m_htType_ProperetyInfos = new Hashtable();
	private List<String> m_scDispPropertieNames = new ArrayList<String>();



	public void finalize() throws Throwable {

	}

	public CompareDefinitionsHelper(){

	}

	/**
	 * 
	 * @param parentCompareInfo
	 * @param propertyId
	 * @param compareCategory
	 * @param strGroupName
	 */
	private Fusion.Foundation.CompareInfo AddChildCompareInfo(Fusion.Foundation.CompareInfo parentCompareInfo, String propertyId, CompareCategory compareCategory, String strGroupName){
		return null;
	}

	/**
	 * 
	 * @param srcDef
	 * @param tgtDef
	 * @param parentCompareInfo
	 * @param bDeepCompare
	 */
	public void Compare(Object srcDef, Object tgtDef, Fusion.Foundation.CompareInfo parentCompareInfo, boolean bDeepCompare){

	}

	/**
	 * 
	 * @param strPropertyID
	 * @param strPropertyName
	 * @param collSource
	 * @param collTarget
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void CompareCollectionItems(String strPropertyID, String strPropertyName, List collSource, List collTarget, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param strPropertyID
	 * @param objSource
	 * @param objTarget
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void CompareCultureInfo(String strPropertyID, Object objSource, Object objTarget, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param strPropertyID
	 * @param strPropertyName
	 * @param dictSource
	 * @param dictTarget
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void CompareDictionaryItems(String strPropertyID, String strPropertyName, Map dictSource, Map dictTarget, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param strPropertyID
	 * @param strPropertyName
	 * @param dictSource
	 * @param dictTarget
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private ArrayList<String> CompareDictionaryValues(String strPropertyID, String strPropertyName, Map dictSource, Map dictTarget, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){
		return null;
	}

	/**
	 * 
	 * @param strPropertyID
	 * @param strPropertyName
	 * @param collSource
	 * @param collTarget
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void CompareFusionValueCollectionItems(String strPropertyID, String strPropertyName, List collSource, List collTarget, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param strPropertyID
	 * @param objSource
	 * @param objTarget
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void CompareFusionValues(String strPropertyID, Object objSource, Object objTarget, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	public static CompareDefinitionsHelper CompareHelperInstance(){
		return null;
	}

	/**
	 * 
	 * @param strPropertyID
	 * @param strPropertyName
	 * @param collSource
	 * @param collTarget
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void CompareNonEmptyCollectionItems(String strPropertyID, String strPropertyName, List collSource, List collTarget, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param strPropertyID
	 * @param strPropertyName
	 * @param dictSource
	 * @param dictTarget
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void CompareNonEmptyDictionaryItems(String strPropertyID, String strPropertyName, Map dictSource, Map dictTarget, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param strPropertyID
	 * @param strPropertyName
	 * @param dictSource
	 * @param dictTarget
	 * @param parentCompareInfo
	 */
	private ArrayList<String> CompareNonEmptyDictionaryValues(String strPropertyID, String strPropertyName, Map dictSource, Map dictTarget, Fusion.Foundation.CompareInfo parentCompareInfo){
		return null;
	}

	/**
	 * 
	 * @param strPropertyID
	 * @param strPropertyName
	 * @param collSource
	 * @param collTarget
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void CompareNonEmptyFusionValueCollectionItems(String strPropertyID, String strPropertyName, List collSource, List collTarget, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param strPropertyID
	 * @param objSource
	 * @param objTarget
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void CompareReferences(String strPropertyID, Object objSource, Object objTarget, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param strPropertyID
	 * @param objSource
	 * @param objTarget
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void CompareValues(String strPropertyID, Object objSource, Object objTarget, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param propertyId
	 * @param srcProperty
	 * @param srcDef
	 * @param tgtProperty
	 * @param tgtDef
	 * @param strPropertyGroupName
	 * @param parentCompareInfo
	 */
	private void DoAutoCompare(String propertyId, PropertyInfo srcProperty, Object srcDef, PropertyInfo tgtProperty, Object tgtDef, String strPropertyGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param propertyId
	 * @param srcProperty
	 * @param srcDef
	 * @param tgtProperty
	 * @param tgtDef
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void DoCollectionOfFusionValuesCompare(String propertyId, PropertyInfo srcProperty, Object srcDef, PropertyInfo tgtProperty, Object tgtDef, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param propertyId
	 * @param srcProperty
	 * @param srcDef
	 * @param tgtProperty
	 * @param tgtDef
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void DoCollectionTypeCompare(String propertyId, PropertyInfo srcProperty, Object srcDef, PropertyInfo tgtProperty, Object tgtDef, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param propertyId
	 * @param srcProperty
	 * @param srcDef
	 * @param tgtProperty
	 * @param tgtDef
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void DoDictionaryTypeCompare(String propertyId, PropertyInfo srcProperty, Object srcDef, PropertyInfo tgtProperty, Object tgtDef, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param propertyId
	 * @param srcProperty
	 * @param srcDef
	 * @param tgtProperty
	 * @param tgtDef
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void DoDictionaryWithStringsCompare(String propertyId, PropertyInfo srcProperty, Object srcDef, PropertyInfo tgtProperty, Object tgtDef, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param propertyId
	 * @param srcProperty
	 * @param srcDef
	 * @param tgtProperty
	 * @param tgtDef
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void DoFusionValuesCompare(String propertyId, PropertyInfo srcProperty, Object srcDef, PropertyInfo tgtProperty, Object tgtDef, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param srcDef
	 * @param srcType
	 * @param tgtDef
	 * @param tgtType
	 * @param parentCompareInfo
	 */
	private void DoReportChangeOfType(Object srcDef, Type srcType, Object tgtDef, Type tgtType, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param strPropertyId
	 * @param srcProperty
	 * @param srcDef
	 * @param tgtProperty
	 * @param tgtDef
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void DoRuleDefCompare(String strPropertyId, PropertyInfo srcProperty, Object srcDef, PropertyInfo tgtProperty, Object tgtDef, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param src
	 * @param tgt
	 */
	private boolean EmptyCollections(List src, List tgt){
		return false;
	}

	/**
	 * 
	 * @param propertyInfo
	 */
	private ComparableAttribute GetComparableAttribute(PropertyInfo propertyInfo){
		return null;
	}

	/**
	 * 
	 * @param pi
	 */
	private Object[] GetCompareAttributes(PropertyInfo pi){
		return null;
	}

	/**
	 * 
	 * @param type
	 */
	private Object[] GetCompareAttributes(Type type){
		return null;
	}

	/**
	 * 
	 * @param parentCompareInfo
	 * @param strGroupName
	 * @param compareCategory
	 */
	private Fusion.Foundation.CompareInfo GetCustomGroup(Fusion.Foundation.CompareInfo parentCompareInfo, String strGroupName, CompareCategory compareCategory){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param defType
	 */
	private String GetDisplayValue(Object def, Type defType){
		return "";
	}

	/**
	 * 
	 * @param defObj
	 */
	private PropertyInfo GetObjectKey(Object defObj){
		return null;
	}

	/**
	 * 
	 * @param type
	 */
	protected PropertyInfo[] GetProperties(Type type){
		return null;
	}

	/**
	 * 
	 * @param ruleDef
	 */
	private boolean IsInLineRule(Object ruleDef){
		return false;
	}

	/**
	 * 
	 * @param strPropertyID
	 * @param piSrcProperty
	 * @param objSourceDef
	 * @param piTgtProperty
	 * @param objTgtDef
	 * @param strGroupName
	 * @param parentCompareInfo
	 */
	private void OnlyCompareReferences(String strPropertyID, PropertyInfo piSrcProperty, Object objSourceDef, PropertyInfo piTgtProperty, Object objTgtDef, String strGroupName, Fusion.Foundation.CompareInfo parentCompareInfo){

	}

	/**
	 * 
	 * @param parentCompareInfo
	 * @param compareCategory
	 */
	private void SetAncestorCompareInfo(Fusion.Foundation.CompareInfo parentCompareInfo, CompareCategory compareCategory){

	}

}