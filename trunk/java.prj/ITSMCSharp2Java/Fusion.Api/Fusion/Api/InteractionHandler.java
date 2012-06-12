package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:52
 */
public final class InteractionHandler extends IDisposable {

	private boolean m_bIsDisposed = false;
	private IOrchestrator m_orch = null;

	public InteractionHandler(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param orch
	 */
	public InteractionHandler(IOrchestrator orch){

	}

	public NewRuleEventHandler AddNewRule(){
		return null;
	}

	public ApplicationSearchRequestHandler ApplicationSearchRequest(){
		return null;
	}

	public ApplicationServiceRequestHandler ApplicationServiceRequest(){
		return null;
	}

	public Fusion.Api.CancelOperationHandler CancelOperation(){
		return null;
	}

	public Fusion.Api.CommitStatusHandler CommitStatus(){
		return null;
	}

	public DisplayListOfObjectsEventHandler DisplayListOfObjects(){
		return null;
	}

	public void Dispose(){

	}

	/**
	 * 
	 * @param bDisposing
	 */
	private void Dispose(boolean bDisposing){

	}

	public Fusion.Api.ExportImportFinishedEventHandler ExportFinished(){
		return null;
	}

	public Fusion.Api.ExportImportRowEventHandler ExportRow(){
		return null;
	}

	public Fusion.Api.ExportImportTableEventHandler ExportTable(){
		return null;
	}

	/**
	 * 
	 * @param se
	 */
	public IBusObKeyList FireApplicationSearchRequest(SearchRequestEventArgs se){
		return null;
	}

	/**
	 * 
	 * @param e
	 */
	public void FireApplicationServiceRequest(ServiceRequestEventArgs e){

	}

	/**
	 * 
	 * @param args
	 */
	public void FireCancelOperationEvent(EventArgs args){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	public Object FireDisplayListOfObjectsEvent(Object sender, DisplayObjectListEventArgs e){
		return null;
	}

	/**
	 * 
	 * @param e
	 */
	public void FireFormActionRequest(BaseFormActionEventArgs e){

	}

	/**
	 * 
	 * @param se
	 */
	public IBusObKeyList FireSimpleSearchRequest(SearchRequestEventArgs se){
		return null;
	}

	public FormActionRequestHandler FormActionRequest(){
		return null;
	}

	public Fusion.Api.ExportImportFinishedEventHandler ImportFinished(){
		return null;
	}

	public Fusion.Api.ExportImportRowEventHandler ImportRow(){
		return null;
	}

	public Fusion.Api.ExportImportTableEventHandler ImportTable(){
		return null;
	}

	/**
	 * 
	 * @param applicationServiceRequest
	 * @param applicationSearchRequest
	 * @param simpleSearchRequest
	 * @param formActionRequest
	 */
	public void InitializeForApplication(ApplicationServiceRequestHandler applicationServiceRequest, ApplicationSearchRequestHandler applicationSearchRequest, ApplicationSearchRequestHandler simpleSearchRequest, FormActionRequestHandler formActionRequest){

	}

	private ~InteractionHandler(){

	}

	public boolean IsDisposed(){
		return null;
	}

	public Fusion.Api.LoadDefEventHandler LoadDef(){
		return null;
	}

	public Fusion.Api.LoadSystemVersionEventHandler LoadSystemVersion(){
		return null;
	}

	public MadDefEventHandler MadDef(){
		return null;
	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	public RuleDef NewRule(Object sender, NewRuleEventArgs e){
		return null;
	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnCancelOperation(Object sender, EventArgs e){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnCommitStatus(Object sender, Fusion.BusinessLogic.CommitEventArgs e){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnExportFinished(Object sender, Fusion.BusinessLogic.ExportImportFinishedEventArgs e){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnExportRow(Object sender, Fusion.BusinessLogic.ExportImportRowEventArgs e){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnExportTable(Object sender, Fusion.BusinessLogic.ExportImportTableEventArgs e){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnImportFinished(Object sender, Fusion.BusinessLogic.ExportImportFinishedEventArgs e){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnImportRow(Object sender, Fusion.BusinessLogic.ExportImportRowEventArgs e){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnImportTable(Object sender, Fusion.BusinessLogic.ExportImportTableEventArgs e){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnLoadDef(Object sender, Fusion.BusinessLogic.LoadDefEventArgs e){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnLoadSystemVersion(Object sender, Fusion.BusinessLogic.LoadSystemVersionEventArgs e){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnTableChange(Object sender, Fusion.BusinessLogic.TableChangeEventArgs e){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnTableChangeProgress(Object sender, Fusion.BusinessLogic.TableChangeProgressEventArgs e){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnValidationFailed(Object sender, Fusion.BusinessLogic.ValidationEventArgs e){

	}

	private Fusion.BusinessLogic.InteractionHandler RealIH(){
		return null;
	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	public IDefinition RequestMadOfDef(Object sender, MadDefEventArgs e){
		return null;
	}

	public ApplicationSearchRequestHandler SimpleSearchRequest(){
		return null;
	}

	private void SubscribeToEvents(){

	}

	public Fusion.Api.TableChangeEventHandler TableChange(){
		return null;
	}

	public Fusion.Api.TableChangeProgressEventHandler TableChangeProgress(){
		return null;
	}

	private void UnsubscribeEvents(){

	}

	public Fusion.Api.ValidationFailedEventHandler ValidationFailed(){
		return null;
	}

}