package Fusion;

import java.io.Serializable;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:01
 */
public class SearchCriteria implements Serializable {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:01
	 */
	public enum ExpressionType {
		Connected,
		Expression,
		ListExpression,
		Occurrences,
		QueryFunctionExpression,
		QueryFunctionListExpression
	}

	private static CaseInsensitiveComparer comparer = new CaseInsensitiveComparer();
	private static CaseInsensitiveHashCodeProvider hashProvider = new CaseInsensitiveHashCodeProvider();
	private Hashtable m_dictSearchParameters;
	private Fusion.QueryFunction m_queryFunction;
	private XmlDocument m_xdQueries;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public SearchCriteria(){

	}

	/**
	 * 
	 * @param xdQueries
	 */
	public SearchCriteria(XmlDocument xdQueries){

	}

	/**
	 * 
	 * @param info
	 * @param c
	 */
	private SearchCriteria(SerializationInfo info, StreamingContext c){

	}

	/**
	 * 
	 * @param xeListExpression
	 * @param strFieldName
	 */
	public void AddFieldValue(XmlElement xeListExpression, String strFieldName){

	}

	/**
	 * 
	 * @param xeListExpression
	 * @param strFunction
	 */
	public void AddFunctionValue(XmlElement xeListExpression, String strFunction){

	}

	/**
	 * 
	 * @param xeListExpression
	 * @param strLiteralValue
	 */
	public void AddLiteralValue(XmlElement xeListExpression, String strLiteralValue){

	}

	/**
	 * 
	 * @param xeListExpression
	 * @param xeQueryFunction
	 */
	public void AddQueryFunctionValue(XmlElement xeListExpression, XmlElement xeQueryFunction){

	}

	/**
	 * 
	 * @param xeListExpression
	 * @param strRule
	 */
	public void AddRuleValue(XmlElement xeListExpression, String strRule){

	}

	/**
	 * 
	 * @param strName
	 * @param value
	 */
	public void AddSearchParameter(String strName, Object value){

	}

	/**
	 * 
	 * @param searchParameter
	 */
	private void AddSearchParameterInXml(ISearchParameter searchParameter){

	}

	/**
	 * 
	 * @param xeListExpression
	 * @param strToken
	 */
	public void AddTokenValue(XmlElement xeListExpression, String strToken){

	}

	/**
	 * 
	 * @param xeListExpression
	 * @param strValueType
	 * @param strValue
	 */
	private void AddValueToListExpression(XmlElement xeListExpression, String strValueType, String strValue){

	}

	/**
	 * 
	 * @param axeExpressions
	 */
	public XmlElement AndExpressions(XmlElement[] axeExpressions){
		return null;
	}

	/**
	 * 
	 * @param xe1
	 * @param xe2
	 */
	public XmlElement AndExpressions(XmlElement xe1, XmlElement xe2){
		return null;
	}

	/**
	 * 
	 * @param xe1
	 * @param xe2
	 * @param xe3
	 */
	public XmlElement AndExpressions(XmlElement xe1, XmlElement xe2, XmlElement xe3){
		return null;
	}

	/**
	 * 
	 * @param xe1
	 * @param xe2
	 */
	public XmlElement AndNonNullExpressions(XmlElement xe1, XmlElement xe2){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param nOccurrences
	 * @param strBusOb
	 * @param strRelationshipName
	 * @param strLinkFieldOrPurpose
	 * @param xeSearchCriteria
	 */
	private XmlElement BuildOccurrencesTag(String strType, int nOccurrences, String strBusOb, String strRelationshipName, String strLinkFieldOrPurpose, XmlElement xeSearchCriteria){
		return null;
	}

	/**
	 * 
	 * @param strBusOb
	 * @param strRelationshipName
	 * @param strLinkFieldOrPurpose
	 * @param xeSearchCriteria
	 */
	public XmlElement BusObAddLink(String strBusOb, String strRelationshipName, String strLinkFieldOrPurpose, XmlElement xeSearchCriteria){
		return null;
	}

	/**
	 * 
	 * @param strBusOb
	 * @param strRelationshipName
	 * @param strLinkFieldOrPurpose
	 * @param xeSearchCriteria
	 */
	public XmlElement BusObAllOccurrences(String strBusOb, String strRelationshipName, String strLinkFieldOrPurpose, XmlElement xeSearchCriteria){
		return null;
	}

	/**
	 * 
	 * @param nOccurrences
	 * @param strBusOb
	 * @param strRelationshipName
	 * @param strLinkFieldOrPurpose
	 * @param xeSearchCriteria
	 */
	public XmlElement BusObAtLeastNumOccurrences(int nOccurrences, String strBusOb, String strRelationshipName, String strLinkFieldOrPurpose, XmlElement xeSearchCriteria){
		return null;
	}

	/**
	 * 
	 * @param nOccurrences
	 * @param strBusOb
	 * @param strRelationshipName
	 * @param strLinkFieldOrPurpose
	 * @param xeSearchCriteria
	 */
	public XmlElement BusObExactOccurrences(int nOccurrences, String strBusOb, String strRelationshipName, String strLinkFieldOrPurpose, XmlElement xeSearchCriteria){
		return null;
	}

	/**
	 * 
	 * @param strIdFieldName
	 * @param lstBusObKeys
	 */
	public XmlElement BusObInKeyList(String strIdFieldName, IBusObKeyList lstBusObKeys){
		return null;
	}

	/**
	 * 
	 * @param strIdFieldName
	 * @param colBusObKeys
	 */
	public XmlElement BusObInKeyList(String strIdFieldName, List colBusObKeys){
		return null;
	}

	/**
	 * 
	 * @param strBusOb
	 * @param strRelationshipName
	 * @param strLinkFieldOrPurpose
	 * @param xeSearchCriteria
	 */
	public XmlElement BusObNoOccurrences(String strBusOb, String strRelationshipName, String strLinkFieldOrPurpose, XmlElement xeSearchCriteria){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param opToUse
	 * @param eValueType
	 * @param strValue
	 */
	private String CheckExpression(String strField, Operators opToUse, ValueSources eValueType, String strValue){
		return "";
	}

	/**
	 * 
	 * @param strConnector
	 * @param axeExpressions
	 */
	private XmlElement ConnectExpressions(String strConnector, XmlElement[] axeExpressions){
		return null;
	}

	/**
	 * 
	 * @param strConnector
	 * @param xe1
	 * @param xe2
	 */
	private XmlElement ConnectExpressions(String strConnector, XmlElement xe1, XmlElement xe2){
		return null;
	}

	/**
	 * 
	 * @param strConnector
	 * @param xe1
	 * @param xe2
	 * @param xe3
	 */
	private XmlElement ConnectExpressions(String strConnector, XmlElement xe1, XmlElement xe2, XmlElement xe3){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param opToUse
	 * @param eValueType
	 * @param strValue
	 * @param strSearchParamName
	 * @param strSearchParamCategory
	 */
	private XmlElement CreateExpression(String strField, Operators opToUse, ValueSources eValueType, String strValue, String strSearchParamName, String strSearchParamCategory){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param strListType
	 */
	private XmlElement CreateListExpression(String strField, String strListType){
		return null;
	}

	/**
	 * 
	 * @param xeFunction
	 * @param strListType
	 */
	private XmlElement CreateQueryFunctionListExpression(XmlElement xeFunction, String strListType){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public static ISearchParameter CreateSearchParameter(String strName){
		return null;
	}

	/**
	 * 
	 * @param strField1
	 * @param opToUse
	 * @param strField2
	 */
	public XmlElement FieldAndFieldExpression(String strField1, Operators opToUse, String strField2){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param opToUse
	 * @param strFunction
	 */
	public XmlElement FieldAndFunctionExpression(String strField, Operators opToUse, String strFunction){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param opToUse
	 * @param strRule
	 */
	public XmlElement FieldAndRuleExpression(String strField, Operators opToUse, String strRule){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param opToUse
	 * @param strToken
	 */
	public XmlElement FieldAndTokenExpression(String strField, Operators opToUse, String strToken){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param opToUse
	 */
	public XmlElement FieldAndValueExpression(String strField, Operators opToUse){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param opToUse
	 * @param strValue
	 */
	public XmlElement FieldAndValueExpression(String strField, Operators opToUse, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param opToUse
	 * @param strValue
	 * @param searchParameter
	 */
	public XmlElement FieldAndValueExpression(String strField, Operators opToUse, String strValue, ISearchParameter searchParameter){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param opToUse
	 * @param strValue
	 * @param strSearchParamName
	 * @param strSearchParameterCategoryType
	 */
	public XmlElement FieldAndValueExpression(String strField, Operators opToUse, String strValue, String strSearchParamName, String strSearchParameterCategoryType){
		return null;
	}

	/**
	 * 
	 * @param strField
	 */
	public XmlElement FieldBetweenExpression(String strField){
		return null;
	}

	/**
	 * 
	 * @param strField
	 */
	public XmlElement FieldInExpression(String strField){
		return null;
	}

	/**
	 * 
	 * @param strField
	 */
	public XmlElement FieldNotBetweenExpression(String strField){
		return null;
	}

	/**
	 * 
	 * @param strField
	 */
	public XmlElement FieldNotInExpression(String strField){
		return null;
	}

	/**
	 * 
	 * @param strTargetParamName
	 */
	private XmlElement FindSearchParameterInXml(String strTargetParamName){
		return null;
	}

	/**
	 * 
	 * @param xeExpression
	 * @param strTargetSearchParamName
	 * @param xeTargetExpression
	 */
	private void FindSimpleExpressionDependingOnType(XmlElement xeExpression, String strTargetSearchParamName, XmlElement xeTargetExpression){

	}

	/**
	 * 
	 * @param xeConnectedExp
	 * @param strTargetSearchParamName
	 * @param xeTargetExpression
	 */
	private void FindSimpleExpressionInConnectedExpressions(XmlElement xeConnectedExp, String strTargetSearchParamName, XmlElement xeTargetExpression){

	}

	/**
	 * 
	 * @param xeOccurencesExp
	 * @param strTargetSearchParamName
	 * @param xeTargetExpression
	 */
	private void FindSimpleExpressionInOccurencesExpressions(XmlElement xeOccurencesExp, String strTargetSearchParamName, XmlElement xeTargetExpression){

	}

	/**
	 * 
	 * @param strTargetSearchParamName
	 */
	private XmlElement FindSimpleExpressionWithParam(String strTargetSearchParamName){
		return null;
	}

	/**
	 * 
	 * @param xeExpression
	 * @param strTargetSearchParamName
	 * @param xeTargetExpression
	 */
	public void FindSimpleExpressionWithParam(XmlElement xeExpression, String strTargetSearchParamName, XmlElement xeTargetExpression){

	}

	public XmlElement GetCriteriaElement(){
		return null;
	}

	/**
	 * 
	 * @param xeConnectedExp
	 * @param strOperator
	 * @param nlExpressions
	 */
	public void GetInfoFromConnectedExpression(XmlElement xeConnectedExp, String strOperator, XmlNodeList nlExpressions){

	}

	/**
	 * 
	 * @param xeExpression
	 * @param strField
	 * @param eOperator
	 * @param eValueType
	 * @param strValue
	 */
	public void GetInfoFromExpression(XmlElement xeExpression, String strField, Operators eOperator, ValueSources eValueType, String strValue){

	}

	/**
	 * 
	 * @param xeExpression
	 * @param strField
	 * @param eOperator
	 * @param eValueType
	 * @param strValue
	 * @param strSearchParamName
	 */
	public void GetInfoFromExpression(XmlElement xeExpression, String strField, Operators eOperator, ValueSources eValueType, String strValue, String strSearchParamName){

	}

	/**
	 * 
	 * @param xeListExpression
	 * @param strField
	 * @param strOperator
	 * @param nlValues
	 */
	public void GetInfoFromListExpression(XmlElement xeListExpression, String strField, String strOperator, XmlNodeList nlValues){

	}

	/**
	 * 
	 * @param xeValue
	 * @param eValueType
	 * @param strValue
	 */
	public void GetInfoFromListExpressionValue(XmlElement xeValue, ValueSources eValueType, String strValue){

	}

	/**
	 * 
	 * @param xeExpression
	 * @param strType
	 * @param nOccurrences
	 * @param strBusOb
	 * @param strRelationshipName
	 * @param strLinkFieldOrPurpose
	 * @param xeSearchCriteria
	 */
	public void GetInfoFromOccurrencesExpression(XmlElement xeExpression, String strType, int nOccurrences, String strBusOb, String strRelationshipName, String strLinkFieldOrPurpose, XmlElement xeSearchCriteria){

	}

	/**
	 * 
	 * @param xeExpression
	 * @param eOperator
	 * @param xeStartFunctionOrValue
	 * @param xeFunctionOrValue
	 */
	public void GetInfoFromQueryFunctionExpression(XmlElement xeExpression, Operators eOperator, XmlElement xeStartFunctionOrValue, XmlElement xeFunctionOrValue){

	}

	/**
	 * 
	 * @param xeListExpression
	 * @param xeCompareFunction
	 * @param strOperator
	 * @param colValues
	 */
	public void GetInfoFromQueryFunctionListExpression(XmlElement xeListExpression, XmlElement xeCompareFunction, String strOperator, List colValues){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param xeCriteria
	 */
	public XmlElement GetRootElementOfSearchCriteria(XmlElement xeCriteria){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Object GetSearchParameter(String strName){
		return null;
	}

	public Map GetSearchParameters(){
		return null;
	}

	/**
	 * 
	 * @param eValueType
	 */
	private String GetStringFromValueType(ValueSources eValueType){
		return "";
	}

	/**
	 * 
	 * @param xeExpression
	 */
	public ExpressionType GetTypeOfExpression(XmlElement xeExpression){
		return null;
	}

	/**
	 * 
	 * @param xeSearchCriteria
	 */
	public XmlElement ImportSearchCriteria(XmlElement xeSearchCriteria){
		return null;
	}

	/**
	 * 
	 * @param strOperator
	 */
	private boolean IsOperatorBetweenOrIn(String strOperator){
		return null;
	}

	/**
	 * 
	 * @param exParameterDef
	 */
	private boolean IsSearchParameter(XmlElement exParameterDef){
		return null;
	}

	/**
	 * 
	 * @param exParameterDef
	 */
	private boolean IsValidatedSearchParameter(XmlElement exParameterDef){
		return null;
	}

	/**
	 * 
	 * @param axeExpressions
	 */
	public XmlElement OrExpressions(XmlElement[] axeExpressions){
		return null;
	}

	/**
	 * 
	 * @param xe1
	 * @param xe2
	 */
	public XmlElement OrExpressions(XmlElement xe1, XmlElement xe2){
		return null;
	}

	/**
	 * 
	 * @param xe1
	 * @param xe2
	 * @param xe3
	 */
	public XmlElement OrExpressions(XmlElement xe1, XmlElement xe2, XmlElement xe3){
		return null;
	}

	public Fusion.QueryFunction QueryFunction(){
		return null;
	}

	/**
	 * 
	 * @param xeFunction
	 */
	public XmlElement QueryFunctionBetweenExpression(XmlElement xeFunction){
		return null;
	}

	/**
	 * 
	 * @param xeQueryFunction1
	 * @param opToUse
	 * @param xeQueryFunction2
	 */
	public XmlElement QueryFunctionExpression(XmlElement xeQueryFunction1, Operators opToUse, XmlElement xeQueryFunction2){
		return null;
	}

	/**
	 * 
	 * @param eValueSources
	 * @param strValue
	 * @param opToUse
	 * @param xeQueryFunction
	 */
	public XmlElement QueryFunctionExpression(ValueSources eValueSources, String strValue, Operators opToUse, XmlElement xeQueryFunction){
		return null;
	}

	/**
	 * 
	 * @param xeQueryFunction
	 * @param opToUse
	 * @param eValueSources
	 * @param strValue
	 */
	public XmlElement QueryFunctionExpression(XmlElement xeQueryFunction, Operators opToUse, ValueSources eValueSources, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeFunction
	 */
	public XmlElement QueryFunctionInExpression(XmlElement xeFunction){
		return null;
	}

	/**
	 * 
	 * @param xeFunction
	 * @param strOperator
	 */
	public XmlElement QueryFunctionListExpression(XmlElement xeFunction, String strOperator){
		return null;
	}

	/**
	 * 
	 * @param xeFunction
	 */
	public XmlElement QueryFunctionNotBetweenExpression(XmlElement xeFunction){
		return null;
	}

	/**
	 * 
	 * @param xeFunction
	 */
	public XmlElement QueryFunctionNotInExpression(XmlElement xeFunction){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param strListType
	 */
	public XmlElement QueryListExpression(String strField, String strListType){
		return null;
	}

	private void RefreshParameterListInDictionary(){

	}

	private void RefreshParameterListInXml(){

	}

	/**
	 * 
	 * @param newSearchParameters
	 */
	public void ReloadSearchParameters(List newSearchParameters){

	}

	/**
	 * 
	 * @param strName
	 */
	public void RemoveSearchParameter(String strName){

	}

	/**
	 * 
	 * @param searchParameter
	 */
	private void RemoveSearchParameterInXml(ISearchParameter searchParameter){

	}

	/**
	 * 
	 * @param searchParameterName
	 */
	private void RemoveSearchParameterInXml(String searchParameterName){

	}

	/**
	 * 
	 * @param xeExpression
	 */
	private void RemoveSearchParameterNameInSimpleExpression(XmlElement xeExpression){

	}

	/**
	 * 
	 * @param xeExpression
	 * @param strSearchParamName
	 */
	private void SetSearchParameterNameInSimpleExpression(XmlElement xeExpression, String strSearchParamName){

	}

	/**
	 * 
	 * @param strSearchParamName
	 * @param strValue
	 */
	private void SetSimpleExpressionValue(String strSearchParamName, String strValue){

	}

	/**
	 * 
	 * @param xeExpression
	 * @param strValue
	 */
	public void SetSimpleExpressionValue(XmlElement xeExpression, String strValue){

	}

	/**
	 * 
	 * @param parameterName
	 * @param executionValue
	 */
	public void UpdateParameterValue(String parameterName, Object executionValue){

	}

	/**
	 * 
	 * @param strName
	 * @param value
	 */
	public void UpdateSearchParameter(String strName, Object value){

	}

	/**
	 * 
	 * @param searchParameter
	 */
	private void UpdateSearchParameterInXml(ISearchParameter searchParameter){

	}

}