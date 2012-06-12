package Fusion.Api;

import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:33
 */
public class BusinessObjectDef extends BllDefinitionObject {

	public BusinessObjectDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public BusinessObjectDef(Object fusionObject){

	}

	/**
	 * 
	 * @param fldDef
	 */
	public void AddField(Fusion.Api.FieldDef fldDef){

	}

	/**
	 * 
	 * @param State
	 */
	public void AddImportantState(String State){

	}

	public boolean AllowDerivation(){
		return false;
	}

	public boolean AllowEditingInFinalState(){
		return false;
	}

	public boolean AllowEmbedding(){
		return false;
	}

	public boolean AllowSingleLevelDerivationOnly(){
		return false;
	}

	public boolean AllowsTightCoupling(){
		return false;
	}

	public boolean AllowViaRelatedSearch(){
		return false;
	}

	public String AssociatedImage(){
		return "";
	}

	public String AuditingBusinessObjectDefName(){
		return "";
	}

	public String BaseClass(){
		return "";
	}

	/**
	 * 
	 * @param strBusObName
	 */
	public static String BaseName(String strBusObName){
		return "";
	}

	/**
	 * 
	 * @param strFieldAnnotation
	 * @param strFieldLinkAnnotation
	 */
	public String BuildFieldName(String strFieldAnnotation, String strFieldLinkAnnotation){
		return "";
	}

	public Fusion.Api.BusObDefRights BusObDefRights(){
		return null;
	}

	public String Category(){
		return "";
	}

	public boolean ChildOfGroup(){
		return false;
	}

	public static String ClassName(){
		return "";
	}

	public boolean CommonlyUsed(){
		return false;
	}

	/**
	 * 
	 * @param fieldType
	 */
	public Fusion.Api.FieldDef CreateField(FieldCategory fieldType){
		return null;
	}

	public DataTable DataTableForDef(){
		return null;
	}

	public Fusion.Api.FieldDef DerivationNameField(){
		return null;
	}

	public boolean DerivedClass(){
		return false;
	}

	/**
	 * 
	 * @param strBusObName
	 */
	public static String DerivedPartOfName(String strBusObName){
		return "";
	}

	public Fusion.Api.FieldDef DisplayNameOrId(){
		return null;
	}

	public boolean EnforceConcurrency(){
		return false;
	}

	public boolean EntireTableCacheable(){
		return false;
	}

	public int EntireTableCacheableState(){
		return 0;
	}

	public String ExternalSourceId(){
		return "";
	}

	public String ExternalSourceName(){
		return "";
	}

	public List FieldDefs(){
		return null;
	}

	public String FieldIdThatControlsGroupDerivation(){
		return "";
	}

	public String FieldIdThatControlsState(){
		return "";
	}

	public List FieldNames(){
		return null;
	}

	public String FieldNameThatControlsGroupDerivation(){
		return "";
	}

	public String FieldNameThatControlsState(){
		return "";
	}

	public List FieldsAndSubfields(){
		return null;
	}

	public Fusion.Api.FieldDef FieldThatContainsDisplayName(){
		return null;
	}

	public String FinalState(){
		return "";
	}

	public String FinalStateCommandText(){
		return "";
	}

	public boolean GeneratesBPCreateEvent(){
		return false;
	}

	public boolean GeneratesBPDeleteEvent(){
		return false;
	}

	public boolean GeneratesBPRetrieveEvent(){
		return false;
	}

	public boolean GeneratesBPUpdateEvent(){
		return false;
	}

	/**
	 * 
	 * @param strAnnotation
	 */
	public Fusion.Api.FieldDef GetAnnotatedField(String strAnnotation){
		return null;
	}

	/**
	 * 
	 * @param iDefObj
	 * @param bIncludeBase
	 * @param defLib
	 * @param strPerspectiveName
	 */
	public static List GetFamilyHolders(Fusion.Api.DefinitionObject iDefObj, boolean bIncludeBase, Fusion.Api.DefinitionLibrary defLib, String strPerspectiveName){
		return null;
	}

	/**
	 * 
	 * @param strFamilyName
	 * @param bIncludeBase
	 * @param defLib
	 * @param strPerspectiveName
	 */
	public static List GetFamilyHolders(String strFamilyName, boolean bIncludeBase, Fusion.Api.DefinitionLibrary defLib, String strPerspectiveName){
		return null;
	}

	/**
	 * 
	 * @param strField
	 */
	public Fusion.Api.FieldDef GetField(String strField){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public Fusion.Api.FieldDef GetFieldById(String strId){
		return null;
	}

	/**
	 * 
	 * @param strStorageName
	 */
	public Fusion.Api.FieldDef GetFieldFromStorageName(String strStorageName){
		return null;
	}

	/**
	 * 
	 * @param strField
	 */
	public Fusion.Api.FieldDef GetFieldOrSubfield(String strField){
		return null;
	}

	public List GetGroupSharedFields(){
		return null;
	}

	public List GetLinkFields(){
		return null;
	}

	/**
	 * 
	 * @param strRelationship
	 */
	public Fusion.Api.RelationshipDef GetRelationship(String strRelationship){
		return null;
	}

	/**
	 * 
	 * @param strRelatedBusObName
	 */
	public Fusion.Api.RelationshipDef GetRelationshipToBusOb(String strRelatedBusObName){
		return null;
	}

	public String GroupName(){
		return "";
	}

	/**
	 * 
	 * @param strName
	 */
	public boolean HasField(String strName){
		return false;
	}

	/**
	 * 
	 * @param strId
	 */
	public boolean HasFieldById(String strId){
		return false;
	}

	public boolean HasState(){
		return false;
	}

	public boolean HideInMaintenance(){
		return false;
	}

	public Fusion.Api.FieldDef IdField(){
		return null;
	}

	public List ImportantStates(){
		return null;
	}

	public boolean IsCacheable(){
		return false;
	}

	/**
	 * 
	 * @param strBusObName
	 */
	public static boolean IsDerivedClass(String strBusObName){
		return false;
	}

	/**
	 * 
	 * @param strClassName
	 */
	public boolean IsDerivedFrom(String strClassName){
		return false;
	}

	public boolean IsLinkedTable(){
		return false;
	}

	public boolean IsTightlyCoupledToBaseClass(){
		return false;
	}

	public boolean IsTopLevelClass(){
		return false;
	}

	public boolean IsValidationObject(){
		return false;
	}

	public String LinkedStorageName(){
		return "";
	}

	public boolean MasterObject(){
		return false;
	}

	public Fusion.Api.FieldDef ParentIdField(){
		return null;
	}

	public boolean ParentOfGroup(){
		return false;
	}

	public boolean PartOfGroup(){
		return false;
	}

	public boolean ReadOnly(){
		return false;
	}

	public String RecallState(){
		return "";
	}

	public String RecallStateCommandText(){
		return "";
	}

	public void RefreshRelationships(){

	}

	/**
	 * 
	 * @param defLib
	 */
	public void RefreshRelationships(Fusion.Api.DefinitionLibrary defLib){

	}

	public List RelationshipDefs(){
		return null;
	}

	public List RelationshipNames(){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public void RemoveFieldById(String strId){

	}

	/**
	 * 
	 * @param State
	 */
	public void RemoveImportantState(String State){

	}

	/**
	 * 
	 * @param fldNew
	 */
	public void ReplaceField(Fusion.Api.FieldDef fldNew){

	}

	public boolean RepresentsEntireGroup(){
		return false;
	}

	private Fusion.BusinessLogic.BusinessObjectDef WhoAmI(){
		return null;
	}

}