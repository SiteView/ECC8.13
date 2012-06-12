package Fusion.Api;

import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:45:20
 */
public class RelationshipDef extends BllDefinitionObject implements IModifyConstraints {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:45:20
	 */
	private class MessageTags {

		private String RelationshipDefRights_AllowChangeCardinalityId = "RelationshipDefRights.AllowChangeCardinality";
		private String RelationshipDefRights_AllowChangeConstraintId = "RelationshipDefRights.AllowChangeConstraint";
		private String RelationshipDefRights_AllowChangeRuleBasedPropertiesId = "RelationshipDefRights.AllowChangeRuleBasedProperties";

		public MessageTags(){

		}

		public void finalize() throws Throwable {

		}

		public String getRelationshipDefRights_AllowChangeCardinalityId(){
			return RelationshipDefRights_AllowChangeCardinalityId;
		}

		public String getRelationshipDefRights_AllowChangeConstraintId(){
			return RelationshipDefRights_AllowChangeConstraintId;
		}

		public String getRelationshipDefRights_AllowChangeRuleBasedPropertiesId(){
			return RelationshipDefRights_AllowChangeRuleBasedPropertiesId;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRelationshipDefRights_AllowChangeCardinalityId(String newVal){
			RelationshipDefRights_AllowChangeCardinalityId = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRelationshipDefRights_AllowChangeConstraintId(String newVal){
			RelationshipDefRights_AllowChangeConstraintId = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRelationshipDefRights_AllowChangeRuleBasedPropertiesId(String newVal){
			RelationshipDefRights_AllowChangeRuleBasedPropertiesId = newVal;
		}

	}

	public RelationshipDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionApi
	 */
	public RelationshipDef(IFusionApi fusionApi){

	}

	/**
	 * 
	 * @param fusionObject
	 */
	public RelationshipDef(Object fusionObject){

	}

	/**
	 * 
	 * @param constraint
	 */
	public int AddConstraint(Fusion.Api.ConstraintDef constraint){
		return 0;
	}

	/**
	 * 
	 * @param constraint
	 */
	public void AddPushConstraint(Fusion.Api.ConstraintDef constraint){

	}

	/**
	 * 
	 * @param def
	 */
	public int AddRollUp(Fusion.Api.RollUpDef def){
		return 0;
	}

	public boolean AllowDerivations(){
		return false;
	}

	public boolean AutoCreateBasedOnDerivationSpecifier(){
		return false;
	}

	public Fusion.Api.RuleDef BeforeAdd(){
		return null;
	}

	public Fusion.Api.RuleDef CanAddNew(){
		return null;
	}

	public Fusion.Api.RuleDef CanChangeState(){
		return null;
	}

	/**
	 * 
	 * @param strType
	 */
	public boolean CanContainObjectOfType(String strType){
		return false;
	}

	public Fusion.Api.RuleDef CanDelete(){
		return null;
	}

	public Fusion.Api.RuleDef CanSave(){
		return null;
	}

	public RelationshipCategory Category(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public int ConstraintCount(){
		return 0;
	}

	public List Constraints(){
		return null;
	}

	public String CustomLinkObjectId(){
		return "";
	}

	public String CustomLinkObjectName(){
		return "";
	}

	public String CustomLinkOwnerCategoryFieldId(){
		return "";
	}

	public String CustomLinkOwnerCategoryFieldName(){
		return "";
	}

	public String CustomLinkOwnerIdFieldId(){
		return "";
	}

	public String CustomLinkOwnerIdFieldName(){
		return "";
	}

	public String CustomLinkTargetCategoryFieldId(){
		return "";
	}

	public String CustomLinkTargetCategoryFieldName(){
		return "";
	}

	public String CustomLinkTargetIdFieldId(){
		return "";
	}

	public String CustomLinkTargetIdFieldName(){
		return "";
	}

	public String DefaultDerivation(){
		return "";
	}

	public String DerivationSpecifier(){
		return "";
	}

	public boolean DontPushStandardConstraints(){
		return false;
	}

	/**
	 * 
	 * @param busObDef
	 */
	public List GetLinkFieldsAssociatedWithEmbeddedRelationship(Fusion.Api.BusinessObjectDef busObDef){
		return null;
	}

	/**
	 * 
	 * @param busObDef
	 * @param groupMemberName
	 */
	public List GetLinkFieldsAssociatedWithEmbeddedRelationship(Fusion.Api.BusinessObjectDef busObDef, String groupMemberName){
		return null;
	}

	/**
	 * 
	 * @param nIndex
	 */
	public Fusion.Api.RollUpDef GetRollUpAt(int nIndex){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public Fusion.Api.RollUpDef GetRollUpById(String strId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.RollUpDef GetRollUpByName(String strName){
		return null;
	}

	public boolean HasDerivationSpecifer(){
		return false;
	}

	public boolean InfiniteMax(){
		return false;
	}

	public boolean IsAssociatedEmbeddedRelationship(){
		return false;
	}

	public boolean IsAssociatedRelationship(){
		return false;
	}

	public boolean IsContainedRelationship(){
		return false;
	}

	public boolean IsContainsEmbeddedRelationship(){
		return false;
	}

	public boolean IsContainsRelationship(){
		return false;
	}

	public boolean IsEmbeddedRelationship(){
		return false;
	}

	public boolean IsReadOnly(){
		return false;
	}

	public boolean LinkBased(){
		return false;
	}

	public int MaxCardinality(){
		return 0;
	}

	public int MinCardinality(){
		return 0;
	}

	public boolean OnlyPushForNewRecords(){
		return false;
	}

	public String OwnerId(){
		return "";
	}

	public String OwnerName(){
		return "";
	}

	public List PushConstraints(){
		return null;
	}

	public Fusion.Api.RelationshipDefRights RelationshipDefRights(){
		return null;
	}

	public void RemoveAllConstraints(){

	}

	public void RemoveAllPushConstraints(){

	}

	public void RemoveAllRollUps(){

	}

	/**
	 * 
	 * @param constraint
	 */
	public void RemoveConstraint(Fusion.Api.ConstraintDef constraint){

	}

	/**
	 * 
	 * @param nIndex
	 */
	public void RemoveConstraintAt(int nIndex){

	}

	/**
	 * 
	 * @param constraint
	 */
	public void RemovePushConstraint(Fusion.Api.ConstraintDef constraint){

	}

	/**
	 * 
	 * @param def
	 */
	public void RemoveRollUp(Fusion.Api.RollUpDef def){

	}

	/**
	 * 
	 * @param nIndex
	 */
	public void RemoveRollUpAt(int nIndex){

	}

	public boolean Reverse(){
		return false;
	}

	public String ReverseName(){
		return "";
	}

	public List RollUps(){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param nIndex
	 */
	public void SetRollUpAt(Fusion.Api.RollUpDef def, int nIndex){

	}

	public String StorageId(){
		return "";
	}

	public String SwitchHandler(){
		return "";
	}

	public Fusion.Api.BusinessObjectDef TargetBusinessObjectDef(){
		return null;
	}

	public String TargetId(){
		return "";
	}

	public String TargetName(){
		return "";
	}

	public boolean TargetsSavedWithOwner(){
		return false;
	}

	/**
	 * 
	 * @param nIndex
	 */
	public Fusion.Api.ConstraintDef this(int nIndex){
		return null;
	}

	public boolean UsesCustomLinkObject(){
		return false;
	}

	private Fusion.BusinessLogic.RelationshipDef WhoAmI(){
		return null;
	}

}