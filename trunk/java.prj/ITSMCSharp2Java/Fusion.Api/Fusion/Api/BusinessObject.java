package Fusion.Api;

import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:31
 */
public class BusinessObject extends MetaObject {

	private int depth;
	private boolean m_bHasCheckedRight;
	private boolean m_bHasViewRight;
	private boolean m_bSaving;
	private Object m_savingLock;

	public BusinessObject(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public BusinessObject(Object fusionObject){

	}

	/**
	 * 
	 * @param target
	 */
	public void AddSubscriber(INotifiableOnly target){

	}

	public boolean AllowBadData(){
		return false;
	}

	public boolean AllowEditIfInFinalState(){
		return false;
	}

	public String BusObDisplayOrBlank(){
		return "";
	}

	public String BusObDisplayOrId(){
		return "";
	}

	public boolean CheckConcurrency(){
		return false;
	}

	/**
	 * 
	 * @param api
	 */
	private void CheckLicensingBasedOnCount(IFusionApi api){

	}

	public static String ClassName(){
		return "";
	}

	public void Clear(){

	}

	/**
	 * 
	 * @param bIncludeChildren
	 * @param bClearNewFlag
	 */
	public void ClearDirtyFlags(boolean bIncludeChildren, boolean bClearNewFlag){

	}

	public Fusion.Api.BusinessObject Clone(){
		return null;
	}

	public boolean CommitChanges(){
		return false;
	}

	public Fusion.Api.BusinessObjectDef Definition(){
		return null;
	}

	/**
	 * 
	 * @param api
	 */
	public UpdateResult DeleteObject(IFusionApi api){
		return null;
	}

	public List FieldNames(){
		return null;
	}

	public List Fields(){
		return null;
	}

	/**
	 * 
	 * @param BusOb
	 * @param Relationship
	 * @param LinkField
	 * @param associatedRelationship
	 */
	public Fusion.Api.BusinessObject FindRelatedBusinessObject(String BusOb, String Relationship, String LinkField, String associatedRelationship){
		return null;
	}

	/**
	 * 
	 * @param strXml
	 */
	public void FromXml(String strXml){

	}

	/**
	 * 
	 * @param api
	 * @param bIncludeChildren
	 */
	public List GatherEvents(IFusionApi api, boolean bIncludeChildren){
		return null;
	}

	/**
	 * 
	 * @param strAnnotation
	 */
	public Fusion.Api.Field GetAnnotatedField(String strAnnotation){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strContents
	 */
	public Fusion.Api.Field GetAnnotatedField(String strName, String strContents){
		return null;
	}

	/**
	 * 
	 * @param fieldName
	 */
	public Fusion.Api.Field GetField(String fieldName){
		return null;
	}

	/**
	 * 
	 * @param fieldName
	 * @param associatedRelationship
	 */
	public Fusion.Api.Field GetField(String fieldName, String associatedRelationship){
		return null;
	}

	/**
	 * 
	 * @param fieldName
	 * @param associatedRelationship
	 * @param initVirtualField
	 */
	public Fusion.Api.Field GetField(String fieldName, String associatedRelationship, boolean initVirtualField){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public Fusion.Api.Field GetFieldById(String strId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.Field GetFieldOrSubfield(String strName){
		return null;
	}

	/**
	 * 
	 * @param strRelationship
	 */
	public Fusion.Api.Relationship GetRelationship(String strRelationship){
		return null;
	}

	/**
	 * 
	 * @param strID
	 */
	public Fusion.Api.Relationship GetRelationshipById(String strID){
		return null;
	}

	public Fusion.Api.Field GetStateField(){
		return null;
	}

	public boolean IsDirty(){
		return false;
	}

	public boolean IsInFinalState(){
		return false;
	}

	public boolean IsNew(){
		return false;
	}

	public boolean NoDataChecks(){
		return false;
	}

	public Fusion.Api.Relationship OwningRelationship(){
		return null;
	}

	/**
	 * 
	 * @param bNoDataChecks
	 */
	public void PostponeValidation(boolean bNoDataChecks){

	}

	public String RecId(){
		return "";
	}

	public List RelationshipNames(){
		return null;
	}

	public List Relationships(){
		return null;
	}

	public void RemoveAllSubscribers(){

	}

	/**
	 * 
	 * @param target
	 */
	public void RemoveSubscriber(INotifiableOnly target){

	}

	public boolean ResumeValidation(){
		return false;
	}

	/**
	 * 
	 * @param ur
	 */
	public boolean ResumeValidation(UpdateResult ur){
		return false;
	}

	/**
	 * 
	 * @param api
	 * @param bIncludeChildren
	 * @param bResetObject
	 */
	public UpdateResult SaveObject(IFusionApi api, boolean bIncludeChildren, boolean bResetObject){
		return null;
	}

	public boolean Saving(){
		return false;
	}

	/**
	 * 
	 * @param bDirty
	 */
	public void SetDirty(boolean bDirty){

	}

	/**
	 * 
	 * @param ur
	 * @param bDirty
	 */
	public void SetDirty(UpdateResult ur, boolean bDirty){

	}

	public String ToString(){
		return "";
	}

	public String ToXml(){
		return "";
	}

	/**
	 * 
	 * @param busObComposition
	 */
	public String ToXml(BusObXmlComposition busObComposition){
		return "";
	}

	/**
	 * 
	 * @param api
	 * @param updateResult
	 */
	private void UpdateCachedBusObs(IFusionApi api, UpdateResult updateResult){

	}

	public boolean Validate(){
		return false;
	}

	/**
	 * 
	 * @param ur
	 */
	public boolean Validate(UpdateResult ur){
		return false;
	}

	public Object Version(){
		return null;
	}

	public Fusion.BusinessLogic.BusinessObject WhoAmI(){
		return null;
	}

}