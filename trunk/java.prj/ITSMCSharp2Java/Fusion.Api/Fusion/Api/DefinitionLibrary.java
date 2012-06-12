package Fusion.Api;

import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:54
 */
public class DefinitionLibrary extends AggregateUser implements IDefinitionLibrary {

	private Fusion.BusinessLogic.DefinitionLibrary m_RealDefinitionLibrary = null;

	public DefinitionLibrary(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param defLibrary
	 */
	public DefinitionLibrary(Fusion.BusinessLogic.DefinitionLibrary defLibrary){

	}

	/**
	 * 
	 * @param scopeType
	 */
	public String AutoScopeOwner(Scope scopeType){
		return "";
	}

	public void ClearAdrCache(){

	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 */
	public void ClearAdrCache(Scope scopeType, String strScopeOwner, String strDefClassName){

	}

	public void ClearMdrCache(){

	}

	/**
	 * 
	 * @param strType
	 * @param strXML
	 */
	public IDefinition CreateDefFromXml(String strType, String strXML){
		return null;
	}

	public Object FusionObject(){
		return null;
	}

	/**
	 * 
	 * @param req
	 */
	public List GetAllDefinitions(DefRequest req){
		return null;
	}

	public List GetAllPlaceHolders(){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strPerspective
	 */
	public List GetAllPlaceHolders(String strType, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param strBusObName
	 */
	public Fusion.Api.BusinessObjectDef GetBusinessObjectDef(String strBusObName){
		return null;
	}

	/**
	 * 
	 * @param strBusObName
	 * @param strPerspective
	 */
	public Fusion.Api.BusinessObjectDef GetBusinessObjectDef(String strBusObName, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param strQualifiedFieldName
	 */
	public Fusion.Api.FieldDef GetBusinessObjectFieldDef(String strQualifiedFieldName){
		return null;
	}

	/**
	 * 
	 * @param strQualifiedFieldName
	 * @param strPerspective
	 */
	public Fusion.Api.FieldDef GetBusinessObjectFieldDef(String strQualifiedFieldName, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.BusinessObjectDef GetCombinedGroupDef(String strName){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public List GetCombinedGroupFieldDefs(String strName){
		return null;
	}

	/**
	 * 
	 * @param req
	 */
	public IDefinition GetDefForEditing(DefRequest req){
		return null;
	}

	/**
	 * 
	 * @param req
	 */
	public IDefinition GetDefinition(DefRequest req){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strName
	 * @param bRetrieveBaseDef
	 * @param strPerspective
	 */
	public List GetDerivedDefsFromStore(String strType, String strName, boolean bRetrieveBaseDef, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param strGroupName
	 * @param strPerspective
	 * @param bIncludeParentOfGroup
	 */
	public List GetGroupPlaceHolderList(String strGroupName, String strPerspective, boolean bIncludeParentOfGroup){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strBaseObjectName
	 * @param bIncludeGroup
	 * @param bIncludeGroupLeader
	 */
	public List GetNamedPresentationPlaceHolderList(String strType, String strBaseObjectName, boolean bIncludeGroup, boolean bIncludeGroupLeader){
		return null;
	}

	/**
	 * 
	 * @param req
	 */
	public IDefinition GetNewDefForEditing(DefRequest req){
		return null;
	}

	/**
	 * 
	 * @param strPerspective
	 */
	public Fusion.Api.PerspectiveDef GetPerspectiveDef(String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param strType
	 */
	public Map GetPlaceHolderDict(String strType){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strPerspective
	 */
	public Map GetPlaceHolderDict(String strType, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param req
	 */
	public List GetPlaceHolderList(DefRequest req){
		return null;
	}

	/**
	 * 
	 * @param strAnnotation
	 * @param strPerspective
	 * @param bExceptionIfNotFound
	 */
	public PlaceHolder[] GetPlaceHoldersByAnnotation(String strAnnotation, String strPerspective, boolean bExceptionIfNotFound){
		return null;
	}

	public List GetSupportedAdrDefinitionTypes(){
		return null;
	}

	public String[] GetSupportedDefinitionTypes(){
		return "";
	}

	public List GetSupportedMdrDefinitionTypes(){
		return null;
	}

	/**
	 * 
	 * @param req
	 */
	public boolean IsDuplicateName(DefRequest req){
		return null;
	}

	/**
	 * 
	 * @param strType
	 */
	public boolean IsMdrType(String strType){
		return null;
	}

	/**
	 * 
	 * @param strType
	 */
	public boolean IsPerspectiveUsedForDefinition(String strType){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	public void MarkDefinitionForDeletion(IDefinition def){

	}

	public Fusion.BusinessLogic.DefinitionLibrary RealDefLibrary(){
		return null;
	}

	/**
	 * 
	 * @param req
	 */
	public void RevertDefinition(DefRequest req){

	}

	/**
	 * 
	 * @param def
	 */
	public void RevertDefinition(IDefinition def){

	}

	/**
	 * 
	 * @param defClassName
	 */
	public Scope[] SupportedScopes(String defClassName){
		return null;
	}

	/**
	 * 
	 * @param req
	 */
	public void UndeleteDefinition(DefRequest req){

	}

	public Object UnprotectedFusionObject(){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	public void UpdateDefinition(IDefinition def){

	}

	/**
	 * 
	 * @param def
	 * @param bCreateNewOnScopeChange
	 */
	public void UpdateDefinition(IDefinition def, boolean bCreateNewOnScopeChange){

	}

}