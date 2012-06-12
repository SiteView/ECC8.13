package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:32
 */
public class SecurityService extends ISecurity {

	private ISecurity m_iSecService = null;

	public SecurityService(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param iSecService
	 */
	public SecurityService(ISecurity iSecService){

	}

	/**
	 * 
	 * @param strGroupName
	 */
	public ISecurityGroup CreateSecurityGroup(String strGroupName){
		return null;
	}

	/**
	 * 
	 * @param strGroupId
	 */
	public void DeleteSecurityGroup(String strGroupId){

	}

	/**
	 * 
	 * @param strBusObName
	 */
	public IBusObSecurity GetBusObSecurity(String strBusObName){
		return null;
	}

	/**
	 * 
	 * @param strStorageName
	 */
	public String GetBusObSecurityClauseForCrystal(String strStorageName){
		return "";
	}

	/**
	 * 
	 * @param strModuleSecurityName
	 */
	public String GetModuleSecurityAlias(String strModuleSecurityName){
		return "";
	}

	/**
	 * 
	 * @param strBusObName
	 */
	public String GetSecurityCriteria(String strBusObName){
		return "";
	}

	/**
	 * 
	 * @param strGroupId
	 * @param strBusObName
	 */
	public String GetSecurityCriteriaForGroup(String strGroupId, String strBusObName){
		return "";
	}

	/**
	 * 
	 * @param strGroupId
	 */
	public ISecurityGroup GetSecurityGroupCopyById(String strGroupId){
		return null;
	}

	/**
	 * 
	 * @param strGroupName
	 */
	public ISecurityGroup GetSecurityGroupCopyByName(String strGroupName){
		return null;
	}

	/**
	 * 
	 * @param strGroupName
	 */
	public String GetSecurityGroupIdByName(String strGroupName){
		return "";
	}

	/**
	 * 
	 * @param strGroupId
	 */
	public String GetSecurityGroupNameById(String strGroupId){
		return "";
	}

	public String[] GetSecurityGroupNames(){
		return null;
	}

	/**
	 * 
	 * @param right
	 */
	public boolean HasAccessSecurityGroupRight(SecurityRight right){
		return false;
	}

	/**
	 * 
	 * @param strGroupId
	 * @param right
	 */
	public boolean HasAccessSecurityGroupRightForGroup(String strGroupId, SecurityRight right){
		return false;
	}

	/**
	 * 
	 * @param strBusObName
	 * @param strFieldName
	 * @param right
	 */
	public boolean HasBusObFieldRight(String strBusObName, String strFieldName, SecurityRight right){
		return false;
	}

	/**
	 * 
	 * @param strGroupId
	 * @param strBusObName
	 * @param strFieldName
	 * @param right
	 */
	public boolean HasBusObFieldRightForGroup(String strGroupId, String strBusObName, String strFieldName, SecurityRight right){
		return false;
	}

	/**
	 * 
	 * @param strBusObName
	 * @param right
	 */
	public boolean HasBusObRight(String strBusObName, SecurityRight right){
		return false;
	}

	/**
	 * 
	 * @param strGroupId
	 * @param strBusObName
	 * @param right
	 */
	public boolean HasBusObRightForGroup(String strGroupId, String strBusObName, SecurityRight right){
		return false;
	}

	/**
	 * 
	 * @param strModuleItemSecurityName
	 * @param right
	 */
	public boolean HasModuleItemRight(String strModuleItemSecurityName, SecurityRight right){
		return false;
	}

	/**
	 * 
	 * @param strModuleSecurityName
	 * @param strModuleItemSecurityName
	 * @param right
	 */
	public boolean HasModuleItemRight(String strModuleSecurityName, String strModuleItemSecurityName, SecurityRight right){
		return false;
	}

	/**
	 * 
	 * @param strGroupId
	 * @param strModuleItemSecurityName
	 * @param right
	 */
	public boolean HasModuleItemRightForGroup(String strGroupId, String strModuleItemSecurityName, SecurityRight right){
		return false;
	}

	/**
	 * 
	 * @param strGroupId
	 * @param strModuleSecurityName
	 * @param strModuleItemSecurityName
	 * @param right
	 */
	public boolean HasModuleItemRightForGroup(String strGroupId, String strModuleSecurityName, String strModuleItemSecurityName, SecurityRight right){
		return false;
	}

	/**
	 * 
	 * @param strRelationshipName
	 * @param right
	 */
	public boolean HasRelationshipRight(String strRelationshipName, SecurityRight right){
		return false;
	}

	/**
	 * 
	 * @param strGroupId
	 * @param strRelationshipName
	 * @param right
	 */
	public boolean HasRelationshipRightForGroup(String strGroupId, String strRelationshipName, SecurityRight right){
		return false;
	}

	public void RequestSupressSecurity(){

	}

	/**
	 * 
	 * @param iSecurityGroup
	 */
	public ISecurityGroup SaveSecurityGroup(ISecurityGroup iSecurityGroup){
		return null;
	}

}