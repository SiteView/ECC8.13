package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:59
 */
public class Definitions implements IDefinitions {

	private IOrchestrator m_orch = null;

	public Definitions(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param orch
	 */
	public Definitions(IOrchestrator orch){

	}

	public List BusinessObjectNames(){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.LoginProcedureDef GetAggregate(Fusion.Asd.LoginProcedureDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.BusinessObjectDef GetAggregate(Fusion.BusinessLogic.BusinessObjectDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.CounterDef GetAggregate(Fusion.BusinessLogic.CounterDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.FieldDef GetAggregate(Fusion.BusinessLogic.FieldDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.FormatDef GetAggregate(Fusion.BusinessLogic.FormatDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.PerspectiveDef GetAggregate(Fusion.BusinessLogic.PerspectiveDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.RelationshipDef GetAggregate(Fusion.BusinessLogic.RelationshipDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.RuleDef GetAggregate(Fusion.BusinessLogic.Rules.RuleDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.TokenDef GetAggregate(Fusion.BusinessLogic.TokenDef def){
		return null;
	}

	/**
	 * 
	 * @param name
	 */
	public Fusion.Api.BusinessObjectDef GetBusinessObjectDef(String name){
		return null;
	}

	/**
	 * 
	 * @param id
	 */
	public Fusion.Api.BusinessObjectDef GetBusinessObjectDefById(String id){
		return null;
	}

	/**
	 * 
	 * @param storageName
	 */
	public Fusion.Api.BusinessObjectDef GetBusinessObjectDefByStorageName(String storageName){
		return null;
	}

	/**
	 * 
	 * @param FieldName
	 */
	public Fusion.Api.FieldDef GetBusinessObjectFieldDef(String FieldName){
		return null;
	}

	public List GetBusObPlaceHolderList(){
		return null;
	}

	/**
	 * 
	 * @param groupName
	 * @param includeBase
	 */
	public List GetBusObPlaceHolderListForGroup(String groupName, boolean includeBase){
		return null;
	}

	/**
	 * 
	 * @param name
	 */
	public List GetCombinedGroupFieldDefs(String name){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.CounterDef GetCounterDef(String strName){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public Fusion.Api.CounterDef GetCounterDefById(String strId){
		return null;
	}

	public List GetCounterPlaceHolderList(){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.FormatDef GetFormatDef(String strName){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public Fusion.Api.FormatDef GetFormatDefById(String strId){
		return null;
	}

	public List GetFormatPlaceHolderList(){
		return null;
	}

	/**
	 * 
	 * @param name
	 */
	public Fusion.Api.BusinessObjectDef GetGroupBusinessObject(String name){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.LoginProcedureDef GetLoginProcedureDef(String strName){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public Fusion.Api.LoginProcedureDef GetLoginProcedureDefById(String strId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.PerspectiveDef GetPerspectiveDef(String strName){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public Fusion.Api.PerspectiveDef GetPerspectiveDefById(String strId){
		return null;
	}

	public List GetPerspectivePlaceHolderList(){
		return null;
	}

	/**
	 * 
	 * @param definitionType
	 * @param name
	 */
	public PlaceHolder GetPlaceHolderForDefinition(String definitionType, String name){
		return null;
	}

	/**
	 * 
	 * @param definitionType
	 * @param id
	 */
	public PlaceHolder GetPlaceHolderForDefinitionById(String definitionType, String id){
		return null;
	}

	/**
	 * 
	 * @param RelationshipName
	 */
	public Fusion.Api.BusinessObjectDef GetRelatedBusinessObjectDef(String RelationshipName){
		return null;
	}

	/**
	 * 
	 * @param name
	 */
	public Fusion.Api.RelationshipDef GetRelationshipDef(String name){
		return null;
	}

	/**
	 * 
	 * @param id
	 */
	public Fusion.Api.RelationshipDef GetRelationshipDefById(String id){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.RuleDef GetRuleDef(String strName){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public Fusion.Api.RuleDef GetRuleDefById(String strId){
		return null;
	}

	public List GetRulePlaceHolderList(){
		return null;
	}

	public List GetSupportedDefinitionTypes(){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.TokenDef GetTokenDef(String strName){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public Fusion.Api.TokenDef GetTokenDefById(String strId){
		return null;
	}

	public List GetTokenPlaceHolderList(){
		return null;
	}

	public void InvalidateCache(){

	}

	public List MasterObjectNames(){
		return null;
	}

	public List RuleNames(){
		return null;
	}

}