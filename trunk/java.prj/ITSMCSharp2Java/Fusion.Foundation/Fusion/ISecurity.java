package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:55
 */
public interface ISecurity {

	/**
	 * 
	 * @param strGroupName
	 */
	public ISecurityGroup CreateSecurityGroup(String strGroupName);

	/**
	 * 
	 * @param strGroupId
	 */
	public void DeleteSecurityGroup(String strGroupId);

	/**
	 * 
	 * @param strBusObName
	 */
	public IBusObSecurity GetBusObSecurity(String strBusObName);

	/**
	 * 
	 * @param strStorageName
	 */
	public String GetBusObSecurityClauseForCrystal(String strStorageName);

	/**
	 * 
	 * @param strModuleSecurityName
	 */
	public String GetModuleSecurityAlias(String strModuleSecurityName);

	/**
	 * 
	 * @param strBusObName
	 */
	public String GetSecurityCriteria(String strBusObName);

	/**
	 * 
	 * @param strGroupId
	 * @param strBusObName
	 */
	public String GetSecurityCriteriaForGroup(String strGroupId, String strBusObName);

	/**
	 * 
	 * @param strGroupId
	 */
	public ISecurityGroup GetSecurityGroupCopyById(String strGroupId);

	/**
	 * 
	 * @param strGroupName
	 */
	public ISecurityGroup GetSecurityGroupCopyByName(String strGroupName);

	/**
	 * 
	 * @param strGroupName
	 */
	public String GetSecurityGroupIdByName(String strGroupName);

	/**
	 * 
	 * @param strGroupId
	 */
	public String GetSecurityGroupNameById(String strGroupId);

	public string[] GetSecurityGroupNames();

	/**
	 * 
	 * @param right
	 */
	public boolean HasAccessSecurityGroupRight(SecurityRight right);

	/**
	 * 
	 * @param strGroupId
	 * @param right
	 */
	public boolean HasAccessSecurityGroupRightForGroup(String strGroupId, SecurityRight right);

	/**
	 * 
	 * @param strBusObName
	 * @param strFieldName
	 * @param right
	 */
	public boolean HasBusObFieldRight(String strBusObName, String strFieldName, SecurityRight right);

	/**
	 * 
	 * @param strGroupId
	 * @param strBusObName
	 * @param strFieldName
	 * @param right
	 */
	public boolean HasBusObFieldRightForGroup(String strGroupId, String strBusObName, String strFieldName, SecurityRight right);

	/**
	 * 
	 * @param strBusObName
	 * @param right
	 */
	public boolean HasBusObRight(String strBusObName, SecurityRight right);

	/**
	 * 
	 * @param strGroupId
	 * @param strBusObName
	 * @param right
	 */
	public boolean HasBusObRightForGroup(String strGroupId, String strBusObName, SecurityRight right);

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
	 * @param strGroupId
	 * @param strModuleItemSecurityName
	 * @param right
	 */
	public boolean HasModuleItemRightForGroup(String strGroupId, String strModuleItemSecurityName, SecurityRight right);

	/**
	 * 
	 * @param strGroupId
	 * @param strModuleSecurityName
	 * @param strModuleItemSecurityName
	 * @param right
	 */
	public boolean HasModuleItemRightForGroup(String strGroupId, String strModuleSecurityName, String strModuleItemSecurityName, SecurityRight right);

	/**
	 * 
	 * @param strRelationshipName
	 * @param right
	 */
	public boolean HasRelationshipRight(String strRelationshipName, SecurityRight right);

	/**
	 * 
	 * @param strGroupId
	 * @param strRelationshipName
	 * @param right
	 */
	public boolean HasRelationshipRightForGroup(String strGroupId, String strRelationshipName, SecurityRight right);

	/**
	 * 
	 * @param iSecurityGroup
	 */
	public ISecurityGroup SaveSecurityGroup(ISecurityGroup iSecurityGroup);

}