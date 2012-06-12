package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:55
 */
public interface ISecurityGroup {

	/**
	 * 
	 * @param strPath
	 * @param kbRight
	 */
	public void AddKBRight(String strPath, KBAccessRight kbRight);

	/**
	 * 
	 * @param strRole
	 */
	public void AddRole(String strRole);

	public void ClearKBRights();

	public void ClearRoles();

	public ISecurityGroup CopyForEdit();

	/**
	 * 
	 * @param category
	 * @param strRightsSetName
	 */
	public void DeleteRightsSet(SecurityCategory category, String strRightsSetName);

	/**
	 * 
	 * @param category
	 * @param strRightsSetName
	 * @param strRightsSetItemName
	 */
	public void DeleteRightsSetItem(SecurityCategory category, String strRightsSetName, String strRightsSetItemName);

	public String Description();

	/**
	 * 
	 * @param strBusObName
	 */
	public IBusObSecurity GetBusObSecurity(String strBusObName);

	/**
	 * 
	 * @param category
	 * @param strName
	 */
	public IDictionaryEnumerator GetExtendedSecurities(SecurityCategory category, String strName);

	/**
	 * 
	 * @param category
	 * @param strName
	 * @param strExtendedSecurityName
	 */
	public String GetExtendedSecurity(SecurityCategory category, String strName, String strExtendedSecurityName);

	/**
	 * 
	 * @param strModuleSecurityName
	 * @param strModuleItemSecurityName
	 */
	public String GetModuleItemDescription(String strModuleSecurityName, String strModuleItemSecurityName);

	/**
	 * 
	 * @param strModuleSecurityName
	 * @param strModuleItemSecurityName
	 */
	public String GetModuleItemFalseVerb(String strModuleSecurityName, String strModuleItemSecurityName);

	/**
	 * 
	 * @param strModuleSecurityName
	 * @param strModuleItemSecurityName
	 */
	public ModuleItemRightCategory GetModuleItemRightCategory(String strModuleSecurityName, String strModuleItemSecurityName);

	/**
	 * 
	 * @param strModuleSecurityName
	 * @param strModuleItemSecurityName
	 */
	public String GetModuleItemSecurityAlias(String strModuleSecurityName, String strModuleItemSecurityName);

	/**
	 * 
	 * @param strModuleSecurityName
	 */
	public string[] GetModuleItemSecurityNames(String strModuleSecurityName);

	/**
	 * 
	 * @param strModuleSecurityName
	 * @param strModuleItemSecurityName
	 */
	public String GetModuleItemTrueVerb(String strModuleSecurityName, String strModuleItemSecurityName);

	/**
	 * 
	 * @param strModuleSecurityName
	 * @param strModuleItemSecurityName
	 */
	public String GetModuleItemViewVerb(String strModuleSecurityName, String strModuleItemSecurityName);

	/**
	 * 
	 * @param strBusObName
	 */
	public String GetSecurityCriteria(String strBusObName);

	/**
	 * 
	 * @param right
	 */
	public boolean HasAccessSecurityGroupRight(SecurityRight right);

	/**
	 * 
	 * @param strBusObName
	 * @param right
	 */
	public boolean HasBusObFieldDefaultRight(String strBusObName, SecurityRight right);

	/**
	 * 
	 * @param strBusObName
	 * @param strFieldName
	 * @param right
	 */
	public boolean HasBusObFieldRight(String strBusObName, String strFieldName, SecurityRight right);

	/**
	 * 
	 * @param strBusObName
	 * @param right
	 */
	public boolean HasBusObRight(String strBusObName, SecurityRight right);

	/**
	 * 
	 * @param strBusObName
	 * @param bView
	 * @param bAdd
	 * @param bEdit
	 * @param bDelete
	 * @param bCanEditInFinalState
	 * @param bCanChangeFromFinalToRecallState
	 */
	public void HasBusObRights(String strBusObName, boolean bView, boolean bAdd, boolean bEdit, boolean bDelete, boolean bCanEditInFinalState, boolean bCanChangeFromFinalToRecallState);

	/**
	 * 
	 * @param right
	 */
	public boolean HasDefaultBusObFieldRight(SecurityRight right);

	/**
	 * 
	 * @param right
	 */
	public boolean HasDefaultBusObRight(SecurityRight right);

	/**
	 * 
	 * @param right
	 */
	public boolean HasDefaultRelationshipRight(SecurityRight right);

	/**
	 * 
	 * @param strModuleItemSecurityName
	 * @param right
	 */
	public boolean HasModuleItemRight(String strModuleItemSecurityName, SecurityRight right);

	/**
	 * 
	 * @param strModuleSecurityName
	 * @param strModuleItemSecurityName
	 * @param right
	 */
	public boolean HasModuleItemRight(String strModuleSecurityName, String strModuleItemSecurityName, SecurityRight right);

	/**
	 * 
	 * @param strRelationshipName
	 * @param right
	 */
	public boolean HasRelationshipRight(String strRelationshipName, SecurityRight right);

	/**
	 * 
	 * @param strRelationshipName
	 * @param bView
	 * @param bAdd
	 * @param bEdit
	 * @param bDelete
	 */
	public void HasRelationshipRight(String strRelationshipName, boolean bView, boolean bAdd, boolean bEdit, boolean bDelete);

	public String Id();

	public boolean IsAdministrator();

	public List KBRightList();

	public String Name();

	/**
	 * 
	 * @param strBusObName
	 * @param right
	 */
	public void RemoveBusObFieldDefaultRight(String strBusObName, SecurityRight right);

	/**
	 * 
	 * @param strBusObName
	 * @param strFieldName
	 * @param right
	 */
	public void RemoveBusObFieldRight(String strBusObName, String strFieldName, SecurityRight right);

	/**
	 * 
	 * @param strBusObName
	 * @param right
	 */
	public void RemoveBusObRight(String strBusObName, SecurityRight right);

	/**
	 * 
	 * @param right
	 */
	public void RemoveDefaultBusObFieldRight(SecurityRight right);

	/**
	 * 
	 * @param right
	 */
	public void RemoveDefaultBusObRight(SecurityRight right);

	/**
	 * 
	 * @param right
	 */
	public void RemoveDefaultRelationshipRight(SecurityRight right);

	/**
	 * 
	 * @param category
	 * @param strName
	 * @param strExtendedSecurityName
	 */
	public void RemoveExtendedSecurity(SecurityCategory category, String strName, String strExtendedSecurityName);

	/**
	 * 
	 * @param strModuleSecurityName
	 * @param strModuleItemSecurityName
	 * @param right
	 */
	public void RemoveModuleItemRight(String strModuleSecurityName, String strModuleItemSecurityName, SecurityRight right);

	/**
	 * 
	 * @param strRelationshipName
	 * @param right
	 */
	public void RemoveRelationshipRight(String strRelationshipName, SecurityRight right);

	/**
	 * 
	 * @param strRole
	 */
	public void RemoveRole(String strRole);

	/**
	 * 
	 * @param strBusObName
	 */
	public void RemoveSecurityCriteria(String strBusObName);

	/**
	 * 
	 * @param strBusObName
	 */
	public void ResetBusObRights(String strBusObName);

	/**
	 * 
	 * @param strBusObName
	 */
	public void ResetDefaultFieldRights(String strBusObName);

	/**
	 * 
	 * @param strBusObName
	 * @param strFieldName
	 */
	public void ResetFieldRights(String strBusObName, String strFieldName);

	/**
	 * 
	 * @param strRelationshipName
	 */
	public void ResetRelationshipRights(String strRelationshipName);

	public List RoleList();

	/**
	 * 
	 * @param strBusObName
	 * @param right
	 */
	public void SetBusObFieldDefaultRight(String strBusObName, SecurityRight right);

	/**
	 * 
	 * @param strBusObName
	 * @param strFieldName
	 * @param right
	 */
	public void SetBusObFieldRight(String strBusObName, String strFieldName, SecurityRight right);

	/**
	 * 
	 * @param strBusObName
	 * @param right
	 */
	public void SetBusObRight(String strBusObName, SecurityRight right);

	/**
	 * 
	 * @param right
	 */
	public void SetDefaultBusObFieldRight(SecurityRight right);

	/**
	 * 
	 * @param right
	 */
	public void SetDefaultBusObRight(SecurityRight right);

	/**
	 * 
	 * @param right
	 */
	public void SetDefaultRelationshipRight(SecurityRight right);

	/**
	 * 
	 * @param category
	 * @param strName
	 * @param strExtendedSecurityName
	 * @param strExtendedSecurityValue
	 */
	public void SetExtendedSecurity(SecurityCategory category, String strName, String strExtendedSecurityName, String strExtendedSecurityValue);

	/**
	 * 
	 * @param strModuleSecurityName
	 * @param strModuleItemSecurityName
	 * @param right
	 */
	public void SetModuleItemRight(String strModuleSecurityName, String strModuleItemSecurityName, SecurityRight right);

	/**
	 * 
	 * @param strRelationshipName
	 * @param right
	 */
	public void SetRelationshipRight(String strRelationshipName, SecurityRight right);

	/**
	 * 
	 * @param strBusObName
	 * @param strSecurityCriteria
	 */
	public void SetSecurityCriteria(String strBusObName, String strSecurityCriteria);

	public String ToString();

	/**
	 * 
	 * @param strBusObName
	 */
	public boolean UseDefaultBusObFieldRights(String strBusObName);

	/**
	 * 
	 * @param strBusObName
	 */
	public boolean UseDefaultBusObRights(String strBusObName);

	/**
	 * 
	 * @param strBusObName
	 * @param strFieldName
	 */
	public boolean UseDefaultFieldRights(String strBusObName, String strFieldName);

	/**
	 * 
	 * @param strRelationshipName
	 */
	public boolean UseDefaultRelationshipRights(String strRelationshipName);

}