package Fusion.Api;

import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:24
 */
public class ApplicationDefinitionRepository extends AggregateUser implements IAdr {

	private Fusion.Application.ApplicationDefinitionRepository m_RealAdr = null;

	public ApplicationDefinitionRepository(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param realAdr
	 */
	public ApplicationDefinitionRepository(Fusion.Application.ApplicationDefinitionRepository realAdr){

	}

	/**
	 * 
	 * @param defNew
	 */
	public boolean AddNewDefinition(IDefinition defNew){
		return false;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 */
	public void ClearCache(Scope scopeType, String strScopeOwner, String strDefClassName){

	}

	/**
	 * 
	 * @param strDefClassName
	 */
	private void ConfirmQueryAllowed(String strDefClassName){

	}

	/**
	 * 
	 * @param strDefClassName
	 */
	public IDefinition CreateDefinitionForEditing(String strDefClassName){
		return null;
	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strSubType
	 */
	public IDefinition CreateDefinitionForEditing(String strDefClassName, String strSubType){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 */
	public IDefinition CreateDefinitionForEditing(Scope scopeType, String strScopeOwner, String strDefClassName){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 * @param strSubType
	 */
	public IDefinition CreateDefinitionForEditing(Scope scopeType, String strScopeOwner, String strDefClassName, String strSubType){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strDefClassName
	 */
	public IDefinition CreateDefinitionForEditingAutoOwner(Scope scopeType, String strDefClassName){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strDefClassName
	 * @param strSubType
	 */
	public IDefinition CreateDefinitionForEditingAutoOwner(Scope scopeType, String strDefClassName, String strSubType){
		return null;
	}

	/**
	 * 
	 * @param defToDelete
	 */
	public boolean DeleteDefinition(IDefinition defToDelete){
		return false;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 * @param strPerspective
	 */
	public List GetAllDefinitionPlaceHolderList(Scope scopeType, String strScopeOwner, String strDefClassName, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param holder
	 */
	public IDefinition GetDefinition(PlaceHolder holder){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 * @param strName
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinition(Scope scopeType, String strScopeOwner, String strDefClassName, String strName, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strName
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinition(Scope scopeType, String strScopeOwner, String strLinkedTo, String strDefClassName, String strName, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strName
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionAutoOwner(Scope scopeType, String strLinkedTo, String strDefClassName, String strName, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 * @param strId
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionById(Scope scopeType, String strScopeOwner, String strDefClassName, String strId, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strId
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionById(Scope scopeType, String strScopeOwner, String strLinkedTo, String strDefClassName, String strId, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strId
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionByIdAutoOwner(Scope scopeType, String strLinkedTo, String strDefClassName, String strId, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param holder
	 */
	public IDefinition GetDefinitionForEditing(PlaceHolder holder){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strName
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionForEditing(Scope scopeType, String strScopeOwner, String strLinkedTo, String strDefClassName, String strName, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strName
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionForEditingAutoOwner(Scope scopeType, String strLinkedTo, String strDefClassName, String strName, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strId
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionForEditingById(Scope scopeType, String strScopeOwner, String strLinkedTo, String strDefClassName, String strId, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strId
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionForEditingByIdAutoOwner(Scope scopeType, String strLinkedTo, String strDefClassName, String strId, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 */
	public List GetDefinitionPlaceHolderList(Scope scopeType, String strScopeOwner, String strDefClassName){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strDefClassName
	 */
	public List GetDefinitionPlaceHolderList(Scope scopeType, String strScopeOwner, String strLinkedTo, String strDefClassName){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strLinkedTo
	 * @param strDefClassName
	 */
	public List GetDefinitionPlaceHolderListAutoOwner(Scope scopeType, String strLinkedTo, String strDefClassName){
		return null;
	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strName
	 */
	public IDefinition GetInternalDefinition(String strDefClassName, String strName){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 * @param strModuleName
	 */
	public List GetModuleDefinitionPlaceHolderList(Scope scopeType, String strScopeOwner, String strDefClassName, String strModuleName){
		return null;
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strModuleName
	 */
	public List GetModuleDefinitionPlaceHolderList(Scope scopeType, String strScopeOwner, String strLinkedTo, String strDefClassName, String strModuleName){
		return null;
	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param scopeType
	 * @param strAliasToCheck
	 */
	public boolean IsDuplicateAlias(String strDefClassName, String strId, Scope scopeType, String strAliasToCheck){
		return false;
	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strAliasToCheck
	 */
	public boolean IsDuplicateAlias(String strDefClassName, String strId, Scope scopeType, String strScopeOwner, String strAliasToCheck){
		return false;
	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param scopeType
	 * @param strNameToCheck
	 */
	public boolean IsDuplicateName(String strDefClassName, String strId, Scope scopeType, String strNameToCheck){
		return false;
	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strNameToCheck
	 */
	public boolean IsDuplicateName(String strDefClassName, String strId, Scope scopeType, String strScopeOwner, String strNameToCheck){
		return false;
	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param scopeType
	 * @param strNameToCheck
	 * @param strAliasToCheck
	 * @param bDuplicateName
	 * @param bDuplicateAlias
	 */
	public void IsDuplicateNameAlias(String strDefClassName, String strId, Scope scopeType, String strNameToCheck, String strAliasToCheck, boolean bDuplicateName, boolean bDuplicateAlias){

	}

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strNameToCheck
	 * @param strAliasToCheck
	 * @param bDuplicateName
	 * @param bDuplicateAlias
	 */
	public void IsDuplicateNameAlias(String strDefClassName, String strId, Scope scopeType, String strScopeOwner, String strNameToCheck, String strAliasToCheck, boolean bDuplicateName, boolean bDuplicateAlias){

	}

	public Fusion.Application.ApplicationDefinitionRepository RealAdr(){
		return null;
	}

	public List RegisteredModules(){
		return null;
	}

	/**
	 * 
	 * @param defNewVersion
	 */
	public boolean UpdateDefinition(IDefinition defNewVersion){
		return false;
	}

	/**
	 * 
	 * @param defNewVersion
	 * @param bCreateNewOnScopeChange
	 */
	public boolean UpdateDefinition(IDefinition defNewVersion, boolean bCreateNewOnScopeChange){
		return false;
	}

}

