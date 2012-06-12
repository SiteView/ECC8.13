package Fusion.Api;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:17
 */
public class Relationship extends MetaObject {

	public Relationship(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public Relationship(Object fusionObject){

	}

	/**
	 * 
	 * @param busOb
	 */
	public boolean AddObject(Fusion.Api.BusinessObject busOb){
		return false;
	}

	/**
	 * 
	 * @param busOb
	 */
	public boolean AlreadyParented(Fusion.Api.BusinessObject busOb){
		return false;
	}

	public Fusion.Api.BusinessObjectCollection BusinessObjects(){
		return null;
	}

	public boolean CanAddNewObject(){
		return false;
	}

	/**
	 * 
	 * @param strType
	 */
	public boolean CanAddNewObject(String strType){
		return false;
	}

	/**
	 * 
	 * @param strType
	 */
	public boolean CanContainObjectOfType(String strType){
		return false;
	}

	public boolean CanDeleteObject(){
		return false;
	}

	/**
	 * 
	 * @param busOb
	 */
	public void ChangeParentToThisRelationship(Fusion.Api.BusinessObject busOb){

	}

	public static String ClassName(){
		return "";
	}

	public void Clear(){

	}

	/**
	 * 
	 * @param linkField
	 */
	public void ClearCurrentForLinkField(String linkField){

	}

	/**
	 * 
	 * @param bIncludeChildren
	 * @param bClearNewFlag
	 */
	public void ClearDirtyFlags(boolean bIncludeChildren, boolean bClearNewFlag){

	}

	/**
	 * 
	 * @param busOb
	 */
	public void ClearParentToThisRelationship(Fusion.Api.BusinessObject busOb){

	}

	/**
	 * 
	 * @param id
	 */
	public boolean Contains(String id){
		return false;
	}

	/**
	 * 
	 * @param linkField
	 * @param purpose
	 * @param switchTo
	 */
	public void CopyAndMakeCurrentForLinkField(String linkField, String purpose, Fusion.Api.BusinessObject switchTo){

	}

	public int Count(){
		return 0;
	}

	/**
	 * 
	 * @param makeCurrent
	 */
	public Fusion.Api.BusinessObject CreateNewObject(boolean makeCurrent){
		return null;
	}

	/**
	 * 
	 * @param name
	 * @param makeCurrent
	 */
	public Fusion.Api.BusinessObject CreateNewObject(String name, boolean makeCurrent){
		return null;
	}

	public Fusion.Api.BusinessObject CurrentBusinessObject(){
		return null;
	}

	public boolean DefaultToDeepQuery(){
		return false;
	}

	public Fusion.Api.RelationshipDef Definition(){
		return null;
	}

	public int DeleteAll(){
		return 0;
	}

	public Fusion.Api.BusinessObjectCollection DeletedBusinessObjects(){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 */
	public boolean DeleteObject(Fusion.Api.BusinessObject busOb){
		return false;
	}

	/**
	 * 
	 * @param strID
	 */
	public boolean DeleteObject(String strID){
		return false;
	}

	/**
	 * 
	 * @param busOb
	 * @param bComitted
	 */
	public boolean DeleteObject(Fusion.Api.BusinessObject busOb, boolean bComitted){
		return false;
	}

	/**
	 * 
	 * @param strID
	 * @param bComitted
	 */
	public boolean DeleteObject(String strID, boolean bComitted){
		return false;
	}

	/**
	 * 
	 * @param strName
	 * @param firstBusOb
	 */
	public Fusion.Api.BusinessObject FindRelatedBusinessObject(String strName, Fusion.Api.BusinessObject firstBusOb){
		return null;
	}

	/**
	 * 
	 * @param LinkField
	 */
	public Fusion.Api.BusinessObject GetCurrentObject(String LinkField){
		return null;
	}

	/**
	 * 
	 * @param strID
	 */
	public Fusion.Api.BusinessObject GetObject(String strID){
		return null;
	}

	public List GetObjects(){
		return null;
	}

	/**
	 * 
	 * @param columns
	 */
	public List GetObjects(List columns){
		return null;
	}

	/**
	 * 
	 * @param colOrderByFieldList
	 * @param columns
	 */
	public List GetObjectsInOrder(List colOrderByFieldList, List columns){
		return null;
	}

	/**
	 * 
	 * @param fieldsToOrderBy
	 * @param ascending
	 * @param columns
	 */
	public List GetObjectsInOrder(ArrayList fieldsToOrderBy, ArrayList ascending, List columns){
		return null;
	}

	/**
	 * 
	 * @param colOrderByFieldList
	 * @param columns
	 * @param strCategory
	 */
	public List GetObjectsInOrder(List colOrderByFieldList, List columns, String strCategory){
		return null;
	}

	/**
	 * 
	 * @param fieldToOrderBy
	 * @param ascending
	 * @param columns
	 */
	public List GetObjectsInOrder(String fieldToOrderBy, boolean ascending, List columns){
		return null;
	}

	/**
	 * 
	 * @param Category
	 */
	public List GetObjectsOfCategory(String Category){
		return null;
	}

	/**
	 * 
	 * @param type
	 * @param columns
	 * @param api
	 */
	public Fusion.Api.VirtualBusObList GetVirtualObjects(VirtualBusObListSupportedTypes type, List columns, IFusionApi api){
		return null;
	}

	public boolean IsDirty(){
		return false;
	}

	public boolean IsLoaded(){
		return false;
	}

	public void LoadIfRequired(){

	}

	/**
	 * 
	 * @param linkField
	 * @param switchTo
	 */
	public void MakeCurrentForLinkField(String linkField, Fusion.Api.BusinessObject switchTo){

	}

	/**
	 * 
	 * @param linkField
	 * @param purpose
	 * @param switchTo
	 */
	public void MakeCurrentForLinkField(String linkField, String purpose, Fusion.Api.BusinessObject switchTo){

	}

	/**
	 * 
	 * @param linkField
	 * @param purpose
	 * @param switchTo
	 */
	public void MoveAndMakeCurrentForLinkField(String linkField, String purpose, Fusion.Api.BusinessObject switchTo){

	}

	public Fusion.Api.BusinessObject OwningBusOb(){
		return null;
	}

	/**
	 * 
	 * @param mergeChanges
	 */
	public void Refresh(boolean mergeChanges){

	}

	/**
	 * 
	 * @param mergeChanges
	 * @param versioningOverride
	 */
	public void Refresh(boolean mergeChanges, String versioningOverride){

	}

	/**
	 * 
	 * @param mergeChanges
	 * @param versioningOverride
	 * @param fieldNames
	 */
	public void Refresh(boolean mergeChanges, String versioningOverride, List fieldNames){

	}

	/**
	 * 
	 * @param busOb
	 */
	public void ReplaceObject(Fusion.Api.BusinessObject busOb){

	}

	/**
	 * 
	 * @param strID
	 */
	public boolean RestoreDeletedObject(String strID){
		return false;
	}

	public boolean SaveChildrenWithParent(){
		return false;
	}

	/**
	 * 
	 * @param strID
	 */
	public boolean SetCurrentObject(String strID){
		return false;
	}

	private Fusion.BusinessLogic.Relationship WhoAmI(){
		return null;
	}

}