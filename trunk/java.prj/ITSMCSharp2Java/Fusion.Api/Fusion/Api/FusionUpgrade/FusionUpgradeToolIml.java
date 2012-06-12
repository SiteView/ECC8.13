package Fusion.Api.FusionUpgrade;
import Fusion.Api.FusionApi;
import Fusion.Api.FusionUpgrade.Defs.ExportDef;
import Fusion.Api.IFusionApi;
import Fusion.Api.FusionUpgrade.Defs.ExportDefinitionItemDef;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:41
 */
public class FusionUpgradeToolIml extends IValidationSources implements IDisposable {

	private String EMAIL_ASSOCIATED_PROFILE_EMPLOYEE_NAME = "EmailAssociatedProfileEmployee";
	private String EMAIL_CONTAINS_ATTACHMENT_NAME = "EmailContainsAttachment";
	private FusionApi m_api;
	private String m_arrBOsFields[][] = new String[][] { new String[] { "ScheduledJob.RecId" }, new String[] { "ScheduledJobHistory.RecId" }, new String[] { "JobClass.RecId" }, new String[] { "TimeUnit.RecId" } };
	private String m_arrBOsNames[] = new String[] { "ScheduledJob", "ScheduledJobHistory", "JobClass", "TimeUnit" };
	private boolean m_bFUDValidate;
	private boolean m_bIsNotOverrideDB;
	private CalculatingResult m_CalcResult;
	private Fusion.DefinitionTransformation.DefinitionSet m_definitionSet = null;
	private Map m_dictDbNames;
	private ExportDef m_ExportDef;
	private ArrayList m_listValidatedObjs = new ArrayList();
	private ProgressEventArgs m_ProgressEventArgs = new ProgressEventArgs();
	private String m_strDefinitionSetFile;
	private String m_strXMLDef;

	public FusionUpgradeToolIml(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param api
	 */
	public FusionUpgradeToolIml(IFusionApi api){

	}

	/**
	 * 
	 * @param strId
	 */
	public void AddValidateObject(String strId){

	}

	public Fusion.Application.ApplicationDefinitionRepository Adr(){
		return null;
	}

	public Map AllTableKeyIndexNames(){
		return null;
	}

	/**
	 * 
	 * @param strId
	 * @param strPerspective
	 */
	protected String BuildIdPerspectiveKey(String strId, String strPerspective){
		return "";
	}

	public CalculatingResult CalcResult(){
		return null;
	}

	/**
	 * 
	 * @param eventArg
	 */
	protected void ChangeProgess(EventArgs eventArg){

	}

	private void CheckConflicts(){

	}

	public void CommitCalendarFeatureDefenitionSet(){

	}

	public void CommitComplianceUtilityDefenitionSet(){

	}

	private void CommitData(){

	}

	private void CommitDefenitionSet(){

	}

	public void CommitEmailDefenitionSet(){

	}

	public void CommitScheduledJobDefenitionSet(){

	}

	public void CommitUserPresenceDefenitionSet(){

	}

	/**
	 * 
	 * @param strType
	 * @param strId
	 */
	public boolean DefinitionObjectExistsForId(String strType, String strId){
		return false;
	}

	/**
	 * 
	 * @param strType
	 * @param strId
	 * @param strPerspective
	 */
	public boolean DefinitionObjectExistsForId(String strType, String strId, String strPerspective){
		return false;
	}

	/**
	 * 
	 * @param strType
	 * @param strName
	 */
	public boolean DefinitionObjectExistsForName(String strType, String strName){
		return false;
	}

	/**
	 * 
	 * @param strType
	 * @param strName
	 * @param strPerspective
	 */
	public boolean DefinitionObjectExistsForName(String strType, String strName, String strPerspective){
		return false;
	}

	public EventHandler DefinitionResolveConflict(){
		return null;
	}

	public String DefinitionSetFile(){
		return "";
	}

	public EventHandler DefinitionSetMessage(){
		return null;
	}

	public Fusion.DefinitionTransformation.DefinitionSet DefSet(){
		return null;
	}

	/**
	 * 
	 * @param strBOName
	 * @param arrBOFields
	 */
	private void DeleteAllBOData(String strBOName, String[] arrBOFields){

	}

	private void DeleteAllBOsDataForScheduledJobWizard(){

	}

	/**
	 * 
	 * @param strField
	 * @param strPerspective
	 */
	public DefinitionStatus DetermineFieldStatus(String strField, String strPerspective){
		return null;
	}

	public void Dispose(){

	}

	public ExportDef ExportDefinition(){
		return null;
	}

	private ~FusionUpgradeToolIml(){

	}

	/**
	 * 
	 * @param scope
	 * @param strScopeOwner
	 * @param strType
	 * @param strId
	 * @param bStepUpChain
	 */
	public DefinitionStatus GetAdrDefinitionStatusById(Scope scope, String strScopeOwner, String strType, String strId, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scope
	 * @param strScopeOwner
	 * @param strType
	 * @param strId
	 * @param strPerspective
	 * @param bStepUpChain
	 */
	public DefinitionStatus GetAdrDefinitionStatusById(Scope scope, String strScopeOwner, String strType, String strId, String strPerspective, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scope
	 * @param strScopeOwner
	 * @param strType
	 * @param strName
	 * @param bStepUpChain
	 */
	public DefinitionStatus GetAdrDefinitionStatusByName(Scope scope, String strScopeOwner, String strType, String strName, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param scope
	 * @param strScopeOwner
	 * @param strType
	 * @param strName
	 * @param strPerspective
	 * @param bStepUpChain
	 */
	public DefinitionStatus GetAdrDefinitionStatusByName(Scope scope, String strScopeOwner, String strType, String strName, String strPerspective, boolean bStepUpChain){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strName
	 * @param strPerspective
	 */
	private IDefinition GetDefinetionByName(String strType, String strName, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strId
	 */
	public DefinitionStatus GetDefinitionStatusById(String strType, String strId){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strId
	 * @param strPerspective
	 */
	public DefinitionStatus GetDefinitionStatusById(String strType, String strId, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strName
	 */
	public DefinitionStatus GetDefinitionStatusByName(String strType, String strName){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strName
	 * @param strPerspective
	 */
	public DefinitionStatus GetDefinitionStatusByName(String strType, String strName, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param strField
	 */
	public DefinitionStatus GetFieldStatus(String strField){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param strPerspective
	 */
	public DefinitionStatus GetFieldStatus(String strField, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param strField
	 * @param strInBusObName
	 */
	public DefinitionStatus GetFieldStatusInBussinessObject(String strField, String strInBusObName){
		return null;
	}

	/**
	 * 
	 * @param strDefType
	 * @param strDefKey
	 * @param bName
	 */
	private IDefinition GetFUDDefinition(String strDefType, String strDefKey, boolean bName){
		return null;
	}

	/**
	 * 
	 * @param strXML
	 * @param charsArray
	 */
	private StringBuilder GetStringBuilder(String strXML, char[] charsArray){
		return null;
	}

	public boolean IsNotOverrideDB(){
		return false;
	}

	/**
	 * 
	 * @param defStatus
	 */
	private boolean IsOverrideRule(DefinitionStatus defStatus){
		return null;
	}

	public MetaDataRepository Mdr(){
		return null;
	}

	/**
	 * 
	 * @param messList
	 */
	protected void OnDefinitionSetMessage(MessageInfoList messList){

	}

	/**
	 * 
	 * @param strError
	 * @param status
	 */
	protected void OnThreadFinish(String strError, ProgressStatus status){

	}

	/**
	 * 
	 * @param valDef
	 */
	protected void OnValidateMessage(IValidateDefinition valDef){

	}

	public BllOrchestrator Orchestrator(){
		return null;
	}

	/**
	 * 
	 * @param defExp
	 */
	private boolean ProcessCalendarBODef(ExportDefinitionItemDef defExp){
		return null;
	}

	public EventHandler ProgressChanged(){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param fudOperation
	 */
	private boolean ResolveNameConflict(IDefinition def, FUDOperationType fudOperation){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	private boolean ResolveReferencesConflict(IDefinition def){
		return null;
	}

	public void SaveDefinitionSet(){

	}

	/**
	 * 
	 * @param strMessage
	 */
	private void SendMessage(String strMessage){

	}

	public EventHandler ThraedFinish(){
		return null;
	}

	public void UpgradeCalendarFeatureDefinitionSet(){

	}

	public void UpgradeComplianceUtilityDefinitionSet(){

	}

	private void UpgradeDefinitionSet(){

	}

	public void UpgradeEmailDefinitionSet(){

	}

	public void UpgradeScheduledJobDefinitionSet(){

	}

	public void UpgradeUserPresenceDefinitionSet(){

	}

	public ArrayList ValidatedObjects(){
		return null;
	}

	public EventHandler ValidatingMessage(){
		return null;
	}

	public void ValidationCalendarUpgradeDefenition(){

	}

	public void ValidationComplianceUtilityUpgradeDefenition(){

	}

	public void ValidationDefenition(){

	}

	public void ValidationDefenitionSet(){

	}

	public void ValidationEmailUpgradeDefenition(){

	}

	public void ValidationScheduledJobUpgradeDefenition(){

	}

	private void ValidationUpgradeDefenition(){

	}

	public void ValidationUserPresenceUpgradeDefenition(){

	}

	public String XMLDefinition(){
		return "";
	}

}