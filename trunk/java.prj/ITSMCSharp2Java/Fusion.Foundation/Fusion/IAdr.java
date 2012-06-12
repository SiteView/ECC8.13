package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:42
 */
public interface IAdr {

	/**
	 * 
	 * @param defNew
	 */
	public boolean AddNewDefinition(IDefinition defNew);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 */
	public void ClearCache(Scope scopeType, String strScopeOwner, String strDefClassName);

	/**
	 * 
	 * @param strDefClassName
	 */
	public IDefinition CreateDefinitionForEditing(String strDefClassName);

	/**
	 * 
	 * @param strDefClassName
	 * @param strSubType
	 */
	public IDefinition CreateDefinitionForEditing(String strDefClassName, String strSubType);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 */
	public IDefinition CreateDefinitionForEditing(Scope scopeType, String strScopeOwner, String strDefClassName);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 * @param strSubType
	 */
	public IDefinition CreateDefinitionForEditing(Scope scopeType, String strScopeOwner, String strDefClassName, String strSubType);

	/**
	 * 
	 * @param scopeType
	 * @param strDefClassName
	 */
	public IDefinition CreateDefinitionForEditingAutoOwner(Scope scopeType, String strDefClassName);

	/**
	 * 
	 * @param scopeType
	 * @param strDefClassName
	 * @param strSubType
	 */
	public IDefinition CreateDefinitionForEditingAutoOwner(Scope scopeType, String strDefClassName, String strSubType);

	/**
	 * 
	 * @param defToDelete
	 */
	public boolean DeleteDefinition(IDefinition defToDelete);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 * @param strPerspective
	 */
	public List GetAllDefinitionPlaceHolderList(Scope scopeType, String strScopeOwner, String strDefClassName, String strPerspective);

	/**
	 * 
	 * @param holder
	 */
	public IDefinition GetDefinition(PlaceHolder holder);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 * @param strName
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinition(Scope scopeType, String strScopeOwner, String strDefClassName, String strName, boolean bStepUpChain);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strName
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinition(Scope scopeType, String strScopeOwner, String strLinkedTo, String strDefClassName, String strName, boolean bStepUpChain);

	/**
	 * 
	 * @param scopeType
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strName
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionAutoOwner(Scope scopeType, String strLinkedTo, String strDefClassName, String strName, boolean bStepUpChain);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 * @param strId
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionById(Scope scopeType, String strScopeOwner, String strDefClassName, String strId, boolean bStepUpChain);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strId
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionById(Scope scopeType, String strScopeOwner, String strLinkedTo, String strDefClassName, String strId, boolean bStepUpChain);

	/**
	 * 
	 * @param scopeType
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strId
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionByIdAutoOwner(Scope scopeType, String strLinkedTo, String strDefClassName, String strId, boolean bStepUpChain);

	/**
	 * 
	 * @param holder
	 */
	public IDefinition GetDefinitionForEditing(PlaceHolder holder);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strName
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionForEditing(Scope scopeType, String strScopeOwner, String strLinkedTo, String strDefClassName, String strName, boolean bStepUpChain);

	/**
	 * 
	 * @param scopeType
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strName
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionForEditingAutoOwner(Scope scopeType, String strLinkedTo, String strDefClassName, String strName, boolean bStepUpChain);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strId
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionForEditingById(Scope scopeType, String strScopeOwner, String strLinkedTo, String strDefClassName, String strId, boolean bStepUpChain);

	/**
	 * 
	 * @param scopeType
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strId
	 * @param bStepUpChain
	 */
	public IDefinition GetDefinitionForEditingByIdAutoOwner(Scope scopeType, String strLinkedTo, String strDefClassName, String strId, boolean bStepUpChain);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 */
	public List GetDefinitionPlaceHolderList(Scope scopeType, String strScopeOwner, String strDefClassName);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strDefClassName
	 */
	public List GetDefinitionPlaceHolderList(Scope scopeType, String strScopeOwner, String strLinkedTo, String strDefClassName);

	/**
	 * 
	 * @param scopeType
	 * @param strLinkedTo
	 * @param strDefClassName
	 */
	public List GetDefinitionPlaceHolderListAutoOwner(Scope scopeType, String strLinkedTo, String strDefClassName);

	/**
	 * 
	 * @param strDefClassName
	 * @param strName
	 */
	public IDefinition GetInternalDefinition(String strDefClassName, String strName);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strDefClassName
	 * @param strModuleName
	 */
	public List GetModuleDefinitionPlaceHolderList(Scope scopeType, String strScopeOwner, String strDefClassName, String strModuleName);

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strLinkedTo
	 * @param strDefClassName
	 * @param strModuleName
	 */
	public List GetModuleDefinitionPlaceHolderList(Scope scopeType, String strScopeOwner, String strLinkedTo, String strDefClassName, String strModuleName);

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param scopeType
	 * @param strAliasToCheck
	 */
	public boolean IsDuplicateAlias(String strDefClassName, String strId, Scope scopeType, String strAliasToCheck);

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strAliasToCheck
	 */
	public boolean IsDuplicateAlias(String strDefClassName, String strId, Scope scopeType, String strScopeOwner, String strAliasToCheck);

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param scopeType
	 * @param strNameToCheck
	 */
	public boolean IsDuplicateName(String strDefClassName, String strId, Scope scopeType, String strNameToCheck);

	/**
	 * 
	 * @param strDefClassName
	 * @param strId
	 * @param scopeType
	 * @param strScopeOwner
	 * @param strNameToCheck
	 */
	public boolean IsDuplicateName(String strDefClassName, String strId, Scope scopeType, String strScopeOwner, String strNameToCheck);

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
	public void IsDuplicateNameAlias(String strDefClassName, String strId, Scope scopeType, String strNameToCheck, String strAliasToCheck, boolean bDuplicateName, boolean bDuplicateAlias);

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
	public void IsDuplicateNameAlias(String strDefClassName, String strId, Scope scopeType, String strScopeOwner, String strNameToCheck, String strAliasToCheck, boolean bDuplicateName, boolean bDuplicateAlias);

	public List RegisteredModules();

	/**
	 * 
	 * @param defNewVersion
	 */
	public boolean UpdateDefinition(IDefinition defNewVersion);

	/**
	 * 
	 * @param defNewVersion
	 * @param bCreateNewOnScopeChange
	 */
	public boolean UpdateDefinition(IDefinition defNewVersion, boolean bCreateNewOnScopeChange);

}